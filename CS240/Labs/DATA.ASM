TITLE data

; data.asm
; Kevin Xiao
; Fall 2013

; Defines each data type listed in Table 3-2

Include Irvine16.inc
.8086

.data
value1 BYTE 255
value2 SBYTE -128
value3 WORD 65535
value4 SWORD -32768
value5 DWORD 4294967295
value6 SDWORD -2147483648
value7 FWORD 4294967296
value8 QWORD 18446744073709551615
value9 TBYTE 18446744073709551616
value10 REAL4 -1.2
value11 REAL8 3.2E-260
value12 REAL10 4.6E+4096

.code
main PROC
	mov ax, @data 		; load data segment register...
	mov ds, ax		; ...with location of data
	mov si, OFFSET value1 	; starting OFFSET
	mov cx, 60 	 	; number of units
	mov bx, BYTE		; doubleword format
	call DumpMem
	mov ax, 4C00h 		; Set up DOS function 4C: exit with termination code...
	int 21h 		; ...exit
main ENDP
END main
