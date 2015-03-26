; export symbols
            XDEF asm_main
            XDEF delay
            XDEF wait20us

; Include derivative-specific definitions 
		INCLUDE 'derivative.inc'  		

C0Fflag:    equ $01         ; clear c0F flag mask

		    
; variable/data section
MY_EXTENDED_RAM: SECTION
; Insert here your data definition. For demonstration, temp_byte is used.
temp_byte:  DS.B   1


; code section
MyCode:     SECTION
; this assembly routine is called by the C/C++ application
asm_main:
            MOVB   #1,temp_byte   ; just some demonstration code
            NOP                   ; Insert here your own code

            RTS                   ; return to caller
            

; delay routine            
delay:
            TFR    d, y         
loop1       LDX    #24000
loop2:      NOP
            DBNE   x, loop2
            DBNE   y, loop1
            RTS
            
; 20us delay                         
wait20us:   MOVB   #$90, TSCR1             ; enable TCNT and fast timer flag clear
            MOVB   #0,   TSCR2             ; set TCNT prescaler to 1
            BSET   TIOS, $01               ; enable OC0
            LDD    TCNT                    ; start an OC0 operation
            ADDD   #480
            STD    TC0
            BRCLR  TFLG1, C0Fflag, *       ; wait for 20 us
            RTS                        