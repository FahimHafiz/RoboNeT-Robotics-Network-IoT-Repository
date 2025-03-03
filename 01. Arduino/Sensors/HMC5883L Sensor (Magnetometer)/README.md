<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>



# Arduino Integration with HMC5883L Sensor (Magnetometer)
This guide explains how to integrate the HMC5883L magnetometer sensor with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Sensor Name and Type
* Name: HMC5883L
* Type: Magnetometer (3-Axis Compass Sensor)
### Required Library
* You will need the "HMC5883L" library to work with this sensor. You can install it from the Arduino Library Manager.

## Purpose
* The HMC5883L sensor measures the Earth's magnetic field along the X, Y, and Z axes. You can use this sensor to:
* Create a digital compass.
* Measure magnetic field strength.
* Determine direction and orientation.

## Hardware Details
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* HMC5883L Sensor Module.
* Connecting Wires: 4 jumper wires (Male-to-Female).
* Power Source: USB cable to power the Arduino.

## Code with Explanation
Here’s a simple Arduino program to read data from the HMC5883L sensor:
```bash
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(void) {
  Serial.begin(9600);


  if (!mag.begin())  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
}

void loop(void) {
  readCompass();
}




void readCompass() {
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = ((-0) + (29 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180 / M_PI;

  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

  delay(500);
}
```



## Code Explanation:
* Include Libraries: Adds required libraries for sensor communication.
* Initialize Sensor: Checks if the HMC5883L is connected properly.
* Read Magnetic Field Data: Captures magnetic field readings along X, Y, and Z axes.
* Print Data: Displays the readings on the Serial Monitor.
## Troubleshooting Tips
* Sensor Not Detected: Ensure the SDA and SCL pins are connected correctly and the power is supplied to the sensor.
* Incorrect Values: Place the sensor away from electronic devices that could interfere with the magnetic field.
* Library Error: Ensure the Adafruit HMC5883L library is installed and up-to-date.
* Wiring Issues: Double-check the connections to avoid loose wires.

## Diagram
<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/54423e09-887e-4411-aab9-4194ffed6093" />
</div>


This setup ensures accurate detection of gas levels using the MQ-2 sensor.

Now you’re ready to use the HMC58*3L sensor with Arduino! Have fun building safety or monitoring systems! 😊

