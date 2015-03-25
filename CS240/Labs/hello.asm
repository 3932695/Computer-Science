TITLE HELLO

; hello.asm
; Kevin Xiao
; Fall 2013

; Displays "Hello, World!"

INCLUDE Irvine16.inc
.8086

.data
array BYTE 48h, 65h, 6Ch, 6Ch, 6Fh, 2Ch, 20h, 57h, 6Fh, 72h, 6Ch, 64h, 21h
.code

main PROC
	mov ax, @data	; grab data location and save in ax register
	mov ds, ax	; move location of data to data segment register

	mov cx, lengthof array	; set iterations to length of string 
	mov bx, offset array	; load beginning of string into bx register
top:
	mov dl, [bx]	 	; move character into dl register
	inc bx			; increment bx to load next character address
	mov ah, 02h		; Set ah to the DOS code for write-character
	int 21h			; initiate DOS
	loop top		; loop to prepare next character
	
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
