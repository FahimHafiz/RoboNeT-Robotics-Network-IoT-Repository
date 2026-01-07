<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# IoT Project 1: Real-Time Sensor Data Display

## Introduction

In this tutorial, we'll build our first complete IoT project - a real-time sensor data display system. This project will simulate sensor data, display it in real-time using various widgets, and provide basic data logging functionality. This is a foundational project that demonstrates core IoT interface concepts.

## Project Overview

Our IoT sensor dashboard will include:
- Real-time temperature, humidity, and pressure displays
- Visual indicators and alerts
- Data logging and export
- Multiple sensor simulation
- Connection status monitoring
- Historical data visualization

## Project Setup

Create a new folder for this project and the following files:
- `sensor_dashboard.py` - Main application
- `sensor_simulator.py` - Sensor data simulation
- `data_logger.py` - Data logging functionality
- `config.json` - Configuration file

## Step 1: Sensor Data Simulator

First, let's create a realistic sensor data simulator:

### sensor_simulator.py

```python
import random
import time
from datetime import datetime
from PyQt6.QtCore import QThread, pyqtSignal
import json

class SensorSimulator(QThread):
    """Simulates multiple IoT sensors with realistic data patterns"""
    
    # Signals for different types of sensor data
    temperature_data = pyqtSignal(float, str)  # value, timestamp
    humidity_data = pyqtSignal(float, str)
    pressure_data = pyqtSignal(float, str)
    light_data = pyqtSignal(int, str)
    air_quality_data = pyqtSignal(int, str)
    
    # Status signals
    sensor_connected = pyqtSignal(str, bool)  # sensor_name, connected
    sensor_error = pyqtSignal(str, str)  # sensor_name, error_message
    
    def __init__(self, config_file="config.json"):
        super().__init__()
        self.running = False
        self.config_file = config_file
        self.load_config()
        
        # Sensor base values for realistic simulation
        self.sensor_states = {
            'temperature': {'value': 22.0, 'trend': 0.0, 'variance': 2.0},
            'humidity': {'value': 55.0, 'trend': 0.0, 'variance': 5.0},
            'pressure': {'value': 1013.0, 'trend': 0.0, 'variance': 10.0},
            'light': {'value': 50, 'trend': 0, 'variance': 20},
            'air_quality': {'value': 75, 'trend': 0, 'variance': 15}
        }
        
        # Sensor reliability (chance of working properly)
        self.sensor_reliability = {
            'temperature': 0.98,
            'humidity': 0.95,
            'pressure': 0.97,
            'light': 0.92,
            'air_quality': 0.90
        }
        
        self.update_interval = 2.0  # seconds
    
    def load_config(self):
        """Load sensor configuration"""
        try:
            with open(self.config_file, 'r') as f:
                self.config = json.load(f)
        except FileNotFoundError:
            # Create default config
            self.config = {
                "sensors": {
                    "temperature": {"enabled": True, "unit": "°C", "min": -10, "max": 40},
                    "humidity": {"enabled": True, "unit": "%", "min": 20, "max": 90},
                    "pressure": {"enabled": True, "unit": "hPa", "min": 980, "max": 1050},
                    "light": {"enabled": True, "unit": "%", "min": 0, "max": 100},
                    "air_quality": {"enabled": True, "unit": "AQI", "min": 0, "max": 200}
                },
                "update_interval": 2.0,
                "simulation_mode": "realistic"
            }
            self.save_config()
    
    def save_config(self):
        """Save current configuration"""
        try:
            with open(self.config_file, 'w') as f:
                json.dump(self.config, f, indent=2)
        except Exception as e:
            print(f"Failed to save config: {e}")
    
    def run(self):
        """Main simulation loop"""
        self.running = True
        
        while self.running:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            # Simulate each enabled sensor
            if self.config["sensors"]["temperature"]["enabled"]:
                self.simulate_temperature(timestamp)
            
            if self.config["sensors"]["humidity"]["enabled"]:
                self.simulate_humidity(timestamp)
            
            if self.config["sensors"]["pressure"]["enabled"]:
                self.simulate_pressure(timestamp)
            
            if self.config["sensors"]["light"]["enabled"]:
                self.simulate_light(timestamp)
            
            if self.config["sensors"]["air_quality"]["enabled"]:
                self.simulate_air_quality(timestamp)
            
            # Wait for next update
            self.msleep(int(self.update_interval * 1000))
    
    def simulate_temperature(self, timestamp):
        """Simulate temperature sensor with realistic patterns"""
        sensor = 'temperature'
        
        # Check if sensor is "working"
        if random.random() > self.sensor_reliability[sensor]:
            self.sensor_error.emit(sensor, "Sensor not responding")
            return
        
        state = self.sensor_states[sensor]
        config = self.config["sensors"][sensor]
        
        # Add some realistic patterns
        hour = datetime.now().hour
        
        # Daily temperature cycle
        daily_factor = 3 * math.sin((hour - 6) * math.pi / 12)
        
        # Gradual trends
        if random.random() < 0.1:  # 10% chance to change trend
            state['trend'] = random.uniform(-0.1, 0.1)
        
        # Calculate new value
        change = state['trend'] + daily_factor * 0.1 + random.uniform(-0.5, 0.5)
        state['value'] += change
        
        # Keep within realistic bounds
        state['value'] = max(config["min"], min(config["max"], state['value']))
        
        # Add small random noise
        noisy_value = state['value'] + random.uniform(-0.2, 0.2)
        
        self.temperature_data.emit(round(noisy_value, 1), timestamp)
        self.sensor_connected.emit(sensor, True)
    
    def simulate_humidity(self, timestamp):
        """Simulate humidity sensor"""
        sensor = 'humidity'
        
        if random.random() > self.sensor_reliability[sensor]:
            self.sensor_error.emit(sensor, "Calibration error")
            return
        
        state = self.sensor_states[sensor]
        config = self.config["sensors"][sensor]
        
        # Humidity often correlates inversely with temperature
        temp_state = self.sensor_states['temperature']
        temp_influence = (temp_state['value'] - 22) * -0.8
        
        # Gradual changes
        if random.random() < 0.08:
            state['trend'] = random.uniform(-0.2, 0.2)
        
        change = state['trend'] + temp_influence * 0.1 + random.uniform(-1, 1)
        state['value'] += change
        
        state['value'] = max(config["min"], min(config["max"], state['value']))
        
        noisy_value = state['value'] + random.uniform(-0.5, 0.5)
        
        self.humidity_data.emit(round(noisy_value, 1), timestamp)
        self.sensor_connected.emit(sensor, True)
    
    def simulate_pressure(self, timestamp):
        """Simulate atmospheric pressure sensor"""
        sensor = 'pressure'
        
        if random.random() > self.sensor_reliability[sensor]:
            self.sensor_error.emit(sensor, "Communication timeout")
            return
        
        state = self.sensor_states[sensor]
        config = self.config["sensors"][sensor]
        
        # Pressure changes slowly
        if random.random() < 0.05:
            state['trend'] = random.uniform(-0.1, 0.1)
        
        change = state['trend'] + random.uniform(-0.5, 0.5)
        state['value'] += change
        
        state['value'] = max(config["min"], min(config["max"], state['value']))
        
        self.pressure_data.emit(round(state['value'], 1), timestamp)
        self.sensor_connected.emit(sensor, True)
    
    def simulate_light(self, timestamp):
        """Simulate light sensor with day/night cycle"""
        sensor = 'light'
        
        if random.random() > self.sensor_reliability[sensor]:
            self.sensor_error.emit(sensor, "Sensor dirty")
            return
        
        state = self.sensor_states[sensor]
        config = self.config["sensors"][sensor]
        
        hour = datetime.now().hour
        
        # Day/night cycle
        if 6 <= hour <= 18:  # Daytime
            target = 80 + 15 * math.sin((hour - 6) * math.pi / 12)
        else:  # Nighttime
            target = 10 + random.uniform(-5, 5)
        
        # Move towards target
        difference = target - state['value']
        state['value'] += difference * 0.1 + random.uniform(-5, 5)
        
        state['value'] = max(config["min"], min(config["max"], state['value']))
        
        self.light_data.emit(int(state['value']), timestamp)
        self.sensor_connected.emit(sensor, True)
    
    def simulate_air_quality(self, timestamp):
        """Simulate air quality sensor"""
        sensor = 'air_quality'
        
        if random.random() > self.sensor_reliability[sensor]:
            self.sensor_error.emit(sensor, "Sensor needs replacement")
            return
        
        state = self.sensor_states[sensor]
        config = self.config["sensors"][sensor]
        
        # Air quality can change based on various factors
        hour = datetime.now().hour
        
        # Rush hour effects
        if hour in [7, 8, 17, 18, 19]:  # Rush hours
            pollution_factor = 20
        else:
            pollution_factor = -10
        
        if random.random() < 0.12:
            state['trend'] = random.uniform(-1, 1)
        
        change = state['trend'] + pollution_factor * 0.05 + random.uniform(-3, 3)
        state['value'] += change
        
        state['value'] = max(config["min"], min(config["max"], state['value']))
        
        self.air_quality_data.emit(int(state['value']), timestamp)
        self.sensor_connected.emit(sensor, True)
    
    def stop(self):
        """Stop the simulation"""
        self.running = False
        self.wait()  # Wait for thread to finish

# Import math for sine calculations
import math
```

