#  LED Blink Simulation using Tinkercad

## Objective:
To simulate a basic LED blinking circuit using Arduino Uno in Tinkercad Circuits. This experiment introduces the concept of digital output and timing control using the `digitalWrite()` and `delay()` functions.

---

## Components Required (in Tinkercad):
- 1 × **Arduino Uno R3**
- 1 × **LED**
- 1 × **220Ω Resistor**
- 2 × **Jumper Wires**
- 1 × **Breadboard** (optional, for neat circuit design)

---

## Circuit Diagram:
**Connection Overview**:
- **LED anode (long leg)** → Arduino **pin 13** (via resistor)
- **LED cathode (short leg)** → **GND**

### Steps to Build the Circuit:
1. Open Tinkercad and create a **New Circuit**.
2. Drag an **Arduino Uno R3** and place it on the workspace.
3. Add an **LED** and a **220-ohm resistor**.
4. Connect:
   - Resistor → Arduino **pin 13**
   - Other side of resistor → LED **anode**
   - LED cathode → Arduino **GND**

> 💡 You can also directly use **pin 13**, which is connected to the onboard LED.

---

## Arduino Code:
Paste the following code into the **Code** section in **Text Mode**:

```cpp
void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as output
}

void loop() {
  digitalWrite(13, HIGH); // Turn LED on
  delay(1000);            // Wait 1 second
  digitalWrite(13, LOW);  // Turn LED off
  delay(1000);            // Wait 1 second
}
```

---

## How to Run Simulation:
1. Click the **Start Simulation** button in Tinkercad.
2. The LED should **blink ON and OFF every second**.
3. Stop the simulation using the **Stop Simulation** button.

---

## Concepts Learned:
- Using `pinMode()` to configure digital pins
- Writing digital signals with `digitalWrite()`
- Controlling timing using `delay()`

---

## Experiment Variations:
- Change the pin from 13 to any digital pin (e.g., 7) and update the code accordingly.
- Try faster or slower blinking by adjusting the delay time.
- Add multiple LEDs on different pins to blink in sequence.

---

## Conclusion:
This experiment helps beginners understand how digital pins can be used to control external devices like LEDs. Tinkercad provides a risk-free environment to explore and learn the basics of Arduino programming and circuit design.

