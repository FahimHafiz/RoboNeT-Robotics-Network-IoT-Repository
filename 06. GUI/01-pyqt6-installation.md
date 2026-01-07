<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# PyQt6 Installation Guide

## Introduction

Welcome to PyQt6! This guide will help you install everything you need to start building GUI applications for IoT projects. PyQt6 is a powerful toolkit that allows you to create desktop applications with Python.

## What We'll Install

1. **Python** (if not already installed)
2. **PyQt6** - The main GUI framework
3. **Qt Designer** - Visual interface designer
4. **Additional IoT Libraries** - For sensor communication

## Step 1: Check Python Installation

First, let's check if Python is installed on your system.

### Windows

1. Open Command Prompt (Press `Win + R`, type `cmd`, press Enter)
2. Type: `python --version`
3. If you see a version number (3.8 or higher), you're good to go!

### macOS/Linux

1. Open Terminal
2. Type: `python3 --version`
3. If you see a version number (3.8 or higher), you're ready!

### If Python is Not Installed

- Visit [python.org](https://python.org)
- Download Python 3.9 or higher
- **Important**: During installation on Windows, check "Add Python to PATH"

## Step 2: Install PyQt6

### Using pip (Recommended)

Open your terminal/command prompt and run:

```bash
pip install PyQt6
```

For macOS/Linux users, you might need:

```bash
pip3 install PyQt6
```

### Install Qt Designer

Qt Designer comes with PyQt6-tools:

```bash
pip install PyQt6-tools
```

## Step 3: Install Additional IoT Libraries

For our IoT projects, we'll need these libraries:

```bash
# For serial communication (Arduino, sensors)
pip install pyserial

# For GPIO control (Raspberry Pi)
pip install RPi.GPIO

# For plotting sensor data
pip install matplotlib

# For data handling
pip install pandas numpy
```

## Step 4: Verify Installation

Let's test if everything is working:

### Test 1: Basic PyQt6

Create a file called `test_pyqt6.py`:

```python
import sys
from PyQt6.QtWidgets import QApplication, QLabel, QMainWindow

class TestWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt6 Test")
        label = QLabel("PyQt6 is working!")
        self.setCentralWidget(label)

app = QApplication(sys.argv)
window = TestWindow()
window.show()
app.exec()
```

Run it:

```bash
python test_pyqt6.py
```

If a window appears with "PyQt6 is working!", you're all set!

### Test 2: Qt Designer

Try to run Qt Designer:

**Windows:**

```bash
designer
```

**macOS/Linux:**

```bash
pyqt6-tools designer
```

If Qt Designer opens, congratulations! You're ready for the next tutorial.

## Troubleshooting

### Common Issues

1. **"pip is not recognized"**

   - Reinstall Python with "Add to PATH" checked
   - Or use full path: `C:\Python39\Scripts\pip.exe install PyQt6`

2. **Permission errors on macOS/Linux**

   - Use: `pip3 install --user PyQt6`

3. **Qt Designer won't open**

   - Try: `python -m PyQt6.uic.pyuic -h`
   - If this works, Designer is installed but path issues exist

4. **Import errors**
   - Make sure you're using the same Python version you installed PyQt6 with
   - Check: `python -c "import PyQt6; print('Success!')"`

### Alternative Installation Methods

#### Using Anaconda

If you use Anaconda:

```bash
conda install -c anaconda pyqt
```

#### Using Virtual Environment (Recommended for projects)

```bash
# Create virtual environment
python -m venv pyqt6_env

# Activate it
# Windows:
pyqt6_env\Scripts\activate
# macOS/Linux:
source pyqt6_env/bin/activate

# Install PyQt6
pip install PyQt6 PyQt6-tools
```

## What's Next?

In the next tutorial, we'll:

- Create our first PyQt6 window
- Understand the basic structure of a PyQt6 application
- Learn about widgets and layouts

## Quick Reference

### Essential Commands

```bash
# Install PyQt6
pip install PyQt6

# Install tools (includes Designer)
pip install PyQt6-tools

# Run Qt Designer
designer  # or pyqt6-tools designer

# Test installation
python -c "import PyQt6; print('PyQt6 installed successfully!')"
```

Ready to start building amazing IoT interfaces? Let's move to Tutorial 2!
