# UNITED INTERNATIONAL UNIVERSITY (UIU)  
## Dept. of Computer Science & Engineering  

## Experiment: Capturing and Processing Images Using a USB Webcam on Raspberry Pi 4B (Ubuntu)  

### Objective  
- Capture and save images using a USB webcam.  
- Record videos using a [webcam](https://images.app.goo.gl/bMqE13HdxSXXGAyC8).  
- Process images (grayscale, resizing, thresholding, and smoothing).  
- Automate dataset collection for machine learning applications.  
- Use a virtual environment to manage dependencies properly.  

---

## Steps  

### Step 1: Update System and Install Required Packages  
1. Open the terminal (`Ctrl + Alt + T`).  
2. Update and upgrade system packages:  
   ```sh
   sudo apt update && sudo apt upgrade -y
   ```
3. Install required dependencies:  
   ```sh
   sudo apt install python3-venv python3-pip fswebcam v4l-utils ffmpeg -y
   ```

---

### Step 2: Create a Project Folder and Virtual Environment  
1. Create a new project directory:  
   ```sh
   mkdir webcam_project && cd webcam_project
   ```
2. Create and activate a virtual environment:  
   ```sh
   python3 -m venv venv
   source venv/bin/activate
   ```
3. Install required Python libraries:  
   ```sh
   pip install opencv-python numpy
   ```
4. Verify OpenCV installation:  
   ```sh
   python3 -c "import cv2; print(cv2.__version__)"
   ```

---

### Step 3: Check and Test the Webcam  
1. Check if the webcam is detected:  
   ```sh
   v4l2-ctl --list-devices
   ```
2. Capture a test image:  
   ```sh
   fswebcam -r 640x480 --jpeg 85 test_image.jpg
   ```
3. View the captured image:  
   ```sh
   xdg-open test_image.jpg
   ```

---

### Step 4: Record a Video Using the Webcam  
1. Record a **10-second** video:  
   ```sh
   ffmpeg -t 10 -f v4l2 -i /dev/video0 -r 25 test_video.mp4
   ```
2. Play the recorded video:  
   ```sh
   xdg-open test_video.mp4
   ```

---

### Step 5: Image Processing Using OpenCV  
#### Convert Image to Grayscale  
Create a Python script:  
```sh
nano process_image.py
```
Paste the following code:  
```python
import cv2

img = cv2.imread("test_image.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imwrite("gray_image.jpg", gray)

print("Grayscale image saved as gray_image.jpg")
```
Run the script:  
```sh
python3 process_image.py
```

---

#### Resize an Image  
Modify `process_image.py`:  
```python
resized = cv2.resize(img, (200, 200))
cv2.imwrite("resized_image.jpg", resized)
```
Run the script:  
```sh
python3 process_image.py
```

---

#### Convert Image to Binary (Thresholding)  
Modify `process_image.py`:  
```python
_, binary = cv2.threshold(gray, 128, 255, cv2.THRESH_BINARY)
cv2.imwrite("binary_image.jpg", binary)
```
Run the script:  
```sh
python3 process_image.py
```

---

#### Apply Smoothing (Blur)  
Modify `process_image.py`:  
```python
blurred = cv2.GaussianBlur(gray, (5, 5), 0)
cv2.imwrite("blurred_image.jpg", blurred)
```
Run the script:  
```sh
python3 process_image.py
```

---

### Step 6: Automate Dataset Collection  
1. Create a dataset folder:  
   ```sh
   mkdir dataset
   ```
2. Capture multiple images:  
   ```sh
   for i in {1..10}; do fswebcam -r 640x480 --jpeg 85 dataset/image_$i.jpg; sleep 2; done
   ```
3. Process all images:  
   ```sh
   nano batch_process.py
   ```
   Paste the following code:  
   ```python
   import cv2, os

   files = os.listdir("dataset")
   for file in files:
       img = cv2.imread(f"dataset/{file}")
       gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
       cv2.imwrite(f"dataset/gray_{file}", gray)

   print("All images converted to grayscale and saved in the dataset folder.")
   ```
   Run the script:  
   ```sh
   python3 batch_process.py
   ```

---

### Step 7: Deactivate Virtual Environment  
To exit the virtual environment:  
```sh
deactivate
```
To reactivate later:  
```sh
source venv/bin/activate
```

---

#Errors and fixes
##Here's the solution if the camera test doesn't work properly

### 1. **Check Webcam Connection**  
Ensure that the webcam is properly connected to your Raspberry Pi and recognized by the system.

- Run `lsusb` to verify that the webcam is detected.
- Check the video device by running `v4l2-ctl --list-devices`. You should see something like `/dev/video0` listed as a device.

### 2. **Check Permissions**  
Sometimes, permission issues can prevent access to the webcam.

- Ensure the user has access to the `/dev/video0` device. Run:
  ```sh
  sudo usermod -aG video $(whoami)
  ```
  Then, log out and log back in for the changes to take effect.

### 3. **Test with `v4l2-ctl`**  
Try capturing an image using `v4l2-ctl` to ensure the webcam is functioning properly.

- Run this command to capture a frame:
  ```sh
  v4l2-ctl --device=/dev/video0 --capture=1 --file=test_image.jpg
  ```
  This will check if the webcam can capture an image through the Video4Linux2 interface.

### 4. **Update Webcam Drivers**  
Ensure your system has the latest webcam drivers. You can update the system with:

```sh
sudo apt update
sudo apt upgrade
```

### 5. **Try Lowering Resolution**  
The `fswebcam` command might fail if the resolution is too high for the webcam or Pi's processing power. Try capturing at a lower resolution:

```sh
fswebcam -r 320x240 --jpeg 85 test_image.jpg
```

### 6. **Use a Different Webcam Software**  
If `fswebcam` continues to have issues, you can try using other tools like `mplayer` or `ffmpeg` to capture images or video from the webcam.

```sh
ffmpeg -f v4l2 -i /dev/video0 -vframes 1 test_image.jpg
```

### 7. **Check for Conflicting Applications**  
Make sure no other applications (e.g., video conferencing apps) are using the webcam, as this can block access for other programs like `fswebcam`.

## [Note: copy the error message and ask Chatgpt for detailed solution of your problem]
