#include "BluetoothSerial.h"
#include "math.h"
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

HardwareSerial gpsSerial(2); // Use UART2 (TX2: GPIO17, RX2: GPIO16)
TinyGPSPlus gps;  // Create TinyGPS++ object



#define RXD2 16
#define TXD2 17

#define R 6371000.0
float pi = PI;

float currLat = 0.0000000;
float currLong = 0.0000000;

float distanceToTarget = 0.0;
float targetHeading = 0.0;
float currentHeading = 0.0;
int current_target = 0;



int L_L_PWM = 32;
int L_R_PWM = 33;

int R_L_PWM = 4;
int R_R_PWM = 2;




float targetList[5][2] = {
  { 23.7993059, 90.4493381 },
  { 23.7995985, 90.4491094 },
  { 23.7991519, 90.4491165 },
  { 23.7993059, 90.4493381 },
  { 23.7991519, 90.4491165 },
};

int size = sizeof(targetList) / sizeof(targetList[0]);
int i = 0;

float targetLat = targetList[current_target][0];
float targetLong = targetList[current_target][1];

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // GPS baud rate, RX, TX

  pinMode(L_L_PWM, OUTPUT);
  pinMode(L_R_PWM, OUTPUT);
  pinMode(R_L_PWM, OUTPUT);
  pinMode(R_R_PWM, OUTPUT);


  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(L_L_PWM, 0);
  ledcAttachPin(L_R_PWM, 1);
  ledcAttachPin(R_L_PWM, 2);
  ledcAttachPin(R_R_PWM, 3);


  SerialBT.begin("Autonomus System"); //Bluetooth device name
  Serial.println("Start. Pair it with bluetooth!");

  if (!mag.begin())  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
}
void loop() {
  while (i < size) {
    currentHeading = readCompass();
    readGPS();

    if (targetLat == 0 && targetLong == 0)
    {
      stopp();
      delay(2000);
    }
    else
    {
      targetHeading = getAnglee(currLat, currLong, targetLat, targetLong);
      LeftRight();

      distanceToTarget = getDistance(currLat, currLong, targetLat, targetLong);
      if (distanceToTarget >= 5)
      {
        goo();
      }
      else if (distanceToTarget < 5) {
        SerialBT.println("Completee!!  NEXT POINT");
        delay(2000);
        i = i + 1;

        if (i == size) {
          stopp();
          delay(100000);
        }
        nextTarget();
      }
    }
  }
}
float getAnglee( float lat1, float long1, float lat2, float long2 )
{
  float dlon = radians(long2 - long1);
  float cLat = radians(lat1);
  float tLat = radians(lat2);
  float a1 = sin(dlon) * cos(tLat);
  float a2 = sin(cLat) * cos(tLat) * cos(dlon);
  a2 = cos(cLat) * sin(tLat) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0)
  {
    a2 += TWO_PI;
  }
  int targetHeading = degrees(a2);

  return targetHeading;
}
float getDistance(float lat1, float long1, float lat2, float long2) {
  float latA = radians(lat1);
  float longA = radians(long1);
  float latB = radians(lat2);
  float longB = radians(long2);

  float dLat = latB - latA;
  float dLong = longB - longA;

  float a = pow(sin(dLat / 2), 2) + cos(latA) * cos(latB) * pow(sin(dLong / 2), 2);
  a = constrain(a, 0.0, 1.0);  // Ensure value is within valid range
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return R * c;  // Returns distance in meters
}
void readGPS()
{
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    gps.encode(c); // Feed data to TinyGPS++

    if (gps.location.isUpdated()) { // When new GPS data is available
      currLat = gps.location.lat();
      currLong = gps.location.lng();

      Serial.print("Latitude: ");
      Serial.print(currLat, 6);
      Serial.print(" | Longitude: ");
      Serial.println(currLong, 6);
    }
  }
}
int readCompass()
{
  sensors_event_t event;
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 29 / 60.0;
  declinationAngle = radians(declinationAngle);
  heading += declinationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180 / M_PI;

  return ((int)headingDegrees);
}



void LeftRight() {
  while (true)  {
    currentHeading = readCompass();
    //    readGPS();

    targetHeading = getAnglee(currLat, currLong, targetLat, targetLong);
    // distanceToTarget = getDistance(currLat, currLong, targetLat, targetLong);


    float headingDiff = fmod(((targetHeading - currentHeading) + 360), 360);


    if (headingDiff <= 8) {
      break;
    }

    if (headingDiff > 180) {
      leftward();
      SerialBT.println("Turning Left...");
    } else {
      rightward();
      SerialBT.println("Turning Right...");
    }
  }
}
void goo()  {
  distanceToTarget = getDistance(currLat, currLong, targetLat, targetLong);

  if (distanceToTarget >= 5)  {
    forward();
    SerialBT.print(distanceToTarget);
    SerialBT.println("      Gooooooooooooo");
    delay(400);
  }
  else {
    stopp();  // Stop when close to target
    SerialBT.println("Target reached! Stopping...");
  }
}


void nextTarget() {
  current_target++;
  if (current_target >= size) {  // Prevent out-of-bounds access
    stopp();
    SerialBT.println("All points reached!");
    delay(100000);
    return;
  }
  targetLat = targetList[current_target][0];
  targetLong = targetList[current_target][1];
  delay(7000);
}


void forward()
{
  ledcWrite(0, 150);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 150);
}


//1250 r 1750 l 1700 f
void rightward()
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 120);
}


void leftward()
{
  ledcWrite(0, 120);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}

void stopp()
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}
