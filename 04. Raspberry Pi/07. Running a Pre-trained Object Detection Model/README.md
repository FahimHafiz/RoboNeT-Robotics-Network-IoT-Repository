# YOLO Object Detection on Raspberry Pi 4/5 & Ubuntu 22+

**A complete guide to running YOLOv8/YOLO11 — live webcam detection and still images — on Raspberry Pi OS (64-bit) and Ubuntu 22.04/24.04.**

---

## Overview

This chapter walks you through deploying Ultralytics YOLO models on:

- Raspberry Pi 4 or 5 (64-bit OS)
- Ubuntu 22.04 / 24.04 (on Pi or a standard x86/ARM machine)

You will end up with:

- **Live webcam detection** — real-time bounding boxes via USB camera
- **Still image detection** — run inference on a single photo and save the output

The key optimization is exporting the model to **NCNN format**, which is purpose-built for ARM CPUs and gives the best speed on the Pi without any accelerator hardware.

---

## Compatibility Table

| Platform | OS | Architecture | Supported |
|---|---|---|---|
| Raspberry Pi 4 | Raspberry Pi OS Bookworm 64-bit | ARM64 | ✅ |
| Raspberry Pi 5 | Raspberry Pi OS Bookworm 64-bit | ARM64 | ✅ |
| Raspberry Pi 4/5 | Ubuntu 22.04 / 24.04 64-bit | ARM64 | ✅ |
| Desktop / Laptop | Ubuntu 22.04 / 24.04 | x86_64 | ✅ |

---

## Step 1 — System Setup

### 1a. Update the system

Open a terminal and run:

```bash
sudo apt update && sudo apt upgrade -y
```

This applies to both Raspberry Pi OS and Ubuntu. On a fresh Pi this can take 5–20 minutes.

### 1b. Install system dependencies

These packages are needed for OpenCV to display the camera feed window:

```bash
sudo apt install -y python3-pip python3-venv \
    libgl1 libglib2.0-0 \
    v4l-utils
```

> **Ubuntu note:** If you are on a headless Ubuntu server (no desktop), replace the display step in the scripts below with saving output to a file instead (see Step 5).

### 1c. Check your camera is detected

Plug in your USB webcam, then run:

```bash
ls /dev/video*
```

You should see `/dev/video0` (and possibly `/dev/video1`, `/dev/video2`). If nothing appears, try a different USB port or camera.

You can also verify with:

```bash
v4l2-ctl --list-devices
```

---

## Step 2 — Create a Working Directory and Virtual Environment

```bash
mkdir ~/yolo
cd ~/yolo
```

Create and activate a Python virtual environment:

```bash
python3 -m venv --system-site-packages venv
source venv/bin/activate
```

You will see `(venv)` prepended to your prompt. **Every time you open a new terminal, re-run these two commands to return to your environment:**

```bash
cd ~/yolo
source venv/bin/activate
```

---

## Step 3 — Install Python Libraries

Install Ultralytics (includes PyTorch, the YOLO framework) and NCNN:

```bash
pip install ultralytics ncnn opencv-python
```

> **This can take 10–20 minutes** on a Pi due to downloading and compiling dependencies. If it seems stalled past 20 minutes, press `Ctrl+C` and run the command again.

Verify the install:

```bash
python3 -c "import ultralytics; ultralytics.checks()"
```

You should see a summary with no errors.

---

## Step 4 — Download and Export the YOLO Model

### 4a. Download a pre-trained model

Ultralytics models are trained on the COCO dataset (80 common object classes: person, car, dog, chair, etc.). Download the nano model (smallest and fastest):

```bash
yolo detect predict model=yolo11n.pt source='https://ultralytics.com/images/bus.jpg'
```

This downloads `yolo11n.pt` and runs a quick test. You can also use `yolo11s.pt` (small) for slightly better accuracy at lower speed, or `yolov8n.pt` if you prefer the YOLOv8 family.

