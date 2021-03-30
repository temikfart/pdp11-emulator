000000:		. = 200
000200:		A:  .WORD   131313, 1, 2, 3, 4, 5, -1, 10, 40, 1000, 100000, 123456, 12345, 0
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
	 123456
	 012345
	 000000
000234:		
000234:		. = 1000
001000:		
001000:		main:	mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		    mov #A, r5
	 012705
	 000200
001010:		loop:    
001010:			mov	(r5)+, r0
	 012500
001012:		    beq end
	 001405
001014:			jsr	pc, putbin
	 004767
	 000046
001020:			jsr	pc, newline
	 004767
	 000106
001024:		    br loop
	 000771
001026:		end:
001026:			halt
	 000000
001030:		
001030:		
001030:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001030:		; putchar
001030:		;   input:	RO - ascii char
001030:		;   output:	none
001030:		;   clobber:	flags
001030:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001030:		ocsr = 0177564	; TTO command and status register for PDP-11
001030:		odat = 0177566  ; TTO data register
001030:		;
001030:		putchar:tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001034:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001036:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001042:			rts	pc		; return
	 000207
001044:		
001044:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001044:		; puts
001044:		;   input:	RO - asciz string
001044:		;   output:	none
001044:		;   clobber:	flags, r0
001044:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001044:		puts:	mov	r1,-(sp)	; save r1 in stack
	 010146
001046:			mov	r0,r1		; copy addr to r1
	 010001
001050:		l1:	movb	(r1)+,r0	; put next char to r0
	 112100
001052:			beq	l2		; if (r0 == 0) goto l2
	 001403
001054:			jsr	pc,putchar	; call putchar()
	 004767
	 177750
001060:			br	l1		; goto l1
	 000773
001062:		l2:	mov	(sp)+,r1	; restore r1 from stack
	 012601
001064:			rts	pc		; return
	 000207
001066:		
001066:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001066:		; putbin  show number in tto in bin representation
001066:		;   input:	RO
001066:		;   output:	tto
001066:		;   clobber:	flags, r0
001066:		; R1 - the saved number
001066:		; R2 - loop counter
001066:		; R0 - digit and ascii code
001066:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001066:		
001066:		putbin:	
001066:			mov	r1,-(sp)	; save r1 in stack
	 010146
001070:			mov	r2,-(sp)	; save r2 in stack
	 010246
001072:		
001072:			mov	r0, r1		; copy number to r1
	 010001
001074:			mov	#20, r2		; 16 bit's counter
	 012702
	 000020
001100:		    
001100:		put2_loop:    
001100:		    mov r1, r0      ; copy number
	 010100
001102:		put2_digit: 
001102:		    mov #'0, r0
	 012700
	 000060
001106:		    tst r1
	 005701
001110:		    bpl put_digit
	 100001
001112:		    inc r0
	 005200
001114:		put_digit:
001114:		    jsr pc, putchar
	 004767
	 177710
001120:		    rol r1
	 006101
001122:		    sob r2, put2_digit
	 077211
001124:		    
001124:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001126:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001130:			rts	pc		; return
	 000207
001132:		
001132:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001132:		; newline  print CRLF into tto
001132:		;   input:	RO
001132:		;   output:	tto
001132:		;   clobber:	flags, r0
001132:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001132:		newline:
001132:			mov	#crlf, r0
	 012700
	 001166
001136:			jsr	pc, puts
	 004767
	 177702
001142:			rts	pc
	 000207
001144:		
001144:		hello:	.asciz	<12><15>/hello, world!/<12><15>
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
001166:		crlf:	.asciz	<12><15>
	    012
	 015
	    000
001171:		
001171:			.end	main
