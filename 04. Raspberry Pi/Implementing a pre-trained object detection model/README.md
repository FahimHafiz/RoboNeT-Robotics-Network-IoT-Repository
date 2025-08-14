# **UNITED INTERNATIONAL UNIVERSITY (UIU)**  
## **Dept. of Computer Science & Engineering**  

## **Experiment: Implementing a Pre-Trained Object Detection Model (TensorFlow Lite) with PiCamera on Raspberry Pi 4B**  

### **Objective**  
To detect objects in real time using **PiCamera** and a **TensorFlow Lite (TFLite) model** optimized for **Raspberry Pi**.

---

## **What You Need**  
- **Raspberry Pi 4B** (4GB is ok but 8GB recommended)  
- **Raspberry Pi OS (64-bit preferred)**  
- **PiCamera [Link](https://www.google.com/search?q=picamera&sca_esv=8febcbffea4305d2&udm=2&biw=1396&bih=649&ei=IVngZ7HmL_easeMP0Kz-qAU&ved=0ahUKEwjx-q7A8KCMAxV3TWwGHVCWH1UQ4dUDCBE&uact=5&oq=picamera&gs_lp=EgNpbWciCHBpY2FtZXJhMgUQABiABDIFEAAYgAQyBRAAGIAEMgUQABiABDIFEAAYgAQyBRAAGIAEMgUQABiABDIFEAAYgAQyBRAAGIAEMgUQABiABEiTDFCDAli8CnABeACQAQCYAakBoAHuCaoBAzAuOLgBA8gBAPgBAZgCCKAC0AqoAgDCAgoQABiABBhDGIoFwgIOEAAYgAQYsQMYgwEYigXCAgsQABiABBixAxiDAcICCBAAGIAEGLEDwgIHEAAYgAQYCpgDBZIHAzAuOKAHyCSyBwMwLji4B9AK&sclient=img#vhid=-tOsdUKBU3RGUM&vssid=mosaic) (official or compatible)**  
- **Internet connection** (for installing packages & downloading models)  
- **Monitor, keyboard, and mouse** (or SSH access)  

---

## **Step 1: Initial Setup**  

### **1. Turn on Raspberry Pi and open the terminal.**  
Update and upgrade the system:  

```sh
sudo apt update && sudo apt upgrade -y
```

### **2. Enable the PiCamera (if not already enabled).**  
Run:  

```sh
sudo raspi-config
```
- Navigate to **Interfacing Options > Camera > Enable**  
- Press **Enter** and **reboot** the Raspberry Pi:  

```sh
sudo reboot
```

To verify that the camera is detected, run:  

```sh
vcgencmd get_camera
```
If the output shows `supported=1 detected=1`, your **PiCamera is ready**.

### **3. Install Required System Packages**  

Install Python tools and dependencies:

```sh
sudo apt install python3-pip python3-picamera python3-opencv libatlas-base-dev -y
```

### **4. Set Up the Project Folder**  

Create a project directory and navigate to it:

```sh
mkdir ~/ObjectDetection
cd ~/ObjectDetection
```

### **5. Create and Activate a Virtual Environment**  

```sh
python3 -m venv env
source env/bin/activate
```

You will see `(env)` in the terminal, indicating the virtual environment is active.

### **6. Install Required Python Libraries**  

```sh
pip install numpy opencv-python tflite-runtime picamera2
```

---

## **Step 2: Download the Pre-Trained TFLite Model**  

### **1. Download the SSD MobileNet V2 Model**
Run:

```sh
wget https://storage.googleapis.com/download.tensorflow.org/models/tflite/task_library/object_detection/sample_model.tflite -O detect.tflite
```

### **2. Download the Label Map File**  

```sh
wget https://storage.googleapis.com/download.tensorflow.org/models/tflite/task_library/object_detection/sample_labelmap.txt -O labelmap.txt
```

Now, both `detect.tflite` and `labelmap.txt` are in your **~/ObjectDetection** folder.

---

## **Step 3: Create the Object Detection Script**  

### **1. Create a Python Script**  

```sh
nano detect_objects.py
```

### **2. Paste the Following Code**  

```python
import cv2
import numpy as np
import tflite_runtime.interpreter as tflite
from picamera2 import Picamera2

# Load the TensorFlow Lite model
model_path = "detect.tflite"
label_path = "labelmap.txt"

# Load labels
with open(label_path, "r") as f:
    labels = [line.strip() for line in f.readlines()]

# Initialize TFLite interpreter
interpreter = tflite.Interpreter(model_path=model_path)
interpreter.allocate_tensors()

# Get input & output details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
input_shape = input_details[0]["shape"]

# Initialize PiCamera2
picam2 = Picamera2()
config = picam2.create_preview_configuration(main={"size": (640, 480)})
picam2.configure(config)
picam2.start()

while True:
    frame = picam2.capture_array()

    # Preprocess frame for model
    img = cv2.resize(frame, (input_shape[2], input_shape[1]))
    img = np.expand_dims(img, axis=0).astype(np.uint8)

    # Run inference
    interpreter.set_tensor(input_details[0]["index"], img)
    interpreter.invoke()

    # Get results
    boxes = interpreter.get_tensor(output_details[0]["index"])[0]  # Bounding boxes
    classes = interpreter.get_tensor(output_details[1]["index"])[0]  # Class indices
    scores = interpreter.get_tensor(output_details[2]["index"])[0]  # Confidence scores

    # Draw detections
    height, width, _ = frame.shape
    for i in range(len(scores)):
        if scores[i] > 0.5:  # Confidence threshold
            ymin, xmin, ymax, xmax = boxes[i]
            xmin = int(xmin * width)
            xmax = int(xmax * width)
            ymin = int(ymin * height)
            ymax = int(ymax * height)
            cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), (0, 255, 0), 2)
            label = f"{labels[int(classes[i])]}: {int(scores[i] * 100)}%"
            cv2.putText(frame, label, (xmin, ymin - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    # Show the frame
    cv2.imshow("Object Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cv2.destroyAllWindows()
picam2.stop()
```

### **3. Save and Exit**
Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.

---

## **Step 4: Run the Object Detection Script**  

Ensure you are in the **ObjectDetection** folder and your virtual environment is active:

```sh
cd ~/ObjectDetection
source env/bin/activate
```

Then, run:

```sh
python3 detect_objects.py
```

### **What Happens?**
- The **PiCamera will start streaming**.
- Objects detected will be highlighted with **bounding boxes and labels**.
- Press **'q'** to **exit**.

---

## **Further Exploration**  

### **1. Test Other TFLite Models**  
You can try different TensorFlow Lite models from the **TFLite Model Zoo**:
🔗 [https://www.tensorflow.org/lite/models](https://www.tensorflow.org/lite/models)  

### **2. Improve Performance**  
- **Optimize model size** using `tflite_convert`  
- **Run with Coral USB Accelerator** for **faster inference**  

### **3. Detect Specific Objects**  
- Use **custom-trained models** for specific tasks like **face detection** or **gesture recognition**.

##You can follow this tutorial too: [Link](https://youtu.be/kX6zWqMP9U4?si=VfWYYeSmE6k9RS_m)

---

## **Conclusion**  

You have successfully:  
✅ Set up **PiCamera** with Raspberry Pi 4B.  
✅ Installed **TensorFlow Lite** and required dependencies.  
✅ Downloaded and used a **pre-trained object detection model**.  
✅ Ran **real-time detection** with a **TFLite model**.  
