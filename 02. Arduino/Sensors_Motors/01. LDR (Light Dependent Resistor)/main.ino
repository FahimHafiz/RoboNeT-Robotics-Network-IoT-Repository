const int ldrPin = A0; // LDR connected to Analog Pin A0

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(ldrPin, INPUT); // Set the LDR pin as input
  Serial.println("LDR Sensor Ready");
}

void loop() {
  int lightValue = analogRead(ldrPin); // Read analog value from LDR

  Serial.print("Light Intensity: ");
  Serial.println(lightValue); // Print light intensity value

  delay(500); // Wait for 500 milliseconds
}
