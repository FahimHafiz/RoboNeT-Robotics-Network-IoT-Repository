# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Dataset Preparation and Preprocessing using Raspberry Pi Camera

### Objective
To capture images and videos using PiCamera, preprocess them (normalization, resizing, color conversion, etc.), and prepare datasets for basic machine learning tasks.

## What You Need
- Raspberry Pi 4B with Raspbian OS installed.
- PiCamera. [Details](https://www.raspberrypi.com/products/camera-module-3/)
- Internet connection for installing packages.
- Monitor, keyboard, and mouse connected to Raspberry Pi.

---

## Steps

### Step 1: Set Up the Raspberry Pi
1. Turn on Raspberry Pi.
2. Open the terminal.
3. Update the system:
   ```sh
   sudo apt update && sudo apt upgrade -y
   ```
4. Install Python tools:
   ```sh
   sudo apt install python3-pip
   pip3 install virtualenv
   ```
5. Set up a project folder:
   ```sh
   mkdir ~/ImageProcessing
   cd ~/ImageProcessing
   ```
6. Create a virtual environment:
   ```sh
   python3 -m venv env
   source env/bin/activate
   ```
   You will see `(env)` in the terminal prompt, indicating the virtual environment is active.
7. Install necessary libraries inside the virtual environment:
   ```sh
   pip install picamera2 opencv-python numpy
   sudo apt install fswebcam
   ```

---

### Step 2: Enable PiCamera
Enable the camera using:
   ```sh
   sudo raspi-config
   ```
Navigate to **Interface Options > Camera**, enable it, and reboot:
   ```sh
   sudo reboot
   ```

---

## Part 1: Capturing Images

### A. Using PiCamera
1. Create a Python script:
   ```sh
   nano capture_picam.py
   ```
2. Paste the following code:
   ```python
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
   ```
3. Save and exit:
   - Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.
4. Run the script to capture images:
   ```sh
   python3 capture_picam.py
   ```
5. The images will be saved in the current folder (`~/ImageProcessing`).

---

## Part 2: Preprocessing Images

1. Create a Python script for preprocessing:
   ```sh
   nano preprocess_images.py
   ```
2. Paste the following code:
   ```python
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
   ```
3. Save and exit:
   - Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.
4. Run the script:
   ```sh
   python3 preprocess_images.py
   ```
5. Processed images will be saved in the current folder, prefixed with `resized_`, `gray_`, and `smoothed_`.

---

## Part 3: Organizing Files

1. Create folders for organization:
   ```sh
   mkdir raw_images processed_images
   ```
2. Move original images to `raw_images` folder:
   ```sh
   mv picam_image_*.jpg raw_images/
   ```
3. Move processed images to `processed_images` folder:
   ```sh
   mv resized_*.jpg gray_*.jpg smoothed_*.jpg processed_images/
   ```

---

## Part 4: Verify Processed Images

1. Create a Python script to display processed images:
   ```sh
   nano verify_image.py
   ```
2. Paste the following code:
   ```python
   import cv2

   img = cv2.imread("processed_images/gray_picam_image_0.jpg", 0)
   cv2.imshow("Processed Image", img)
   cv2.waitKey(0)
   cv2.destroyAllWindows()
   ```
3. Save and exit:
   - Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.
4. Run the script:
   ```sh
   python3 verify_image.py
   ```
5. The processed image will open in a window.
