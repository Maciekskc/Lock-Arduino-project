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


#ustawienie pinów wyjściowych
pinsSetup:
	sbi DDRD-0x20, 4
  sbi DDRD-0x20, 6
	sbi DDRD-0x20, 7
  sbi DDRB-0x20, 4
  sbi DDRB-0x20, 5
  #wywolanie metody stopującej silnik aby uniknąć nie porządanego uruchomienia
  call engineStop
  ret

#metody opóźnień
delay_500ms:
    ldi  r18, 41
    ldi  r19, 150
    ldi  r20, 128
    call L1
    ret
    
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    ret
	
delay_1500ms:
    nop
    ldi  r18, 122
    ldi  r19, 193
    ldi  r20, 130
    call L2
    ret
    
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2
    nop
    ret

#zatrzymanie silnika
engineStop:
	cbi PORTD-0x20, 4
	cbi PORTD-0x20, 7
  ret
#uruchomienie silnika w lewo
engineLeft:
	sbi PORTD-0x20, 4
	cbi PORTD-0x20, 7
  ret
#uruchomienie silnika w prawo
engineRight:
	cbi PORTD-0x20, 4
	sbi PORTD-0x20, 7
  ret

#zapalanie i gaszenie diod i brzęczyka
redLedOn:
	sbi PORTB-0x20, 5
  ret

redLedOff:
	cbi PORTB-0x20, 5
  ret
	
greenLedOn:
	sbi PORTB-0x20, 4
  ret
	
greenLedOff:
	cbi PORTB-0x20, 4
  ret
	
buzzerOn:
	sbi PORTD-0x20, 6
  ret
	
buzzerOff:
	cbi PORTD-0x20, 6
  ret
  
