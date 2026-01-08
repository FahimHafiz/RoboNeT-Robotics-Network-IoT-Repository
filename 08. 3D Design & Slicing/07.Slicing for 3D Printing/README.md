# <a name="_44mz1z7f8w6"></a> **SLICING PARAMETERS BASICS**
-----
### <a name="_lxnp3zmk0r5a"></a>**Layer Height**
This defines the thickness of each printed layer.

**Small layers:** Smooths the surface and adds more detail.\
 **Large Layers:** Saves time, prints fast, but the surface will be rough.

Typical values: 0.12 - 0.28 

- **pla/petg:** 0.2 for good balance.**\

- **Abs:** 0.25 for the layer bondings.**\

- **Tpu:** 0.25 - 0.3. It will reduce the chance of clogging.**\

-----
### <a name="_7mqaptu7pbm4"></a>**Wall Thickness**
Wall is basically the outer shell of the object.\
 Thicker walls mean stronger parts.

If the nozzle is 0.4, then set the thickness to 1.2mm = 3 walls.\
 The wall should be multiplied by the nozzle size.

- **Pla/Petg:** 2-3 walls.**\

- **Abs:** 3-5 walls to resist the cracks.**\

- **TPU:** 2 walls for flexibility.**\

-----
### <a name="_eksssv7d7oex"></a>**Top/Bottom Layers**
Defines the solidness of the top and bottom surfaces of the object.

**Too few:** holes and weak areas.\
 **Too many:** wastes time.

Common: 4-6 is enough for the top and bottom.

-----
### <a name="_idiwdgiqmbnm"></a>**Infill**
Defines the internal structure that supports the model.

**Density:** 10-100% (according to the need or the use case of the object)\
 Pattern: Gyroid, Hexagonal, Zigzag etc.

**Low infill:** Fast and lightweight object.\
 High Infill: Strong but Heavy.

- **Pla/Petg:** 20-40% for most parts.**\

- **Abs:** 30-50% for strength.**\

- **Tpu:** 10-20% makes it flexible.**\

-----
### <a name="_m54k1nyp1nuo"></a>**Printing Temperature**
Defines the melting temperature of the filaments.\
 **Too low =** under-extrusion (weak, gaps).\
 **Too high =** stringing or blobs.

**Typical ranges:**

- **PLA:** 190–210 °C**\

- **ABS:** 230–250 °C**\

- **PETG:** 230–250 °C**\

- **TPU:** 210–230 °C**\

-----
### <a name="_voob3se52r4v"></a>**Bed Temperature**
Defines the 1st layer print temperature for the adhesion of the filament with the plate.

**Typical ranges:**

- **PLA:** 50–60 °C**\

- **ABS:** 90–110 °C**\

- **PETG:** 70–85 °C**\

- **TPU:** 40–60 °C**\

-----
### <a name="_kec4n14e8rtx"></a>**Print Speed**
Defines the speed of the moving extruder of the 3d printer.

**Fast =** less print time, but rougher outers.\
 **Slow =** smoother print, better adhesion.

**Typical:**

- **PLA:** 50–70 mm/s**\

- **ABS:** 40–60 mm/s**\

- **PETG:** 40–60 mm/s**\

- **TPU:** 20–35 mm/s**\

-----
### <a name="_qw50ix6jfkfi"></a>**Retraction**
Retracts filament when its moving onthe empty space or mid-air to prevent thing stringings in the object.

**Distance:** pulled back distance of the filament\
 **Speed:** how fast it pulls back the filament.

**Example:** 1 mm at 35 mm/s for PLA.**\
Too much retraction causes clogg.

Too little retraction causes the stringings.

- **PLA:** 0.8–1.2 mm**\

- **ABS:** 1.0–1.5 mm**\

- **PETG:** 0.6–1.0 mm**\

- **TPU:** 0.3–0.8 mm
-----
### <a name="_wjrj43buha3o"></a>**Cooling Fan Speed**
Defines the cooling fan speeds after each layer of extrusion.

\
 Too speed is bad for ABS as it helps the cracks.

**Typical:**

- **PLA:** 100% after first 2 layers**\

- **ABS:** 0–20% (or off)**\

- **PETG:** 30–50%**\

- **TPU:** 50–70%**\

-----
### <a name="_j9onvuid9p4z"></a>**Adhesion Type**
Ensures good adhesion for the object's initial layer to the build plate.

**Common options:**

- **Skirt:** only outline.**\

- **Brim: a** wide plate for the adhesion of the object.
- **Raft:** thick base printed below the object for better adhesion.**\


ABS often needs a brim or raft.\
 PLA, PETG, and TPU usually do fine with a skirt.

-----
### <a name="_8cruuuqwil1e"></a>**Supports**
Used for printing in mid-air.\
 Enable this only when the model has areas with angles > 60°.

Remove supports carefully after printing.

- **PLA:** removes easily.**\

- **ABS:** requires good cooling for the supports.**\

- **PETG:** needs fewer supports as it sticks well.**\

- **TPU:** avoid if possible.**\

-----
### <a name="_utis0lnvto2z"></a>**Flow Rate**
Controls how much filament is pushed out.\
 Default is 100%, but you can fine-tune if prints look under- or over-extruded.

Increase slightly (102–105%) if gaps appear.\
 Decrease (95–98%) if edges look too thick.


