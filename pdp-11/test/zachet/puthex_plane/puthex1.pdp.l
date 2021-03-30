000000:		ocsr = 0177564	; TTO command and status register for PDP-11
000000:		odat = 0177566  ; TTO data register
000000:		
000000:		    . = 200
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
000230:		HEX:    .ASCIZ      /0123456789ABCDEF/
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
000251:		
000251:		    . = 1000
001000:		
001000:		main:
001000:		
001000:		    mov @#A, r0
	 013700
	 000200
001004:		
001004:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001004:		; puthex  show number in tto in hex representation
001004:		;   input:	RO
001004:		;   output:	tto
001004:		;   clobber:	flags, r0
001004:		; R1 - the saved number
001004:		; R2 - loop counter
001004:		; R3 - shift by n bits
001004:		; R0 - digit and ascii code
001004:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001004:		puthex:	
001004:			mov	r0,r1		; copy number to r1
	 010001
001006:			mov	#4, r2		; 16 bit's counter
	 012702
	 000004
001012:		    mov #-14, r3     ; first shift by 14 bits
	 012703
	 177764
001016:		    
001016:		put16_loop:    
001016:		    mov r1, r0      ; copy number
	 010100
001020:		    ash r3, r0      ; r0 >> r3
	 072003
001022:			bic	#~17, r0    ; (r0 >> r3) & 0xF
	 042700
	 177760
001026:		    add #HEX, r0    ; r0 = HEX[r0]
	 062700
	 000230
001032:		    movb (r0), r0   ; r0 = *r0
	 111000
001034:		
001034:		putchar:
001034:		    tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001040:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001042:			movb	r0,@#odat	; put char to the odat
	 110037
	 177566
001046:		
001046:		    add #4, r3
	 062703
	 000004
001052:			sob	r2, put16_loop 
	 077217
001054:			
001054:			halt
	 000000
