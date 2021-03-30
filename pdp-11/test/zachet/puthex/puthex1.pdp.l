000000:		. = 200
000200:		A:  .WORD   11064, 2, 3, 4, 5, -1, 10, 40, 1000, 100000, 6543, 0
	 011064
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
000230:		
000230:		. = 1000
001000:		
001000:		main:	mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		;    mov #A, r1
001004:		;loop:    
001004:		;	mov	(r1)+, r0
001004:		;    beq r0, end
001004:		    mov @#A, r0
	 013700
	 000200
001010:			jsr	pc, puthex
	 004767
	 000066
001014:			jsr	pc, newline
	 004767
	 000142
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
001060:		; puthex  show number in tto in hex representation
001060:		;   input:	RO
001060:		;   output:	tto
001060:		;   clobber:	flags, r0
001060:		; R1 - the saved number
001060:		; R2 - loop counter
001060:		; R3 - shift by n bits
001060:		; R0 - digit and ascii code
001060:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001060:		HEX:    .ASCIZ      /0123456789ABCDEF/
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
001101:		        .EVEN
001102:		puthex:	
001102:			mov	r1,-(sp)	; save r1 in stack
	 010146
001104:			mov	r2,-(sp)	; save r2 in stack
	 010246
001106:			mov	r3,-(sp)	; save r3 in stack
	 010346
001110:		
001110:			mov	r0,r1		; copy number to r1
	 010001
001112:			mov	#4, r2		; 16 bit's counter
	 012702
	 000004
001116:		    mov #-14, r3     ; first shift by 14 bits
	 012703
	 177764
001122:		    
001122:		put16_loop:    
001122:		    mov r1, r0      ; copy number
	 010100
001124:		    ash r3, r0      ; r0 >> r3
	 072003
001126:			bic	#~17, r0    ; (r0 >> r3) & 0xF
	 042700
	 177760
001132:		    add #HEX, r0    ; r0 = HEX[r0]
	 062700
	 001060
001136:		    movb (r0), r0   ; r0 = *r0
	 111000
001140:		    jsr	pc, putchar ; printf("%c", r0)
	 004767
	 177656
001144:		    add #4, r3
	 062703
	 000004
001150:			sob	r2, put16_loop 
	 077214
001152:			
001152:			mov	(sp)+,r3	; restore r3 from stack
	 012603
001154:			mov	(sp)+,r2	; restore r2 from stack
	 012602
001156:			mov	(sp)+,r1	; restore r1 from stack
	 012601
001160:			rts	pc		; return
	 000207
001162:		
001162:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001162:		; newline  print CRLF into tto
001162:		;   input:	RO
001162:		;   output:	tto
001162:		;   clobber:	flags, r0
001162:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001162:		newline:
001162:			mov	#crlf, r0
	 012700
	 001216
001166:			jsr	pc, puts
	 004767
	 177644
001172:			rts	pc
	 000207
001174:		
001174:		hello:	.asciz	<12><15>/hello, world!/<12><15>
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
001216:		crlf:	.asciz	<12><15>
	    012
	 015
	    000
001221:		
001221:			.end	main
