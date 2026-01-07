<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# Qt Designer Basics and Integration

## Introduction

Qt Designer is a powerful visual tool for creating PyQt6 interfaces. Instead of writing all your layout code by hand, you can drag and drop widgets, arrange them visually, and then use the generated code in your Python applications. This is especially useful for complex IoT interfaces with many controls.

## Installing and Running Qt Designer

### Running Qt Designer

After installing PyQt6-tools (from Tutorial 1), you can run Qt Designer:

**Windows:**
```bash
designer
```

**macOS/Linux:**
```bash
pyqt6-tools designer
```

**Alternative method (all platforms):**
```bash
python -m PyQt6.uic.pyuic --help
```

If this works, Designer is installed correctly.

## Qt Designer Interface Overview

When you open Qt Designer, you'll see:

1. **Widget Box** (left): Contains all available widgets
2. **Form Editor** (center): Where you design your interface
3. **Property Editor** (right): Edit properties of selected widgets
4. **Object Inspector** (top right): Shows widget hierarchy

## Creating Your First UI with Designer

### Step 1: Create a New Form

1. Open Qt Designer
2. Choose "Main Window" template
3. Click "Create"

### Step 2: Design an IoT Control Panel

Let's create a simple IoT device controller:

1. **Add a Title Label:**
   - Drag a Label from Widget Box to the form
   - Double-click to edit text: "IoT Device Controller"
   - In Property Editor, set:
     - objectName: `titleLabel`
     - font: Bold, size 16
     - alignment: AlignCenter

2. **Add Device Selection:**
   - Drag a Label: "Device Type:"
   - Drag a ComboBox next to it
   - Set ComboBox objectName: `deviceComboBox`
   - Right-click ComboBox → Edit Items → Add: "Arduino", "Raspberry Pi", "ESP32"

3. **Add Connection Status:**
   - Drag a Label: "Status: Disconnected"
   - Set objectName: `statusLabel`
   - Set styleSheet: `background-color: #ffcdd2; padding: 5px; border-radius: 3px;`

4. **Add Control Buttons:**
   - Drag a QPushButton: "Connect"
   - Set objectName: `connectButton`
   - Drag another QPushButton: "Read Sensors"
   - Set objectName: `readSensorsButton`

5. **Add Sensor Display:**
   - Drag two Labels for "Temperature:" and "Humidity:"
   - Drag two QLCDNumber widgets next to them
   - Set objectNames: `temperatureLCD` and `humidityLCD`

### Step 3: Arrange with Layouts

1. **Select widgets you want to group**
2. **Right-click → Lay Out**:
   - Vertically: Stack widgets top to bottom
   - Horizontally: Arrange widgets left to right
   - In Grid: Arrange in rows and columns

3. **Set main layout**:
   - Right-click on the form background
   - Choose "Lay Out → Lay Out Vertically"

### Step 4: Save Your Design

1. File → Save As
2. Name it `iot_controller.ui`
3. Save in your project folder

## Converting UI Files to Python Code

You have two ways to use your Designer files:

### Method 1: Convert to Python File (Static)

Convert your `.ui` file to a `.py` file:

```bash
pyuic6 -x iot_controller.ui -o iot_controller.py
```

This creates a Python file you can modify and use:

```python
# iot_controller.py (generated)
from PyQt6 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(400, 300)
        
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        
        # ... all your widgets are defined here ...
        
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
    
    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "IoT Controller"))
        # ... all text is set here ...
```

### Method 2: Load UI File Dynamically (Recommended)

Load the `.ui` file directly in your Python code:

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.uic import loadUi

