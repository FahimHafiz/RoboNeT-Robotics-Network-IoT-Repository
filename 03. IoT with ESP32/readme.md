# 🌐 IoT with ESP32

This folder offers a structured learning path for ESP32-based IoT projects.  
Starting with ESP32 basics and Wi-Fi setup, it progresses through web servers, sensor integration, and cloud connectivity.  
Modules cover LED control, data logging to databases like MySQL and Firebase, and real-time monitoring.


## ✅ What you’ll learn

- ESP32 fundamentals and common development workflow.
- Connecting ESP32 to Wi‑Fi and building web-based controls.
- Sending/receiving data using HTTP (client/server).
- Displaying sensor readings on a web page.
- Logging data to external services (MySQL, Google Sheets).
- Real-time cloud communication using Firebase Realtime Database.

## 📂 Folder Contents

This section lists the 11 modules in the ESP32 IoT tutorial series.  
Each module provides hands-on projects and code examples for specific IoT concepts.  
Topics range from ESP32 introduction to advanced database and cloud integrations.

- **[What is an ESP32](<./00. What is an ESP32/>)** 
  - Introduction to ESP32 and its role in IoT projects.
  - Arduino IDE setup for ESP32 board support.
  - Running a basic Blink program and verifying the upload/output.

- **[Wifi Configuration](<./01. Wifi Configuration/>)**  
  - Scanning nearby Wi‑Fi networks (SSID discovery).
  - Connecting ESP32 to Wi‑Fi and checking connection status.
  - Working with IP info (local IP, gateway) and reconnection behavior.

- **[Web Server - LED Control from Browser](<./02. Web Server - LED Control from Browser/>)**  
  - Creating a simple HTTP web server on ESP32.
  - Building a browser-based interface to control an LED.
  - Handling routes like ON/OFF endpoints and mapping them to GPIO.

- **[HTTP Client - Website Communication](<./03. HTTP Client - Website Communication/>)**  
  - Using ESP32 as an HTTP client (GET/POST requests).
  - Sending data to a website/API endpoint and reading responses.
  - Basic response handling (status codes + payload).

- **[Sensor Web Display - DHT Temperature and Humidity](<./04. Sensor Web Display - DHT Temperature and Humidity/>)**  
  - Reading temperature and humidity from a DHT sensor.
  - Displaying sensor data on a web dashboard hosted by ESP32.
  - Optional improvements: refresh logic, thresholds, clean formatting.

- **[Multiple Device Control - Relays and Appliances](<./05. Multiple Device Control - Relays and Appliances/>)**  
  - Controlling multiple relay channels using ESP32 GPIO pins.
  - Web interface for controlling multiple appliances independently.
  - Managing device states (ON/OFF) safely and consistently.

- **[Insert Data into MySQL Database using PHP and Arduino IDE](<./06. Insert Data into MySQL Database using PHP and Arduino IDE/>)**  
  - Sending sensor data from ESP32 to a PHP endpoint via HTTP.
  - PHP script inserts received data into a MySQL database table.
  - Verifying inserts and structuring fields (timestamp, values, device id).

- **[Google Sheets via Google Sheets API](<./07. Google Sheets via Google Sheets API/>)**  
  - Sending sensor readings to Google Sheets using the Sheets API.
  - Writing new rows (timestamp + readings) programmatically.
  - Handling common issues like auth, quota, and error responses.

- **[Google Sheets via Apps Script](<./08. Google Sheets via Apps Script/>)**  
  - Using Google Apps Script as a lightweight endpoint for ESP32.
  - Logging data into Google Sheets without direct API calls from ESP32.
  - Optional automation: triggers, formatting, basic notifications.

- **[Getting Started with Firebase (Realtime Database)](<./09. Getting Started with Firebase (Realtime Database)/>)**  
  - Setting up Firebase project and enabling Realtime Database.
  - Writing ESP32 data to Firebase paths (JSON tree structure).
  - Basic understanding of rules/permissions and data organization.

- **[Read From Firebase Database](<./10. Read From Firebase Database/>)**  
  - Reading data/state values from Firebase to control ESP32 behavior.
  - Keeping ESP32 state synced with cloud values (polling/updates).
  - Using cloud-controlled actions (LED/relay control, monitoring states).


## 🧩 How to use

1. Start with: [00. What is an ESP32](<./00. What is an ESP32/>)
2. Then complete Wi‑Fi setup: [01. Wifi Configuration](<./01. Wifi Configuration/>)
3. Move forward step-by-step (Web Server → HTTP Client → Sensor Dashboard → Cloud/Database).

