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