### 4b. Export to NCNN format

NCNN is optimized for ARM CPUs. It gives significantly faster inference than running PyTorch directly on the Pi:

```bash
yolo export model=yolo11n.pt format=ncnn
```

This creates a folder called `yolo11n_ncnn_model/` in your current directory. This is what you will load for inference.

> If you have a **custom-trained model** (your own `.pt` file), copy it into `~/yolo/` and replace `yolo11n.pt` with your filename in the commands above.

---

## Step 5 — The Detection Scripts

Save these two scripts into `~/yolo/`.

---

### Script A: Live Webcam Detection

Save as `~/yolo/webcam_detect.py`:

```python
"""
YOLO Live Detection — USB Webcam
Raspberry Pi 4/5 — Raspberry Pi OS or Ubuntu (Xorg/X11)

Usage:
  python webcam_detect.py --model yolo11n_ncnn_model --camera 0
  python webcam_detect.py --model yolo11n_ncnn_model --camera 0 --width 640 --height 480
  python webcam_detect.py --model yolo11n_ncnn_model --camera 0 --conf 0.4
"""

import cv2
from ultralytics import YOLO
import time
import argparse

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--model",  type=str,   default="yolo11n_ncnn_model")
    parser.add_argument("--camera", type=int,   default=0)
    parser.add_argument("--width",  type=int,   default=640)
    parser.add_argument("--height", type=int,   default=480)
    parser.add_argument("--conf",   type=float, default=0.25)
    return parser.parse_args()

args = parse_args()

# Load model
print(f"[INFO] Loading model: {args.model}")
model = YOLO(args.model, task="detect")

# Open camera
print(f"[INFO] Opening camera {args.camera} at {args.width}x{args.height}")
cap = cv2.VideoCapture(args.camera)
cap.set(cv2.CAP_PROP_FRAME_WIDTH,  args.width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, args.height)
cap.set(cv2.CAP_PROP_BUFFERSIZE,   1)

if not cap.isOpened():
    print(f"[ERROR] Cannot open camera {args.camera}")
    print(f"        Run: ls /dev/video*  to see available cameras")
    exit(1)

print("[INFO] Press Q to quit, S to save screenshot.")

fps = 0

while True:
    ret, frame = cap.read()
    if not ret:
        print("[WARN] Failed to read frame, retrying...")
        time.sleep(0.1)
        continue

    # Run inference
    t0      = time.time()
    results = model(frame, conf=args.conf, verbose=False)[0]
    inf_ms  = (time.time() - t0) * 1000

    # Smooth FPS
    fps = fps * 0.8 + 0.2 * (1000.0 / max(inf_ms, 1.0))

    # Draw detections
    annotated = results.plot()

    # Overlay stats
    cv2.putText(annotated, f"FPS: {fps:.1f}",
                (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2)
    cv2.putText(annotated, f"Objects: {len(results.boxes)}",
                (10, 65), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
    cv2.putText(annotated, f"Inf: {inf_ms:.0f}ms",
                (10, 95), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (200, 200, 200), 1)

    cv2.imshow("YOLO Webcam", annotated)

    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break
    elif key == ord('s'):
        fname = f"webcam_{int(time.time())}.jpg"
        cv2.imwrite(fname, annotated)
        print(f"[INFO] Saved: {fname}")

cap.release()
cv2.destroyAllWindows()
print(f"[INFO] Done. Final FPS: {fps:.1f}")
```

**Run it:**

```bash
python webcam_detect.py --model yolo11n_ncnn_model --camera 0 --width 640 --height 480
```

Press `q` to quit. Press `s` to save a screenshot of the current frame.

---

### Script B: Still Image Detection

Save as `~/yolo/image_detect.py`:

