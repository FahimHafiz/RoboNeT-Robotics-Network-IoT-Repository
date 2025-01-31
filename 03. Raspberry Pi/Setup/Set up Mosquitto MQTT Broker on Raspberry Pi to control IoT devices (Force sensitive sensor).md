Experiment: Set up Mosquitto MQTT Broker on Raspberry Pi to control IoT devices (Force sensitive sensor)

Objective: To set up Mosquitto MQTT Broker on Raspberry Pi, connect a force-sensitive sensor, and demonstrate sending and receiving sensor data for IoT applications.

What You Need

  Raspberry Pi 4B with Raspbian OS installed.
  Force-sensitive sensor (e.g., FSR).
  10kΩ resistor.
  Breadboard and jumper wires.
  Internet connection for Raspberry Pi.
  Monitor, keyboard, and mouse connected to Raspberry Pi.

Step 1: Update System and Install Tools

Open the terminal and update your system:

 sudo apt update && sudo apt upgrade -y

1. Install Python tools and Mosquitto MQTT Broker:


sudo apt install python3-pip mosquitto mosquitto-clients

  pip3 install virtualenv

Step 2: Set Up Project Folder and Virtual Environment

Create a project folder:
  
  mkdir ~/IoT_Project
  cd ~/IoT_Project

Create a virtual environment:

  python3 -m venv env
  source env/bin/activate

Install required Python libraries in the virtual environment:
  pip install paho-mqtt RPi.GPIO

Step 3: Enable Mosquitto MQTT Broker

Start the Mosquitto service:

 sudo systemctl start mosquitto

1. Enable Mosquitto to start on boot:
 
 sudo systemctl enable mosquitto

2. Test the MQTT broker locally:

Open one terminal and run:

 mosquitto_sub -h localhost -t "test/topic"


Open another terminal and publish a message:

 mosquitto_pub -h localhost -t "test/topic" -m "Hello, MQTT!"

You should see "Hello, MQTT!" in the first terminal.

Step 4: Connect Force-Sensitive Sensor

Wiring the Sensor:
Connect one end of the force-sensitive sensor to 5V on the Raspberry Pi.
Connect the other end to one leg of a 10kΩ resistor.
Connect the second leg of the resistor to GND.
Connect the junction of the resistor and sensor to GPIO pin 17 (physical pin 11).

Step 5: Write Python Scripts

A. Sensor Data Publisher

Create a script to publish sensor data:

 nano sensor_publisher.py

1. Paste the following code:

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


Save and exit:
Press CTRL+O, hit ENTER, then press CTRL+X.

B. Data Receiver (Subscriber)
Create a script to subscribe and receive sensor data:

 nano data_subscriber.py

1. Paste the following code:
 
 
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


Save and exit:
Press CTRL+O, hit ENTER, then press CTRL+X.
Step 6: Run the System
Run the Publisher Script:
 In one terminal, activate the virtual environment and run the publisher:

  source env/bin/activate
  python3 sensor_publisher.py


1. Run the Subscriber Script:

Open another terminal, activate the virtual environment, and run the subscriber:
  source env/bin/activate
  python3 data_subscriber.py

1. Test the System:
Apply force to the sensor, and you should see the published force values in the subscriber terminal.
Further Exploration

GPS Module:

Integrate a GPS module to publish location data to a different topic (e.g., gps/location).
Home Assistant:

Use Home Assistant for a user-friendly IoT dashboard to visualize and control devices.
Automation:

Set up triggers or alarms based on force sensor readings.

