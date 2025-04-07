# United International University

## Department of Computer Science and Engineering

# **RoboQuest- A Self-Driving GPS Tracking Car**

## **Project Overview**

The goal of this project is to develop an **ESP32-based autonomous vehicle** capable of navigating to predefined GPS coordinates. The car processes **real-time GPS data** to determine its location and control the movement of motors using a motor driver module. Additionally, a **Bluetooth module** transmits navigation and status updates to a mobile device for monitoring.

This project demonstrates how **GPS-based autonomous navigation** can be applied to small-scale robotic systems, which can be further enhanced with obstacle detection, real-time tracking, and wireless communication.

![overview](https://github.com/user-attachments/assets/7c173e28-a579-42e4-b037-e9549250d14d)
---

## **Hardware Components and Justifications**

### **1. ESP32 Microcontroller** To learn more about ESP32 and its usage, visit the [ESP32 Documentation](https://github.com/FahimHafiz/NetIoT-Network-IoT-Repository/tree/main/02.%20ESP32).

- **Why are we using ESP32 for this project?** The ESP32 is chosen because of its built-in **WiFi & Bluetooth**, **dual-core processing**, and **multiple GPIOs** that allow for seamless integration with sensors and motor drivers. It offers an efficient solution for IoT-based projects. Compared to Arduino UNO or Nano, ESP32 offers more processing power and wireless communication features.
- **Power Consumption:** ~160mA (active mode)
- **Student Challenge:** _What other microcontrollers could be used in place of ESP32 and what would be the trade-offs?_

### **2. GPS Module (NEO-6M or similar)** For an in-depth explanation of how GPS modules work, refer to [GPS Module Guide]().

- **Why is a GPS module necessary?** The GPS module provides **real-time latitude and longitude data**, which is crucial for autonomous navigation. The vehicle uses this information to determine its position and make navigation decisions. Alternative indoor localization systems (like IR beacons or WiFi triangulation) may not work as reliably outdoors.
- **Operating Voltage:** 3.3V – 5V 
- **Power Consumption:** ~50mA
- **Student Challenge:** _Could you use a different positioning system (e.g., GLONASS, GSM triangulation)? What benefits and limitations would that bring?_

Sure! Here's your corrected and updated version of that section, keeping the original structure and integrating the **BTS7960** motor driver:

---

**3. Motor Driver (BTS7960)**  
*For additional details about motor drivers, check the Motor Driver Guide.*

**Why do we need a motor driver?**  
The ESP32 cannot directly power motors due to low output current and voltage levels. A motor driver (H-Bridge circuit) is required to provide sufficient voltage and current for motor control. The **BTS7960** is a MOSFET-based motor driver capable of handling high current loads, making it more efficient and powerful than traditional ICs like L298N or L293D.

**Power Requirements:**  
- **BTS7960**: 5V logic input, motor voltage 6V – 27V, continuous current up to 43A (with proper heat dissipation)

**Student Challenge:**  
*What if you used L298N or TB6612FNG instead?*  
What are the limitations of traditional H-Bridge ICs compared to high-current MOSFET-based drivers like BTS7960?  
What are the efficiency and thermal management benefits when using a MOSFET-based driver?

---

### **4. Four DC Motors (200 RPM Each)** To know how to operate those motors using motor driver see the previously mentioned Motor driver guide.
The vehicle requires four motors to enable movement in **forward, backward, and turning directions**. The speed and torque of these motors allow precise navigation. Compared to servo or stepper motors, DC motors offer simplicity and higher speed control.
- **Motor Specifications:**
 - **Voltage:** 6V – 12V 
 - **Current:** ~300mA – 600mA per motor (depending on load) 
 - **Power Consumption:** ~5W per motor
- **Student Challenge:** _Could you use geared motors, stepper motors, or brushless DC motors instead? How would that affect performance?_

### **5. Bluetooth Module (Optional if not using ESP32's built-in Bluetooth)**
- **Why include a Bluetooth module?** Bluetooth allows for **real-time monitoring of GPS coordinates and system status** via a mobile device. It's useful during development or for debugging.
- **Power Consumption:** ~30mA
- **Student Challenge:** _What about using WiFi or LoRa instead of Bluetooth? In what situations would each be preferable?_

### **6. Battery Pack (Funfly 1550mAh 4S 100C 14.8V 22.94Wh Li-Po)** For a detailed explanation of Li-Po batteries, watch [Battery Information](https://youtu.be/D98e2lRe2O8?si=R-YbRmi-yAfHtEH4).

- **Why this battery?** This rechargeable **4-cell (4S) Li-Po battery** provides sufficient voltage and current for all components, ensuring stable operation. The 100C rating means it can deliver very high current bursts if needed.
- **What does mAh mean?** Milliamp-hours (mAh) is a measure of electric charge, showing how much current a battery can supply over time. 1550mAh means the battery can supply 1550 milliamps for 1 hour (or 775mA for 2 hours, etc).
- **Estimated Power Consumption Calculation:**
 - **ESP32:** 160mA @ 3.3V → **0.528W**
 - **GPS Module:** 50mA @ 5V → **0.25W**
 - **Motor Driver:** 2A max @ 5V → **10W**
 - **Motors (4x 200 RPM):** 600mA each @ 12V → **28.8W** (4 motors)
 - **Total Estimated Load:** **39.578W**
- **Battery Runtime Calculation:**
 - Battery Energy = 14.8V × 1.55Ah = **22.94Wh**
 - Estimated Runtime = 22.94Wh / 39.578W ≈ **~35 minutes**
- **Explanation of Calculation:**
   - Total power drawn by all components = 39.578W
   - Battery provides 22.94 watt-hours of energy
   - Runtime (in hours) = Total Energy / Power Consumption = 22.94Wh / 39.578W ≈ 0.5796 hours
   - Convert hours to minutes: 0.5796 × 60 ≈ **35 minutes**
- **Student Challenge:** _How would the runtime change if we replaced the battery with a 2200mAh 3S Li-Po or swapped the motors with lower-power ones? Calculate the new runtime._

### **7. Chassis and Wheels**
- **Why do we need a chassis?** The chassis serves as the **structural frame** for mounting electronic components and enabling movement. PVC is lightweight, cost-effective, and easy to modify.
- **Material Used:** **PVC Board**
- **Student Challenge:** _What if you used an acrylic frame or aluminum? How would it impact performance, durability, and weight?_

### **8. HMC5883 Compass Module** For additional details about motor drivers, check the [HMC5883L Sensor Guide](https://github.com/FahimHafiz/NetIoT-Network-IoT-Repository/tree/main/01.%20Arduino/Sensors_Motors/HMC5883L%20Sensor%20(Magnetometer)).
- **Why include a Compass Module?**
  - The compass module provides **heading information**, which is crucial for accurate navigation. The vehicle uses this heading to determine its orientation relative to the target GPS coordinates, allowing for precise turns and course corrections.
  - It allows the vehicle to maintain the correct course even when GPS signals are weak or unavailable.
  - Compared to gyroscopes alone, it gives absolute direction (North-South) rather than just rotation.
  - **Operating Voltage:** 3.3V - 5V
  - **Power Consumption:** ~3mA
- **Student Challenge:** _Can a gyroscope replace a compass? What are the pros and cons of using IMUs (Inertial Measurement Units) instead of a dedicated compass module?_

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
- **Explanation of Calculation:**
   - Total power consumption ≈ 39.578W
   - Battery capacity = 14.8V × 1.55Ah = 22.94Wh
   - Runtime = 22.94Wh ÷ 39.578W = **0.5796 hours** ≈ **35 minutes**
- **Student Challenge:** _If any component is replaced with a different version (e.g., GPS with higher current rating, different battery capacity), how would that affect the total runtime? Calculate the new runtime._

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

### A flowchart is given below to show the workflow of the system

![flowchart](https://github.com/user-attachments/assets/3f2f4ee6-cd8c-4b76-ac5c-7d01d87b3a02)


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

