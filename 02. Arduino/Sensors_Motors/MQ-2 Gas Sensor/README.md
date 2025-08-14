<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>


# Arduino Integration with MQ-2 Gas Sensor
This guide explains how to integrate an MQ-2 Gas Sensor with an Arduino board. The documentation is designed for junior students and is easy to understand.
## Component Name and Type
* Name: MQ-2 Gas Sensor
* Type: Gas Sensor (Detects LPG, Smoke, Alcohol, and Methane)
## Required Library
* No additional libraries are required for basic functionality. The sensor outputs analog values, which can be read using Arduino's analog pins.
## Purpose
* The MQ-2 gas sensor is used to:
* Detects gases like LPG, methane, alcohol, and smoke.
* Build safety systems such as gas leakage detectors.
* Automate alerts or responses based on gas levels.
## Hardware Details
Components Needed:
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* MQ-2 Gas Sensor: Module with analog and digital outputs.
* Connecting Wires: Jumper wires (Male-to-Male or Male-to-Female).
* Power Supply: USB cable to power the Arduino.
## Code with Explanation
Here’s a simple Arduino program to read gas levels using the MQ-2 sensor:
```bash
const int mq2Pin = A0; // MQ-2 analog output connected to A0

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(mq2Pin, INPUT); // Set the MQ-2 pin as input
  Serial.println("MQ-2 Gas Sensor Ready");
}

void loop() {
  int gasLevel = analogRead(mq2Pin); // Read analog value from MQ-2

  Serial.print("Gas Level: ");
  Serial.println(gasLevel); // Print gas level value

  delay(500); // Wait for 500 milliseconds
```
## Code Explanation:
* Define Pins: Specifies the pin where the MQ-2 is connected.
* Setup Function: Configures the MQ-2 pin as an input and initializes the Serial Monitor.
* Loop Function:
  * Reads the analog value from the sensor.
  * Prints the gas level value to the Serial Monitor.
## roubleshooting Tips
* No Readings: Ensure the connections are correct and secure.
* Incorrect Values: Allow the sensor to preheat for 20-30 seconds before readings stabilize.
* Serial Monitor Issues: Ensure the correct baud rate (9600) is selected in the Serial Monitor.
* Fluctuating Values: Test the sensor in a stable environment with minimal interference.
## Diagram
Below is a block diagram explaining the system:

|MQ-2 Pin  |  Arduino Pin  |  Description|
|----------|---------------|--------------|
|VCC       |5V             |Power supply|
|GND       |GND            |Common ground|
|AO        |A0             |Analog output to Arduino|
|DO        |D2 (Optional)   |Digital output for threshold detection|

### Circuit Description:
* The analog output (AO) is connected to Arduino's A0 pin to measure gas levels.
* The digital output (DO) can be used with a threshold potentiometer to trigger alerts.

This setup ensures accurate detection of gas levels using the MQ-2 sensor.

Now you’re ready to use the MQ-2 gas sensor with Arduino! Have fun building safety or monitoring systems! 😊

