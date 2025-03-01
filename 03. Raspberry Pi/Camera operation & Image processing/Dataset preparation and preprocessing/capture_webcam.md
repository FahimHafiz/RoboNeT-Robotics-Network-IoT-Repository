import cv2
cap = cv2.VideoCapture(0)
for i in range(5):  # Capture 5 images
    ret, frame = cap.read()
    if ret:
        filename = f"webcam_image_{i}.jpg"
        cv2.imwrite(filename, frame)
        print(f"Saved: {filename}")
    else:
        print("Failed to capture image")
cap.release()
