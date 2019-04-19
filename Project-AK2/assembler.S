#include <avr/io.h>

.global pinsSetup
.global delay_500ms
.global delay_1500ms
.global engineStop
.global engineLeft
.global engineRight
.global redLedOn
.global redLedOff
.global greenLedOn
.global greenLedOn
.global buzzerOn
.global buzzerOff

pinsSetup:
	sbi DDRD-0x20, 4
	sbi DDRD-0x20, 6
  ret
 
delay_500ms:
    ldi  r18, 21
    ldi  r19, 75
    ldi  r20, 191
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    nop
	
delay_1500ms:
    ldi  r18, 61
    ldi  r19, 225
    ldi  r20, 64
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2
    rjmp PC+1
	
engineStop:
	cbi PD4
	cbi PD7
	
engineLeft:
	sbi PD4
	cbi PD7
	
engineRight:
	cbi PD4
	sbi PD7
	
redLedOn:
	sbi PB5

redLedOff:
	cbi PB5
	
greenLedOn:
	sbi PB4
	
greenLedOff:
	cbi PB4
	
buzzerOn:
	sbi PD6
	
buzzerOff:
	cbi PD6
