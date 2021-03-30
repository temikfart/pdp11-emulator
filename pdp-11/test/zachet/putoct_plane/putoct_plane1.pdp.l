000000:		; print only the one oct number
000000:		ocsr = 0177564	; TTO command and status register for PDP-11
000000:		odat = 0177566  ; TTO data register
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
001000:		main: mov	#main,sp	; init stack
	 012706
	 001000
001004:		
001004:		    mov @#A, r0
	 013700
	 000200
001010:		
001010:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001010:		; put8  show number in tto in octet representation
001010:		;   input:	RO
001010:		;   output:	tto
001010:		;   clobber:	flags, r0
001010:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001010:		put8:	
001010:			mov	r1,-(sp)	; save r1 in stack
	 010146
001012:			mov	r2,-(sp)	; save r2 in stack
	 010246
001014:		
001014:			mov	r0,r1		; copy number to r1
	 010001
001016:			mov	#5, r2		; 16 bit's counter		
	 012702
	 000005
001022:		
001022:			movb	#'0, r0		; put char '0'
	 112700
	 000060
001026:			tst	r1
	 005701
001030:			bpl	put8_0
	 100001
001032:			inc	r0
	 005200
001034:		
001034:		put8_0:	; jsr	pc, putchar	
001034:		    tstb	@#ocsr	; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001040:			bpl	put8_0		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001042:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001046:		
001046:		put8_2:	mov	r1, r0	
	 010100
001050:			rol	r0
	 006100
001052:			rol	r0
	 006100
001054:			rol	r0
	 006100
001056:			rol	r0
	 006100
001060:			rol	r0
	 006100
001062:			bic	#~7, r0 
	 042700
	 177770
001066:			add	#'0, r0		; put char '0'
	 062700
	 000060
001072:			;jsr	pc, putchar
001072:		putc2:
001072:		    tstb	@#ocsr	; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001076:			bpl	putc2		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001100:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001104:		    
001104:			asl	r1
	 006301
001106:			asl	r1
	 006301
001110:			asl	r1
	 006301
001112:			sob	r2, put8_2 
	 077223
001114:			
001114:			;mov	(sp)+,r2	; restore r2 from stack
001114:			;mov	(sp)+,r1	; restore r1 from stack
001114:			;rts	pc		; return
001114:		
001114:		    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001114:		    ; new line
001114:		    mov #12, r0
	 012700
	 000012
001120:		putc12:
001120:		    tstb	@#ocsr
	 105737
	 177564
001124:			bpl	putc12	
	 100375
001126:			movb	r0,@#odat
	 110037
	 177566
001132:		
001132:		    mov #15, r0
	 012700
	 000015
001136:		putc15:
001136:		    tstb	@#ocsr
	 105737
	 177564
001142:			bpl	putc15	
	 100375
001144:			movb	r0,@#odat
	 110037
	 177566
001150:		
001150:		
001150:			halt
	 000000
001152:		
001152:		
