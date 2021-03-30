000000:		ocsr = 0177564   ; TTO command and status register for PDP-11
000000:		odat = 0177566   ; TTO data register
000000:		
000000:		    . = 1000
001000:		    mov    #'*, R0     ; R0 = symbol * ascii code 
	 012700
	 000052
001004:		putchar:
001004:		    tstb   @#ocsr      ; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001010:		    bpl    putchar     ; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001012:		    movb   R0,@#odat   ; put char to the odat
	 110037
	 177566
001016:		    
001016:		    halt
	 000000
