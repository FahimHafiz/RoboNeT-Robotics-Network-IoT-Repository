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
