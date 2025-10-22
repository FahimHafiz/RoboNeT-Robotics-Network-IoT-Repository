# UNITED INTERNATIONAL UNIVERSITY (UIU)  
## Dept. of Computer Science & Engineering  

## Experiment: Setting Up and Testing a USB Webcam on Raspberry Pi 4B (Ubuntu)  

### Objective  
- Install and configure a USB webcam on Raspberry Pi 4B.  
- Verify webcam detection and supported formats.  
- Capture images using `fswebcam`.  
- Optimize settings for better image quality.  

---  

## Steps  

### Step 1: Install Required Packages  
1. Open the terminal (`Ctrl + Alt + T`).  
2. Update and install necessary packages:  
   ```sh  
   sudo apt update && sudo apt upgrade -y  
   sudo apt install fswebcam v4l-utils -y  
   ```  

---  

### Step 2: Verify Webcam Detection  
1. Check if the webcam is detected by listing connected USB devices:  
   ```sh  
   lsusb  
   ```  
2. Get detailed USB device information:  
   ```sh  
   usb-devices  
   ```  
3. List available video devices:  
   ```sh  
   v4l2-ctl --list-devices  
   ```  

---  

### Step 3: Ensure Proper Permissions  
1. Add the current user to the `video` group for webcam access:  
   ```sh  
   sudo usermod -aG video $(whoami)  
   ```  
2. Log out and log back in for changes to take effect.  

---  

### Step 4: Check Supported Video Formats  
1. List supported formats, resolutions, and frame rates:  
   ```sh  
   v4l2-ctl --list-formats-ext | more  
   ```  

---  

### Step 5: Capture an Image Using `fswebcam`  
1. Take an image at 1920x1080 resolution using the `YUYV` pixel format:  
   ```sh  
   fswebcam -r 1920x1080 -p YUYV test.jpg  
   ```  
2. Capture an image with additional optimizations:  
   - `-S 60`: Skip the first 60 frames (useful for better quality).  
   - `-D 2`: Delay capture by 2 seconds.  
   - `-F 2`: Capture two frames and use the second for better quality.  
   
   ```sh  
   fswebcam -r 1920x1080 -p YUYV -S 60 -D 2 -F 2 test.jpg  
   ```  

---  

### Step 6: View the Captured Image  
1. Open the captured image using the default image viewer:  
   ```sh  
   xdg-open test.jpg  
   ```  

---  

For Help regarding this experiment, follow this: [Link](https://youtu.be/_uVaZalaSbI?si=DrInA56fHJvOdKZl)  or [this link](https://youtu.be/QBvEuhQ8t1k?si=KI4VZy2TsJaRvkqn)

### Conclusion  
By following these steps, you have successfully installed and configured a USB webcam on Raspberry Pi 4B, verified its detection, checked supported formats, and captured high-quality images using `fswebcam`. You can further extend this by recording videos or integrating the webcam into other applications like OpenCV.  

