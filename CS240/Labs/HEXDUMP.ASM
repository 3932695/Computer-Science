TITLE HEXDUMP

; HEXDUMP.ASM
; Kevin Xiao
; Fall 2013

; Dumps ASCII hexadecimal representation of passed file
; Hexadecimal pair represents one byte
; 16 bytes per line, with ASCII representation on right 

INCLUDE Irvine16.inc
.8086

DOSEXIT = 4C00h
DOSCALL = 21h

.data

Filename BYTE 129 DUP(0)		
Fhndl dw ?
Buffer db ?

hexArray BYTE "0123456789abcdef"

.code

write PROC			; Accept ASCII hex in dl, prints character
	push	ax
	mov	ah, 2
	int	DOSCALL
	pop	ax
	ret
write ENDP

HexOut PROC			; Accepts a byte in ax, prints two-digit...
	push 	cx		; ...hex to represent that byte
	push	ax
	and 	ax, 11110000b
	mov	cl, 4
	shr	ax, cl
	mov	si, ax
	mov	dl, hexArray[si]
	call	write
	pop	ax
	push	ax
	and	ax, 00001111b
	mov	si, ax
	mov	dl, hexArray[si]
	call	write
	pop	ax
	pop	cx
	ret
HexOut ENDP

AddressOut PROC			; Prints 8-digit address in ax
	push	ax		; PROC split into 4 HexOut operations
	push	bx		; Recursive stack used, acknowledging...
	push	cx		; ...little endian order
	push 	dx
	mov	ax, 3
	call	AddressHelper
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	ret
AddressOut ENDP

AddressHelper PROC		; Recursive helper PROC for AddressOut
	push	bx		; Base case: ax = 0
	mov	cl, 8		; Upon reaching base, trace out and...
	shr	bx, cl		; ...pop saved bytes - apply HexOut PROC
	cmp	ax, 0
	je	skip
	dec	ax
	call	AddressHelper
skip:
	pop	bx
	mov	ax, bx
	call	HexOut
	ret
AddressHelper ENDP

DumpStack PROC			; main PROC pushes read characters to stack
	mov	dl, "|"		; Prints all characters accumulated in stack
	call	write		; Called after every 16 bytes
	push	bp		; Also called at end of file
	push	cx		; Tabs and new lines substituted with '.'
	push	dx		; Formatting included at start + end of PROC
	mov	cx, bp		; sp reassigned outside of PROC to remove...
	sub	cx, sp		; ...printed characters from stack
	shr	cx, 1
	sub	cx, 4
top:
	sub	bp, 2
	mov	dl, [bp]
	cmp	dl, 09h
	je	Substitute
	cmp	dl, 0Ah
	je	Substitute
	jmp	Skip
Substitute:
	mov	dl, "."
Skip:
	call	write
	loop	top

	pop	dx
	pop	cx
	pop	bp
	mov	dl, "|"
	call	write
	mov	dl, 0Ah
	call	write
	mov	dl, 0Dh
	call	write
	ret
DumpStack ENDP

PassCommand PROC			; Retrieves command line parameters
	push 	es			; Copy of GetCommandTail
	push 	ax			; Copies command line to null-...
	push	bx			; ...terminated string
	push	cx			; Fills buffer array at dx with string
	push	si
	push	di

	mov	ah, 62h
	int	DOSCALL
	mov	es, bx

	mov	si, dx
	mov	di, 81h
	mov	cx, 0
	mov	cl, es:[di-1]
	cmp	cx, 0
	je	L2
	cld
	mov	al, " "
	repz	scasb
	jz	L2
	dec	di
	inc	cx
L1:	
	mov	al, es:[di]
	mov	[si], al
	inc	si
	inc	di
	loop	L1
	clc
	jmp	L3
L2:
	stc
L3:
	mov	BYTE ptr [si], 0
	
	pop	di
	pop	si
	pop	cx
	pop	bx
	pop	ax
	pop	es
	ret
PassCommand ENDP

main PROC	

	mov	ax, @data
	mov	ds, ax

	mov	dx, OFFSET Filename
	call	PassCommand

	mov	ah, 3dh			; Open existing file interrupt
	mov	al, 0			; Read
	lea	dx, [Filename]		; Make DS point to this file
	int	DOSCALL
	mov	[FHndl], ax		; Save handler
	
	mov	cl, 16			; Initializing ebx to 0
	shr	bx, cl
	mov	bx, 0
	shl	bx, cl
Top:
	push	bx			; bx used to count bytes
	mov	ah, 3fh			; Read from file interrupt
	mov	bx, [FHndl]		; Accepts handler in bx
	mov	cx, 1			; Read one byte
	lea	dx, [Buffer]		; Buffer for data
	int	DOSCALL
	cmp	ax, cx			; Check for end-of-file
	jne	EOF
	pop	bx
	
	mov	al, [Buffer]		; Ignore all carriage returns
	cmp	al, 0Dh
	je	SkipNL
	
	mov	ax, bx			; Print address every 16 bytes
	and	ax, 0000000000001111b
	cmp	ax, 0
	jne	SkipAddress
	call	AddressOut
	mov	dl, " "
	call	write
	call 	write
	mov	bp, sp			; Save stack pointer
SkipAddress:
	mov	al, [Buffer]		; Print out current byte
	call	HexOut
	push	ax			; Save current byte to stack
	mov	dl, " "
	call 	write
	inc	bx

	mov	ax, bx			; Add space every 8 bytes
	and	ax, 0000000000000111b
	cmp	al, 0
	jne	SkipSpace
	mov	dl, " "
	call 	write
SkipSpace:
	mov	ax, bx			; Print all accumalated characters...
	and	ax, 0000000000001111b	; ...every 16 bytes, starting from...
	cmp	ax, 0			; ...bp, ending at bp - sp - 4 bytes
	jne	SkipNL
	call 	DumpStack
	mov	sp, bp

	mov	ax, bx			; Pauses program when screen is filled
	mov 	cx, 368
	div	cx
	cmp	dx, 0
	jne	SkipNL
	mov	ah, 00h
	int	16h
SkipNL:
	jmp	Top

EOF:
	pop	bx
	mov 	cx, bx
ZeroFence:				; Complete unfinished rows when...
	mov 	ax, bx			; ...file ends before row is finished
	and	ax, 0000000000001111b
	cmp	ax, 0
	je	EOF2
	mov	dl, " "
	call	write
	call	write
	call	write
	and	ax, 0000000000000111b
	cmp	ax, 0
	jne	MiddleFence
	call	write
MiddleFence:				; Still need space every 8 bytes
	inc	bx
	jmp	ZeroFence
EOF2:
	mov	dl, " "			; Dump bytes remaining in stack
	call	write
	call	DumpStack
	mov	sp, bp

	mov	bx, cx			; Print final byte address value
	call	AddressOut
	
	mov	bx, [FHndl]		
	mov	ah, 3eh			; Close file
	int	DOSCALL

	mov 	ax, DOSEXIT	; Terminate DOS
	int 	DOSCALL 	
main ENDP
END main
