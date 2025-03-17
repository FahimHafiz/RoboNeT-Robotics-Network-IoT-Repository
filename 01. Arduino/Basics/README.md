
# 🛠️ Arduino Basics - Getting Started  

Welcome to the **Arduino Basics** section! 🎉  

This section is designed for beginners to learn how to set up an **Arduino board**, write and upload their **first program**, and understand **pin configurations**.  

---

## 🎯 What You’ll Learn  
✅ How to **install the Arduino IDE**  
✅ How to **set up your Arduino board**  
✅ How to **write and upload your first program**  
✅ Understanding **pin configurations and basic components**  

---

## 1️⃣ **Installing Arduino IDE**  

Before you start coding, you need to **install the Arduino IDE**.  

### **🔹 Steps to Install Arduino IDE**  
1. Download the **Arduino IDE** from the [official website](https://www.arduino.cc/en/software).  
2. Install the software on your **Windows, Mac, or Linux** system.  
3. Launch the **Arduino IDE** and get ready to code!

---

## 2️⃣ **Setting Up Your Arduino Board**  

To start using your **Arduino**, follow these steps:  

### **🔹 Connecting Your Board**  
1. **Plug your Arduino board** into your computer via **USB cable**.  
2. Open the **Arduino IDE** and navigate to:  
   - **Tools > Board > Select your Arduino model** (e.g., Arduino Uno).  
   - **Tools > Port > Select the correct COM port** (Windows) or `/dev/ttyUSB` (Mac/Linux).  

---

## 3️⃣ **Writing and Uploading Your First Program**  

Now that your board is connected, let’s write our **first Arduino program**!  

### **🔹 Blink an LED**  

```cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```




<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>




# Experiment : Introduction to Arduino UNO.

## Objective: 
This documentation aims to provide a beginner-friendly guide to getting started with Arduino and ESP32 development. It covers the installation of the Arduino IDE, initial setup for Arduino and ESP32 boards, and testing with a simple "Blink" program to ensure the setup works correctly. The goal is to empower students to build confidence in using these platforms for future projects.


## Arduino Launch History :  
You’ll need arduino IDE to get started with the arduino and esp32 programming. To get the latest version of the IDE follow this link and follow the instructions.

[IDE download link](https://www.arduino.cc/en/software) <br>
[Installation Guide link for Windows](https://docs.arduino.cc/software/ide-v1/tutorials/Windows/) <br>
[Installation Guide Link for macOS](https://docs.arduino.cc/software/ide-v1/tutorials/macOS/) <br>
[Learn Arduino code](https://docs.arduino.cc/language-reference/?_gl=1*1fzdi51*_up*MQ..*_ga*MzMyOTcyNjE2LjE3MzY2MjQ1ODc.*_ga_NEXN8H46L5*MTczNjYyNDU4NC4xLjEuMTczNjYyNDU4OS4wLjAuNTMzMjg0MTkx) <br>
How to write and upload the code to Arduino:  [Upload Code Guide](https://youtu.be/xQfC72VeV7Y?si=Ls96MXAMnVyEDich)

## Features of Arduino: 
* Open-Source Hardware and Software
* Cross-Platform Support
* Easy-to-Use Programming
* Wide Range of Boards
* Input/Output (I/O) Capabilities
* Serial Communication
* Expandability with Shields
* Large Community and Documentation


## Arduino pin diagram : 

<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/a5a063ee-f4db-4244-9c25-fe15577c0fdf" />
</div>
