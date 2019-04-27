/*******************************************************************
            Projekt: Zasuwka do drzwi.
Moduł decyzyjny opiera się na kodzie w języku C z bibliotą MFRC522 
obsługującą czujnik kart magnetycznych.
Moduł operacyjny wykonujący akcje opiera się na metodach
napisanych w języku assembler, ich lista znajduje sie w pliku 
nagłówkowym:"assembler.h", metody podają napięcia na poszczególne 
piny co pozwalaotwierać, zamykać zamek oraz świecić diodami
i uruchamiać brzęczyk

Projekt ustawiony pod płytkę Arduino Leaonardo.

Wykorzystane piny:
| Urządzenie                |   Odpowiadający pin               |
-----------------------------------------------------------------
Silnik  -sterowanie w prawo:|   Digital PIN 6
        -sterowanie w lewo: |   Digital PIN 4
Czerwona dioda LED :        |   Digital PIN 9
Zielona dioda LED           |   Digital PIN 8
Brzeęczyk                   |   Digital PIN 12
Moduł MFRC522:              
        * RST/Reset         |   ICDP-5
        * SPI SS            |   Digital PIN 10
        * SPI MOSI          |   ICSP-4
        * SPI MISO          |   ICSP-1
        * SPI SCK           |   ICSP-3


******************************************************************/
#include <SPI.h>
#include <MFRC522.h>
#include "assembler.h"
constexpr uint8_t RST_PIN =  5  ;        // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN =  10   ;      // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // instancja modułu MFRC522
bool state = false; //status zamka(false -otwarty/true -zamknięty - domyślnie otwarty)

void setup() {
  pinsSetup();       //USTAWIANIE PINOW DO TESTOWANIA AKCJI
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		 // PĘTLA WYKRYWAJĄCA BŁĄD URUCHOMIENIA OKNA DIALOGOWEGO
	SPI.begin();			// Inicjacja portów ICSP(SPI)
	mfrc522.PCD_Init();		// Inicjacja modułu MFRC522
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); //komunikat okna dialogowego sygnalizujący poprawne uruchomienie komponentów
}

void loop() {
	// Dodawanie nowej karty
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// wybieranie jednej z kart
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
 
//operacja po zeskanoaniu karty
if (mfrc522.uid.uidByte[0] == 0x3a &&
     mfrc522.uid.uidByte[1] == 0x98 &&
     mfrc522.uid.uidByte[2] == 0x34 &&
     mfrc522.uid.uidByte[3] == 0x2d) {
     //shardkodowane ID karty która ma dostęp
     Serial.println("Card 3A-98-34-2D, access granted");
     if(state){
      closing();//akcja zamyjkania zamka
      state = true;
     }else{
      opening();//akcja otworzenia zamka
      state = false;
     }   
}else{
    //niepoprawny adres id wyswietla komunikat i w oknie dialogowym
    //o nieznanym adresie id karty i wyświetla go
     Serial.print("Unknowed card (NR:");
     Serial.print(mfrc522.uid.uidByte[0],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[1],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[2],HEX);
     Serial.print("-");
     Serial.print(mfrc522.uid.uidByte[3],HEX);
     Serial.println("), access denied");
     wrongId();
     
}

}

//niepoprawny adres id, brzęczyk + czerwona doda
void wrongId(){
  redLedOn();
  buzzerOn();
  delay_1500ms();
  redLedOff();
  buzzerOff();
}

//otwieranie i zamykanie zamka + mryganie zieloną dioda i pikanie
void opening(){
  engineLeft();
  greenLedOn();
  buzzerOn();
  delay_500ms();
  greenLedOff();
  buzzerOff();
  delay_500ms();
  greenLedOn();
  buzzerOn();
  delay_500ms();
  greenLedOn();
  buzzerOn();
  engineStop();
}

void closing(){
  engineRight();
  greenLedOn();
  buzzerOn();
  delay_500ms();
  greenLedOff();
  buzzerOff();
  delay_500ms();
  greenLedOn();
  buzzerOn();
  delay_500ms();
  greenLedOn();
  buzzerOn();
  engineStop();
}
