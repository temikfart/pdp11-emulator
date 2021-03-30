000000:		ocsr = 0177564	; TTO command and status register for PDP-11
000000:		odat = 0177566  ; TTO data register
000000:		
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
000224:		HEX:    .ASCIZ      /0123456789ABCDEF/
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
000245:		
000245:		. = 1000
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
	 001441
001014:		
001014:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001014:		; puthex  show number in tto in hex representation
001014:		;   input:	RO
001014:		;   output:	tto
001014:		;   clobber:	flags, r0
001014:		; R1 - the saved number
001014:		; R2 - loop counter
001014:		; R3 - shift by n bits
001014:		; R0 - digit and ascii code
001014:		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
001014:		puthex:	
001014:			mov	r0,r1		; copy number to r1
	 010001
001016:			mov	#4, r2		; 16 bit's counter
	 012702
	 000004
001022:		    mov #-14, r3     ; first shift by 14 bits
	 012703
	 177764
001026:		    
001026:		put16_loop:    
001026:		    mov r1, r0      ; copy number
	 010100
001030:		    ash r3, r0      ; r0 >> r3
	 072003
001032:			bic	#~17, r0    ; (r0 >> r3) & 0xF
	 042700
	 177760
001036:		    add #HEX, r0    ; r0 = HEX[r0]
	 062700
	 000224
001042:		    movb (r0), r0   ; r0 = *r0
	 111000
001044:		
001044:		putchar:
001044:		    tstb	@#ocsr		; test bit 7 in ocsr (it's sign bit!!!)
	 105737
	 177564
001050:			bpl	putchar		; if ( bit 7 == 0 ) wait ... device is busy
	 100375
001052:			movb	r0, @#odat	; put char to the odat
	 110037
	 177566
001056:		
001056:		    add #4, r3
	 062703
	 000004
001062:			sob	r2, put16_loop 
	 077217
001064:		
001064:		    ; newline
001064:		putc12:
001064:		    tstb	@#ocsr
	 105737
	 177564
001070:			bpl	    putc12
	 100375
001072:			movb	#12, @#odat
	 112737
	 000012
	 177566
001100:		putc15:
001100:		    tstb	@#ocsr
	 105737
	 177564
001104:			bpl	    putc15
	 100375
001106:			movb	#15, @#odat
	 112737
	 000015
	 177566
001114:		
001114:		    br loop
	 000735
001116:		end:
001116:			halt
	 000000
