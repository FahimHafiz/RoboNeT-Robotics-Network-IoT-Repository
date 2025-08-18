# Bipolar Stepper Motor Control with Arduino (A4988 Driver)

This tutorial guides you through controlling a **bipolar stepper motor** with pins **A+, A-, B+, B-** using an **Arduino Uno** and an **A4988 stepper driver** in the **Circuit Designer IDE**.

## 1. Components Needed

- **Arduino Uno**
- **Bipolar stepper motor** (e.g., NEMA 17) with 4 wires:
  - A+, A− (Coil A)
  - B+, B− (Coil B)
- **A4988 stepper motor driver**
- **External motor power supply** (e.g., 12V for NEMA 17)
- **Breadboard** & jumper wires
- **100 µF electrolytic capacitor**

## 2. Set Up the Circuit in Circuit Designer IDE

### Create a New Project

- Open **Circuit Designer IDE** and create a new project for your circuit.

### Add Components

From the component library in Circuit Designer IDE, add the following:
- **Arduino Uno**
- **Bipolar stepper motor** (ensure it has A+, A-, B+, B- pins, e.g., NEMA 17)
- **A4988 stepper motor driver**
- **Power supply** (set to 12V for motor)
- **Breadboard** (optional for organization)
- **Jumper wires**
- **100 µF electrolytic capacitor**

### Wire the Circuit

Connect the components as follows:

#### Motor to A4988
| Motor Pin | A4988 Pin |
|-----------|-----------|
| A+        | 1A        |
| A−        | 1B        |
| B+        | 2A        |
| B−        | 2B        |

#### A4988 to Arduino
| A4988 Pin     | Arduino Pin / Connection |
|---------------|--------------------------|
| VMOT          | Motor power + (e.g., 12V)|
| GND (VMOT)    | Motor power GND          |
| VDD           | Arduino 5V               |
| GND (VDD)     | Arduino GND              |
| STEP          | Pin 3                    |
| DIR           | Pin 4                    |
| EN (optional) | Arduino GND (always on)  |

> **⚠️ Warning**: Always connect the 100 µF capacitor across **VMOT** and **GND** (close to the driver) to protect against voltage spikes.

![Circuit Diagram](https://github.com/user-attachments/assets/1a7691ee-f832-4bea-bd50-8614107f8333)

## 3. Arduino Code — Basic Rotation

In Circuit Designer IDE, open the code editor for the Arduino Uno and paste the following code:

```cpp
#define dirPin 4
#define stepPin 3
#define stepsPerRevolution 200 // Typical NEMA 17 value

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // Clockwise
  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  }
  delay(1000);

  // Counterclockwise
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  }
  delay(1000);
}
```

## 4. Running the Simulation

1. Connect the motor to the A4988 as shown in the **Motor to A4988** table.
2. Connect the A4988 to the Arduino and power supply in Circuit Designer IDE.
3. Attach the 100 µF capacitor between **VMOT** and **GND** on the A4988.
4. Upload the Arduino code in the Circuit Designer IDE code editor.
5. Power the motor using the **external power supply** (not from Arduino’s 5V pin).
6. Run the simulation in Circuit Designer IDE to watch the motor rotate forward, then backward.

## 5. Notes

- If the motor vibrates but doesn’t rotate, swap either **A+ ↔ A−** or **B+ ↔ B−** in the circuit.
- Change `delayMicroseconds(800)` to adjust speed — smaller delay = faster speed.
- Adjust `stepsPerRevolution` according to your motor's datasheet.
- For smoother motion, enable **microstepping** by wiring MS1, MS2, MS3 pins on the A4988 (consult the driver’s documentation).
- Verify all connections in Circuit Designer IDE’s schematic view to ensure accuracy.

## Troubleshooting

- **Motor Not Moving**:
  - Check all connections, ensure the **external power supply** is active, and confirm the correct pin assignments in the code.
- **Simulation Errors**:
  - Ensure the Circuit Designer IDE project is properly configured with the correct components and no loose connections.
- **Incorrect Rotation**:
  - Verify the motor coil connections (A+, A-, B+, B-) match the A4988 pinout.

## Next Steps

- **Add Sensors**: Integrate a sensor (e.g., limit switch) to control motor movement.
- **Use Libraries**: Explore the **AccelStepper** library for advanced motor control.
- **Save and Share**: Export your Circuit Designer IDE project and share it for collaboration.

✅ You have successfully controlled a **bipolar stepper motor** with Arduino using the **A4988 driver** in Circuit Designer IDE!
