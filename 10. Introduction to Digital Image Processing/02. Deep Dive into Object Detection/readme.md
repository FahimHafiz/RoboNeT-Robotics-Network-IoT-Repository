# Building an Object Detection Model in Roboflow

This section of the tutorial covers the core workflow of a computer vision project: uploading data and performing manual annotations.

## 1. Navigating the Sidebar
Once your project is created, the left-hand sidebar becomes your primary navigation hub. It is divided into logical steps for the machine learning lifecycle.

<img width="489" height="425" alt="Navigation Sidebar" src="https://github.com/user-attachments/assets/d1e10b7e-4e1b-4977-a98f-25d4fec45ef7" />

* **Upload:** Where you bring in raw data (images or videos).
* **Annotate:** The workspace where you draw boxes and label objects.
* **Dataset:** Where your processed and versioned images live.

---

## 2. Uploading Your Data
Before a model can learn, it needs examples. In the **Upload** tab, you can drag and drop images directly from your computer.

<img width="742" height="461" alt="Upload Screen" src="https://github.com/user-attachments/assets/5ff736f5-dfbe-4646-b941-e364ca19ef72" />

For this tutorial, we are using a street-view image of New York City. This image contains many objects common in urban environments like cars, pedestrians, and traffic lights.

<img width="1427" height="594" alt="Uploaded Image Preview" src="https://github.com/user-attachments/assets/a032708f-3f34-4bcd-bb26-478b85cae086" />

* **Tip:** Ensure your images are diverse. If you only upload sunny photos, your model might struggle in the rain!

---

## 3. The Annotation Workflow
After uploading, your images move to the **Annotate** tab. Since we are building this from scratch, we will label the data ourselves.

<img width="1732" height="787" alt="Annotation Dashboard" src="https://github.com/user-attachments/assets/f8e37f7c-6363-48a7-b708-5bd46f267a42" />

1.  Click on the image batch.
2.  Select **Annotate Image**.
3.  Choose **Label Myself** to open the labeling editor.

---

## 4. Master the Labeling Tools
The vertical toolbar on the left of the editor contains everything you need to teach your model.

<img width="62" height="551" alt="Toolbar" src="https://github.com/user-attachments/assets/7f5ade31-6cad-42dd-a435-315b030bdc40" />

### The Bounding Box Tool
Since this is an **Object Detection** project, the **Bounding Box (B)** tool is our most important instrument.

<img width="280" height="171" alt="Bounding Box Tool" src="https://github.com/user-attachments/assets/6a92850b-60fa-4f63-8c86-391dbf8b3dbb" />


**How to label correctly:**
* **Click and Drag:** Click at one corner of an object and drag to the opposite corner.
* **Tight Fit:** Ensure the box fits the object as closely as possible. Excessive "empty space" inside the box can confuse the model.
* **Completeness:** Label every instance of the object in the image. If you miss one, the model might learn that the object is "background."
<img width="188" height="209" alt="image" src="https://github.com/user-attachments/assets/f7492c42-5d90-4abd-9762-d68e900b8755" />

# Finalizing Annotations and Class Management

Once you have drawn your bounding boxes, you must assign them to a **Class**. This tells the model not just *where* an object is, but *what* it is.

## 5. Creating and Assigning Classes
When you finish drawing a box, a pop-up will appear asking you to identify the object.

<img width="287" height="258" alt="Class Creation Pop-up" src="https://github.com/user-attachments/assets/448c109d-6176-46c1-b607-cddec94e4bf1" />

* **Naming Convention:** Give your class a clear, singular name (e.g., "Car" instead of "Cars").
* **Consistency:** Always use the exact same class name for the same type of object across your entire dataset.
* **Keyboard Shortcuts:** You can often press 'Enter' to quickly save the label or use number keys to select existing classes.

---

## 6. Preparing for Training
After you have meticulously annotated every object in your image, the status of that image will change from "Unannotated" to "Annotated."

### Checklist Before Moving On:
* **No Missing Labels:** Did you box every target object in the frame?
* **Correct Classes:** Are the labels accurate? (e.g., You didn't accidentally label a "Bus" as a "Car").
* **Occlusion:** If an object is partially hidden (like a car behind a tree), box the visible portion and ensure your project settings handle occlusions if necessary.

Once your images are fully annotated, you are ready to proceed to the **Generate** and **Train** phases to build your artificial intelligence model!
