TITLE	.HW6 (EXE) Editor
	.MODEL	SMALL
	.STACK	64
	.DATA


BIODATA SEGMENT AT  40H	; for keyboard buffer
    ORG 1AH		; from hw5
HEADPTR DW  ?
TAILPTR DW  ?
KBBUF   DB  ?
BIODATA ENDS

BUFFERSIZE	EQU	256
BUFFER	DB	BUFFERSIZE-1 DUP (0FFH)
ENDOFBUFFER	DB	0FFH
CURSUR	DW	0	;current cursur position on buffer
ISEDIT	DB	0	; 0 : EDIT, 1 : INSERT

PREVCURSURSIZE	DW	?	; for restore
PREVATTRIBUTE	DB	?	; environment before execute

	.CODE
	.386	;for PUSHA
A10MAIN PROC	NEAR
	MOV	AX, @data
	MOV DS, AX
	MOV ES, AX
	CALL	B10INIT

A20MAINLOOP:
	CALL	C10GETCHAR
	CALL	F10ISSPECIALLKEY; if function key pressed
	JE	A30ONSPECIALKEY	; then a30
	JNE	A40ONASCKII	; else, a40
	
A30ONSPECIALKEY:
	CMP AL, 1BH	; if ESC pressed
	JE	A60END	; end.
	CALL	D10ONSPECIALKEY
	JMP	A50DISPLAY
A40ONASCKII:
	CALL	E10ONASCII
	JMP	A50DISPLAY	
A50DISPLAY:
	CALL	I10DISPLAY
	JMP	A20MAINLOOP
A60END:
	;restore attributes
	MOV	AH, 01H		
	MOV	CX, PREVCURSURSIZE
	INT	10H	

	MOV	AX, 601H	;scroll up 1
	MOV	CX,	0000
	MOV	DX, 184FH
	MOV	BH, PREVATTRIBUTE
	INT	10H

	; set cursur left,down
	MOV	AH, 02H
	MOV	BH, 00
	MOV	DH, 24
	MOV	DL, 0
	INT 10H
	
	;then print buffer.
	CALL L10DISPLAYWIHTOUTCLEAR
	
	MOV AX, 4C00H
	INT 21H 
A10MAIN	ENDP


B10INIT	PROC	NEAR
	PUSHA
B00GETCURRENTSTATUS:
	MOV	AH, 03H
	MOV	BH, 00
	INT	10H
	MOV	PREVCURSURSIZE, CX
B001GETCURRENTATTRIBUTE:
	MOV	AH, 08H
	MOV	BH, 00
	INT	10H
	MOV	PREVATTRIBUTE,	AH
B20CLEARSCREEN:
	CALL J10CLEAR
B30SETCURSORSIZE:
	MOV	AH, 01H
	MOV	CH, 00
	MOV	CL, 14
	INT	10H	
	POPA
	RET
B10INIT	ENDP

C10GETCHAR	PROC	NEAR	;this code is from hw5
    MOV AX, 40H
    MOV ES, AX

C20WAIT:
    MOV BX, ES:HEADPTR	; 40H:1AH, HEAD of Keyboard Buffer
    MOV CX, ES:TAILPTR	; 40H:1CH, TAIL of Keyboard Buffer
    CMP BX, CX		; is Head and Tail Same?
    JE  C20WAIT		; then wait, becuase no key pressed yet

    MOV AX, ES:[BX]	; Get ScanCode and ASCII Into AX
    ADD BX, 2		; Add 2byte to HEAD
    CMP BX, 3EH		; if HEAD over buffer?
    JNE C30EXIT

    MOV BX, 1EH		; then initialize that into 40H:1EH, start of buffer.
C30EXIT:
    MOV ES:HEADPTR, BX	; save changed HEAD.
	MOV	BX, @data
	MOV ES, BX
    RET
C10GETCHAR	ENDP

D10ONSPECIALKEY	PROC	NEAR
	CMP AL, 1BH	;	ESC
	JE	D20ONESC
	CMP	AL, 08H	;	BACKSPACE
	JE	D21ONBACKSPACE
	CMP	AX,	53E0H	;	DELETE
	JE	D22ONDELETE
	CMP	AX,	52E0H	;	INSERT
	JE	D23ONINSERT
	CMP	AX,	50E0H	;	DOWNARROW
	JE	D24ONDOWNARROW
	CMP	AX,	48E0H	;	UPARROW
	JE	D25ONUPARROW
	CMP	AX,	4BE0H	;	LEFTARROW
	JE	D26ONLEFTARROW
	CMP	AX,	4DE0H	;	RIGHTARROW
	JE	D27ONRIGHTARROW

D20ONESC:
	JMP	D30END
D21ONBACKSPACE:
	CMP CURSUR, 0	; no char in buffer?
	JE	D30END	; then end.
		
	;mov (cur-1 ~ buffer-1) <- (cur ~ buffer)

	; cur--;
	; for n = cur ~ (buffersize - cursur -1 )
	; buffer[n] = buffer[n+1]

	DEC	CURSUR
	MOV	CX, BUFFERSIZE - 1
	SUB	CX,	CURSUR
	LEA	DI, BUFFER
	ADD	DI, CURSUR
	LEA	SI,	BUFFER+1
	ADD	SI, CURSUR
	CLD
	REP MOVSB
	JMP	D30END
