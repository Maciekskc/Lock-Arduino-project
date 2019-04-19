#include <SPI.h>
#include <MFRC522.h>
#include "assembler.h"
constexpr uint8_t RST_PIN =  5  ;        // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN =  10   ;      // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  pinMode(12,OUTPUT);       //USTAWIANIE PINOW DO TESTOWANIA AKCJI
  pinMode(7,OUTPUT);
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4) // PĘTLA WYKRYWAJĄCA BŁĄD URUCHOMIENIA OKNA DALOGOWEGO
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
      pinsSetup();
     delay_500ms();
     delay_1500ms();
     engineStop();
     engineLeft();
     engineRight();
     redLedOn();
     redLedOff();
     greenLedOn();
     greenLedOff();
     buzzerOn();
     buzzerOff();
}

void loop() {
	// Look for new cards
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
 
	// Dump debug info about the card; PICC_HaltA() is automatically called

if (mfrc522.uid.uidByte[0] == 0x3a &&           //zhardkodowany kod karty poprawnej
     mfrc522.uid.uidByte[1] == 0x98 &&
     mfrc522.uid.uidByte[2] == 0x34 &&
     mfrc522.uid.uidByte[3] == 0x2d) {
     Serial.println("Card 3A-98-34-2D, access granted");
     digitalWrite(12,HIGH);
     delay(1000);
     digitalWrite(12,LOW);
}else{
     Serial.print("Unknowed card (NR:");      // informacje o nowej karcie
     Serial.print(mfrc522.uid.uidByte[0],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[1],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[2],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[3],HEX);
     Serial.println("), access denied");
     digitalWrite(7,HIGH);
     delay(1000);
     digitalWrite(7,LOW);
     
}

}