class IoTController(QMainWindow):
    def __init__(self):
        super().__init__()
        # Load the UI file
        loadUi('iot_controller.ui', self)
        
        # Now you can access widgets by their objectName
        self.connectButton.clicked.connect(self.connect_device)
        self.readSensorsButton.clicked.connect(self.read_sensors)
        self.deviceComboBox.currentTextChanged.connect(self.device_changed)
    
    def connect_device(self):
        """Handle connect button click"""
        current_text = self.connectButton.text()
        if current_text == "Connect":
            device = self.deviceComboBox.currentText()
            self.statusLabel.setText(f"Status: Connected to {device}")
            self.statusLabel.setStyleSheet("background-color: #c8e6c9; padding: 5px; border-radius: 3px;")
            self.connectButton.setText("Disconnect")
        else:
            self.statusLabel.setText("Status: Disconnected")
            self.statusLabel.setStyleSheet("background-color: #ffcdd2; padding: 5px; border-radius: 3px;")
            self.connectButton.setText("Connect")
    
    def read_sensors(self):
        """Handle read sensors button click"""
        import random
        temp = round(random.uniform(20.0, 30.0), 1)
        humidity = random.randint(40, 80)
        
        self.temperatureLCD.display(temp)
        self.humidityLCD.display(humidity)
        
        self.statusLabel.setText(f"Sensors: {temp}°C, {humidity}%")
    
    def device_changed(self, device_name):
        """Handle device selection change"""
        print(f"Device changed to: {device_name}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTController()
    window.show()
    app.exec()
```

## Complete IoT Dashboard Example with Designer

Let's create a more complex IoT dashboard step by step:

### Step 1: Design in Qt Designer

Create `iot_dashboard.ui` with these widgets:

**Main Structure:**
- MainWindow with central widget
- Vertical layout for main content

**Header Section:**
- Label: "IoT Environmental Monitor" (objectName: `titleLabel`)
- Label: Current date/time (objectName: `dateTimeLabel`)

**Sensor Section (GroupBox: "Sensor Readings"):**
- Grid layout with:
  - Temperature: Label + QLCDNumber (`temperatureLCD`)
  - Humidity: Label + QLCDNumber (`humidityLCD`) 
  - Pressure: Label + QLCDNumber (`pressureLCD`)
  - Light: Label + QProgressBar (`lightProgressBar`)

**Control Section (GroupBox: "Device Control"):**
- LED Control: CheckBox (`ledCheckBox`) + Slider (`brightnessSlider`) + Label (`brightnessLabel`)
- Fan Control: CheckBox (`fanCheckBox`) + SpinBox (`fanSpeedSpinBox`)
- Heater: CheckBox (`heaterCheckBox`)

**Connection Section:**
- Device ComboBox (`deviceComboBox`)
- Connect Button (`connectButton`)
- Status Label (`connectionStatusLabel`)

**Action Buttons:**
- Read All Sensors (`readAllButton`)
- Auto Mode Toggle (`autoModeButton`)
- Reset All (`resetButton`)

### Step 2: Python Implementation

```python
import sys
import random
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.QtCore import QTimer, QDateTime
from PyQt6.uic import loadUi

class IoTDashboard(QMainWindow):
    def __init__(self):
        super().__init__()
        # Load the UI file
        loadUi('iot_dashboard.ui', self)
        
        # Initialize variables
        self.connected = False
        self.auto_mode = False
        self.led_enabled = False
        self.fan_enabled = False
        self.heater_enabled = False
        
        # Setup timer for auto updates
        self.auto_timer = QTimer()
        self.auto_timer.timeout.connect(self.auto_update)
        
        # Setup datetime timer
        self.datetime_timer = QTimer()
        self.datetime_timer.timeout.connect(self.update_datetime)
        self.datetime_timer.start(1000)  # Update every second
        
        # Connect all signals
        self.connect_signals()
        
        # Initialize UI
        self.update_datetime()
        self.update_connection_status()
    
    def connect_signals(self):
        """Connect all widget signals to their slots"""
        # Connection controls
        self.connectButton.clicked.connect(self.toggle_connection)
        self.deviceComboBox.currentTextChanged.connect(self.device_changed)
        
        # Sensor reading
        self.readAllButton.clicked.connect(self.read_all_sensors)
        
        # Device controls
        self.ledCheckBox.stateChanged.connect(self.led_state_changed)
        self.brightnessSlider.valueChanged.connect(self.brightness_changed)
        self.fanCheckBox.stateChanged.connect(self.fan_state_changed)
        self.fanSpeedSpinBox.valueChanged.connect(self.fan_speed_changed)
        self.heaterCheckBox.stateChanged.connect(self.heater_state_changed)
        
        # Mode controls
        self.autoModeButton.clicked.connect(self.toggle_auto_mode)
        self.resetButton.clicked.connect(self.reset_all)
    
    def update_datetime(self):
        """Update the date/time display"""
        current_time = QDateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
        self.dateTimeLabel.setText(f"Current Time: {current_time}")
    
    def toggle_connection(self):
        """Handle connect/disconnect button"""
        if not self.connected:
            device = self.deviceComboBox.currentText()
            self.connected = True
            self.connectButton.setText("Disconnect")
            self.connectionStatusLabel.setText(f"Connected to {device}")
            self.connectionStatusLabel.setStyleSheet("background-color: #c8e6c9; padding: 5px; border-radius: 3px;")
            
            # Enable controls when connected
            self.enable_controls(True)
        else:
            self.connected = False
            self.connectButton.setText("Connect")
            self.connectionStatusLabel.setText("Disconnected")
            self.connectionStatusLabel.setStyleSheet("background-color: #ffcdd2; padding: 5px; border-radius: 3px;")
            
            # Disable controls when disconnected
            self.enable_controls(False)
            if self.auto_mode:
                self.toggle_auto_mode()  # Stop auto mode
    
    def enable_controls(self, enabled):
        """Enable/disable all control widgets"""
        self.readAllButton.setEnabled(enabled)
        self.ledCheckBox.setEnabled(enabled)
        self.fanCheckBox.setEnabled(enabled)
        self.heaterCheckBox.setEnabled(enabled)
        self.autoModeButton.setEnabled(enabled)
        self.resetButton.setEnabled(enabled)
    
    def device_changed(self, device_name):
        """Handle device selection change"""
        if self.connected:
            self.connectionStatusLabel.setText(f"Connected to {device_name}")
    
    def read_all_sensors(self):
        """Simulate reading all sensors"""
        if not self.connected:
            return
        
        # Generate random sensor values
        temperature = round(random.uniform(18.0, 32.0), 1)
        humidity = random.randint(30, 90)
        pressure = random.randint(990, 1050)
        light = random.randint(0, 100)
        
        # Update displays
        self.temperatureLCD.display(temperature)
        self.humidityLCD.display(humidity)
        self.pressureLCD.display(pressure)
        self.lightProgressBar.setValue(light)
        
        print(f"Sensors read: {temperature}°C, {humidity}%, {pressure}hPa, {light}% light")
    
    def led_state_changed(self, state):
        """Handle LED checkbox state change"""
        from PyQt6.QtCore import Qt
        self.led_enabled = state == Qt.CheckState.Checked.value
        self.brightnessSlider.setEnabled(self.led_enabled)
        
        if not self.led_enabled:
            self.brightnessSlider.setValue(0)
            self.brightnessLabel.setText("0%")
    
    def brightness_changed(self, value):
        """Handle brightness slider change"""
        self.brightnessLabel.setText(f"{value}%")
        if self.led_enabled and self.connected:
            print(f"LED brightness set to {value}%")
    
    def fan_state_changed(self, state):
        """Handle fan checkbox state change"""
        from PyQt6.QtCore import Qt
        self.fan_enabled = state == Qt.CheckState.Checked.value
        self.fanSpeedSpinBox.setEnabled(self.fan_enabled)
        
        if not self.fan_enabled:
            self.fanSpeedSpinBox.setValue(0)
    
    def fan_speed_changed(self, value):
        """Handle fan speed change"""
        if self.fan_enabled and self.connected:
            print(f"Fan speed set to {value}%")
    
    def heater_state_changed(self, state):
        """Handle heater checkbox state change"""
        from PyQt6.QtCore import Qt
        self.heater_enabled = state == Qt.CheckState.Checked.value
        if self.heater_enabled and self.connected:
            print("Heater turned ON")
        else:
            print("Heater turned OFF")
    
    def toggle_auto_mode(self):
        """Toggle automatic mode"""
        if not self.auto_mode:
            self.auto_mode = True
            self.autoModeButton.setText("Stop Auto")
            self.auto_timer.start(3000)  # Update every 3 seconds
            print("Auto mode started")
        else:
            self.auto_mode = False
            self.autoModeButton.setText("Auto Mode")
            self.auto_timer.stop()
            print("Auto mode stopped")
    
    def auto_update(self):
        """Automatic update function"""
        self.read_all_sensors()
        
        # Auto-control based on sensor readings
        current_temp = self.temperatureLCD.value()
        current_light = self.lightProgressBar.value()
        
        # Auto fan control based on temperature
        if current_temp > 28:
            if not self.fan_enabled:
                self.fanCheckBox.setChecked(True)
            self.fanSpeedSpinBox.setValue(min(100, int((current_temp - 25) * 20)))
        elif current_temp < 22:
            if self.fan_enabled:
                self.fanCheckBox.setChecked(False)
        
        # Auto LED control based on light level
        if current_light < 30:
            if not self.led_enabled:
                self.ledCheckBox.setChecked(True)
            self.brightnessSlider.setValue(100 - current_light)
        elif current_light > 70:
            if self.led_enabled:
                self.ledCheckBox.setChecked(False)
        
        # Auto heater control
        if current_temp < 20:
            if not self.heater_enabled:
                self.heaterCheckBox.setChecked(True)
        elif current_temp > 25:
            if self.heater_enabled:
                self.heaterCheckBox.setChecked(False)
    
    def reset_all(self):
        """Reset all controls to defaults"""
        # Stop auto mode if running
        if self.auto_mode:
            self.toggle_auto_mode()
        
        # Reset all controls
        self.ledCheckBox.setChecked(False)
        self.fanCheckBox.setChecked(False)
        self.heaterCheckBox.setChecked(False)
        self.brightnessSlider.setValue(0)
        self.fanSpeedSpinBox.setValue(0)
        
        # Clear sensor displays
        self.temperatureLCD.display(0)
        self.humidityLCD.display(0)
        self.pressureLCD.display(0)
        self.lightProgressBar.setValue(0)
        
        print("All controls reset")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    dashboard = IoTDashboard()
    dashboard.show()
    app.exec()
```

## Designer Tips and Best Practices

### 1. Naming Convention
Always set meaningful objectNames:
- Use camelCase: `temperatureLabel`, `connectButton`
- Be descriptive: `sensorReadingGroup`, `deviceControlPanel`
- Include widget type: `temperatureLCD`, `connectButton`

### 2. Layout Management
- Always use layouts, even for simple forms
- Use spacers to control widget positioning
- Set size policies appropriately
- Use QGroupBox to organize related controls

### 3. Property Setting
Common properties to set in Designer:
- **objectName**: For accessing in Python
- **text**: Display text
- **toolTip**: Help text on hover
- **styleSheet**: CSS-like styling
- **enabled**: Whether widget is interactive
- **visible**: Whether widget is shown

### 4. Widget Organization
- Use QGroupBox for logical grouping
- Set tab order for keyboard navigation
- Use consistent margins and spacing
- Align related widgets

## Debugging Designer Files

Common issues when using Designer files:

### 1. ObjectName Errors
```python
# Error: 'Ui_MainWindow' object has no attribute 'myButton'
# Solution: Check objectName in Designer matches Python code
```

### 2. UI File Not Found
```python
# Error: FileNotFoundError: [Errno 2] No such file or directory: 'myfile.ui'
# Solution: Ensure UI file is in correct location or use full path
loadUi('path/to/myfile.ui', self)
```

### 3. Import Errors
```python
# Error: ModuleNotFoundError: No module named 'PyQt6.uic'
# Solution: Install PyQt6-tools
pip install PyQt6-tools
```

## Practice Exercise

Create a complete IoT greenhouse controller using Qt Designer:

1. **Design Requirements:**
   - Temperature, humidity, and soil moisture displays
   - Watering system controls (on/off, duration)
   - Ventilation fan controls (speed control)
   - Lighting controls (on/off, timer settings)
   - Connection status and device selection
   - Auto mode for climate control

2. **Implementation Requirements:**
   - Load UI dynamically with `loadUi()`
   - Implement all control logic
   - Add automatic climate control in auto mode
   - Include data logging functionality

## What's Next?

In the next tutorial, we'll learn about:
- Advanced form handling
- Dialog boxes and popup windows
- Input validation
- File operations
- Error handling

Ready to build more complex interfaces? Let's move to Tutorial 6!