<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# PyQt6 Widgets and Layouts

## Introduction

Widgets are the building blocks of your PyQt6 applications. They're the buttons, labels, text boxes, and other elements that users interact with. Layouts help you organize these widgets neatly in your window.

## Essential Widgets for IoT Applications

### 1. Display Widgets (Show Information)

#### QLabel - Text and Image Display
Perfect for showing sensor readings, status messages, and device information.

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PyQt6.QtCore import Qt

class SensorDisplay(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("Sensor Dashboard")
        self.setGeometry(200, 200, 400, 300)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Different types of labels
        title_label = QLabel("IoT Sensor Dashboard")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title_label.setStyleSheet("font-size: 20px; font-weight: bold; color: #2E86AB;")
        
        # Sensor readings
        temp_label = QLabel("Temperature: 25.4°C")
        humidity_label = QLabel("Humidity: 60%")
        pressure_label = QLabel("Pressure: 1013 hPa")
        
        # Style sensor labels
        sensor_style = "font-size: 14px; padding: 5px; border: 1px solid #ccc; margin: 2px;"
        temp_label.setStyleSheet(sensor_style + "background-color: #ffebee;")
        humidity_label.setStyleSheet(sensor_style + "background-color: #e3f2fd;")
        pressure_label.setStyleSheet(sensor_style + "background-color: #f3e5f5;")
        
        # Status with colored background
        status_label = QLabel("Status: Online")
        status_label.setStyleSheet("background-color: #4CAF50; color: white; padding: 8px; border-radius: 4px;")
        
        layout.addWidget(title_label)
        layout.addWidget(temp_label)
        layout.addWidget(humidity_label)
        layout.addWidget(pressure_label)
        layout.addWidget(status_label)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = SensorDisplay()
    window.show()
    app.exec()
```

#### QLCDNumber - Digital Display
Great for showing numeric sensor values in a digital format.

```python
from PyQt6.QtWidgets import QLCDNumber

# Create LCD display for temperature
temp_lcd = QLCDNumber(5)  # 5 digits
temp_lcd.display(25.47)
temp_lcd.setStyleSheet("background-color: black; color: red;")
```

### 2. Input Widgets (Get User Input)

#### QLineEdit - Single Line Text Input
For device names, IP addresses, sensor IDs, etc.

```python
from PyQt6.QtWidgets import QLineEdit

# Device configuration inputs
device_name = QLineEdit()
device_name.setPlaceholderText("Enter device name (e.g., Arduino_01)")
device_name.setText("Arduino_01")  # Default value

ip_address = QLineEdit()
ip_address.setPlaceholderText("192.168.1.100")
ip_address.setMaxLength(15)  # Limit IP address length
```

#### QSpinBox and QDoubleSpinBox - Numeric Input
Perfect for setting thresholds, delays, and numeric parameters.

```python
from PyQt6.QtWidgets import QSpinBox, QDoubleSpinBox

# Temperature threshold setting
temp_threshold = QSpinBox()
temp_threshold.setRange(-50, 150)  # Temperature range
temp_threshold.setValue(25)  # Default value
temp_threshold.setSuffix("°C")

# Voltage setting with decimals
voltage_setting = QDoubleSpinBox()
voltage_setting.setRange(0.0, 5.0)
voltage_setting.setValue(3.3)
voltage_setting.setSingleStep(0.1)
voltage_setting.setSuffix("V")
```

#### QSlider - Range Selection
Great for LED brightness, motor speed, etc.

```python
from PyQt6.QtWidgets import QSlider

# LED brightness control
brightness_slider = QSlider(Qt.Orientation.Horizontal)
brightness_slider.setRange(0, 255)
brightness_slider.setValue(128)
brightness_slider.setTickPosition(QSlider.TickPosition.TicksBelow)
brightness_slider.setTickInterval(50)
```

### 3. Selection Widgets

#### QCheckBox - On/Off Switches
Perfect for enabling/disabling features or devices.

```python
from PyQt6.QtWidgets import QCheckBox

# Device control checkboxes
led_checkbox = QCheckBox("LED Control")
fan_checkbox = QCheckBox("Cooling Fan")
alarm_checkbox = QCheckBox("Temperature Alarm")

led_checkbox.setChecked(True)  # Start checked
```

#### QRadioButton - Exclusive Choices
For selecting operation modes or device types.

```python
from PyQt6.QtWidgets import QRadioButton, QButtonGroup

# Operating modes
mode1 = QRadioButton("Manual Mode")
mode2 = QRadioButton("Automatic Mode")
mode3 = QRadioButton("Sleep Mode")

# Group them so only one can be selected
mode_group = QButtonGroup()
mode_group.addButton(mode1)
mode_group.addButton(mode2)
mode_group.addButton(mode3)

mode2.setChecked(True)  # Default selection
```

#### QComboBox - Dropdown Lists
For selecting from multiple options like sensor types or communication protocols.

```python
from PyQt6.QtWidgets import QComboBox

# Sensor type selection
sensor_combo = QComboBox()
sensor_combo.addItems(["DHT22", "BME280", "DS18B20", "BMP180"])
sensor_combo.setCurrentText("DHT22")

# Communication protocol
protocol_combo = QComboBox()
protocol_combo.addItems(["WiFi", "Bluetooth", "Serial", "I2C"])
```

### 4. Action Widgets

#### QPushButton - Interactive Buttons
Essential for triggering actions like reading sensors, controlling devices.

```python
from PyQt6.QtWidgets import QPushButton

# Control buttons
read_sensor_btn = QPushButton("Read Sensors")
connect_btn = QPushButton("Connect to Device")
emergency_stop_btn = QPushButton("EMERGENCY STOP")

# Style buttons
read_sensor_btn.setStyleSheet("""
    QPushButton {
        background-color: #2196F3;
        color: white;
        border: none;
        padding: 10px;
        border-radius: 5px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #1976D2;
    }
""")

emergency_stop_btn.setStyleSheet("""
    QPushButton {
        background-color: #f44336;
        color: white;
        border: none;
        padding: 15px;
        border-radius: 5px;
        font-size: 16px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #d32f2f;
    }
""")
```

## Layout Management

Layouts automatically arrange widgets in your window. They handle resizing and keep your interface looking good.

### 1. QVBoxLayout - Vertical Stacking

```python
from PyQt6.QtWidgets import QVBoxLayout

# Stack widgets vertically
layout = QVBoxLayout()
layout.addWidget(title_label)
layout.addWidget(temp_display)
layout.addWidget(humidity_display)
layout.addWidget(control_button)
```

### 2. QHBoxLayout - Horizontal Arrangement

```python
from PyQt6.QtWidgets import QHBoxLayout

# Arrange widgets horizontally
layout = QHBoxLayout()
layout.addWidget(label)
layout.addWidget(input_field)
layout.addWidget(button)
```

### 3. QGridLayout - Grid System

```python
from PyQt6.QtWidgets import QGridLayout

# Create a grid layout
grid = QGridLayout()

# Add widgets at specific positions (row, column)
grid.addWidget(QLabel("Temperature:"), 0, 0)
grid.addWidget(temp_display, 0, 1)
grid.addWidget(QLabel("Humidity:"), 1, 0)
grid.addWidget(humidity_display, 1, 1)
grid.addWidget(QLabel("Pressure:"), 2, 0)
grid.addWidget(pressure_display, 2, 1)

# Span multiple columns
grid.addWidget(control_button, 3, 0, 1, 2)  # row, col, rowspan, colspan
```

### 4. QFormLayout - Form-Style Layout

```python
from PyQt6.QtWidgets import QFormLayout

# Create form-style layout
form = QFormLayout()
form.addRow("Device Name:", device_name_input)
form.addRow("IP Address:", ip_input)
form.addRow("Port:", port_spinbox)
form.addRow("Protocol:", protocol_combo)
```

## Complete IoT Control Panel Example

Here's a comprehensive example combining multiple widgets and layouts:

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                             QHBoxLayout, QGridLayout, QLabel, QPushButton, 
                             QLineEdit, QSpinBox, QSlider, QCheckBox, QComboBox,
                             QLCDNumber, QProgressBar, QGroupBox)
from PyQt6.QtCore import Qt

class IoTControlPanel(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Control Panel")
        self.setGeometry(100, 100, 600, 500)
        
        # Main widget and layout
        main_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Title
        title = QLabel("IoT Device Control Center")
        title.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title.setStyleSheet("font-size: 24px; font-weight: bold; color: #1976D2; margin: 10px;")
        main_layout.addWidget(title)
        
        # Device Configuration Section
        config_group = QGroupBox("Device Configuration")
        config_layout = QGridLayout()
        
        config_layout.addWidget(QLabel("Device Name:"), 0, 0)
        self.device_name = QLineEdit("Arduino_Sensor_01")
        config_layout.addWidget(self.device_name, 0, 1)
        
        config_layout.addWidget(QLabel("Connection:"), 1, 0)
        self.connection_combo = QComboBox()
        self.connection_combo.addItems(["WiFi", "Bluetooth", "Serial"])
        config_layout.addWidget(self.connection_combo, 1, 1)
        
        config_group.setLayout(config_layout)
        main_layout.addWidget(config_group)
        
        # Sensor Readings Section
        sensors_group = QGroupBox("Sensor Readings")
        sensors_layout = QGridLayout()
        
        # Temperature
        sensors_layout.addWidget(QLabel("Temperature:"), 0, 0)
        self.temp_lcd = QLCDNumber(4)
        self.temp_lcd.display(25.4)
        sensors_layout.addWidget(self.temp_lcd, 0, 1)
        sensors_layout.addWidget(QLabel("°C"), 0, 2)
        
        # Humidity
        sensors_layout.addWidget(QLabel("Humidity:"), 1, 0)
        self.humidity_progress = QProgressBar()
        self.humidity_progress.setValue(65)
        sensors_layout.addWidget(self.humidity_progress, 1, 1)
        sensors_layout.addWidget(QLabel("%"), 1, 2)
        
        sensors_group.setLayout(sensors_layout)
        main_layout.addWidget(sensors_group)
        
        # Control Section
        control_group = QGroupBox("Device Control")
        control_layout = QVBoxLayout()
        
        # LED Control
        led_layout = QHBoxLayout()
        self.led_checkbox = QCheckBox("LED Status")
        led_layout.addWidget(self.led_checkbox)
        
        led_layout.addWidget(QLabel("Brightness:"))
        self.brightness_slider = QSlider(Qt.Orientation.Horizontal)
        self.brightness_slider.setRange(0, 100)
        self.brightness_slider.setValue(50)
        led_layout.addWidget(self.brightness_slider)
        
        self.brightness_label = QLabel("50%")
        led_layout.addWidget(self.brightness_label)
        
        control_layout.addLayout(led_layout)
        
        # Fan Control
        fan_layout = QHBoxLayout()
        fan_layout.addWidget(QLabel("Fan Speed:"))
        self.fan_speed = QSpinBox()
        self.fan_speed.setRange(0, 255)
        self.fan_speed.setValue(128)
        fan_layout.addWidget(self.fan_speed)
        fan_layout.addWidget(QLabel("RPM"))
        
        control_layout.addLayout(fan_layout)
        control_group.setLayout(control_layout)
        main_layout.addWidget(control_group)
        
        # Action Buttons
        button_layout = QHBoxLayout()
        
        self.connect_btn = QPushButton("Connect")
        self.read_btn = QPushButton("Read Sensors")
        self.reset_btn = QPushButton("Reset")
        
        # Style buttons
        button_style = """
            QPushButton {
                padding: 10px 20px;
                font-size: 14px;
                border-radius: 5px;
                border: none;
            }
        """
        
        self.connect_btn.setStyleSheet(button_style + "background-color: #4CAF50; color: white;")
        self.read_btn.setStyleSheet(button_style + "background-color: #2196F3; color: white;")
        self.reset_btn.setStyleSheet(button_style + "background-color: #FF9800; color: white;")
        
        button_layout.addWidget(self.connect_btn)
        button_layout.addWidget(self.read_btn)
        button_layout.addWidget(self.reset_btn)
        
        main_layout.addLayout(button_layout)
        
        # Status Bar
        self.status_label = QLabel("Status: Ready")
        self.status_label.setStyleSheet("background-color: #E8F5E8; padding: 5px; border-radius: 3px;")
        main_layout.addWidget(self.status_label)
        
        main_widget.setLayout(main_layout)
        self.setCentralWidget(main_widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    panel = IoTControlPanel()
    panel.show()
    app.exec()
```

## Widget Properties and Methods

### Common Properties for All Widgets

```python
# Visibility
widget.show()
widget.hide()
widget.setVisible(True/False)

# Size
widget.resize(width, height)
widget.setFixedSize(width, height)
widget.setMinimumSize(width, height)
widget.setMaximumSize(width, height)

# Position
widget.move(x, y)

# Styling
widget.setStyleSheet("color: red; background-color: yellow;")

# Enable/Disable
widget.setEnabled(True/False)

# Tooltips
widget.setToolTip("This is a helpful tooltip")
```

### Layout Properties

```python
# Spacing
layout.setSpacing(10)  # Space between widgets
layout.setContentsMargins(10, 10, 10, 10)  # Margins around the layout

# Stretch factors (for flexible sizing)
layout.addWidget(widget, stretch=1)  # This widget will take more space

# Alignment
layout.addWidget(widget, alignment=Qt.AlignmentFlag.AlignCenter)
```

## Best Practices for IoT Applications

1. **Group Related Controls**: Use QGroupBox to organize related widgets
2. **Use Appropriate Widgets**: LCD numbers for readings, sliders for ranges
3. **Provide Visual Feedback**: Use colors to show status (green=good, red=error)
4. **Clear Labels**: Make it obvious what each control does
5. **Reasonable Defaults**: Set sensible default values
6. **Input Validation**: Use appropriate ranges and formats

## Practice Exercise

Create an IoT greenhouse controller with:
1. Temperature and humidity displays (LCD numbers)
2. Ventilation fan speed control (slider)
3. Watering system on/off (checkbox)
4. Light intensity setting (spinbox)
5. Monitoring status display (label)
6. Emergency override button

## What's Next?

In the next tutorial, we'll learn about:
- Event handling and signals/slots
- Making widgets respond to user actions
- Connecting widgets together
- Real-time updates

Ready to make your widgets interactive? Let's move to Tutorial 4!