```python
"""
YOLO Object Detection on a Still Image
Works on Raspberry Pi 4/5 and Ubuntu.

Usage:
    python image_detect.py --model yolo11n_ncnn_model --image photo.jpg
    python image_detect.py --model yolo11n_ncnn_model --image photo.jpg --no-display
"""

import argparse
import cv2
from ultralytics import YOLO
import os
import time

def parse_args():
    parser = argparse.ArgumentParser(description="YOLO still image detection")
    parser.add_argument("--model", type=str, default="yolo11n_ncnn_model",
                        help="Path to NCNN model folder (or .pt file)")
    parser.add_argument("--image", type=str, required=True,
                        help="Path to input image file")
    parser.add_argument("--conf", type=float, default=0.5,
                        help="Confidence threshold (0.0 – 1.0)")
    parser.add_argument("--output", type=str, default="",
                        help="Path to save output image (auto-named if empty)")
    parser.add_argument("--no-display", action="store_true",
                        help="Skip showing the result window (useful on headless servers)")
    return parser.parse_args()

def main():
    args = parse_args()

    if not os.path.isfile(args.image):
        print(f"[ERROR] Image not found: {args.image}")
        return

    # Load model
    print(f"[INFO] Loading model: {args.model}")
    model = YOLO(args.model, task="detect")

    # Load image
    frame = cv2.imread(args.image)
    print(f"[INFO] Image size: {frame.shape[1]}x{frame.shape[0]}")

    # Run inference
    t_start = time.time()
    results = model(frame, conf=args.conf, verbose=False)
    elapsed = time.time() - t_start

    # Annotate
    annotated = results[0].plot()

    # Print detections
    detections = results[0].boxes
    print(f"\n[RESULTS] Inference time: {elapsed*1000:.1f} ms")
    print(f"[RESULTS] Objects detected: {len(detections)}")
    for box in detections:
        cls_id = int(box.cls[0])
        cls_name = model.names[cls_id]
        conf = float(box.conf[0])
        xyxy = box.xyxy[0].tolist()
        print(f"  - {cls_name} ({conf:.2f})  bbox: [{int(xyxy[0])}, {int(xyxy[1])}, {int(xyxy[2])}, {int(xyxy[3])}]")

    # Save output
    if args.output:
        out_path = args.output
    else:
        base, ext = os.path.splitext(args.image)
        out_path = f"{base}_detected{ext if ext else '.jpg'}"

    cv2.imwrite(out_path, annotated)
    print(f"\n[INFO] Output saved to: {out_path}")

    # Display
    if not args.no_display:
        cv2.imshow("YOLO Detection Result — press any key to close", annotated)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
```

**Run it:**

```bash
# Display result in a window and save automatically
python image_detect.py --model yolo11n_ncnn_model --image photo.jpg

# Save to a specific file without opening a window (good for headless Ubuntu servers)
python image_detect.py --model yolo11n_ncnn_model --image photo.jpg --output result.jpg --no-display
```

---

## Step 6 — Capture a Still Image from the Webcam

You can grab a still from your webcam using this one-liner (no extra software needed):

```bash
python3 -c "
import cv2
cap = cv2.VideoCapture(0)
ret, frame = cap.read()
if ret:
    cv2.imwrite('webcam_capture.jpg', frame)
    print('Saved: webcam_capture.jpg')
else:
    print('Failed to capture')
cap.release()
"
```

Then run detection on it:

```bash
python image_detect.py --model yolo11n_ncnn_model --image webcam_capture.jpg
```

---

## Step 7 — Ubuntu-Specific Notes

### Running with a desktop (GUI)

If Ubuntu has a desktop environment (GNOME, XFCE, etc.), the `cv2.imshow()` window works out of the box. No changes needed.

### Running headless (no desktop / SSH session)

If you're SSHing into your Pi or Ubuntu server, `cv2.imshow()` will fail. Use `--no-display` with the image script, and for webcam detection, replace the display block with saving frames:

In `webcam_detect.py`, replace the `cv2.imshow(...)` / `cv2.waitKey(...)` block with:

