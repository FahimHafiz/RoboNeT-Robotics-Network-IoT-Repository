<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>

# Arduino Integration with BTS7960 Motor Driver
This guide explains how to integrate the BTS7960 motor driver with an Arduino board. The documentation is designed for junior students and is easy to understand.
## Component Name and Type
* Name: BTS7960
* Type: High-Power Motor Driver
### Required Library
* No additional libraries are required for basic functionality. The motor driver is controlled using PWM signals from the Arduino.
## Purpose
* The BTS7960 motor driver is used to:
* Control DC motors with high current requirements (up to 43A).
* Adjust motor speed and direction using PWM signals.
* Build projects like robotic arms, electric vehicles, or conveyor systems.
## Hardware Details
Components Needed:
* Arduino Board: Arduino UNO
* BTS7960 Motor Driver Module.
* DC Motor: Any suitable motor within the current limit.
* Power Supply: 12V
* Connecting Wires: Jumper wires (Male-to-Female).
## Code with Explanation
Here’s a simple Arduino program to control the motor speed and direction using the BTS7960 motor driver:
```bash
const int R_EN = 2;  // Right enable pin
const int L_EN = 3; // Left enable pin
const int R_PWM = 5; // Right PWM pin
const int L_PWM = 6; // Left PWM pin

void setup() {
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Move motor forward
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, LOW);
  analogWrite(R_PWM, 128); // 50% speed
  analogWrite(L_PWM, 0);
  delay(2000);

  // Move motor backward
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, HIGH);
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 128); // 50% speed
  delay(2000);

  // Stop motor
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, LOW);
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 0);
  delay(2000);
}
```
## Code Explanation:
* Define Pins: Specifies the pins connected to the BTS7960 module.
* Setup Function: Configures the pins as outputs.
* Loop Function:
  * Controls the motor to move forward, backward, and stop.
  * Uses analogWrite for speed control and digitalWrite for direction.
## Troubleshooting Tips
* Motor Not Moving: Ensure the power supply to the motor driver is sufficient and connections are correct.
* Incorrect Direction: Verify the connections of the motor terminals and Arduino pins.
* No Speed Control: Check the PWM pins and ensure the correct duty cycle is applied.
* Overheating: Avoid exceeding the current limits of the motor driver and use proper cooling if necessary.
## Diagram
Below is a block diagram explaining the system:

<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/396d5ede-7699-4ca8-a80b-826e0dbe734c" />
</div>

This setup ensures smooth motor control with adjustable speed and direction.

Now you’re ready to use the BTS7960 motor driver with Arduino! Have fun building amazing motor control projects! 😊

