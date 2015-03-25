TITLE FIB

; fib.asm
; Kevin Xiao
; Fall 2013

; Computes ith Fibonacci number

INCLUDE Irvine16.inc
.8086

.data
i WORD 7

.code

main PROC
	mov ax, @data	; grab data location and save in ax register
	mov ds, ax	; move location of data to data segment register
	
	
	mov ax, 0	; initialize result register
	mov bx, 1	; initialize addition register
	mov cx, i	; iterations 'i' saved in cx register 
fibLoop:
	mov dx, ax	; save current result to dx register
	add ax, bx	; add addition register to result register
	mov bx, dx	; replace addition register with result saved in dx
	loop fibLoop	; decrement cx and loop to fibLoop destination

	call DumpRegs	; display all registers
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
