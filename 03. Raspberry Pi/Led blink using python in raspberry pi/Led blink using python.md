Experiment: LED Blinking Using Python on Raspberry Pi 4.
Objective: To demonstrate the process of controlling an LED using the Raspberry Pi 4 by writing a Python program to make the LED blink at regular intervals. 
This experiment introduces beginners to GPIO pin usage and basic Python coding for hardware interaction.

Step 1: Gather Required Components
1 x LED (any color)
1 x Resistor (220Ω recommended)
Jumper wires
Breadboard

Step 2: Connect the LED to Raspberry Pi
Place the LED on the breadboard.


    The longer leg is the positive (anode).
    The shorter leg is the negative (cathode).
    Connect the positive leg of the LED to GPIO14 (Pin 8) on the Raspberry Pi using a jumper wire.
    Connect the negative leg of the LED to one end of the 220Ω resistor.


Connect the other end of the resistor to a GND pin (Pin 6) on the Raspberry Pi.


Step 3: Enable GPIO Access
Open a terminal and install the GPIO library:

  sudo apt update
  sudo apt install python3-gpiozero


Step 4: Create a Folder for the Project

On the Raspberry Pi desktop, create a folder named led_blink.
Open Thonny, and save a new file as led_blink.py in the led_blink folder.

Step 5: Write the Python Code

Paste the following code into led_blink.py:

  led_blink.py

Step 6: Run the Program
Open Thonny and load the led_blink.py file.


Click the Run button (green triangle) to execute the program.

The LED will blink ON and OFF every second.

To stop the program, press Ctrl+C in the terminal or click the Stop button in Thonny.


Step 7: Clean Up

Disconnect the Raspberry Pi from power before removing the connections.
Store your components safely for future use.

