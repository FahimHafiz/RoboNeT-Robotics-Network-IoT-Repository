from qmc5883l import QMC5883L
import time

# Initialize the QMC5883L sensor
compass = QMC5883L()

try:
    while True:
        heading = compass.get_bearing()
        print(f"Heading: {heading:.2f}°")
        time.sleep(1)  # Delay to avoid flooding the output
except KeyboardInterrupt:
    print("\nExiting the program.")
