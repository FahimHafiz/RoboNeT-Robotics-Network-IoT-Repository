![esp32](https://github.com/user-attachments/assets/1cecad82-7354-42b6-be85-692708303225)


# Experiment: Introduction to ESP32

## Objective: 
This documentation provides a beginner-friendly guide to getting started with ESP32 development. It covers the installation of the Arduino IDE, initial setup for ESP32 boards, and testing with a simple "Blink" program to ensure the setup works correctly. The goal is to empower students to build confidence in using ESP32 for future projects.

---

## ESP32 Setup Guide:
ESP32 Setup Guide Youtube Video: [link](https://www.youtube.com/watch?v=AitCKcyjHuQ)
### Step 1: Installing the ESP32 Board in Arduino IDE
To program the ESP32 using the Arduino IDE, follow these steps:

1. **Open Arduino IDE** (Ensure you have the latest version).
2. **Add ESP32 Board Manager URL:**
   - Open **File** → **Preferences**
   - In the **Additional Board Manager URLs** field, paste the following link:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Click **OK** to save.
3. **Install ESP32 Board:**
   - Open **Tools** → **Board** → **Boards Manager**
   - Search for `esp32`
   - Select **ESP32 by Espressif Systems** and click **Install**
4. **Restart Arduino IDE** to apply the changes.

---

### Step 2: Connecting ESP32 to Your Computer
1. **Connect ESP32 using a USB cable.** Ensure it’s a data cable, not just a charging cable.
2. **Check COM Port:**
   - Go to **Tools** → **Port** and select the detected ESP32 port.
3. **Select the ESP32 Board Model:**
   - Go to **Tools** → **Board**
   - Choose the appropriate ESP32 board model (e.g., **ESP32 Dev Module**).

---

### Step 3: Installing Required Libraries
To work with ESP32, install the required libraries:

- **WiFi Library:** Built-in for ESP32, no need to install separately.
- **ESPAsyncWebServer** (for web applications):
  - Open **Sketch** → **Include Library** → **Manage Libraries**
  - Search for `ESPAsyncWebServer` and install.
- **Adafruit Sensor Libraries** (for sensors like DHT11, BMP280, etc.):
  - Install `Adafruit Unified Sensor` from the Library Manager.

---

### Step 4: Uploading the First Code (Blink)
1. Open Arduino IDE and paste the following code:
   ```cpp
   void setup() {
     pinMode(2, OUTPUT); // Built-in LED on ESP32
   }
   
   void loop() {
     digitalWrite(2, HIGH);
     delay(1000);
     digitalWrite(2, LOW);
     delay(1000);
   }
   ```
2. Click **Upload** and wait for the compilation and flashing process to complete.
3. If you see an error, press and hold the **BOOT** button on ESP32 while uploading.
4. Once uploaded, the built-in LED on GPIO2 should blink every second.

---

## ESP32 Features:
* Dual-Core Processor
* Built-in WiFi and Bluetooth
* Multiple I/O Pins
* Analog and Digital Inputs
* Low Power Consumption
* High Processing Power for IoT Applications

---

## ESP32 Pin Diagram:
<div align="center">
  <img width="750" alt="ESP32 Pin Diagram" src="https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/08/ESP32-DOIT-DEVKIT-V1-Board-Pinout-36-GPIOs-updated.jpg?resize=750%2C538&quality=100&strip=all&ssl=1" />
</div>

This documentation should help beginners set up and start using the ESP32 in their projects efficiently.
