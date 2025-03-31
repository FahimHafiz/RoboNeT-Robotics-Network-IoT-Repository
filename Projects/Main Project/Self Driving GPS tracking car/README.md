# United International University

## Department of Computer Science and Engineering

# **Self-Driving GPS Tracking Car**

## **Project Overview**

The goal of this project is to develop an **ESP32-based autonomous vehicle** capable of navigating to predefined GPS coordinates. The car processes **real-time GPS data** to determine its location and control the movement of motors using a motor driver module. Additionally, a **Bluetooth module** transmits navigation and status updates to a mobile device for monitoring.

This project demonstrates how **GPS-based autonomous navigation** can be applied to small-scale robotic systems, which can be further enhanced with obstacle detection, real-time tracking, and wireless communication.

![overview](https://github.com/user-attachments/assets/7c173e28-a579-42e4-b5037-e9549250d14d)

---

## **Hardware Components and Justifications**

### **1. ESP32 Microcontroller** To learn more about ESP32 and its usage, visit the [ESP32 Documentation](https://github.com/FahimHafiz/NetIoT-Network-IoT-Repository/tree/main/02.%20ESP32).

- **Why are we using ESP32 for this project?** The ESP32 is chosen because of its built-in **WiFi & Bluetooth**, **dual-core processing**, and **multiple GPIOs** that allow for seamless integration with sensors and motor drivers. It offers an efficient solution for IoT-based projects.
- **Power Consumption:** ~160mA (active mode)

### **2. GPS Module (NEO-6M or similar)** For an in-depth explanation of how GPS modules work, refer to [GPS Module Guide]().

- **Why is a GPS module necessary?** The GPS module provides **real-time latitude and longitude data**, which is crucial for autonomous navigation. The vehicle uses this information to determine its position and make navigation decisions.
- **Operating Voltage:** 3.3V – 5V 
- **Power Consumption:** ~50mA

### **3. Motor Driver (L298N or L293D)** For additional details about motor drivers, check the [Motor Driver Guide](https://github.com/FahimHafiz/NetIoT-Network-IoT-Repository/tree/main/01.%20Arduino/Sensors_Motors/BTS7960_Motor_Driver).

- **Why do we need a motor driver?** The ESP32 cannot directly power motors due to **low output current and voltage levels**. A **motor driver (H-Bridge circuit)** is required to provide sufficient voltage and current for motor control.
- **Power Requirements:**
 - **L298N:** 5V logic input, motor voltage 7V – 12V, peak current 2A 
 - **L293D:** 5V logic input, motor voltage 4.5V – 12V, max current 600mA per channel

### **4. Four DC Motors (200 RPM Each)** To know how to operate those motors using motor driver see the previously mentioned Motor driver guide.
The vehicle requires four motors to enable movement in **forward, backward, and turning directions**. The speed and torque of these motors allow precise navigation.
- **Motor Specifications:**
 - **Voltage:** 6V – 12V 
 - **Current:** ~300mA – 600mA per motor (depending on load) 
 - **Power Consumption:** ~5W per motor

### **5. Bluetooth Module (Optional if not using ESP32's built-in Bluetooth)**
- **Why include a Bluetooth module?** Bluetooth allows for **real-time monitoring of GPS coordinates and system status** via a mobile device.
- **Power Consumption:** ~30mA

### **6. Battery Pack (Funfly 1550mAh 4S 100C 14.8V 22.94Wh Li-Po)** For a detailed explanation of Li-Po batteries, watch [Battery Information]([https://images.app.goo.gl/WE2Rad5Mmi6zy4Sg8](https://youtu.be/D98e2lRe2O8?si=R-YbRmi-yAfHtEH4)).

- **Why this battery?** This rechargeable **4-cell (4S) Li-Po battery** provides sufficient voltage and current for all components, ensuring stable operation.
- **Estimated Power Consumption Calculation:**
 - **ESP32:** 160mA @ 3.3V → **0.528W**
 - **GPS Module:** 50mA @ 5V → **0.25W**
 - **Motor Driver:** 2A max @ 5V → **10W**
 - **Motors (4x 200 RPM):** 600mA each @ 12V → **28.8W** (4 motors)
 - **Total Estimated Load:** **39.578W**
 - **Battery Capacity:** 22.94Wh / 39.578W ≈ **35 minutes of runtime**

### **7. Chassis and Wheels**
- **Why do we need a chassis?** The chassis serves as the **structural frame** for mounting electronic components and enabling movement.
- **Material Used:** **PVC Board**

### **8. HMC5883 Compass Module**
- **Why include a Compass Module?**
  - The compass module provides **heading information**, which is crucial for accurate navigation. The vehicle uses this heading to determine its orientation relative to the target GPS coordinates, allowing for precise turns and course corrections.
  - It allows the vehicle to maintain the correct course even when GPS signals are weak or unavailable.
  - **Operating Voltage:** 3.3V - 5V
  - **Power Consumption:** ~3mA

---

## **Software Requirements**
- **Arduino IDE** (for programming ESP32)
- **ESP32 Board Support Package** (for ESP32 compatibility)
- **TinyGPS++ Library** (to process GPS data)
- **BluetoothSerial Library** (for Bluetooth communication)
- **Adafruit HMC5883 Library** (for compass communication)

---

## **Power Consumption Summary**
| **Component** | **Voltage** | **Current** | **Power Consumption** |
|--------------|------------|------------|------------------|
| ESP32 | 3.3V | 160mA | 0.528W |
| GPS Module | 5V | 50mA | 0.25W |
| Motor Driver | 5V | 2A | 10W |
| Motors (4x) | 12V | 600mA each | 28.8W |
| Compass Module | 5V | 3mA | 0.015W |
| **Total Power** | | | **39.593W** |

- **Battery: Funfly 1550mAh 4S 100C Li-Po (14.8V, 22.94Wh)**
- **Estimated Runtime:** **~35 minutes** under full load

---

## **Installation & Usage**
1. **Install Arduino IDE** and required libraries.
2. **Assemble the hardware** following the wiring diagram.
3. **Upload the code** to the ESP32.
4. **Power the system** using the battery pack.
5. **Connect to Bluetooth** and monitor the data.
6. **Set GPS coordinates** in the code and test navigation.

---

## **Code Explanation**

The code uses the ESP32 to control the car's movement based on GPS and compass data. Key functions include:

-   **`readGPS()`**: Reads and parses GPS data to get the car's current location.
-   **`readCompass()`**: Reads heading data from the HMC5883 compass module.
-   **`getDistance()`**: Calculates the distance between two GPS coordinates.
-   **`getAnglee()`**: Calculates the bearing between two GPS coordinates.
-   **`LeftRight()`**: Adjusts the car's heading using motor control based on the difference between the current and target headings.
-   **`goo()`**: Moves the car forward.
-   **`nextTarget()`**: Selects the next GPS coordinate from the target list.
-   **`forward()`, `leftward()`, `rightward()`, `stopp()`**: Functions to control the motors.

The code continuously reads GPS and compass data, calculates the car's position and heading, and adjusts the motors to navigate to the target GPS coordinates. Bluetooth is used to transmit real-time data to a mobile device.

---

## **License**
This project is **open-source** and available for modification and improvement.
