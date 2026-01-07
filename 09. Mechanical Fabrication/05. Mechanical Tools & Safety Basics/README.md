# **Module 5 — Mechanical Tools & Safety Basics** 

This module is about the **basic tools** you will use again and again in robotics.  
If you learn these tools well, your builds will be:

* safer  
* faster  
* cleaner  
* stronger (parts won’t shake loose)  
* easier to fix later

A lot of robot problems come from simple tool mistakes like:

* using the wrong size tool  
* tightening too much and stripping threads  
* drilling a hole in the wrong spot  
* building parts slightly crooked (misalignment)

So this module focuses on **doing the basics correctly**.

---

## **5.1 Safety rules**

These rules sound obvious, but they prevent most lab accidents.

### **Always do these**

* **Wear eye protection** when drilling, cutting, grinding, or using power tools.  
* **Tie hair** and avoid loose sleeves near spinning tools.  
* **Remove rings / bracelets** (they can catch).  
* **Clamp your part** before drilling or cutting. Don’t hold it by hand.  
* **Keep the area clean** (metal chips are sharp, tools on floor are dangerous).  
* **Unplug/remove battery** before changing drill bits or blades.

### **A big safety rule**

If something is **spinning**, do not touch it.  
Wait for it to fully stop.

---

## **5.2 Hand tools**

### **A) Screwdrivers**

![][image7]

**Used for:** screws (Phillips “+”, flat “-”, sometimes Torx “star”).

**Common mistake:** using the wrong size → the head gets damaged (“stripped”).

**Simple tips**

* Use the correct tip size so it fits tight.  
* Push straight down while turning.  
* If it starts slipping, stop and change tool.

---

### **B) Allen keys / Hex keys**

![][image8]

Robotics uses these a lot (especially for M3, M4, M5 bolts).

**Used for:** socket-head bolts (the ones with a hex hole).

**Common mistake:** using a slightly wrong size → it rounds the hex hole.

**Simple tips**

* Make sure the hex key goes **all the way in** before turning.  
* Keep the key straight (don’t twist at an angle).  
* If the bolt is tight, don’t force it with a tiny L-key—use a better handle or a hex bit.

---

### **C) Wrenches and spanners**

![][image9]      ![][image10]

**Used for:** nuts and bolts with a flat head (hex head).

**Simple tips**

* Use the correct size. A loose wrench will slip and damage the nut.  
* If possible, use a **box-end** wrench (grips better than open-end).  
* If you can, use two tools: one holds the bolt head, one turns the nut.

---

### **D) Socket wrench (ratchet)**

![][image11]

**Used for:** nuts/bolts quickly, especially when there are many.

**Why it’s great**

* faster than a normal wrench  
* fits better and slips less

**Simple tip**

* Make sure the socket is fully seated on the nut before turning.

---

### **E) Pliers (normal, needle nose, circlip pliers, locking pliers)**

![][image12]![][image13]  
Normal Pliers & Nose Pliers  
![][image14]![][image15]  
Circlip Pliers  
![][image16]  
Locking Pliers

**Used for:**

* holding small parts  
* pulling zip ties  
* bending small metal tabs (light work)  
* grabbing something you can’t reach  
* Using circlip lock

**Common mistake:** using pliers as a wrench  
This can damage the nut/bolt.

**Simple rule:**  
Pliers are for **grabbing**, not for proper tightening.

---

### **F) Cutting tools (wire cutters, flush cutters)**

![][image17]![][image18]  
Wire cutters and Flush cutters

**Used for:**

* cutting zip ties  
* cutting wires  
* trimming small plastic parts

**Tip**

* Use the right cutter. Don’t cut steel wire with a small electronics cutter.

---

### **G) Files \+ sandpaper \+ deburring tool**

![][image19]  
Files

![][image20]  
Sandpapers

After cutting metal or plastic, edges can be sharp.

**Used for:**

* removing sharp edges  
* smoothing holes  
* making parts safer and cleaner

**Simple tip**

* Always deburr holes before assembly. It makes parts sit flat and fit better.

---

## **5.3 Power tools**

### **A) Power drill**

![][image21]

**Used for:**

* drilling holes  
* driving screws (carefully)

**Key idea:**  
A drill is strong. It can also ruin parts fast if you rush.

**Simple tips**

