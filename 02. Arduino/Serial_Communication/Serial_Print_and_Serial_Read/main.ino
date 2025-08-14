void setup() {
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
  Serial.println("Arduino Serial Communication Ready");
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    String input = Serial.readString(); // Read the incoming data as a string

    Serial.print("You entered: ");
    Serial.println(input); // Print the received data back to the Serial Monitor
  }

  delay(100); // Wait for a short time
}
