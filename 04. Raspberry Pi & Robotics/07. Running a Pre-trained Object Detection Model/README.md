# **Running YOLO Object Detection on Raspberry Pi 5 (Ubuntu)**

**Target Hardware:** Raspberry Pi 5 (4GB or 8GB RAM recommended)

**Target OS:** Ubuntu 24.04 LTS

**Software:** Python 3.12, YOLO (v11 or newer)

## **1. Introduction**

**YOLO (You Only Look Once)** is a state-of-the-art computer vision model known for its speed and accuracy. It can perform object detection, segmentation, and classification in real-time.

In this chapter, we will install the **Ultralytics YOLO** library on a Raspberry Pi 5 running Ubuntu 24.04. We will run inference on a static image to detect objects.

## **2. Prerequisites**

* **Hardware:** Raspberry Pi 5 (8GB RAM is ideal for larger models, but 4GB works).  
* **OS:** Ubuntu 24.04 (64-bit).  
* **Storage:** A fast microSD card or, ideally, an **NVMe SSD** for faster model loading times.  
* **Internet:** Required to download model weights.

---

## **3. System Preparation**

### **Step A: Verify OS and Python**

First, ensure you are running the correct version of Ubuntu and Python. Open your terminal and run:
```
#Check OS Version (Should be Ubuntu 24.04)

lsb_release -a
```
The output should look like this
```
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 24.04.1 LTS
Release:	24.04
Codename:	noble
```
### Check Python Version (Should be 3.12 or newer)
```
python3 --version
```
The output:
```
Python 3.12.3
```

### **Step B: Install System Dependencies**

We need `git` to download repositories and `git-lfs` (Large File Storage) because AI models are often large files.


```
#Update system
sudo apt update && sudo apt upgrade -y

#Install Git and Git LFS
sudo apt install -y git git-lfs

#Initialize Git LFS
sudo git lfs install
git lfs install
```
---

## **4. Installation (Virtual Environment)**

To keep our AI environment clean, we will create a dedicated folder and a Python Virtual Environment.



### 1. Install venv support
```
sudo apt install -y python3.12-venv
```
### 2. Create a workspace folder
```
cd ~

mkdir testYolo

cd testYolo
```
### 3. Create the virtual environment named 'env'
```
python3 -m venv env
```
### 4. Activate the environment
```
source env/bin/activate
```
*Note: You must run `source env/bin/activate` every time you open a new terminal to work on this project.*

### **Step C: Install YOLO (Ultralytics)**

We will install the official Ultralytics package directly from GitHub to ensure we have the latest version.


### Install setup tools
```
pip install setuptools
```
### Install YOLO/Ultralytics
```
pip install git+https://github.com/ultralytics/ultralytics.git@main
```
*it will take a few time to install Ultralytics*
---

## **5. Running Object Detection (Python)**

We will write a Python script to detect objects in an image.

**Preparation:**

1. Take a photo (e.g., of a desk with objects) or download a sample image.  
2. Name it `test_image.jpg` and place it inside your `testYolo` folder.

### **Option A: High Accuracy (Recommended)**

This uses the standard YOLO model. It is more accurate but requires more RAM.

Create the file:  
```
nano yolo_full.py
```

Paste the following code:  
```python 
from ultralytics import YOLO

# Load the model

# Options: yolo11n.pt (nano - fastest), yolo11s.pt (small), 

# yolo11m.pt (medium), yolo11l.pt (large - most accurate but slow)

print("Loading Model...")

model = YOLO("yolo11l.pt") 

# Run inference on your image

print("Running Inference...")

results = model("test_image.jpg")

# Process results

for result in results:

    result.show()                  # Display to screen (requires monitor)

    result.save(filename="result_full.jpg")  # Save to disk

    print(" Detection complete! Saved as 'result_full.jpg'")
```
 **Save and exit** `nano`:  
   * Press `Ctrl + S` to save.  
   * Press `Ctrl + X` to exit.  
 
### Run it:
``` 
python3 yolo_full.py
```


![][image1]

3. *(Note: The first run will automatically download the `yolo11l.pt` model file, which may take a minute.)*

### **Option B: High Speed (NCNN Optimized)**

If you need faster performance (e.g., for video), you can convert the model to **NCNN** format, which is optimized for mobile CPUs like the Raspberry Pi. *Note: Accuracy may slightly decrease.*

Create the file:  
``` 
nano yolo_ncnn.py
```

Paste the following code:  
```python  
from ultralytics import YOLO

# 1. Load the standard Nano model

model = YOLO("yolo11n.pt")

# 2. Export to NCNN format (Optimized for Pi)

print("Exporting to NCNN...")

model.export(format="ncnn") 

# 3. Load the new NCNN model

ncnn_model = YOLO("yolo11n_ncnn_model")

# 4. Run inference

print("Running Inference...")

results = ncnn_model("test_image.jpg")

# 5. Save results

for result in results:

    result.save(filename="result_ncnn.jpg")

    print(" Optimized detection saved as 'result_ncnn.jpg'")
```
 **Save and exit** `nano`:  
   * Press `Ctrl + S` to save.  
   * Press `Ctrl + X` to exit.  

### Run it:
``` 
python3 yolo_ncnn.py
```
---

## **6\. Understanding the Output**

After running the script, check your folder:

```
ls -l *.jpg
```
You will see `result_full.jpg`. Open this image to see the **Bounding Boxes** drawn around detected objects (e.g., "cup", "mouse", "keyboard") along with confidence scores.

![][image2]







### **Model Comparison**

* **`yolo11n.pt` (Nano):** Fastest, least accurate. Good for high-speed video.  
* **`yolo11l.pt` (Large):** Slowest (approx 1-3 seconds per image on Pi 5), but highly accurate. Best for static image analysis.



## **Assessment & Evaluation**

### Excellent work! You have learned *hardware setup, operating systems, terminal skills, Python GPIO programming, networking with SSH, computer vision with OpenCV, and object detection with a pre-trained model*. Ready to test your knowledge? [Click here to take the evaluation!](https://docs.google.com/forms/d/e/1FAIpQLSfHdoqlC4ytbOAoFErrhIMYJArXgw1D1DR8fWt9YyhMMss3lw/viewform?usp=header)


# [Let's learn about Networking](../../04.%20Raspberry%20Pi%20%26%20Robotics/)


[image1]: <../assets/07. Running a Pre-trained Object Detection Model/vscode.png>

[image2]: <../assets/07. Running a Pre-trained Object Detection Model/result_full.jpg>
