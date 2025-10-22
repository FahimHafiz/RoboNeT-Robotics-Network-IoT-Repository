import cv2
import glob
# Find all JPG images in the folder
images = glob.glob("*.jpg")
for img_path in images:
    img = cv2.imread(img_path)
    # Resize image
    resized = cv2.resize(img, (128, 128))
    # Convert to grayscale
    gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
    # Smooth the image
    smoothed = cv2.GaussianBlur(gray, (5, 5), 0)
    # Save processed images
    cv2.imwrite(f"resized_{img_path}", resized)
    cv2.imwrite(f"gray_{img_path}", gray)
    cv2.imwrite(f"smoothed_{img_path}", smoothed)
    print(f"Processed: {img_path}")
