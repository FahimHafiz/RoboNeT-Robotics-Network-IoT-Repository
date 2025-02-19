
<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>


# Arduino Integration with MPU6050 Sensor (Accelerometer and Gyroscope)
This guide explains how to integrate the MPU6050 accelerometer and gyroscope sensor with an Arduino board. The documentation is designed for junior students and is easy to understand.

## Sensor Name and Type
* Name: MPU6050
* Type: Accelerometer and Gyroscope (6 Degrees of Freedom)
### Required Library
* You will need the "MPU6050" library by Electronic Cats or "Adafruit MPU6050" library. You can install it from the Arduino Library Manager.

## Purpose
The MPU6050 sensor measures acceleration and angular velocity along the X, Y, and Z axes. You can use this sensor to:
* Detect motion and orientation.
* Measure tilt and rotation.
* Build IMUs (Inertial Measurement Units) for robots, drones, and other systems.

## Hardware Details
* Arduino Board: Any model (e.g., Uno, Nano, Mega).
* MPU6050 Sensor Module.
* Connecting Wires: 4 jumper wires (Male-to-Female).
* Power Source: USB cable to power the Arduino.

## Code with Explanation
Here’s a simple Arduino program to read data from the MPU6050 sensor:
```bash
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the MPU6050 sensor
  if (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("MPU6050 not detected. Check connections!");
    while (1);
  }

  Serial.println("MPU6050 Ready");
}

void loop() {
  // Read acceleration and gyroscope data
  Vector rawAccel = mpu.readRawAccel();
  Vector rawGyro = mpu.readRawGyro();

  // Display results on Serial Monitor
  Serial.print("Accel X: "); Serial.print(rawAccel.XAxis);
  Serial.print(" Y: "); Serial.print(rawAccel.YAxis);
  Serial.print(" Z: "); Serial.println(rawAccel.ZAxis);

  Serial.print("Gyro X: "); Serial.print(rawGyro.XAxis);
  Serial.print(" Y: "); Serial.print(rawGyro.YAxis);
  Serial.print(" Z: "); Serial.println(rawGyro.ZAxis);

  delay(500); // Wait for 0.5 seconds before reading again
}
```

## Code Explanation:
* Include Libraries: Adds required libraries for sensor communication.
* Initialize Sensor: Checks if the MPU6050 is connected properly.
* Read Data: Captures raw acceleration and gyroscope readings.
* Print Data: Displays the readings on the Serial Monitor.

## Troubleshooting Tips
* Sensor Not Detected: Ensure the SDA and SCL pins are connected correctly and the power is supplied to the sensor.
* Incorrect Values: Place the sensor on a stable surface to avoid interference.
* Library Error: Ensure the MPU6050 library is installed and up-to-date.
* Wiring Issues: Double-check the connections to avoid loose wires.

## Diagram
Below is a block diagram explaining the system:

|  Arduino Board  |   MPU6050 Sensor    |
|-----------------|---------------------|
|         VCC     |           VCC       |
|         GND     |           GND       |
|         SDA     |           SDA       |
|         SCL     |           SCL       |

This simple setup ensures the sensor communicates with the Arduino using I2C protocol.

Now you’re ready to use the MPU6050 accelerometer and gyroscope sensor with Arduino! Enjoy exploring motion and orientation! 😊

