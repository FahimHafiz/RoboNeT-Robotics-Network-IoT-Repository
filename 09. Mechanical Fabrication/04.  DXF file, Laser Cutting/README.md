# **Module 4 — DXF Files, Laser Cutting** 

In this module you will learn how to go from a CAD design to a real part using:

* **DXF files** (the file type many machines understand)  
* **Laser cutting** (fast cutting from sheet)

And most important: you will learn how to make parts that **actually fit together** when you assemble them.

---

## **4.1 What is a DXF file (simple meaning)**

A **DXF** file is a drawing file that stores **lines and shapes** (2D).

Think of it like this:

* CAD part \= full 3D model  
* DXF \= a flat “top view” or “side view” outline the machine can cut

Most laser cutters and many CNC workflows love DXF because it is clean and simple.

**DXF is mainly used for:**

* cutting a shape from a sheet (plate)  
* making holes and slots  
* making flat parts that later become a 3D structure

---

## **4.2 DXF is usually 2D (and that’s okay)**

Many robotics frames start as **flat plates**:

* base plate  
* side plates  
* motor mount plates  
* brackets  
* gearboxes plates  
* sensor plates

Then you connect them using:

* bolts and nuts  
* tabs and slots  
* spacers  
* angle brackets  
* welding (sometimes)

So even though DXF is “flat”, you can build a strong 3D robot body from flat parts.

---

## **4.3 How to export DXF from Fusion 360**

Different CAD software has different buttons, but the idea is always the same:

### **Step 1: Choose the flat face / sketch**

* Select the top face for sketch (mandatory)  
* Design the sketch or use the project tool for the component to get the outline.

### **Step 2: Export as DXF**

Common export names:

* “Export DXF”  
* “Save as DXF”  
* “Export sketch to DXF”

### **Step 3: Check units (very important)**

If your design is in **mm**, export in **mm**.  
If it exports in **inches** by mistake, your part size becomes wrong.

**Simple rule:**  
Always open the DXF once (in the laser/CNC software) and measure a known distance to confirm size.

---

## **4.4 DXF cleaning (make the file machine-friendly)**

Sometimes DXF files have extra stuff that causes problems.

Before cutting, check:

###  **Only the needed lines**

Remove:

* extra construction lines  
* duplicate lines (two lines on top of each other)  
* random points

###  **Closed shapes are better**

For cutting, the outline should be a **closed loop** (like one clean boundary).

If the outline has small gaps, the machine may:

* not cut properly  
* cut in weird order  
* skip the shape

###  **Use layers (if your lab uses them)**

Some labs like using layers such as:

* CUT  
* ENGRAVE (marking lines)  
* SCORE (light cut for fold/bend)

If you don’t need layers, keep it simple—just make clean cutting lines.

---

## **4.5 Laser cutting basics (what it does)**

A laser cutter is best for **fast cutting from a sheet**.

You place a sheet material on the bed (like acrylic, wood, thin metal if your machine supports it), and the laser follows your DXF lines.

**Laser cutting is great for:**

* fast prototypes  
* plates with lots of holes  
* tab-slot parts  
* clean edges (especially in acrylic)

---

## **4.6 The kerf problem (why parts don’t fit)**

When a laser cuts, it removes a tiny bit of material.  
That removed width is called **kerf** or **offset**

**Simple meaning:**  
The cut is not “zero thickness.” It has a tiny width.

### **Why kerf matters**

If you design a slot that is exactly the same size as the tab, the cut will remove material and the fit changes.

So you must design with kerf in mind.

### **Easy way to handle kerf (best method)**

Don’t guess the kerf. **Measure it.**

**Kerf test idea:**

1. Cut a small rectangle that should be, for example, 20 mm wide  
2. Measure the cut piece with a caliper/ruler  
3. The difference helps you understand your machine’s cut behavior

Every machine \+ material \+ setting can change kerf.

---

## **4.7 Tolerance**

**Tolerance** means: how much “extra space” or “tightness” you allow so parts can fit.

Real life is not perfect. Even if CAD is perfect.

So we design plus/minus the kerf or offset.

* holes slightly bigger for bolts  
* slots slightly bigger/smaller depending on fit we want

---

## **4.8 Fit types (how tight should it be?)**

In robotics, fit matters a lot. Here are the main fit types in easy words:

### **1\) Loose fit (easy to assemble)**

* parts slide in easily  
* good for quick assembly  
* not great if you need perfect alignment

Use for:

* covers  
* quick frame plates  
* parts you will remove often

### **2\) Normal fit (good balance)**

* parts fit well  
* not too hard to assemble  
* holds shape better

Use for:

* frame tab-slot builds  
* brackets and mounts

### **3\) Tight fit (hard to assemble, but strong)**

* needs force to push together  
* very stable if done right  
* can crack weak materials (like acrylic)

Use for:

* press-fit style designs (careful\!)  
* special joints where you want no movement

**Best beginner advice:**  
Start with **normal fit**, then adjust after a test cut.

---

## **4.9 Tab-and-slot design**

Tab-slot is the most common way to build 3D structures from flat plates.

### **What is it?**

![][image6]

* **Tab** \= the sticking-out part  
* **Slot** \= the hole that tab goes into

### **Why it’s good**

* parts self-align  
* assembly is faster  
* frame becomes stronger (less twisting)

### **Simple design tips**

* Add **enough tabs** (more tabs \= better alignment)  
* Make tabs longer than the sheet thickness  
* Avoid tiny thin tabs (they snap)  
* Add bolt holes near tabs if you want extra strength

---

## **4.10 Hole sizes for bolts (very practical)**

Bolts rarely fit nicely in “exact size holes.”

Example idea:

* If bolt is 5 mm, you often design a hole slightly bigger (so it goes in easily)

Why?

* drilling/cutting is not perfect  
* alignment shifts during assembly  
* you want easy building, not fighting holes

**Repo tip:**  
Make a small “hole size test strip” once and reuse the results for future projects.

---

## **4.11 Assembly tips (make your parts buildable)**

Here’s what makes assembly smooth:

### **1\) Add tool space**

Leave room for:

* Allen key  
* wrench  
* screwdriver

A design can look perfect but become impossible to tighten.

### **2\) Use spacers and standoffs**

Spacers help:

* keep plates parallel  
* avoid rubbing  
* keep alignment stable

### **3\) Do a test-fit before final build**

Before you fully tighten everything:

* loosely assemble  
* check if parts sit flat  
* check alignment  
* spin moving parts by hand (if possible)

Then tighten.

---

## **4.12 Common mistakes (and easy fixes)**

### **Mistake 1: DXF exported in wrong size**

**Fix:** check units, measure inside the cutting software.

### **Mistake 2: Slots too tight (parts don’t go in)**

**Fix:** enlarge slot a little or reduce tab size. Do a small test first.

### **Mistake 3: Forgetting kerf**

**Fix:** cut a test piece and adjust.

### **Mistake 4: Holes don’t line up in assembly**

**Fix:** slightly larger holes \+ better alignment features (tabs, jigs).

---

## **4.13 Simple “before you cut” checklist**

Before cutting any real part:

* Units are correct (mm vs inch)  
* No duplicate lines  
* All outlines are closed shapes  
* Kerf/fit tested (at least once)  
* Bolt holes are slightly bigger than bolt  
* Tool access space exists (wrench/Allen key)  
* Plan how parts will assemble