## Step 2: Data Logger

Create a data logging system to store sensor readings:

### data_logger.py

```python
import csv
import json
import os
from datetime import datetime, timedelta
from PyQt6.QtCore import QObject, pyqtSignal

class DataLogger(QObject):
    """Handles data logging for IoT sensor data"""
    
    log_saved = pyqtSignal(str)  # filename
    log_error = pyqtSignal(str)  # error message
    
    def __init__(self, log_directory="sensor_logs"):
        super().__init__()
        self.log_directory = log_directory
        self.current_session = []
        self.session_start = datetime.now()
        
        # Create log directory if it doesn't exist
        os.makedirs(log_directory, exist_ok=True)
        
        # Initialize current session file
        self.session_file = self.get_session_filename()
        self.init_csv_file()
    
    def get_session_filename(self):
        """Generate filename for current session"""
        timestamp = self.session_start.strftime("%Y%m%d_%H%M%S")
        return os.path.join(self.log_directory, f"sensor_data_{timestamp}.csv")
    
    def init_csv_file(self):
        """Initialize CSV file with headers"""
        try:
            with open(self.session_file, 'w', newline='') as csvfile:
                fieldnames = ['timestamp', 'sensor_type', 'value', 'unit', 'status']
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                writer.writeheader()
        except Exception as e:
            self.log_error.emit(f"Failed to initialize log file: {str(e)}")
    
    def log_data(self, sensor_type, value, unit, status="OK"):
        """Log a single sensor reading"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        data_point = {
            'timestamp': timestamp,
            'sensor_type': sensor_type,
            'value': value,
            'unit': unit,
            'status': status
        }
        
        # Add to current session
        self.current_session.append(data_point)
        
        # Write to CSV file
        try:
            with open(self.session_file, 'a', newline='') as csvfile:
                fieldnames = ['timestamp', 'sensor_type', 'value', 'unit', 'status']
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                writer.writerow(data_point)
        except Exception as e:
            self.log_error.emit(f"Failed to write to log: {str(e)}")
    
    def get_recent_data(self, sensor_type, minutes=60):
        """Get recent data for a specific sensor"""
        cutoff_time = datetime.now() - timedelta(minutes=minutes)
        
        recent_data = []
        for data_point in self.current_session:
            point_time = datetime.strptime(data_point['timestamp'], "%Y-%m-%d %H:%M:%S")
            if point_time >= cutoff_time and data_point['sensor_type'] == sensor_type:
                recent_data.append(data_point)
        
        return recent_data
    
    def export_session_json(self, filename=None):
        """Export current session to JSON"""
        if filename is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = os.path.join(self.log_directory, f"session_export_{timestamp}.json")
        
        try:
            export_data = {
                "session_info": {
                    "start_time": self.session_start.strftime("%Y-%m-%d %H:%M:%S"),
                    "export_time": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                    "total_readings": len(self.current_session)
                },
                "data": self.current_session
            }
            
            with open(filename, 'w') as jsonfile:
                json.dump(export_data, jsonfile, indent=2)
            
            self.log_saved.emit(filename)
            return filename
            
        except Exception as e:
            self.log_error.emit(f"Failed to export JSON: {str(e)}")
            return None
    
    def get_session_summary(self):
        """Get summary statistics for current session"""
        if not self.current_session:
            return {}
        
        summary = {
            'session_start': self.session_start.strftime("%Y-%m-%d %H:%M:%S"),
            'duration': str(datetime.now() - self.session_start),
            'total_readings': len(self.current_session),
            'sensors': {}
        }
        
        # Group by sensor type
        sensor_data = {}
        for reading in self.current_session:
            sensor = reading['sensor_type']
            if sensor not in sensor_data:
                sensor_data[sensor] = []
            sensor_data[sensor].append(float(reading['value']))
        
        # Calculate statistics for each sensor
        for sensor, values in sensor_data.items():
            if values:
                summary['sensors'][sensor] = {
                    'count': len(values),
                    'min': min(values),
                    'max': max(values),
                    'avg': round(sum(values) / len(values), 2),
                    'latest': values[-1]
                }
        
        return summary
    
    def clear_session(self):
        """Clear current session data"""
        self.current_session.clear()
        self.session_start = datetime.now()
        self.session_file = self.get_session_filename()
        self.init_csv_file()
```

