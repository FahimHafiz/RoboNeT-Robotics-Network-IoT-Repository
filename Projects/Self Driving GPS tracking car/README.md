# United International University  
## Department of Computer Science and Engineering  

# Self-Driving GPS Tracking Car

## Overview
This project is an ESP32-based autonomous vehicle that navigates to preset GPS coordinates. The car utilizes an ESP32 microcontroller to process GPS data and determine its location. It then controls the movement of motors via a motor driver module to reach the target location. A Bluetooth module is used to send status updates to a mobile device.

![overview](https://github.com/user-attachments/assets/7c173e28-a579-42e4-b037-e9549250d14d)


## Features
- **Autonomous navigation** using GPS coordinates
- **Real-time location tracking** with GPS module
- **Bluetooth communication** for status monitoring
- **Motor control** for precise movement adjustments
- **Distance calculation algorithm** to determine navigation strategy
- **Direction adjustment mechanism** to correct heading errors

## Hardware Requirements
- **ESP32** microcontroller
- **GPS module** (e.g., NEO-6M GPS)
- **Motor driver** (e.g., L298N or L293D)
- **Two DC motors** for movement
- **Battery pack** (Li-ion or Li-Po recommended)
- **Bluetooth module** (if separate from ESP32)
- **Chassis and wheels** for mobility
- **Voltage regulator** (if needed to manage power supply)

## Software Requirements
- **Arduino IDE** for programming
- **ESP32 board support package** installed in Arduino IDE
- **TinyGPS++ library** for GPS data processing
- **BluetoothSerial library** for Bluetooth communication

## Wiring Diagram
| ESP32 Pin | Connection |
|-----------|-----------|
| 3V3       | GPS VCC |
| GND       | GPS GND |
| GPS RX    | ESP32 TX |
| GPS TX    | ESP32 RX |
| Motor IN1 | ESP32 GPIO X |
| Motor IN2 | ESP32 GPIO Y |
| Enable A  | PWM GPIO |
| Bluetooth TX | ESP32 RX |
| Bluetooth RX | ESP32 TX |

<img width="897" alt="diagram" src="https://github.com/user-attachments/assets/5ba249dc-792b-4837-8eb4-86a1ebd24553" />

## Code Explanation
### 1. Library Inclusions and Definitions
```cpp
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <BluetoothSerial.h>
```
- **`TinyGPS++`** processes GPS location data.
- **`HardwareSerial`** establishes serial communication with the GPS module.
- **`BluetoothSerial`** handles Bluetooth communication with an external device.

### 2. GPS Module Initialization
```cpp
HardwareSerial GPS_Serial(1);
TinyGPSPlus gps;
BluetoothSerial SerialBT;
```
- **GPS_Serial** is set up to read data from the GPS module.
- **TinyGPSPlus** object is created for parsing GPS signals.
- **SerialBT** is initialized to send real-time data via Bluetooth.

### 3. Motor Control Functions
```cpp
void moveForward() {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
}
void moveBackward() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
}
void stopMotors() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
}
```
- Functions for **moving forward, backward, and stopping** are defined.

### 4. GPS Data Processing
```cpp
void processGPS() {
    while (GPS_Serial.available() > 0) {
        gps.encode(GPS_Serial.read());
    }
}
```
- Reads incoming GPS signals and updates current location.

### 5. Navigation Logic
```cpp
void navigateTo(float targetLat, float targetLon) {
    float currentLat = gps.location.lat();
    float currentLon = gps.location.lng();
    float distance = calculateDistance(currentLat, currentLon, targetLat, targetLon);
    adjustDirection(targetLat, targetLon, currentLat, currentLon);
}
```
- **Retrieves current GPS coordinates**.
- **Calculates distance** to the target.
- **Adjusts movement direction** to navigate correctly.

### 6. Distance Calculation Algorithm
```cpp
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    float dLat = radians(lat2 - lat1);
    float dLon = radians(lon2 - lon1);
    float a = sin(dLat/2) * sin(dLat/2) + cos(radians(lat1)) * cos(radians(lat2)) * sin(dLon/2) * sin(dLon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float distance = 6371 * c * 1000; // Convert to meters
    return distance;
}
```
- Uses **Haversine formula** to calculate the distance between two coordinates.

### 7. Bluetooth Status Updates
```cpp
void sendBluetoothStatus() {
    SerialBT.print("Current Location: ");
    SerialBT.print(gps.location.lat(), 6);
    SerialBT.print(", ");
    SerialBT.println(gps.location.lng(), 6);
}
```
- Sends **real-time GPS data** via Bluetooth to an external device.

## Installation & Usage
1. **Set up Arduino IDE** and install required libraries.
2. **Connect ESP32** to the GPS module and motor driver as per the wiring diagram.
3. **Upload the code** to the ESP32 using Arduino IDE.
4. **Power the system** using a battery pack.
5. **Check Bluetooth connection** to receive status updates.
6. **Configure target GPS coordinates** within the code before deployment.
7. **Monitor movement** and ensure it reaches the destination accurately.

## Future Improvements
- **Obstacle avoidance** using ultrasonic sensors.
- **Real-time tracking** to recieve coordinates to verify accuracy of the traversal.

## License
This project is **open-source** and available for modification and improvement.

