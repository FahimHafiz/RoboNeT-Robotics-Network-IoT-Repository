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
