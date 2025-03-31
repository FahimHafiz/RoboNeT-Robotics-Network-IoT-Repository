
#include "BluetoothSerial.h"  // Include Bluetooth Serial library
#include "math.h"           // Include math library for calculations
#include <HardwareSerial.h> // Include Hardware Serial library
#include <TinyGPSPlus.h>     // Include TinyGPSPlus library for GPS data
#include <Wire.h>           // Include Wire library for I2C communication
#include <Adafruit_Sensor.h> // Include Adafruit Sensor library
#include <Adafruit_HMC5883_U.h> // Include Adafruit HMC5883 library for compass

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); // Create compass object

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // Create Bluetooth Serial object

HardwareSerial gpsSerial(2); // Create Hardware Serial object for GPS (UART2)
TinyGPSPlus gps;             // Create TinyGPSPlus object

#define RXD2 16 // Define GPS RX pin
#define TXD2 17 // Define GPS TX pin

#define R 6371000.0 // Earth's radius in meters
float pi = PI;       // Define PI

float currLat = 0.0000000;  // Current latitude
float currLong = 0.0000000; // Current longitude

float distanceToTarget = 0.0; // Distance to target GPS coordinate
float targetHeading = 0.0;    // Target heading angle
float currentHeading = 0.0;   // Current heading angle
int current_target = 0;       // Index of current target GPS coordinate

int L_L_PWM = 32; // Left left motor PWM pin
int L_R_PWM = 33; // Left right motor PWM pin
int R_L_PWM = 4;  // Right left motor PWM pin
int R_R_PWM = 2;  // Right right motor PWM pin

float targetList[5][2] = { // Array of target GPS coordinates
  { 23.7993059, 90.4493381 },
  { 23.7995985, 90.4491094 },
  { 23.7991519, 90.4491165 },
  { 23.7993059, 90.4493381 },
  { 23.7991519, 90.4491165 },
};

int size = sizeof(targetList) / sizeof(targetList[0]); // Number of target coordinates
int i = 0;                                             // Loop counter

float targetLat = targetList[current_target][0];  // Current target latitude
float targetLong = targetList[current_target][1]; // Current target longitude

bool bluetoothControl = false; // Flag to enable/disable Bluetooth control mode

void setup() {
  Serial.begin(9600);                                   // Initialize serial communication
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);           // Initialize GPS serial communication
  pinMode(L_L_PWM, OUTPUT);                             // Set motor driver pins as output
  pinMode(L_R_PWM, OUTPUT);
  pinMode(R_L_PWM, OUTPUT);
  pinMode(R_R_PWM, OUTPUT);
  ledcSetup(0, 5000, 8);                                // Configure PWM channels
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);
  ledcAttachPin(L_L_PWM, 0);                            // Attach PWM channels to motor driver pins
  ledcAttachPin(L_R_PWM, 1);
  ledcAttachPin(R_L_PWM, 2);
  ledcAttachPin(R_R_PWM, 3);
  SerialBT.begin("CarControl");                        // Initialize Bluetooth serial
  Serial.println("Start. Pair it with bluetooth!");
  if (!mag.begin()) {                                    // Initialize compass
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
}

void loop() {
  if (SerialBT.available()) {       // Check for Bluetooth data
    char command = SerialBT.read(); // Read command character
    Serial.print("Received command: ");
    Serial.println(command);
    bluetoothControl = true;         // Enable Bluetooth control mode
    controlByBluetooth(command);    // Call Bluetooth control function
  }

  if (bluetoothControl == false) { // If bluetooth control mode is off, run gps control.
    // Commented out GPS navigation code
    // while (i < size) {
    //   currentHeading = readCompass();
    //   readGPS();
    //   if (targetLat == 0 && targetLong == 0) {
    //     stopp();
    //     delay(2000);
    //   } else {
    //     targetHeading = getAnglee(currLat, currLong, targetLat, targetLong);
    //     LeftRight();
    //     distanceToTarget = getDistance(currLat, currLong, targetLat, targetLong);
    //     if (distanceToTarget >= 5) {
    //       goo();
    //     } else if (distanceToTarget < 5) {
    //       SerialBT.println("Completee!!  NEXT POINT");
    //       delay(2000);
    //       i = i + 1;
    //       if (i == size) {
    //         stopp();
    //         delay(100000);
    //       }
    //       nextTarget();
    //     }
    //   }
    // }
  }
}

void controlByBluetooth(char command) { // Function to control motors via Bluetooth
  switch (command) {
    case 'F':
      forward();
      break;
    case 'B':
      backward();
      break;
    case 'L':
      leftward();
      break;
    case 'R':
      rightward();
      break;
    case 'S':
      stopp();
      bluetoothControl = false; // Disable Bluetooth control mode
      break;
    default:
      SerialBT.println("Invalid command");
      break;
  }
}

// ... (rest of the code: getAnglee, getDistance, readGPS, readCompass, LeftRight, goo, nextTarget, forward, backward, rightward, leftward, stopp)
