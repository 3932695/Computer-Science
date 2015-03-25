INCLUDE Irvine16.inc

.8086			

TERMINATE = 4C00h
CALLDOS = 21h
CALLBIOS = 10h
SPEAKER_PORT = 61h
SPEAKER_ON = 3h
DOSDATA = 40h
KEYFLAG = 17h
SHIFT = 3
CTRL = 4
ALT = 8
BUFFER_SIZE = 80
.data
SetOn BYTE 0
; OutputName db "output.asm", 0			; Recorded output goes here
; InputName db "data.asm", 0
FileHandle dw ?						; Store file handle here
LastFreq WORD 440
LastKey WORD ?
CharBuffer dw "."
HighNotes	WORD 523, 554, 587, 622, 659, 698, 740, 783, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 
523, 554, 587, 622, 659, 698, 740, 783, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568

LowNotes	WORD 494, 466, 440, 415, 392, 370, 349, 330, 311, 294, 277, 262, 247, 233, 220, 208, 196,
494, 466, 440, 415, 392, 370, 349, 330, 311, 294, 277, 262, 247, 233, 220, 208, 196

HighKeys	WORD 1071h, 332h, 1177h, 433h, 1265h, 1372h, 635h, 1474h, 736h, 1579h, 837h, 1675h, 1769h, 0A39h, 186Fh, 0B30h, 1970h, 1A5Bh, 0D3Dh, 1B5Dh, 
4177, 832, 4439, 1059, 4677, 4946, 1573, 5204, 1886, 5465, 2086, 5717, 5961, 2600, 6223, 2857, 6480, 6779, 3371, 7037

LowKeys 	WORD 352Fh, 273Bh, 342Eh, 266Ch, 332Ch, 256Bh, 326Dh, 316Eh, 2368h, 3062h, 2267h, 2F76h, 2E63h, 2064h, 2D78h, 1F73h, 2C7Ah,
13631, 10042, 13374, 9804, 13116, 9547, 12877, 12622, 9032, 12354, 8775, 12118, 11843, 8260, 11608, 8019, 11354
.code

PlayState PROC

		mov ah, 3Dh			; Open existing file
		mov al, 0			; Read
		lea dx, [buffer + 2]; Link to this file name
		int 21h
		mov FileHandle, ax 	; Save file handler
		
		call SpeakerOn
	PlayTop:
		mov	ah, 3Fh			; Read from file interrupt
		mov	bx, Filehandle	; Accepts handler in bx
		mov	cx, 2			; Read one byte
		lea	dx, [CharBuffer]; Buffer for data
		int	21h
		cmp	ax, cx			; Check for end-of-file
		jne	EOF

		mov ax, CharBuffer
		; cmp ax, LastKey
		; je PlaySkip
		; push ax
		call CalcNoteFreq
		call SetSpeakerFrequency
		
		; call MyWriteInt	
		; mov ah, 0Eh
		; mov al, "|"
		; int 10h
		; pop ax
	; PlaySkip:
		; mov LastKey, ax
		jmp PlayTop

	EOF:
		call SpeakerOff
		ret
PlayState ENDP
	
SpeakerOn PROC
	push	ax
; .data
; TurningOn BYTE "Turning on speaker...", 0dh, 0ah, 0
; .code

	; push	dx					;
	; mov	dx, offset TurningOn	;
	; ;call	WriteString			; Write "Turning on speaker..."
	; pop	dx						;
	
	in	al, SPEAKER_PORT		; Get speaker status
	or	al, SPEAKER_ON
	out	SPEAKER_PORT, al
	
	pop	ax
	ret
SpeakerOn ENDP
	
SpeakerOff PROC
	push	ax
; .data
; TurningOff BYTE "Turning off speaker...", 0dh, 0ah, 0
; .code
	; push	dx
	; mov	dx, offset TurningOff
	; ;call	WriteString
	; pop	dx
	in	al, SPEAKER_PORT	; Get speaker status
	and	al, not SPEAKER_ON
	out	SPEAKER_PORT, al
	pop	ax
	ret
SpeakerOff ENDP

