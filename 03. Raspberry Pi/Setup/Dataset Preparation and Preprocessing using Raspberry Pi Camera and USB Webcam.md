Experiment: Dataset Preparation and Preprocessing using Raspberry Pi Camera and USB Webcam.

Objective: To capture images and videos using PiCamera and USB webcam, preprocess them (normalization, resizing, color conversion, etc.), and prepare datasets for basic machine learning tasks.

What You Need
Raspberry Pi 4B with Raspbian OS installed.
PiCamera or USB webcam.
Internet connection for installing packages.
Monitor, keyboard, and mouse connected to Raspberry Pi.

Steps
Step 1: Set Up the Raspberry Pi

Turn on Raspberry Pi.

Open the terminal.

Update the system:

 sudo apt update && sudo apt upgrade -y

Install Python tools:

  sudo apt install python3-pip
  pip3 install virtualenv


3. Set up a project folder:
 
  mkdir ~/ImageProcessing
  cd ~/ImageProcessing


4. Create a virtual environment:
  python3 -m venv env
  source env/bin/activate

You will see (env) in the terminal prompt, indicating the virtual environment is active.
5. Install necessary libraries inside the virtual environment:

  pip install picamera2 opencv-python numpy
  sudo apt install fswebcam

Step 2: Enable PiCamera
Enable the camera using:

sudo raspi-config

Navigate to Interface Options > Camera, enable it, and reboot:

sudo reboot

Part 1: Capturing Images
A. Using PiCamera

Create a Python script:


nano capture_picam.py

1. Paste the following code:


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


2. Save and exit:
Press CTRL+O, hit ENTER, then press CTRL+X.
Run the script to capture images:

 python3 capture_picam.py
3. The images will be saved in the current folder (~/ImageProcessing).

B. Using USB Webcam

Create a Python script:


 nano capture_webcam.py

1. Paste the following code:

import cv2
cap = cv2.VideoCapture(0)
for i in range(5):  # Capture 5 images
    ret, frame = cap.read()
    if ret:
        filename = f"webcam_image_{i}.jpg"
        cv2.imwrite(filename, frame)
        print(f"Saved: {filename}")
    else:
        print("Failed to capture image")
cap.release()

2. Save and exit:
Press CTRL+O, hit ENTER, then press CTRL+X.
Run the script:

 python3 capture_webcam.py

Captured images will also be saved in ~/ImageProcessing.
Part 2: Preprocessing Images
Create a Python script for preprocessing:

 nano preprocess_images.py

1. Paste the following code:

import cv2
import glob
# Find all JPG images in the folder
images = glob.glob("*.jpg")
for img_path in images:
    img = cv2.imread(img_path)
    # Resize image
    resized = cv2.resize(img, (128, 128))
    # Convert to grayscale
    gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
    # Smooth the image
    smoothed = cv2.GaussianBlur(gray, (5, 5), 0)
    # Save processed images
    cv2.imwrite(f"resized_{img_path}", resized)
    cv2.imwrite(f"gray_{img_path}", gray)
    cv2.imwrite(f"smoothed_{img_path}", smoothed)
    print(f"Processed: {img_path}")



2. Save and exit:
Press CTRL+O, hit ENTER, then press CTRL+X.
Run the script:

python3 preprocess_images.py

 Processed images will be saved in the current folder, prefixed with resized_, gray_, and smoothed_.

Part 3: Organizing Files

Create folders for organization:

 mkdir raw_images processed_images

1. Move original images to raw_images folder:
 
 mv picam_image_*.jpg webcam_image_*.jpg raw_images/

2. Move processed images to processed_images folder:

 mv resized_*.jpg gray_*.jpg smoothed_*.jpg processed_images/

Part 4: Verify Processed Images
Create a Python script to display processed images:

 nano verify_image.py


Paste the following code:

import cv2
img = cv2.imread("processed_images/gray_picam_image_0.jpg", 0)
cv2.imshow("Processed Image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()

Save and exit:

Press CTRL+O, hit ENTER, then press CTRL+X.
Run the script:

 python3 verify_image.py

 The processed image will open in a window.




