<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>



# Arduino Integration with Button and LED Control
This guide explains how to integrate a Button and LED with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Component Name and Type
* Name: Button and LED
* Type: Input (Button) and Output (LED)
### Required Library
* #### No external library is needed for this project.
## Purpose
This setup allows you to:
* Turn an LED ON and OFF using a button.
* Learn how to handle digital inputs and outputs in Arduino.
* Understand the basics of user interaction with electronics.
## Hardware Details
### Components Needed:
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* Button: Push button switch.
* LED: Any color LED.
* Resistors: 220Ω for LED, 10kΩ for button pull-down.
* Connecting Wires: Male-to-Male or Male-to-Female jumper wires.
* Power Supply: USB cable to power the Arduino.


## Code with Explanation
Here’s a simple Arduino program to control an LED using a button:
Code Example:
```bash
const int buttonPin = 2;  // Button connected to D2
const int ledPin = 13;    // LED connected to D13
int buttonState = 0;      // Variable to store button state

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read button state

  if (buttonState == HIGH) { // If button is pressed
    digitalWrite(ledPin, HIGH); // Turn LED ON
    Serial.println("LED ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    Serial.println("LED OFF");
  }
}
```

## Code Explanation:
* Define Pins: Assigns pin numbers for the button and LED.
* Setup Function: Initializes pin modes and serial communication.
* Read Button State: Continuously checks if the button is pressed.
* Control LED: Turns LED ON when the button is pressed, otherwise turns it OFF.
* Serial Output: Displays LED status on the Serial Monitor.
## Troubleshooting Tips
* LED Not Turning ON: Check LED polarity and connections.
* Button Not Working: Ensure correct wiring and use a pull-down resistor (10kΩ).
* Unstable Readings: Try adding a small delay in the loop (e.g., delay(50);).
* No Serial Output: Verify the baud rate in the Serial Monitor (9600).
## Diagram
Below is a block diagram explaining the system:

|  Arduino Board       | Button & LED         |
|----------------------|----------------------|
|       D2 (Input)     |            Button    |
|       D13 (Output)   |              LED     |
|       GND            |              GND     |
|       5V             |              VCC     |

This setup helps in understanding digital inputs and outputs in Arduino.

Now you’re ready to control an LED with a button using Arduino! 😊