* Start slow. Speed up only when the hole is stable.  
* Clamp the workpiece.  
* Use a **pilot hole** first for bigger holes (small hole → bigger hole).  
* For metal, use slower speed and steady pressure.

**Common mistakes**

* drill bit slipping and scratching the part  
* drilling at an angle  
* holes ending up in the wrong place

**Fix**

* mark the center (pen or punch)  
* clamp  
* drill slowly at first

---

### **B) Impact driver**

![][image22]

**Used for:** driving screws fast (mainly in wood or thick materials).

**Be careful**  
Impact drivers hit hard. In robotics builds, they can:

* strip screw heads  
* strip threads  
* crack plastic parts

**Simple rule**  
Use impact driver only when you truly need it.  
For most robotics assembly, a drill with a clutch is safer.

---

### **C) Drill with clutch settings (very useful)**

![][image23]

Many cordless drills have a **clutch ring** (numbers).

**What it does**  
It stops the drill from pushing too hard.

**Why it’s good**  
It prevents:

* over-tightening  
* stripping threads  
* cracking plastic

**Simple tip**  
Start with a low number and increase only if needed.

---

## **5.4 Tightening bolts the right way**

### **The biggest beginner problem: over-tightening**

Over-tightening can:

* strip the thread (especially in aluminum or plastic)  
* break the bolt (small bolts can snap)  
* crush carbon fiber / plastic parts  
* bend thin plates

### **A simple tightening method (works well)**

1. Tighten until it becomes **snug** (it stops being loose)  
2. Then give a **small extra turn**  
3. Stop

If you feel the bolt suddenly gets “soft” while turning, stop.  
That usually means the thread is starting to strip.

### **Good habit: “tighten in steps”**

If a part has 4 bolts:

* put all bolts in first  
* tighten lightly first  
* then tighten more after everything is aligned

---

## **5.5 Avoiding misalignment**

Misalignment means parts are not lined up straight.  
This causes:

* bearings binding  
* shafts not spinning smoothly  
* gears not meshing properly  
* robot shaking

### **Easy alignment tips**

* **Do not fully tighten one bolt first.**  
  Put all bolts in, then tighten slowly in turns.  
* If it’s a plate with many bolts, tighten in a **cross pattern** (like a car wheel).  
* If something feels forced, don’t “fight it.”  
  Loosen, realign, then tighten again.

### **A good test**

After assembly:

* spin the shaft by hand (if it should spin)  
* move the joint by hand (if it should move)  
  If it feels tight or stuck, alignment is probably off.

---

## **5.6 Drilling holes**

### **Step 1: Mark the center**

Use a marker, then make a small dent if possible (center punch).  
This stops the drill bit from sliding.

### **Step 2: Clamp the part**

This is non-negotiable for safety.

### **Step 3: Drill a small pilot hole**

Example: drill 3 mm first, then 6 mm.

### **Step 4: Drill the final size**

Go slow for metal.

### **Step 5: Deburr the hole**

Remove sharp edges so parts sit flat.

---

## **5.7 Common mistakes**

### **Mistake 1: Stripping the screw head**

**Cause:** wrong tool size or angled tool  
**Fix:** correct bit size, push straight

### **Mistake 2: Stripping the threads**

**Cause:** over-tightening or bolt cross-threading  
**Fix:** start bolts by hand first, tighten slowly

### **Mistake 3: Cross-threading (bolt goes in wrong)**

**How it feels:** it “fights” from the start  
**Fix:** back out and restart straight (don’t force)

### **Mistake 4: Loose bolts from vibration**

**Fix options:**

* use locknuts (nyloc)  
* use spring washer (sometimes)  
* use threadlocker (only if your lab allows it)  
* recheck bolts after the first test run

### **Mistake 5: Holes don’t line up**

**Fix:**

* check your measurement  
* use slightly larger clearance holes (small increase helps a lot)  
* use proper alignment features (tabs/slots/spacers)

---

## **5.8 Simple “tool cheat sheet”**

Use this as a quick decision guide:

* Need to tighten a hex socket bolt → **Allen key / hex bit**  
* Need to tighten a nut → **wrench or socket**  
* Need holes → **drill press (best) or drill (careful)**  
* Need to hold a small part while working → **pliers**  
* Sharp edges after cutting → **file / deburr**  
* Need to drive lots of screws fast → **drill with clutch**  
* Not sure? → start with **hand tools** (slower but safer)
