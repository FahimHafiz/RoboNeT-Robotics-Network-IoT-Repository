## **4.4 Project 1: Blinking an LED**

Our first hardware project is the "Hello, World\!" of electronics: blinking an LED.

**Hardware Needed:**

* 1 x LED (any color)  
* 1 x 330Ω Resistor (or any in the 220-330Ω range)  
* 2 x Jumper Wires  
* 1 x Breadboard

**Hardware Setup:**

1. **Safety First:** Unplug your Raspberry Pi from the power supply before connecting any wires to the GPIO pins.  
2. **LEDs have polarity:** The longer leg is the positive (anode), and the shorter leg is the negative (cathode).  
3. **Build the circuit:**

**![][image1]**

* Connect a jumper wire from a **GND** pin on the Pi to the blue (negative) rail on your breadboard.  
  * Connect the **short leg** (cathode) of the LED to this same negative rail on the breadboard.  
  * Connect the **long leg** (anode) of the LED to an empty row on the breadboard.  
  * Plug one leg of the **330Ω resistor** into the same row as the LED's long leg.  
  * Plug the other leg of the resistor into a different empty row.  
  * Connect your second jumper wire from **GPIO 17** (pin 11\) on the Pi to the row with the resistor's second leg.

**The Code:**

1. Once your circuit is built, plug your Pi back in and boot it up.  
2. Open a **Terminal**, navigate to your `Projects` folder (`cd Projects`).  
3. Create a new file: `nano blink.py`

Type (or copy) the following code into `nano`:
```python
import RPi.GPIO as GPIO  # Import the GPIO library
import time              # Import the time library for delays
# Set the pin numbering mode (BCM refers to the GPIO number, not the pin number)
GPIO.setmode(GPIO.BCM)
# Disable warnings
GPIO.setwarnings(False)
# Set up GPIO pin 17 as an output pin
LED_PIN = 17
GPIO.setup(LED_PIN, GPIO.OUT)
print("LED Blinking... Press Ctrl+C to exit.")
try:
 # Loop forever
    while True:
        print("LED ON")
        GPIO.output(LED_PIN, GPIO.HIGH)  # Turn the LED on
        time.sleep(1)                    # Wait for 1 second
        print("LED OFF")
        GPIO.output(LED_PIN, GPIO.LOW)   # Turn the LED off
        time.sleep(1)                    # Wait for 1 second
except KeyboardInterrupt:
    # This part runs when you press Ctrl+C
    print("Stopping program.")
    GPIO.cleanup()  # Clean up the GPIO pins
```
**Execution Instructions:**

1. Save the file and exit `nano` (`Ctrl+X`, `Y`, `Enter`).

Run the script. Because it accesses hardware, you must use `sudo`:

sudo python3 blink.py

2. Look at your breadboard. Your LED should be blinking on and off every second\!  
3. To stop the program, go to your terminal and press `Ctrl + C`. The `GPIO.cleanup()` command will run, turning the LED off.

---

### Next Project

➡️ **[Project 2: Reading a Sensor (Push Button)](Project%202%3A%20Reading%20a%20Sensor%20%28Push%20Button%29.md)**

[image1]: <../assets/04-programming-with-python-and-gpio/image1.png>
