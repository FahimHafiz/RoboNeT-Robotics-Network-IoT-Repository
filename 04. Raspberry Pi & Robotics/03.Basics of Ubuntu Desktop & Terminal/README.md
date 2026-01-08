# **Basics of Ubuntu Desktop & Terminal**

Welcome to your new Ubuntu desktop\! Now that the operating system is installed, this chapter will help you get comfortable with the visual interface (the "desktop") and the powerful command-line interface (the "terminal").

#### **3.1 Navigating the Desktop**

![][image1]

The Ubuntu desktop (which uses an interface called "GNOME") is clean and easy to use. Here are the main parts you'll interact with:

1. **The Activities Bar (The "Dock"):** This is the vertical bar on the left side of your screen. It holds your favorite applications and shows which ones are currently running (indicated by a small dot).  
   * **Clicking an icon** will launch the app or bring it into focus.  
   * The **"Show Applications" icon** (a 3x3 grid of dots at the bottom) will open a full list of all software installed on your Pi.  
2. **The Top Bar:** This horizontal bar at the top of the screen provides status information.  
   * **Activities (Top Left):** Clicking this (or pressing the `Super` key \- the Windows or Command key on your keyboard) will show you all open windows, allowing you to switch between them easily.  
   * **System Menu (Top Right):** This is where you control volume, Wi-Fi, Bluetooth, and, most importantly, **Power Off / Restart** your Raspberry Pi.  
3. **Finding Files:** Click the "Files" icon (looks like a filing cabinet) on the Activities Bar. This will open the file manager, where you can browse your `Documents`, `Downloads`, `Pictures`, etc., just like on Windows or macOS.  
4. **Finding Applications:** Click the 9-dot "Show Applications" icon at the bottom of the Dock. You can then type the name of any app you're looking for, such as `Firefox` (your web browser) or `Terminal`.

## **3.2 Introduction to the Linux Terminal**

While the desktop is great for many tasks, the **Terminal** (also called the "command line") is the most powerful tool in Linux. It allows you to run commands, install software, and configure your system by typing text. For IoT projects, using the terminal is essential.

**Why is it so powerful?**

* **Direct Control:** You are giving precise, direct instructions to the computer.  
* **Automation:** You can write scripts to perform complex, repetitive tasks.  
* **Remote Access:** As you'll see in Chapter 6, the terminal is how you will remotely log in to your Pi (using SSH) without needing a monitor.

**How to open the Terminal:**

1. Click the "**Show Applications**" icon (9 dots) at the bottom of the Dock.  
2. Type `Terminal` and click the icon that appears.  
3. **Pro-Tip:** Right-click the **Terminal** icon in your Dock and select "Add to Favorites." This will keep it there for easy access.

You will now see a window with a blinking cursor, ready for your commands.

## **3.3 Essential Commands for Beginners**

A command is made up of a program's name followed by *options* or *arguments*. Let's learn the five most important ones.

Type each of these into your terminal and press `Enter` to see what they do.

**1\. `pwd` (Print Working Directory)**

* **What it does:** Tells you which directory (folder) you are currently in. When you first open the terminal, you are in your "home" directory.

**Example:**  
```
pwd
```

* *Output:* `/home/yourusername`

**2\. `ls` (List)**

* **What it does:** Lists all the files and directories inside your current directory.

**Example:**  
```
ls
```
* *Output:* `Desktop Documents Downloads Music Pictures Videos`

**3\. `cd` (Change Directory)**

* **What it does:** Moves you into a different directory.

**Example:** Let's move into the `Documents` directory.
```
cd Documents
```
* **Try it:** Type `pwd` again. You'll see your location has changed. To go back up to the parent directory, type `cd ..`

**4\. `nano` (Text Editor)**

* **What it does:** A simple, easy-to-use text editor that runs inside the terminal. This is how we will write our Python code.

**Example:** Let's create a file named `test.txt`.
```
nano test.txt
```
* This will open a full-screen editor. Type "**Hello World\!**" into it.  
* To save and exit:  
  1. Press `Ctrl + X` (to Exit).  
  2. It will ask "Save modified buffer?". Press `Y` (for Yes).  
  3. It will ask "File Name to Write: test.txt". Press `Enter` to confirm.  
* You're now back at the command line. Type `ls` to see your new file\!

**5\. `sudo` (SuperUser Do)**

* **What it does:** This is the most important command. It stands for "SuperUser Do" and allows you to run a command with administrator (or "root") privileges. You **must** use `sudo` for tasks like installing software or changing system files.  
* **Example:** You can't install software without it. (We'll use this in the next section).

#### 

## **3.4 Keeping Your System Updated**

Just like Windows or macOS, your Ubuntu system receives security patches and software updates. It's crucial to keep your system updated. We do this using a tool called `apt` (Advanced Package Tool), and we must use `sudo` to run it.

---


There are two steps:

**Step 1: `sudo apt update`**

* This command doesn't *install* anything. It just contacts the Ubuntu software servers and **fetches the latest list** of available software and updates.

Type this in your terminal:
``` 
sudo apt update
```
It will ask for your password. This is the same **password** you use to log in to the desktop. **You will not see the cursor move as you type.** This is a security feature. Press `Enter` when you're done.

**Step 2: `sudo apt upgrade`**

* After the "update" is complete, this command will **install** all the new updates.

Type this in your terminal:
```
sudo apt upgrade
```
* It will show you a list of all the packages to be upgraded and ask "D**o you want to continue? \[Y/n\]**".  
* Press **`Y`** and then **`Enter`.**  
* This may take 10-20 minutes as it downloads and installs all the updates.

You should run these two commands regularly (once a week or so) to keep your Raspberry Pi secure and up-to-date.



### Next Chapter

➡️ **[Programming with Python and GPIO](../04.Programming%20with%20Python%20and%20GPIO/README.md)**

[image1]: <../assets/03-basics-of-ubuntu-desktop-terminal/image1.png>