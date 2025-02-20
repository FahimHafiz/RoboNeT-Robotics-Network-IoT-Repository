# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Implementing a Pre-Trained Object Detection Model (TensorFlow Lite)

### Objective
To detect objects in real time using a webcam and a TensorFlow Lite (TFLite) model optimized for Raspberry Pi.

### What You Need
- Raspberry Pi (4B) with Raspbian OS installed.
- USB webcam.
- Internet connection for installing packages and downloading models.
- Monitor, keyboard, and mouse connected to Raspberry Pi.

---

## Step 1: Initial Setup

### 1. Turn on Raspberry Pi and open the terminal.
Update and upgrade the system:

```sh
sudo apt update && sudo apt upgrade -y
```

### 2. Install Python tools:

```sh
sudo apt install python3-pip
pip3 install virtualenv
```

### 3. Set up a project folder:

```sh
mkdir ~/ObjectDetection
cd ~/ObjectDetection
```

### 4. Create a virtual environment:

```sh
python3 -m venv env
source env/bin/activate
```

You will see `(env)` in the terminal prompt, indicating the virtual environment is active.

### 5. Install necessary libraries:

```sh
pip install numpy opencv-python tflite-runtime
```

---

## Step 2: Download Pre-Trained TFLite Model

### 1. Download the TFLite SSD MobileNet V2 model:
Go to the official TensorFlow Lite model zoo: **TFLite Model Zoo**.
Download the SSD MobileNet V2 TFLite model by running the following in the terminal:

```sh
wget https://storage.googleapis.com/download.tensorflow.org/models/tflite/task_library/object_detection/sample_model.tflite -O detect.tflite
```

### 2. Download the label map file:
This file maps the model's output to human-readable labels. Run:

```sh
wget https://storage.googleapis.com/download.tensorflow.org/models/tflite/task_library/object_detection/sample_labelmap.txt -O labelmap.txt
```

Both `detect.tflite` and `labelmap.txt` will now be in your `~/ObjectDetection` folder.

---

## Step 3: Create the Python Script for Real-Time Detection

### 1. Create a Python script:

```sh
nano detect_objects.py
```

### 2. Paste the following code:

```python
import cv2
import numpy as np
import tflite_runtime.interpreter as tflite

# Load the TFLite model
model_path = "detect.tflite"
label_path = "labelmap.txt"

# Load labels
with open(label_path, "r") as f:
    labels = [line.strip() for line in f.readlines()]

# Initialize the interpreter
interpreter = tflite.Interpreter(model_path=model_path)
interpreter.allocate_tensors()

# Get input and output details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
input_shape = input_details[0]["shape"]

# Open webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Preprocess frame
    img = cv2.resize(frame, (input_shape[2], input_shape[1]))
    img = np.expand_dims(img, axis=0)
    img = img.astype(np.uint8)

    # Run inference
    interpreter.set_tensor(input_details[0]["index"], img)
    interpreter.invoke()

    # Get results
    boxes = interpreter.get_tensor(output_details[0]["index"])[0]  # Bounding box coordinates
    classes = interpreter.get_tensor(output_details[1]["index"])[0]  # Class index
    scores = interpreter.get_tensor(output_details[2]["index"])[0]  # Confidence scores

    # Draw detections on the frame
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

cap.release()
cv2.destroyAllWindows()
```

### 3. Save and exit:
Press `CTRL+O`, hit `ENTER`, then press `CTRL+X`.

---

## Step 4: Run the Object Detection Script

Run the script:

```sh
python3 detect_objects.py
```

- The webcam will open, and real-time object detection will begin.
- Detected objects will be highlighted with bounding boxes and labels.
- Press `q` to quit the application.

---

## Further Exploration

### Experiment with other TFLite models:
- Download different TFLite models from the TensorFlow Lite Model Zoo.

### Explore lightweight models:
- Try models like **MobileNet** or **Tiny YOLO** for faster detection.

### Optimize for specific tasks:
- Use models trained for specialized tasks like **face detection** or **gesture recognition**.

---

This concludes the experiment on **Implementing a Pre-Trained Object Detection Model using TensorFlow Lite on Raspberry Pi**. 🚀

