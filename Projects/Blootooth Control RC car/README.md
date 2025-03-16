# United International University  
## Department of Computer Science and Engineering  

# ESP32 Bluetooth Car

## Overview
This project is an ESP32-based Bluetooth-controlled car that uses the `DabbleESP32` library to receive gamepad inputs via Bluetooth. The car's movement is controlled through PWM signals that regulate the speed and direction of two DC motors.

## Features
- Bluetooth-based remote control using Dabble App
- Independent control of left and right motors
- PWM-based speed control
- Directional movement (forward, backward, left, right)

## Hardware Requirements
- ESP32 board
- Two DC motors
- L298N Motor Driver or similar
- Power supply (battery pack)
- Bluetooth-enabled device with the Dabble app installed

## Software Requirements
- Arduino IDE
- ESP32 board support installed
- `DabbleESP32` library installed

## Wiring Diagram
| ESP32 Pin | Connection |
|-----------|-----------|
| 22        | Right motor enable (PWM) |
| 16        | Right motor IN1 |
| 17        | Right motor IN2 |
| 23        | Left motor enable (PWM) |
| 18        | Left motor IN1 |
| 19        | Left motor IN2 |

![ESP32 Bluetooth Car](https://github.com/user-attachments/assets/b0c1bf0a-5a53-4357-b933-844f7889ec06)


## Code Explanation
### 1. Library Inclusions and Definitions
```cpp
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
```
- Enables gamepad module in `DabbleESP32`.

### 2. Motor Pin Configuration
```cpp
int enableRightMotor = 22; 
int rightMotorPin1 = 16;
int rightMotorPin2 = 17;
int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;
```
- Defines motor control pins.

### 3. PWM Setup
```cpp
const int PWMFreq = 1000;
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;
```
- Configures PWM frequency and resolution.

### 4. Motor Control Function
```cpp
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
    if (rightMotorSpeed < 0) {
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
    } else if (rightMotorSpeed > 0) {
        digitalWrite(rightMotorPin1, HIGH);
        digitalWrite(rightMotorPin2, LOW);
    }
}
```
- Controls motor direction based on speed values.

### 5. Bluetooth Gamepad Input Handling
```cpp
void loop() {
    Dabble.processInput();
    int xAxis = GamePad.getXaxisData();
    int yAxis = GamePad.getYaxisData();
}
```
- Processes Bluetooth input from the gamepad.

## Installation & Usage
1. Install the `DabbleESP32` library in Arduino IDE.
2. Upload the code to the ESP32 board.
3. Connect the ESP32 to the `Dabble` app via Bluetooth.
4. Control the car using the app’s gamepad module.

## Future Improvements
- Adding obstacle detection with ultrasonic sensors.
- Implementing a PID controller for smoother movement.
- Integrating a mobile app for custom control features.

## License
This project is open-source and available for modification and improvement.

