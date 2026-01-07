# **Module 10 — Assembly & Troubleshooting**

This module is about building the full robot cleanly and fixing common problems.

Even if your parts are perfect, a robot can still fail because of:

* wrong assembly order  
* parts not aligned  
* bolts not tightened correctly  
* bearings squeezed too hard  
* shafts not straight  
* loose fits causing wobble (play)  
* gears/belts/chains not aligned

So here we focus on:

1. **how to assemble properly**  
2. **how to find problems**  
3. **how to fix them**

---

## **10.1 Before assembly: plan the order (don’t rush)**

A good assembly feels smooth. A rushed assembly becomes messy.

### **Simple planning steps**

* Put all parts on the table  
* Group them:  
  * frame parts  
  * moving parts (shafts, bearings, joints)  
  * fasteners (bolts, nuts, washers)  
  * electronics mounting (standoffs, plates)  
* Read your CAD and decide:  
  * what must go first  
  * what will be blocked later

**Simple tip:**  
If a bolt becomes impossible to reach later, install it earlier.

---

## **10.2 Frame assembly (make the base strong and straight)**

The frame is like the skeleton of the robot.

### **Frame assembly rules**

* Put all bolts in first (do not tighten fully)  
* Check the frame is sitting flat (not twisted)  
* Tighten slowly and evenly  
* Use locknuts for vibration areas

### **How to check if the frame is twisted**

* Put it on a flat surface (table)  
* Press corners lightly  
  If it rocks, it’s twisted.

Fix:

* loosen bolts  
* push it flat  
* tighten again evenly

---

## **10.3 Bearings and shafts (most common source of problems)**

If bearings and shafts are wrong, everything feels rough.

### **Easy bearing \+ shaft rules**

* Bearings must sit straight  
* Shafts must be straight  
* Use spacers so parts don’t rub  
* Tightening should not “squeeze” bearings too much

### **The best test**

After assembly, spin the shaft by hand.

* If it spins smooth → good  
* If it feels tight/rough → something is wrong

---

## **10.4 Alignment (simple meaning)**

Alignment means parts line up correctly.

If alignment is bad:

* bearings bind  
* gears make noise  
* belt/chain slips  
* robot vibrates more

### **Easy alignment tips**

* Don’t force parts into place  
* If holes don’t line up, fix alignment—not force bolts  
* Use spacers to keep plates parallel  
* Tighten bolts evenly (not one side fully first)

---

## **10.5 “Loose fit” and “lash” (why it happens)**

### **Loose fit means:**

Parts have too much free movement.

This causes:

* wobble  
* vibration  
* shaking sensors  
* inaccurate motion

### **Lash (backlash) means:**

When you move a gear/shaft, it can move a little before it actually “catches.”

Backlash is common in:

* gears  
* chain drives  
* belt drives (if loose)  
* joints with loose bolts

Some backlash is normal, but too much is bad.

---

## **10.6 Fixing common issues (easy troubleshooting guide)**

### **Problem 1: Shaft is hard to rotate**

**Common reasons**

* bearings not aligned  
* bearings pressed wrong  
* bolts too tight squeezing the bearing area  
* shaft bent  
* something rubbing

**Fix steps**

1. Loosen the bearing plate bolts slightly and test again  
2. Check if spacers are correct length  
3. Check shaft straightness (roll it on a flat table)  
4. Look for rubbing marks

---

### **Problem 2: Bearings feel rough or noisy**

**Common reasons**

* pressed using wrong ring  
* dirt inside bearing  
* bearing damaged from force  
* misalignment

**Fix steps**

* remove bearing and check  
* clean area  
* reinstall carefully  
* replace bearing if it still feels rough

---

### **Problem 3: Robot frame shakes a lot**

**Common reasons**

* loose bolts  
* weak frame (flex)  
* wheels not balanced  
* motor mount flexing

**Fix steps**

* tighten \+ use locknuts  
* add gussets/brackets  
* increase thickness or add support ribs  
* check wheels and shafts

---

### **Problem 4: Bolts keep getting loose**

**Common reasons**

* vibration  
* no locknuts  
* soft material compressing under bolt head

**Fix steps**

* use locknuts  
* add washers  
* use threadlocker (if allowed)  
* recheck bolts after first run

---

### **Problem 5: Parts rubbing each other**

**Common reasons**

* wrong spacer length  
* misalignment  
* parts shifting during tightening

**Fix steps**

* add/adjust spacers  
* realign plates  
* tighten slowly and evenly

---

### **Problem 6: Gear system noisy or skipping**

**Common reasons**

* gear not aligned  
* gear mesh too tight or too loose  
* shaft wobble

**Fix steps**

* align gears in the same plane (straight line)  
* adjust distance between gears  
* check if shaft is supported well (bearings both sides helps)

---

### **Problem 7: Belt/chain slipping**

**Common reasons**

* too loose tension  
* pulleys/sprockets not aligned  
* motor mount flexing

**Fix steps**

* adjust tension  
* align pulleys/sprockets  
* strengthen motor mount

---

### **Problem 8: Holes don’t match during assembly**

**Common reasons**

* measurement mistakes  
* tolerance too tight  
* parts warped (welding heat or thin plates)

**Fix steps**

* use slightly larger clearance holes next time  
* use a file to correct small mismatch (for prototypes)  
* redesign with alignment features (tabs/slots)

---

## **10.7 Common assembly mistakes (and how to avoid)**

### **Mistake 1: Tightening one bolt fully first**

This pulls the frame crooked.

Fix:

* put all bolts in first  
* tighten little by little

### **Mistake 2: Over-tightening into plastic**

This cracks parts.

Fix:

* washers  
* snug only  
* use inserts or nuts

### **Mistake 3: Forgetting tool access**

You can’t tighten or remove later.

Fix:

* design space for Allen key/wrench in CAD

### **Mistake 4: Not checking spin/movement before final tightening**

Fix:

* always test movement before final torque

---

## **10.8 Final “robot assembly checklist” (super useful in repo)**

### **Before power-on**

* frame is flat and not twisted  
* all main bolts tight  
* locknuts used on vibration areas  
* wires are not near moving parts  
* wheels spin freely by hand  
* shafts rotate smoothly  
* gears/belts/chains aligned  
* no rubbing anywhere

### **After first test run (very important)**

* recheck bolts (some will loosen first time)  
* check heat near motors  
* check for new scratches (rubbing signs)  
* listen for new noises

---

## **10.10 End of mechanical fabrication section**

If someone follows these 10 modules and actually tries the mini tasks, they will learn:

* how to choose materials  
* how to use fabrication machines  
* how to make parts fit  
* how to assemble correctly  
* how to troubleshoot real mechanical problems
