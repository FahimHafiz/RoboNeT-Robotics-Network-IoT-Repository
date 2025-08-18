# Servo Motor Control with Arduino in TinkerCAD

This tutorial will guide you through controlling a **servo motor** using an **Arduino Uno** in **TinkerCAD**.

---

## 1. Components Needed

- Arduino Uno
- SG90 or similar hobby servo motor
- Breadboard (optional, for neat wiring)
- Jumper wires
- External power supply (optional, for larger servos)

---

## 2. Servo Motor Pinout

A standard hobby servo has **three wires**:

| Servo Wire Color | Function  | Arduino Pin |
|------------------|-----------|-------------|
| Brown / Black    | GND       | GND         |
| Red              | +5V       | 5V          |
| Orange / Yellow  | Signal    | Pin 9       |

> ⚠️ For larger servos (e.g., MG996R), use an **external 5–6V power supply** and connect its GND to the Arduino GND.

---

## 3. Circuit Diagram

**Connections:**

1. Servo **GND** → Arduino **GND**  
2. Servo **VCC** → Arduino **5V** (or external 5V–6V supply)  
3. Servo **Signal** → Arduino **digital pin 9**  

---

## 4. Arduino Code — Sweep Motion

```cpp
#include <Servo.h>

Servo myServo;  // Create servo object

void setup() {
  myServo.attach(9); // Signal pin connected to Arduino pin 9
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos); // Move to position
    delay(15);          // Wait for movement
  }

  // Sweep back from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }
}
```

<img width="1117" height="630" alt="image" src="https://github.com/user-attachments/assets/ac8d0a7b-e2e7-4a5a-bbf6-ad1832b19aed" />


---

## 5. Arduino Code — Move to Specific Angles

```cpp
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {
  myServo.write(0);   // Move to 0 degrees
  delay(1000);

  myServo.write(90);  // Move to 90 degrees
  delay(1000);

  myServo.write(180); // Move to 180 degrees
  delay(1000);
}
```

---

## 6. Running in TinkerCAD

1. Open [TinkerCAD Circuits](https://www.tinkercad.com/circuits).
2. Create a **New Circuit**.
3. Place an **Arduino Uno** and **servo motor**.
4. Connect the servo motor according to the pinout above.
5. Copy and paste the Arduino code into the **Code Editor**.
6. Click **Start Simulation** to see the servo move.

---

## 7. Notes

- **Small servos** like SG90 can be powered directly from Arduino’s 5V pin.
- **Larger servos** require an external supply for stable operation.
- Servo angles are usually **0° to 180°**. For continuous rotation servos, the control method is different (PWM speed control).

---

✅ You have successfully controlled a servo motor in TinkerCAD using Arduino!
