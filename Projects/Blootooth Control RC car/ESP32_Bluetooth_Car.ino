// Define custom settings for Dabble and include the Gamepad module for Bluetooth control
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Define motor control pins
// Right motor connections
int enableRightMotor = 22;  // PWM control pin for right motor speed
int rightMotorPin1 = 16;     // Right motor direction control pin 1
int rightMotorPin2 = 17;     // Right motor direction control pin 2

// Left motor connections
int enableLeftMotor = 23;  // PWM control pin for left motor speed
int leftMotorPin1 = 18;    // Left motor direction control pin 1
int leftMotorPin2 = 19;    // Left motor direction control pin 2

// Define maximum motor speed (PWM range is 0-255)
#define MAX_MOTOR_SPEED 255

// PWM configuration for motor speed control
const int PWMFreq = 1000;  // PWM frequency set to 1 KHz
const int PWMResolution = 8;  // 8-bit resolution (values range from 0 to 255)
const int rightMotorPWMSpeedChannel = 4;  // PWM channel for right motor
const int leftMotorPWMSpeedChannel = 5;   // PWM channel for left motor

// Function to control motor speed and direction
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  // Right motor direction control
  if (rightMotorSpeed < 0) // Move backward
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);    
  }
  else if (rightMotorSpeed > 0) // Move forward
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);      
  }
  else // Stop right motor
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);      
  }

  // Left motor direction control
  if (leftMotorSpeed < 0) // Move backward
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);    
  }
  else if (leftMotorSpeed > 0) // Move forward
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);      
  }
  else // Stop left motor
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);      
  }

  // Set motor speed using PWM
  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed)); // Right motor speed
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));   // Left motor speed
}

// Function to set up pin modes and initialize PWM for motor speed control
void setUpPinModes()
{
  // Configure motor control pins as output
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Set up PWM channels for speed control
  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);  
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel); 

  // Stop motors initially
  rotateMotor(0, 0); 
}

// Setup function (runs once at startup)
void setup()
{
  setUpPinModes(); // Initialize pin modes and PWM
  Dabble.begin("MyBluetoothCar"); // Initialize Bluetooth communication with the Dabble app
}

// Main loop function (runs repeatedly)
void loop()
{
  int rightMotorSpeed = 0;  // Initialize right motor speed
  int leftMotorSpeed = 0;   // Initialize left motor speed

  Dabble.processInput(); // Process input from the Bluetooth gamepad

  // Check for Gamepad button presses and set motor speeds accordingly
  if (GamePad.isUpPressed()) // Move forward
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  if (GamePad.isDownPressed()) // Move backward
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (GamePad.isLeftPressed()) // Turn left (right motor moves forward, left motor moves backward)
  {
    rightMotorSpeed = MAX_MOTOR_SPEED;
    leftMotorSpeed = -MAX_MOTOR_SPEED;
  }

  if (GamePad.isRightPressed()) // Turn right (left motor moves forward, right motor moves backward)
  {
    rightMotorSpeed = -MAX_MOTOR_SPEED;
    leftMotorSpeed = MAX_MOTOR_SPEED;
  }

  // Apply motor speed settings
  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}
