## Project: GPS Destination Input and Bluetooth Transmission - Detailed Implementation Guide

### 1. Problem Statement:

Upgrade the ESP32-based GPS tracker car by allowing users to **input destination coordinates via Bluetooth**. The ESP32 should receive these coordinates and confirm successful reception, enabling evaluation or storage for future tasks.

---

### 2. Objectives:

* **Bluetooth-Based Coordinate Input:** Allow users to send GPS destination coordinates (latitude and longitude) via a Bluetooth terminal app.
* **Coordinate Parsing and Storage:** Receive, parse, and store the coordinates in the ESP32 for internal use.
* **Confirmation Message:** Send a clear acknowledgment back to the user confirming receipt and correctness of the coordinates.

---

### 3. Step-by-Step Solution:

#### Step 1: Enable Bluetooth Communication on ESP32

* **Detailed Action:**
  * Initialize Bluetooth using the `BluetoothSerial` library.
  * Assign a recognizable device name like `"GPS_Car_Input"` for easy pairing.
  * Continuously listen for incoming strings using `SerialBT.readStringUntil('\n')`.

* **Hints:**
  * Pair ESP32 with a mobile or computer using system Bluetooth settings.
  * Use apps like **Serial Bluetooth Terminal** (Android) or **TeraTerm/Putty** (Windows).

---

#### Step 2: Coordinate Format and Parsing

* **Detailed Action:**
  * Define a command format such as: `DEST:23.7812,90.4006`
  * In the ESP32 code:
    * Check if the received message starts with `"DEST:"`
    * Extract the substring containing latitude and longitude.
    * Split the string at the comma and convert both parts to `float`.

* **Hints:**
  * Use `indexOf()`, `substring()`, and `toFloat()` to extract values.
  * Validate ranges: latitude (−90 to +90), longitude (−180 to +180).

---

#### Step 3: Send Confirmation Back to User

* **Detailed Action:**
  * After successful parsing, send a message like:
    ```
    Destination Received:
    Latitude: 23.7812
    Longitude: 90.4006
    ```
  * If parsing fails, send an error message like:
    ```
    Invalid format. Use DEST:lat,lon
    ```

* **Hints:**
  * Keep messages clear and user-friendly.
  * Use `SerialBT.println()` for each line.

---

### 4. System Workflow Diagram

This diagram provides a visual overview of how the Bluetooth-based coordinate input works:



---
