const int mq2Pin = A0; // MQ-2 analog output connected to A0

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(mq2Pin, INPUT); // Set the MQ-2 pin as input
  Serial.println("MQ-2 Gas Sensor Ready");
}

void loop() {
  int gasLevel = analogRead(mq2Pin); // Read analog value from MQ-2

  Serial.print("Gas Level: ");
  Serial.println(gasLevel); // Print gas level value

  delay(500); // Wait for 500 milliseconds
