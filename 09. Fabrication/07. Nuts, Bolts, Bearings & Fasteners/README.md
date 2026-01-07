# **Module 7 — Nuts, Bolts, Bearings & Fasteners**

This module is about the small parts that hold your robot together:

* nuts and bolts  
* washers  
* locknuts  
* spacers and standoffs  
* bearings and bushings

These look “small”, but they decide if your robot feels:

* solid or shaky  
* smooth or stuck  
* easy to repair or painful to repair

A lot of robots fail because of:

* wrong bolt length  
* loose bolts from vibration  
* bad bearing alignment  
* squeezing bearings too hard  
* using the wrong washer or no washer  
  ---

## **7.1 Nuts and bolts (basic idea)**

![][image30]

A **bolt** goes through holes and holds parts together.  
A **nut** goes on the end of the bolt to clamp the parts.

In robotics, we mostly use:

* **M3** (small robots, electronics mounts)  
* **M4 / M5** (frames, motor mounts)  
* **M6** (bigger load areas)

*(M number means the bolt diameter in mm. Example: M5 is \~5 mm.)*

---

## 

## **7.2 How to choose the correct bolt**

### **Step 1: Choose the bolt thickness (M3, M4, M5…)**

Pick thicker bolts when:

* the part takes more force  
* the part vibrates a lot  
* it’s a frame or motor mount

Pick smaller bolts when:

* the part is light  
* it’s a cover or sensor mount

### **Step 2: Choose the bolt length**

A simple way:

* add the thickness of the parts you are joining  
* add washer thickness (if using)  
* add enough extra so the nut fully grabs the threads

**Simple rule:**  
After tightening, the bolt should stick out past the nut by about **1–3 threads**.  
Not too long, not too short.

### **Step 3: Choose bolt head type**

Common bolt heads:

* **Socket head (Allen key)**: very common in robotics, strong, clean  
* **Hex head (wrench)**: strong, easy to tighten, but needs more space  
* **Button head (Allen key, rounded)**: nice look, lower profile, not as strong as socket head  
  ---

## **7.3 Washers**

![][image31]

A washer is a simple metal ring, but it helps a lot.

### **What washers do**

* spread the force so the bolt doesn’t damage the part  
* help prevent parts from cracking (especially plastic and carbon fiber)  
* protect surfaces from getting scratched  
* help bolts stay tight (in some cases)

### **When you should always use washers**

* with **plastic parts**  
* with **carbon fiber**  
* on thin metal plates  
* when the bolt head is small and may dig into the part

**Simple tip:**  
If you see the bolt head “sinking into” the material, you need washers.

---

## **7.4 Locking methods**

Robots vibrate. Motors shake. Driving creates shocks.  
So bolts slowly loosen if you don’t lock them.

### **A) Locknut (nyloc nut)**

![][image32]

This is the nut with a blue/white nylon ring inside.

**Why it’s good**

* it resists loosening  
* very common in robotics  
* easy to use

**When to use**

* frames  
* motor mounts  
* any place with vibration

**Simple note:**  
After many uses, nylon wears out. Replace if it feels too easy to turn.

---

### **B) Spring washer (split washer)**

![][image33]

Looks like a cut ring.

**Use**

* sometimes helps, but not the best in many robotics builds

Many teams prefer locknuts or threadlocker instead.

---

### **C) Threadlocker (like Loctite)**

![][image34]

This is a liquid you put on threads to stop loosening.

**Good**

* strong against vibration  
* clean assembly

**Bad**

* makes removal harder  
* not always allowed in some labs  
* you must choose correct type (removable vs permanent)

**Simple rule:**  
Use it only when you’re sure you won’t need quick removal.

---

## **7.5 Spacers, standoffs, and why they are important**

### **Spacer (simple meaning)**

![][image35]

A spacer is a small tube (metal or plastic) that keeps distance between parts.

**Why spacers are used**

* keep two plates parallel  
* stop parts from rubbing  
* keep bearings from being squeezed  
* maintain alignment

### **Standoff**

![][image36]

A standoff is like a spacer with threads (often used for electronics boards).

**Common use**

* mounting Arduino, Raspberry Pi, motor drivers

**Simple tip:**  
Spacers and standoffs make your robot look clean and also reduce mistakes.

---

## **7.6 Bearings**

![][image37]

A **bearing** lets a shaft spin smoothly with less friction.

### **Where bearings show up in robotics**

* wheel shafts  
* arm joints  
* gear shafts  
* rollers  
* pulleys

If bearings are installed wrong, you will feel:

* stiffness  
* heat  
* noise  
* wobble  
  ---

## **7.7 Bearings vs bushings**

![][image38]

### **Bearing**

* has small balls inside  
* spins very smoothly  
* good for fast motion and low friction

### **Bushing**

* simple sleeve (no balls)  
* cheaper and simpler  
* more friction than bearings  
* can be good for slow joints and dirty environments

**Simple rule:**

* if it must spin fast and smooth → bearing  
* if it’s slow, simple, cheap → bushing  
  ---

## **7.8 How to install bearings the correct way**

This is one of the most important skills.

### **The golden rule**

**Do not push through the balls.**  
You should press the bearing using the correct ring.

Bearings have:

* **outer ring** (outside)  
* **inner ring** (inside)

### **If you are pressing a bearing into a hole (housing)**

Press on the **outer ring**.

### **If you are pushing a shaft into the bearing**

Press on the **inner ring**.

If you press the wrong ring, you can damage the bearing and it won’t spin well.

---

## **7.9 Alignment and load direction**

### **Alignment**

Bearings need to sit straight. If they sit tilted:

* shaft binds  
* bearing wears fast  
* motion becomes rough

### **Load direction**

Bearings are good for certain types of force:

* **side force** (radial) like wheel load is okay  
* **push/pull along shaft** (axial) depends on bearing type

Most simple bearings are mainly happy with **side loads**.

---

## **7.10 Preload**

Preload means you tighten things so there is **no looseness**, but also not so tight that it binds.

If too loose:

* wobble and play

If too tight:

* stiffness, heat, bearing damage

**How to find a good preload**

* tighten slowly  
* spin the shaft by hand  
* stop when wobble is gone but it still spins freely  
  ---

## **7.11 Common fastener mistakes**

### **Mistake 1: Bolt too short**

**Problem:** nut doesn’t grab enough threads → weak joint  
**Fix:** choose longer bolt

### **Mistake 2: Bolt too long**

**Problem:** hits other parts, looks messy, can block motion  
**Fix:** shorter bolt or add spacer

### **Mistake 3: No washer on plastic/carbon fiber**

**Problem:** cracks or crushed material  
**Fix:** add washers

### **Mistake 4: No locking method in vibration areas**

**Problem:** bolts loosen during driving  
**Fix:** locknuts or threadlocker

### **Mistake 5: Bearing pressed wrong**

**Problem:** bearing becomes rough  
**Fix:** press on correct ring (outer vs inner)

### **Mistake 6: Bearing alignment ignored**

**Problem:** shaft doesn’t spin freely  
**Fix:** realign plates, use spacers, ensure holes are correct

---

## **7.12 Quick “which fastener should I use?” guide**

* Frame joint with vibration → **bolt \+ washer \+ nyloc nut**  
* Electronics mount → **standoff \+ small screws**  
* Plastic part → **bolt \+ large washer**  
* Something you remove often → **bolt \+ washer \+ locknut** (or normal nut if you check often)  
* Rotating shaft area → **bearing \+ spacer \+ correct preload**
