	page	60,132
TITLE	A04ASM1	(COM)	Move and add operations plus display
	.MODEL SMALL
	.CODE
	ORG 100H
BEGIN:	JMP MAIN
; ----------------------------------------------------------
FLDD	DW	0AH
FLDE	DW	0F120H
FLDF	DW	?
; ----------------------------------------------------------
MAIN	PROC	NEAR
		MOV AX, CS
		MOV DS, AX ; - init DS by CS

		MOV	AX, FLDD
		ADD	AX, FLDE
		MOV	FLDF, AX ; - FLDF = FLDD + FLDE

		MOV	CX, 2 ; - 2 byte, 2 loop
		LEA DI, FLDF
		ADD DI, CX ; - for load byte of FLDF		
A10PRINTLOOP:
		DEC DI
		MOV	DH, [DI] ; - load 1 byte of FLDF
		MOV BX, 2 ; - 1 byte need 2 character, so, 2 print loop
PRINTDL:
		MOV	DL, 11110000B
		AND	DL, DH ; - load upper 4 bit into DL

		MOV AH, CL
		MOV CL, 4
		SHR DL, CL
		MOV	CL, AH ; - shift DL's bit to bottom

		CMP	DL, 10 ; - 0~9 or A~F
		JB	ARABIT
		JMP	ALPHABET
ARABIT:
		ADD	DL, 30H
		JMP	PRINT
ALPHABET:
		ADD	DL, 37H
		JMP	PRINT
PRINT:
		MOV	AH, 02H
		INT	21H ; - print DL character

		MOV AH, CL
		MOV CL, 4
		SHL DH, CL
		MOV	CL, AH ; - shift DH left 4 bit to reuse above DL 4bit loadding codes. 

		DEC BX
		JNZ PRINTDL ; - loop for loading twise (2 character per 1 byte)

		LOOP	A10PRINTLOOP
OVER:
		MOV	AX,	4C00H
		INT	21H
MAIN	ENDP
		END	BEGIN