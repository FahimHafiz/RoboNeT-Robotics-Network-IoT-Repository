<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>

# PyQt6 Basics: Your First Window

## Introduction

Now that you have PyQt6 installed, let's create your first GUI application! This tutorial will teach you the fundamental concepts of PyQt6 and how to create a basic window.

## Understanding PyQt6 Structure

Every PyQt6 application has these key components:

1. **QApplication** - Manages the entire application
2. **QMainWindow** - The main window of your application
3. **Widgets** - UI elements like buttons, labels, text boxes
4. **Event Loop** - Keeps the application running and responsive

## Your First PyQt6 Application

Let's start with the simplest possible PyQt6 application:

### Example 1: Basic Window

Create a file called `first_window.py`:

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow

# Create the application
app = QApplication(sys.argv)

# Create the main window
window = QMainWindow()
window.setWindowTitle("My First PyQt6 Window")
window.setGeometry(100, 100, 400, 300)  # x, y, width, height
window.show()

# Start the event loop
app.exec()
```

**Run it:** `python first_window.py`

You should see an empty window! 🎉

## Breaking Down the Code

Let's understand each line:

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow
```
- Import necessary modules
- `sys` provides access to command line arguments
- `QApplication` and `QMainWindow` are our building blocks

```python
app = QApplication(sys.argv)
```
- Creates the application object
- `sys.argv` passes command line arguments

```python
window = QMainWindow()
```
- Creates the main window object

```python
window.setWindowTitle("My First PyQt6 Window")
window.setGeometry(100, 100, 400, 300)
```
- Sets window title and position/size
- `setGeometry(x, y, width, height)`

```python
window.show()
```
- Makes the window visible

```python
app.exec()
```
- Starts the event loop (keeps the app running)

## Object-Oriented Approach (Recommended)

The professional way to write PyQt6 applications is using classes:

### Example 2: Class-Based Window

Create `class_window.py`:

```python
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        # Set window properties
        self.setWindowTitle("IoT Control Panel")
        self.setGeometry(200, 200, 500, 400)
        
        # Create a welcome label
        label = QLabel("Welcome to IoT with PyQt6!")
        label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        
        # Set the label as central widget
        self.setCentralWidget(label)

# Application setup
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    app.exec()
```

## Adding Basic Widgets

Let's add some interactive elements:

### Example 3: Multiple Widgets

Create `widgets_demo.py`:

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, 
                             QVBoxLayout, QLabel, QPushButton, QLineEdit)
from PyQt6.QtCore import Qt

