# Experiment: Enable and use SSH on Raspberry Pi for secure remote access.

**Objective:** To enable and use SSH on Raspberry Pi for secure remote access and file transfers.

**What You Need**

* Raspberry Pi with Raspbian OS installed and connected to the same network as your computer.
* Another device (PC, laptop, or smartphone) for SSH access.
* (Optional) Software like PuTTY (for Windows) or Terminal (for macOS/Linux).

**Step 1: Enable SSH on Raspberry Pi**

1. **Open Raspberry Pi Configuration Tool:**

   * **Desktop Interface:** Go to: `Menu → Preferences → Raspberry Pi Configuration → Interfaces → Enable SSH`.
   * **Terminal:**
     ```bash
     sudo raspi-config
     ```
     Navigate to: `Interfacing Options → SSH → Enable`.

2. **Restart SSH service (optional):**

   ```bash
   sudo systemctl restart ssh
   ```

3. **Check SSH Status:**

   Verify SSH is running:

   ```bash
   sudo systemctl status ssh
   ```

   If active, you’ll see a message like “active (running)”.

**Step 2: Find Your Raspberry Pi’s IP Address**

Run the following command to find the IP address:

```bash
hostname -I
```

Example output: `192.168.1.100`.

**Step 3: Connect to Raspberry Pi via SSH**

**A. From Linux/macOS Terminal**

1. Open the terminal on your computer.

2. Use the `ssh` command to connect:

   ```bash
   ssh pi@<Raspberry-Pi-IP>
   ```

   Example:

   ```bash
   ssh pi@192.168.1.100
   ```

3. Enter the Raspberry Pi’s password when prompted (default: `raspberry` if unchanged).

**B. From Windows Using PuTTY**

1. Download and install PuTTY from [https://www.putty.org/](https://www.putty.org/).

2. Open PuTTY and enter:

   * Host Name (or IP address): Your Raspberry Pi’s IP (e.g., `192.168.1.100`).
   * Port: `22` (default for SSH).

3. Click `Open`.

4. Enter your Raspberry Pi username (default: `pi`) and password.

**Step 4: Transfer Files Using SSH**

**A. Using `scp` Command (Linux/macOS)**

1. **Transfer file from PC to Raspberry Pi:**

   ```bash
   scp /path/to/local/file pi@<Raspberry-Pi-IP>:/home/pi/
   ```

   Example:

   ```bash
   scp mydocument.txt pi@192.168.1.100:/home/pi/
   ```

2. **Transfer file from Raspberry Pi to PC:**

   ```bash
   scp pi@<Raspberry-Pi-IP>:/path/to/remote/file /path/to/local/destination/
   ```

   Example:

   ```bash
   scp pi@192.168.1.100:/home/pi/mydocument.txt ./
   ```

**B. Using FileZilla (Cross-Platform GUI Tool)**

1. Download FileZilla from [https://filezilla-project.org/](https://filezilla-project.org/).

2. Open FileZilla and set up the connection:

   * Host: `sftp://<Raspberry-Pi-IP>` (e.g., `sftp://192.168.1.100`).
   * Username: `pi`.
   * Password: `raspberry` (or your custom password).
   * Port: `22`.

3. Click `Quickconnect` to browse and transfer files.

**Further Exploration**

* **Automate File Transfers:** Use tools like `rsync` for automated and efficient file transfers.
* **Use SSH for Remote Desktop:** Install VNC Viewer or X11 Forwarding to control Raspberry Pi’s desktop environment via SSH.
* **Explore SFTP:** Use SFTP (Secure File Transfer Protocol) to manage files via SSH.
* **Try SSH Keys:** Set up SSH keys for passwordless login, which is more secure.
