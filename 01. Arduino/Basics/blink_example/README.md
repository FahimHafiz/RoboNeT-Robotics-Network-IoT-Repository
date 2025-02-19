<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>

# Blinking LED with Arduino Uno: 
This example shows the simplest thing you can do with an Arduino to see physical output: it blinks the on-board LED.

## Hardware Required :
* Arduino Uno
* LED
* 220 ohm resistor




## The Pin Diagram:


<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/43a8a878-8f5a-4146-942c-bbf5c1788acf" />
</div>






## After connecting copy paste the following code there:

```bash
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

## Explanation:
* ```void setup():```
 This runs once when the Arduino starts. Here, we tell the Arduino to treat the onboard LED pin as an "output" so we can control it.


* ```void loop():```
 This runs repeatedly in a loop. It alternates between turning the LED on and off, each time waiting for 1 second.


* ```pinMode(LED_BUILTIN, OUTPUT);:```
 Prepares the built-in LED pin (connected to LED_BUILTIN) to send signals (ON/OFF).


* ```digitalWrite(LED_BUILTIN, HIGH);:```
 Sends power to the LED, turning it ON.


* ```delay(1000);:```
 Pauses the program for 1 second (1000 milliseconds) before continuing.


* ```digitalWrite(LED_BUILTIN, LOW);:```
 Stops sending power to the LED, turning it OFF.


* ```delay(1000);:```
 Waits another 1 second before restarting the loop.




# Conclusion: 
This documentation provides a straightforward introduction to Arduino Uno development. By following the outlined steps, beginners can set up the Arduino IDE, familiarize themselves with basic features, and successfully execute a "Blink" program to test their hardware setup. This foundational knowledge empowers students to confidently explore and develop more complex projects using the Arduino platform.
