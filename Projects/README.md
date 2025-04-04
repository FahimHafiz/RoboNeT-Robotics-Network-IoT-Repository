
# 🚗 ESP32-Based GPS-Guided Smart Car with Bluetooth Control

## 📌 Project Overview

This project demonstrates a **GPS-guided autonomous car** built using the **ESP32 microcontroller**, with additional support for **Bluetooth-based manual control**, real-time **GPS coordinate tracking**, and **interactive mapping using Google Maps**. It serves as an educational and practical implementation of embedded systems, navigation algorithms, and wireless communication.

---

## 🎯 Objectives & Capabilities

This project has been designed to achieve the following goals:

### ✅ Core Functionalities
- **Autonomous Navigation**: The car uses GPS coordinates to navigate through pre-defined waypoints.
- **Real-time Location Tracking**: Continuously calculates and updates the car’s position using latitude and longitude.
- **Directional Control with Compass**: Adjusts heading direction based on magnetometer (compass) readings for accurate path alignment.

### 📱 Bluetooth Integration
- **Manual Remote Control**: Send commands (`F`, `B`, `L`, `R`, `S`) via Bluetooth to manually control the car’s motion.
- **Coordinate Broadcasting**: Retrieve the car’s current location through Bluetooth on request.
- **Path Programming via Bluetooth**: Send custom coordinate paths to the car remotely, allowing it to traverse user-defined routes.

### 🗺️ Mapping & Visualization
- **Coordinate Logging**: GPS data can be logged and exported for visualization.
- **Google Maps Integration**: Coordinates can be plotted on Google Maps to trace the exact route taken or planned.

---

## 🔍 Why This Project Matters

This project is not only functional but also educational. It brings together multiple disciplines within electronics and computer science:

- 📡 **Embedded Systems**: Demonstrates peripheral integration on the ESP32 including UART, PWM, I2C.
- 🧭 **Sensor Fusion**: Combines GPS and compass data for intelligent navigation.
- 📶 **Wireless Communication**: Uses Bluetooth to bridge human interaction and machine control.
- 🗺️ **Geospatial Processing**: Applies trigonometry and geodesic calculations to determine distance and heading between GPS points.

---

## 💡 Educational Benefits

This project is ideal for students, makers, and hobbyists who want to learn:

- How to build GPS-enabled devices with ESP32.
- How to read and parse GPS data using `TinyGPS++`.
- How to interface a digital compass (HMC5883L) via I2C.
- How to generate precise motor control using PWM.
- How to send and receive commands over Bluetooth using `BluetoothSerial`.
- How to convert GPS logs into usable paths on Google Maps.

---
