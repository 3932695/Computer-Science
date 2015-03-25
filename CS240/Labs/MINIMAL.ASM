TITLE minimal

; minimal.asm
; Prof. Bailey
; Fall 2013

; Adds two 16-bit unsigned integers.

INCLUDE Irvine16.inc
.8086

.data
x WORD 265
y WORD 197
result WORD ?

.code
main PROC
	mov ax, @data	; load data segment register...
	mov ds, ax	; ...with location of our data
	mov ax, x	; move x to the accumulator
	add ax, y	; add y to the accumulator
	mov result, ax	; store the result in memory
	call DumpRegs	; display all registers
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
