<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>


# Arduino Integration with DHT11 Sensor (Temperature and Humidity Sensor)
This guide explains how to integrate the DHT11 temperature and humidity sensor with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Sensor Name and Type
* Name: DHT11
* Type: Temperature and Humidity Sensor
### Required Library
* You will need the "DHT" library by Adafruit. You can install it from the Arduino Library Manager.

## Purpose
* The DHT11 sensor measures:
* Temperature (in Celsius and Fahrenheit).
* Humidity (as a percentage).
You can use this sensor to:
* Monitor environmental conditions.
* Build weather stations.
* Control systems based on temperature and humidity.
## Hardware Details
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* DHT11 Sensor Module (with or without breakout board).
* Connecting Wires: 3 jumper wires (Male-to-Female).
* Power Source: USB cable to power the Arduino.

## Code with Explanation
Here’s a simple Arduino program to read data from the DHT11 sensor:
```bash
#include <DHT.h>

#define DHTPIN 2     // Pin where the DHT11 is connected
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 Sensor Ready");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  delay(2000); // Wait for 2 seconds before reading again
}
```
## Code Explanation:
* Include Libraries: Adds the DHT library for sensor communication.
* Define Pins: Specifies the pin where the DHT11 is connected.
* Initialize Sensor: Prepares the DHT11 sensor for reading data.
* Read Data: Captures temperature and humidity readings.
* Print Data: Displays the readings on the Serial Monitor.
## Troubleshooting Tips
* Sensor Not Detected: Ensure the DATA pin is connected correctly and the power is supplied to the sensor.
* Incorrect Readings: Place the sensor in a stable environment to get accurate readings.
* Library Error: Ensure the DHT library is installed and up-to-date.
* Wiring Issues: Double-check the connections to avoid loose wires.
## Diagram
Below is a block diagram explaining the system:

|  Arduino Board          |      DHT11 Sensor     |
|-------------------------|-----------------------|
|         VCC             |           VCC         |
|         GND             |           GND         |
|         Digital Pin 2   |           DATA        |

This simple setup ensures the sensor communicates with the Arduino to measure temperature and humidity.

Now you’re ready to use the DHT11 temperature and humidity sensor with Arduino! Enjoy building cool projects! 😊

