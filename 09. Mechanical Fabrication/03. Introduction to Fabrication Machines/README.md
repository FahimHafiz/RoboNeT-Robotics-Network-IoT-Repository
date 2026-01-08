# **Module 3 — Introduction to Fabrication Machines**

In this module, I’ll explain the most common machines used in robotics fabrication:
<table align="center">
  <tr>
    <td align="center" valign="bottom">
      <img src="https://github.com/user-attachments/assets/f0a5b7ab-fdf9-42ae-8699-5b01ebd7f125" width="250" alt="3D Printer" /><br />
      <b>3D Printer</b>
    </td>
    <td align="center" valign="bottom">
      <img src="https://github.com/user-attachments/assets/1b7d1973-4813-41eb-82e5-cc6113843152" width="250" alt="Laser Cutter" /><br />
      <b>Laser Cutter</b>
    </td>
  </tr>
  <tr>
    <td align="center" valign="bottom">
      <img src="https://github.com/user-attachments/assets/a6b2f044-dd8c-4882-b933-81176e3803bd" width="250" alt="Lathe" /><br />
      <b>Lathe</b>
    </td>
    <td align="center" valign="bottom">
      <img src="https://github.com/user-attachments/assets/20772bbb-5b7d-4e3c-9d70-3539957b6891" width="250" alt="Drill Press" /><br />
      <b>Drill Press</b>
    </td>
  </tr>
</table>

The goal is simple:  
When you look at a robot part, you should know **which machine to use**, **why**, and **what problems to watch out for**.

---

## **3.1 Big idea: each machine is good at something**

A mistake beginners make is trying to use **one machine for everything**.  
But every machine has a “best job.”

Think like this:

* **3D printer** → best for *plastic shapes* and quick prototypes  
* **Laser cutter** → best for *flat sheets* and fast clean cuts  
* **CNC** → best for *strong accurate parts* (metal or plastic)  
* **Lathe** → best for *round parts* (shafts, spacers)  
* **Drill press** → best for *straight clean holes*

---

## **3.2 3D Printer (FDM) — “Print plastic parts”**
<p align="center">
<img width="1513" height="525" alt="image" src="https://github.com/user-attachments/assets/703f6a62-e11f-46dd-816a-713d2f45e796" />
</p>

### **What it does**

A 3D printer makes parts by melting plastic and putting it down layer by layer.

### **Best used for**

* quick **prototype parts** (version 1, version 2, etc.)  
* **covers** and **holders** (electronics box, sensor mount)  
* small brackets with light load  
* parts with weird shapes that are hard to cut from metal

### **Not great for**

* parts that take heavy force (like a motor mount in a high power drivetrain)  
* parts near heat (motors can warm up the area)  
* super accurate holes (holes can come out slightly off)

### **Common materials (simple)**

* **PLA**: easiest, stiff, but can crack and can soften in heat  
* **ABS**: tougher, handles heat better, but harder to print  
* **TPU**: flexible (rubber-like), for wheels/bumper, not for frames

### **Simple design tips**

* Don’t make thin “skinny” parts. Make them thicker.  
* Add extra material around bolt holes.  
* Use **nuts** or **inserts** if a bolt will be removed many times.  
* If a part must be strong, use ribs (extra support walls).

### **Safety**

* Don’t touch the hot nozzle or hot bed.  
* Be careful with fumes (especially ABS). Use ventilation.

---

## **3.3 Laser Cutter — “Cut flat parts fast”**
<p align="center">
<img width="1160" height="481" alt="image" src="https://github.com/user-attachments/assets/9cbac304-75b7-4d13-b858-ab88e97d6849" />
</p>

### **What it does**

A laser cutter cuts **2D shapes** from a flat sheet using a laser beam.

### **Best used for**

* **plates** (robot base plate, side plates)  
* brackets (flat style)  
* quick frame parts  
* parts that need to match shapes nicely (slot-tab designs)

### **Not great for**

* thick metal (most basic lasers can’t cut thick metal)  
* making round shafts (laser is for sheets, not rods)  
* parts that need deep 3D shape (laser is 2D cutting)

### **Materials it often cuts**

