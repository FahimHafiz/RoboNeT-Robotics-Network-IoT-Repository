# I2C (Inter-Integrated Circuit) Communication

## 1. Introduction
I2C (Inter-Integrated Circuit) is a synchronous, multi-device serial communication protocol used to connect multiple sensors and peripherals with a microcontroller using only two wires. It is widely used in embedded systems, Arduino, Raspberry Pi, and ESP32 for sensor interfacing, LCDs, EEPROMs, and more.

---

## 2. How I2C Works
I2C uses two main lines:
- **SDA (Serial Data Line)**: Transfers data between devices.
- **SCL (Serial Clock Line)**: Synchronizes the data transfer.

### Communication Process:
1. The **Master** device (e.g., Arduino) initiates communication.
2. The **Slave** device (e.g., sensor) acknowledges and responds.
3. Data is transmitted in **packets**, consisting of:
   - **Start Condition**: Master sends a signal to start communication.
   - **Address Frame**: 7-bit or 10-bit address identifying the slave.
   - **Read/Write Bit**: Specifies read (1) or write (0) operation.
   - **Data Frames**: 8-bit data followed by an acknowledgment.
   - **Stop Condition**: Signals the end of communication.

### Multiple Devices on I2C Bus
I2C supports multiple devices using unique addresses, allowing up to 127 devices on the same bus.

---

## 3. Connecting I2C Devices
### Common Wiring for I2C Devices
| Arduino Pin | I2C Device Pin |
|------------|---------------|
| A4 (SDA)   | SDA           |
| A5 (SCL)   | SCL           |
| 5V         | VCC           |
| GND        | GND           |

> *Note: Some boards (ESP32, STM32) use different SDA and SCL pins.*

### Pull-up Resistors
I2C requires **pull-up resistors** (typically 4.7kΩ) on the SDA and SCL lines to function correctly.

---

## 4. Example Code (Arduino I2C Communication)
### Scanning I2C Devices
```cpp
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Scanning...");
}

void loop() {
  byte error, address;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C Device Found at Address 0x");
      Serial.println(address, HEX);
    }
  }
  delay(5000);
}
```

### Sending and Receiving Data via I2C
**Master Code (Arduino)**
```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(8); // Address of slave
  Wire.write("Hello");
  Wire.endTransmission();
  delay(1000);
}
```

**Slave Code (Arduino)**
```cpp
#include <Wire.h>

void setup() {
  Wire.begin(8); // Slave address
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}
```

---

## 5. Applications of I2C
- Connecting multiple sensors (e.g., temperature, accelerometers, gyroscopes).
- LCD and OLED displays.
- EEPROM storage.
- Real-time clocks (RTC).
- Interfacing microcontrollers with peripherals.

---

## 6. Troubleshooting I2C Issues
| Issue | Solution |
|-------|----------|
| No device detected | Check wiring and pull-up resistors. |
| Data corruption | Ensure correct baud rate and device address. |
| Bus freezing | Reset communication by re-initializing Wire.begin(). |
| Multiple devices conflict | Verify unique addresses for each device. |

---

## 7. Advantages & Disadvantages of I2C
### **Advantages:**
✅ Supports multiple devices on a single bus.
✅ Requires only two wires.
✅ Synchronization with clock signal ensures reliable data transfer.

### **Disadvantages:**
❌ Slower compared to SPI (100kHz – 3.4MHz).
❌ More complex than UART due to addressing system.
❌ Pull-up resistors required.

---

## 8. Conclusion
I2C is a powerful and efficient communication protocol for connecting multiple devices using only two wires. Understanding its working principles, addressing system, and troubleshooting methods allows for seamless integration of sensors and peripherals into Arduino projects.

Now, you have a complete understanding of **I2C Communication**! 

