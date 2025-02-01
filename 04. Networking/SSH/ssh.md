##Experiment: Enable and use SSH on Raspberry Pi for secure remote access.

Objective: To enable and use SSH on Raspberry Pi for secure remote access and file transfers.

What You Need
Raspberry Pi with Raspbian OS installed and connected to the same network as your computer.
Another device (PC, laptop, or smartphone) for SSH access.
(Optional) Software like PuTTY (for Windows) or Terminal (for macOS/Linux).

Step 1: Enable SSH on Raspberry Pi
1. Open Raspberry Pi Configuration Tool:
If using the desktop interface, go to:
 Menu → Preferences → Raspberry Pi Configuration → Interfaces → Enable SSH.
If using the terminal:
    sudo raspi-config
 Navigate to:
 Interfacing Options → SSH → Enable.


2. Restart SSH service (optional):
   sudo systemctl retart ssh

3. Check SSH Status:
   sudo systemctl status ssh

 Verify SSH is running:





If active, you’ll see a message like “active (running)”.

Step 2: Find Your Raspberry Pi’s IP Address

Run the following command to find the IP address:

  hostname -I

Example output: 192.168.1.100.

Step 3: Connect to Raspberry Pi via SSH
A. From Linux/macOS Terminal
Open the terminal on your computer.
Use the ssh command to connect:

 ssh pi@<Raspberry-Pi-IP>

2. Enter the Raspberry Pi’s password when prompted (default: raspberry if unchanged).
B. From Windows Using PuTTY
Download and install PuTTY from https://www.putty.org/.

2. Open PuTTY and enter:
Host Name (or IP address): Your Raspberry Pi’s IP (e.g., 192.168.1.100).
Port: 22 (default for SSH).
3. Click Open.
Enter your Raspberry Pi username (default: pi) and password.

Step 4: Transfer Files Using SSH
A. Using scp Command (Linux/macOS)
Transfer file from PC to Raspberry Pi:

 scp /path/to/local/file pi@<Raspberry-Pi-IP>:/home/pi/


Transfer file from Raspberry Pi to PC:


B. Using FileZilla (Cross-Platform GUI Tool)
Download FileZilla from https://filezilla-project.org/.
Open FileZilla and set up the connection:
Host: sftp://<Raspberry-Pi-IP> (e.g., sftp://192.168.1.100).
Username: pi.
Password: raspberry (or your custom password).
Port: 22.
Click Quickconnect to browse and transfer files.

Further Exploration
Automate File Transfers: Use tools like rsync for automated and efficient file transfers.
Use SSH for Remote Desktop: Install VNC Viewer or X11 Forwarding to control Raspberry Pi’s desktop environment via SSH.
Explore SFTP: Use SFTP (Secure File Transfer Protocol) to manage files via SSH.
Try Secure SSH

