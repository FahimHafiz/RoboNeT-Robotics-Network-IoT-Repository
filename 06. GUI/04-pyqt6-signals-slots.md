<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# PyQt6 Events and Signals/Slots

## Introduction

Events and signals/slots are what make your PyQt6 applications interactive! When a user clicks a button, moves a slider, or types in a text box, these actions create events. Signals and slots are PyQt6's way of handling these events and making widgets communicate with each other.

## Understanding Signals and Slots

### What are Signals?
Signals are notifications sent by widgets when something happens:
- Button clicked
- Text changed
- Slider moved
- Timer timeout

### What are Slots?
Slots are functions that respond to signals:
- Built-in slots (like `close()`, `show()`)
- Custom functions you write

### The Connection
You connect signals to slots using the `connect()` method:
```python
signal.connect(slot)
```

## Basic Signal/Slot Examples

### Example 1: Button Click Response

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QPushButton, QLabel

class ButtonExample(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("Button Click Example")
        self.setGeometry(300, 300, 300, 200)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Create widgets
        self.status_label = QLabel("Click the button!")
        self.click_button = QPushButton("Click Me")
        
        # Connect signal to slot
        self.click_button.clicked.connect(self.button_clicked)
        
        layout.addWidget(self.status_label)
        layout.addWidget(self.click_button)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)
    
    def button_clicked(self):
        """This is a custom slot function"""
        self.status_label.setText("Button was clicked!")
        print("Button clicked!")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ButtonExample()
    window.show()
    app.exec()
```

### Example 2: IoT Device Connection Simulator

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QLabel, QLineEdit, QComboBox)

class IoTConnector(QMainWindow):
    def __init__(self):
        super().__init__()
        self.connected = False
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Connector")
        self.setGeometry(250, 250, 400, 250)
        
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Device selection
        device_layout = QHBoxLayout()
        device_layout.addWidget(QLabel("Device:"))
        self.device_combo = QComboBox()
        self.device_combo.addItems(["Arduino Uno", "Raspberry Pi", "ESP32", "NodeMCU"])
        device_layout.addWidget(self.device_combo)
        
        # IP Address input
        ip_layout = QHBoxLayout()
        ip_layout.addWidget(QLabel("IP Address:"))
        self.ip_input = QLineEdit()
        self.ip_input.setPlaceholderText("192.168.1.100")
        self.ip_input.setText("192.168.1.100")
        ip_layout.addWidget(self.ip_input)
        
        # Status display
        self.status_label = QLabel("Status: Disconnected")
        self.status_label.setStyleSheet("background-color: #ffcdd2; padding: 10px; border-radius: 5px;")\n        
        # Connect button
        self.connect_btn = QPushButton("Connect")\n        self.connect_btn.setStyleSheet("""
            QPushButton {
                background-color: #4CAF50;
                color: white;
                padding: 10px;
                border: none;
                border-radius: 5px;
                font-size: 14px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        """)
        
        # Connect signals
        self.connect_btn.clicked.connect(self.toggle_connection)
        self.device_combo.currentTextChanged.connect(self.device_changed)
        self.ip_input.textChanged.connect(self.ip_changed)
        
        # Add to layout
        main_layout.addLayout(device_layout)
        main_layout.addLayout(ip_layout)
        main_layout.addWidget(self.status_label)
        main_layout.addWidget(self.connect_btn)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def toggle_connection(self):
        """Slot for connect/disconnect button"""
        if not self.connected:
            # Connect
            device = self.device_combo.currentText()
            ip = self.ip_input.text()
            
            if ip:  # Simple validation
                self.connected = True
                self.status_label.setText(f"Status: Connected to {device} at {ip}")
                self.status_label.setStyleSheet("background-color: #c8e6c9; padding: 10px; border-radius: 5px;")
                self.connect_btn.setText("Disconnect")
                self.connect_btn.setStyleSheet("""
                    QPushButton {
                        background-color: #f44336;
                        color: white;
                        padding: 10px;
                        border: none;
                        border-radius: 5px;
                        font-size: 14px;
                    }
                    QPushButton:hover {
                        background-color: #d32f2f;
                    }
                """)
            else:
                self.status_label.setText("Status: Please enter IP address")
        else:
            # Disconnect
            self.connected = False
            self.status_label.setText("Status: Disconnected")
            self.status_label.setStyleSheet("background-color: #ffcdd2; padding: 10px; border-radius: 5px;")
            self.connect_btn.setText("Connect")
            self.connect_btn.setStyleSheet("""
                QPushButton {
                    background-color: #4CAF50;
                    color: white;
                    padding: 10px;
                    border: none;
                    border-radius: 5px;
                    font-size: 14px;
                }
                QPushButton:hover {
                    background-color: #45a049;
                }
            """)
    
    def device_changed(self, device_name):
        """Slot for device selection change"""
        print(f"Device changed to: {device_name}")
        if self.connected:
            self.status_label.setText(f"Status: Connected to {device_name}")
    
    def ip_changed(self, new_ip):
        """Slot for IP address change"""
        print(f"IP changed to: {new_ip}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTConnector()
    window.show()
    app.exec()
```

