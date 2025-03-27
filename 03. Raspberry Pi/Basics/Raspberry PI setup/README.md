# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Introduction to Raspberry Pi

### Objective
To set up and configure a Raspberry Pi 4 with the necessary software and hardware to enable seamless camera functionality. This includes verifying the camera module, testing image and video capture, and ensuring the system is optimized for future image processing and object detection tasks.

### Step 1: Download Raspberry Pi OS using Raspberry Pi Imager
1. Go to the official Raspberry Pi website and download [Raspberry Pi Imager](https://www.raspberrypi.com/software/) for your operating system (Windows, macOS, or Linux).
2. Install Raspberry Pi Imager by opening the downloaded file and following the installation prompts.

### Step 2: Prepare the SD Card
1. Insert a blank microSD card (at least 8GB) into your computer using an SD card reader.
2. Launch Raspberry Pi Imager on your computer.
3. Select your Raspberry Pi device:
   - Click **"Choose Device"** and select **"Raspberry Pi 4"** (or another model if applicable).
4. Select storage:
   - Click **"Choose Storage"** and select the microSD card you inserted earlier.
5. Choose OS:
   - Select the **64-bit version** of Raspberry Pi OS from the list of available operating systems.
6. Click **"Next"** and choose **"No"** for the additional configuration option.
7. Click **"Write"** to start the installation process. The OS will be written and verified automatically.
8. Once finished, safely eject the SD card from your computer.

### Step 3: Insert SD Card into Raspberry Pi
1. Insert the SD card into the microSD slot of your Raspberry Pi.
2. Connect the necessary peripherals:
   - **Keyboard**
   - **Mouse**
   - **Monitor (HDMI cable)**
   - **Power supply**

### Step 4: First Boot Setup
1. Power on the Raspberry Pi by connecting the power supply.
2. Follow the on-screen instructions to complete the initial setup:
   - Select **language** and **keyboard layout**.
   - Connect to **Wi-Fi**.
   - **Update software** if prompted.
3. Restart the Raspberry Pi to apply the settings.

### Step 5: Verify Camera Module
1. Open the terminal and enable the camera module:
   ```sh
   sudo raspi-config
   ```
2. Navigate to **Interface Options > Camera** and enable it.
3. Reboot your Raspberry Pi:
   ```sh
   sudo reboot
   ```
4. Test the camera by running:
   ```sh
   libcamera-hello
   ```

### Completion
After completing the above steps, your Raspberry Pi is ready for use with the Raspberry Pi OS installed. You can now proceed with additional configurations, such as setting up the camera for image processing and object detection.

