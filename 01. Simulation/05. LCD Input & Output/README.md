# Tinkercad 16x2 LCD with Serial Input Tutorial

This tutorial guides you through using Tinkercad to simulate an Arduino with a 16x2 LCD, displaying custom messages entered via the Serial Monitor. The provided Arduino code uses the LiquidCrystal library to control the LCD and updates the display with user input on the first row, while optionally showing a seconds counter on the second row. This is ideal for learning Arduino programming and LCD interfacing without physical hardware.

## Prerequisites

- A Tinkercad account (free at [tinkercad.com](https://www.tinkercad.com)).
- Basic understanding of Arduino programming and the Tinkercad interface.
- No physical hardware is required, as Tinkercad simulates all components.

## Step 1: Set Up the Circuit in Tinkercad

### Create a New Circuit

- Log in to Tinkercad and start a new circuit project.

### Add Components

From the components panel, drag the following to the workspace:
- **Arduino Uno R3**
- **16x2 LCD** (search for "LCD")
- **10kΩ Potentiometer**
- **Breadboard** (optional for organization)
- **Jumper wires** (available in the workspace)

### Wire the Circuit

Connect the LCD to the Arduino as follows:
- **LCD RS** to Arduino pin 12
- **LCD Enable** to Arduino pin 11
- **LCD D4** to Arduino pin 5
- **LCD D5** to Arduino pin 4
- **LCD D6** to Arduino pin 3
- **LCD D7** to Arduino pin 2
- **LCD R/W** to ground (GND on Arduino or breadboard)
- **LCD VSS** to ground
- **LCD VCC** to 5V (from Arduino)

Connect the potentiometer for contrast:
- One outer pin to 5V
- Other outer pin to ground
- Middle pin (wiper) to LCD VO (pin 3)

### Adjust Potentiometer

- Click the potentiometer in Tinkercad, and in the properties panel, set the slider to ~50% for initial contrast. Adjust later if the text isn't visible.

<img width="1192" height="745" alt="image" src="https://github.com/user-attachments/assets/d3a91507-adf3-49ce-8c39-faa638ba07ce" />

## Step 2: Add the Arduino Code

### Open the Code Editor

- In Tinkercad, click the **Code** button to open the code editor.

### Paste the Code

Replace the default code with the following:

```cpp
#include <LiquidCrystal.h>

// Initialize the LCD with the same pin configuration
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

int seconds = 0;
String message = "Type your msg!"; // Default message

void setup() {
  // Start the Serial communication
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows
  lcd_1.begin(16, 2);
  
  // Print the initial message to the LCD
  lcd_1.print(message);
}

void loop() {
  // Check if new data is available from Serial
  if (Serial.available() > 0) {
    // Read the incoming string
    message = Serial.readStringUntil('\n');
    
    // Clear the first row
    lcd_1.setCursor(0, 0);
    lcd_1.print("                "); // Clear line with spaces
    
    // Display the new message
    lcd_1.setCursor(0, 0);
    lcd_1.print(message.substring(0, 16)); // Limit to 16 characters
  }
  
  // Display seconds on second row
  lcd_1.setCursor(0, 1);
  lcd_1.print(seconds);
  
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
}
```

### Verify the Code

- Tinkercad will highlight any syntax errors. The **LiquidCrystal** library is built into Tinkercad, so no additional setup is needed.

## Step 3: Simulate and Test

### Start Simulation

- Click **Start Simulation** in Tinkercad to run the circuit and code.

### Open Serial Monitor

- Click the **Serial Monitor** button at the bottom of the code editor.
- Set the baud rate to **9600** (matching `Serial.begin(9600);`).

### Send a Message

- In the Serial Monitor's input field, type a message (e.g., "Hello Tinkercad!") and press **Enter**.
- The LCD's first row should display your message (up to 16 characters).
- The second row shows the seconds counter, updating every second.

### Adjust Contrast

- If the LCD text isn't visible, pause the simulation, adjust the potentiometer slider, and restart.

## Step 4: Customize the Display

### Change Default Message

- Edit `String message = "Type your msg!";` to a custom message (e.g., "Welcome to LCD!").

### Remove Seconds Counter

- Delete these lines from `loop()` to free the second row:
  ```cpp
  lcd_1.setCursor(0, 1);
  lcd_1.print(seconds);
  ```

### Add Scrolling for Long Messages

Replace the message display code in `loop()` with:

```cpp
if (Serial.available() > 0) {
  message = Serial.readStringUntil('\n');
  lcd_1.setCursor(0, 0);
  lcd_1.print("                ");
  lcd_1.setCursor(0, 0);
  lcd_1.print(message.substring(0, 16));
}
if (message.length() > 16) {
  for (int i = 0; i <= message.length() - 16; i++) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 0);
    lcd_1.print(message.substring(i, i + 16));
    delay(500);
  }
}
```

This scrolls long messages by shifting the display every 500ms.

## Troubleshooting

- **LCD Blank**:
  - Verify all connections, especially **R/W** to ground and **VO** to the potentiometer.
  - Adjust the potentiometer slider for better contrast.
- **Serial Monitor Issues**:
  - Ensure the baud rate is **9600** and you're pressing **Enter** after typing.
- **Overlapping Text**:
  - Confirm the `lcd_1.print("                ");` line is clearing the row properly.

## Next Steps

- **Add Sensors**: Integrate a sensor (e.g., temperature sensor) to display real-time data.
- **Use Buttons**: Add buttons to cycle through predefined messages.
- **Save and Share**: Name your Tinkercad project and share the link to showcase your work.

This setup lets you experiment with dynamic LCD displays in a virtual environment. For further customization or specific features, explore Tinkercad's component library or modify the code to suit your project needs.