## Common Widget Signals

### Button Signals
```python
button.clicked.connect(slot_function)          # Button clicked
button.pressed.connect(slot_function)          # Button pressed down
button.released.connect(slot_function)         # Button released
```

### Text Input Signals
```python
line_edit.textChanged.connect(slot_function)       # Text changed
line_edit.textEdited.connect(slot_function)        # Text edited by user
line_edit.returnPressed.connect(slot_function)     # Enter key pressed
line_edit.editingFinished.connect(slot_function)   # Editing finished
```

### Slider Signals
```python
slider.valueChanged.connect(slot_function)         # Value changed
slider.sliderMoved.connect(slot_function)          # Slider moved by user
slider.sliderPressed.connect(slot_function)        # Slider pressed
slider.sliderReleased.connect(slot_function)       # Slider released
```

### Checkbox Signals
```python
checkbox.stateChanged.connect(slot_function)       # Check state changed
checkbox.clicked.connect(slot_function)            # Checkbox clicked
```

### Combobox Signals
```python
combo.currentTextChanged.connect(slot_function)    # Selected text changed
combo.currentIndexChanged.connect(slot_function)   # Selected index changed
combo.activated.connect(slot_function)             # Item activated
```

## Real-time IoT Control Example

Here's a comprehensive example showing multiple widgets working together:

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QLabel, QSlider, QCheckBox,
                             QSpinBox, QLCDNumber, QProgressBar, QGroupBox)
from PyQt6.QtCore import Qt, QTimer
import random

