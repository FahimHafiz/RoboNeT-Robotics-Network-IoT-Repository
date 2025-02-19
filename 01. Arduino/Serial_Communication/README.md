

# Serial Communication in Arduino
### Concept of Serial Communication
Serial communication is a way for Arduino to send and receive data one bit at a time over a single wire (or two wires for full-duplex communication). It is commonly used for:

* Communicating with a PC (via USB) using the Serial Monitor.
* Exchanging data with other microcontrollers or sensors.
* Controlling modules like GPS, Bluetooth, and WiFi.
## Types of Serial Communication in Arduino
###UART (Universal Asynchronous Receiver Transmitter)

* Uses TX (Transmit) and RX (Receive) pins.
* No clock signal, data transmitted asynchronously.
* Example: Arduino <-> PC via USB.
### I2C (Inter-Integrated Circuit)

* Uses SDA (Data) and SCL (Clock) pins.
* Multiple devices can communicate using addresses.
* Example: Arduino <-> OLED Display.
### SPI (Serial Peripheral Interface)

* Uses MOSI, MISO, SCK, and SS pins.
* Fast communication for sensors & SD cards.
* Example: Arduino <-> SD Card Module.
