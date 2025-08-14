#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // Pin where the DS18B20 is connected

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.println("DS18B20 Sensor Ready");
}

void loop() {
  sensors.requestTemperatures(); // Send command to get temperatures
  float temperature = sensors.getTempCByIndex(0); // Read temperature in Celsius

  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Sensor not connected!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); // Wait for 1 second before reading again
}
