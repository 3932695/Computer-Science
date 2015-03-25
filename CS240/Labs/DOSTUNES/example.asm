INCLUDE Irvine16.inc

.8086			

TERMINATE = 4C00h
CALLDOS = 21h
CALLBIOS = 10h
SPEAKER_PORT = 61h
SPEAKER_ON = 3h
.data
.code
	
SpeakerOn PROC
	push	ax
.data
TurningOn BYTE "Turning on speaker...", 0dh, 0ah, 0
.code

	push	dx					;
	mov	dx, offset TurningOn	;
	call	WriteString			; Write "Turning on speaker..."
	pop	dx						;
	
	in	al, SPEAKER_PORT		; Get speaker status
	or	al, SPEAKER_ON
	out	SPEAKER_PORT, al
	
	pop	ax
	ret
SpeakerOn ENDP
	
SpeakerOff PROC
	push	ax
.data
TurningOff BYTE "Turning off speaker...", 0dh, 0ah, 0
.code
	push	dx
	mov	dx, offset TurningOff
	call	WriteString
	pop	dx
	in	al, SPEAKER_PORT	; Get speaker status
	and	al, not SPEAKER_ON
	out	SPEAKER_PORT, al
	pop	ax
	ret
SpeakerOff ENDP

TIMER_CONTROL_PORT = 43h
TIMER_READY = 0B6h
TIMER_DATA_PORT = 42h
	
SetTimerCount PROC
	;; AX - count to set the timer to
	
	push	dx
	mov	dx, offset SettingFreq
	call	WriteString
	pop	dx
	
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

.data
CLK_FREQ DWORD 1193180
;CLK_FREQ DWORD 0b61098h
.code
SetSpeakerFrequency PROC
	;; AX - frequency to generate on speaker
.data
SettingFreq BYTE "Setting speaker frequency", 0dh, 0ah, 0
.code
	call dumpregs					; Write "Setting speaker frequency"
	push	dx						;
	mov	dx, offset SettingFreq		;
	call	WriteString				;
	mov	dx, ax						; Unnecessary line?
	pop	dx							;
	
	push	ax						
	push	cx
	push	dx
	
	mov	cx, ax						; CX now contains frequency
	mov	AX, WORD PTR CLK_FREQ		; AX contains the magic number
	mov	DX, WORD PTR CLK_FREQ[2]	; ...which overflows into DX
	div	cx		; AX = DX:AX / CX (DX = remainder)
	
	call	SetTimerCount
	pop	dx
	pop	cx
	pop	ax
	ret
SetSpeakerFrequency ENDP

NoteFreq PROC
	;; AX - note (A = 0)
	;; DX - Octive (4 is middle C octive)
	;; Return:
	;; AX = Frequency
	
	push	dx
	
	push	dx
	mov	dx, 440		; Frequency of A below middle C
	mov	cx, 466-440	; Size of a semitone
	mul	cx		; dx:ax = ax * cx: multiply to get the right number of semitones
	add	dx, cx		; Add the semitone to A
	pop	dx
	
	cmp	dx, 4
	jl	lower
	je	done
	
	sub	dx, 4
	mov	cx, dx
mult:
	shl	ax, 1
	loop	mult
	jmp	done
lower:
	mov	cx, 4
	sub	cx, dx

divide:
	shr	ax, 1
	loop	divide
	
done:
	pop	dx
	ret
NoteFreq ENDP

HoldIt PROC
.data
Waiting BYTE "Waiting...", 0dh, 0ah, 0
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
DoneWaiting BYTE "Done waiting", 0dh, 0ah, 0
.code
	push	dx
	mov	dx, offset DoneWaiting
	call	WriteString
	pop	dx
	
	ret
HoldIt ENDP
	
.data
NOTES	WORD 523, 587, 659, 698, 783, 880, 988, 1046
;NOTES	WORD 523, 587, 659, 698
;NOTES	WORD 523		;
.code
	
main PROC
	mov	ax, @data
	mov	ds, ax

	
	call	SpeakerOn
	
	mov	cx, lengthof NOTES
	mov	si, 0
top:							; Looping through all the notes in the array, CX contains length of array
	mov	ax, NOTES[si]					; AX contains frequency input
	shr	ax, 1							; Divide AX by two..
	inc	si								; increment SI twice to get next note frequency
	inc	si								; 
	call	SetSpeakerFrequency			; AX contains frequency
	call	HoldIt						; Hold note
	
	loop	top

	call	SpeakerOff

	mov	ax, TERMINATE
	int	CALLDOS
	

main ENDP
END main
