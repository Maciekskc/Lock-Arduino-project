#include "assembler.h"

void setup() {
  // put your setup code here, to run once:
  pinsSetup();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
   for(int i=0; i<5; i++){
    engineLeft();
    delay_500ms();
    engineRight();
    delay_500ms();
  }
  engineStop();
  delay_1500ms();
}
