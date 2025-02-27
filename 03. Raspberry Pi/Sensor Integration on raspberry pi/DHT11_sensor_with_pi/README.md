# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Sensor Integration with Raspberry Pi: Reading Data from a DHT11 Sensor

**Objective:** To demonstrate how to connect a DHT11 temperature and humidity sensor to a Raspberry Pi and use Python to read and display sensor data on the terminal.

**Step 1: Gather Required Components**

* Raspberry Pi (any model, e.g., Raspberry Pi 4B)
* DHT11 Temperature and Humidity Sensor
* 10kΩ Resistor (optional, for stable data readings)
* Jumper wires
* Breadboard

**Step 2: Connect the DHT11 Sensor to the Raspberry Pi**

| DHT11 Pin | Connection        | Raspberry Pi Pin |
| --------- | ----------------- | ---------------- |
| VCC       | 3.3V Power        | Pin 1            |
| GND       | Ground            | Pin 6            |
| DATA      | GPIO4 (Data)      | Pin 7            |

1. Connect the VCC pin of the DHT11 to Pin 1 (3.3V) on the Raspberry Pi.
2. Connect the GND pin of the DHT11 to Pin 6 (GND).
3. Connect the DATA pin of the DHT11 to GPIO4 (Pin 7) on the Raspberry Pi.
4. Use a 10kΩ resistor between the VCC and DATA pins of the DHT11 for stable signal readings.

   ![raspberry-pi-4-40-pin-description-](https://github.com/user-attachments/assets/4b2b60c6-51a0-4ff7-8cd4-ea0e6e35b746)


**Step 3: Install Required Libraries**

Open the terminal on your Raspberry Pi and install the `Adafruit_DHT` library for reading DHT11 data:

```bash
pip install Adafruit_DHT
```

**Step 4: Create a Project Folder**

1. On your Raspberry Pi desktop, create a folder named `dht11_project`.
2. Inside the folder, create a new Python file named `read_dht11.py`.

**Step 5: Write the Python Code**

Open Thonny and load the `read_dht11.py` file.

Write the following code:

```python
import Adafruit_DHT
import time  # Import the time module

# Define the sensor type and GPIO pin
SENSOR = Adafruit_DHT.DHT11
GPIO_PIN = 4  # GPIO4 (Pin 7)

try:
    while True:
        # Read temperature and humidity from the DHT11 sensor
        humidity, temperature = Adafruit_DHT.read(SENSOR, GPIO_PIN)

        # Check if reading was successful
        if humidity is not None and temperature is not None:
            print(f"Temperature: {temperature:.1f}°C  Humidity: {humidity:.1f}%")
        else:
            print("Failed to retrieve data from sensor. Retrying...")

        time.sleep(2)  # Wait for 2 seconds before the next reading (adjust as needed)

except KeyboardInterrupt:
    print("\nProgram stopped by user.")
```

**Step 6: Run the Program**

1. Save the code in Thonny.
2. Click the Run button (green triangle) in Thonny to execute the script.
3. The terminal will display the temperature and humidity readings from the DHT11 sensor.

**Example output:**

```
Temperature: 24.3°C  Humidity: 56.7%
```

**Step 7: Troubleshooting Tips**

* Ensure the wiring is correct and secure.
* If you see "Failed to retrieve data," check the resistor connection between VCC and DATA.
* Verify that the `Adafruit_DHT` library is installed properly.
* Consider adding a small delay using `time.sleep()` in your loop to prevent excessive sensor readings and improve stability.  I've added a 2-second delay to the code above.
* Some DHT11 sensors can be a bit finicky.  If you continue to have trouble, try a different DHT11 sensor if you have one.
