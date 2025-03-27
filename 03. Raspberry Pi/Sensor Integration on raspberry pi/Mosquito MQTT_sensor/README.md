# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Set up Mosquitto MQTT Broker on Raspberry Pi to control IoT devices (Force sensitive sensor)

**Objective:** To set up Mosquitto MQTT Broker on Raspberry Pi, connect a force-sensitive sensor, and demonstrate
sending and receiving sensor data for IoT applications.

**What You Need**

* Raspberry Pi 4B with Raspbian OS installed.
* Force-sensitive sensor (e.g., FSR).[Link](https://images.app.goo.gl/HDH1uxgPYexEatf87)
* 10kΩ resistor.[Link](https://www.ic-components.com/blog/understanding-10k-ohm-resistor-color-code-and-application.jsp)
* Breadboard and jumper wires.
* Internet connection for Raspberry Pi.
* Monitor, keyboard, and mouse connected to Raspberry Pi.

**Step 1: Update System and Install Tools**

Open the terminal and update your system:

```bash
sudo apt update && sudo apt upgrade -y
```

1. Install Python tools and Mosquitto MQTT Broker:

```bash
sudo apt install python3-pip mosquitto mosquitto-clients
pip3 install virtualenv
```

**Step 2: Set Up Project Folder and Virtual Environment**

1. Create a project folder:

   ```bash
   mkdir ~/IoT_Project
   cd ~/IoT_Project
   ```

2. Create a virtual environment:

   ```bash
   python3 -m venv env
   source env/bin/activate
   ```

3. Install required Python libraries in the virtual environment:

   ```bash
   pip install paho-mqtt RPi.GPIO
   ```

**Step 3: Enable Mosquitto MQTT Broker**

1. Start the Mosquitto service:

   ```bash
   sudo systemctl start mosquitto
   ```

2. Enable Mosquitto to start on boot:

   ```bash
   sudo systemctl enable mosquitto
   ```

3. Test the MQTT broker locally:

   Open one terminal and run:

   ```bash
   mosquitto_sub -h localhost -t "test/topic"
   ```

   Open another terminal and publish a message:

   ```bash
   mosquitto_pub -h localhost -t "test/topic" -m "Hello, MQTT!"
   ```

   You should see "Hello, MQTT!" in the first terminal.

**Step 4: Connect Force-Sensitive Sensor**

**Wiring the Sensor:**

1. Connect one end of the force-sensitive sensor to 5V on the Raspberry Pi.
2. Connect the other end to one leg of a 10kΩ resistor.
3. Connect the second leg of the resistor to GND.
4. Connect the junction of the resistor and sensor to GPIO pin 17 (physical pin 11).

   ![raspberry-pi-4-40-pin-description-](https://github.com/user-attachments/assets/87843b0f-4351-44b1-ab4c-63ab6b3edebe)

**Step 5: Write Python Scripts**

**A. Sensor Data Publisher (`sensor_publisher.py`)**

Create a script to publish sensor data:

```bash
nano sensor_publisher.py
```

1. Paste the following code:

   ```python
   import RPi.GPIO as GPIO
   import time
   import paho.mqtt.client as mqtt

   # MQTT broker details
   BROKER = "localhost"
   TOPIC = "sensor/force"

   # GPIO setup
   SENSOR_PIN = 17
   GPIO.setmode(GPIO.BCM)
   GPIO.setup(SENSOR_PIN, GPIO.IN)

   # MQTT setup
   client = mqtt.Client()
   client.connect(BROKER)

   try:
       while True:
           force_value = GPIO.input(SENSOR_PIN)  # Read sensor value
           client.publish(TOPIC, str(force_value))
           print(f"Published: {force_value}")
           time.sleep(1)  # Publish every 1 second
   except KeyboardInterrupt:
       print("Exiting...")
   finally:
       GPIO.cleanup()
   ```

Save and exit:
Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.

**B. Data Receiver (Subscriber) (`data_subscriber.py`)**

Create a script to subscribe and receive sensor data:

```bash
nano data_subscriber.py
```

1. Paste the following code:

   ```python
   import paho.mqtt.client as mqtt

   # MQTT broker details
   BROKER = "localhost"
   TOPIC = "sensor/force"

   # Callback for receiving messages
   def on_message(client, userdata, message):
       print(f"Received: {message.payload.decode()}")

   # MQTT setup
   client = mqtt.Client()
   client.on_message = on_message
   client.connect(BROKER)

   client.subscribe(TOPIC)
   client.loop_forever()
   ```

Save and exit:

Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.

**Step 6: Run the System**

1. **Run the Publisher Script:**

   In one terminal, activate the virtual environment and run the publisher:

   ```bash
   source env/bin/activate
   python3 sensor_publisher.py
   ```

2. **Run the Subscriber Script:**

   Open another terminal, activate the virtual environment, and run the subscriber:

   ```bash
   source env/bin/activate
   python3 data_subscriber.py
   ```

3. **Test the System:**

   Apply force to the sensor, and you should see the published force values in the subscriber terminal.

**Further Exploration**

* **GPS Module:** Integrate a GPS module to publish location data to a different topic (e.g., `gps/location`).
* **Home Assistant:** Use Home Assistant for a user-friendly IoT dashboard to visualize and control devices.
* **Automation:** Set up triggers or alarms based on force sensor readings.
```
