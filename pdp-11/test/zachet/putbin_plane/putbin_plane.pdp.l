000000:		ocsr = 0177564	; TTO command and status register for PDP-11
000000:		odat = 0177566  ; TTO data register
000000:		
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
001000:		main:
001000:		
001000:		    mov #A, r5
	 012705
	 000200
001004:		loop:    
001004:			mov	(r5)+, r0
	 012500
001006:		    beq end
	 001435
001010:		
001010:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001010:		; putbin  show number in tto in bin representation
001010:		;   input:	RO
001010:		;   output:	tto
001010:		;   clobber:	flags, r0
001010:		; R1 - the saved number
001010:		; R2 - loop counter
001010:		; R0 - digit and ascii code
001010:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001010:		
001010:		putbin:	
001010:			mov	r0, r1		; copy number to r1
	 010001
001012:			mov	#20, r2		; 16 bit's counter
	 012702
	 000020
001016:		    
001016:		put2_loop:    
001016:		    mov r1, r0      ; copy number
	 010100
001020:		put2_digit: 
001020:		    mov #'0, r0
	 012700
	 000060
001024:		    tst r1
	 005701
001026:		    bpl putchar
	 100001
001030:		    inc r0
	 005200
001032:		putchar:
001032:		    tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001036:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001040:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001044:		    
001044:		    rol r1
	 006101
001046:		    sob r2, put2_digit
	 077214
001050:		    
001050:		    ; new line
001050:		put12:
001050:		    tstb	@#ocsr
	 105737
	 177564
001054:			bpl	    put12
	 100375
001056:			movb	#12, @#odat
	 112737
	 000012
	 177566
001064:		put15:
001064:		    tstb	@#ocsr
	 105737
	 177564
001070:			bpl	    put15
	 100375
001072:			movb	#15, @#odat
	 112737
	 000015
	 177566
001100:		    
001100:		
001100:		    br loop
	 000741
001102:		end:
001102:			halt
	 000000
