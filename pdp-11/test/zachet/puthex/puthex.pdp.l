000000:		. = 200
000200:		A:  .WORD   11064, 125715, -1, 1, 10, 40, 1000, 100000, 6543, 0
	 011064
	 125715
	 177777
	 000001
	 000010
	 000040
	 001000
	 100000
	 006543
	 000000
000224:		
000224:		. = 1000
001000:		
001000:		main:	mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		    mov #A, r1
	 012701
	 000200
001010:		loop:    
001010:			mov	(r1)+, r0
	 012100
001012:		    beq end
	 001405
001014:		;    mov @#A, r0
001014:			jsr	pc, puthex
	 004767
	 000070
001020:			jsr	pc, newline
	 004767
	 000144
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
001066:		; puthex  show number in tto in hex representation
001066:		;   input:	RO
001066:		;   output:	tto
001066:		;   clobber:	flags, r0
001066:		; R1 - the saved number
001066:		; R2 - loop counter
001066:		; R3 - shift by n bits
001066:		; R0 - digit and ascii code
001066:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001066:		HEX:    .ASCIZ      /0123456789ABCDEF/
	    060
	 061
	    062
	 063
	    064
	 065
	    066
	 067
	    070
	 071
	    101
	 102
	    103
	 104
	    105
	 106
	    000
001107:		        .EVEN
001110:		puthex:	
001110:			mov	r1,-(sp)	; save r1 in stack
	 010146
001112:			mov	r2,-(sp)	; save r2 in stack
	 010246
001114:			mov	r3,-(sp)	; save r3 in stack
	 010346
001116:		
001116:			mov	r0,r1		; copy number to r1
	 010001
001120:			mov	#4, r2		; 16 bit's counter
	 012702
	 000004
001124:		    mov #-14, r3     ; first shift by 14 bits
	 012703
	 177764
001130:		    
001130:		put16_loop:    
001130:		    mov r1, r0      ; copy number
	 010100
001132:		    ash r3, r0      ; r0 >> r3
	 072003
001134:			bic	#~17, r0    ; (r0 >> r3) & 0xF
	 042700
	 177760
001140:		    add #HEX, r0    ; r0 = HEX[r0]
	 062700
	 001066
001144:		    movb (r0), r0   ; r0 = *r0
	 111000
001146:		    jsr	pc, putchar ; printf("%c", r0)
	 004767
	 177656
001152:		    add #4, r3
	 062703
	 000004
001156:			sob	r2, put16_loop 
	 077214
001160:			
001160:			mov	(sp)+,r3	; restore r3 from stack
	 012603
001162:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001164:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001166:			rts	pc		; return
	 000207
001170:		
001170:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001170:		; newline  print CRLF into tto
001170:		;   input:	RO
001170:		;   output:	tto
001170:		;   clobber:	flags, r0
001170:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001170:		newline:
001170:			mov	#crlf, r0
	 012700
	 001224
001174:			jsr	pc, puts
	 004767
	 177644
001200:			rts	pc
	 000207
001202:		
001202:		hello:	.asciz	<12><15>/hello, world!/<12><15>
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
001224:		crlf:	.asciz	<12><15>
	    012
	 015
	    000
001227:		
001227:			.end	main