## Step 3: Main Sensor Dashboard

Now let's create the main application:

### sensor_dashboard.py

```python
import sys
import json
from datetime import datetime
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QGridLayout, QWidget, QPushButton, QLabel, QLCDNumber,
                             QProgressBar, QGroupBox, QTextEdit, QComboBox, QSpinBox,
                             QCheckBox, QMessageBox, QFileDialog, QTableWidget,
                             QTableWidgetItem, QTabWidget)
from PyQt6.QtCore import QTimer, Qt, pyqtSlot
from PyQt6.QtGui import QFont, QPalette, QColor

from sensor_simulator import SensorSimulator
from data_logger import DataLogger

class SensorDashboard(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("IoT Real-Time Sensor Dashboard")
        self.setGeometry(100, 100, 1200, 800)
        
        # Initialize components
        self.sensor_simulator = SensorSimulator()
        self.data_logger = DataLogger()
        
        # Data storage for real-time plotting
        self.sensor_history = {
            'temperature': [],
            'humidity': [],
            'pressure': [],
            'light': [],
            'air_quality': []
        }
        
        # Connection status
        self.sensor_status = {
            'temperature': False,
            'humidity': False,
            'pressure': False,
            'light': False,
            'air_quality': False
        }
        
        self.initUI()
        self.connect_signals()
        self.setup_timers()
        
        # Start simulation
        self.start_monitoring()
    
    def initUI(self):
        """Initialize the user interface"""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Create tab widget for different views
        tab_widget = QTabWidget()
        
        # Real-time monitoring tab
        monitoring_tab = self.create_monitoring_tab()
        tab_widget.addTab(monitoring_tab, "Real-Time Monitoring")
        
        # Data analysis tab
        analysis_tab = self.create_analysis_tab()
        tab_widget.addTab(analysis_tab, "Data Analysis")
        
        # Settings tab
        settings_tab = self.create_settings_tab()
        tab_widget.addTab(settings_tab, "Settings")
        
        # Main layout
        main_layout = QVBoxLayout()
        main_layout.addWidget(tab_widget)
        
        central_widget.setLayout(main_layout)
        
        # Set application style
        self.setStyleSheet("""
            QMainWindow {
                background-color: #f0f0f0;
            }
            QGroupBox {
                font-weight: bold;
                border: 2px solid #cccccc;
                border-radius: 5px;
                margin-top: 1ex;
                padding-top: 10px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px 0 5px;
            }
            QLCDNumber {
                background-color: #000000;
                color: #00ff00;
                border: 2px solid #cccccc;
                border-radius: 5px;
            }
            QPushButton {
                background-color: #4CAF50;
                color: white;
                border: none;
                padding: 8px 16px;
                border-radius: 4px;
                font-size: 14px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
            QPushButton:pressed {
                background-color: #3e8e41;
            }
        """)
    
    def create_monitoring_tab(self):
        """Create the real-time monitoring tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Top row - Control panel
        control_group = QGroupBox("System Control")
        control_layout = QHBoxLayout()
        
        self.start_stop_btn = QPushButton("Stop Monitoring")
        self.start_stop_btn.clicked.connect(self.toggle_monitoring)
        
        self.export_btn = QPushButton("Export Data")
        self.export_btn.clicked.connect(self.export_data)
        
        self.clear_btn = QPushButton("Clear Data")
        self.clear_btn.clicked.connect(self.clear_data)
        
        # System status
        self.system_status = QLabel("System Status: Running")
        self.system_status.setStyleSheet("background-color: #c8e6c9; padding: 8px; border-radius: 4px;")
        
        control_layout.addWidget(self.start_stop_btn)
        control_layout.addWidget(self.export_btn)
        control_layout.addWidget(self.clear_btn)
        control_layout.addStretch()
        control_layout.addWidget(self.system_status)
        
        control_group.setLayout(control_layout)
        
        # Sensor displays
        sensors_layout = QGridLayout()
        
        # Temperature
        temp_group = self.create_sensor_group("Temperature", "°C", "#ff6b35")
        self.temp_lcd = temp_group.findChild(QLCDNumber)
        self.temp_status = temp_group.findChild(QLabel, "status_label")
        sensors_layout.addWidget(temp_group, 0, 0)
        
        # Humidity
        humidity_group = self.create_sensor_group("Humidity", "%", "#4ecdc4")
        self.humidity_lcd = humidity_group.findChild(QLCDNumber)
        self.humidity_status = humidity_group.findChild(QLabel, "status_label")
        sensors_layout.addWidget(humidity_group, 0, 1)
        
        # Pressure
        pressure_group = self.create_sensor_group("Pressure", "hPa", "#45b7d1")
        self.pressure_lcd = pressure_group.findChild(QLCDNumber)
        self.pressure_status = pressure_group.findChild(QLabel, "status_label")
        sensors_layout.addWidget(pressure_group, 1, 0)
        
        # Light
        light_group = self.create_sensor_group("Light", "%", "#f9ca24")
        self.light_progress = light_group.findChild(QProgressBar)
        self.light_status = light_group.findChild(QLabel, "status_label")
        sensors_layout.addWidget(light_group, 1, 1)
        
        # Air Quality
        air_group = self.create_sensor_group("Air Quality", "AQI", "#6c5ce7")
        self.air_progress = air_group.findChild(QProgressBar)
        self.air_status = air_group.findChild(QLabel, "status_label")
        sensors_layout.addWidget(air_group, 2, 0)
        
        # Recent alerts
        alerts_group = QGroupBox("Recent Alerts")
        alerts_layout = QVBoxLayout()
        
        self.alerts_text = QTextEdit()
        self.alerts_text.setMaximumHeight(120)
        self.alerts_text.setReadOnly(True)
        
        alerts_layout.addWidget(self.alerts_text)
        alerts_group.setLayout(alerts_layout)
        
        sensors_layout.addWidget(alerts_group, 2, 1)
        
        # Add to main layout
        layout.addWidget(control_group)
        layout.addLayout(sensors_layout)
        
        tab.setLayout(layout)
        return tab
    
    def create_sensor_group(self, name, unit, color):
        """Create a sensor display group"""
        group = QGroupBox(f"{name} Sensor")
        layout = QVBoxLayout()
        
        if name in ["Light", "Air Quality"]:
            # Use progress bar for percentage values
            display = QProgressBar()
            display.setRange(0, 100 if name == "Light" else 200)
            display.setFormat(f"%v {unit}")
            display.setStyleSheet(f"""
                QProgressBar {{
                    border: 2px solid grey;
                    border-radius: 5px;
                    text-align: center;
                    font-size: 14px;
                    font-weight: bold;
                }}
                QProgressBar::chunk {{
                    background-color: {color};
                    border-radius: 3px;
                }}
            """)
        else:
            # Use LCD display for precise values
            display = QLCDNumber(5)
            display.setStyleSheet(f"""
                QLCDNumber {{
                    background-color: #000000;
                    color: {color};
                    border: 2px solid #cccccc;
                    border-radius: 5px;
                }}
            """)
        
        # Value label
        value_label = QLabel(f"Current: -- {unit}")
        value_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        
        # Status label
        status_label = QLabel("Status: Disconnected")
        status_label.setObjectName("status_label")
        status_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        status_label.setStyleSheet("background-color: #ffcdd2; padding: 4px; border-radius: 3px; color: red;")
        
        layout.addWidget(display)
        layout.addWidget(value_label)
        layout.addWidget(status_label)
        
        group.setLayout(layout)
        return group
    
    def create_analysis_tab(self):
        """Create the data analysis tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Analysis controls
        control_group = QGroupBox("Analysis Controls")
        control_layout = QHBoxLayout()
        
        control_layout.addWidget(QLabel("Time Range:"))
        self.time_range_combo = QComboBox()
        self.time_range_combo.addItems(["Last 10 minutes", "Last 30 minutes", "Last hour", "All data"])
        
        self.refresh_analysis_btn = QPushButton("Refresh Analysis")
        self.refresh_analysis_btn.clicked.connect(self.refresh_analysis)
        
        control_layout.addWidget(self.time_range_combo)
        control_layout.addWidget(self.refresh_analysis_btn)
        control_layout.addStretch()
        
        control_group.setLayout(control_layout)
        
        # Data table
        data_group = QGroupBox("Raw Data")
        data_layout = QVBoxLayout()
        
        self.data_table = QTableWidget()
        self.data_table.setColumnCount(5)
        self.data_table.setHorizontalHeaderLabels(["Timestamp", "Sensor", "Value", "Unit", "Status"])
        
        # Auto-resize columns
        header = self.data_table.horizontalHeader()
        header.setStretchLastSection(True)
        
        data_layout.addWidget(self.data_table)
        data_group.setLayout(data_layout)
        
        # Statistics
        stats_group = QGroupBox("Statistics Summary")
        self.stats_text = QTextEdit()
        self.stats_text.setMaximumHeight(150)
        self.stats_text.setReadOnly(True)
        
        stats_layout = QVBoxLayout()
        stats_layout.addWidget(self.stats_text)
        stats_group.setLayout(stats_layout)
        
        layout.addWidget(control_group)
        layout.addWidget(data_group, 2)  # Give more space to data table
        layout.addWidget(stats_group)
        
        tab.setLayout(layout)
        return tab
    
    def create_settings_tab(self):
        """Create the settings tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Simulation settings
        sim_group = QGroupBox("Simulation Settings")
        sim_layout = QGridLayout()
        
        sim_layout.addWidget(QLabel("Update Interval:"), 0, 0)
        self.interval_spinbox = QSpinBox()
        self.interval_spinbox.setRange(1, 60)
        self.interval_spinbox.setValue(2)
        self.interval_spinbox.setSuffix(" seconds")
        sim_layout.addWidget(self.interval_spinbox, 0, 1)
        
        # Sensor enable/disable
        sim_layout.addWidget(QLabel("Enable Sensors:"), 1, 0)
        
        self.sensor_checkboxes = {}
        sensors = ["temperature", "humidity", "pressure", "light", "air_quality"]
        for i, sensor in enumerate(sensors):
            checkbox = QCheckBox(sensor.replace('_', ' ').title())
            checkbox.setChecked(True)
            self.sensor_checkboxes[sensor] = checkbox
            sim_layout.addWidget(checkbox, 2 + i // 2, i % 2)
        
        sim_group.setLayout(sim_layout)
        
        # Alert settings
        alert_group = QGroupBox("Alert Thresholds")
        alert_layout = QGridLayout()
        
        # Temperature alerts
        alert_layout.addWidget(QLabel("Temperature Max:"), 0, 0)
        self.temp_max_spinbox = QSpinBox()
        self.temp_max_spinbox.setRange(-50, 100)
        self.temp_max_spinbox.setValue(30)
        self.temp_max_spinbox.setSuffix("°C")
        alert_layout.addWidget(self.temp_max_spinbox, 0, 1)
        
        # Humidity alerts
        alert_layout.addWidget(QLabel("Humidity Max:"), 1, 0)
        self.humidity_max_spinbox = QSpinBox()
        self.humidity_max_spinbox.setRange(0, 100)
        self.humidity_max_spinbox.setValue(80)
        self.humidity_max_spinbox.setSuffix("%")
        alert_layout.addWidget(self.humidity_max_spinbox, 1, 1)
        
        # Air quality alerts
        alert_layout.addWidget(QLabel("Air Quality Max:"), 2, 0)
        self.air_max_spinbox = QSpinBox()
        self.air_max_spinbox.setRange(0, 300)
        self.air_max_spinbox.setValue(150)
        self.air_max_spinbox.setSuffix(" AQI")
        alert_layout.addWidget(self.air_max_spinbox, 2, 1)
        
        alert_group.setLayout(alert_layout)
        
        # Apply settings button
        apply_btn = QPushButton("Apply Settings")
        apply_btn.clicked.connect(self.apply_settings)
        
        layout.addWidget(sim_group)
        layout.addWidget(alert_group)
        layout.addStretch()
        layout.addWidget(apply_btn)
        
        tab.setLayout(layout)
        return tab
    
    def connect_signals(self):
        """Connect sensor simulator signals to dashboard slots"""
        # Data signals
        self.sensor_simulator.temperature_data.connect(self.update_temperature)
        self.sensor_simulator.humidity_data.connect(self.update_humidity)
        self.sensor_simulator.pressure_data.connect(self.update_pressure)
        self.sensor_simulator.light_data.connect(self.update_light)
        self.sensor_simulator.air_quality_data.connect(self.update_air_quality)
        
        # Status signals
        self.sensor_simulator.sensor_connected.connect(self.update_sensor_status)
        self.sensor_simulator.sensor_error.connect(self.handle_sensor_error)
        
        # Data logger signals
        self.data_logger.log_saved.connect(self.on_log_saved)
        self.data_logger.log_error.connect(self.on_log_error)
    
    def setup_timers(self):
        """Setup timers for periodic updates"""
        # Analysis refresh timer
        self.analysis_timer = QTimer()
        self.analysis_timer.timeout.connect(self.refresh_analysis)
        self.analysis_timer.start(30000)  # Refresh every 30 seconds
    
    @pyqtSlot(float, str)
    def update_temperature(self, value, timestamp):
        """Update temperature display"""
        self.temp_lcd.display(value)
        
        # Update value label
        temp_group = self.temp_lcd.parent()
        value_label = temp_group.findChildren(QLabel)[0]
        value_label.setText(f"Current: {value}°C")
        
        # Check for alerts
        if value > self.temp_max_spinbox.value():
            self.add_alert(f"HIGH TEMPERATURE: {value}°C at {timestamp}")
        
        # Log data
        self.data_logger.log_data("temperature", value, "°C")
        
        # Store for history
        self.sensor_history['temperature'].append((timestamp, value))
        if len(self.sensor_history['temperature']) > 100:  # Keep last 100 readings
            self.sensor_history['temperature'].pop(0)
    
    @pyqtSlot(float, str)
    def update_humidity(self, value, timestamp):
        """Update humidity display"""
        self.humidity_lcd.display(value)
        
        # Update value label
        humidity_group = self.humidity_lcd.parent()
        value_label = humidity_group.findChildren(QLabel)[0]
        value_label.setText(f"Current: {value}%")
        
        # Check for alerts
        if value > self.humidity_max_spinbox.value():
            self.add_alert(f"HIGH HUMIDITY: {value}% at {timestamp}")
        
        # Log data
        self.data_logger.log_data("humidity", value, "%")
        
        # Store for history
        self.sensor_history['humidity'].append((timestamp, value))
        if len(self.sensor_history['humidity']) > 100:
            self.sensor_history['humidity'].pop(0)
    
    @pyqtSlot(float, str)
    def update_pressure(self, value, timestamp):
        """Update pressure display"""
        self.pressure_lcd.display(value)
        
        # Update value label
        pressure_group = self.pressure_lcd.parent()
        value_label = pressure_group.findChildren(QLabel)[0]
        value_label.setText(f"Current: {value} hPa")
        
        # Log data
        self.data_logger.log_data("pressure", value, "hPa")
        
        # Store for history
        self.sensor_history['pressure'].append((timestamp, value))
        if len(self.sensor_history['pressure']) > 100:
            self.sensor_history['pressure'].pop(0)
    
    @pyqtSlot(int, str)
    def update_light(self, value, timestamp):
        """Update light display"""
        self.light_progress.setValue(value)
        
        # Update value label
        light_group = self.light_progress.parent()
        value_label = light_group.findChildren(QLabel)[0]
        value_label.setText(f"Current: {value}%")
        
        # Log data
        self.data_logger.log_data("light", value, "%")
        
        # Store for history
        self.sensor_history['light'].append((timestamp, value))
        if len(self.sensor_history['light']) > 100:
            self.sensor_history['light'].pop(0)
    
    @pyqtSlot(int, str)
    def update_air_quality(self, value, timestamp):
        """Update air quality display"""
        self.air_progress.setValue(value)
        
        # Update value label and color based on AQI level
        air_group = self.air_progress.parent()
        value_label = air_group.findChildren(QLabel)[0]
        value_label.setText(f"Current: {value} AQI")
        
        # Color coding for air quality
        if value <= 50:
            color = "#4CAF50"  # Good - Green
            level = "Good"
        elif value <= 100:
            color = "#FFEB3B"  # Moderate - Yellow
            level = "Moderate"
        elif value <= 150:
            color = "#FF9800"  # Unhealthy for sensitive - Orange
            level = "Unhealthy for Sensitive"
        elif value <= 200:
            color = "#f44336"  # Unhealthy - Red
            level = "Unhealthy"
        else:
            color = "#9C27B0"  # Very Unhealthy - Purple
            level = "Very Unhealthy"
        
        self.air_progress.setStyleSheet(f"""
            QProgressBar {{
                border: 2px solid grey;
                border-radius: 5px;
                text-align: center;
                font-size: 14px;
                font-weight: bold;
            }}
            QProgressBar::chunk {{
                background-color: {color};
                border-radius: 3px;
            }}
        """)
        
        # Check for alerts
        if value > self.air_max_spinbox.value():
            self.add_alert(f"POOR AIR QUALITY: {value} AQI ({level}) at {timestamp}")
        
        # Log data
        self.data_logger.log_data("air_quality", value, "AQI")
        
        # Store for history
        self.sensor_history['air_quality'].append((timestamp, value))
        if len(self.sensor_history['air_quality']) > 100:
            self.sensor_history['air_quality'].pop(0)
    
    @pyqtSlot(str, bool)
    def update_sensor_status(self, sensor_name, connected):
        """Update sensor connection status"""
        self.sensor_status[sensor_name] = connected
        
        # Find the appropriate status label
        status_label = None
        if sensor_name == "temperature":
            status_label = self.temp_status
        elif sensor_name == "humidity":
            status_label = self.humidity_status
        elif sensor_name == "pressure":
            status_label = self.pressure_status
        elif sensor_name == "light":
            status_label = self.light_status
        elif sensor_name == "air_quality":
            status_label = self.air_status
        
        if status_label:
            if connected:
                status_label.setText("Status: Connected")
                status_label.setStyleSheet("background-color: #c8e6c9; padding: 4px; border-radius: 3px; color: green;")
            else:
                status_label.setText("Status: Disconnected")
                status_label.setStyleSheet("background-color: #ffcdd2; padding: 4px; border-radius: 3px; color: red;")
    
    @pyqtSlot(str, str)
    def handle_sensor_error(self, sensor_name, error_message):
        """Handle sensor errors"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        self.add_alert(f"SENSOR ERROR ({sensor_name}): {error_message} at {timestamp}")
        
        # Log error
        self.data_logger.log_data(sensor_name, 0, "error", error_message)
    
    def add_alert(self, message):
        """Add an alert message to the alerts display"""
        current_text = self.alerts_text.toPlainText()
        new_text = f"{message}\\n{current_text}"
        
        # Keep only last 10 alerts
        lines = new_text.split('\\n')
        if len(lines) > 10:
            lines = lines[:10]
        
        self.alerts_text.setText('\\n'.join(lines))
    
    def start_monitoring(self):
        """Start sensor monitoring"""
        if not self.sensor_simulator.isRunning():
            self.sensor_simulator.start()
            self.system_status.setText("System Status: Running")
            self.system_status.setStyleSheet("background-color: #c8e6c9; padding: 8px; border-radius: 4px;")
    
    def stop_monitoring(self):
        """Stop sensor monitoring"""
        if self.sensor_simulator.isRunning():
            self.sensor_simulator.stop()
            self.system_status.setText("System Status: Stopped")
            self.system_status.setStyleSheet("background-color: #ffcdd2; padding: 8px; border-radius: 4px;")
    
    def toggle_monitoring(self):
        """Toggle monitoring on/off"""
        if self.sensor_simulator.isRunning():
            self.stop_monitoring()
            self.start_stop_btn.setText("Start Monitoring")
        else:
            self.start_monitoring()
            self.start_stop_btn.setText("Stop Monitoring")
    
    def export_data(self):
        """Export collected data"""
        filename, _ = QFileDialog.getSaveFileName(
            self, "Export Sensor Data",
            f"sensor_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json",
            "JSON files (*.json);;CSV files (*.csv);;All files (*.*)"
        )
        
        if filename:
            if filename.endswith('.json'):
                exported_file = self.data_logger.export_session_json(filename)
                if exported_file:
                    QMessageBox.information(self, "Export Complete", f"Data exported to:\\n{exported_file}")
            else:
                # For CSV, copy the current session file
                import shutil
                try:
                    shutil.copy2(self.data_logger.session_file, filename)
                    QMessageBox.information(self, "Export Complete", f"Data exported to:\\n{filename}")
                except Exception as e:
                    QMessageBox.critical(self, "Export Error", f"Failed to export data:\\n{str(e)}")
    
    def clear_data(self):
        """Clear all collected data"""
        reply = QMessageBox.question(self, "Clear Data", 
                                   "Are you sure you want to clear all collected data?\\n\\n"
                                   "This action cannot be undone.")
        
        if reply == QMessageBox.StandardButton.Yes:
            self.data_logger.clear_session()
            self.sensor_history = {key: [] for key in self.sensor_history.keys()}
            self.alerts_text.clear()
            self.refresh_analysis()
            QMessageBox.information(self, "Data Cleared", "All data has been cleared.")
    
    def refresh_analysis(self):
        """Refresh the data analysis tab"""
        # Update data table
        session_data = self.data_logger.current_session
        
        # Filter by time range if needed
        time_range = self.time_range_combo.currentText()
        if time_range != "All data":
            # Implementation for time filtering would go here
            pass
        
        # Populate table
        self.data_table.setRowCount(len(session_data))
        for i, data_point in enumerate(session_data):
            self.data_table.setItem(i, 0, QTableWidgetItem(data_point['timestamp']))
            self.data_table.setItem(i, 1, QTableWidgetItem(data_point['sensor_type']))
            self.data_table.setItem(i, 2, QTableWidgetItem(str(data_point['value'])))
            self.data_table.setItem(i, 3, QTableWidgetItem(data_point['unit']))
            self.data_table.setItem(i, 4, QTableWidgetItem(data_point['status']))
        
        # Update statistics
        summary = self.data_logger.get_session_summary()
        if summary:
            stats_text = f"Session Started: {summary['session_start']}\\n"
            stats_text += f"Duration: {summary['duration']}\\n"
            stats_text += f"Total Readings: {summary['total_readings']}\\n\\n"
            
            for sensor, stats in summary['sensors'].items():
                stats_text += f"{sensor.upper()}:\\n"
                stats_text += f"  Count: {stats['count']}\\n"
                stats_text += f"  Range: {stats['min']} - {stats['max']}\\n"
                stats_text += f"  Average: {stats['avg']}\\n"
                stats_text += f"  Latest: {stats['latest']}\\n\\n"
            
            self.stats_text.setText(stats_text)
        else:
            self.stats_text.setText("No data available for analysis.")
    
    def apply_settings(self):
        """Apply settings changes"""
        # Update sensor simulator configuration
        new_interval = self.interval_spinbox.value()
        if hasattr(self.sensor_simulator, 'update_interval'):
            self.sensor_simulator.update_interval = new_interval
        
        # Enable/disable sensors
        for sensor, checkbox in self.sensor_checkboxes.items():
            if hasattr(self.sensor_simulator, 'config'):
                self.sensor_simulator.config['sensors'][sensor]['enabled'] = checkbox.isChecked()
        
        # Save configuration
        if hasattr(self.sensor_simulator, 'save_config'):
            self.sensor_simulator.save_config()
        
        QMessageBox.information(self, "Settings Applied", "Settings have been applied successfully.")
    
    @pyqtSlot(str)
    def on_log_saved(self, filename):
        """Handle log saved signal"""
        print(f"Log saved: {filename}")
    
    @pyqtSlot(str)
    def on_log_error(self, error_message):
        """Handle log error signal"""
        QMessageBox.warning(self, "Logging Error", error_message)
    
    def closeEvent(self, event):
        """Handle application close"""
        # Stop sensor simulation
        if self.sensor_simulator.isRunning():
            self.sensor_simulator.stop()
        
        # Export final data
        final_export = self.data_logger.export_session_json()
        if final_export:
            QMessageBox.information(self, "Session Saved", 
                                   f"Final session data saved to:\\n{final_export}")
        
        event.accept()

def main():
    app = QApplication(sys.argv)
    
    # Set application properties
    app.setApplicationName("IoT Sensor Dashboard")
    app.setApplicationVersion("1.0")
    app.setOrganizationName("IoT Solutions")
    
    dashboard = SensorDashboard()
    dashboard.show()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
```

