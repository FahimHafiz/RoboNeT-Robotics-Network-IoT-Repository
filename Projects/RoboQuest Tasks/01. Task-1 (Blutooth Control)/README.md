# **Project: Bluetooth Remote Control for GPS Tracking Car (Using a Bluetooth Serial Terminal App)**

## **1. Problem Statement**

The existing self-driving GPS tracking car operates autonomously based on predefined GPS coordinates. However, there's a need for manual control in situations where autonomous navigation is not suitable or desired. This project aims to implement a Bluetooth-based remote control system, enabling users to control the car's movement via a readily available Bluetooth serial terminal app on a mobile phone.

## **2. Objectives**

- Integrate Bluetooth communication into the existing ESP32 code.
- Develop a method to receive control commands from a Bluetooth serial terminal app.
- Modify motor control logic to respond to Bluetooth commands.
- Use a readily available mobile app to send bluetooth commands.

## **3. Step-by-Step Guide**

### **Step 1: Selecting a Bluetooth Serial Terminal App**

- **Concept:** Bluetooth serial terminal apps allow users to send and receive text data via Bluetooth.
- **Action:** Search for "Bluetooth Serial Terminal" on the Google Play Store. Install a reliable app (e.g., "Bluetooth Terminal" by QWERTY, "Serial Bluetooth Terminal" by Kai Morich).
- **Hint:** Look for apps with good reviews and a simple interface.

### **Step 2: Understanding Bluetooth Communication (ESP32 Side)**

- **Concept:** Bluetooth Serial communication allows data exchange between the ESP32 and a mobile device as if they were connected via a serial cable.
- **Action:** Review the `BluetoothSerial.h` library documentation. Understand how to initialize Bluetooth, receive data, and send data.
- **Hint:** The `SerialBT.available()`, `SerialBT.read()`, and `SerialBT.write()` functions are crucial.

### **Step 3: Receiving Bluetooth Commands**

- **Concept:** Design a simple protocol to represent control commands. For example:
    - 'F' = Forward
    - 'B' = Backward
    - 'L' = Left
    - 'R' = Right
    - 'S' = Stop
- **Action:** Modify the `loop()` function to check for incoming Bluetooth data. If data is available, read it and store it in a variable.
- **Hint:** Use a `switch` statement to handle different commands.

### **Step 4: Motor Control Logic Modification**

- **Concept:** Adapt the existing motor control functions (`forward()`, `backward()`, `leftward()`, `rightward()`, `stopp()`) to be triggered by Bluetooth commands instead of GPS-based calculations.
- **Action:** Create a new section within the `loop()` function to interpret the received Bluetooth commands and call the corresponding motor control functions.
- **Hint:** Temporarily disable the GPS-based navigation logic to prevent conflicts.

### **Step 5: Testing and Debugging**

- **Action:**
    1. Pair your mobile phone with the ESP32's Bluetooth module.
    2. Open the Bluetooth serial terminal app.
    3. Connect to the ESP32.
    4. Send the predefined command characters ('F', 'B', 'L', 'R', 'S').
    5. Verify that the car responds correctly.
- **Hint:** Use `Serial.println()` statements to print the received commands and motor actions for debugging.

## **4. Code Modifications**

Students will need to make the following changes to the existing code:

- **Include Bluetooth Library:**
    - `#include "BluetoothSerial.h"`
- **Initialize Bluetooth Serial:**
    - `BluetoothSerial SerialBT;`
    - `SerialBT.begin("CarControl");`
- **Read Bluetooth Data:**
    - Implement logic to read data from `SerialBT.read()`
- **Interpret Commands:**
    - Use a `switch` statement to interpret received characters.
- **Motor Control Based on Commands:**
    - Call motor control functions based on interpreted commands.
- **Disable GPS Navigation (Temporarily):**
    - Comment out or conditionally disable GPS-based navigation logic.

## **Finally the system workflow will be the following**

<p align="center">
  <img src="https://github.com/user-attachments/assets/014052db-fe17-4b7f-b447-362f1318ee15" alt="diagram" width="500"/>
</p>

## **5. Hints and Considerations**

- **Bluetooth Pairing:** Ensure the mobile device is properly paired with the ESP32's Bluetooth module.
- **Command Protocol:** Keep the command protocol simple for initial testing.
- **Error Handling:** Implement basic error handling for invalid commands.
- **Motor Safety:** Add safeguards to prevent motor damage (e.g., speed limits, sudden stops).
- **App Selection:** Choose a reliable Bluetooth serial terminal app.
- **Testing environment:** test in an open space.
