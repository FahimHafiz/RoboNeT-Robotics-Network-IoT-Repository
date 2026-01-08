# **Basic Networking and Remote Access (SSH)**

Now that your Raspberry Pi is running projects, you probably don't want to leave a full keyboard, mouse, and monitor attached to it forever. This is where networking comes in. In this chapter, you'll learn how to find your Pi on the network and control it remotely from your main computer.

## **5.1 Checking Your Connection**

Before you can connect *to* your Pi, you need to know its address. On a network, this is called an **IP Address** (Internet Protocol address). Each device on your Wi-Fi or wired network has a unique one (e.g., `192.168.1.14`).

### How to Find Your Pi's IP Address (Method 1: Desktop)

1. On your Ubuntu desktop, click the **System Menu** in the top-right corner.  
2. Click on "Wired Settings" or "Wi-Fi" (whichever you are using).  
3. Click the settings cog next to your active connection.  
4. A window will pop up. Your IP address will be listed as "IPv4 Address".

### How to Find Your Pi's IP Address (Method 2: Terminal)

This is a faster and more reliable method.

1. Open your **Terminal**.

Type the following command and press `Enter`:
```
ip addr show
```
2. This will show a lot of text. Look for your connection (e.g., `eth0` for wired/Ethernet or `wlan0` for Wi-Fi).  
3. Under the `inet` field, you will see your IP address.

**If you need help, here’s how to [find the current IP address of Raspberry Pi](https://raspberrytips.com/find-current-ip-raspberry-pi/).**



### Using `ping` to Check Your Connection

The `ping` command is a simple network tool that sends a small packet to another device to see if it responds. It's like a submarine's sonar.

1. Open your **Terminal**.

Let's see if you can reach Google. Type:
```
ping google.com
```
2. If you have an internet connection, you will see replies coming back, showing you the response time.  
3. To stop `ping`, press `Ctrl + C`.

## **5.2 Remote Access with SSH**

**What is SSH?**

SSH stands for **Secure Shell**. It is a protocol that allows you to open a secure terminal connection to another computer over a network.

This means you can have your Raspberry Pi sitting in a corner with only its power cable connected, and you can control it completely (run scripts, install software, shut it down) from the terminal of your main Windows, macOS, or Linux computer. This is called running "headless."

### How to Enable SSH on Ubuntu Desktop

For security, the SSH server is not installed by default on Ubuntu Desktop. We must install and enable it.

1. Open a **Terminal** on your Raspberry Pi.

First, make sure your package lists are updated:
```
sudo apt update
```
Next, install the SSH server software:
```
sudo apt install openssh-server
```
* Press `Y` and `Enter` if it asks for confirmation.

Once installed, the SSH service should start automatically. 

You can check its status with:
```
sudo systemctl status ssh
```
![][image1]

* As long as you see "**active (running)**" in green, you are good to go.  
  * (If it's not running, you can start it with `sudo systemctl start ssh`).

Your Raspberry Pi is now ready to accept SSH connections.

*If not automatically started. Enable SSH :*
```
sudo systemctl enable ssh
```
**How to Connect to Your Pi via SSH**

You will need two pieces of information:

* Your Pi's **username** (e.g., `pi`)  
* Your Pi's **IP Address** (e.g., `192.168.1.14`)

### From a Windows Computer

You can use the built-in PowerShell or Command Prompt.

1. Open your Start Menu and type `PowerShell` or `cmd`.

In the terminal window, type the following command, replacing `yourusername` and `<your-pi-ip-address>` with your own:

ssh yourusername@\<your-pi-ip-address\>

* **Example:** `ssh pi@192.168.1.14`

### **Using Third-part GUI app(Putty) in Windows**

If you use Windows on your main PC, you will probably install and use a third-party tool to use SSH, like [Termius](https://termius.com/) or [Putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html), for example.

On Windows 11, the *ssh* command is available from the command prompt, but it’s bare bones. Full client programs like Termius or Putty are often better.

**Putty is one of the most used software programs to access SSH hosts on Windows**, and if you start it will be perfect. Download the file matching your computer specifications. And depending on the version chosen, install it or not (there is a portable edition), then launch it.

Putty looks like this:

![][image2]

To log in, type the IP address in the “Host Name” field and click on “Open”.

**From a macOS or Linux Computer:**

1. Open the **Terminal** application.

Type the same command, replacing with your details:

ssh yourusername@\<your-pi-ip-address\>

* **Example:** `ssh pi@192.168.1.14`

### Your First Connection

The very first time you connect, you will see a security message like this:

![][image3] 


This is completely normal. Your computer is just asking you to verify that this is a new device you trust.

1. Type `yes` and press `Enter`.  
2. It will now ask for your password. This is the password for your user on the **Raspberry Pi**. Type it and press `Enter`. (You will not see the cursor move).

If successful, you will see your Raspberry Pi's command prompt (e.g., `yourusername@ubuntu-pi:~$`).

You are now controlling your Raspberry Pi's terminal from your main computer\! You can run any command, like `ls`, `nano blink.py`, or `sudo apt update`.




---

### Next Chapter

➡️ **[Computer Vision with Raspberry Pi](../06.Computer%20Vision%20with%20Raspberry%20Pi/README.md)**

[image1]: <../assets/05-basic-networking-and-remote-access-ssh/image1.png>

[image2]: <../assets/05-basic-networking-and-remote-access-ssh/image2.png>

[image3]: <../assets/05-basic-networking-and-remote-access-ssh/image3.png>