<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>


# Arduino Integration with LDR (Light Dependent Resistor)
This guide explains how to integrate an LDR (Light Dependent Resistor) with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Component Name and Type
* Name: LDR (Light Dependent Resistor)
* Type: Analog Light Sensor
### Required Library
* No additional libraries are required for basic functionality. The LDR works with the Arduino's analog pins.
## Purpose
* The LDR sensor is used to:
* Measure the intensity of ambient light.
* Automate systems based on light levels, such as streetlights or smart curtains.
* Build light-following robots or light-sensitive alarms.
## Hardware Details
Components Needed:
* Arduino Board: Any model 
* LDR Sensor: A Light Dependent Resistor.
* Resistor: 10kΩ (to create a voltage divider).
* Connecting Wires: Jumper wires (Male-to-Female).
* Breadboard: For easy connections.

## Code with Explanation
Here’s a simple Arduino program to read light intensity using the LDR:
```bash
const int ldrPin = A0; // LDR connected to Analog Pin A0

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(ldrPin, INPUT); // Set the LDR pin as input
  Serial.println("LDR Sensor Ready");
}

void loop() {
  int lightValue = analogRead(ldrPin); // Read analog value from LDR

  Serial.print("Light Intensity: ");
  Serial.println(lightValue); // Print light intensity value

  delay(500); // Wait for 500 milliseconds
}
```
## Code Explanation:
* Define Pins: Specifies the pin where the LDR is connected.
* Setup Function: Configures the LDR pin as an input and initializes the Serial Monitor.
* Loop Function:
* Reads the analog value from the LDR.
* Prints the light intensity value to the Serial Monitor.
## Troubleshooting Tips
* No Readings: Ensure the connections are correct and secure.
* Incorrect Values: Verify the resistor value (10kΩ is recommended) and check the ambient light source.
* Serial Monitor Issues: Ensure the correct baud rate (9600) is selected in the Serial Monitor.
* Fluctuating Values: Avoid shadows or interference from changing light sources.
## Diagram
Below is a block diagram explaining the system:
Follow the table below to connect the LDR to the Arduino:

|    LDR Terminal    |    Arduino Pin    |    Additional Components               |
|--------------------|-------------------|----------------------------------------|
|    One Terminal    |    5V             |    Connected directly to 5V            |
|    Other Terminal  |      A0           |  Connected via a 10kΩ resistor to GND  |

### Circuit Description:
* One side of the LDR is connected to 5V.
* The other side of the LDR is connected to Analog Pin A0 on the Arduino and also to a 10kΩ resistor, which is connected to GND. This forms a voltage divider circuit.

This setup ensures accurate light intensity measurements using the LDR sensor.

Now you’re ready to use the LDR sensor with Arduino! Have fun exploring light-based projects! 😊