D22ONDELETE:
	LEA	DI, BUFFER
	ADD	DI, CURSUR
	CMP	BYTE PTR [DI], 0FFH	; cursur is on end of buffer?
	JE	D30END			; then there are nothing delete.

	;mov (cur ~ buffer-1) <- (cur+1 ~ buffer)

	; for n = cur ~ (buffersize - cursur - 1)
	; buffer[n] = buffer[n+1]
	

	MOV	CX, BUFFERSIZE - 1
	SUB	CX,	CURSUR
	LEA	DI, BUFFER
	ADD	DI, CURSUR
	LEA	SI,	BUFFER+1
	ADD	SI, CURSUR
	CLD
	REP MOVSB
	JMP	D30END
D23ONINSERT:
	CALL	H10TOGGLEEDITMODE
	JMP	D30END
D24ONDOWNARROW:
	CALL	K10CALCULATECURSUR	; (dh, dl) <- cursur position
	MOV	CX, DX			; store postion into CX
	LEA	DI, BUFFER
	ADD	DI, CURSUR

	; calculate next cursur position for next character from buffer
	; then check  
	; (next row) <= (current row + 1)
	; && (next column <= current column)
	; find last one that satisfy above condition
	; then set cursur to that last one. 

D241MAINLOOP:
	CMP	BYTE PTR [DI], 0FFH	; end of buffer?
	JE	D249END			
	CMP	BYTE PTR [DI], 0DH	; enter?
	JE	D242ENTER
	JNE	D243NOTENTER
D242ENTER:			; on enter
	INC	DH		; increase row
	MOV	DL, 0		; and set column 0
	JMP	D244DECISION
D243NOTENTER:
	INC	DL		; on non-enter, inc column
	CMP	DL, 80		; over width?
	JE	D242ENTER	; then process like enter key pressed
	JMP	D244DECISION
D244DECISION:
	MOV	BH, CH		; if(current row +2 == next row) 
	ADD	BH, 2
	CMP	BH, DH
	JE	D249END		; then exit.
	MOV BH, CH		; if(current row + 1 == next row)
	ADD BH, 1
	CMP BH, DH
	JE D245ONEROWDOWN	; then D245
	JNE D246ENDOFLOOP	; else, D246
D245ONEROWDOWN:
	CMP DL, CL		; if(nextcolumn <= current column)
	JA	D249END		; false -> exit
	JBE	D246ENDOFLOOP	; true -> D246

D246ENDOFLOOP:
	INC	CURSUR		; inc cursur
	INC	DI		; next character
	JMP	D241MAINLOOP	; continue loop

D249END:
	JMP	D30END

D25ONUPARROW:

	; similar with down-arrow.
	; comparing cursur position from start of buffer
	; not next of current.

	; calculate cursur position for next character from start of buffer
	; then check  
	; (row + 1) <= (current row)
	; && (column <= current column)
	; find last one that satisfy above condition
	; then set cursur to that last one. 


	CALL	K10CALCULATECURSUR
	MOV	CX, DX		; store current row, col into CX
	LEA	DI, BUFFER	; character from start of buffer
	MOV	DX, 0		; not next of current cursur.
D251MAINLOOP:
	CMP BYTE PTR [DI], 0FFH	; if there are no character in buffer
	JE	D259END		; then exit
	CMP	BYTE PTR [DI], 0DH
	JE	D252ENTER
	JNE	D253NOTENTER
D252ENTER:
	INC	DH		; inc row
	MOV	DL, 0		; set column 0
	JMP	D254DECISION
D253NOTENTER:
	INC	DL		; inc column
	CMP	DL, 80		; if column > width
	JE	D252ENTER	; process like enter pressed
	JMP	D254DECISION
D254DECISION:
	MOV	BH, DH		; compare row+1 , current row 
	ADD	BH, 1
	CMP	BH, CH
	JB	D256ENDOFLOOP	; row+1 < current row -> continue loop
	JE	D255ONEROWUP	; row+1 == current row -> more dicision
	JA	D259END		; row == current row -> exit
D255ONEROWUP:
	CMP DL, CL		; on row+1 == current row,
	JA	D259END		; col > current col -> exit
	JBE	D256ENDOFLOOP	; else, continue loop

D256ENDOFLOOP:
	INC	DI		; next character
	JMP	D251MAINLOOP

D259END:
	LEA SI, BUFFER
	SUB	DI, SI
	MOV	CURSUR, DI	; set 1 dimension cursur.
	JMP	D30END

D26ONLEFTARROW:
	CMP	CURSUR, 0	; if cursur is on left-top
	JE	D30END		; exit
	DEC	CURSUR		; else, dec cursur
	JMP	D30END
D27ONRIGHTARROW:
	LEA	DI, BUFFER	; if next character of cursur
	ADD	DI, CURSUR	; is end of buffer
	CMP	BYTE PTR [DI], 0FFH
	JE	D30END		; then exit
	INC	CURSUR		; else inc cursur
	JMP	D30END
