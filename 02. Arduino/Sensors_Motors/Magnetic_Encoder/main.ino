#include <Wire.h>
#include <AS5600.h>

AS5600 encoder;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!encoder.begin()) {
    Serial.println("Encoder not detected! Check wiring.");
    while (1);
  }
  Serial.println("Magnetic Encoder Ready");
}

void loop() {
  int position = encoder.getPosition();
  float angle = encoder.getAngle();

  Serial.print("Position: ");
  Serial.print(position);
  Serial.print("\tAngle: ");
  Serial.println(angle);

  delay(500);
}
