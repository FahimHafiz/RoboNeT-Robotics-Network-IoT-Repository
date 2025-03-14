# UNITED INTERNATIONAL UNIVERSITY (UIU)  
## Dept. of Computer Science & Engineering  

## Experiment: Capturing and Processing Images Using a USB Webcam on Raspberry Pi 4B (Ubuntu)  

### Objective  
- Capture and save images using a USB webcam.  
- Record videos using a webcam.  
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
