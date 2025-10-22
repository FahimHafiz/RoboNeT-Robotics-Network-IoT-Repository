import time
from qmc5883l import QMC5883L

# Initialize the QMC5883L sensor with I2C bus 1
compass = QMC5883L(bus=1)

try:
    while True:
        # Read the compass heading
        heading = compass.get_bearing()

        # Ensure valid data
        if heading is not None:
            print(f"Heading: {heading:.2f}°")
        else:
            print("Warning: Failed to read heading data")

        time.sleep(1)  # Delay to prevent excessive readings

except Exception as e:
    print(f"Error: {e}")

except KeyboardInterrupt:
    print("\nExiting the program.")
