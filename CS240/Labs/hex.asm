TITLE HEX

; hex.asm
; Kevin Xiao
; Fall 2013

; Writes the hexadecimal character representing the al register to the screen
; The four most significant bits of al are guaranteed to be zeros

INCLUDE Irvine16.inc
.8086

.data
array 	BYTE 30h, 31h, 32h, 33h, 34h, 35h, 36h, 37h, 38h, 39h 
	BYTE 41h, 42h, 43h, 44h, 45h, 46h
ALreg	BYTE 0Ah
.code

main PROC
	mov ax, @data	; grab data location and save in ax register
	mov ds, ax	; move location of data to data segment register
	
	mov al, ALreg	; store target hexadecimal into al register

	mov bx, 0		; initialize bx register to zeros
	mov bl, al		; copy target hexadecimal from al to bl
	mov si, bx		; copy bx register to si register (index)

	mov dl, array[si] 	; move character into dl register
	mov ah, 02h		; Set ah to the DOS code for write-character
	int 21h			; initiate DOS
	
	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
