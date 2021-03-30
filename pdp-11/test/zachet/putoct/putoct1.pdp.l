000000:		; print only the one oct number
000000:		
000000:		. = 200
000200:		A:  .WORD   123456, 165432, 1, 2, 3, 4, 5, -1, 10, 20, 40, 100, 1000, 100000, 6543, 0
	 123456
	 165432
	 000001
	 000002
	 000003
	 000004
	 000005
	 177777
	 000010
	 000020
	 000040
	 000100
	 001000
	 100000
	 006543
	 000000
000240:		
000240:		. = 1000
001000:		
001000:		main:	mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		    mov @#A, r0
	 013700
	 000200
001010:			jsr	pc, put8
	 004767
	 000040
001014:			halt
	 000000
001016:		
001016:		
001016:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001016:		; putchar
001016:		;   input:	RO - ascii char
001016:		;   output:	none
001016:		;   clobber:	flags
001016:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001016:		ocsr = 0177564	; TTO command and status register for PDP-11
001016:		odat = 0177566  ; TTO data register
001016:		;
001016:		putchar:tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001022:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001024:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001030:			rts	pc		; return
	 000207
001032:		
001032:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001032:		; puts
001032:		;   input:	RO - asciz string
001032:		;   output:	none
001032:		;   clobber:	flags, r0
001032:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001032:		puts:	mov	r1,-(sp)	; save r1 in stack
	 010146
001034:			mov	r0,r1		; copy addr to r1
	 010001
001036:		l1:	movb	(r1)+,r0	; put next char to r0
	 112100
001040:			beq	l2		; if (r0 == 0) goto l2
	 001403
001042:			jsr	pc,putchar	; call putchar()
	 004767
	 177750
001046:			br	l1		; goto l1
	 000773
001050:		l2:	mov	(sp)+,r1	; restore r1 from stack
	 012601
001052:			rts	pc		; return
	 000207
001054:		
001054:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001054:		; put8  show number in tto in octet representation
001054:		;   input:	RO
001054:		;   output:	tto
001054:		;   clobber:	flags, r0
001054:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001054:		put8:	
001054:			mov	r1,-(sp)	; save r1 in stack
	 010146
001056:			mov	r2,-(sp)	; save r2 in stack
	 010246
001060:		
001060:			mov	r0,r1		; copy number to r1
	 010001
001062:			mov	#5, r2		; 16 bit's counter		
	 012702
	 000005
001066:		
001066:			movb	#'0, r0		; put char '0'
	 112700
	 000060
001072:			tst	r1
	 005701
001074:			bpl	put8_0
	 100001
001076:			inc	r0
	 005200
001100:		put8_0:	jsr	pc, putchar	
	 004767
	 177712
001104:		
001104:		put8_2:	mov	r1, r0	
	 010100
001106:			rol	r0
	 006100
001110:			rol	r0
	 006100
001112:			rol	r0
	 006100
001114:			rol	r0
	 006100
001116:			rol	r0
	 006100
001120:			bic	#~7, r0 
	 042700
	 177770
001124:			add	#'0, r0		; put char '0'
	 062700
	 000060
001130:			jsr	pc, putchar
	 004767
	 177662
001134:			asl	r1
	 006301
001136:			asl	r1
	 006301
001140:			asl	r1
	 006301
001142:			sob	r2, put8_2 
	 077220
001144:			
001144:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001146:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001150:			rts	pc		; return
	 000207
001152:		
001152:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001152:		; newline  print CRLF into tto
001152:		;   input:	RO
001152:		;   output:	tto
001152:		;   clobber:	flags, r0
001152:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001152:		newline:
001152:			mov	#crlf, r0
	 012700
	 001206
001156:			jsr	pc, puts
	 004767
	 177650
001162:			rts	pc
	 000207
001164:		
001164:		CR=15
001164:		LF=12
001164:		
001164:		hello:	.asciz	<CR><LF>/hello, world!/<CR><LF>
	    015
	 012
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
	 015
	    012
	 000
001206:		crlf:	.asciz	<CR><LF>
	    015
	 012
	    000
001211:		
001211:			.end	main
