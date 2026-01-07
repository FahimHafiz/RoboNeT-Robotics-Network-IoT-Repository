<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# PyQt6 Data Handling and File Operations

## Introduction

IoT applications generate and consume lots of data - sensor readings, configuration files, logs, and reports. This tutorial covers how to handle data storage, work with JSON and CSV files, manage application settings, and implement data persistence in your PyQt6 IoT applications.

## Working with JSON Configuration Files

JSON is perfect for storing IoT device configurations, settings, and structured data:

### IoT Configuration Manager

```python
import sys
import json
import os
from datetime import datetime
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QLabel, QTextEdit, QListWidget,
                             QInputDialog, QMessageBox, QSplitter, QGroupBox)
from PyQt6.QtCore import Qt

class IoTConfigManager(QMainWindow):
    def __init__(self):
        super().__init__()
        self.config_file = "iot_devices.json"
        self.devices_config = {}
        self.initUI()
        self.load_configurations()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Configuration Manager")
        self.setGeometry(150, 150, 800, 600)
        
        central_widget = QWidget()
        main_layout = QHBoxLayout()
        
        # Left panel - Device list
        left_panel = QGroupBox("Registered Devices")
        left_layout = QVBoxLayout()
        
        self.device_list = QListWidget()
        self.device_list.itemSelectionChanged.connect(self.device_selected)
        
        device_buttons = QHBoxLayout()
        add_device_btn = QPushButton("Add Device")
        remove_device_btn = QPushButton("Remove Device")
        clone_device_btn = QPushButton("Clone Device")
        
        add_device_btn.clicked.connect(self.add_device)
        remove_device_btn.clicked.connect(self.remove_device)
        clone_device_btn.clicked.connect(self.clone_device)
        
        device_buttons.addWidget(add_device_btn)
        device_buttons.addWidget(remove_device_btn)
        device_buttons.addWidget(clone_device_btn)
        
        left_layout.addWidget(self.device_list)
        left_layout.addLayout(device_buttons)
        left_panel.setLayout(left_layout)
        
        # Right panel - Configuration editor
        right_panel = QGroupBox("Device Configuration (JSON)")
        right_layout = QVBoxLayout()
        
        self.config_editor = QTextEdit()
        self.config_editor.setPlaceholderText("Select a device to view its configuration...")
        
        config_buttons = QHBoxLayout()
        save_btn = QPushButton("Save Configuration")
        validate_btn = QPushButton("Validate JSON")
        export_btn = QPushButton("Export All")
        import_btn = QPushButton("Import Devices")
        
        save_btn.clicked.connect(self.save_current_config)
        validate_btn.clicked.connect(self.validate_json)
        export_btn.clicked.connect(self.export_all_configs)
        import_btn.clicked.connect(self.import_configs)
        
        config_buttons.addWidget(save_btn)
        config_buttons.addWidget(validate_btn)
        config_buttons.addWidget(export_btn)
        config_buttons.addWidget(import_btn)
        
        # Status label
        self.status_label = QLabel("Ready")
        self.status_label.setStyleSheet("background-color: #e8f5e8; padding: 5px; border-radius: 3px;")
        
        right_layout.addWidget(self.config_editor)
        right_layout.addLayout(config_buttons)
        right_layout.addWidget(self.status_label)
        right_panel.setLayout(right_layout)
        
        # Use splitter for resizable panels
        splitter = QSplitter(Qt.Orientation.Horizontal)
        splitter.addWidget(left_panel)
        splitter.addWidget(right_panel)
        splitter.setSizes([250, 550])  # Set initial sizes
        
        main_layout.addWidget(splitter)
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def load_configurations(self):
        """Load device configurations from JSON file"""
        try:
            if os.path.exists(self.config_file):
                with open(self.config_file, 'r') as f:
                    self.devices_config = json.load(f)
                
                self.refresh_device_list()
                self.status_label.setText(f"Loaded {len(self.devices_config)} devices from {self.config_file}")
            else:
                # Create sample configuration
                self.create_sample_config()
                
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load configurations:\\n{str(e)}")
            self.devices_config = {}
    
    def create_sample_config(self):
        """Create sample IoT device configurations"""
        self.devices_config = {
            "greenhouse_sensor": {
                "device_info": {
                    "name": "Greenhouse Environmental Sensor",
                    "type": "Multi-sensor",
                    "location": "Greenhouse Zone A",
                    "manufacturer": "Arduino",
                    "model": "Uno R3 + DHT22 + BMP280"
                },
                "network": {
                    "ip_address": "192.168.1.101",
                    "port": 8080,
                    "protocol": "HTTP",
                    "wifi_ssid": "GreenHouse_WiFi"
                },
                "sensors": [
                    {
                        "type": "temperature",
                        "unit": "celsius",
                        "pin": 2,
                        "reading_interval": 60,
                        "calibration_offset": 0.0
                    },
                    {
                        "type": "humidity",
                        "unit": "percentage",
                        "pin": 2,
                        "reading_interval": 60,
                        "calibration_offset": 0.0
                    },
                    {
                        "type": "pressure",
                        "unit": "hPa",
                        "pin": "I2C",
                        "reading_interval": 300,
                        "calibration_offset": 0.0
                    }
                ],
                "thresholds": {
                    "temperature_min": 18.0,
                    "temperature_max": 28.0,
                    "humidity_min": 50.0,
                    "humidity_max": 80.0,
                    "pressure_min": 980.0,
                    "pressure_max": 1050.0
                },
                "actions": {
                    "ventilation_fan": {
                        "trigger": "temperature > 25",
                        "pin": 3,
                        "action": "digital_high"
                    },
                    "irrigation": {
                        "trigger": "humidity < 60",
                        "pin": 4,
                        "action": "digital_high",
                        "duration": 30
                    }
                },
                "data_logging": {
                    "enabled": True,
                    "local_storage": True,
                    "cloud_upload": False,
                    "retention_days": 30
                },
                "last_updated": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            },
            "security_camera": {
                "device_info": {
                    "name": "Security Camera System",
                    "type": "IP Camera",
                    "location": "Main Entrance",
                    "manufacturer": "Raspberry Pi Foundation",
                    "model": "Pi 4B + Camera Module"
                },
                "network": {
                    "ip_address": "192.168.1.102",
                    "port": 8081,
                    "protocol": "RTSP",
                    "wifi_ssid": "Security_WiFi"
                },
                "camera_settings": {
                    "resolution": "1920x1080",
                    "framerate": 30,
                    "night_vision": True,
                    "motion_detection": True,
                    "recording_quality": "high"
                },
                "detection_settings": {
                    "sensitivity": 75,
                    "detection_zones": [
                        {"name": "entrance", "coordinates": [100, 100, 400, 300]},
                        {"name": "parking", "coordinates": [500, 200, 800, 500]}
                    ],
                    "alert_email": "security@example.com"
                },
                "storage": {
                    "local_recording": True,
                    "cloud_backup": True,
                    "retention_days": 7,
                    "max_storage_gb": 500
                },
                "last_updated": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
        }
        
        self.save_configurations()
        self.refresh_device_list()
    
    def save_configurations(self):
        """Save all configurations to JSON file"""
        try:
            with open(self.config_file, 'w') as f:
                json.dump(self.devices_config, f, indent=2)
            return True
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save configurations:\\n{str(e)}")
            return False
    
    def refresh_device_list(self):
        """Refresh the device list widget"""
        self.device_list.clear()
        for device_id in self.devices_config.keys():
            device_name = self.devices_config[device_id].get('device_info', {}).get('name', device_id)
            self.device_list.addItem(f"{device_id} - {device_name}")
    
    def device_selected(self):
        """Handle device selection"""
        current_item = self.device_list.currentItem()
        if current_item:
            device_id = current_item.text().split(' - ')[0]
            config_json = json.dumps(self.devices_config[device_id], indent=2)
            self.config_editor.setText(config_json)
            self.status_label.setText(f"Viewing configuration for: {device_id}")
    
    def add_device(self):
        """Add a new device"""
        device_id, ok = QInputDialog.getText(self, "New Device", "Enter device ID:")
        
        if ok and device_id:
            if device_id in self.devices_config:
                QMessageBox.warning(self, "Error", "Device ID already exists!")
                return
            
            # Create basic device template
            template = {
                "device_info": {
                    "name": f"New {device_id}",
                    "type": "Unknown",
                    "location": "Not specified",
                    "manufacturer": "",
                    "model": ""
                },
                "network": {
                    "ip_address": "192.168.1.100",
                    "port": 8080,
                    "protocol": "HTTP"
                },
                "sensors": [],
                "thresholds": {},
                "actions": {},
                "data_logging": {
                    "enabled": True,
                    "local_storage": True,
                    "retention_days": 7
                },
                "last_updated": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            }
            
            self.devices_config[device_id] = template
            self.refresh_device_list()
            
            # Select the new device
            for i in range(self.device_list.count()):
                if self.device_list.item(i).text().startswith(device_id):
                    self.device_list.setCurrentRow(i)
                    break
            
            self.status_label.setText(f"Added new device: {device_id}")
    
    def remove_device(self):
        """Remove selected device"""
        current_item = self.device_list.currentItem()
        if not current_item:
            QMessageBox.warning(self, "Error", "Please select a device to remove.")
            return
        
        device_id = current_item.text().split(' - ')[0]
        
        reply = QMessageBox.question(self, "Confirm Delete", 
                                   f"Are you sure you want to delete device '{device_id}'?\\n\\n"
                                   "This action cannot be undone.")
        
        if reply == QMessageBox.StandardButton.Yes:
            del self.devices_config[device_id]
            self.refresh_device_list()
            self.config_editor.clear()
            self.status_label.setText(f"Removed device: {device_id}")
    
    def clone_device(self):
        """Clone selected device"""
        current_item = self.device_list.currentItem()
        if not current_item:
            QMessageBox.warning(self, "Error", "Please select a device to clone.")
            return
        
        source_device_id = current_item.text().split(' - ')[0]
        new_device_id, ok = QInputDialog.getText(self, "Clone Device", 
                                               f"Enter new device ID for clone of '{source_device_id}':")
        
        if ok and new_device_id:
            if new_device_id in self.devices_config:
                QMessageBox.warning(self, "Error", "Device ID already exists!")
                return
            
            # Deep copy the configuration
            import copy
            cloned_config = copy.deepcopy(self.devices_config[source_device_id])
            cloned_config['device_info']['name'] = f"Clone of {cloned_config['device_info']['name']}"
            cloned_config['last_updated'] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            self.devices_config[new_device_id] = cloned_config
            self.refresh_device_list()
            self.status_label.setText(f"Cloned device: {source_device_id} -> {new_device_id}")
    
    def save_current_config(self):
        """Save current configuration being edited"""
        current_item = self.device_list.currentItem()
        if not current_item:
            QMessageBox.warning(self, "Error", "Please select a device.")
            return
        
        device_id = current_item.text().split(' - ')[0]
        config_text = self.config_editor.toPlainText()
        
        try:
            # Validate JSON
            new_config = json.loads(config_text)
            
            # Update timestamp
            new_config['last_updated'] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            # Save to memory
            self.devices_config[device_id] = new_config
            
            # Save to file
            if self.save_configurations():
                self.status_label.setText(f"Saved configuration for: {device_id}")
                self.status_label.setStyleSheet("background-color: #c8e6c9; padding: 5px; border-radius: 3px;")
            
        except json.JSONDecodeError as e:
            QMessageBox.critical(self, "JSON Error", f"Invalid JSON format:\\n{str(e)}")
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save configuration:\\n{str(e)}")
    
    def validate_json(self):
        """Validate current JSON in editor"""
        config_text = self.config_editor.toPlainText()
        
        if not config_text.strip():
            QMessageBox.information(self, "Validation", "No content to validate.")
            return
        
        try:
            json.loads(config_text)
            QMessageBox.information(self, "Validation", "JSON is valid! ✓")
            self.status_label.setText("JSON validation passed")
            self.status_label.setStyleSheet("background-color: #c8e6c9; padding: 5px; border-radius: 3px;")
        except json.JSONDecodeError as e:
            QMessageBox.critical(self, "JSON Error", f"Invalid JSON:\\n{str(e)}")
            self.status_label.setText("JSON validation failed")
            self.status_label.setStyleSheet("background-color: #ffcdd2; padding: 5px; border-radius: 3px;")
    
    def export_all_configs(self):
        """Export all configurations to a file"""
        from PyQt6.QtWidgets import QFileDialog
        
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Export Configurations", 
            f"iot_devices_export_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                export_data = {
                    "export_info": {
                        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                        "device_count": len(self.devices_config),
                        "exported_by": "IoT Config Manager"
                    },
                    "devices": self.devices_config
                }
                
                with open(file_path, 'w') as f:
                    json.dump(export_data, f, indent=2)
                
                QMessageBox.information(self, "Success", f"Exported {len(self.devices_config)} devices to:\\n{file_path}")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to export:\\n{str(e)}")
    
    def import_configs(self):
        """Import configurations from a file"""
        from PyQt6.QtWidgets import QFileDialog
        
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Import Configurations", "",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                with open(file_path, 'r') as f:
                    data = json.load(f)
                
                # Check if it's an export file or direct device config
                if 'devices' in data and 'export_info' in data:
                    import_devices = data['devices']
                    info = data['export_info']
                    msg = f"Import {info.get('device_count', 0)} devices exported on {info.get('timestamp', 'unknown')}?"
                else:
                    import_devices = data
                    msg = f"Import {len(import_devices)} devices from file?"
                
                reply = QMessageBox.question(self, "Confirm Import", msg)
                
                if reply == QMessageBox.StandardButton.Yes:
                    conflicts = []
                    imported = 0
                    
                    for device_id, config in import_devices.items():
                        if device_id in self.devices_config:
                            conflicts.append(device_id)
                        else:
                            self.devices_config[device_id] = config
                            imported += 1
                    
                    if conflicts:
                        conflict_msg = f"Imported {imported} devices.\\n\\nConflicts (not imported):\\n" + "\\n".join(conflicts)
                        QMessageBox.warning(self, "Import Complete", conflict_msg)
                    else:
                        QMessageBox.information(self, "Import Complete", f"Successfully imported {imported} devices.")
                    
                    self.refresh_device_list()
                    self.save_configurations()
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to import:\\n{str(e)}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTConfigManager()
    window.show()
    app.exec()
```

