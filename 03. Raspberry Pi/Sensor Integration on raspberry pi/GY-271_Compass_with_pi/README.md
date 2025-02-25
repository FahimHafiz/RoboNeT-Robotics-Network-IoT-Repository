# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Using the GY-271 (QMC5883L) Magnetometer (Compass) Sensor with Raspberry Pi

**Objective:** To connect the GY-271 sensor to Raspberry Pi, read data using I2C, and display direction (compass headings).

**What You Need**

* GY-271 Magnetometer Sensor (QMC5883L)
* Raspberry Pi 4B with Raspbian OS installed
* Jumper Wires
* Breadboard (optional)

**Step 1: Enable I2C on Raspberry Pi**

1. Open the terminal and run:

   ```bash
   sudo raspi-config
   ```

2. Navigate to:

   `Interfacing Options → I2C → Enable`

   ![gy271_1](https://github.com/user-attachments/assets/128f15b4-d1b3-43ec-a5cd-884eef9dc30f)


4. Reboot the Raspberry Pi:

   ```bash
   sudo reboot
   ```

**Step 2: Connect the GY-271 Sensor to Raspberry Pi**

| GY-271 Pin | Raspberry Pi Pin |
| --------- | ---------------- |
| VCC       | 3.3V or 5V       |
| GND       | GND              |
| SDA       | GPIO 2 (Pin 3)   |
| SCL       | GPIO 3 (Pin 5)   |

Connect using jumper wires.

![raspberry-pi-4-40-pin-description-](https://github.com/user-attachments/assets/16df3eda-a5f1-488e-a807-6717e53d533c)


**Step 3: Create Project Folder and Files**

1. Create a folder for your project:

   ```bash
   mkdir ~/compass_project
   cd ~/compass_project
   ```

2. Create the Python script:

   ```bash
   nano compass_qmc5883l.py
   ```

**Step 4: Setup Virtual Environment (Optional)**

Create a virtual environment (optional but recommended):

```bash
python3 -m venv env
source env/bin/activate
```

**Step 5: Install I2C Tools and Python Libraries**

```bash
sudo apt-get install -y i2c-tools
pip install smbus2
```

Install the `qmc5883L` library:

```bash
pip install qmc5883l
```

**Step 6: Verify Sensor Connection**

Run the following command to scan for the sensor:

```bash
i2cdetect -y 1
```

You should see the address `0x0D` (for QMC5883L) or possibly `0x1E` if it's configured in HMC5883L mode.

**Step 7: Python Code to Read Compass Data**

Copy and paste the following code into `compass_qmc5883l.py`:

```python
from qmc5883l import QMC5883L
import time

# Initialize the QMC5883L sensor
compass = QMC5883L()

try:
    while True:
        heading = compass.get_bearing()
        print(f"Heading: {heading:.2f}°")
        time.sleep(1)  # Delay to avoid flooding the output
except KeyboardInterrupt:
    print("\nExiting the program.")
```

**Step 8: Run the Program**

1. Activate the virtual environment (if you created one):

   ```bash
   source env/bin/activate  # If using a virtual environment
   ```

2. Run the Python script:

   ```bash
   python3 compass_qmc5883l.py
   ```

Observe the compass heading displayed in degrees.

**Expected output:**

```
Heading: 125.32°
Heading: 126.15°
Heading: 124.98°
......
```

**Further Exploration**

* **Display Heading on an OLED/LED:** Connect an OLED or LED display to show the compass readings.
* **Use Compass in Navigation Projects:** Combine the GY-271 with GPS (e.g., NEO-6M) for navigation in robotics or drones.
* **Calibrate the Sensor:** Improve accuracy by implementing a calibration routine to account for magnetic distortions.  This is important for real-world applications.  You'll often need to find the minimum and maximum readings in the X, Y, and Z axes by rotating the sensor.
