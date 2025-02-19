const int buttonPin = 2;  // Button connected to D2
const int ledPin = 13;    // LED connected to D13
int buttonState = 0;      // Variable to store button state

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read button state

  if (buttonState == HIGH) { // If button is pressed
    digitalWrite(ledPin, HIGH); // Turn LED ON
    Serial.println("LED ON");
  } else {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    Serial.println("LED OFF");
  }
}