## Working with CSV Data

CSV files are perfect for sensor data, logs, and tabular IoT information:

### IoT Data Logger and CSV Manager

```python
import sys
import csv
import json
from datetime import datetime, timedelta
import random
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QLabel, QTableWidget, QTableWidgetItem,
                             QTextEdit, QComboBox, QDateEdit, QSpinBox, QCheckBox,
                             QFileDialog, QMessageBox, QGroupBox, QProgressBar)
from PyQt6.QtCore import QTimer, QDate, Qt

class IoTDataLogger(QMainWindow):
    def __init__(self):
        super().__init__()
        self.sensor_data = []
        self.is_logging = False
        self.initUI()
        self.setup_timer()
    
    def initUI(self):
        self.setWindowTitle("IoT Sensor Data Logger & CSV Manager")
        self.setGeometry(100, 100, 900, 700)
        
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Control Panel
        control_group = QGroupBox("Data Collection Control")
        control_layout = QHBoxLayout()
        
        # Device selection
        control_layout.addWidget(QLabel("Device:"))
        self.device_combo = QComboBox()
        self.device_combo.addItems(["Greenhouse_Sensor", "Weather_Station", "Security_System"])
        control_layout.addWidget(self.device_combo)
        
        # Logging interval
        control_layout.addWidget(QLabel("Interval:"))
        self.interval_spinbox = QSpinBox()
        self.interval_spinbox.setRange(1, 3600)
        self.interval_spinbox.setValue(5)
        self.interval_spinbox.setSuffix(" sec")
        control_layout.addWidget(self.interval_spinbox)
        
        # Auto-save checkbox
        self.auto_save_checkbox = QCheckBox("Auto-save CSV")
        self.auto_save_checkbox.setChecked(True)
        control_layout.addWidget(self.auto_save_checkbox)
        
        # Start/Stop logging
        self.log_button = QPushButton("Start Logging")
        self.log_button.clicked.connect(self.toggle_logging)
        control_layout.addWidget(self.log_button)
        
        # Clear data
        clear_button = QPushButton("Clear Data")
        clear_button.clicked.connect(self.clear_data)
        control_layout.addWidget(clear_button)
        
        control_group.setLayout(control_layout)
        
        # Data Table
        data_group = QGroupBox("Collected Data")
        data_layout = QVBoxLayout()
        
        self.data_table = QTableWidget()
        self.data_table.setColumnCount(6)
        self.data_table.setHorizontalHeaderLabels([
            "Timestamp", "Device", "Temperature (°C)", "Humidity (%)", "Pressure (hPa)", "Light (%)"
        ])
        
        # Auto-resize columns
        header = self.data_table.horizontalHeader()
        header.setStretchLastSection(True)
        
        data_layout.addWidget(self.data_table)
        data_group.setLayout(data_layout)
        
        # File Operations
        file_group = QGroupBox("File Operations")
        file_layout = QHBoxLayout()
        
        save_csv_btn = QPushButton("Save as CSV")
        load_csv_btn = QPushButton("Load CSV")
        export_json_btn = QPushButton("Export JSON")
        generate_report_btn = QPushButton("Generate Report")
        
        save_csv_btn.clicked.connect(self.save_csv)
        load_csv_btn.clicked.connect(self.load_csv)
        export_json_btn.clicked.connect(self.export_json)
        generate_report_btn.clicked.connect(self.generate_report)
        
        file_layout.addWidget(save_csv_btn)
        file_layout.addWidget(load_csv_btn)
        file_layout.addWidget(export_json_btn)
        file_layout.addWidget(generate_report_btn)
        
        file_group.setLayout(file_layout)
        
        # Status and Progress
        status_layout = QHBoxLayout()
        self.status_label = QLabel("Ready to start logging")
        self.progress_bar = QProgressBar()
        self.progress_bar.setVisible(False)
        
        status_layout.addWidget(self.status_label)
        status_layout.addWidget(self.progress_bar)
        
        # Add all to main layout
        main_layout.addWidget(control_group)
        main_layout.addWidget(data_group)
        main_layout.addWidget(file_group)
        main_layout.addLayout(status_layout)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def setup_timer(self):
        """Setup timer for data collection"""
        self.data_timer = QTimer()
        self.data_timer.timeout.connect(self.collect_data)
    
    def toggle_logging(self):
        """Start or stop data logging"""
        if not self.is_logging:
            # Start logging
            interval = self.interval_spinbox.value() * 1000  # Convert to milliseconds
            self.data_timer.start(interval)
            self.is_logging = True
            self.log_button.setText("Stop Logging")
            self.log_button.setStyleSheet("background-color: #f44336; color: white;")
            self.status_label.setText(f"Logging data every {self.interval_spinbox.value()} seconds...")
        else:
            # Stop logging
            self.data_timer.stop()
            self.is_logging = False
            self.log_button.setText("Start Logging")
            self.log_button.setStyleSheet("background-color: #4CAF50; color: white;")
            self.status_label.setText("Logging stopped")
            
            # Auto-save if enabled
            if self.auto_save_checkbox.isChecked() and self.sensor_data:
                self.auto_save_data()
    
    def collect_data(self):
        """Simulate collecting sensor data"""
        device = self.device_combo.currentText()
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        # Simulate sensor readings with some realistic variation
        base_temp = 22.0 if device == "Greenhouse_Sensor" else 18.0
        temperature = round(base_temp + random.uniform(-5, 8), 1)
        
        base_humidity = 60 if device == "Greenhouse_Sensor" else 45
        humidity = max(0, min(100, base_humidity + random.randint(-15, 20)))
        
        pressure = round(1013 + random.uniform(-20, 15), 1)
        light = random.randint(0, 100)
        
        # Add to data list
        data_row = {
            'timestamp': timestamp,
            'device': device,
            'temperature': temperature,
            'humidity': humidity,
            'pressure': pressure,
            'light': light
        }
        
        self.sensor_data.append(data_row)
        
        # Add to table
        row = self.data_table.rowCount()
        self.data_table.insertRow(row)
        
        self.data_table.setItem(row, 0, QTableWidgetItem(timestamp))
        self.data_table.setItem(row, 1, QTableWidgetItem(device))
        self.data_table.setItem(row, 2, QTableWidgetItem(str(temperature)))
        self.data_table.setItem(row, 3, QTableWidgetItem(str(humidity)))
        self.data_table.setItem(row, 4, QTableWidgetItem(str(pressure)))
        self.data_table.setItem(row, 5, QTableWidgetItem(str(light)))
        
        # Scroll to bottom
        self.data_table.scrollToBottom()
        
        # Update status
        self.status_label.setText(f"Collected {len(self.sensor_data)} data points - Last: {timestamp}")
    
    def clear_data(self):
        """Clear all collected data"""
        if self.sensor_data:
            reply = QMessageBox.question(self, "Clear Data", 
                                       f"Are you sure you want to clear {len(self.sensor_data)} data points?")
            
            if reply == QMessageBox.StandardButton.Yes:
                self.sensor_data.clear()
                self.data_table.setRowCount(0)
                self.status_label.setText("Data cleared")
    
    def save_csv(self):
        """Save data as CSV file"""
        if not self.sensor_data:
            QMessageBox.warning(self, "No Data", "No data to save!")
            return
        
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Save CSV File",
            f"sensor_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv",
            "CSV files (*.csv);;All files (*.*)"
        )
        
        if file_path:
            try:
                with open(file_path, 'w', newline='') as csvfile:
                    fieldnames = ['timestamp', 'device', 'temperature', 'humidity', 'pressure', 'light']
                    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                    
                    writer.writeheader()
                    for row in self.sensor_data:
                        writer.writerow(row)
                
                QMessageBox.information(self, "Success", f"Saved {len(self.sensor_data)} records to:\\n{file_path}")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to save CSV:\\n{str(e)}")
    
    def load_csv(self):
        """Load data from CSV file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Load CSV File", "",
            "CSV files (*.csv);;All files (*.*)"
        )
        
        if file_path:
            try:
                new_data = []
                with open(file_path, 'r') as csvfile:
                    reader = csv.DictReader(csvfile)
                    for row in reader:
                        new_data.append(row)
                
                if new_data:
                    # Ask whether to append or replace
                    if self.sensor_data:
                        reply = QMessageBox.question(self, "Load Data", 
                                                   f"Found {len(new_data)} records in file.\\n\\n"
                                                   f"Append to existing {len(self.sensor_data)} records?",
                                                   QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No | QMessageBox.StandardButton.Cancel)
                        
                        if reply == QMessageBox.StandardButton.Cancel:
                            return
                        elif reply == QMessageBox.StandardButton.No:
                            self.sensor_data.clear()
                            self.data_table.setRowCount(0)
                    
                    # Add loaded data
                    self.sensor_data.extend(new_data)
                    self.refresh_table()
                    
                    QMessageBox.information(self, "Success", f"Loaded {len(new_data)} records from CSV")
                else:
                    QMessageBox.warning(self, "Empty File", "No data found in CSV file")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to load CSV:\\n{str(e)}")
    
    def refresh_table(self):
        """Refresh the data table with current data"""
        self.data_table.setRowCount(0)
        
        for i, data_row in enumerate(self.sensor_data):
            self.data_table.insertRow(i)
            self.data_table.setItem(i, 0, QTableWidgetItem(data_row['timestamp']))
            self.data_table.setItem(i, 1, QTableWidgetItem(data_row['device']))
            self.data_table.setItem(i, 2, QTableWidgetItem(str(data_row['temperature'])))
            self.data_table.setItem(i, 3, QTableWidgetItem(str(data_row['humidity'])))
            self.data_table.setItem(i, 4, QTableWidgetItem(str(data_row['pressure'])))
            self.data_table.setItem(i, 5, QTableWidgetItem(str(data_row['light'])))
    
    def export_json(self):
        """Export data as JSON file"""
        if not self.sensor_data:
            QMessageBox.warning(self, "No Data", "No data to export!")
            return
        
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Export JSON File",
            f"sensor_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                export_data = {
                    "export_info": {
                        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                        "record_count": len(self.sensor_data),
                        "exported_by": "IoT Data Logger"
                    },
                    "data": self.sensor_data
                }
                
                with open(file_path, 'w') as jsonfile:
                    json.dump(export_data, jsonfile, indent=2)
                
                QMessageBox.information(self, "Success", f"Exported {len(self.sensor_data)} records to JSON")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to export JSON:\\n{str(e)}")
    
    def generate_report(self):
        """Generate a summary report"""
        if not self.sensor_data:
            QMessageBox.warning(self, "No Data", "No data for report generation!")
            return
        
        try:
            # Calculate statistics
            temperatures = [float(row['temperature']) for row in self.sensor_data]
            humidity_values = [float(row['humidity']) for row in self.sensor_data]
            pressure_values = [float(row['pressure']) for row in self.sensor_data]
            
            report = f"""IoT SENSOR DATA REPORT
Generated: {datetime.now().strftime("%Y-%m-%d %H:%M:%S")}

SUMMARY:
- Total Records: {len(self.sensor_data)}
- Time Period: {self.sensor_data[0]['timestamp']} to {self.sensor_data[-1]['timestamp']}
- Devices: {', '.join(set(row['device'] for row in self.sensor_data))}

TEMPERATURE STATISTICS:
- Minimum: {min(temperatures):.1f}°C
- Maximum: {max(temperatures):.1f}°C
- Average: {sum(temperatures)/len(temperatures):.1f}°C

HUMIDITY STATISTICS:
- Minimum: {min(humidity_values):.1f}%
- Maximum: {max(humidity_values):.1f}%
- Average: {sum(humidity_values)/len(humidity_values):.1f}%

PRESSURE STATISTICS:
- Minimum: {min(pressure_values):.1f} hPa
- Maximum: {max(pressure_values):.1f} hPa
- Average: {sum(pressure_values)/len(pressure_values):.1f} hPa

DEVICE BREAKDOWN:"""
            
            # Device breakdown
            device_counts = {}
            for row in self.sensor_data:
                device = row['device']
                device_counts[device] = device_counts.get(device, 0) + 1
            
            for device, count in device_counts.items():
                percentage = (count / len(self.sensor_data)) * 100
                report += f"\\n- {device}: {count} records ({percentage:.1f}%)"
            
            # Show report in dialog
            report_dialog = QMessageBox()
            report_dialog.setWindowTitle("Data Report")
            report_dialog.setText("Data analysis complete!")
            report_dialog.setDetailedText(report)
            report_dialog.exec()
            
            # Option to save report
            reply = QMessageBox.question(self, "Save Report", "Would you like to save this report to a file?")
            if reply == QMessageBox.StandardButton.Yes:
                file_path, _ = QFileDialog.getSaveFileName(
                    self, "Save Report",
                    f"sensor_report_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt",
                    "Text files (*.txt);;All files (*.*)"
                )
                
                if file_path:
                    with open(file_path, 'w') as f:
                        f.write(report)
                    QMessageBox.information(self, "Success", f"Report saved to:\\n{file_path}")
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to generate report:\\n{str(e)}")
    
    def auto_save_data(self):
        """Auto-save data when logging stops"""
        filename = f"auto_save_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
        
        try:
            with open(filename, 'w', newline='') as csvfile:
                fieldnames = ['timestamp', 'device', 'temperature', 'humidity', 'pressure', 'light']
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                
                writer.writeheader()
                for row in self.sensor_data:
                    writer.writerow(row)
            
            self.status_label.setText(f"Auto-saved {len(self.sensor_data)} records to {filename}")
            
        except Exception as e:
            self.status_label.setText(f"Auto-save failed: {str(e)}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTDataLogger()
    window.show()
    app.exec()
```

