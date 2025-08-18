# Soil Moisture Sensor in TinkerCAD
## Building a Soil Moisture Detection System in Tinkercad

This project guides you through setting up an Arduino Uno with a soil moisture sensor in Tinkercad to measure soil moisture levels and control indicator LEDs based on the readings. The results will be displayed in Tinkercad's Serial Monitor.

### 1. Getting Started with Tinkercad Circuits

Tinkercad Circuits is a web-based simulator for building and testing electronic circuits, including Arduino-based projects.

- **Access Tinkercad**: Navigate to [www.tinkercad.com](https://www.tinkercad.com) and log in.
- **Create a New Circuit**: From the main Tinkercad page, click on "Circuits" in the left-hand menu, then select "Create new Circuit".
- **Rename Your Circuit**: Tinkercad assigns random names to new circuits. Click on the generated name in the upper left corner and rename it (e.g., "Soil Moisture Detector").

**Basic Navigation**:
- **Zoom and Pan**: Use the scroll wheel to zoom in and out, and click and drag a blank area to pan across the screen.
- **Rotate**: Select a component and click the rotate tool (top left) to rotate it.
- **Delete/Undo/Redo**: Use the delete button to remove components, or the undo/redo buttons for corrections.

### 2. Adding Components to Your Workplane

Drag and drop components from the right-side menu onto your editing area.

- **Arduino Uno R3**: In the component selector (right scroll box), search for "Arduino Uno R3". Click on it and place it in the workspace. The Arduino Uno R3 is a versatile development board with ATmega328P and ATmega16U2 processors, ideal for learning electronics and coding.
- **Breadboard**: Search for "breadboard" and place a "Breadboard Small" next to the Arduino Uno. Breadboards are plastic boards with holes for connecting components without soldering.
- **Soil Moisture Sensor**: Search for "soil moisture" and select the "Soil Moisture Sensor". Drag and drop it onto your workplane.
- **LEDs**: Search for "LED" and place five LEDs (for pins 8, 9, 10, 11, and 12) on the breadboard. LEDs will indicate different moisture levels.
- **Resistors**: Search for "resistor" and place a 220-ohm resistor for each LED to limit current and protect them.

### 3. Wiring the Circuit

Correct electrical connections are essential for the circuit to function.

**Powering the Breadboard**:
- Connect the Arduino’s "5V" pin (bottom row, next to "GND") to the red (+) rail on the breadboard using a red wire.
- Connect any "GND" pin on the Arduino (e.g., next to 5V) to the blue or black (-) rail on the breadboard using a black wire.
- **Note**: The (+) and (-) rails are connected vertically. The middle rows (a-e and f-j) are connected horizontally in sets of five holes, with a gap in the middle.

**Connecting the Soil Moisture Sensor**:
- **VCC pin**: Connect to the red (+) rail on the breadboard (5V).
- **GND pin**: Connect to the blue or black (-) rail on the breadboard (GND).
- **AOUT pin**: Connect to Analog Pin A1 on the Arduino for reading moisture data.
- **Power Control**: Connect the VCC pin of the sensor to Analog Pin A0 on the Arduino (used to control power to the sensor).

**Connecting the LEDs**:
- For each LED (connected to pins 8, 9, 10, 11, and 12):
  - Connect the anode (longer leg) to the corresponding digital pin (8, 9, 10, 11, or 12) on the Arduino.
  - Connect the cathode (shorter leg) to a 220-ohm resistor, then connect the other end of the resistor to the blue or black (-) rail (GND).
- Ensure each LED is oriented correctly (anode to Arduino pin, cathode to resistor).

<img width="730" height="748" alt="image" src="https://github.com/user-attachments/assets/8f099db2-ac11-4a21-aa68-1e4110ba978a" />

### 4. Coding the Arduino

The Arduino is programmed using a C++-based language.

- **Open the Code Editor**: Click the "Code" button in the upper right corner of the Tinkercad interface. Select "Text" mode and press "Continue" if prompted.
- **Delete Existing Code**: Highlight and delete any default code.
- **Enter the Code**: Copy and paste the following code into the editor:

```cpp
int moisture = 0;

void setup() {
  pinMode(A0, OUTPUT); // Power control for sensor
  pinMode(A1, INPUT);  // Analog input for moisture reading
  Serial.begin(9600);  // Initialize serial communication
  pinMode(8, OUTPUT);  // LED for moisture > 800
  pinMode(9, OUTPUT);  // LED for moisture 600-799
  pinMode(10, OUTPUT); // LED for moisture 400-599
  pinMode(11, OUTPUT); // LED for moisture 200-399
  pinMode(12, OUTPUT); // LED for moisture < 200
}

void loop() {
  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A1); // Read moisture value
  // Turn off the sensor to reduce metal corrosion
  digitalWrite(A0, LOW);
  
  Serial.println(moisture); // Print moisture value to Serial Monitor
  
  // Turn off all LEDs
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
  // Light up LEDs based on moisture levels
  if (moisture < 200) {
    digitalWrite(12, HIGH); // Very dry
  } else if (moisture < 400) {
    digitalWrite(11, HIGH); // Dry
  } else if (moisture < 600) {
    digitalWrite(10, HIGH); // Moderately moist
  } else if (moisture < 800) {
    digitalWrite(9, HIGH);  // Moist
  } else {
    digitalWrite(8, HIGH);  // Very moist
  }
  
  delay(100); // Wait for 100 millisecond(s)
}
```

**Code Explanation**:
- `int moisture = 0;`: Declares a variable to store the moisture reading.
- `void setup()`: Runs once at startup to configure pins:
  - `pinMode(A0, OUTPUT)`: Sets A0 as output to control sensor power.
  - `pinMode(A1, INPUT)`: Sets A1 as input to read moisture data.
  - `Serial.begin(9600)`: Initializes serial communication at 9600 baud rate.
  - `pinMode(8 to 12, OUTPUT)`: Configures digital pins 8-12 for LED outputs.
- `void loop()`: Runs repeatedly:
  - Powers the sensor using `digitalWrite(A0, HIGH)`, waits 10ms, reads the moisture value from A1, then powers off the sensor to reduce corrosion.
  - Prints the moisture value to the Serial Monitor.
  - Turns off all LEDs to reset them.
  - Uses a series of `if-else` statements to light one LED based on moisture level thresholds:
    - `< 200`: Very dry (pin 12 LED).
    - `200-399`: Dry (pin 11 LED).
    - `400-599`: Moderately moist (pin 10 LED).
    - `600-799`: Moist (pin 9 LED).
    - `>= 800`: Very moist (pin 8 LED).
  - `delay(100)`: Pauses for 100ms between readings.

### 5. Simulating Your Circuit

After wiring and coding, run the simulation.

- **Start Simulation**: Click the "Start Simulation" button in the top right of the Tinkercad toolbar.
- **Observe Results**:
  - The virtual USB cable connects to the Arduino, providing power.
  - Open the "Serial Monitor" (bottom left of the code editor) to view moisture readings.
  - In Tinkercad, adjust the soil moisture sensor’s simulated moisture level (e.g., by sliding the moisture value in the component’s settings) to observe changes in the Serial Monitor and LED states.
- **Stop Simulation**: Click the "Stop Simulation" button when finished.

### Important Considerations

- **Breadboard Connections**: Power rails are connected vertically; middle rows (a-e and f-j) are connected horizontally in sets of five holes. Double-check connections to avoid errors.
- **LED Polarity**: Ensure LEDs are connected correctly (anode to Arduino pin, cathode to resistor to GND).
- **Troubleshooting**: If the circuit doesn’t work, verify all connections, ensure wires are fully inserted, and check that the code matches the pin assignments.
- **Serial Monitor Baud Rate**: The code’s `Serial.begin(9600)` must match the Serial Monitor’s baud rate (Tinkercad handles this automatically).

By following these steps, you can successfully build and simulate a soil moisture detection system in Tinkercad.