* acrylic  
* wood / MDF  
* cardboard  
* some plastics (depends on type)  
* **some laser cutters can cut thin metal**, but not all

Important: Some plastics are **dangerous** to laser cut (like PVC).  
Always check your lab rules.

### **Simple design tips**

* Laser cutting removes a tiny bit of material. This is called **kerf** (basically “cut width”).  
* If you want a tight fit (slot and tab), you may need to test and adjust.

### **Safety**

* Never leave a laser cutter running alone.  
* Fire risk is real (especially with wood).  
* Use proper ventilation.

---

## **3.4 Lathe — “Make round parts”**
<p align="center">
<img width="694" height="351" alt="image" src="https://github.com/user-attachments/assets/66991fe8-8fb4-441d-acd0-c7511cdedf61" />
</p>

### **What it does**

A lathe spins a rod (like metal or plastic) and cuts it to make it smooth and round.

### **Best used for**

* **shafts**  
* **spacers**  
* **bushings**  
* round standoffs  
* any part that looks like a cylinder

### **Not great for**

* flat plates (laser/CNC is better)  
* box shapes

### **Why it matters in robotics**

Robots often need:

* shafts for wheels, pulleys, gears  
* spacers for alignment  
* smooth round pieces for bearings

A lathe makes these parts clean and accurate.

### **Safety (very important)**

* No gloves near spinning machines (gloves can get pulled in).  
* Tie hair and remove loose items.  
* Don’t touch a spinning part.  
* Use correct tool setup (ask supervisor if unsure).

---

## **3.5 Drill Press — “Make straight clean holes”**
<p align="center">
<img width="455" height="401" alt="image" src="https://github.com/user-attachments/assets/730e951b-575a-4c0d-8dd7-b51ec79cb008" />
</p>

### **What it does**

A drill press makes holes straight down, with much better control than handheld drilling.

### **Best used for**

* drilling accurate holes in metal/wood/plastic  
* making bolt holes  
* enlarging holes slowly and cleanly  
* drilling many holes in the same spot accurately

### **Not great for**

* cutting shapes (it only makes holes)  
* drilling at weird angles (unless you have special setups)

### **Simple tips**

* Use a center punch (small dent) so the drill doesn’t slip.  
* Clamp your part. Don’t hold it by hand.  
* Use the right drill speed (metal usually needs slower speed than wood).

### **Safety**

* Always clamp the work.  
* Wear eye protection.  
* Remove the chuck key before turning on.

---

## **3.6 Quick guide: which machine should I use?**

Here’s an easy decision guide:

* I need a **quick plastic part** → **3D printer**  
* I need a **flat plate from a sheet** → **laser cutter**  
* I need a **strong and accurate metal part** → **CNC**  
* I need a **shaft or spacer** → **lathe**  
* I just need **clean straight holes** → **drill press**

---

## **3.7 Real robotics examples**

### **Example 1: Motor mount plate**

* If it’s plastic and low load → 3D print (temporary)  
* If it must stay stiff and aligned → CNC aluminum or steel

### **Example 2: Robot chassis (2D frame)**

* Fast and clean → laser cut plates  
* Stronger and more accurate → CNC plate

### **Example 3: Wheel shaft**

* Best option → lathe (clean shaft)  
* If no lathe → buy ready shaft and cut to length carefully

### **Example 4: Sensor bracket**

* Great for 3D print (easy shape \+ quick)  
* Add ribs so it doesn’t shake

---

## **3.8 Common beginner mistakes**

### **Mistake 1: Printing a “structural part” in PLA and expecting it to act like metal**

Fix: use thicker design, or move to aluminum/steel for load parts.

### **Mistake 2: Laser cutting and expecting perfect tight fits without testing**

Fix: make a small test piece first, adjust the slot size.

### **Mistake 3: CNC parts that are impossible to assemble**

Fix: leave tool access space for bolts and screws.

### **Mistake 4: Drilling by hand and getting angled holes**

Fix: use a drill press and clamp the part.

---

### [Next Chapter: DXF file, Laser Cutting](../04.%20%20DXF%20file,%20Laser%20Cutting/README.md)

---
