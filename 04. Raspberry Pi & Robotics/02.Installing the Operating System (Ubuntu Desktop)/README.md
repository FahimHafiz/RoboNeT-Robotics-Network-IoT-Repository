# **Installing the Operating System (Ubuntu Desktop)**

This chapter provides a complete, step-by-step guide to installing the full **Ubuntu Desktop** operating system on your **Raspberry Pi**. We will cover downloading the necessary tools for **Windows**, **macOS**, and **Linux**, and then walk through the entire installation process.

### **2.1 Why Ubuntu?**

While the Raspberry Pi has its own official OS (Raspberry Pi OS), we are using **Ubuntu Desktop** for this guide. Ubuntu is one of the most popular and powerful versions of Linux in the world.

The benefits for us include:

* **Robust & Full-Featured Desktop:** You get a complete, modern desktop experience, similar to what you'd find on a PC.  
* **Strong Community Support:** A massive global community means that if you have a problem, it's very likely someone has already solved it and posted the answer online.  
* **Software Availability:** A wide range of software is readily available and easy to install.

### **2.2 Downloading the Tools**

Before we begin, you only need to download one item to your main computer (your Windows PC, Mac, or Linux machine).

**Tool 1: Raspberry Pi Imager** This is the official and easiest-to-use tool for writing operating systems to an SD card. It works on Windows, macOS, and Linux, and it now **includes the Ubuntu image** we need.

* **Official Download Page:** [**https://www.raspberrypi.com/software/**](https://www.raspberrypi.com/software/)

**For Windows users:**

1. Go to the download page and click the [**"Download for Windows"**](https://downloads.raspberrypi.com/imager/imager_latest.exe) button.  
2. Run the `.exe` file you downloaded.  
3. Follow the installation wizard to install the Imager on your PC.

**For macOS users:**

1. Go to the download page and click the **"[Download for macOS](https://downloads.raspberrypi.com/imager/imager_latest.dmg)"** button.  
2. A `.dmg` file will be downloaded. Open it.  
3. Drag the `Raspberry Pi Imager` icon into your `Applications` folder.

**For Linux users (Ubuntu/Debian-based):**

1. You can download the `.deb` file from the website, but it's much easier to install it from the terminal.  
   * Open your terminal and type the following commands:
    ```
    sudo apt update
    ```
    ```
    sudo apt install rpi-imager  
2. This will install the Imager just like any other application.  
   

## **2.3 Flashing the OS to the microSD Card**

This is the most important step. We will use the Raspberry Pi Imager on your computer to "flash" (write) Ubuntu to your microSD card. The Imager's interface is identical on Windows, macOS, and Linux.

**Insert your microSD card** into your computer's SD card reader. If your computer doesn't have one, you will need a **USB SD card reader**.

**Open the Raspberry Pi Imager** application.

   ![][image1]

Click the **"CHOOSE DEVICE"** button. A list will pop up. Select **"Raspberry Pi 4"**.

   ![][image2]

Click the **"CHOOSE OS"** button.

* A menu will appear. Navigate to:  
  `Other general-purpose OS` \-\> `Ubuntu` \-\> `Ubuntu Desktop 22.04.X LTS (64-bit)`

   ![][image3]`  
  


  Click the **"CHOOSE STORAGE"** button.  
  * A list of connected drives will appear. Carefully select your microSD card.

  **\!\! WARNING \!\!** This process will **ERASE ALL DATA** from the drive you select. Double-check that you have selected the correct microSD card and not a regular hard drive or USB stick.

   ![][image4]
  
   ![][image5]

   Click “**Next**”


  

   A final warning will appear, reminding you that all data will be erased. Click **"YES"** continue.

   ![][image6]


  The Imager will now **download the Ubuntu image** and then write it to the card and verify it. This process can take 10-20 minutes, so be patient.

   ![][image7]

  When it's finished, a message will pop up saying the write was **successful**. You can now close the Imager and safely eject the microSD card from your computer.

#### 

## **2.5 First Boot and Initial Setup**

Your microSD card is now a bootable Ubuntu drive. Let's start with the Pi.

1. Insert the microSD card into the slot on the bottom of your Raspberry Pi.

2. Connect your peripherals in this order:  
   1. Plug your **Micro HDMI cable** into the Pi and your monitor.  
   2. Plug in your **USB keyboard** and **USB mouse**.  
3. **Finally, plug in the USB-C power cable.** The Pi has no power button; it will turn on as soon as you plug it in.  
4. You will see the Raspberry Pi boot screen, followed by the Ubuntu loading screen. The very first boot can take a few minutes as the system configures itself.  
5. You will be greeted by the **Ubuntu Setup Wizard**.  
6. Follow the on-screen steps:  
   1. **Welcome:** Select your language and click "Continue."  
   2. **Keyboard:** Select your keyboard layout and click "Continue."  
   3. **Wireless:** Select your Wi-Fi network and enter the password. This is important for downloading updates.  
   4. **Timezone:** Choose your location on the map and click "Continue."  
   5. **Who are you?:** This is the most important step. Fill in your **name**, a **username**, and a **password**. **Write this down\!** This will be your administrator account.  
7. The system will finish the setup, log you in, and take you to the desktop.

### **Congratulations**\! You have successfully installed a full **Ubuntu Desktop** on your **Raspberry Pi.**



---

### Next Chapter

➡️ **[Basics of Ubuntu Desktop & Terminal](../03.Basics%20of%20Ubuntu%20Desktop%20%26%20Terminal/README.md)**

[image1]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image1.png>

[image2]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image2.png>

[image3]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image3.png>

[image4]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image4.png>

[image5]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image5.png>

[image6]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image6.png>

[image7]: <../assets/02-installing-the-operating-system-ubuntu-desktop/image7.png>