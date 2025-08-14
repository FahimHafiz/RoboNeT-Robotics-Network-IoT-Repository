const int R_EN = 2;  // Right enable pin
const int L_EN = 3; // Left enable pin
const int R_PWM = 5; // Right PWM pin
const int L_PWM = 6; // Left PWM pin

void setup() {
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Move motor forward
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, LOW);
  analogWrite(R_PWM, 128); // 50% speed
  analogWrite(L_PWM, 0);
  delay(2000);

  // Move motor backward
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, HIGH);
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 128); // 50% speed
  delay(2000);

  // Stop motor
  digitalWrite(R_EN, LOW);
  digitalWrite(L_EN, LOW);
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 0);
  delay(2000);
}
