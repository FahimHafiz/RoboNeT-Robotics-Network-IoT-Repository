<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>

# Arduino Integration with RFID Module (RC522)
This guide explains how to integrate the RFID Module (RC522) with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Component Name and Type
* Name: RFID Module (RC522)
* Type: Radio Frequency Identification (RFID) Reader and Writer
### Required Library
* You will need the MFRC522 library to work with this module. Install it via the Arduino Library Manager.

## Purpose
* The RFID Module (RC522) is used to:
* Read unique IDs from RFID cards or tags.
* Build access control systems.
* Store and retrieve small amounts of data on RFID cards.

## Hardware Details
Components Needed:
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* RFID Module (RC522): Includes the reader and RFID card/tag.
* Connecting Wires: Jumper wires (Male-to-Male or Male-to-Female).
* Power Supply: USB cable to power the Arduino.
## Code with Explanation
Here’s a simple Arduino program to read RFID tags:
Code Example:
```bash
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
```
## Code Explanation:
* Include Libraries: Adds the SPI and MFRC522 libraries for communication with the RFID module.
* Initialize RFID Module: Configures the RC522 to start reading cards.
* Check for Cards: PICC_IsNewCardPresent() detects if a card is near the reader.
* Read UID: PICC_ReadCardSerial() retrieves the unique ID (UID) of the card.
* Print UID: Displays the card UID on the Serial Monitor.

## Troubleshooting Tips
* No Card Detected: Ensure the RFID module is powered (check the LED).
* Incorrect UID Values: Verify the connections, especially the SPI pins.
* Library Issues: Make sure the MFRC522 library is installed and up-to-date.
* Unstable Readings: Use a stable 3.3V power source for the RFID module.

## Diagram
Below is a block diagram explaining the system:

|RFID Pin  |  Arduino Pin  |  Description  |
|----------|---------------|---------------|
|SDA        |D10          |Serial Data (SPI SS pin)|
|SCK        |D13          |Serial Clock (SPI SCK pin)|
|MOSI        |D11          |Master Out Slave In|
|MISO        |D12          |Master In Slave Out|
|IRQ         |Not used      |Interrupt (optional)|
|GND          |GND          |Ground|
|RST            |D9          |Reset|
|3.3V            |3.3V          |Power supply|


This setup ensures smooth communication between the Arduino and the RFID module.

Now you’re ready to use the RFID Module (RC522) with Arduino for exciting projects like access control systems! 😊

