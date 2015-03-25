TITLE LAB5

; LAB5.ASM
; Kevin Xiao
; Fall 2013

; Various procedures.

INCLUDE Irvine16.inc
.8086

BUFFER_SIZE = 80

.data


hexArray 	BYTE	"0123456789ABCDEF"
buffer 		DB 	BUFFER_SIZE, ?, BUFFER_SIZE DUP (0)
readprompt	DB	"Write something: $"
readreturn 	DB	"You wrote: $"
prompt1 	DB	"Enter first number: $"
prompt2 	DB	"Enter second number: $"
promptreturn	DB 	"Product = $"
delayprompt	DB 	"Wait for how many milliseconds? $"
delayreturn	DB 	"Surprise! $"

.code

SafeRead PROC
; Allows user to enter (via keyboard) a string of characters to buffer
	push ax
	push bx
	push dx

	mov ah, 0Ah		; Read keyboard input and store into buffer
	mov dx, OFFSET buffer
	int 21h

	mov bx, 0		; Attach null-terminate character
	mov bl, buffer[1]
	mov buffer[bx+2], '$'
	
	mov dl, 0Ah		; Integrated new line character
	mov ah, 2
	int 21h

	pop dx
	pop bx
	pop ax
	ret
SafeRead ENDP

; FastMultiply takes registers AX and BX, unsigned words; returning their...
; product in AX. Procedure assumes product fits into 16 bits.

FastMultiply PROC
	push dx
	push cx
	push bx
	push ax
	
	mov dx, 0
	mov cx, 0
top:		; Loop splits AX*BX into AX*1 + AX*2 + AX*4 + AX*8 + ...
	shr bx, cl
	and bx, 0000000000000001b
	cmp bx, 0
	je EmptyBit
	shl ax, cl
	add dx, ax
EmptyBit:
	inc cl
	pop ax
	pop bx
	push bx
	push ax
	cmp cl, 15
	jne top

	pop ax
	mov ax, dx	
	pop bx
	pop cx
	pop dx
	ret
FastMultiply ENDP

; MyDelay takes register a number of milliseconds in AX, and returns only...
; after approximately that time has elapsed.

MyDelay PROC
	push ax
	push bx
	push cx
	push dx
	call CalcDelay	; Takes milliseconds in AX and converts to format...
			; employed by DOS interrupt 2Ch
	call TrueDelay	; Takes hrs:mins in AX and secs:milli in BX and...
			; pauses program for that length of time
	pop dx
	pop cx
	pop bx
	pop ax
	ret
MyDelay ENDP

TrueDelay PROC
	push ax
	mov ah, 2Ch
	int 21h
	pop ax
	add ax, cx
	add bx, dx	
			; Converting time bases into 60/60/100 (hrs/mins/secs)
	cmp bl, 64h	; Convert 100 centiseconds to 1 second
	jl Skip1
	add bx, 0100h
	sub bl, 64h
Skip1:
	cmp bx, 3C00h	; Convert 60 seconds to 1 minute
	jl Skip2
	inc ax
	sub bx, 3C00h
Skip2:
	cmp al, 3Ch 	; Convert 60 minutes to 1 hour
	jl top
	add ax, 0100h
	sub al, 3Ch	

top:			; Loops indefinitely, with current time >= saved time
	push ax		; ...as exit condition
	mov ah, 2Ch
	int 21h
	pop ax
	cmp ax, cx
	jne top
	cmp bx, dx
	jge top 

	ret
TrueDelay ENDP

CalcDelay PROC
	mov cx, ax
	mov ax, 0
	mov bx, 0
	mov dl, 0
top:			; As many loops here as there are milliseconds
			; Loop checks for carry instances with every added...
			; millisecond
	cmp cx, 0
	je skip
	dec cx
	inc dl
	cmp dl, 0Ah
	jne top
	inc bx
	mov dl, 0
	cmp bl, 64h
	jne top
	add bx, 0100h
	mov bl, 0
	cmp bx, 3C00h
	jne top
	inc ax
	mov bx, 0
;	cmp al, 3Ch		; Passed input cannot exceed 65.535 seconds
;	jne top			; Calculating hours isn't necessary
;	add ax, 0100h
;	mov al, 0
	jmp top
skip:
	ret
CalcDelay ENDP

ProcessInt PROC			; Turns string in buffer into integers
				; buffer must be integer string
				; Stores result in AX
	push dx
	push cx
	push bx
	
	mov ax,	1
	mov bx, 0
	mov cx, 0
	mov bl, buffer[1]
top:				
	mov dl, buffer[bx + 1]
	sub dl, 30h
	push bx
	push ax
	mov bx, dx
	call FastMultiply
	add cx, ax
	pop ax
	mov bx, 10
	call FastMultiply
	pop bx
	dec bx
	cmp bx, 0
	jne top
	
	mov ax, cx
	pop bx
	pop cx
	pop dx
	ret
ProcessInt ENDP

PrintString PROC 	; Prints string at offset in DX
	push ax
	mov ah, 9
	int 21h
	pop ax
	ret
PrintString ENDP

PrintAX PROC		; Prints out AX in decimal form
	push ax
	push bx
	push cx
	push dx
	push si

;	Removed instructions for signed integers
;	cmp 	ax, 0		; Perform two's complement modification...
;	JG 	skip		; ...if AX value is below zero
;	not 	ax
;	inc 	ax
;	push	ax
;	mov 	dl, 2Dh		; Add negative sign
;	mov 	ah, 02h
;	int 	21h
;	pop	ax
;skip:
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
	
	pop si
	pop dx
	pop cx
	pop bx
	pop ax	
	ret
PrintAX ENDP

main PROC
	mov ax, @data	; load data segment register...
	mov ds, ax	; ...with location of our data
	
	mov dx, OFFSET readprompt
	call PrintString
		
	call SafeRead

	mov dx, OFFSET readreturn	; SafeRead demonstration
	call PrintString
	mov dx, OFFSET buffer + 2
	call PrintString

	mov dl, 0Ah
	mov ah, 2
	int 21h
	mov dl, 0Dh
	int 21h

	mov dx, OFFSET prompt1		; FastMultiply demonstration...
	call PrintString		; and more SafeRead!
	call SafeRead
	call ProcessInt
	mov bx, ax
	mov dx, OFFSET prompt2
	call PrintString
	call SafeRead
	call ProcessInt
	call FastMultiply
	mov dx, OFFSET promptreturn
	call PrintString
	call PrintAX
	
	mov ah, 2
	mov dl, 0Ah
	int 21h
	mov dl, 0Dh
	int 21h

	mov dx, OFFSET delayprompt
	call PrintString
	call SafeRead
	call ProcessInt
	call MyDelay
	mov dx, OFFSET delayreturn
	call PrintString	

	mov ax, 4C00h	; Set up DOS function 4C: exit with termination code...
	int 21h 	; ...exit
main ENDP
END main
