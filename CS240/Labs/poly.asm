TITLE POLY

; poly.asm
; Kevin Xiao
; Fall 2013

; Given a, b, c and x, compute ax^2 + bx + c and store result in ax register.

INCLUDE Irvine16.inc
.8086

.data
aval SWORD 2
bval SWORD 3 
cval SWORD -1
xval SWORD 7

.code

main PROC
	mov ax, @data	; grab data location and save in ax register
	mov ds, ax	; move location of data to data segment register
	
	; Performing 'x^2'
	mov ax, xval	; move 'x' value into ax register
	mov bx, xval	; move 'x' value into bx register
	imul bx		; multiply ax by bx and store result in ax

	; Multiplying previous by 'a' and saving result
	mov bx, aval	; move 'a' value into bx register
	imul bx		; multiply ax by bx and store result in ax
	mov cx, ax	; move value in ax to cx register

	; Performing 'bx' 
	mov ax, xval	; move 'x' value into ax register
	mov bx, bval	; move 'b' vlaue into bx register
	imul bx		; multiply ax by bx and store result in ax

	; Adding 'c' and 'ax^2' to retrieve final result
	mov bx, cval	; move 'c' value into bx register
	add ax, bx	; add bx to previous ax result 
	add ax, cx	; add saved cx result to ax register
		
	call DumpRegs	; display all registers
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
