# **Module 2 — Choosing the Right Materials** 

## **2.0 Why material choice matters more than people think**

In robotics, material choice is not just “metal vs plastic.” It decides:

* how heavy the robot becomes (and how hard the motors have to work)  
* whether parts bend, crack, or stay aligned  
* how easy it is to manufacture (laser cut / CNC / 3D print / weld)  
* how long it survives vibration, impacts, and repeated motion  
* how clean the assembly feels (tight fits vs wobbly joints)

A lot of beginners pick materials based on what’s available. That’s normal at first. But to build better robots, you start choosing materials based on the **loads \+ environment \+ fabrication method**.

---

## **2.1 The properties I actually care about in robotics**

When selecting a material, these are the properties that matter most in real builds:

### **Strength (won’t permanently bend)**

* Think: “Can it survive the peak load without yielding?”  
* Important for: brackets, mounts, chassis plates, shafts, fastener areas

### **Stiffness (won’t flex too much)**

* Stiffness is what keeps **alignment** correct.  
* A part can be “strong enough” but still flex a lot and cause problems.  
* Important for: frames, arm links, drivetrain plates, sensor mounting (cameras hate vibration)

### **Density (weight)**

* Lower density \= lighter robot.  
* But lighter is not always better if you lose stiffness or durability.  
* Important for: mobile robots, drones, arms

### **Toughness (impact resistance)**

* Toughness is basically “does it crack when something hits it?”  
* Important for: bumpers, guards, parts near collisions

### **Wear \+ friction (rubbing parts)**

* Important for: sliding joints, bushings, spacers, contact surfaces

### **Heat resistance**

* Motors, gearboxes, sunlight, enclosed electronics… heat shows up.  
* Important for: mounts near motors, parts near electronics, enclosed robot bodies

### **Corrosion resistance**

* Outdoor robots, humid labs, sweaty hands, water exposure.  
* Important for: anything that sits for months, fasteners, frames

### **Manufacturability**

Ask: Can I actually make this with the machines I have?

* laser cutting works great for certain sheet materials  
* CNC works better for thicker parts or accurate holes  
* 3D printing is fast, but plastic behavior is different from metal  
* welding is strong but can warp parts and needs skill

---

## **2.2 The “loads” robots really apply** 

## Before choosing material, I try to label the load type:

* **Tension / Compression**: pulling or pushing (less common alone in robots)  
* **Bending**: super common (arms, brackets, chassis plates)  
* **Shear**: bolts and joints experience this a lot  
* **Torsion**: shafts, couplers, twisting frames  
* **Impact**: crashes, drops, sudden stops  
* **Vibration**: motors \+ driving \+ gear mesh (this loosens fasteners and cracks weak parts)

Most robotics failures I’ve seen are either:

1. bending flex causing misalignment  
2. vibration loosening stuff  
3. impact cracking brittle parts

---

## **2.3 Quick comparison of common robotics materials**

| Material | Best at | Weak at | Typical robotics use |
| :---: | :---: | :---: | :---: |
| **Mild Steel** | strength, stiffness, weldability, cheap | heavy, rusts | welded frames, mounts, shafts (sometimes) |
| **Stainless Steel** | corrosion resistance, strong | expensive, harder to machine, heavy | outdoor hardware, shafts, fasteners, brackets |
| **Aluminum** | weight savings, machinable, good stiffness-to-weight | softer than steel, threads can strip | frames, plates, brackets, gearbox plates |
| **Carbon Fiber** | very stiff & light (in-plane) | expensive, brittle edges, hard to join, dust hazard | lightweight plates, arms, panels |
| **PLA** | easy prints, stiff, dimensionally decent | brittle, low heat resistance | quick prototypes, covers |
| **ABS** | tougher than PLA, better temp | warps, printing is harder | mounts, housings, functional parts |
| **TPU** | flexible, shock absorbing | not stiff, hard to hold tolerances  | tires, bumpers, vibration isolators  |

---

## **2.4 Material deep dive (what to use, when, and why)**

### **A) Mild Steel**

