
# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: LED Blinking Using Python on Raspberry Pi 4

### Objective
To demonstrate the process of controlling an LED using the Raspberry Pi 4 by writing a Python program to make the LED blink at regular intervals. This experiment introduces beginners to GPIO pin usage and basic Python coding for hardware interaction.

### Step 1: Gather Required Components
- 1 x LED (any color) [See More](https://www.divilabs.com/2013/04/multi-color-leds-beginner-level-guide.html)
- 1 x Resistor (220Ω recommended)[Learn More](https://www.ariat-tech.com/blog/the-essential-guide-to-1k-ohm-resistors-characteristics-and-uses.html)
- Jumper wires [See More](https://blog.sparkfuneducation.com/what-is-jumper-wire)
- Breadboard [See More](https://sfxpcb.com/how-to-use-a-breadboard-and-how-it-works/)

### Step 2: Connect the LED to Raspberry Pi
1. Place the LED on the breadboard.
   - The longer leg is the positive (anode).
   - The shorter leg is the negative (cathode).
2. Connect the positive leg of the LED to GPIO14 (Pin 8) on the Raspberry Pi using a jumper wire.
3. Connect the negative leg of the LED to one end of the 220Ω resistor.
4. Connect the other end of the resistor to a GND pin (Pin 6) on the Raspberry Pi.

   ![led_pi](https://github.com/user-attachments/assets/1377d0e4-3c31-44c7-86a3-cc0d489cf41e)


### Step 3: Enable GPIO Access
Open a terminal and install the GPIO library:
```sh
sudo apt update
sudo apt install python3-gpiozero
```

### Step 4: Create a Folder for the Project
1. On the Raspberry Pi desktop, create a folder named `led_blink`.
2. Open Thonny, and save a new file as `led_blink.py` in the `led_blink` folder.

### Step 5: Write the Python Code
Copy the following code into `led_blink.py`:

```python
from gpiozero import LED
from time import sleep

# Initialize the LED (connected to GPIO14)
led = LED(14)

# Blink the LED
try:
    while True:
        led.on()  # Turn LED on
        print("LED is ON")
        sleep(1)  # Wait for 1 second
        led.off()  # Turn LED off
        print("LED is OFF")
        sleep(1)  # Wait for 1 second
except KeyboardInterrupt:
    print("Program stopped by user.")
```

### Step 6: Run the Program
1. Open Thonny and load the `led_blink.py` file.
2. Click the **Run** button (green triangle) to execute the program.
3. The LED will blink ON and OFF every second.
4. To stop the program, press `Ctrl+C` in the terminal or click the **Stop** button in Thonny.

### Step 7: Clean Up
- Disconnect the Raspberry Pi from power before removing the connections.
- Store your components safely for future use.

