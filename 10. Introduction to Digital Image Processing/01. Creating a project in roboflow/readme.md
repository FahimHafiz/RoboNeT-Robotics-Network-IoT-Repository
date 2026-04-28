# Creating a Project in Roboflow

This tutorial will guide you through the process of setting up a new computer vision project. We will focus on creating an **Object Detection** model for this walkthrough.

## Step 1: Access the Projects Dashboard
Open your Roboflow dashboard and locate the project icon in the sidebar.

<img width="177" height="530" alt="Navigate to Projects" src="https://github.com/user-attachments/assets/8b4d3357-66e7-40b1-b1a1-057495014637" />

Click on the **Projects** button to view your existing workspace.

---

## Step 2: Initialize a New Project
Once you are in the projects view, look for the creation button in the top right or center of the screen.

<img width="376" height="228" alt="New Project Button" src="https://github.com/user-attachments/assets/5f53e21a-d96c-4840-b7ce-ed0f25707cd3" />

Click on the **Create New Project** button to begin the setup wizard.

---

## Step 3: Choose Your Project Type
You will be presented with several options. It is important to choose the one that matches your goal.

<img width="1492" height="846" alt="Project Selection Screen" src="https://github.com/user-attachments/assets/8cb107e1-897d-4467-80fa-8fcf9b51805b" />

### Understanding the Options:

1. **Object Detection**
   * **What it does:** Identifies specific objects and tells you exactly where they are located.
   * **Method:** You draw **Bounding Boxes** (rectangles) around objects.
   * **Use Cases:** Counting inventory, tracking players, or identifying vehicles.

2. **Classification**
   * **What it does:** Assigns labels to an entire image.
   * **Method:** You tag the whole image (e.g., "sunny" or "damaged").
   * **Use Cases:** Sorting photos or quality control (Pass/Fail).

3. **Instance Segmentation**
   * **What it does:** Outlines the precise, actual shape of multiple objects.
   * **Method:** You use **Polygons** to trace exact edges.
   * **Use Cases:** Medical imaging or precision robotics.

4. **Keypoint Detection**
   * **What it does:** Identifies "landmarks" or skeleton structures.
   * **Method:** You place points on specific joints to create a **Skeleton Structure**.
   * **Use Cases:** Pose estimation or gesture recognition.

5. **Multimodal**
   * **What it does:** Connects images with text pairs.
   * **Method:** Uses **Prompts** and **Visual Question Answering (VQA)**.
   * **Use Cases:** Accessibility descriptions or image search.

6. **Semantic Segmentation**
   * **What it does:** Categorizes every single pixel.
   * **Difference:** It treats all objects of the same class as one mass (e.g., all "grass" is one segment).
   * **Use Cases:** Autonomous driving or satellite analysis.

---

## Step 4: Starting with Object Detection
For this tutorial, we will proceed with **Object Detection**. Enter your project details such as the project name and the name of the object you are detecting.

<img width="733" height="656" alt="Configure Object Detection" src="https://github.com/user-attachments/assets/5aef98b8-5d44-41e5-93e4-7764f32cdf0b" />

**Action:** Select "Object Detection" from the list and fill in the required project information to get started!
