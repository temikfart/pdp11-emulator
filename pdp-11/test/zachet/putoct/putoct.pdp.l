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
001004:		    mov #hello, r0
	 012700
	 001212
001010:		    jsr pc, puts
	 004767
	 000044
001014:			jsr	pc, newline
	 004767
	 000160
001020:		    ;halt
001020:		
001020:		    mov #A, r1
	 012701
	 000200
001024:		loop:    
001024:			mov	(r1)+, r0
	 012100
001026:		    beq end
	 001405
001030:			jsr	pc, put8
	 004767
	 000046
001034:			jsr	pc, newline
	 004767
	 000140
001040:		    br loop
	 000771
001042:		end:
001042:			halt
	 000000
001044:		
001044:		
001044:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001044:		; putchar
001044:		;   input:	RO - ascii char
001044:		;   output:	none
001044:		;   clobber:	flags
001044:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001044:		ocsr = 0177564	; TTO command and status register for PDP-11
001044:		odat = 0177566  ; TTO data register
001044:		;
001044:		putchar:tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001050:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001052:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001056:			rts	pc		; return
	 000207
001060:		
001060:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001060:		; puts
001060:		;   input:	RO - asciz string
001060:		;   output:	none
001060:		;   clobber:	flags, r0
001060:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001060:		puts:	mov	r1,-(sp)	; save r1 in stack
	 010146
001062:			mov	r0,r1		; copy addr to r1
	 010001
001064:		l1:	movb	(r1)+,r0	; put next char to r0
	 112100
001066:			beq	l2		; if (r0 == 0) goto l2
	 001403
001070:			jsr	pc,putchar	; call putchar()
	 004767
	 177750
001074:			br	l1		; goto l1
	 000773
001076:		l2:	mov	(sp)+,r1	; restore r1 from stack
	 012601
001100:			rts	pc		; return
	 000207
001102:		
001102:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001102:		; put8  show number in tto in octet representation
001102:		;   input:	RO
001102:		;   output:	tto
001102:		;   clobber:	flags, r0
001102:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001102:		put8:	
001102:			mov	r1,-(sp)	; save r1 in stack
	 010146
001104:			mov	r2,-(sp)	; save r2 in stack
	 010246
001106:		
001106:			mov	r0,r1		; copy number to r1
	 010001
001110:			mov	#5, r2		; 16 bit's counter		
	 012702
	 000005
001114:		
001114:			movb	#'0, r0		; put char '0'
	 112700
	 000060
001120:			tst	r1
	 005701
001122:			bpl	put8_0
	 100001
001124:			inc	r0
	 005200
001126:		put8_0:	jsr	pc, putchar	
	 004767
	 177712
001132:		
001132:		put8_2:	mov	r1, r0	
	 010100
001134:			rol	r0
	 006100
001136:			rol	r0
	 006100
001140:			rol	r0
	 006100
001142:			rol	r0
	 006100
001144:			rol	r0
	 006100
001146:			bic	#~7, r0 
	 042700
	 177770
001152:			add	#'0, r0		; put char '0'
	 062700
	 000060
001156:			jsr	pc, putchar
	 004767
	 177662
001162:			asl	r1
	 006301
001164:			asl	r1
	 006301
001166:			asl	r1
	 006301
001170:			sob	r2, put8_2 
	 077220
001172:			
001172:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001174:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001176:			rts	pc		; return
	 000207
001200:		
001200:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001200:		; newline  print CRLF into tto
001200:		;   input:	RO
001200:		;   output:	tto
001200:		;   clobber:	flags, r0
001200:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001200:		newline:
001200:			mov	#crlf, r0
	 012700
	 001234
001204:			jsr	pc, puts
	 004767
	 177650
001210:			rts	pc
	 000207
001212:		
001212:		CR=15
001212:		LF=12
001212:		
001212:		hello:	.asciz	<CR><LF>/hello, world!/<CR><LF>
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
001234:		crlf:	.asciz	<CR><LF>
	    015
	 012
	    000
001237:		
001237:			.end	main