```python
# Save every Nth frame instead of displaying
frame_count = 0
if frame_count % 30 == 0:  # save every 30 frames
    cv2.imwrite(f"frame_{frame_count:05d}.jpg", annotated)
frame_count += 1
```

### Ubuntu camera permissions

If `/dev/video0` exists but you get a permission error:

```bash
sudo usermod -aG video $USER
# Then log out and back in, or run:
newgrp video
```

---

## Performance Reference

Expected FPS on the **YOLO11n NCNN model** at 640×480:

| Hardware | ~FPS |
|---|---|
| Raspberry Pi 4 (4GB) | 4–6 FPS |
| Raspberry Pi 5 (8GB) | 8–12 FPS |
| Ubuntu x86_64 laptop (CPU only) | 20–60 FPS |

> FPS depends on scene complexity, resolution, and system load. Lower resolution = higher FPS.

### Tips to improve speed

- Use `yolo11n_ncnn_model` (nano) rather than small or medium
- Reduce resolution: `--width 320 --height 240`
- Close other applications to free RAM
- Optionally try `yolov8n_ncnn_model` — sometimes slightly faster than YOLO11n on Pi 4
- For Pi 5: consider the [Raspberry Pi AI HAT+](https://www.raspberrypi.com/products/ai-hat/) for 10–30× acceleration

---

## Quick Reference: All Commands

```bash
# 1. Setup (one time)
mkdir ~/yolo && cd ~/yolo
python3 -m venv --system-site-packages venv
source venv/bin/activate
pip install ultralytics ncnn opencv-python
yolo export model=yolo11n.pt format=ncnn

# 2. Every session — activate environment
cd ~/yolo && source venv/bin/activate

# 3. Live webcam detection
python webcam_detect.py --model yolo11n_ncnn_model --camera 0

# 4. Still image detection (with display)
python image_detect.py --model yolo11n_ncnn_model --image photo.jpg

# 5. Still image detection (headless / no window)
python image_detect.py --model yolo11n_ncnn_model --image photo.jpg --no-display
```

---

## Troubleshooting

**"Cannot open camera"**
Run `ls /dev/video*` to confirm the device exists. Try `--camera 1` if you have multiple cameras. Re-plug the USB cable.

**"No module named cv2"**
Run `pip install opencv-python` inside the virtual environment.

**Very slow / 0–1 FPS**
Make sure you exported to NCNN format and are pointing `--model` at the `_ncnn_model` folder, not the `.pt` file.

**`imshow` crashes or freezes on Ubuntu**
Add `--no-display` to the image script, or install a desktop environment. For SSH, use X11 forwarding (`ssh -X user@pi`) or just save output files.

**Install stalls**
Press `Ctrl+C` and re-run `pip install ultralytics ncnn opencv-python`. Slow internet or intermittent connection is the usual cause.

**Permission denied on /dev/video0**
Run `sudo usermod -aG video $USER` then log out and back in.

---

---
---

## No webcam? No Pi Camera? No problem. 
*Any Android or iPhone on the same Wi-Fi network can stream live video to your Raspberry Pi or Ubuntu machine for real-time YOLO detection.*
### Follow this repo: [Click here !](https://github.com/AthinNazmul/Using-Your-Phone-as-an-IP-Cam-for-YOLO-Detection)

---
---
---


## **Assessment & Evaluation**

### Excellent work! You have learned *hardware setup, operating systems, terminal skills, Python GPIO programming, networking with SSH, computer vision with OpenCV, and object detection with a pre-trained model*. Ready to test your knowledge? [Click here to take the evaluation!](https://docs.google.com/forms/d/e/1FAIpQLSfHdoqlC4ytbOAoFErrhIMYJArXgw1D1DR8fWt9YyhMMss3lw/viewform?usp=header)


# [Let's learn about Networking](../../05.%20Networking/)


[image1]: <../assets/07. Running a Pre-trained Object Detection Model/vscode.png>

[image2]: <../assets/07. Running a Pre-trained Object Detection Model/result_full.jpg>
