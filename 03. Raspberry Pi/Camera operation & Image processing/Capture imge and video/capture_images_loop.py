from picamera2 import Picamera2
from time import sleep
# Initialize the camera
camera = Picamera2()
# Start the camera
camera.start()
# Capture 5 images in a loop
for i in range(5):
    file_name = f"image_{i+1}.jpg"
    camera.capture_file(file_name)
    print(f"Image {i+1} saved as {file_name}")
    sleep(2)  # Wait 2 seconds between captures
# Stop the camera
camera.stop()
