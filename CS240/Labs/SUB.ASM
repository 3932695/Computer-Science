TITLE sub

; sub.asm
; Kevin Xiao
; Fall 2013

; Subtracts three 16-bit unsighed integers (computes result x-y-z)

INCLUDE Irvine16.inc
.8086

.data
x WORD 265
y WORD 197
z WORD 42

result WORD ?

.code
main PROC
	mov ax, @data	; load data segment register...
	mov ds, ax	; ...with location of our data
	mov ax, x	; move x to the accumulator
	sub ax, y	; subtract y from the accumulator
	sub ax, z	; subtract z from the accumulator
	mov result, ax	; store the result in memory
	call DumpRegs	; display all registers
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
