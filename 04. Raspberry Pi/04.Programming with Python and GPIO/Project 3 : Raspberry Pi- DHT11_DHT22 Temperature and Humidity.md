## **4.6 Project 3 : Raspberry Pi: DHT11/DHT22 Temperature and Humidity**

## **DHT Sensor Pinout**

![DHT22 Temperature and Humidity Sensor using Arduino IDE][image2]

The following table shows the DHT22 and DHT11 pinout. When the sensor is facing you, pin numbering starts at 1 from left to right

| DHT pin | Connect to |
| :---- | :---- |
| **1** | 3.3V |
| **2** | Any digital GPIO; also connect a 4.7k Ohm pull-up resistor |
| **3** | Don’t connect |
| **4** | GND |

## **Parts Required**


Here’s a list of parts you need to build the circuit (if you don’t have a DHT breakout board, you need a 4.7kOhm resistor):

* Raspberry Pi board
* DHT11 or DHT22 temperature and humidity sensor  
* 4.7k Ohm resistor 
* Breadboard 
* Jumper wires

## **Wiring the DHT11/DHT22 Sensor to the Raspberry Pi**

Wire the DHT22 or DHT11 sensor to the Raspberry Pi as shown in the following schematic diagram. If you have a DHT breakout board, ignore the resistor.

![Raspberry Pi DHT Sensor Wiring][image4]

In this example, we’re connecting the DHT data pin to GPIO 4. However, you can use any other suitable digital GPIO.

## **Getting DHT11/22 Temperature and Humidity**

There are different ways to get temperature and humidity readings from the DHT11 or DHT22 sensors using the Raspberry Pi with Python. We’ll use the [**Adafruit\_CircuitPython\_DHT**](https://github.com/adafruit/Adafruit_CircuitPython_DHT) Python library.

### **Update your Raspberry Pi**

First, update and upgrade your Raspberry Pi, if any updates are available. Run the following command:
```
sudo apt update && sudo apt upgrade
```
If there’s a need to update, it will ask you if you want to continue. Click **Y** and **Enter** to proceed. You may need to wait a few minutes if it needs to update.

### **Create a Virtual Environment**

We’ll install the DHT library in a virtual environment. Creating a virtual environment will isolate the Python libraries we’re using, in this case, the DHT library, from the rest of the system.

We’ll create our virtual environment on a directory on our *Desktop*. Enter the following command on a Terminal window to move to the Desktop:
```
cd ~/Desktop
```
Create a folder for your project. This is where we’ll create the virtual environment and install the library. We’ll create a folder called *dht\_test*.
```
mkdir dht_test
```
Move to the newly created folder:
```
cd ~/Desktop/dht_test
```
Create a virtual environment for this directory called myenv. This must be the same directory where we’ll install the DHT library. Replace myenv with the desired name for your virtual environment.
```
python3 -m venv myenv
```
Then, you can run the following command to check that the virtual environment is there.
```
ls -l
````
![Create a Virtual Environment Raspberry Pi Python][image5]

Activate the virtual environment:
```
source myenv/bin/activate
```
Your prompt should change to indicate that you are now in the virtual environment.

![Activate Python Virtual Environment][image6]

### **Installing the Adafruit\_CircuitPython\_DHT Library**

Now that we are in our virtual environment, we can install the library. Run the following command:
```
python3 -m pip install adafruit-circuitpython-dht
```
After a few seconds, the library will be installed (ignore any yellow warnings about deprecated packages).

![Installing the Adafruit\_CircuitPython\_DHT Library][image7]

### **Python Code for Raspberry Pi DHT11/DHT22**

```python

# Based on Adafruit_CircuitPython_DHT Library Example

import time

import board

import adafruit_dht

# Sensor data pin is connected to GPIO 4

sensor = adafruit_dht.DHT22(board.D4)

# Uncomment for DHT11

#sensor = adafruit_dht.DHT11(board.D4)

while True:

    try:

        # Print the values to the serial port

        temperature_c = sensor.temperature

        temperature_f = temperature_c * (9 / 5) + 32

        humidity = sensor.humidity

        print("Temp={0:0.1f}ºC, Temp={1:0.1f}ºF, Humidity={2:0.1f}%".format(temperature_c, temperature_f, humidity))

    except RuntimeError as error:

        # Errors happen fairly often, DHT's are hard to read, just keep going

        print(error.args[0])

        time.sleep(2.0)

        continue

    except Exception as error:

        sensor.exit()

        raise error

    time.sleep(3.0)
```


## **Demonstration**

Save your Python file on the same folder of your virtual environment (in our case *Desktop/dht\_test*). Then run it on your Raspberry Pi. Run the following command (make sure you are on the correct path—the same folder of the virtual environment):
```
python dht-basic.py
```
The virtual environment must be active to run the script. If the virtual environment is not active, you can rerun the following command to activate myenv.
```
source myenv/bin/activate
```
You should get new temperature and humidity readings on the Python Shell or on the Raspberry Pi Terminal every three seconds.

![Raspberry Pi Print Temperature and Humidity DHT22 DHT11 Sensor][image8]

You can stop the execution of the program by pressing **CTRL**\+**C**.

[image1]: <../assets/04-programming-with-python-and-gpio/image1.png>

[image2]: <../assets/04-programming-with-python-and-gpio/dht22-pinout.webp>

[image3]: <../assets/04-programming-with-python-and-gpio/Raspberry-Pi-DHT-Circuit.webp>

[image4]: <../assets/04-programming-with-python-and-gpio/wiring -DHT-Circuit.webp>

[image5]: <../assets/04-programming-with-python-and-gpio/create-virtual-environment.webp>

[image6]: <../assets/04-programming-with-python-and-gpio/virtual-environment.webp>

[image7]: <../assets/04-programming-with-python-and-gpio/installing-circuitpython-dht.webp>

[image8]: <../assets/04-programming-with-python-and-gpio/dht-print-sensor-readings-raspberry-pi.webp>