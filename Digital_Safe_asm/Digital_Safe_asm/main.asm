;
; Digital_Safe_asm.asm
;
; Created: 10/6/2020 8:40:36 PM
; Author : Toshi & Ioanna
;

;***********************************************************
; Define variables
.def TEMP = R16			; 
.def DELAYTIME = R18	;Use R18 as a delay time amount
.def COUNTER = R19		;USe R19 as a counter for loops and such
.def TempLED = R21		;Use R21 as a place to store the LED value
.def Passcode1 = R22	;Use R22-R25 to store the passcode bytes
.def Passcode2 = R23	;largest digit possible is 9999 9999
.def Passcode3 = R24	;which requires 4 bytes to store
.def Passcode4 = R25
.equ SP = 0xDF			; 

; Rename column masks
.equ col1 = 0xEF		; Column 1 including 1, 4, 7, *
.equ col2 = 0xDF		; Column 2 including 2, 5, 8, 0
.equ col3 = 0xBF		; Column 3 including 3, 6, 9, #
.equ col4 = 0x7F		; Column 4 inlcuding A, B, C, D

; Rename keys
.equ key0  = 0xD7
.equ key1  = 0xEE
.equ key2  = 0xDE
.equ key3  = 0xBE
.equ key4  = 0xED
.equ key5  = 0xDD
.equ key6  = 0xBD
.equ key7  = 0xEB
.equ key8  = 0xDB
.equ key9  = 0xBB
.equ key10 = 0x7E		; A key
.equ key11 = 0x7D		; B key
.equ key12 = 0X7B		; C key
.equ key13 = 0X77		; D key
.equ key14 = 0XE7		; * key
.equ key15 = 0XB7		; # key

;***********************************************************


;***********************************************************
; Define here Reset and interrupt vectors, if any
reset:
   rjmp start
   reti      ; Addr $01
   reti      ; Addr $02
   reti      ; Addr $03
   reti      ; Addr $04
   reti      ; Addr $05
   reti      ; Addr $06        Use 'rjmp myVector'
   reti      ; Addr $07        to define a interrupt vector
   reti      ; Addr $08
   reti      ; Addr $09
   reti      ; Addr $0A
   reti      ; Addr $0B        This is just an example
   reti      ; Addr $0C        Not all MCUs have the same
   reti      ; Addr $0D        number of interrupt vectors
   reti      ; Addr $0E
   reti      ; Addr $0F
   reti      ; Addr $10

;***********************************************************


;***********************************************************
; Start program
start:
		LDI TEMP, SP		; Init Stack Pointer
		OUT 0x3D, TEMP		; Load TEMP value into 0x3D

		CALL Initialise		; Go to initialise subroutine


	
		LDI DELAYTIME, 200		;set delay time to 200
loop: 
		CALL ReadOne
		CALL Display

		CALL ReadNone
		LDI TempLED, 0x00
		CALL Display

		RJMP loop



;***********************************************************


;***********************************************************
; Initialise PORT B, PORT C and PORT C timers
Initialise:	
		; Initalise Port B
		LDI TEMP, 0xFF		; 0b11111111
		OUT DDRB, TEMP		; Outputs to DDRB (all outputs)

		LDI TEMP, 0x00		; 0b00000000
		OUT PORTB, TEMP		; Turns all LEDs off

		; Initialise Port C
		LDI TEMP, 0xF0		; 0b11110000
		OUT DDRC, TEMP		; Outptus to DDRC (sets rows to inputs and columns to outputs)

		LDI TEMP, 0x0F		; 0b00001111
		OUT PORTC, TEMP		; Enable pull up resistors on the row inptus

		LDI TEMP, 0xFF		; 0b11111111
		OUT PORTC, TEMP		; Set columns to all on (idle state)

		; Timers
		LDI TEMP, (1<<CS00) | (1<<CS02)		;set prescaler of timer0 to 1024
		OUT TCCR0, TEMP

		LDI TEMP, (1<<CS10) | (1<<CS12)		;set prescaler of timer1 to 1024
		OUT TCCR1B, TEMP



		RET

;***********************************************************


