# **Module 6 — Welding & Lathe Operations**

<p align="center">
<img width="1151" height="577" alt="image" src="https://github.com/user-attachments/assets/2ce5ee26-dd65-4bc3-ae2e-8b164428f3e3" />
</p>

In robotics, you often reach a point where bolts and simple plates are not enough.  
This is where **welding** and **lathe work** become useful.

* **Welding** helps you join metal parts permanently.  
* A **lathe** helps you make clean, round parts like shafts and spacers.

This module explains **when to use them**, **how they work**, and **how to stay safe**.

---

## **6.1 When should I weld, and when should I not?**

Welding is strong, but it is not always the best choice.

### **Welding is a good idea when:**

* you want a **strong frame** that will not loosen over time  
* you want fewer bolts and less “shaking loose”  
* you need a part to act like **one solid piece**  
* the robot will take **hits** (combat-style robots, rough terrain robots, heavy robots)

### **Welding is NOT a good idea when:**

* you need to **take it apart later**  
* you need **very accurate alignment** (welding heat can bend parts)  
* you are still in early prototype stage (you will want changes)  
* the part is thin and easy to warp  
* you don’t have the right safety setup

**Simple rule:**  
If you think you will change the design soon → use bolts first.  
When the design is stable → welding can make it stronger.

---

## **6.2 Welding types (MIG, TIG, Arc) in simple words**

### **A) MIG welding (easy and common)**

<p align="center">
<img width="604" height="391" alt="image" src="https://github.com/user-attachments/assets/f294e7d4-7d2a-4626-bc3f-c6d9f6a5e26b" />
</p>

**What it is:**  
A welding gun feeds wire automatically, and it melts into the joint.

**Why people use it:**

* easier to learn than TIG  
* fast for frames  
* great for mild steel

**Good for:**

* robot frames  
* brackets  
* thick steel parts

**Not great for:**

* super thin metal (easy to burn through)  
* very “clean looking” welds (it can be messy if settings are wrong)

---

### **B) TIG welding (clean and precise)**

<p align="center">
<img width="583" height="385" alt="image" src="https://github.com/user-attachments/assets/870dc7d3-df80-466e-bae7-ff9168f18f11" />
</p>

**What it is:**  
You use a torch with a tungsten tip, and you add filler rod by hand (like “welding with a pen”).

**Why people use it:**

* very clean, neat welds  
* good control  
* great for aluminum and thin steel

**Good for:**

* nice looking welds  
* thin parts  
* aluminum builds

**Not great for:**

* fast work (TIG is slower)  
* beginners (harder than MIG)

---

### **C) Arc welding (stick welding)**

<p align="center">
<img width="557" height="398" alt="image" src="https://github.com/user-attachments/assets/4a6a0457-2b3f-4ffc-ba77-b657c30b1995" />
</p>

**What it is:**  
You use a “stick” electrode. The stick melts and makes the weld.

**Why people use it:**

* works outdoors  
* strong welds  
* equipment can be cheaper

**Good for:**

* thicker steel  
* rough work, outdoor work

**Not great for:**

* thin sheet metal  
* clean small robotics work (can be harder and more messy)

## **C) Mig Welding V/S Tig Welding **

### Working Principle

<p align="center">
<img width="1152" height="841" alt="image" src="https://github.com/user-attachments/assets/72742096-6730-4b1e-aebc-1dec853fa078" />
  <br>
  <em> Mig V/S Tig Principle </em>
</p>

### Welding Gun

<p align="center">
<img width="565" height="318" alt="image" src="https://github.com/user-attachments/assets/dabd1fd1-7b15-46c0-bd35-ef8649677adc" />
  <br>
  <em> Mig V/S Tig Principle </em>
</p>

### Select Based On Your Work

<div align="center">

| Feature | ARC | MIG | TIG |
| :--- | :---: | :---: | :---: |
| **Speed** | Moderate | Fast | Slow |
| **Cost (Cheap)** | Cheap | Moderate | High |
| **Ease of Learning** | Moderate | Moderate | Hard |
| **Precision** | Low | Moderate | High |
| **Thick Material** | Yes | Yes | No |
| **Thin Material** | No | Moderate | Yes |

</div>

---

## **6.3 What makes a weld strong (simple points)**

A strong weld is not just “more metal.” It’s about good preparation.

### **1\) Clean the metal**

Paint, rust, oil, dirt → weak weld and bad weld quality.

**Do this:**

* grind or sand the area  
* wipe off oil/grease

### **2\) Good fit before welding**

If the parts have gaps, welding becomes harder and weaker.

**Good habit:**

* clamp parts tight  
* check alignment  
* then tack weld (small weld points) first

### **3\) Correct heat**

Too little heat → weld doesn’t fuse well  
Too much heat → burn-through and warping

If you see:

* holes forming → too hot  
* weld sitting on top like a rope → not enough heat / wrong technique

### **4\) Weld size should match the job**

A small bracket doesn’t need huge welds.  
Big welds add weight and can warp parts more.

---

## **6.4 Warping (metal bending because of heat)**

<p align="center">
<img width="874" height="393" alt="image" src="https://github.com/user-attachments/assets/538ed45f-8c32-4c2a-b17c-6902e24f73e0" />
</p>

This is a big welding problem in robotics.

**What happens:**  
Welding heats metal a lot in one area. When it cools, it can pull and bend the part.