class IoTController(QMainWindow):
    def __init__(self):
        super().__init__()
        self.led_enabled = False
        self.fan_enabled = False
        self.initUI()
        self.setup_timer()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Controller")
        self.setGeometry(200, 200, 500, 400)
        
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Sensor Display Section
        sensor_group = QGroupBox("Sensor Readings")
        sensor_layout = QHBoxLayout()
        
        # Temperature LCD
        temp_layout = QVBoxLayout()
        temp_layout.addWidget(QLabel("Temperature"))
        self.temp_lcd = QLCDNumber(4)
        self.temp_lcd.display(23.5)
        temp_layout.addWidget(self.temp_lcd)
        
        # Humidity Progress Bar
        humidity_layout = QVBoxLayout()
        humidity_layout.addWidget(QLabel("Humidity"))
        self.humidity_bar = QProgressBar()
        self.humidity_bar.setValue(45)
        humidity_layout.addWidget(self.humidity_bar)
        
        sensor_layout.addLayout(temp_layout)
        sensor_layout.addLayout(humidity_layout)
        sensor_group.setLayout(sensor_layout)
        
        # Control Section
        control_group = QGroupBox("Device Control")
        control_layout = QVBoxLayout()
        
        # LED Control
        led_layout = QHBoxLayout()
        self.led_checkbox = QCheckBox("LED Control")
        self.brightness_slider = QSlider(Qt.Orientation.Horizontal)
        self.brightness_slider.setRange(0, 100)
        self.brightness_slider.setValue(50)
        self.brightness_slider.setEnabled(False)  # Disabled initially
        self.brightness_label = QLabel("50%")
        
        led_layout.addWidget(self.led_checkbox)
        led_layout.addWidget(QLabel("Brightness:"))
        led_layout.addWidget(self.brightness_slider)
        led_layout.addWidget(self.brightness_label)
        
        # Fan Control
        fan_layout = QHBoxLayout()
        self.fan_checkbox = QCheckBox("Fan Control")
        self.fan_speed = QSpinBox()
        self.fan_speed.setRange(0, 100)
        self.fan_speed.setValue(0)
        self.fan_speed.setSuffix("%")
        self.fan_speed.setEnabled(False)  # Disabled initially
        
        fan_layout.addWidget(self.fan_checkbox)
        fan_layout.addWidget(QLabel("Speed:"))
        fan_layout.addWidget(self.fan_speed)
        
        control_layout.addLayout(led_layout)
        control_layout.addLayout(fan_layout)
        control_group.setLayout(control_layout)
        
        # Action Buttons
        button_layout = QHBoxLayout()
        self.read_btn = QPushButton("Read Sensors")
        self.auto_btn = QPushButton("Auto Mode")
        self.reset_btn = QPushButton("Reset All")
        
        button_layout.addWidget(self.read_btn)
        button_layout.addWidget(self.auto_btn)
        button_layout.addWidget(self.reset_btn)
        
        # Status
        self.status_label = QLabel("Status: Ready")
        
        # Connect all signals
        self.connect_signals()
        
        # Add to main layout
        main_layout.addWidget(sensor_group)
        main_layout.addWidget(control_group)
        main_layout.addLayout(button_layout)
        main_layout.addWidget(self.status_label)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def connect_signals(self):
        """Connect all widget signals to their slots"""
        # LED controls
        self.led_checkbox.stateChanged.connect(self.led_state_changed)
        self.brightness_slider.valueChanged.connect(self.brightness_changed)
        
        # Fan controls
        self.fan_checkbox.stateChanged.connect(self.fan_state_changed)
        self.fan_speed.valueChanged.connect(self.fan_speed_changed)
        
        # Buttons
        self.read_btn.clicked.connect(self.read_sensors)
        self.auto_btn.clicked.connect(self.toggle_auto_mode)
        self.reset_btn.clicked.connect(self.reset_all)
    
    def led_state_changed(self, state):
        """Handle LED checkbox state change"""
        self.led_enabled = state == Qt.CheckState.Checked.value
        self.brightness_slider.setEnabled(self.led_enabled)
        
        if self.led_enabled:
            self.status_label.setText("Status: LED Enabled")
        else:
            self.status_label.setText("Status: LED Disabled")
            self.brightness_slider.setValue(0)
    
    def brightness_changed(self, value):
        """Handle brightness slider change"""
        self.brightness_label.setText(f"{value}%")
        if self.led_enabled:
            self.status_label.setText(f"Status: LED Brightness {value}%")
    
    def fan_state_changed(self, state):
        """Handle fan checkbox state change"""
        self.fan_enabled = state == Qt.CheckState.Checked.value
        self.fan_speed.setEnabled(self.fan_enabled)
        
        if not self.fan_enabled:
            self.fan_speed.setValue(0)
    
    def fan_speed_changed(self, value):
        """Handle fan speed change"""
        if self.fan_enabled:
            self.status_label.setText(f"Status: Fan Speed {value}%")
    
    def read_sensors(self):
        """Simulate reading sensors"""
        # Simulate random sensor values
        temp = round(random.uniform(20.0, 30.0), 1)
        humidity = random.randint(40, 80)
        
        self.temp_lcd.display(temp)
        self.humidity_bar.setValue(humidity)
        
        self.status_label.setText(f"Status: Sensors read - {temp}°C, {humidity}%")
    
    def toggle_auto_mode(self):
        """Toggle automatic mode"""
        if self.auto_btn.text() == "Auto Mode":
            self.auto_btn.setText("Manual Mode")
            self.status_label.setText("Status: Auto mode enabled")
            self.timer.start(2000)  # Update every 2 seconds
        else:
            self.auto_btn.setText("Auto Mode")
            self.status_label.setText("Status: Manual mode")
            self.timer.stop()
    
    def reset_all(self):
        """Reset all controls"""
        self.led_checkbox.setChecked(False)
        self.fan_checkbox.setChecked(False)
        self.brightness_slider.setValue(50)
        self.fan_speed.setValue(0)
        self.temp_lcd.display(0)
        self.humidity_bar.setValue(0)
        self.status_label.setText("Status: All reset")
        
        if self.timer.isActive():
            self.timer.stop()
            self.auto_btn.setText("Auto Mode")
    
    def setup_timer(self):
        """Setup timer for auto mode"""
        self.timer = QTimer()
        self.timer.timeout.connect(self.auto_update)
    
    def auto_update(self):
        """Auto mode update function"""
        self.read_sensors()
        
        # Auto-adjust fan based on temperature
        current_temp = self.temp_lcd.value()
        if current_temp > 25:
            if not self.fan_enabled:
                self.fan_checkbox.setChecked(True)
            self.fan_speed.setValue(min(100, int((current_temp - 20) * 10)))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    controller = IoTController()
    controller.show()
    app.exec()