**How it behaves:** strong, stiff, forgiving, but heavy.  
**Why people love it:** cheap and welds well.

**Pros**

* high stiffness → good alignment  
* weldable (MIG is common)  
* affordable and easy to source

**Cons**

* heavy (mobile robots feel it immediately)  
* rusts unless coated/painted  
* can be overkill for small robots

**Best uses**

* welded base frames  
* motor mounts that must not flex  
* parts that see impacts

**Fabrication tips**

* drill \+ grind works fine  
* welding can warp thin sections → tack weld and sequence welds  
* add paint, powder coat, or at least oil to stop rust

---

### **B) Stainless Steel**

**How it behaves:** strong and corrosion resistant, but more annoying to machine.

**Pros**

* resists rust (huge if outdoor or humid)  
* good strength and durability

**Cons**

* heavier than aluminum  
* harder to drill/cut (work hardening can happen if tools are dull)  
* more expensive

**Best uses**

* exposed hardware in outdoor robots  
* shafts / fasteners where rust would be a problem  
* thin brackets that must survive corrosion

**Fabrication tips**

* use sharp bits, cutting fluid, steady feed (don’t rub)  
* plan for cost: stainless is rarely “prototype cheap”

---

### **C) Aluminum (common: 6061, 5052\)**

**How it behaves:** light, easy to machine, great for most robot structures.

**Pros**

* much lighter than steel  
* strong enough for many robots  
* easy CNC and drilling  
* good stiffness-to-weight ratio

**Cons**

* threads can strip (especially in thin plate)  
* softer → dents easier than steel  
* welding needs better technique (and not always worth it for small parts)

**Best uses**

* robot chassis plates (laser cut or CNC)  
* arm plates and brackets  
* gearbox mounting plates  
* structural tubes/extrusions

**Fabrication tips**

* if you’re bolting into aluminum, consider:  
  * thicker material, or  
  * threaded inserts, or  
  * through-bolts \+ nuts  
* deburr edges (aluminum burrs are sharp and annoying)  
* for thin sheet, 5052 is often nicer for bending; 6061 is often nicer for machining

---

### **D) Carbon Fiber Sheet (typically carbon fiber \+ resin laminate)**

**How it behaves:** extremely stiff for its weight in the sheet plane, but edges can chip and it’s not “friendly” like metal.

**Pros**

* amazing stiffness-to-weight  
* looks clean and “high performance”  
* great for lightweight plates

**Cons**

* expensive  
* brittle failure (can crack instead of bending)  
* hard to make threaded features directly  
* dust hazard when cutting/sanding (you *need* PPE and good cleanup)

**Best uses**

* lightweight structural plates  
* panels, braces, arms where weight matters a lot  
* stiffness-critical parts where you don’t want flex

**Fabrication tips**

* best cut methods: CNC with proper bits, waterjet (if available)  
* avoid breathing dust; use mask/respirator and vacuum cleanup  
* joining:  
  * usually bolts \+ washers (spread load)  
  * avoid over-tightening (crushes laminate)  
  * consider aluminum “clamp plates” to distribute force

---

### **E) PLA (3D printing)**

**How it behaves:** prints easily, holds shape well, but can crack and softens with heat.

**Pros**

* easiest material for fast prototypes  
* stiff enough for many non-critical parts  
* good dimensional accuracy for basic prints

**Cons**

* brittle (especially thin parts)  
* low heat resistance (hot car / near motor can deform)  
* not great for impact or high vibration

**Best uses**

* early prototypes to check fit  
* sensor mounts indoors  
* covers, cable guides, simple brackets (light-duty)

**Print tips**

* avoid thin “knife-edge” sections  
* add fillets at corners (sharp corners crack)  
* don’t rely on PLA threads; use heat-set inserts or nuts

---

### **F) ABS (3D printing)**

**How it behaves:** tougher than PLA and better with heat, but printing is harder (warping).

**Pros**

* stronger/tougher behavior than PLA in many cases  
* better temperature resistance  
* more forgiving under impacts

**Cons**