TIMER_CONTROL_PORT = 43h
TIMER_READY = 0B6h
TIMER_DATA_PORT = 42h
	
SetTimerCount PROC 						; AX - count to set the timer to
		push	ax
		push	dx
		mov	dx, ax
		mov	al, TIMER_READY
		out	TIMER_CONTROL_PORT, al
		mov	al, dl
		out	TIMER_DATA_PORT, al
		mov	al, dh
		out	TIMER_DATA_PORT, al
		pop	dx
		pop	ax
		ret
SetTimerCount ENDP

SetSpeakerFrequency PROC				; AX - frequency to generate on speaker
	.data
	SettingFreq BYTE "Setting speaker frequency", 0dh, 0ah, 0
	CLK_FREQ DWORD 1193180				;CLK_FREQ DWORD 0b61098h
	.code
		; push	dx						;
		; mov	dx, offset SettingFreq		;
		; call	WriteString				;
		; mov	dx, ax						; Unnecessary line?
		; pop	dx							;
		
		push	ax						
		push	cx
		push	dx
		
		mov	cx, ax						; CX now contains frequency
		mov	AX, WORD PTR CLK_FREQ		; AX contains the magic number
		mov	DX, WORD PTR CLK_FREQ[2]	; ...which overflows into DX
		div	cx							; AX = DX:AX / CX (DX = remainder)
		
		call	SetTimerCount
		pop	dx
		pop	cx
		pop	ax
		ret
SetSpeakerFrequency ENDP

HoldIt PROC
	.data
	Waiting BYTE "Tuning to A440 pitch standard...", 0dh, 0ah, 0
	.code
		push	dx
		mov	dx, offset Waiting
		call	WriteString
		pop	dx

		push	cx
		mov	cx, 3Fh
	outer:	
		push	cx
		mov	cx, 0FFFFh
	inner:	
		
		loop inner
		pop	cx
		
		loop outer
		pop	cx
	.data
	DoneWaiting BYTE "Done tuning, welcome to DOSTUNES!", 0dh, 0ah, 0
	.code
		push	dx
		mov	dx, offset DoneWaiting
		call	WriteString
		pop	dx
		
		ret
HoldIt ENDP

FluteState PROC
		push ax
		push es
		mov ax, DOSDATA
		mov es, ax
		call CreateFile
		
	; ---- Main Loop ----
	FluteTop:	
		mov [SetOn], 0
		mov al, es:[KEYFLAG]			; When did we learn this location?
										; Is there a similar location for key presses?
		test al, CTRL
		jz SkipExit
		jmp break
	SkipExit:
			
		test al, SHIFT
		jz SkipPlay
		mov [SetOn], 1
	SkipPlay:
		
		push ax
		push dx
		
		
		mov ah, 1
		int 16h
		jz SkipCheck
		mov ah, 0
		int 16h
	;	ax now contains key pressed
		call CalcNoteFreq
	;	ax now contains frequency
		mov [LastFreq], ax
		call SetSpeakerFrequency

	SkipCheck:
		pop dx
		pop ax
		
		cmp SetOn, 0
		je mute
		call SpeakerOn
		call WriteNotes
		jmp FluteTop
	mute:
		call SpeakerOff
		jmp FluteTop
	; ---- Main Loop ----
		
	break:
		call SpeakerOff
		pop es
		pop ax
		ret
FluteState ENDP

CreateFile PROC
		push ax
		push cx
		push dx
		
		mov ah, 3Ch
		mov cx, 0
		mov dx, OFFSET [buffer + 2]
		int 21h
		
		mov FileHandle, ax
		
		pop dx
		pop cx
		pop ax
		ret
CreateFile ENDP

