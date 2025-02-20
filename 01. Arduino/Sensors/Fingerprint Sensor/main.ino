#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger(&mySerial);

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("Fingerprint Sensor Ready");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor found and verified!");
  } else {
    Serial.println("Sensor not found :(");
    while (1) { delay(1); }
  }
}

void loop() {
  Serial.println("Place your finger on the sensor...");
  uint8_t id = finger.getImage();
  if (id == FINGERPRINT_OK) {
    Serial.println("Finger detected!");
  } else {
    Serial.println("No finger detected");
    delay(1000);
    return;
  }

  id = finger.image2Tz();
  if (id == FINGERPRINT_OK) {
    Serial.println("Fingerprint converted");
  } else {
    Serial.println("Error in conversion");
    return;
  }

  id = finger.fingerFastSearch();
  if (id == FINGERPRINT_OK) {
    Serial.print("Found a match! ID: ");
    Serial.println(finger.fingerID);
  } else {
    Serial.println("No match found");
  }

  delay(1000);
}
