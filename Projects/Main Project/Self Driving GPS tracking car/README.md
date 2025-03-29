# United International University  
## Department of Computer Science and Engineering  

# **Self-Driving GPS Tracking Car**  

## **Project Overview**  
The goal of this project is to develop an **ESP32-based autonomous vehicle** capable of navigating to predefined GPS coordinates. The car will process **real-time GPS data** to determine its location and control the movement of motors using a motor driver module. Additionally, a **Bluetooth module** will transmit navigation and status updates to a mobile device for monitoring.  

This project aims to demonstrate how **GPS-based autonomous navigation** can be applied to small-scale robotic systems, which can be further enhanced with obstacle detection, real-time tracking, and wireless communication.  

![overview](https://github.com/user-attachments/assets/7c173e28-a579-42e4-b037-e9549250d14d)

---

## **Hardware Components and Justifications**  

### **1. ESP32 Microcontroller** 
To know more about ESP32 and it's usage, visit this: [ESP32]([02. ESP32](https://github.com/FahimHafiz/NetIoT-Network-IoT-Repository/tree/main/02.%20ESP32))
- **Why ESP32 is chosen for this project?** The ESP32 is chosen due to its built-in **WiFi & Bluetooth**, **dual-core processing**, and **multiple GPIOs** that allow for easy integration with sensors and motor drivers.  
- **Power Consumption:** ~160mA (active mode)  

### **2. GPS Module (NEO-6M or similar)**
[Link](https://images.app.goo.gl/YzeaGAUka7XqRg128)
- **Why?** It provides real-time latitude and longitude data, which is essential for autonomous navigation.  
- **Operating Voltage:** 3.3V – 5V  
- **Power Consumption:** ~50mA  

### **3. Motor Driver (L298N or L293D)**  
[Link](https://images.app.goo.gl/6MKFwQTkeC5m5sdP9)
- **Why?** The ESP32 cannot directly power motors, so an **H-Bridge motor driver** is used to provide sufficient voltage and current.  
- **Power Requirements:**  
  - **L298N:** 5V logic input, motor voltage 7V – 12V, peak current 2A  
  - **L293D:** 5V logic input, motor voltage 4.5V – 12V, max current 600mA per channel  

### **4. Four DC Motors**
[Link](https://images.app.goo.gl/oJi21Bt1LuS9vT7W9)
- **Why?** These motors drive the vehicle forward, backward, and turn to the correct direction based on GPS data.  
- **Motor Specifications:**  
  - **Voltage:** 6V – 12V  
  - **Current:** ~300mA – 600mA per motor (depending on load)  
  - **Power Consumption:** ~5W per motor  

### **5. Bluetooth Module (Optional if not using ESP32's built-in Bluetooth)**  
- **Why?** It allows for real-time monitoring of GPS coordinates and system status through a mobile device.  
- **Power Consumption:** ~30mA  

### **6. Battery Pack (Li-ion or Li-Po, 7.4V or 12V)**  
[Link](https://images.app.goo.gl/WE2Rad5Mmi6zy4Sg8)
- **Why?** A rechargeable battery powers the ESP32, motors, and other components. A **step-down regulator** may be needed for stable voltage to ESP32 and sensors.  
- **Estimated Battery Requirement:**  
  - Total estimated power consumption: **~1.5A – 2A**  
  - If using a **7.4V Li-Po battery (2500mAh)**, runtime is around **1 – 1.5 hours**.  

### **7. Chassis and Wheels**  
- **Why?** The body structure to hold all electronic components and enable movement.
- We used a PVC board for our car

---

## **Software Requirements**  
- **Arduino IDE** (for programming ESP32)  
- **ESP32 Board Support Package** (for ESP32 compatibility)  
- **TinyGPS++ Library** (to process GPS data)  
- **BluetoothSerial Library** (for Bluetooth communication)  

---

## **Wiring Diagram**  

| **ESP32 Pin** | **Connection** |
|--------------|--------------|
| 3V3 | GPS VCC |
| GND | GPS GND |
| GPS RX | ESP32 TX |
| GPS TX | ESP32 RX |
| Motor IN1 | ESP32 GPIO X |
| Motor IN2 | ESP32 GPIO Y |
| Enable A | PWM GPIO |
| Bluetooth TX | ESP32 RX |
| Bluetooth RX | ESP32 TX |

![Wiring Diagram](https://github.com/user-attachments/assets/5ba249dc-792b-4837-8eb4-86a1ebd24553)  

---

## **Code Explanation**  

### **1. Library Inclusions and Definitions**  
```cpp
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <BluetoothSerial.h>
```
- **TinyGPS++** processes GPS location data.  
- **HardwareSerial** establishes serial communication with the GPS module.  
- **BluetoothSerial** allows Bluetooth communication with a mobile device.  

### **2. GPS Module Initialization**  
```cpp
HardwareSerial GPS_Serial(1);
TinyGPSPlus gps;
BluetoothSerial SerialBT;
```
- **GPS_Serial** is set up to read GPS data.  
- **TinyGPSPlus** is initialized for processing GPS signals.  
- **SerialBT** is initialized for Bluetooth communication.  

### **3. Motor Control Functions**  
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
- Functions to **move forward, backward, and stop** the car.  

### **4. GPS Data Processing**  
```cpp
void processGPS() {
    while (GPS_Serial.available() > 0) {
        gps.encode(GPS_Serial.read());
    }
}
```
- Reads and updates **current GPS coordinates**.  

### **5. Navigation Logic**  
```cpp
void navigateTo(float targetLat, float targetLon) {
    float currentLat = gps.location.lat();
    float currentLon = gps.location.lng();
    float distance = calculateDistance(currentLat, currentLon, targetLat, targetLon);
    adjustDirection(targetLat, targetLon, currentLat, currentLon);
}
```
- Retrieves **current coordinates**, **calculates distance**, and **adjusts movement direction**.  

### **6. Distance Calculation Algorithm**  
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
- Uses the **Haversine formula** to determine the shortest distance between two points.  

### **7. Bluetooth Status Updates**  
```cpp
void sendBluetoothStatus() {
    SerialBT.print("Current Location: ");
    SerialBT.print(gps.location.lat(), 6);
    SerialBT.print(", ");
    SerialBT.println(gps.location.lng(), 6);
}
```
- Sends **real-time GPS data** via Bluetooth.  

---

## **Installation & Usage**  
1. **Install Arduino IDE** and required libraries.  
2. **Assemble the hardware** following the wiring diagram.  
3. **Upload the code** to the ESP32.  
4. **Power the system** using the battery pack.  
5. **Connect to Bluetooth** and monitor the data.  
6. **Set GPS coordinates** in the code and test navigation.  

---

## **Future Improvements**  
- **Obstacle avoidance** with ultrasonic sensors.  
- **Real-time tracking** with cloud-based data logging.  
- **WiFi-based remote control** for improved monitoring.  

---

## **License**  
This project is **open-source** and available for modification and improvement.  

---
