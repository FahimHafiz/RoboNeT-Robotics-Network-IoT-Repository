# **Programming with Python and GPIO**

This is where the real fun begins. In this chapter, you'll learn how to write simple Python programs and use them to control and read from the Raspberry Pi's General Purpose Input/Output (GPIO) pins. This is the foundation of all IoT projects.

## **4.1 "Hello, World\!" in Python**

Python is a beginner-friendly programming language that's perfect for the Raspberry Pi. Ubuntu comes with Python pre-installed. Let's write your first script.

1. **Open your Terminal** .

In your home directory, let's create a new folder for our projects:  
mkdir Projects

2. Move into that new directory: 
   ```
   cd Projects  
   ```
3. Use `nano` to create a new Python file. We'll call it `hello.py`.  
   ```
   nano hello.py  
   ```
4. In the `nano` editor, type the following single line of code: 
   ```
   print("Hello, World! This is my Raspberry Pi.") 
   ``` 
   **![][image2]**

5.  **Save and exit** `nano`:  
   * Press `Ctrl + S` to save.  
   * Press `Ctrl + X` to exit.  

Now, run your script using the `python3` command:
``` 
python3 hello.py
```
6. You should see your message printed to the terminal. **Congratulations**, you're a **Python** programmer xD\!

#### 

## **4.2 Understanding the GPIO Pins**

The **GPIO** pins are a **40-pin** header on your **Raspberry Pi** that allows it to talk to other hardware, like LEDs, sensors, and motors.
**![][image1]**
Here's what you need to know:

* **GPIO:** These are the "**general purpose**" pins you can control. They can be set as an **output** (to send a signal, like turning on an LED) or an **input** (to read a signal, like a button press).  
* **VCC (Power):** The pins provide 3.3 volts (`3V3`) and 5 volts (`5V`). These are used to provide power to your electronic components. **Warning: Never connect a 5V pin directly to a 3V3 pin or a GPIO pin, as this can permanently damage your Pi.**  
* **GND (Ground):** These are the ground pins. Any circuit you build must be connected to a GND pin to complete the circuit.

## **4.3 Installing the Necessary Python Library**

To control the GPIO pins easily with Python, we need to install a library. The most common one is `RPi.GPIO`.

1. Open your **Terminal**.

Install the library using **`apt`**. Remember from Chapter 4, we need to use **`sudo`** to install software:
```  
sudo apt update
```
```
sudo apt install python3-rpi.gpio
```

2. This will download and install the library. You're now ready to build circuits.

---

## **Projects**

Now that you have the basics down, it's time to build some hands-on projects:

1. **[Project 1: Blinking an LED](Blinking%20an%20LED.md)** - Learn to control GPIO output pins by making an LED blink.

2. **[Project 2: Reading a Sensor (Push Button)](Reading%20a%20Sensor%20%28Push%20Button%29.md)** - Learn to read GPIO input pins by detecting button presses.

3. **[Project 3: Raspberry Pi - DHT11/DHT22 Temperature and Humidity](Raspberry%20Pi-%20DHT11_DHT22%20Temperature%20and%20Humidity.md)** - Read temperature and humidity data from DHT sensors.

---

### Next Chapter

➡️ **[Basic Networking and Remote Access (SSH)](../05.Basic%20Networking%20and%20Remote%20Access%20%28SSH%29/README.md)**


[image1]: <../assets/root/image2.png>
[image2]: <../assets/04-programming-with-python-and-gpio/hello.png>







