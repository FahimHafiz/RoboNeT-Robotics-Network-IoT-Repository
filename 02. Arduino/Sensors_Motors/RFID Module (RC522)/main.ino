#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9  // Reset pin
#define SS_PIN 10  // Slave Select pin

MFRC522 rfid(SS_PIN, RST_PIN); // Create an MFRC522 instance

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  SPI.begin();        // Initialize SPI bus
  rfid.PCD_Init();    // Initialize RFID module
  Serial.println("RFID Module Ready");
}

void loop() {
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) return;

  // Read the card
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  rfid.PICC_HaltA(); // Halt PICC communication
}