class IoTDashboard(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Dashboard")
        self.setGeometry(300, 300, 400, 300)
        
        # Create central widget and layout
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Create widgets
        title_label = QLabel("IoT Device Controller")
        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title_label.setStyleSheet("font-size: 18px; font-weight: bold; color: blue;")
        
        device_input = QLineEdit()
        device_input.setPlaceholderText("Enter device name...")
        
        connect_button = QPushButton("Connect to Device")
        status_label = QLabel("Status: Disconnected")
        
        # Add widgets to layout
        layout.addWidget(title_label)
        layout.addWidget(device_input)
        layout.addWidget(connect_button)
        layout.addWidget(status_label)
        
        # Set the layout
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    dashboard = IoTDashboard()
    dashboard.show()
    app.exec()
```

## Common Widgets for IoT Applications

Here are widgets you'll use frequently in IoT projects:

### Labels and Text
```python
# Label for displaying information
label = QLabel("Temperature: 25°C")

# Text input for user data
text_input = QLineEdit()
text_input.setPlaceholderText("Enter sensor ID...")

# Multi-line text area
from PyQt6.QtWidgets import QTextEdit
text_area = QTextEdit()
```

### Buttons
```python
# Regular button
button = QPushButton("Read Sensor")

# Checkbox for on/off states
from PyQt6.QtWidgets import QCheckBox
checkbox = QCheckBox("Enable LED")

# Radio buttons for options
from PyQt6.QtWidgets import QRadioButton
radio1 = QRadioButton("Mode 1")
radio2 = QRadioButton("Mode 2")
```

### Value Controls
```python
# Spinbox for numeric input
from PyQt6.QtWidgets import QSpinBox
spinbox = QSpinBox()
spinbox.setRange(0, 100)

# Slider for ranges
from PyQt6.QtWidgets import QSlider
slider = QSlider(Qt.Orientation.Horizontal)
slider.setRange(0, 255)  # For LED brightness

# Progress bar for status
from PyQt6.QtWidgets import QProgressBar
progress = QProgressBar()
progress.setValue(75)
```

## Window Properties and Styling

### Setting Window Properties
```python
class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Basic properties
        self.setWindowTitle("IoT Controller")
        self.setGeometry(100, 100, 600, 400)
        
        # Fixed size (optional)
        self.setFixedSize(600, 400)
        
        # Minimum/maximum size
        self.setMinimumSize(300, 200)
        self.setMaximumSize(800, 600)
```

### Basic Styling
```python
# Style individual widgets
label.setStyleSheet("""
    QLabel {
        color: red;
        font-size: 16px;
        font-weight: bold;
        background-color: yellow;
        padding: 10px;
        border: 2px solid blue;
        border-radius: 5px;
    }
""")

# Style the entire window
self.setStyleSheet("""
    QMainWindow {
        background-color: #f0f0f0;
    }
    QPushButton {
        background-color: #4CAF50;
        color: white;
        border: none;
        padding: 10px;
        border-radius: 5px;
    }
    QPushButton:hover {
        background-color: #45a049;
    }
""")
```

## Practice Exercise

Create a simple IoT device simulator with these features:
1. Device name input field
2. Temperature display label
3. LED on/off button
4. Status indicator

### Solution Template

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, 
                             QVBoxLayout, QHBoxLayout, QLabel, 
                             QPushButton, QLineEdit)

class IoTSimulator(QMainWindow):
    def __init__(self):
        super().__init__()
        self.led_status = False
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Simulator")
        self.setGeometry(300, 300, 400, 250)
        
        # Create central widget and main layout
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Device name section
        device_layout = QHBoxLayout()
        device_layout.addWidget(QLabel("Device:"))
        self.device_input = QLineEdit()
        self.device_input.setText("Arduino_01")
        device_layout.addWidget(self.device_input)
        
        # Temperature display
        self.temp_label = QLabel("Temperature: 24.5°C")
        self.temp_label.setStyleSheet("font-size: 14px; color: blue;")
        
        # LED control
        led_layout = QHBoxLayout()
        self.led_button = QPushButton("Turn LED ON")
        self.led_status_label = QLabel("LED: OFF")
        led_layout.addWidget(self.led_button)
        led_layout.addWidget(self.led_status_label)
        
        # Status
        self.status_label = QLabel("Status: Ready")
        self.status_label.setStyleSheet("color: green;")
        
        # Add all to main layout
        main_layout.addLayout(device_layout)
        main_layout.addWidget(self.temp_label)
        main_layout.addLayout(led_layout)
        main_layout.addWidget(self.status_label)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    simulator = IoTSimulator()
    simulator.show()
    app.exec()
```

## Key Concepts to Remember

1. **Always create QApplication first** - It manages your entire application
2. **Use classes for complex applications** - Much cleaner and maintainable
3. **Set a central widget** - MainWindow needs a central widget to display content
4. **Call show()** - Windows are hidden by default
5. **Start the event loop** - app.exec() keeps your application running

## Common Beginner Mistakes

1. **Forgetting app.exec()** - Your window will appear and immediately close
2. **Not setting central widget** - Content won't display properly
3. **Creating widgets without a parent** - May cause memory issues
4. **Forgetting to call show()** - Window stays hidden

## What's Next?

In the next tutorial, we'll dive deeper into:
- Different types of widgets
- Layout management
- Widget properties and methods
- Event handling basics

## Quick Reference

```python
# Basic window template
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow

class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("My App")
        self.setGeometry(100, 100, 400, 300)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    app.exec()
```

Ready to learn about widgets and layouts? Let's move to Tutorial 3!