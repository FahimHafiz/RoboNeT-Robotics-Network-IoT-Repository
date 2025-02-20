# UNITED INTERNATIONAL UNIVERSITY (UIU)
## Dept. of Computer Science & Engineering

## Experiment: Capturing Image and Video with Raspberry Pi Camera

### Objective
To guide beginners through the process of capturing a single image, multiple images in a loop, and a video using the Raspberry Pi 4B camera module. This documentation provides step-by-step instructions for setting up the camera, writing Python scripts in Thonny, and successfully executing the tasks.

### Step 1: Create a Project Folder
1. On your Raspberry Pi desktop, right-click and create a new folder. Name it `camera_project`.
2. Open the folder and create three subfolders:
   - `single_image`
   - `image_loop`
   - `video_capture`

### Step 2: Enable the Camera
1. Open the terminal and type:
   ```sh
   sudo raspi-config
   ```
2. Navigate to **Interface Options > Camera** and enable it.
3. Reboot your Raspberry Pi to apply changes:
   ```sh
   sudo reboot
   ```

### Step 3: Install Required Libraries
1. Open Thonny.
2. In the terminal at the bottom of Thonny, install the `picamera2` library:
   ```sh
   pip install picamera2
   ```
   (If not already installed.)

### Step 4: Capture a Single Image
1. Navigate to the `single_image` folder in your project.
2. Open Thonny and create a new file. Save it in the `single_image` folder as `capture_image.py`.
3. Write the following code:

   ```python
   from picamera2 import Picamera2
   from time import sleep

   # Initialize the camera
   camera = Picamera2()

   # Configure the camera
   camera.start()
   sleep(2)  # Allow time for the camera to adjust

   # Capture and save an image
   camera.capture_file("image.jpg")
   print("Image saved as image.jpg")

   # Stop the camera
   camera.stop()
   ```

4. Run the code in Thonny, and the image will be saved in the `single_image` folder as `image.jpg`.

### Step 5: Capture Images in a Loop
1. Navigate to the `image_loop` folder in your project.
2. Open Thonny and create a new file. Save it in the `image_loop` folder as `capture_images_loop.py`.
3. Write the following code:

   ```python
   from picamera2 import Picamera2
   from time import sleep

   # Initialize the camera
   camera = Picamera2()

   # Start the camera
   camera.start()

   # Capture 5 images in a loop
   for i in range(5):
       file_name = f"image_{i+1}.jpg"
       camera.capture_file(file_name)
       print(f"Image {i+1} saved as {file_name}")
       sleep(2)  # Wait 2 seconds between captures

   # Stop the camera
   camera.stop()
   ```

4. Run the code in Thonny. It will save 5 images (`image_1.jpg`, `image_2.jpg`, etc.) in the `image_loop` folder.

### Step 6: Capture a Video
1. Navigate to the `video_capture` folder in your project.
2. Open Thonny and create a new file. Save it in the `video_capture` folder as `capture_video.py`.
3. Write the following code:

   ```python
   from picamera2 import Picamera2
   from time import sleep

   # Initialize the camera
   camera = Picamera2()

   # Start the camera
   camera.start_recording("video.h264")
   print("Recording started...")

   # Record for 10 seconds
   sleep(10)

   # Stop the recording
   camera.stop_recording()
   print("Recording stopped. Video saved as video.h264")
   ```

4. Run the code in Thonny. It will record a 10-second video and save it as `video.h264` in the `video_capture` folder.

### Step 7: Play the Video
1. Open the terminal and navigate to the `video_capture` folder:
   ```sh
   cd ~/camera_project/video_capture
   ```
2. Play the video using the built-in video player:
   ```sh
   omxplayer video.h264
   ```

### Step 8: Clean Up (Optional)
You can delete unnecessary files from the folders to keep your project organized.