WriteNotes PROC
		push ax
		push bx
		push cx
		push dx
		
		mov ax, LastFreq
		;---- HIGH NOTES
		mov cx, lengthof HighKeys
		mov si, 0
	WriteHighTop:
		mov bx, HighNotes[si]
		cmp ax, bx
		jne WriteHighSkip
		mov ax, HighKeys[si]
		jmp WriteBreak
	WriteHighSkip:
		inc si
		inc si
		loop WriteHighTop
		;---- HIGH NOTES
		;---- LOW NOTES
		mov cx, lengthof LowKeys
		mov si, 0
	WriteLowTop:
		mov bx, LowNotes[si]
		cmp ax, bx
		jne WriteLowSkip
		mov ax, LowKeys[si]
		jmp WriteBreak
	WriteLowSkip:
		inc si
		inc si
		loop WriteLowTop
		;---- LOW NOTES
		mov ax, "!"
	WriteBreak:
	
		mov [CharBuffer], ax
	
		mov ah, 40h
		mov bx, FileHandle
		mov cx, 2
		mov dx, OFFSET CharBuffer
		int 21h
		
		pop dx
		pop cx
		pop bx
		pop ax
		ret
WriteNotes ENDP

MyWriteInt PROC							; Prints hexadecimals words in AX
	.data
	hexArray BYTE	"0123456789ABCDEF"
	.code
		push ax
		push bx
		push cx
		push dx
		
		mov	bx, 0	
	MyNext:								; Divide by base and push remainder to stack...
		inc bx							; ...to get all the digits
		mov	dx, 0
		mov cx, 16						; Set to base 10
		div	cx
		push dx	
		cmp ax, 0
		jne	MyNext
		
		mov	cx, bx						; Keeping track of how many pushes
	MyTop:
		pop	si							; Now pop and print
		mov	al, hexArray[si]
		mov	ah, 0Eh
		int	10h
		loop MyTop
		
		pop dx
		pop cx
		pop bx
		pop ax
		ret
MyWriteInt ENDP

CalcNoteFreq PROC
		push cx
		push si
		push bx
		;---- HIGH NOTES
		mov cx, lengthof HighKeys
		mov si, 0
	HighTop:
		mov bx, HighKeys[si]
		cmp ax, bx
		jne HighSkip
		mov ax, HighNotes[si]
		jmp Break
	HighSkip:
		inc si
		inc si
		loop HighTop
		;---- HIGH NOTES
		;---- LOW NOTES
		mov cx, lengthof LowKeys
		mov si, 0
	LowTop:
		mov bx, LowKeys[si]
		cmp ax, bx
		jne LowSkip
		mov ax, LowNotes[si]
		jmp Break
	LowSkip:
		inc si
		inc si
		loop LowTop
		;---- LOW NOTES
		mov ax, 90000
	Break:
		pop bx
		pop si
		pop cx
		ret
CalcNoteFreq ENDP

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
	mov buffer[bx+2], 0

	pop dx
	pop bx
	pop ax
	ret
SafeRead ENDP

	.data
	buffer 		DB 	BUFFER_SIZE, ?, BUFFER_SIZE DUP (0)
	mainprompt BYTE "Type 'r' to record, type 'p' to playback, type 'e' to exit.", 0dh, 0ah, 0
	fluteprompt BYTE "Name your recording?", 0dh, 0ah, 0
	recordinstruct BYTE "'Shift' blows 'flute'. Keyboard adjusts pitch. Hit 'ctrl' when done.", 0dh, 0ah, 0
	playprompt BYTE "Name of recording to playback?", 0dh, 0ah, 0
	.code
main PROC
		mov	ax, @data
		mov	ds, ax
		
		
		call	SpeakerOn

		mov	ax, 440							; AX contains frequency input
		call	SetSpeakerFrequency			; AX contains frequency
		call	HoldIt						; Hold note
		call 	SpeakerOff
		
	MenuLoop:
		mov dx, OFFSET mainprompt
		call WriteString
		call SafeRead
		
		cmp buffer[2], 'r'					; Record mode
		jne SkipFluteState
		mov dx, OFFSET fluteprompt
		call WriteString
		call SafeRead

		mov dx, OFFSET recordinstruct
		call WriteString
		call FluteState
		jmp MenuLoop
	SkipFluteState:
	
		
		cmp buffer[2], 'p'
		jne SkipPlayState
		mov dx, OFFSET playprompt
		call WriteString
		call SafeRead

		call PlayState
		jmp MenuLoop
	SkipPlayState:
		cmp buffer[2], 'e'
		jne MenuLoop

		mov	ax, TERMINATE
		int	CALLDOS
		

main ENDP
END main
