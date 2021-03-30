000000:		. = 200
000200:		A:  .WORD   131313, 1, 2, 3, 4, 5, -1, 10, 40, 1000, 100000, 6543, 0
	 131313
	 000001
	 000002
	 000003
	 000004
	 000005
	 177777
	 000010
	 000040
	 001000
	 100000
	 006543
	 000000
000232:		
000232:		. = 1000
001000:		
001000:		main:	mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		;    mov #A, r5
001004:		;loop:    
001004:		;	mov	(r5)+, r0
001004:		;    beq end
001004:		    mov @#A, r0
	 013700
	 000200
001010:			jsr	pc, putbin
	 004767
	 000044
001014:			jsr	pc, newline
	 004767
	 000104
001020:		;    br loop
001020:		end:
001020:			halt
	 000000
001022:		
001022:		
001022:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001022:		; putchar
001022:		;   input:	RO - ascii char
001022:		;   output:	none
001022:		;   clobber:	flags
001022:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001022:		ocsr = 0177564	; TTO command and status register for PDP-11
001022:		odat = 0177566  ; TTO data register
001022:		;
001022:		putchar:tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001026:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001030:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001034:			rts	pc		; return
	 000207
001036:		
001036:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001036:		; puts
001036:		;   input:	RO - asciz string
001036:		;   output:	none
001036:		;   clobber:	flags, r0
001036:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001036:		puts:	mov	r1,-(sp)	; save r1 in stack
	 010146
001040:			mov	r0,r1		; copy addr to r1
	 010001
001042:		l1:	movb	(r1)+,r0	; put next char to r0
	 112100
001044:			beq	l2		; if (r0 == 0) goto l2
	 001403
001046:			jsr	pc,putchar	; call putchar()
	 004767
	 177750
001052:			br	l1		; goto l1
	 000773
001054:		l2:	mov	(sp)+,r1	; restore r1 from stack
	 012601
001056:			rts	pc		; return
	 000207
001060:		
001060:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001060:		; putbin  show number in tto in bin representation
001060:		;   input:	RO
001060:		;   output:	tto
001060:		;   clobber:	flags, r0
001060:		; R1 - the saved number
001060:		; R2 - loop counter
001060:		; R0 - digit and ascii code
001060:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001060:		
001060:		putbin:	
001060:			mov	r1,-(sp)	; save r1 in stack
	 010146
001062:			mov	r2,-(sp)	; save r2 in stack
	 010246
001064:		
001064:			mov	r0, r1		; copy number to r1
	 010001
001066:			mov	#20, r2		; 16 bit's counter
	 012702
	 000020
001072:		    
001072:		put2_loop:    
001072:		    mov r1, r0      ; copy number
	 010100
001074:		put2_digit: 
001074:		    mov #'0, r0
	 012700
	 000060
001100:		    tst r1
	 005701
001102:		    bpl put_digit
	 100001
001104:		    inc r0
	 005200
001106:		put_digit:
001106:		    jsr pc, putchar
	 004767
	 177710
001112:		    rol r1
	 006101
001114:		    sob r2, put2_digit
	 077211
001116:		    
001116:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001120:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001122:			rts	pc		; return
	 000207
001124:		
001124:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001124:		; newline  print CRLF into tto
001124:		;   input:	RO
001124:		;   output:	tto
001124:		;   clobber:	flags, r0
001124:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001124:		newline:
001124:			mov	#crlf, r0
	 012700
	 001160
001130:			jsr	pc, puts
	 004767
	 177702
001134:			rts	pc
	 000207
001136:		
001136:		hello:	.asciz	<12><15>/hello, world!/<12><15>
	    012
	 015
	    150
	 145
	    154
	 154
	    157
	 054
	    040
	 167
	    157
	 162
	    154
	 144
	    041
	 012
	    015
	 000
001160:		crlf:	.asciz	<12><15>
	    012
	 015
	    000
001163:		
001163:			.end	main
