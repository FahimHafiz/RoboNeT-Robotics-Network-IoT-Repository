# **Module 9 — Putting It All Together: Prototyping Workflow**

This module explains the full workflow from idea → CAD → real parts → final working prototype.

In robotics, you usually don’t make the “final robot” in one try.  
Most people build like this:

**Version 1 → test → fix → Version 2 → test → fix → Version 3…**

That is normal. That is how real engineering works.

---

## **9.1 The full workflow**

Here is the common path:

1. **Plan the design**  
2. **Make CAD model**  
3. **Choose materials**  
4. **Choose fabrication method** (3D print / laser / CNC / welding)  
5. **Make parts**  
6. **Test-fit parts** (before final tightening)  
7. **Assemble fully**  
8. **Test the robot**  
9. **Fix problems**  
10. **Make improved version**

---

## **9.2 Step 1: Plan first**

Before CAD, write simple things:

* What is the robot supposed to do?  
* How much weight will it carry?  
* How fast will it move?  
* Where are the motors, wheels, battery, and controller going?  
* What parts need to move?  
* Where might it hit or crash?

Even a rough sketch helps.

**Simple tip:**  
If you don’t plan, you will redesign later anyway, but with more pain.

---

## **9.3 Step 2: CAD model**

When making CAD, always think about:

### **A) How will I assemble it?**

* Can I fit a wrench inside?  
* Can I insert bolts easily?  
* Can I remove parts later?

### **B) What needs to be strong?**

* motor mount area  
* wheel area  
* arm joint area  
* frame corners

### **C) What needs good alignment?**

* bearings  
* shafts  
* gears and pulleys  
* belt/chain paths

**Simple tip:**  
Robots fail when moving parts are not aligned.

---

## **9.4 Step 3: Choose the material**

* quick test part → PLA  
* tougher print part → ABS  
* flexible part → TPU  
* strong light frame → aluminum  
* very strong frame → steel  
* light stiff plate → carbon fiber (if safe)

Pick material based on the job.

---

## **9.5 Step 4: Choose how to make the part**

### **Use 3D printer when:**

* you need fast prototype  
* shape is complex  
* part is not under heavy load

### **Use laser cutting when:**

* part is flat plate from sheet  
* you want fast cutting  
* you want tab-slot assembly

### **Use CNC when:**

* you need accurate holes  
* you need strong metal parts  
* alignment is critical (bearing plates, motor plates)

### **Use welding when:**

* you want a strong permanent frame  
* design is already stable (not changing every day)

---

## **9.6 Step 5: Make parts (prototype first, not perfect)**

Before cutting expensive material, do a cheap test.

### **Good prototype ideas**

* cardboard/wood quick model (size check)  
* PLA print (fit check)  
* laser cut acrylic/wood (shape and assembly check)

**Simple tip:**  
Prototype is not waste. Prototype saves money and time.

---

## **9.7 Step 6: Test-fit (most important step)**

A test-fit means you assemble parts loosely before final build.

### **Why test-fit matters**

Because you catch problems early:

* holes don’t line up  
* slots are too tight  
* tools can’t reach screws  
* bearings are not aligned  
* parts rub and block movement

### **How to test-fit correctly**

* assemble with bolts but don’t fully tighten yet  
* check if plates sit flat  
* check if shafts rotate  
* check if nothing is rubbing  
* only after everything looks correct → tighten slowly

---

## **9.8 Step 7: Assembly (build it clean)**

### **Assembly rules**

* Put all bolts in first, then tighten  
* Tighten evenly (don’t fully tighten one corner first)  
* Use washers on soft materials  
* Use locknuts in vibration areas  
* Add spacers where needed for alignment

### **Simple “good build feeling”**

A well-built robot feels:

* solid  
* smooth  
* no rattling  
* no forced parts

---

## **9.9 Step 8: Testing the robot (real test)**

Testing is not just “it moves.” You should test like this:

### **Test A: Basic movement test**

* drive slowly  
* check if wheels spin freely  
* check if it pulls to one side

### **Test B: Load test**

* put a small load first  
* increase load slowly  
* watch for bending, slipping, strange noises

### **Test C: Vibration test**

* run motors for a while  
* check if bolts loosen  
* check if parts shake too much

### **Test D: Heat test (if needed)**

* run for a few minutes  
* check motor area temperature  
* check if PLA is getting soft (if used)

---

## **9.10 Step 9: Fixing problems (common ones)**

Here are common problems and what they usually mean:

### **Problem: robot makes rattling noise**

* bolts may be loose  
* parts may be hitting each other

Fix:

* tighten bolts  
* add washers/spacers  
* check for rubbing

### **Problem: shaft feels hard to spin**

* bearing misalignment  
* bearing squeezed too tight  
* shaft not straight

Fix:

* loosen and realign  
* check spacers  
* check shaft/bearing fit

### **Problem: chain/belt slips**

* wrong tension  
* misalignment

Fix:

* adjust tension  
* align sprockets/pulleys

### **Problem: bracket bends**

Fix:

* thicker material  
* add ribs/gussets  
* move bolts farther apart  
* shorten lever arm (reduce bending)

---

## **9.11 Version system**

It helps to label changes like:

* V1: works but weak  
* V2: stronger mounts, better alignment  
* V3: lighter, cleaner assembly, easy maintenance

### **What to write down each version**

* what failed?  
* why did it fail?  
* what did you change?  
* did it fix the problem?

This documentation is gold for a repo.

---

## **9.12 Simple “prototyping checklist”**

Before making final parts:

* CAD includes tool access space  
* material chosen for load  
* prototype done (at least one test version)  
* holes/slots tested for fit  
* test-fit assembly done  
* shaft rotation checked  
* bolts locked for vibration  
* nothing rubs during movement

---

### [Next Chapter: Assembly & Troubleshooting ](../10.%20Assembly%20&%20Troubleshooting/README.md)

---
