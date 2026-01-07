# **Module 3 — Introduction to Fabrication Machines**

In this module, I’ll explain the most common machines used in robotics fabrication:

* **3D Printer**  
* **Laser Cutter**  
* **CNC Machine**  
* **Lathe**  
* **Drill Press**

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

![][image1]

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

![][image2]

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

## **3.4 CNC Machine — “Cut strong parts accurately”**

![][image3]

### **What it does**

CNC is a computer-controlled machine that cuts material using spinning tools (like an automatic milling machine).

In simple words:  
**CNC removes material to shape your part.**

### **Best used for**

* strong metal parts (aluminum is very common)  
* accurate holes and flat surfaces  
* gearbox plates, motor plates, bearing plates  
* parts where alignment matters a lot

### **Not great for**

* fast “same day quick part” if setup time is long  
* very thin sheets (laser can be quicker)  
* super complex shapes without experience

### **Materials it can cut**

* aluminum (very common)  
* plastics (like acrylic, Delrin, etc.)  
* wood (sometimes)  
* steel (depends on machine power)

### **Simple design tips**

* Leave space for bolts and tools (wrench/allen key clearance).  
* Plan how the part will be held (clamps or vise).  
* Try to avoid super tiny features if you’re new.

### **Safety**

* Wear eye protection.  
* Keep hands away from the spinning tool.  
* Tie hair, avoid loose clothing.  
* Chips can be sharp and hot.

---

## **3.5 Lathe — “Make round parts”**

### **![][image4]**

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

## **3.6 Drill Press — “Make straight clean holes”**

![][image5]

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

## **3.7 Quick guide: which machine should I use?**

Here’s an easy decision guide:

* I need a **quick plastic part** → **3D printer**  
* I need a **flat plate from a sheet** → **laser cutter**  
* I need a **strong and accurate metal part** → **CNC**  
* I need a **shaft or spacer** → **lathe**  
* I just need **clean straight holes** → **drill press**

---

## **3.8 Real robotics examples**

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

## **3.9 Common beginner mistakes**

### **Mistake 1: Printing a “structural part” in PLA and expecting it to act like metal**

Fix: use thicker design, or move to aluminum/steel for load parts.

### **Mistake 2: Laser cutting and expecting perfect tight fits without testing**

Fix: make a small test piece first, adjust the slot size.

### **Mistake 3: CNC parts that are impossible to assemble**

Fix: leave tool access space for bolts and screws.

### **Mistake 4: Drilling by hand and getting angled holes**

Fix: use a drill press and clamp the part.
