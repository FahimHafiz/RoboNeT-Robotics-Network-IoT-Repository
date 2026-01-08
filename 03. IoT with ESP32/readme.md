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

### What is an ESP32
- Overview of ESP32 features and common IoT use-cases.
- Installing/setting up ESP32 board support in Arduino IDE.
- Running a first program (typically Blink) and verifying upload/serial output.

### Wifi Configuration
- Scanning nearby Wi‑Fi networks (SSID discovery).
- Connecting ESP32 to a Wi‑Fi network (credentials + connection status).
- Working with IP details (local IP, gateway, reconnection strategy).

### Web Server - LED Control from Browser
- Hosting a simple HTTP web server on ESP32.
- Creating a basic web UI (buttons/toggles) to control an LED.
- Handling URL routes (e.g., `/on`, `/off`) and updating GPIO accordingly.

### HTTP Client - Website Communication
- Sending HTTP requests (GET/POST) from ESP32 to a server/API.
- Parsing server responses (status code, payload text/JSON if used).
- Using HTTP client flow for cloud updates, webhooks, or REST APIs.

### Sensor Web Display - DHT Temperature and Humidity
- Reading DHT temperature/humidity values on ESP32.
- Serving sensor data on a local webpage (live values or periodic refresh).
- Adding thresholds/alerts or basic formatting for readability.

### Multiple Device Control - Relays and Appliances
- Controlling multiple relay channels using ESP32 GPIO.
- Building a multi-switch web interface (per-device ON/OFF).
- Basic safety/logic patterns (default OFF, state tracking, fail-safe behavior).

### Insert Data into MySQL Database using PHP and Arduino IDE
- Sending sensor/device data from ESP32 to a PHP endpoint (HTTP request).
- PHP script receiving data and inserting into a MySQL table.
- Defining database schema fields (timestamp, device id, sensor values) and verifying inserts.

### Google Sheets via Google Sheets API
- Authenticating/authorizing requests to Google Sheets API (keys/tokens depending on approach).
- Writing new rows (timestamp + sensor values) into a spreadsheet.
- Handling rate limits/errors and confirming data appears correctly.

### Google Sheets via Apps Script
- Using Apps Script web app (or script endpoint) to receive ESP32 data.
- Writing received values to a Google Sheet without direct API handling on ESP32.
- Optional automation patterns (triggers, formatting, notifications).

### Getting Started with Firebase (Realtime Database)
- Creating a Firebase project and enabling Realtime Database.
- Writing data from ESP32 to database paths (e.g., `/devices/device1/...`).
- Understanding real-time data structure (JSON tree) and basic read/write rules.

### Read From Firebase Database
- Reading values from Firebase paths to control ESP32 behavior.
- Handling asynchronous updates (polling or stream-like update patterns depending on library).
- Using cloud-controlled states (e.g., LED/relay states) and syncing local device state.


## 🧩 How to use

1. Start with: [00. What is an ESP32](<./00. What is an ESP32/>)
2. Then complete Wi‑Fi setup: [01. Wifi Configuration](<./01. Wifi Configuration/>)
3. Move forward step-by-step (Web Server → HTTP Client → Sensor Dashboard → Cloud/Database).