D30END:
	RET
D10ONSPECIALKEY	ENDP

E10ONASCII	PROC	NEAR
	LEA	DI, BUFFER
	ADD 	DI, CURSUR	; DI = buffer[cursur]
	CALL 	G10ISEDITMODE
	JE	E20ONEDIT
	JNE	E30ONINSERT
E20ONEDIT:
	; on edit mode, if next character of cursur is
	; enter or end of buffer,
	; then it can processed like insert mode.
	CMP	BYTE PTR [DI], 0DH
	JE	E30ONINSERT
	CMP	BYTE PTR [DI], 0FFH
	JE	E30ONINSERT
				; else, just change character
	MOV	[DI], AL	; buffer[cursur] = AL;
	INC	CURSUR		; end inc cursur.
	JMP E40END
E30ONINSERT:

	; push back 1 character from cursur position.
	MOV	CX, BUFFERSIZE-1
	SUB	CX, CURSUR
	LEA	DI, BUFFER + BUFFERSIZE-1
	LEA	SI, BUFFER + BUFFERSIZE-2
	STD
	REP MOVSB
	
	; then just put character into space
	LEA	DI, BUFFER
	ADD 	DI, CURSUR
	MOV	[DI], AL
	INC	CURSUR
E40END:
	RET
E10ONASCII	ENDP

F10ISSPECIALLKEY	PROC	NEAR	; ZF. for JE or JNE
	CMP AL, 1BH		;	ESC
	JE	F20END
	CMP	AL, 08H		;	BACKSPACE
	JE	F20END
	CMP	AX,	53E0H	;	DELETE
	JE	F20END
	CMP	AX,	52E0H	;	INSERT
	JE	F20END
	CMP	AX,	50E0H	;	DOWNARROW
	JE	F20END
	CMP	AX,	48E0H	;	UPARROW
	JE	F20END
	CMP	AX,	4BE0H	;	LEFTARROW
	JE	F20END
	CMP	AX,	4DE0H	;	RIGHTARROW
	JE	F20END
F20END:	
	RET
F10ISSPECIALLKEY	ENDP

G10ISEDITMODE	PROC	NEAR
	CMP	ISEDIT,	0
	RET
G10ISEDITMODE	ENDP

H10TOGGLEEDITMODE	PROC	NEAR
	XOR	ISEDIT, 1
	RET
H10TOGGLEEDITMODE	ENDP

I10DISPLAY	PROC	NEAR
	CALL	J10CLEAR
	CALL	L10DISPLAYWIHTOUTCLEAR
	
	CALL 	K10CALCULATECURSUR ; get cursur into DX
	MOV	AH, 02H	; then set cursur with F10 02H
	MOV	BH, 00H
	INT	10H
	RET
I10DISPLAY	ENDP

J10CLEAR	PROC	NEAR
	PUSHA
	MOV	AX, 0600H
	MOV	BH, 0EH
	MOV	CX, 0000
	MOV	DX, 184FH
	INT	10H

	;set cursur to left-top
	MOV	AH, 02H
	MOV	BH, 00H
	MOV	DH, 00H
	MOV	DL, 00H
	INT	10H
	POPA
	RET
J10CLEAR	ENDP

K10CALCULATECURSUR	PROC	NEAR	;	DH, DL (ROW, COL)
	; calculate current cursur position
	; with 1 dimension cursur 'CURSUR'
	MOV	CX, CURSUR
	MOV	DX, 0
	CMP	CURSUR, 0	; no character in cursur?
	JE	K30END		; then exit
	LEA	DI, BUFFER
K20LOOP:
	CMP	BYTE PTR [DI], 0DH	; enter?
	JE	K21ENTER
	JNE	K22NOTENTER
K21ENTER:
	INC	DH		; inc row
	MOV	DL,	0	; set col 0
	JMP	K23ENDOFLOOP
K22NOTENTER:
	INC	DL		; inc col
	CMP	DL,	80	; if col > width
	JE	K21ENTER	; then process like enter pressed
	JMP	K23ENDOFLOOP
K23ENDOFLOOP:
	INC	DI		; next character.
	LOOP	K20LOOP
K30END:
	RET
K10CALCULATECURSUR	ENDP



L10DISPLAYWIHTOUTCLEAR	PROC NEAR
	LEA	DI, BUFFER
	MOV	AH, 02H
L20MAINLOOP:
	MOV	DL, [DI]
	CMP	DL, 0FFH
	JE	L30END
	INT	21H		; print [DI] with F21 02H
	CMP	DL, 0DH		; if enter
	JE	L21LINEFEED	; then need print linefeed
	JNE	L22NEXTCHAR

L21LINEFEED:
	MOV	DL, 0AH
	INT	21H
	JMP	L22NEXTCHAR

L22NEXTCHAR:
	INC DI
	JMP L20MAINLOOP

L30END:
	RET
L10DISPLAYWIHTOUTCLEAR	ENDP

END A10MAIN