**How to reduce warping:**

* do **tack welds** first (4 corners, then check)  
* weld in **small steps**, not one long weld  
* weld on opposite sides (like “left side then right side”)  
* clamp parts to something flat if possible

**Simple idea:**  
Don’t “fully weld” until you are sure everything is straight.

---

## **6.5 Welding joints you will see a lot**

<p align="center">
<img width="1287" height="769" alt="image" src="https://github.com/user-attachments/assets/1c9b4755-42aa-4eb9-b3b4-48f3cb8e4671" />
</p>

* **Butt joint**: two pieces end-to-end  
* **Lap joint**: one piece overlaps another  
* **T-joint**: one piece meets another like a “T”  
* **Corner joint**: like building a box corner

For robot frames, **T-joints and corner joints** are very common.

---

## **6.6 Welding safety (very important)**

<p align="center">
<img width="1314" height="581" alt="image" src="https://github.com/user-attachments/assets/07b8331f-a52b-44bf-b46a-ad3535b8fe3a" />
</p>

Welding is not like normal tools. It has strong light, heat, and fumes.

### **Always use:**

* welding helmet (correct shade)  
* welding gloves  
* long sleeves (protect skin)  
* closed shoes  
* good ventilation (fumes are real)

### **Big safety rules:**

* Don’t look at the arc without a helmet (it can hurt your eyes badly)  
* Keep flammable stuff away (paper, alcohol, rags, plastic)  
* Hot metal looks the same as cold metal. Assume it’s hot.

---

## **6.7 When machining is better than welding**

Sometimes welding is strong, but machining gives better accuracy.

Choose machining (CNC/lathe) when:

* you need **straight shafts**  
* you need **bearings to align**  
* you need **holes in the right spot**  
* you need **parts to spin smoothly**

**Simple example:**  
If a bearing seat is even slightly off, your shaft will bind.  
So that part should be machined, not welded.

---

# **Lathe Section**

## **6.8 What is a lathe**

<p align="center">
<img width="1229" height="609" alt="image" src="https://github.com/user-attachments/assets/0026680f-5c1f-4977-ae30-02868dfaf773" />
</p>

A **lathe** is a machine that spins a round piece (like a rod), and a cutting tool shapes it.

If you need a part that is:

* round  
* smooth  
* same size all the way  
* accurate

---

## **6.9 Common lathe parts in robotics**

You will often make:

* **shafts** (for wheels, pulleys, gears)  
* **spacers** (to keep parts aligned)  
* **standoffs** (like a spacer but used for mounting)  
* **bushings** (simple bearings)  
* **bearing seats** (a step where a bearing fits)

These parts sound small, but they make assemblies feel “professional.”

---

## **6.10 Basic lathe operations**

<p align="center">
<img width="1585" height="889" alt="image" src="https://github.com/user-attachments/assets/fd69591f-bddd-49c4-8574-ecb70a5f855f" />
</p>

### **A) Turning**

**Meaning:** making the outside diameter smaller and smooth.

Example: turning a 10 mm rod down to 8 mm.

---

### **B) Facing**

**Meaning:** making the end of the part flat and clean.

Example: after cutting a rod, the end is rough. Facing makes it flat.

---

### **C) Drilling (on a lathe)**

You can drill into the center of a spinning part.

Example: hole for a bolt through a spacer.

---

### **D) Boring**

**Meaning:** making an inside hole larger and more accurate.

Example: you drilled a hole, but it’s not the right size. Boring makes it exact.

---

### **E) Parting (cut-off)**

**Meaning:** cutting the finished part off the rod.

This is how you make spacers in the correct length.

---

## **6.11 Why accuracy matters**

In robotics, a tiny error can become a big problem.

Example:

* a shaft is slightly too big → bearing won’t fit  
* a shaft is slightly too small → bearing is loose and wobbles  
* spacer length is wrong → plates squeeze bearings and the shaft won’t spin

**Simple rule:**  
If parts rotate, accuracy matters more.

---

## **6.12 Lathe safety**

A lathe is dangerous if you treat it casually.

### **Never do these:**

* don’t wear gloves (gloves can get pulled in)  
* don’t wear loose sleeves  
* don’t lean close to a spinning part  
* don’t leave the chuck key in the chuck (remove it immediately)

### **Always do these:**

* wear eye protection  
* tie hair  
* check the part is clamped tight  
* start at low speed if you’re unsure  
* keep hands away from spinning parts

### **Lathe rule:**  
**Spinning machines don’t forgive mistakes.**

---

## **6.13 Common beginner mistakes**

### **Welding mistakes**

**1\) Welding without cleaning metal**

* Fix: grind/sand and wipe first

**2\) Welding first, then checking alignment**

* Fix: tack weld first, check, then weld

**3\) Too much heat**

* Fix: shorter welds, pauses, better settings

---

### **Lathe mistakes**

**1\) Part not clamped tight**

* Fix: tighten properly and re-check before starting

**2\) Cutting too deep in one pass**

* Fix: take small cuts, be patient

**3\) Wrong speed**

* Fix: start slow, increase slowly

**4\) Not measuring**

* Fix: measure often (diameter and length)

---

### [Next Chapter: Nut, Bolts, Bearings & Fasteners](../07.%20Nuts,%20Bolts,%20Bearings%20&%20Fasteners/README.md)

---
