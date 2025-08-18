# Photodiode with Arduino in Tinkercad

This tutorial guides you through setting up a **photodiode** with an **Arduino Uno** in Tinkercad to measure light intensity. The photodiode’s analog output controls the brightness of an LED using PWM, with values displayed in the Serial Monitor. This is ideal for learning about light sensing and analog output control in a virtual environment.

## Prerequisites

- A Tinkercad account (free at [tinkercad.com](https://www.tinkercad.com)).
- Basic understanding of Arduino programming and the Tinkercad interface.
- No physical hardware is required, as Tinkercad simulates all components.

## 1. Components Needed

- **Arduino Uno R3**
- **Photodiode** (light sensor)
- **LED**
- **220-ohm Resistor** (for the LED)
- **Breadboard**
- **Jumper wires**

## 2. Pinout and Circuit Setup

### Photodiode to Arduino

| Photodiode Pin | Arduino Pin / Connection |
| -------------- | ------------------------ |
| Anode (+)      | Analog pin A0            |
| Cathode (-)    | Arduino GND              |

### LED to Arduino

| LED Pin | Arduino Pin / Connection |
| ------- | ------------------------ |
| Anode   | Digital pin 9 (PWM)      |
| Cathode | 220-ohm resistor to GND  |

> **Note**: The photodiode in the image is connected with its anode to A0 and cathode to GND. In Tinkercad, the photodiode may be simulated as a light-dependent resistor (LDR) or similar sensor; adjust the connections based on the component’s pin labels in the Tinkercad library.

## 3. Set Up the Circuit in Tinkercad

### Create a New Circuit

- Log in to Tinkercad and click **Circuits** > **Create new Circuit**.
- Rename the circuit (e.g., "Photodiode Light Sensor") by clicking the default name in the top left.

### Add Components

From the components panel (right side), drag the following to the workspace:

- **Arduino Uno R3**
- **Photodiode** (search for "photodiode" or "light sensor"; Tinkercad may use an LDR as a substitute)
- **LED**
- **220-ohm Resistor**
- **Breadboard** (small)
- **Jumper wires**

### Wire the Circuit

1. **Power the Breadboard**:
   - Connect Arduino’s **5V** pin to the red (+) rail on the breadboard (use a red wire).
   - Connect Arduino’s **GND** pin to the blue (-) rail on the breadboard (use a black wire).
2. **Connect the Photodiode**:
   - **Anode (+)** to Arduino pin **A0**.
   - **Cathode (-)** to the breadboard’s blue (-) rail (GND).
3. **Connect the LED**:
   - **Anode** (longer leg) to Arduino pin **9** (PWM-capable).
   - **Cathode** (shorter leg) to a 220-ohm resistor, then connect the resistor to the breadboard’s blue (-) rail (GND).

<img width="1025" height="679" alt="image" src="https://github.com/user-attachments/assets/3457af60-3ef7-4f27-862c-1b98f15c0baf" />

> **Note**: The provided image shows the circuit with a photodiode connected to A0, an LED on pin 9 with a resistor to GND, and a switch (not used in the code). In Tinkercad, you can simulate light changes by adjusting the photodiode’s properties or using an LDR with a light source component.

## 4. Arduino Code

### Open the Code Editor

- Click the **Code** button in Tinkercad’s top right corner.
- Select **Text** mode and click **Continue** if prompted.
- Delete any default code.

### Paste the Code

Copy and paste the following code into the editor:

```cpp
int sensorValue = 0;
int outputValue = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the analog input value from the photodiode
  sensorValue = analogRead(A0);
  // Map the sensor value to PWM range (0-255) for LED brightness
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // Write the output value to the LED
  analogWrite(9, outputValue);
  // Print the results to the Serial Monitor
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  // Wait 2 milliseconds for the analog-to-digital converter to settle
  delay(2); // Wait for 2 millisecond(s)
}
```

### Code Explanation

- `int sensorValue = 0;`: Stores the analog reading from the photodiode (0-1023).
- `int outputValue = 0;`: Stores the mapped PWM value (0-255) for the LED.
- `pinMode(A0, INPUT);`: Configures A0 as an input to read the photodiode.
- `pinMode(9, OUTPUT);`: Configures pin 9 as an output for PWM control of the LED.
- `Serial.begin(9600);`: Initializes serial communication at 9600 baud rate.
- `sensorValue = analogRead(A0);`: Reads the light intensity from the photodiode.
- `outputValue = map(sensorValue, 0, 1023, 0, 255);`: Maps the 0-1023 range to 0-255 for PWM.
- `analogWrite(9, outputValue);`: Sets the LED brightness based on light intensity.
- `Serial.print("sensor = "); Serial.println(sensorValue);`: Displays the sensor value in the Serial Monitor.
- `delay(2);`: Pauses for 2ms to allow the analog-to-digital converter to stabilize.

## 5. Simulate and Test

### Start Simulation

- Click **Start Simulation** in Tinkercad’s top right corner.

### Open Serial Monitor

- Click the **Serial Monitor** button at the bottom of the code editor.
- Ensure the baud rate is set to **9600** (matching `Serial.begin(9600);`).

### Test the Photodiode

- In Tinkercad, adjust the light level by interacting with the photodiode properties (e.g., using a light source component or slider if available).
- Observe the Serial Monitor for changing sensor values (0-1023).
- The LED brightness should vary inversely with light intensity (brighter light = lower sensor value = dimmer LED).

### Adjust Sensitivity

- If the LED response is too sensitive or insufficient, modify the `map()` function parameters (e.g., `map(sensorValue, 0, 1023, 0, 255)`) to adjust the range.

## 6. Troubleshooting

- **No Readings in Serial Monitor**:
  - Verify the baud rate is 9600 in both the code and Serial Monitor.
  - Ensure the photodiode’s anode is connected to A0 and cathode to GND.
- **LED Not Lighting**:
  - Check that the LED is connected correctly (anode to pin 9, cathode to resistor to GND).
  - Confirm pin 9 is used (a PWM pin) and the code is uploaded.
- **Unstable Readings**:
  - Increase the `delay(2)` value to slow down readings.
  - Check for loose connections in the Tinkercad workspace.
- **No Light Response**:
  - Ensure the photodiode properties in Tinkercad are set to simulate varying light levels.

## 7. Next Steps

- **Add a Display**: Use a 16x2 LCD to show sensor values (refer to the LiquidCrystal library).
- **Add a Buzzer**: Trigger a buzzer based on light thresholds.
- **Calibrate the Sensor**: Adjust the `map()` function for specific light conditions.
- **Save and Share**: Name your Tinkercad project and share the link to showcase your work.

✅ You have successfully set up and simulated a **photodiode** with Arduino in Tinkercad!
