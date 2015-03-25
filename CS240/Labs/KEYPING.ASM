TERMINATE = 4C00h
TSR = 3100h
GETINT = 35h
SETINT = 25h
KEYINT = 9h
CALLDOS = 21h
CALLBIOS = 10h
DOSDATA = 40h
KEYFLAG = 17h
CTRL = 4
ALT = 8
RIGHTSHIFT = 1
CURSORVD = 0
CURSORHD = 72

.model tiny
.8086
.code
		org 100h
start:
		jmp setup

		; Begin data definitions here

hexArray BYTE	"0123456789ABCDEF"
old_timer DD 00000000h
old_key DD 00000000h
clock_welcome DB 0Ah, 0Dh, "Clock installed! Press CTRL to enable, ALT to disable.", '$'
clock_disable DB 0Ah, 0Dh, "Clock disabled! Press CTRL to enable clock.", 0Ah, 0Dh, '$'
clock_enable DB 0Ah, 0Dh, "Clock enabled! Press ALT to disable clock.", 0Ah, 0Dh, '$'
clock_already DB 0Ah, 0Dh, "Clock already installed!", '$'
clock_on DB 0
oldsp dw ?
oldss dw ?
mystack word 100 dup (?)
newsp word offset newsp

MyWriteInt PROC			; Converts hexadecimals words in AX to decimal form
	push bx
	push cx
	push dx
	
	mov	bx, 0	
next:					; Divide by ten and push remainder to stack...
	inc bx				; ...to get all the digits in decimal form
	mov	dx, 0
	mov cx, 16
	div	cx
	push dx	
	cmp ax, 0
	jne	next
	
	mov	cx, bx			; Keeping track of how many pushes
top:
	pop	si				; Now pop and print
	mov	al, cs:hexArray[si]
	mov	ah, 0Eh
	int	10h
	loop 	top
	
	pop dx
	pop cx
	pop bx
	ret
MyWriteInt ENDP

new_timer PROC

        push ax
		
		mov bh, 0				; save cursor position
		mov ah, 03h
		int 10h
		push dx
		
		mov ah, 02h				; move cursor position
		mov bh, 0
		mov dh, CURSORVD
		mov dl, CURSORHD
		int 10h
		
		mov ah, 02h				; get time
		int 1Ah

		mov ah, 0
		mov al, ch
		call InsertZero			; output hours
		call MyWriteInt		
		
		mov ah, 0Eh
		mov al, ':'
		int 10h		
		
		mov ah, 0
		mov al, cl
		call InsertZero			; output minutes
		call MyWriteInt
		
		mov ah, 0Eh
		mov al, ':'
		int 10h
		
		mov ah, 0
		mov al, dh
		call InsertZero			; output seconds
		call MyWriteInt
		
		mov ah, 02h				; restore cursor position
		mov bh, 0
		pop dx
		int 10h

		pop ax
        STI

        IRET

new_timer ENDP

InsertZero PROC
		push ax
		cmp al, 10h
		jge skip
		mov ah, 0Eh
		mov al, cs:hexArray[0]
		int 10h
skip:
		pop ax
		ret
InsertZero ENDP

new_key PROC
		sti
		push ax
		push es
		
		mov ax, DOSDATA
		mov es, ax
		
		mov al, es:[KEYFLAG]
		push ax
		
		test al, CTRL
		jz SkipCtrl
		cmp cs:clock_on, 1
		je SkipCtrl
		CLI                            ;+-
        PUSH   CS                      ;| Install new_timer
        POP    DS                      ;|
        LEA    DX, new_timer
        MOV    AL, 1Ch
        MOV    AH, 25h
        INT    21h
		mov cs:clock_on, 1
		mov dx, OFFSET cs:clock_enable
		call PrintString
SkipCtrl:
		pop ax
		
		test al, ALT
		jz SkipAlt
		cmp cs:clock_on, 0
		je SkipAlt
		CLI
		PUSH   DS
        LDS    DX,CS:[old_timer]         ;+- 
        MOV    AL, 1Ch                  ;| Disinstall timer
        MOV    AH, 25h                  ;| 
		INT    21h                     ;|
		mov cs:clock_on, 0
		pop	ds
		sti
		mov dx, OFFSET CS:clock_disable
		call PrintString
SkipAlt:
		
		pop es
		pop ax
	
		push word ptr [cs:old_key + 2] ; I have no idea...
        push word ptr [cs:old_key]     ; how this part works
        retf
new_key ENDP

PrintString PROC 	; Prints string at offset in DX
	push ax
	mov ah, 9
	int 21h
	pop ax
	ret
PrintString ENDP
		
setup:
		mov ax, cs
		mov ds, ax
		
		mov oldsp, sp
		mov oldss, ss
		push cs
		cli
		pop ss
		mov sp, newsp
		
        MOV    AL, 01Ch                 ;+-
        MOV    AH, 35h                  ;| Save old_timer
        INT    21h                     ;|
        MOV    WORD PTR [old_timer],BX
        MOV    WORD PTR [old_timer][2],ES

		MOV    AL, 9h                 ;+-
        MOV    AH, 35h                  ;| Save old_key
        INT    21h                     ;|
		
		mov ax, WORD PTR [es:old_key]
		mov dx, WORD PTR [old_key]
		cmp ax, dx
		jne exit
		
		
        MOV    WORD PTR [old_key],BX
        MOV    WORD PTR [old_key][2],ES
		
		
		
		cli	
		PUSH   CS                      ;| Install new_key
        POP    DS                      ;|
		LEA    DX, new_key
		MOV    AL, 9h
		MOV    AH, 25h
		INT    21h

		mov dx, OFFSET clock_welcome
		call PrintString
		
		jmp skipexit
exit:
		mov dx, OFFSET clock_already
		call PrintString
skipexit:
		cli
		mov sp, oldsp
		mov ss, oldss
		sti
		mov ax, TSR
		int CALLDOS
		
end start
