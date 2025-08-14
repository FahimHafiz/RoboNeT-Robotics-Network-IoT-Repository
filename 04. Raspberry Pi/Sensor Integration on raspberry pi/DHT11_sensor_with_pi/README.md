# **UNITED INTERNATIONAL UNIVERSITY (UIU)**
## **Dept. of Computer Science & Engineering**
## **Experiment: Sensor Integration with Raspberry Pi - Reading Data from a DHT11 Sensor**

### **Objective**  
To demonstrate how to connect a **DHT11 temperature and humidity sensor** to a **Raspberry Pi** and use **Python** to read and display sensor data on the terminal.

---

## **Step 1: Gather Required Components**
- **Raspberry Pi** (Any model, e.g., Raspberry Pi 4B)
- **DHT11 Temperature and Humidity Sensor** [See details](https://nerdshed.com.ng/product/dht11-temperature-humidity-sensor-module/)
- **10kΩ Resistor** *(optional, for stable data readings)* [See more](https://www.ic-components.com/blog/understanding-10k-ohm-resistor-color-code-and-application.jsp)
- **Jumper Wires** [Link](https://images.app.goo.gl/XiQQWwA9xu7B6DGs5)
- **Breadboard** *(optional for easy connections)*

---

## **Step 2: Connect the DHT11 Sensor to the Raspberry Pi**

### **Pin Connections**
| **DHT11 Pin** | **Connection**    | **Raspberry Pi Pin** |
|--------------|-----------------|------------------|
| **VCC**      | 3.3V Power       | Pin 1           |
| **GND**      | Ground           | Pin 6           |
| **DATA**     | GPIO4 (Data)      | Pin 7           |

### **Wiring Instructions**
1. **Connect the VCC pin** of the DHT11 to **Pin 1 (3.3V)** on the Raspberry Pi.
2. **Connect the GND pin** of the DHT11 to **Pin 6 (GND)**.
3. **Connect the DATA pin** of the DHT11 to **GPIO4 (Pin 7)** on the Raspberry Pi.
4. **Use a 10kΩ pull-up resistor** between **VCC and DATA** pins to ensure stable readings.

---

## **Step 3: Update & Install Required Libraries**

### **Update Raspberry Pi Packages**
Before installing dependencies, update your system:

```bash
sudo apt update && sudo apt upgrade -y
```

### **Install Required Python Libraries**
```bash
sudo apt install python3-libgpiod -y
pip install Adafruit_DHT
```

> **Note:** If `pip` is not installed, install it using:
```bash
sudo apt install python3-pip -y
```

---

## **Step 4: Create a Project Folder**
To organize your files, create a new project folder:

```bash
mkdir -p ~/dht11_project
cd ~/dht11_project
```

---

## **Step 5: Create the Python Script**
Create a Python script file to read data from the DHT11 sensor.

```bash
nano read_dht11.py
```

---

## **Step 6: Write the Python Code**
Copy and paste the following **error-free** Python code into `read_dht11.py`:

```python
import Adafruit_DHT
import time  

# Define sensor type and GPIO pin
SENSOR = Adafruit_DHT.DHT11
GPIO_PIN = 4  # GPIO4 (Pin 7)

try:
    while True:
        # Read temperature and humidity from the DHT11 sensor with retries
        humidity, temperature = Adafruit_DHT.read_retry(SENSOR, GPIO_PIN)

        # Check if reading was successful
        if humidity is not None and temperature is not None:
            print(f"Temperature: {temperature:.1f}°C  Humidity: {humidity:.1f}%")
        else:
            print("Failed to retrieve data from sensor. Retrying...")

        time.sleep(2)  # 2-second delay for stable readings

except KeyboardInterrupt:
    print("\nProgram stopped by user.")
```

---

## **Step 7: Run the Program**
1. **Save the file** (`Ctrl + X`, then `Y`, then `Enter`).
2. **Run the script** using:

```bash
python3 read_dht11.py
```

---

## **Step 8: Expected Output**
If everything is set up correctly, the terminal should display:

```
Temperature: 25.2°C  Humidity: 55.3%
Temperature: 25.3°C  Humidity: 55.4%
...
```

---

## **Step 9: Troubleshooting**
If you encounter **issues**, check the following:
✅ **Wiring is correct** (Check pin numbers).  
✅ **Ensure Python and dependencies are installed correctly**.  
✅ **Check sensor stability** (Try adding/removing the **10kΩ resistor**).  
✅ **Reboot the Raspberry Pi** and retry running the script.  

> **If you still get errors**, run:
```bash
pip install --upgrade Adafruit_DHT
```

---
