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
.global greenLedOff
.global buzzerOn
.global buzzerOff



pinsSetup:
  sbi DDRD-0x20, 4
  sbi DDRD-0x20, 7
  sbi DDRD-0x20, 7
  sbi DDRB-0x20, 4
  sbi DDRB-0x20, 5
 
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
    nop
  
engineStop:
  cbi PORTD-0x20, 4
  cbi PORTD-0x20, 7
  
engineLeft:
  sbi PORTD-0x20, 4
  cbi PORTD-0x20, 7
  
engineRight:
  cbi PORTD-0x20, 4
  sbi PORTD-0x20, 7
  
redLedOn:
  sbi PORTB-0x20, 5

redLedOff:
  cbi PORTB-0x20, 5
  
greenLedOn:
  sbi PORTB-0x20, 4
  
greenLedOff:
  cbi PORTB-0x20, 4
  
buzzerOn:
  sbi PORTD-0x20, 6
  
buzzerOff:
  cbi PORTD-0x20, 6