## Step 4: Configuration File

Create a basic configuration file:

### config.json

```json
{
  "sensors": {
    "temperature": {
      "enabled": true,
      "unit": "°C",
      "min": -10,
      "max": 40,
      "alert_threshold": 30
    },
    "humidity": {
      "enabled": true,
      "unit": "%",
      "min": 20,
      "max": 90,
      "alert_threshold": 80
    },
    "pressure": {
      "enabled": true,
      "unit": "hPa",
      "min": 980,
      "max": 1050,
      "alert_threshold": 1040
    },
    "light": {
      "enabled": true,
      "unit": "%",
      "min": 0,
      "max": 100,
      "alert_threshold": 95
    },
    "air_quality": {
      "enabled": true,
      "unit": "AQI",
      "min": 0,
      "max": 200,
      "alert_threshold": 150
    }
  },
  "update_interval": 2.0,
  "simulation_mode": "realistic",
  "data_logging": {
    "enabled": true,
    "auto_export": true,
    "retention_hours": 24
  }
}
```

## Running the Project

1. **Install required packages:**
   ```bash
   pip install PyQt6
   ```

2. **Create the project files** as shown above

3. **Run the application:**
   ```bash
   python sensor_dashboard.py
   ```

## Key Features Demonstrated

### Real-Time Data Display
- LCD numbers for precise readings
- Progress bars for percentage values
- Color-coded status indicators
- Automatic value updates

### Data Management
- Real-time data logging to CSV
- Session-based data storage
- Export functionality (JSON/CSV)
- Data analysis and statistics

### User Interface Design
- Tabbed interface for different views
- Responsive layout with proper sizing
- Professional styling with CSS
- Clear visual hierarchy

### Sensor Simulation
- Realistic sensor value patterns
- Error simulation and handling
- Configurable sensor parameters
- Connection status monitoring

### Alert System
- Threshold-based alerts
- Real-time alert display
- Error message handling
- Visual and textual feedback

## Extension Ideas

1. **Add Charts/Graphs**: Use matplotlib to show historical trends
2. **Database Integration**: Store data in SQLite database
3. **Network Communication**: Connect to real IoT devices
4. **Email Alerts**: Send notifications when thresholds are exceeded
5. **Remote Monitoring**: Add web interface for remote access

## What's Next?

In the next tutorial, we'll build:
- LED Control Interface Project
- Device control and automation
- Real hardware communication
- Advanced user interactions

This project serves as a foundation for more complex IoT applications. You can extend it with real sensor data, network communication, and advanced visualization features.

Ready to control IoT devices? Let's move to Tutorial 9!