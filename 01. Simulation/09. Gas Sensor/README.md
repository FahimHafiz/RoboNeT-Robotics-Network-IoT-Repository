# 6-Pin Gas Sensor (MQ-2) with Arduino in Tinkercad

This tutorial guides you through setting up a **6-pin gas sensor** (e.g., MQ-2) with pins **A1, A2, H1, H2, B1, B2** using an **Arduino Uno** in Tinkercad to detect gas concentrations (e.g., LPG, methane, smoke). The sensor’s analog output will be read and displayed in the Serial Monitor, with an LED indicating high gas levels. This is ideal for learning about gas sensing and Arduino programming in a virtual environment.

## Prerequisites

- A Tinkercad account (free at [tinkercad.com](https://www.tinkercad.com)).
- Basic understanding of Arduino programming and the Tinkercad interface.
- No physical hardware is required, as Tinkercad simulates all components.

## 1. Components Needed

- Arduino Uno R3
- 6-pin gas sensor (e.g., MQ-2 with pins A1, A2, H1, H2, B1, B2)
- Breadboard
- Jumper wires
- LED
- 220-ohm resistor (for the LED)

## 2. Pinout for 6-Pin Gas Sensor (MQ-2)

The 6-pin MQ-2 gas sensor has two sets of pins: **A1, A2** (analog output pins) and **H1, H2, B1, B2** (heater and sensing element pins). In Tinkercad’s simulation, the sensor is simplified, but the connections follow the standard MQ-2 configuration. Typically, A1 or A2 provides the analog output, while H1/H2 and B1/B2 are used for the heater circuit, often requiring power and ground connections.

### Gas Sensor to Arduino
| Gas Sensor Pin | Arduino Pin / Connection |
|----------------|--------------------------|
| A1             | Analog pin A0            |
| A2             | Leave unconnected        |
| H1             | Arduino 5V               |
| H2             | Arduino GND              |
| B1             | Arduino 5V               |
| B2             | Arduino GND              |

### LED to Arduino
| LED Pin   | Arduino Pin / Connection |
|-----------|--------------------------|
| Anode     | Digital pin 8            |
| Cathode   | 220-ohm resistor to GND  |

> **Note**: In Tinkercad, the gas sensor’s heater pins (H1, H2, B1, B2) may not all be required, as the simulation simplifies the heater circuit. Connecting H1 and B1 to 5V and H2 and B2 to GND ensures proper operation. A2 is typically redundant for analog output, so A1 is used for reading the sensor value.

## 3. Set Up the Circuit in Tinkercad

### Create a New Circuit
- Log in to Tinkercad and click **Circuits** > **Create new Circuit**.
- Rename the circuit (e.g., "MQ-2 Gas Sensor Detector") by clicking the default name in the top left.

### Add Components
From the components panel (right side), drag the following to the workspace:
- **Arduino Uno R3**
- **Gas Sensor** (search for "gas sensor" or "MQ-2"; Tinkercad’s model may label pins as A1, A2, H1, H2, B1, B2)
- **Breadboard** (small)
- **LED**
- **220-ohm Resistor**
- **Jumper wires**

### Wire the Circuit
1. **Power the Breadboard**:
   - Connect Arduino’s **5V** pin to the red (+) rail on the breadboard (use a red wire).
   - Connect Arduino’s **GND** pin to the blue (-) rail on the breadboard (use a black wire).
2. **Connect the Gas Sensor**:
   - **A1** to Arduino pin **A0** (for analog output).
   - **A2**: Leave unconnected (not used in this setup).
   - **H1** to the breadboard’s red (+) rail (5V).
   - **H2** to the breadboard’s blue (-) rail (GND).
   - **B1** to the breadboard’s red (+) rail (5V).
   - **B2** to the breadboard’s blue (-) rail (GND).
3. **Connect the LED**:
   - **Anode** (longer leg) to Arduino pin **8**.
   - **Cathode** (shorter leg) to a 220-ohm resistor, then connect the resistor to the breadboard’s blue (-) rail (GND).

<img width="763" height="750" alt="image" src="https://github.com/user-attachments/assets/5ce23677-a871-4745-9cd4-f8cc340371c7" />


## 4. Arduino Code

### Open the Code Editor
- Click the **Code** button in Tinkercad’s top right corner.
- Select **Text** mode and click **Continue** if prompted.
- Delete any default code.

### Paste the Code
Copy and paste the following code into the editor:

```cpp
int gasSensorPin = A0; // Analog pin for gas sensor (A1)
int ledPin = 8;        // Digital pin for LED
int gasValue = 0;      // Variable to store gas sensor value

void setup() {
  pinMode(ledPin, OUTPUT);    // Set LED pin as output
  Serial.begin(9600);         // Initialize serial communication
}

void loop() {
  gasValue = analogRead(gasSensorPin); // Read gas sensor value from A1
  float voltage = gasValue * (5.0 / 1023.0); // Convert to voltage

  // Print gas value and voltage to Serial Monitor
  Serial.print("Gas Value: ");
  Serial.print(gasValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Turn on LED if gas value exceeds threshold (e.g., 300)
  if (gasValue > 300) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500); // Wait for 500 milliseconds
}
```

### Code Explanation
- `int gasSensorPin = A0;`: Defines the analog pin (A0) connected to the sensor’s A1 pin for reading gas concentration.
- `int ledPin = 8;`: Defines the digital pin (8) for the LED.
- `Serial.begin(9600);`: Initializes serial communication at 9600 baud rate.
- `gasValue = analogRead(gasSensorPin);`: Reads the analog value (0-1023) from A1.
- `float voltage = gasValue * (5.0 / 1023.0);`: Converts the analog value to a voltage (0-5V) for reference.
- `if (gasValue > 300)`: Lights the LED if the gas value exceeds 300 (adjustable based on Tinkercad’s sensor response).
- `delay(500);`: Pauses for 500ms between readings to stabilize output.

## 5. Simulate and Test

### Start Simulation
- Click **Start Simulation** in Tinkercad’s top right corner.

### Open Serial Monitor
- Click the **Serial Monitor** button at the bottom of the code editor.
- Ensure the baud rate is set to **9600** (matching `Serial.begin(9600);`).

### Test the Gas Sensor
- In Tinkercad, click the gas sensor to open its properties panel. Adjust the simulated gas concentration (e.g., using the slider or input field) to mimic different gas levels (e.g., methane, LPG, smoke).
- Observe the Serial Monitor for gas value and voltage readings.
- When the gas value exceeds 300, the LED should light up; otherwise, it remains off.

### Adjust Threshold
- If the LED triggers too easily or not at all, adjust the threshold value (300) in the code to match the sensor’s simulated range in Tinkercad.

## 6. Troubleshooting

- **No Readings in Serial Monitor**:
  - Verify the baud rate is 9600 in both the code and Serial Monitor.
  - Ensure the A1 pin is connected to Arduino pin A0.
- **LED Not Lighting**:
  - Check that the LED is connected correctly (anode to pin 8, cathode to resistor to GND).
  - Adjust the threshold value (300) if gas values are outside the expected range.
- **Sensor Not Responding**:
  - Confirm all sensor pins are connected as specified (H1, B1 to 5V; H2, B2 to GND; A1 to A0).
  - In Tinkercad, ensure the gas sensor is set to simulate varying gas levels in the properties panel.
- **Unstable Readings**:
  - Increase the `delay(500)` value to slow down readings.
  - Check for loose connections in the Tinkercad workspace.

## 7. Next Steps

- **Add an LCD**: Use a 16x2 LCD to display gas values (refer to the LiquidCrystal library).
- **Add a Buzzer**: Connect a buzzer to alert when gas levels are high.
- **Calibrate the Sensor**: Experiment with threshold values to detect specific gases (e.g., methane, LPG).
- **Save and Share**: Name your Tinkercad project and share the link to showcase your work.

✅ You have successfully set up and simulated a **6-pin gas sensor (MQ-2)** with Arduino in Tinkercad!