* warps and shrinks → needs good printer setup  
* fumes (ventilation matters)  
* dimensional accuracy can be trickier

**Best uses**

* functional robot parts that see bumps  
* housings near warm electronics  
* mounts that need some toughness

**Print tips**

* enclosure helps a lot  
* design with thicker walls and ribs  
* use inserts for bolts if the part gets removed often

---

### **G) TPU (3D printing)**

**How it behaves:** flexible rubber-like plastic. Great for damping and grip, not for stiff structures.

**Pros**

* shock absorption and vibration damping  
* good grip (wheels/feet)  
* survives impacts well

**Cons**

* hard to keep precise dimensions  
* not stiff (structures will flex)  
* harder to print fast

**Best uses**

* wheels/tires  
* bumpers  
* cable strain relief  
* vibration isolators for sensors

**Print tips**

* slower print speeds help  
* design thicker features than you think you need

---

## **2.5 Material selection workflow**

This is the method I use to avoid random guesses:

### **Step 1: Define the part’s job**

What is it?

* frame plate? bracket? arm link? guard? wheel? mount?

### **Step 2: Label the dominant load**

* bending / torsion / impact / vibration / wear / heat?

### **Step 3: Pick the manufacturing method you actually have**

* laser cut? 3D print? CNC? hand tools? welding?

### **Step 4: Choose material based on the biggest risk**

Examples:

* if stiffness is the risk → aluminum or steel (or CF sheet)  
* if impact is the risk → tough plastic (ABS/PC/Nylon) or steel  
* if heat is the risk → avoid PLA  
* if corrosion is the risk → stainless or protected steel/aluminum

### **Step 5: Decide thickness/geometry before upgrading material**

A lot of times you don’t need a “stronger material.” You need:

* thicker plate  
* ribs/gussets  
* better load path  
* shorter lever arms  
* better fastener layout

Geometry upgrades are often cheaper than material upgrades.

---

## **2.6 Real robotics examples**

### **Example 1: Mobile robot chassis plate (indoor)**

* Goal: stiff enough, not too heavy, easy to mount components  
* Good choice: **laser-cut aluminum**  
* If budget is tight: **plywood** (prototype) then upgrade  
* Avoid: PLA chassis (it flexes and cracks around bolts)

### **Example 2: Motor mount for drivetrain**

* Risk: vibration \+ torque \+ alignment  
* Good choice: **aluminum (thicker) or mild steel**  
* Extra tip: use **through-bolts \+ locknuts** and add ribs if it flexes

### **Example 3: Lightweight arm link**

* Risk: bending stiffness, weight  
* Good choice: **aluminum tube/plate** or **carbon fiber sheet** (if you can fabricate it safely)  
* Avoid: thin PLA (it creeps and flexes over time)

### **Example 4: Protective electronics cover**

* Risk: impacts \+ convenience  
* Good choice: **PLA (easy)** or **ABS (tougher)**  
* TPU is also nice as a gasket or edge bumper

### **Example 5: Wheels / tires**

* Need: grip \+ shock handling  
* Good choice: **TPU** for printed tires (or TPU tread on rigid hub)  
* Hub itself: PLA/ABS or aluminum depending on load

### **Example 6: Outdoor robot fasteners and exposed brackets**

* Risk: rust  
* Good choice: **stainless fasteners**, aluminum brackets, or coated steel

---

## **2.7 Common mistakes**

### **Mistake 1: Choosing based only on “strength”**

Stiffness and alignment matter more for many robot parts.

### **Mistake 2: Using PLA near heat**

PLA can deform in warm conditions. Motors \+ enclosed spaces \= trouble.

### **Mistake 3: Carbon fiber without load spreading**

Bolting CF without washers/plates can crush the laminate.

### **Mistake 4: Relying on plastic threads**

Plastic threads wear out fast. Use:

* heat-set inserts  
* embedded nuts  
* through-bolts

### **Mistake 5: Thin aluminum with tapped holes**

Threads strip. If it must be removable, use nuts or inserts, or go thicker.