## Application Settings Management

Managing user preferences and application settings:

### Settings Manager

```python
import sys
import json
import os
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QLabel, QLineEdit, QSpinBox,
                             QCheckBox, QComboBox, QGroupBox, QFormLayout, QMessageBox)
from PyQt6.QtCore import QSettings

class IoTSettingsManager(QMainWindow):
    def __init__(self):
        super().__init__()
        # Use QSettings for cross-platform settings storage
        self.settings = QSettings("IoTCompany", "IoTControlPanel")
        self.initUI()
        self.load_settings()
    
    def initUI(self):
        self.setWindowTitle("IoT Application Settings")
        self.setGeometry(250, 250, 500, 600)
        
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Application Settings
        app_group = QGroupBox("Application Settings")
        app_layout = QFormLayout()
        
        self.theme_combo = QComboBox()
        self.theme_combo.addItems(["Light", "Dark", "Auto"])
        
        self.language_combo = QComboBox()
        self.language_combo.addItems(["English", "Spanish", "French", "German"])
        
        self.auto_save_checkbox = QCheckBox("Auto-save data")
        self.auto_connect_checkbox = QCheckBox("Auto-connect on startup")
        
        self.save_interval = QSpinBox()
        self.save_interval.setRange(1, 3600)
        self.save_interval.setValue(300)
        self.save_interval.setSuffix(" seconds")
        
        app_layout.addRow("Theme:", self.theme_combo)
        app_layout.addRow("Language:", self.language_combo)
        app_layout.addRow("", self.auto_save_checkbox)
        app_layout.addRow("", self.auto_connect_checkbox)
        app_layout.addRow("Save Interval:", self.save_interval)
        
        app_group.setLayout(app_layout)
        
        # Network Settings
        network_group = QGroupBox("Default Network Settings")
        network_layout = QFormLayout()
        
        self.default_ip = QLineEdit()
        self.default_port = QSpinBox()
        self.default_port.setRange(1, 65535)
        self.default_port.setValue(8080)
        
        self.connection_timeout = QSpinBox()
        self.connection_timeout.setRange(1, 60)
        self.connection_timeout.setValue(10)
        self.connection_timeout.setSuffix(" seconds")
        
        self.retry_attempts = QSpinBox()
        self.retry_attempts.setRange(1, 10)
        self.retry_attempts.setValue(3)
        
        network_layout.addRow("Default IP:", self.default_ip)
        network_layout.addRow("Default Port:", self.default_port)
        network_layout.addRow("Connection Timeout:", self.connection_timeout)
        network_layout.addRow("Retry Attempts:", self.retry_attempts)
        
        network_group.setLayout(network_layout)
        
        # Data Settings
        data_group = QGroupBox("Data Management")
        data_layout = QFormLayout()
        
        self.max_records = QSpinBox()
        self.max_records.setRange(100, 100000)
        self.max_records.setValue(10000)
        
        self.data_retention_days = QSpinBox()
        self.data_retention_days.setRange(1, 365)
        self.data_retention_days.setValue(30)
        self.data_retention_days.setSuffix(" days")
        
        self.export_format = QComboBox()
        self.export_format.addItems(["CSV", "JSON", "XML"])
        
        self.compress_exports = QCheckBox("Compress exported files")
        
        data_layout.addRow("Max Records:", self.max_records)
        data_layout.addRow("Data Retention:", self.data_retention_days)
        data_layout.addRow("Export Format:", self.export_format)
        data_layout.addRow("", self.compress_exports)
        
        data_group.setLayout(data_layout)
        
        # Alert Settings
        alert_group = QGroupBox("Alert Settings")
        alert_layout = QFormLayout()
        
        self.enable_alerts = QCheckBox("Enable system alerts")
        self.enable_alerts.setChecked(True)
        
        self.alert_email = QLineEdit()
        self.alert_email.setPlaceholderText("admin@example.com")
        
        self.email_server = QLineEdit()
        self.email_server.setPlaceholderText("smtp.gmail.com")
        
        self.email_port = QSpinBox()
        self.email_port.setRange(1, 65535)
        self.email_port.setValue(587)
        
        alert_layout.addRow("", self.enable_alerts)
        alert_layout.addRow("Alert Email:", self.alert_email)
        alert_layout.addRow("SMTP Server:", self.email_server)
        alert_layout.addRow("SMTP Port:", self.email_port)
        
        alert_group.setLayout(alert_layout)
        
        # Buttons
        button_layout = QHBoxLayout()
        
        save_btn = QPushButton("Save Settings")
        load_btn = QPushButton("Reload Settings")
        reset_btn = QPushButton("Reset to Defaults")
        export_btn = QPushButton("Export Settings")
        import_btn = QPushButton("Import Settings")
        
        save_btn.clicked.connect(self.save_settings)
        load_btn.clicked.connect(self.load_settings)
        reset_btn.clicked.connect(self.reset_to_defaults)
        export_btn.clicked.connect(self.export_settings)
        import_btn.clicked.connect(self.import_settings)
        
        button_layout.addWidget(save_btn)
        button_layout.addWidget(load_btn)
        button_layout.addWidget(reset_btn)
        button_layout.addWidget(export_btn)
        button_layout.addWidget(import_btn)
        
        # Add to main layout
        main_layout.addWidget(app_group)
        main_layout.addWidget(network_group)
        main_layout.addWidget(data_group)
        main_layout.addWidget(alert_group)
        main_layout.addLayout(button_layout)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def save_settings(self):
        """Save all settings"""
        try:
            # Application settings
            self.settings.setValue("theme", self.theme_combo.currentText())
            self.settings.setValue("language", self.language_combo.currentText())
            self.settings.setValue("auto_save", self.auto_save_checkbox.isChecked())
            self.settings.setValue("auto_connect", self.auto_connect_checkbox.isChecked())
            self.settings.setValue("save_interval", self.save_interval.value())
            
            # Network settings
            self.settings.setValue("default_ip", self.default_ip.text())
            self.settings.setValue("default_port", self.default_port.value())
            self.settings.setValue("connection_timeout", self.connection_timeout.value())
            self.settings.setValue("retry_attempts", self.retry_attempts.value())
            
            # Data settings
            self.settings.setValue("max_records", self.max_records.value())
            self.settings.setValue("data_retention_days", self.data_retention_days.value())
            self.settings.setValue("export_format", self.export_format.currentText())
            self.settings.setValue("compress_exports", self.compress_exports.isChecked())
            
            # Alert settings
            self.settings.setValue("enable_alerts", self.enable_alerts.isChecked())
            self.settings.setValue("alert_email", self.alert_email.text())
            self.settings.setValue("email_server", self.email_server.text())
            self.settings.setValue("email_port", self.email_port.value())
            
            QMessageBox.information(self, "Success", "Settings saved successfully!")
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save settings:\\n{str(e)}")
    
    def load_settings(self):
        """Load saved settings"""
        try:
            # Application settings
            self.theme_combo.setCurrentText(self.settings.value("theme", "Light"))
            self.language_combo.setCurrentText(self.settings.value("language", "English"))
            self.auto_save_checkbox.setChecked(self.settings.value("auto_save", True, bool))
            self.auto_connect_checkbox.setChecked(self.settings.value("auto_connect", False, bool))
            self.save_interval.setValue(self.settings.value("save_interval", 300, int))
            
            # Network settings
            self.default_ip.setText(self.settings.value("default_ip", "192.168.1.100"))
            self.default_port.setValue(self.settings.value("default_port", 8080, int))
            self.connection_timeout.setValue(self.settings.value("connection_timeout", 10, int))
            self.retry_attempts.setValue(self.settings.value("retry_attempts", 3, int))
            
            # Data settings
            self.max_records.setValue(self.settings.value("max_records", 10000, int))
            self.data_retention_days.setValue(self.settings.value("data_retention_days", 30, int))
            self.export_format.setCurrentText(self.settings.value("export_format", "CSV"))
            self.compress_exports.setChecked(self.settings.value("compress_exports", False, bool))
            
            # Alert settings
            self.enable_alerts.setChecked(self.settings.value("enable_alerts", True, bool))
            self.alert_email.setText(self.settings.value("alert_email", ""))
            self.email_server.setText(self.settings.value("email_server", "smtp.gmail.com"))
            self.email_port.setValue(self.settings.value("email_port", 587, int))
            
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to load settings:\\n{str(e)}")
    
    def reset_to_defaults(self):
        """Reset all settings to defaults"""
        reply = QMessageBox.question(self, "Reset Settings", 
                                   "Are you sure you want to reset all settings to defaults?")
        
        if reply == QMessageBox.StandardButton.Yes:
            self.settings.clear()
            self.load_settings()
            QMessageBox.information(self, "Reset", "Settings reset to defaults.")
    
    def export_settings(self):
        """Export settings to JSON file"""
        from PyQt6.QtWidgets import QFileDialog
        
        file_path, _ = QFileDialog.getSaveFileName(
            self, "Export Settings",
            f"iot_settings_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                settings_dict = {}
                
                # Get all settings
                for key in self.settings.allKeys():
                    settings_dict[key] = self.settings.value(key)
                
                export_data = {
                    "export_info": {
                        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                        "application": "IoT Control Panel",
                        "version": "1.0"
                    },
                    "settings": settings_dict
                }
                
                with open(file_path, 'w') as f:
                    json.dump(export_data, f, indent=2)
                
                QMessageBox.information(self, "Success", f"Settings exported to:\\n{file_path}")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to export settings:\\n{str(e)}")
    
    def import_settings(self):
        """Import settings from JSON file"""
        from PyQt6.QtWidgets import QFileDialog
        
        file_path, _ = QFileDialog.getOpenFileName(
            self, "Import Settings", "",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                with open(file_path, 'r') as f:
                    data = json.load(f)
                
                if 'settings' in data:
                    settings_dict = data['settings']
                else:
                    settings_dict = data
                
                reply = QMessageBox.question(self, "Import Settings", 
                                           f"Import {len(settings_dict)} settings from file?\\n\\n"
                                           "This will overwrite current settings.")
                
                if reply == QMessageBox.StandardButton.Yes:
                    # Clear existing settings
                    self.settings.clear()
                    
                    # Import new settings
                    for key, value in settings_dict.items():
                        self.settings.setValue(key, value)
                    
                    # Reload UI
                    self.load_settings()
                    
                    QMessageBox.information(self, "Success", "Settings imported successfully!")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to import settings:\\n{str(e)}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTSettingsManager()
    window.show()
    app.exec()
```

## Best Practices for Data Handling

1. **Always validate data** before saving
2. **Use appropriate file formats** (JSON for config, CSV for tabular data)
3. **Handle file errors gracefully** with try-catch blocks
4. **Provide user feedback** during long operations
5. **Backup important data** before modifications
6. **Use QSettings** for application preferences
7. **Implement auto-save** for critical data
8. **Show progress** for large file operations

## Practice Exercise

Create a complete IoT device management system with:

1. **Device Registry** (JSON storage)
   - Add/remove/edit devices
   - Import/export device configurations
   - Validation and error handling

2. **Data Logger** (CSV storage)
   - Real-time sensor simulation
   - Data filtering and analysis
   - Report generation

3. **Settings Manager**
   - User preferences
   - Connection settings
   - Data retention policies

4. **Backup System**
   - Automatic backups
   - Manual backup/restore
   - Data integrity checks

## What's Next?

In the next tutorial, we'll start building practical IoT projects:
- Basic sensor data display project
- Real-time monitoring interface
- Hardware communication basics
- Arduino/Raspberry Pi integration

Ready to build real IoT applications? Let's move to Tutorial 8!