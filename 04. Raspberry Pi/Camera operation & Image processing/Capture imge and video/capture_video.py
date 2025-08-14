from picamera2 import Picamera2
from time import sleep
# Initialize the camera
camera = Picamera2()
# Start the camera
camera.start_recording("video.h264")
print("Recording started...")
# Record for 10 seconds
sleep(10)
# Stop the recording
camera.stop_recording()
print("Recording stopped. Video saved as video.h264")
