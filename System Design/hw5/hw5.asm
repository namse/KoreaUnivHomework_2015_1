TITLE   .HW5 (EXE) Keybaord Buffer
    .MODEL  SMALL
    .STACK 64
    .DATA
BIODATA SEGMENT AT  40H
    ORG 1AH
HEADPTR DW  ?
TAILPTR DW  ?
KBBUF   DB  ?
BIODATA ENDS

PRINT   DB  ' ', '$'

    .CODE
A10MAIN PROC    FAR
    MOV AX, @data
    MOV DS, AX
    LEA DX, PRINT	; DX for F21H:09H
A20LOOP:
    CALL B10INPUT
    CMP AL, 1BH		; 'ESC' pressed?
    JE  A30EXIT		; then end of program

    MOV DS:PRINT, AL	; copy ascii to ds:print for F21H:09H
    MOV AH, 09H		; F21H:09H
    INT 21H		
    JMP A20LOOP		; Execute Loop Until 'esc' pressed
A30EXIT:
    MOV AX, 4C00H
    INT 21H 
A10MAIN ENDP

B10INPUT    PROC    NEAR
    MOV AX, 40H
    MOV ES, AX

B20WAIT:
    MOV BX, ES:HEADPTR	; 40H:1AH, HEAD of Keyboard Buffer
    MOV CX, ES:TAILPTR	; 40H:1CH, TAIL of Keyboard Buffer
    CMP BX, CX		; is Head and Tail Same?
    JE  B20WAIT		; then wait, becuase no key pressed yet

    MOV AX, ES:[BX]	; Get ScanCode and ASCII Into AX
    ADD BX, 2		; Add 2byte to HEAD
    CMP BX, 3EH		; if HEAD over buffer?
    JNE B30EXIT

    MOV BX, 1EH		; then initialize that into 40H:1EH, start of buffer.
B30EXIT:
    MOV ES:HEADPTR, BX	; save changed HEAD.
    RET
B10INPUT    ENDP

    END A10MAIN