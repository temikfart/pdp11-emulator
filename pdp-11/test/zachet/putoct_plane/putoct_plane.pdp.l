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
001004:		    mov #A, r5
	 012705
	 000200
001010:		loop:
001010:		    mov (r5)+, r0
	 012500
001012:		    beq end
	 001461
001014:		
001014:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001014:		; put8  show number in tto in octet representation
001014:		;   input:	RO
001014:		;   output:	tto
001014:		;   clobber:	flags, r0
001014:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001014:		put8:	
001014:			mov	r1,-(sp)	; save r1 in stack
	 010146
001016:			mov	r2,-(sp)	; save r2 in stack
	 010246
001020:		
001020:			mov	r0,r1		; copy number to r1
	 010001
001022:			mov	#5, r2		; 16 bit's counter		
	 012702
	 000005
001026:		
001026:			movb	#'0, r0		; put char '0'
	 112700
	 000060
001032:			tst	r1
	 005701
001034:			bpl	put8_0
	 100001
001036:			inc	r0
	 005200
001040:		
001040:		put8_0:	; jsr	pc, putchar	
001040:		    tstb	@#ocsr	; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001044:			bpl	put8_0		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001046:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001052:		
001052:		put8_2:	mov	r1, r0	
	 010100
001054:			rol	r0
	 006100
001056:			rol	r0
	 006100
001060:			rol	r0
	 006100
001062:			rol	r0
	 006100
001064:			rol	r0
	 006100
001066:			bic	#~7, r0 
	 042700
	 177770
001072:			add	#'0, r0		; put char '0'
	 062700
	 000060
001076:			;jsr	pc, putchar
001076:		putc2:
001076:		    tstb	@#ocsr	; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001102:			bpl	putc2		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001104:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001110:		    
001110:			asl	r1
	 006301
001112:			asl	r1
	 006301
001114:			asl	r1
	 006301
001116:			sob	r2, put8_2 
	 077223
001120:			
001120:			;mov	(sp)+,r2	; restore r2 from stack
001120:			;mov	(sp)+,r1	; restore r1 from stack
001120:			;rts	pc		; return
001120:		
001120:		    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001120:		    ; new line
001120:		    mov #12, r0
	 012700
	 000012
001124:		putc12:
001124:		    tstb	@#ocsr
	 105737
	 177564
001130:			bpl	putc12	
	 100375
001132:			movb	r0,@#odat
	 110037
	 177566
001136:		
001136:		    mov #15, r0
	 012700
	 000015
001142:		putc15:
001142:		    tstb	@#ocsr
	 105737
	 177564
001146:			bpl	putc15	
	 100375
001150:			movb	r0,@#odat
	 110037
	 177566
001154:		
001154:		
001154:		    br loop
	 000715
001156:		end:
001156:			halt
	 000000
001160:		
001160:		