```

## Passing Data with Signals

Sometimes you need to pass data from the signal to the slot:

### Example: Custom Signals with Data

```python
from PyQt6.QtCore import pyqtSignal

class CustomWidget(QWidget):
    # Define custom signal that passes data
    data_received = pyqtSignal(str, int)  # Signal with string and int parameters
    
    def __init__(self):
        super().__init__()
        
        # Connect custom signal to slot
        self.data_received.connect(self.handle_data)
    
    def send_data(self):
        """Emit signal with data"""
        self.data_received.emit("Temperature", 25)
    
    def handle_data(self, sensor_type, value):
        """Handle the received data"""
        print(f"Received {sensor_type}: {value}")
```

## Lambda Functions for Simple Slots

For simple operations, you can use lambda functions:

```python
# Instead of creating a separate function
button.clicked.connect(lambda: self.status_label.setText("Button clicked!"))

# Passing parameters
button1.clicked.connect(lambda: self.set_device("Arduino"))
button2.clicked.connect(lambda: self.set_device("Raspberry Pi"))

def set_device(self, device_name):
    self.device_label.setText(f"Selected: {device_name}")
```

## Event Handling

Besides signals/slots, you can also override event handler methods:

```python
class MyWindow(QMainWindow):
    def closeEvent(self, event):
        """Handle window close event"""
        print("Window is closing!")
        event.accept()  # Allow close
        # or event.ignore() to prevent closing
    
    def keyPressEvent(self, event):
        """Handle key press events"""
        if event.key() == Qt.Key.Key_Escape:
            self.close()
        super().keyPressEvent(event)
    
    def mousePressEvent(self, event):
        """Handle mouse press events"""
        if event.button() == Qt.MouseButton.LeftButton:
            print("Left mouse button pressed")
        super().mousePressEvent(event)
```

## Best Practices

1. **Keep slots simple**: Do the main work in separate methods
2. **Use descriptive names**: `button_clicked()` is better than `handle_click()`
3. **Handle errors**: Always consider what might go wrong
4. **Disconnect signals**: When widgets are destroyed, disconnect signals to prevent errors
5. **Use custom signals**: For complex applications, create your own signals

## Practice Exercise

Create an IoT greenhouse monitor with:
1. Temperature threshold spinbox that changes a warning label color
2. Watering button that disables for 5 seconds after clicking
3. Light timer that automatically updates every second
4. Emergency stop that disables all controls

## What's Next?

In the next tutorial, we'll learn about:
- Qt Designer - Visual interface creation
- Converting Designer files to Python
- Integrating Designer UIs with code
- Professional workflow

Ready to design visually? Let's move to Tutorial 5!