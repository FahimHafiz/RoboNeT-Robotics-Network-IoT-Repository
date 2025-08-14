# Experiment: Introduction to VNC Protocol on Raspberry Pi

**Objective:** To enable and use the VNC protocol on Raspberry Pi for remote desktop access.

**What You Need**

* Raspberry Pi with Raspbian OS installed and connected to the same network as your computer.
* Another device (PC, laptop, or smartphone) to connect to the Raspberry Pi remotely.
* (Optional) VNC Viewer software installed on the remote device.

**Step 1: Enable VNC on Raspberry Pi**

1. **Open Raspberry Pi Configuration Tool:**

   * **Desktop Interface:** Go to: `Menu → Preferences → Raspberry Pi Configuration → Interfaces → Enable VNC`.
   * **Terminal:**
     ```bash
     sudo raspi-config
     ```
     Navigate to: `Interfacing Options → VNC → Enable`.

2. **Restart VNC service (optional):**

   ```bash
   sudo systemctl restart vncserver-x11-serviced.service
   ```

**Step 2: Find Your Raspberry Pi’s IP Address**

Run the following command to find the IP address:

```bash
hostname -I
```

Example output: `192.168.1.100`.

**Step 3: Install VNC Viewer on Your Computer**

1. Download VNC Viewer from [https://www.realvnc.com/](https://www.realvnc.com/) and install it on your computer or smartphone.

2. Open VNC Viewer and enter your Raspberry Pi’s IP address (e.g., `192.168.1.100`) in the Address bar.

**Step 4: Connect to Raspberry Pi**

When prompted, enter your Raspberry Pi’s login credentials:

* Username: `pi` (default).
* Password: `raspberry` (default, or your custom password).

Once connected, you will see the Raspberry Pi’s desktop interface.

**Step 5: Use VNC for Remote Access**

1. **Control Your Raspberry Pi Remotely:** Interact with the Raspberry Pi’s desktop as if you were directly using it.

2. **Transfer Files:** Use the VNC Viewer file transfer option to send or receive files between your computer and Raspberry Pi.

**Further Exploration**

* **Secure VNC Connection:** Use a strong password by changing the Raspberry Pi password.  Consider setting up SSH tunneling for a more secure connection.
* **Access VNC Over the Internet:** Set up port forwarding on your router for remote access outside your local network.  Be *very* careful when doing this and consider the security implications.  A VPN is a much better approach.
* **Explore Advanced Features:**
    * Screen recording.
    * Multiple user sessions.
