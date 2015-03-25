TITLE FUNCS

; funcs.asm
; Kevin Xiao
; Fall 2013

; Exercises in creating procedures, see comments on procedures for details 

INCLUDE Irvine16.inc
.8086

.data

hello 	BYTE 	"Hello, World!", 0
array1 	WORD 	1, 2, 3, 4
array2 	BYTE 	1, 2, 3, 4
factor	WORD	4
hexArray BYTE	"0123456789ABCDEF"
myWord SWORD	0E168h

.code

MyWriteString PROC		; Prints out a null-terminated string
top:
	mov 	dl, [bx]	; Print character...
	mov 	ah, 02h		; ...with this command...
	int 	21h		; ...from DOS
	
	inc	bx		; Increment to next character's address
	mov 	dl, 0		; Load zero for...
	cmp 	dl, [bx]	; ...null-character test
	jne 	top		; No null-character? Continue printing.
	ret
MyWriteString ENDP

ArraySum PROC			; Stores sum of elements in an array in AX

	and 	dx, 00FFh	; Clear DH as bx cannot accept DL alone
	dec 	cx		; No. of additions is one-less length of array
	mov	ax, [bx]	
top:				; Addition loop
	add 	bx, dx		; Scaling accounted for, element size in DL 
	add 	ax, [bx]	
	loop 	top

	cmp	dx, 1		; With BYTE arrays, AH should be wiped
	jne	skip		
	and 	ax, 00FFh	
skip:	
	call DumpRegs
	ret
ArraySum ENDP

Fact PROC			; Calculates factorial of value in ax
	mov 	bx, 0		; BX saves recursive parameter
	cmp	ax, 1		; Base case, ax reaches 1
	je	skip		; If equal to 1, skip to multiplication
	dec	ax		; If not, decrease ax...
	call 	Fact		; ...and go deeper
skip:
	inc	bx		; When 1 is hit, trace back to original no...
	mul	bx		; ...whilst multiplying on the way
	ret
Fact ENDP

HexOut PROC			; Prints out array of bytes
top:
	mov	ax, [bx]
	and	ax, 0F0h	; Mask least significant bits
	shr	ax, 1		; Syntax glitch? Can't shift beyond one
	shr 	ax, 1
	shr 	ax, 1
	shr	ax, 1
	mov	si, ax		; Most significant bits passed as array index
	mov	dl, hexArray[si]
	mov 	ah, 02h		; Print character
	int 	21h

	mov	ax, [bx]	; Repeat with least significant bits
	and	ax, 0Fh
	mov	si, ax
	mov	dl, hexArray[si]
	mov	ah, 02h
	int	21h
	mov	dl, 20h
	mov 	ah, 02h
	int	21h
	inc	bx
	loop top
	ret
HexOut ENDP

MyWriteInt PROC			; Converts hexadecimals words to decimal form

	cmp 	ax, 0		; Perform two's complement modification...
	JG 	skip		; ...if AX value is below zero
	not 	ax
	inc 	ax
	push	ax
	mov 	dl, 2Dh		; Add negative sign
	mov 	ah, 02h
	int 	21h
	pop	ax
skip:
	mov	bx, 0	
next:				; Divide by ten and push remainder to stack...
	inc 	bx		; ...to get all the digits in decimal form
	mov	dx, 0
	mov 	cx, 10
	div	cx
	push	dx	
	cmp 	ax, 0
	jne	next
	
	mov	cx, bx		; Keeping track of how many pushes
top:
	pop	si			; Now pop and print
	mov	dl, hexArray[si]
	mov	ah, 02h
	int	21h
	loop 	top
	ret
MyWriteInt ENDP

main PROC
	mov 	ax, @data	; load data segment register...
	mov 	ds, ax	; ...with location of our data
	
	mov 	bx, OFFSET hello
	call 	MyWriteString
	
	mov 	bx, OFFSET array1
	mov 	cx, lengthof array1
	mov 	dl, TYPE array1
	call 	ArraySum

	mov 	ax, factor
	call	Fact
	call 	DumpRegs

	mov	bx, OFFSET array2
	mov	cx, lengthof array2
	call	HexOut

	mov	ax, myWord
	call 	MyWriteInt

	mov 	ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 	21h 	; ...exit
main ENDP
END main
