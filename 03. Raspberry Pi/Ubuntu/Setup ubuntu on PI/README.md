# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Installing Ubuntu 22.04 on Raspberry Pi

### Objective
To install and configure Ubuntu 22.04 on a Raspberry Pi 4 using Raspberry Pi Imager. This includes downloading the OS, flashing it onto an SD card, and performing the initial setup to ensure the system is ready for further development and experimentation.

### Step 1: Download Raspberry Pi Imager
1. Visit the official Raspberry Pi website and download **[Raspberry Pi Imager](https://www.raspberrypi.com/software/)** for your operating system (Windows, macOS, or Linux).
2. Install Raspberry Pi Imager by opening the downloaded file and following the installation prompts.

### Step 2: Prepare the SD Card
1. Insert a blank microSD card (at least **16GB**) into your computer using an SD card reader.
2. Launch Raspberry Pi Imager on your computer.
3. Select your Raspberry Pi device:
   - Click **"Choose Device"** and select **"Raspberry Pi 4"** (or another model if applicable).
4. Select storage:
   - Click **"Choose Storage"** and select the microSD card you inserted earlier.
5. Choose OS:
   - Click **"Choose OS"**, then navigate to **"Other general-purpose OS" > "Ubuntu" > "Ubuntu 22.04 LTS (64-bit)"**.
6. Click **"Next"** and configure the settings if needed (Wi-Fi, username, password, etc.).
7. Click **"Write"** to start the installation process. The OS will be written and verified automatically.
8. Once finished, safely eject the SD card from your computer.

### Step 3: Insert SD Card into Raspberry Pi
1. Insert the SD card into the **microSD slot** of your Raspberry Pi.
2. Connect the necessary peripherals:
   - **Keyboard**
   - **Mouse**
   - **Monitor (HDMI cable)**
   - **Power supply**

### Step 4: First Boot Setup
1. Power on the Raspberry Pi by connecting the power supply.
2. The system will boot into Ubuntu's setup process.
3. Follow the on-screen instructions:
   - Select **language** and **keyboard layout**.
   - Set up **Wi-Fi** (if applicable).
   - Create a **user account** (username and password).
   - Wait for Ubuntu to complete the initial configuration.
4. Restart the Raspberry Pi to apply the settings.

### Step 5: Update and Verify Installation
1. Open the terminal and update the system:
   ```sh
   sudo apt update && sudo apt upgrade -y
   ```
2. Verify Ubuntu version:
   ```sh
   lsb_release -a
   ```
3. If needed, install additional utilities:
   ```sh
   sudo apt install -y net-tools vim git
   ```

### Completion
After completing the above steps, your Raspberry Pi is now running **Ubuntu 22.04 LTS**. You can now proceed with additional configurations and software installations based on your project requirements.

