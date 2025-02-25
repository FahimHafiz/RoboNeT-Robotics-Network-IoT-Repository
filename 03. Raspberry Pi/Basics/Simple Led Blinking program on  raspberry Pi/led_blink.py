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
