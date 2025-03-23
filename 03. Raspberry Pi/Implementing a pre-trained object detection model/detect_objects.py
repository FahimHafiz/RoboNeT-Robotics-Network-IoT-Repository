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
