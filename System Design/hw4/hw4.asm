TITLE	.HW4 (EXE) String Input And Search I
	.MODEL	SMALL
	.STACK 64
	.DATA
PARLIST LABEL BYTE
MAXLEN	DB	41
ACTULEN	DB	?
KBNAME	DB	42 DUP(' ')

OUTPUT	DB	4 DUP(' ')

	.CODE
A10MAIN	PROC	FAR
	MOV AX, @DATA
	MOV DS, AX
	MOV ES, AX

	MOV AH, 0AH	; Input String from keyboards
	LEA DX, PARLIST
	INT 21H
	
	MOV AL, 0	; AL for count of i and I
	MOV CH, 0	; initialize cx by ACTULEN
	MOV CL, ACTULEN	; for searching 'i' loop
	LEA DI, KBNAME
SEARCHILOOP:
	MOV BH, [DI]	; copy KBNAME's character into BH
	CMP BH, 49H	; if BH eqaul with 'i'
	JE FOUNDI
	CMP BH, 69H	; or equal with 'I'
	JNE NOTI
FOUNDI:
	INC AL		; then count it
NOTI:
	INC DI
	LOOP SEARCHILOOP

	LEA DI, OUTPUT	; ready to printing Decimal, not Hex
	MOV CH, 10	; to devide 10
	MOV CL, 24H	; to add '$'
HEXTODEC:
	MOV AH, 0	; erase AH's value to devide only AL with 10
	DIV CH		; AL / 10. then AH = Remainder, AL : Quotient
	ADD AH, 30H	; ADD '0'
	MOV [DI], AH	; store Remainder
	
	INC DI

	CMP AL, 0	; if all number changed from hex to dec,
	JNZ HEXTODEC	; then stop looping

	MOV [DI], CL	; ADD '$' for function 21 : 09

	LEA SI, OUTPUT	; Ready to Reverse Decimal numbers
	DEC DI		; Because I calculated in Little Endian
			; si : start->end of OUTPUT, di : end->start of OUTPUT
REVERSE:
	CMP SI, DI	; if SI is over DI
	JNB PRINT	; then stop reverse
	MOV BH, [DI]	; Or, Reverse
	MOV DL, [SI]
	MOV [DI], DL
	MOV [SI], BH
	
	INC SI		; to reverse next number
	DEC DI
	JMP REVERSE

PRINT:
	MOV AH, 08H	; get display attribute
	MOV BH, 00
	INT 10H

	MOV BH, AH	; set BH by gotten attribute
	MOV AX, 0601H	; function 10-06, scroll 1 up
	MOV CX, 0000H
	MOV DX, 184FH
	INT 10H 

	MOV AH, 09H	; display dx(output)
	LEA DX, OUTPUT
	INT 21H

	MOV AX, 4C00H	; end
	INT 21H
A10MAIN	ENDP
	END A10MAIN