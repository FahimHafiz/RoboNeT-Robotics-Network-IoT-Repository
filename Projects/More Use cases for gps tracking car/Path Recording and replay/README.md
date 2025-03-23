### **Concept: Path Recording & Replay with GPS Data**

#### **Objective:**
The goal is to store the GPS coordinates of the car as it moves, then send that data to a device via Bluetooth for later use (such as analyzing the path on Google My Maps).

#### **How It Works:**

1. **Data Collection:**
   The GPS module continuously provides the car's current latitude and longitude, which are appended to an array or list in memory. Each time the car updates its position, the new coordinates are stored.

2. **Completion of the Path:**
   When the car finishes its route or reaches the destination, the entire path (list of coordinates) is saved. You can then retrieve all the data at once.

3. **Bluetooth Communication:**
   Using the `BluetoothSerial` library, the recorded data is sent to a paired device. This could be your phone or computer where you can receive the data in real-time or as a batch after the car finishes the route.

4. **Saving the Data:**
   The received data is parsed and saved into a CSV file, where each row contains a latitude and longitude point (and possibly other details). This CSV file can then be uploaded to **Google My Maps** for visualization.

5. **Visualization on Google My Maps:**
   After saving the path data as a CSV file, you can import it directly into **Google My Maps** to visualize the path and analyze the car’s journey.

---

### **Code Segments to Help with Implementation**

#### **1. GPS Data Collection**

You’ll first need to collect GPS data and store it in an array or list. Here’s how you can do that:

```cpp
#include <BluetoothSerial.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

BluetoothSerial SerialBT;
TinyGPSPlus gps;
HardwareSerial mySerial(1);

const int RX_PIN = 16;  // RX pin for GPS
const int TX_PIN = 17;  // TX pin for GPS
float latitude, longitude;

// Store GPS data points
String pathData = "";  // String to hold the entire path

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car");  // Bluetooth device name
  mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // GPS serial port

  Serial.println("GPS Path Recording Started...");
}

void loop() {
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read());

    if (gps.location.isUpdated()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();

      // Format the coordinates and add them to the path data string
      String dataPoint = String(latitude, 6) + "," + String(longitude, 6) + "\n";
      pathData += dataPoint;  // Append new data point to the path

      // Log the data to serial and Bluetooth
      Serial.println(dataPoint);
      SerialBT.println(dataPoint);
    }
  }
}
```

#### **Explanation:**
- **GPS Module:** The `TinyGPS++` library is used to interface with the GPS module. The car’s location (latitude and longitude) is updated continuously and stored in the `pathData` string.
- **Bluetooth Communication:** The `BluetoothSerial` library sends each new data point to a paired device.
- **Data Storage:** Each GPS coordinate is appended to the `pathData` string, which holds all the coordinates in chronological order.

---

#### **2. Sending Data via Bluetooth to a Device**

After collecting the coordinates, the car will send the entire path data to a Bluetooth-connected device. This is done at the end of the journey, once the car has completed its path.

```cpp
void sendDataToDevice() {
  SerialBT.println("Path Completed, Sending Data...");

  // Send the entire path data
  SerialBT.print(pathData);
}
```

#### **Explanation:**
- Once the journey is complete, the `sendDataToDevice()` function sends the collected path data (stored in `pathData`) via Bluetooth to the connected device.
- On the paired device (e.g., phone/computer), you can use a Bluetooth Serial Terminal to receive this data.

---

#### **3. Saving Data as CSV on Your Device**

On the receiving end (phone/computer), you can save the received data in CSV format. Here’s a brief guideline for that:
- Use any Bluetooth Serial Terminal app (like **Serial Bluetooth Terminal** for Android or **CoolTerm** for Windows/Mac).
- When the data is received, copy it to a text file and save it as `path_data.csv`.
- Each row in the CSV will represent a GPS point in the format: `latitude,longitude`.

---

#### **4. Visualizing the Data on Google My Maps**

To visualize the path on **Google My Maps**, follow these steps:

1. **Prepare the CSV File:**
   - After receiving the GPS data from the car, save it as a CSV file on your computer. Each row should contain a latitude and longitude pair, and the file should be formatted like this:

   ```csv
   Latitude,Longitude
   12.345678,-98.765432
   12.346678,-98.764432
   ...
   ```

2. **Import the CSV File into Google My Maps:**

   - Go to **[Google My Maps](https://www.google.com/mymaps)** and log in with your Google account.
   - Click on **Create a New Map**.
   - In the left sidebar, click on **Import**.
   - Choose the `path_data.csv` file from your computer.
   - After importing, Google My Maps will automatically plot the coordinates on the map.

3. **Adjust the Map:**
   - Once the data is uploaded, you can customize the map, change the color of the path, add markers, or modify other properties to better visualize the route.
   - You can also add labels or other information, such as the time the car passed each point, if available.

#### **Explanation:**
- **CSV File Format:** Make sure the CSV file is structured correctly with the headers `Latitude` and `Longitude`. This helps Google My Maps identify the data as geographic coordinates.
- **Google My Maps Import:** The import feature in Google My Maps reads the CSV and automatically maps each latitude and longitude pair onto the map.
- **Customization:** You can further customize the path by adding colors, changing icons for markers, or even creating multiple layers to represent different paths or sessions.

---

### **Applications & Benefits:**

- **Route Comparison:** You can compare different paths taken by the car over multiple runs, analyzing the efficiency or detecting deviations.
- **Efficiency Analysis:** By recording and comparing multiple runs on the same route, you can evaluate how obstacles or conditions affect the travel time.
- **Obstacle Detection:** If an obstacle caused a detour, it would be visible in the path data, helping to identify problematic areas for future route planning.
- **Mapping Unknown Terrain:** If the car navigates an area that hasn’t been mapped yet, it will create a map of the area, which can be visualized and analyzed.

---

### **Summary:**
This approach allows you to store the GPS data of the car’s movements and later visualize it on **Google My Maps**. By leveraging Bluetooth for communication and Google My Maps for visualization, you can analyze the efficiency of the route, detect obstacles, and create new paths based on the data.
