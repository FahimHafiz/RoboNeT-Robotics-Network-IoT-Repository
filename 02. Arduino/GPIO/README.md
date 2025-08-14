# Concept of Read and Write in Arduino
In Arduino, reading refers to getting data from a source (e.g., sensors, buttons, serial input), while writing means sending data somewhere (e.g., LEDs, motors, serial monitor, memory).

# Types of Read and Write Operations
### Digital Read & Write (For on/off signals like buttons and LEDs)

* #### Read: digitalRead(pin) → Reads HIGH or LOW from a digital input (e.g., a button).
* #### Write: digitalWrite(pin, HIGH/LOW) → Sends HIGH (ON) or LOW (OFF) to a digital output (e.g., LED, relay).
### Analog Read & Write (For variable signals like sensors and dimmable LEDs)

* #### Read: analogRead(pin) → Reads a value between 0 and 1023 from an analog sensor (e.g., a temperature sensor).
* #### Write: analogWrite(pin, value) → Outputs a PWM signal (0-255) to control brightness or speed (e.g., dim an LED).
### Serial Read & Write (For communication with a PC or other devices)

* #### Read: Serial.read() or Serial.readString() → Reads input from the Serial Monitor or another device.
* #### Write: Serial.print() or Serial.println() → Sends data to a PC or another microcontroller.
### EEPROM Read & Write (For storing permanent data)

* #### Read: EEPROM.read(address) → Reads a stored value from memory.
* #### Write: EEPROM.write(address, value) → Saves a value to memory that stays even after power off.

