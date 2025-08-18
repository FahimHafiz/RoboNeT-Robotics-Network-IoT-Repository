# DC Motor Control with Arduino in TinkerCAD

This tutorial will guide you through controlling a simple **DC motor with 2 terminals** using an **Arduino Uno** in **TinkerCAD**.

---

## 1. Components Needed

- Arduino Uno
- NPN Transistor (e.g., 2N2222 or TIP120)
- 1 × 220 Ω resistor
- DC Motor (2 terminals)
- External power supply (optional, for higher speed)
- Diode (e.g., 1N4007) for back-EMF protection
- Breadboard
- Jumper wires

---

## 2. Circuit Diagram

**Connections:**

1. **Motor Terminal 1** → +5V (or external +V)
2. **Motor Terminal 2** → Collector of transistor
3. **Emitter** of transistor → GND
4. **Base** of transistor → Arduino **pin 9** through **220 Ω resistor**
5. **GND of external supply** (if used) → Arduino GND
6. **Diode** across motor terminals, cathode (strip side) to +V

> 💡 The diode protects the circuit from voltage spikes when the motor stops.

<img width="1007" height="618" alt="image" src="https://github.com/user-attachments/assets/e02708f8-2aa9-47b7-85ad-b59df919153b" />

---

## 3. Arduino Code — On/Off Control

```cpp
int motorPin = 9; // Connected to transistor base via resistor

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH); // Motor ON
  delay(2000);                  // Wait 2 seconds
  digitalWrite(motorPin, LOW);  // Motor OFF
  delay(2000);                  // Wait 2 seconds
}
```

---

## 4. Arduino Code — Speed Control with PWM

```cpp
int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Ramp up speed
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(motorPin, speed);
    delay(50);
  }

  // Ramp down speed
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(motorPin, speed);
    delay(50);
  }
}
```

---

## 5. Running in TinkerCAD

1. Open [TinkerCAD Circuits](https://www.tinkercad.com/circuits).
2. Create a **New Circuit**.
3. Place an **Arduino Uno**, **breadboard**, **DC motor**, **NPN transistor**, **diode**, **resistor**, and wires.
4. Connect them according to the diagram above.
5. Copy and paste the Arduino code into the **Code Editor**.
6. Click **Start Simulation** to see the motor run.

---

## 6. Notes

- If the motor spins in the opposite direction, swap the two motor wires.
- Avoid connecting the motor directly to the Arduino pin — it can damage the microcontroller.
- Use external power for more torque and speed, but always share the GND with Arduino.

---

✅ You have successfully controlled a DC motor in TinkerCAD using Arduino!
