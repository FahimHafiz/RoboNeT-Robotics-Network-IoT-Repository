# **Set Up USB Camera for OpenCV on Raspberry Pi (Ubuntu)**

This guide shows how to set up a USB camera for your OpenCV projects on a Raspberry Pi 4 or 5 running **Ubuntu**. While OpenCV works with the official ribbon-cable cameras, USB webcams are often easier to use for beginners and offer plug-and-play compatibility.

## **Prerequisites**

Before proceeding, ensure you have:

* A Raspberry Pi 4 or 5 board.  
* A standard USB Webcam (e.g., Logitech C920, C270, or generic).  
* **OS:** Ubuntu Server or Desktop (22.04 or 24.04) installed and running.  
* **Software:** OpenCV installed (we will cover the quick install below).

---

## **Step 1: Install Essential Tools & OpenCV**

Unlike Raspberry Pi OS, Ubuntu does not come with video device tools pre-installed. You need to install them manually to find your camera.

Open your terminal and run:

```  
# Update system package list  
sudo apt update

#Install video tools (for v4l2-ctl) and OpenCV  
sudo apt install -y v4l-utils python3-opencv
```
---

## **Step 2: Configure User Permissions (Crucial for Ubuntu)**

On Ubuntu, your default user is not automatically part of the "video" group. This prevents your scripts from accessing the camera.

Add your user to the video group:  
``` 
sudo usermod -aG video $USER
```


**Action Required:** You must **Log Out and Log Back In** (or reboot) for this change to take effect.  
```  
sudo reboot
```
 

---

## **Step 3: List Your USB Devices**

Once your Pi is back online, connect your USB camera. Now, let's identify it.

Run the following command to list all video devices:

```
v4l2-ctl --list-devices
```
**Expected Output:** You will see output similar to this:

``` 
HD Pro Webcam C920 (usb-0000:01:00.0-1.3):  
    /dev/video0  
    /dev/video1
```
* **Understanding the Output:** Even though multiple lines might appear (`/dev/video0`, `/dev/video1`), the camera ID is usually the **lowest number**.  
* In this case, our Camera ID is **0** (from `/dev/video0`).

---

## **Step 4: Python Script (OpenCV Test)**

We will create a simple Python script to stream video from the camera.

Create a new file:  
```  
nano opencv_test_usb_camera.py
```
 
1. Copy and paste the following code:

```python
import cv2

# Initialize Video Capture  
# Change '0' to '1' or '2' if your camera is not detected  
camera_id = 0  
video_capture = cv2.VideoCapture(camera_id)

if not video_capture.isOpened():  
    print("Error: Could not open video device.")  
    exit()

print("Camera active. Press 'q' to quit.")

while True:  
    # Read frames from the video  
    result, video_frame = video_capture.read()  
      
    # Terminate the loop if the frame is not read successfully  
    if result is False:  
        print("Error: Failed to capture frame.")  
        break

    # Display the frame  
    # NOTE: This requires a Desktop/Monitor.   
    # If using SSH only, this line will fail.  
    cv2.imshow("USB Camera Test", video_frame)

    # Stop loop when 'q' is pressed  
    if cv2.waitKey(1) & 0xFF == ord("q"):  
        break

video_capture.release()  
cv2.destroyAllWindows()
```
3. Save the file: Press `Ctrl+X`, then `Y`, then `Enter`.

---

## **Step 5: Run the Script**

Execute the script using Python 3:

``` 
python3 opencv_test_usb_camera.py
```
If you are using a Desktop environment (a monitor plugged into the Pi), a window should pop up showing the live video feed. Press **q** to close it.

---

## **Troubleshooting**

### **1\. "Permission Denied" or Camera fails to open**

* **Cause:** You likely skipped Step 2\.  
* **Fix:** Run `sudo usermod -aG video $USER` and then **reboot** your Pi.

### **2\. "qt.qpa.plugin: Could not load the Qt platform plugin 'xcb'"(SSH Mode)**

* **Cause:** You are running this via SSH (Headless) without a monitor. OpenCV cannot open a window (`cv2.imshow`) inside a text-only terminal.  
* **Fix:** You must either connect a monitor to the Pi or modify the code to save the image (`cv2.imwrite`) instead of showing it (`cv2.imshow`).

### **3\. Wrong Camera ID**

* **Cause:** Sometimes `/dev/video0` is taken by a system dummy device.  
* **Fix:** Try changing the line `camera_id = 0` to `camera_id = 1` or `camera_id = 2` in the Python script.