;***********************************************************
; ReadOne function 
;Uses
;TEMP	-	Value of the key presses
ReadOne:
	Column1:
	    LDI	temp, col1		; Assign 1st column to temp
		OUT portC, temp		; Put temp into portC
		LDI R18, 50
		CALL Delay_ms

		IN temp, pinC		; Read PINC values (0x13) and put into temp
		CPI temp, col1		; Compare pinC value with col1
		BREQ Column2		; Go to Column2 if equal (key has not been pressed in col1)
		
		CPI temp, key1		; check for key1
		BRNE CheckKey4		; If not equal, check for key4
		LDI TempLED, 0x01	; If equal, temp = 1
		RET					; Return back

	CheckKey4:	     	; 
		CPI temp, key4		; check for key4
		BRNE CheckKey7		; If not equal, check for key7
		LDI TempLED, 0x08	; If equal, temp = 4
		RET					; Reutrn back

	CheckKey7:	     	; 
		CPI temp, key7		; check for key7
		BRNE CheckKey14		; If not equal, check for key10	
		LDI TempLED, 0x40	; If equal, temp = 7
		RET					; Reutrn back

	CheckKey14:	     	; 
		CPI temp, key14		; check for key4
		BRNE Column2		; If not equal, check for Column2
		LDI TempLED, 0xFF	; If equal, temp = 10
		RET					; Reutrn back

	Column2:			
	    LDI	temp, col2		; Assign 2nd column to temp
		OUT portC, temp		; Put temp into portC
		LDI R18, 50
		CALL Delay_ms

		IN temp, pinC		; Read PINC values (0x13) and put into temp
		CPI temp, col2		; Compare pinC value with col2
		BREQ Column3		; Go to Column3 if equal (key has not been pressed in col2)
		
		CPI temp, key2		; check for key2
		BRNE CheckKey5		; If not equal, check for key5	
		LDI TempLED, 0x02	; If equal, temp = 2
		RET					; Return back

	CheckKey5:	     	; 
		CPI temp, key5		; check for key5
		BRNE CheckKey8		; If not equal, check for key8
		LDI TempLED, 0x10	; If equal, temp = 5
		RET					; Reutrn back

	CheckKey8:	     	; 
		CPI temp, key8		; check for key8
		BRNE CheckKey0		; If not equal, check for key0
		LDI TempLED, 0x80	; If equal, temp = 8
		RET					; Reutrn back

	CheckKey0:	     	; 
		CPI temp, key0		; check for key0
		BRNE Column3		; If not equal, check for Column3
		LDI TempLED, 0x00	; If equal, temp = 0
		RET					; Reutrn back


	Column3:			
	    LDI	temp, col3		; Assign 3rd column to temp
		OUT portC, temp		; Put temp into portC
		LDI R18, 50
		CALL Delay_ms

		IN temp, pinC		; Read PINC values (0x13) and put into temp
		CPI temp, col3		; Compare pinC value with col3
		BREQ Column4		; Go back to Column1 if equal (key has not been pressed in col3)
		
		CPI temp, key3		; check for key3
		BRNE CheckKey6		; If not equal, check for key6
		LDI TempLED, 0x04	; If equal, temp = 3
		RET					; Return back

	CheckKey6:	     	; 
		CPI temp, key6		; check for key6
		BRNE CheckKey9		; If not equal, check for key9
		LDI TempLED, 0x20	; If equal, temp = 6
		RET					; Reutrn back

	CheckKey9:	     	; 
		CPI temp, key9		; check for key9
		BRNE CheckKey15		; If not equal, check for key11
		LDI TempLED, 0x81	; If equal, temp = 9
		RET					; Reutrn back

	CheckKey15:	     	    ; 
		CPI temp, key15		; check for key11
		BRNE Column4		; If not equal, check for Column4	
		LDI TempLED, 0x0F	; If equal, temp = 11
		RET					; Reutrn back

	Column4:			
	    LDI	temp, col4		; Assign 4th column to temp
		OUT portC, temp		; Put temp into portC
		LDI R18, 50
		CALL Delay_ms

		IN temp, pinC		; Read PINC values (0x13) and put into temp
		CPI temp, col4		; Compare pinC value with col3
		BREQ RoundLoopcol1		; Go back to Column1 if equal (key has not been pressed in col3)
		
		CPI temp, key10		; check for key10
		BRNE CheckKey11		; If not equal, check for key11
		LDI TempLED, 0x03	; If equal, temp = 0x0A
		RET					; Return back

	CheckKey11:	     	; 
		CPI temp, key11		; check for key11
		BRNE CheckKey12		; If not equal, check for key12
		LDI TempLED, 0x0C	; If equal, temp = 0x0B
		RET					; Reutrn back

	CheckKey12:	     	; 
		CPI temp, key12		; check for key
		BRNE CheckKey13		; If not equal, check for key11
		LDI TempLED, 0x30	; If equal, temp = 0x0C
		RET					; Reutrn back

	CheckKey13:	     	    ; 
		CPI temp, key13		; check for key14
		BRNE RoundLoopCol1	; If not equal, check for Column1
		LDI TempLED, 0xC0	; If equal, temp = 0x0D
		RET					; Reutrn back

	RoundLoopCol1: 
		RJMP Column1 


	    RET
