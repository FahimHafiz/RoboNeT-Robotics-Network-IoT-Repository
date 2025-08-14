<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>

# Arduino Integration with Soil Moisture Sensor
This guide explains how to integrate a Soil Moisture Sensor with an Arduino board. The documentation is designed for junior students and is easy to understand.
## Component Name and Type
* Name: Soil Moisture Sensor
* Type: Analog/Digital Sensor
### Required Library
* No additional libraries are required for basic functionality. The sensor works with the Arduino's analog and digital pins.
## Purpose
* The Soil Moisture Sensor is used to:
* Measure the moisture level in soil.
* Automate irrigation systems based on soil dryness.
* Monitor plant health in smart gardening systems.

## Hardware Details
Components Needed:
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* Soil Moisture Sensor Module: Typically includes two probes and a module with analog and digital outputs.
* Connecting Wires: Jumper wires (Male-to-Male or Male-to-Female).
* Power Supply: USB cable to power the Arduino.

## Code with Explanation
Here’s a simple Arduino program to read soil moisture levels:
```bash
const int soilPin = A0; // Soil moisture sensor analog output connected to A0
const int threshold = 500; // Set a threshold value for moisture level

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(soilPin, INPUT); // Set the soil sensor pin as input
  Serial.println("Soil Moisture Sensor Ready");
}

void loop() {
  int moistureValue = analogRead(soilPin); // Read analog value from the sensor

  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureValue); // Print the moisture value

  if (moistureValue < threshold) {
    Serial.println("Soil is dry! Water the plant.");
  } else {
    Serial.println("Soil moisture is sufficient.");
  }

  delay(1000); // Wait for 1 second
}
```
## Code Explanation:
* Define Pins: Specifies the pin where the sensor is connected.
* Setup Function: Configures the sensor pin as an input and initializes the Serial Monitor.
* Loop Function:
  * Reads the analog value from the sensor.
  * Prints the moisture level to the Serial Monitor.
  * Checks if the moisture level is below a threshold and provides feedback.

## Troubleshooting Tips
* No Readings: Ensure the connections are correct and secure.
* Incorrect Values: Check if the sensor probes are properly inserted into the soil.
* Serial Monitor Issues: Ensure the correct baud rate (9600) is selected in the Serial Monitor.
* Fluctuating Values: Test the sensor in consistent soil conditions and avoid moving the probes frequently.

## Diagram
Below is a block diagram explaining the system:

|Sensor Pin  |  Arduino Pin  |  Description  |
|------------|---------------|---------------|
|VCC         |  5V           |  Power supply |
|  GND       |      GND      |  Common ground|
|    AO      |      A0       |Analog output to Arduino|
|DO (Optional)|D2|Digital output for threshold detection

## Circuit Description:
* The analog output (AO) is connected to Arduino's A0 pin to measure soil moisture levels.
* The digital output (DO) can be used to trigger alerts or actions when the moisture level crosses a threshold.

This setup ensures accurate soil moisture measurements using the sensor.

Now you’re ready to use the Soil Moisture Sensor with Arduino! Have fun building smart gardening projects! 😊

