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
001000:		    mov @#A, r0
	 013700
	 000200
001004:		
001004:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001004:		; putbin  show number in tto in bin representation
001004:		;   input:	RO
001004:		;   output:	tto
001004:		;   clobber:	flags, r0
001004:		; R1 - the saved number
001004:		; R2 - loop counter
001004:		; R0 - digit and ascii code
001004:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001004:		
001004:		putbin:	
001004:			mov	r0, r1		; copy number to r1
	 010001
001006:			mov	#20, r2		; 16 bit's counter
	 012702
	 000020
001012:		    
001012:		put2_loop:    
001012:		    mov r1, r0      ; copy number
	 010100
001014:		put2_digit: 
001014:		    mov #'0, r0
	 012700
	 000060
001020:		    tst r1
	 005701
001022:		    bpl putchar
	 100001
001024:		    inc r0
	 005200
001026:		putchar:
001026:		    tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001032:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001034:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001040:		    
001040:		    rol r1
	 006101
001042:		    sob r2, put2_digit
	 077214
001044:		    
001044:			halt
	 000000
