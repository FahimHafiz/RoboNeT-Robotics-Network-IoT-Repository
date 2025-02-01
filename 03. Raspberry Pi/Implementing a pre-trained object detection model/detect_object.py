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
