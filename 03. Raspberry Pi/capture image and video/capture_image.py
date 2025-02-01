from picamera2 import Picamera2
from time import sleep

# Initialize the camera
camera = Picamera2()

# Configure the camera
camera.start()
sleep(2)  # Allow time for the camera to adjust

# Capture and save an image
camera.capture_file("image.jpg")
print("Image saved as image.jpg")

# Stop the camera
camera.stop()
