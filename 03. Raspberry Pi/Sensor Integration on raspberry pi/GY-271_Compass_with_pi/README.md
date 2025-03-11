# **UNITED INTERNATIONAL UNIVERSITY (UIU)**  
## **Dept. of Computer Science & Engineering**  

## **Experiment: Using the GY-271 (QMC5883L) Magnetometer (Compass) Sensor with Raspberry Pi**  

### **Objective:**  
To connect the **GY-271 (QMC5883L) Magnetometer sensor** to a **Raspberry Pi**, read data using **I2C**, and display **compass headings**.  

---

## **What You Need**  

- **GY-271 Magnetometer Sensor (QMC5883L)**  
- **Raspberry Pi 4B** (or any Raspberry Pi with I2C support) with **Raspberry Pi OS** installed  
- **Jumper Wires**  
- **Breadboard** (optional)  

---

## **Step 1: Enable I2C on Raspberry Pi**  

### **1. Open the terminal and run:**  

```bash
sudo raspi-config
```

### **2. Navigate to:**  
🔹 **Interfacing Options → I2C → Enable**  

![i2c](https://github.com/user-attachments/assets/84fe2e42-a47e-4d90-9164-df12ff61ef37)


### **3. Reboot the Raspberry Pi:**  

```bash
sudo reboot
```

---

## **Step 2: Connect the GY-271 Sensor to Raspberry Pi**  

| **GY-271 Pin** | **Raspberry Pi Pin** |
|--------------|------------------|
| **VCC**      | **3.3V or 5V** *(Use 5V for better performance)* |
| **GND**      | **GND** |
| **SDA**      | **GPIO 2 (Pin 3)** |
| **SCL**      | **GPIO 3 (Pin 5)** |

🔗 **Connect using jumper wires.**  

> **Note:** The GY-271 can operate at **both 3.3V and 5V**, but **5V is recommended** for stable readings.  

---

## **Step 3: Install Required Software and Libraries**  

### **1. Update & Upgrade Your System**  
To avoid compatibility issues, first **update** your Raspberry Pi OS:  

```bash
sudo apt update && sudo apt upgrade -y
```

### **2. Install I2C Tools and Python Dependencies**  

```bash
sudo apt install -y i2c-tools python3-smbus python3-pip python3-venv
```

### **3. Install Required Python Libraries**  

```bash
pip install smbus2
pip install qmc5883l-python
```

🔹 This ensures **I2C communication** and **sensor library support**.

---

## **Step 4: Verify Sensor Connection**  

### **1. Check if I2C is Detected**  

Run the following command:  

```bash
i2cdetect -y 1
```

📌 **Expected Output:**  
A table should appear showing **`0x0D`** (QMC5883L’s default address).  

> **If no address appears:**  
> - Check **wiring** (ensure SDA & SCL are connected properly).  
> - Try using **5V instead of 3.3V** for VCC.  
> - Ensure I2C is enabled (`sudo raspi-config` → **Interfacing Options** → **I2C** → Enable).  

---

## **Step 5: Create Project Folder & Script**  

### **1. Create a Folder for Your Project**  

```bash
mkdir ~/compass_project
cd ~/compass_project
```

### **2. (Optional) Create a Virtual Environment**  

Creating a **virtual environment** helps keep your Python libraries organized:  

```bash
python3 -m venv env
source env/bin/activate
```

### **3. Create the Python Script**  

```bash
nano compass_qmc5883l.py
```

---

## **Step 6: Python Code to Read Compass Data**  

📌 **Copy and paste this complete, error-free code into** `compass_qmc5883l.py`:  

```python
import time
from qmc5883l import QMC5883L

# Initialize the QMC5883L sensor with I2C bus 1
compass = QMC5883L(bus=1)

try:
    while True:
        # Read the compass heading
        heading = compass.get_bearing()

        # Ensure valid data
        if heading is not None:
            print(f"Heading: {heading:.2f}°")
        else:
            print("Warning: Failed to read heading data")

        time.sleep(1)  # Delay to prevent excessive readings

except Exception as e:
    print(f"Error: {e}")

except KeyboardInterrupt:
    print("\nExiting the program.")
```

---

## **Step 7: Run the Program**  

### **1. Activate Virtual Environment (If Created)**  

```bash
source env/bin/activate
```

### **2. Run the Python Script**  

```bash
python3 compass_qmc5883l.py
```

✅ **Expected Output:**  
```
Heading: 125.32°
Heading: 126.15°
Heading: 124.98°
...
```

---

## **Step 8: Calibration for Accurate Readings (Important!)**  

### **Why Calibration is Needed?**  
The sensor **may have magnetic distortions** due to nearby electronics. **Calibration** ensures accuracy.  

### **1. Automatic Calibration (Recommended for Beginners)**  
Modify your script **before the loop**:  

```python
compass.calibrate(count=500)  # Collects 500 samples for calibration
```

This will run a **simple calibration** and adjust the sensor automatically.  

### **2. Manual Calibration (Advanced Users)**  
- Rotate the sensor **in all directions** and collect **min/max values** for **X, Y, and Z axes**.  
- Subtract offsets from sensor readings in your script.  

---

## **🎯 Further Exploration**  

🔹 **Display on OLED/LED:** Connect an **OLED** or **7-segment display** to show the compass heading.  
🔹 **Navigation Project:** Combine **GY-271** with **GPS (NEO-6M)** for **robotics/drone navigation**.  
🔹 **Use Kalman Filtering:** Improve **sensor stability** for **smoother readings**.  

---

# ✅ **Final Checklist (For Beginners)**  
🔲 **Enable I2C in `raspi-config`**  
🔲 **Use `i2cdetect -y 1` to check sensor detection**  
🔲 **Install `python3-smbus` and `qmc5883l-python`**  
🔲 **Ensure `VCC` is connected to `5V` for best performance**  
🔲 **Run script with `python3 compass_qmc5883l.py`**  
🔲 **Perform sensor calibration for accuracy**  

