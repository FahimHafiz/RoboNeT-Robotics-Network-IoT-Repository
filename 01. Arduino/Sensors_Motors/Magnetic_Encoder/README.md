<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>


# Arduino Integration with Magnetic Encoder
This guide explains how to integrate a magnetic encoder with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Component Name and Type
* Name: Magnetic Encoder
* Type: Rotary Position Sensor
### Required Library
*  You will need the "Encoder" library to work with the magnetic encoder. You can install it from the Arduino Library Manager.
## Purpose
* The magnetic encoder is used to:
* Measure the rotational position of a shaft.
* Determine angular velocity and direction of rotation.
* Build projects such as robotic arms, motor controllers, and automation systems.
## Hardware Details
Components Needed:
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* Magnetic Encoder: Compatible encoder module (e.g., AS5600).
* Connecting Wires: 4 jumper wires (Male-to-Female).
* Power Supply: USB cable to power the Arduino.

## Code with Explanation
Here’s a simple Arduino program to read the position from a magnetic encoder:
```bash
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
```
## Code Explanation:
* Include Libraries: Adds the required library for the encoder.
* Initialize Encoder: Checks if the magnetic encoder is connected properly.
* Read Data: Captures the position and angle values from the encoder.
* Print Data: Displays the readings on the Serial Monitor.
## Troubleshooting Tips
* Encoder Not Detected: Ensure the SDA and SCL pins are connected correctly and the power is supplied.
* Incorrect Readings: Verify that the encoder is aligned properly with the rotating shaft.
* Library Error: Ensure the AS5600 library is installed and up-to-date.
* Wiring Issues: Double-check the connections to avoid loose wires.
## Diagram
Below is a block diagram explaining the system:

<div align="center">
  <img width="429" alt="Image" src="https://github.com/user-attachments/assets/91c0d105-e1bd-42a8-873c-6a7be66bf9c8" />
</div>



Note: For boards like the Arduino Mega, check the I2C pins (usually SCL = 21, SDA = 20).

This setup ensures accurate position and angle measurement using a magnetic encoder.

Now you’re ready to use a magnetic encoder with Arduino! Have fun building amazing projects! 😊

