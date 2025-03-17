const int soilPin = A0; // Soil moisture sensor analog output connected to A0
const int threshold = 500; // Set a threshold value for moisture level

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(soilPin, INPUT); // Set the soil sensor pin as input
  Serial.println("Soil Moisture Sensor Ready");
}

void loop() {
  int moistureValue = analogRead(soilPin); // Read analog value from the sensor

  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureValue); // Print the moisture value

  if (moistureValue < threshold) {
    Serial.println("Soil is dry! Water the plant.");
  } else {
    Serial.println("Soil moisture is sufficient.");
  }

  delay(1000); // Wait for 1 second
}
