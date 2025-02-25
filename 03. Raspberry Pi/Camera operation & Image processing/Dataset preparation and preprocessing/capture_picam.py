from picamera2 import Picamera2
import time

picam2 = Picamera2()
picam2.start()

for i in range(5):  # Capture 5 images
    filename = f"picam_image_{i}.jpg"
    picam2.capture_file(filename)
    print(f"Saved: {filename}")
    time.sleep(1)

picam2.stop()