;***************************************************************

;***********************************************************
;take in 6-8 inputs and store in 4 bytes
;Uses
;R18	-	Low byte of Delay Length in seconds
;R22, R23, R24, R25
InputPasscode:
			POP R16
			POP R17

			CLR R22
			CLR R23
			CLR R24
			CLR R25

			CLR COUNTER


			CPI 

			POP R17
			POP R16
			RET

;***********************************************************
;waits until nothing is pressed
ReadNone:
			PUSH TEMP

		ReadNone_L1:
			IN TEMP, PINC		;read PINC 
			ANDI TEMP, 0x0F		;Mask only the input pins
			CPI TEMP, 0x0F
			BRNE ReadNone_L1	;Loop if not all columns are high

			POP TEMP
			RET


;************************************************************************
;
; takes whatever is in the TempLED register and outputs it to the LEDs
Display:
	    	OUT	PORTB, TempLED
			RET

					
;***************************************************************
			

;***************************************************************
; millisecond timer function 
;Uses
;R18	-	Delay Length in milliseconds
Delay_ms:
		PUSH TEMP					;save contents for later
		PUSH R17
		PUSH R19
		CLR COUNTER					;initialise a counter(R19) to 0

		LDI TEMP, 0x00				;set timer to 0
		OUT TCNT0, TEMP

		LDI TEMP, 12				;set output compare to 12
		OUT OCR0, TEMP

	Delay_ms_L1:
		LDI TEMP, (1<<OCF0)			;reset overflow counter, (set OCF0 to 1)
		OUT TIFR, TEMP
			

	Delay_ms_L2:
		IN TEMP, TIFR				;read the overflow bit
		ANDI TEMP, (1<<OCF0)		;bit mask to check only the overflow bit
		CPI TEMP, (1<<OCF0)			;check if it is set to 1
		BRNE Delay_ms_L2			;keep checking until it is set

		LDI TEMP, 0x00				;set timer to 0
		OUT TCNT0, TEMP

		INC COUNTER					;increment a counter for the number of milliseconds passed

		CP COUNTER, R18				;Compare delay length(R18) with counter(r17)
		BRLO Delay_ms_L1			;repeat if less then delay length(R18)

		POP R19
		POP R17
		POP TEMP
		RET
;***********************************************************

;***********************************************************
;Seconds delay fuction
;Uses
;R18	-	Low byte of Delay Length in seconds
Delay_sec:
		PUSH TEMP					;save contents for later
		PUSH R17
		PUSH R19					;initialise a counter

		CLR TEMP					;set timer to 0
		CLR R17
		OUT TCNT1H, TEMP			;Low byte in 16 bit value must always bet written last
		OUT TCNT1L, TEMP

		LDI TEMP, 0xC7				;set output compare to 11719 for 1 second (2DC7 in hex)
		LDI R17, 0x2D
		OUT OCR1AH, R17
		OUT OCR1AL, TEMP
		

		CLR COUNTER					;initialise a counter(R19) to 0

	Delay_sec_L1:
		LDI TEMP, (1<<OCF1A)		;reset overflow counter, (set to 1)
		OUT TIFR, TEMP
			

	Delay_sec_L2:
		IN TEMP, TIFR				;read the overflow bit
		ANDI TEMP, (1<<OCF1A)		;bit mask only the overflow bit
		CPI TEMP, (1<<OCF1A)		;check if it is set to 1
		BRNE Delay_sec_L2			;keep checking until it is set

		CLR TEMP					;set timer to 0
		CLR R17
		OUT TCNT1H, R17				;TCNT1H
		OUT TCNT1L, TEMP			;TCNT1L

		INC COUNTER

		CP COUNTER, R18				;Compare delay length(R18) with counter(r17)
		BRLO Delay_sec_L1			;repeat if less then delay length(R18)

		POP R19
		POP R17
		POP TEMP
		RET
;***********************************************************	



	
	.exit 	;this must always be at the end		