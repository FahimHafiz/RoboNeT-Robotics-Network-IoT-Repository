<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# PyQt6 Forms, Dialogs, and User Input

## Introduction

In IoT applications, you often need to collect configuration data, display settings dialogs, show error messages, or get user input. This tutorial covers creating forms, handling different types of dialogs, validating user input, and managing application settings.

## Input Validation

Before we dive into dialogs, let's learn how to validate user input properly:

### Text Input Validation

```python
import sys
import re
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QLabel, QLineEdit, QPushButton, QMessageBox)
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QValidator, QIntValidator, QDoubleValidator, QRegularExpressionValidator

class InputValidationDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("Input Validation for IoT Configuration")
        self.setGeometry(200, 200, 400, 300)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Device Name (alphanumeric only)
        device_layout = QHBoxLayout()
        device_layout.addWidget(QLabel("Device Name:"))
        self.device_input = QLineEdit()
        self.device_input.setPlaceholderText("Arduino_01")
        # Regex validator: letters, numbers, underscore only
        device_validator = QRegularExpressionValidator(r"^[a-zA-Z0-9_]+$")
        self.device_input.setValidator(device_validator)
        device_layout.addWidget(self.device_input)
        
        # IP Address validation
        ip_layout = QHBoxLayout()
        ip_layout.addWidget(QLabel("IP Address:"))
        self.ip_input = QLineEdit()
        self.ip_input.setPlaceholderText("192.168.1.100")
        # IP address pattern
        ip_pattern = r"^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
        ip_validator = QRegularExpressionValidator(ip_pattern)
        self.ip_input.setValidator(ip_validator)
        ip_layout.addWidget(self.ip_input)
        
        # Port number (1-65535)
        port_layout = QHBoxLayout()
        port_layout.addWidget(QLabel("Port:"))
        self.port_input = QLineEdit()
        self.port_input.setPlaceholderText("8080")
        port_validator = QIntValidator(1, 65535)
        self.port_input.setValidator(port_validator)
        port_layout.addWidget(self.port_input)
        
        # Temperature threshold (decimal)
        temp_layout = QHBoxLayout()
        temp_layout.addWidget(QLabel("Max Temperature:"))
        self.temp_input = QLineEdit()
        self.temp_input.setPlaceholderText("25.5")
        temp_validator = QDoubleValidator(-50.0, 150.0, 2)  # -50 to 150, 2 decimals
        self.temp_input.setValidator(temp_validator)
        temp_layout.addWidget(self.temp_input)
        temp_layout.addWidget(QLabel("°C"))
        
        # Validation button
        self.validate_button = QPushButton("Validate All")\n        self.validate_button.clicked.connect(self.validate_all_inputs)
        
        # Status label
        self.status_label = QLabel("Enter configuration data...")\n        
        # Add to layout
        layout.addLayout(device_layout)
        layout.addLayout(ip_layout)
        layout.addLayout(port_layout)
        layout.addLayout(temp_layout)
        layout.addWidget(self.validate_button)
        layout.addWidget(self.status_label)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)
    
    def validate_all_inputs(self):
        """Validate all input fields"""
        errors = []
        
        # Device name check
        device_name = self.device_input.text().strip()
        if not device_name:
            errors.append("Device name is required")
        elif len(device_name) < 3:
            errors.append("Device name must be at least 3 characters")
        
        # IP address check
        ip_address = self.ip_input.text().strip()
        if not ip_address:
            errors.append("IP address is required")
        elif not self.is_valid_ip(ip_address):
            errors.append("Invalid IP address format")
        
        # Port check
        port_text = self.port_input.text().strip()
        if not port_text:
            errors.append("Port number is required")
        else:
            try:
                port = int(port_text)
                if not (1 <= port <= 65535):
                    errors.append("Port must be between 1 and 65535")
            except ValueError:
                errors.append("Port must be a number")
        
        # Temperature check
        temp_text = self.temp_input.text().strip()
        if not temp_text:
            errors.append("Temperature threshold is required")
        else:
            try:
                temp = float(temp_text)
                if not (-50 <= temp <= 150):
                    errors.append("Temperature must be between -50 and 150°C")
            except ValueError:
                errors.append("Temperature must be a number")
        
        # Display results
        if errors:
            error_msg = "\\n".join(errors)
            self.status_label.setText(f"Validation failed:\\n{error_msg}")
            self.status_label.setStyleSheet("color: red; background-color: #ffebee; padding: 10px; border-radius: 5px;")
            
            # Show error dialog
            QMessageBox.warning(self, "Validation Error", error_msg)
        else:
            self.status_label.setText("All inputs are valid!")
            self.status_label.setStyleSheet("color: green; background-color: #e8f5e8; padding: 10px; border-radius: 5px;")
            
            # Show success dialog
            QMessageBox.information(self, "Success", "Configuration validated successfully!")
    
    def is_valid_ip(self, ip):
        """Additional IP validation"""
        try:
            parts = ip.split('.')
            if len(parts) != 4:
                return False
            for part in parts:
                if not (0 <= int(part) <= 255):
                    return False
            return True
        except:
            return False

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = InputValidationDemo()
    window.show()
    app.exec()
```

## Message Boxes and Notifications

Message boxes are essential for showing alerts, confirmations, and information to users:

### Basic Message Boxes

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QWidget, 
                             QPushButton, QMessageBox)

class MessageBoxDemo(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Message Box Examples")
        self.setGeometry(250, 250, 300, 200)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Different types of message boxes
        info_btn = QPushButton("Sensor Connected (Info)")
        warning_btn = QPushButton("High Temperature (Warning)")
        error_btn = QPushButton("Connection Failed (Error)")
        question_btn = QPushButton("Reset Device? (Question)")
        custom_btn = QPushButton("Custom IoT Message")
        
        # Connect buttons
        info_btn.clicked.connect(self.show_info)
        warning_btn.clicked.connect(self.show_warning)
        error_btn.clicked.connect(self.show_error)
        question_btn.clicked.connect(self.show_question)
        custom_btn.clicked.connect(self.show_custom)
        
        layout.addWidget(info_btn)
        layout.addWidget(warning_btn)
        layout.addWidget(error_btn)
        layout.addWidget(question_btn)
        layout.addWidget(custom_btn)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)
    
    def show_info(self):
        """Information message"""
        QMessageBox.information(self, "Sensor Status", 
                               "DHT22 sensor connected successfully!\\n"
                               "Temperature: 24.5°C\\nHumidity: 55%")
    
    def show_warning(self):
        """Warning message"""
        QMessageBox.warning(self, "Temperature Alert", 
                           "WARNING: Temperature has exceeded 30°C!\\n"
                           "Current reading: 32.1°C\\n\\n"
                           "Consider activating cooling system.")
    
    def show_error(self):
        """Error message"""
        QMessageBox.critical(self, "Connection Error", 
                            "Failed to connect to IoT device!\\n\\n"
                            "Error details:\\n"
                            "- Device not responding\\n"
                            "- Check network connection\\n"
                            "- Verify device power")
    
    def show_question(self):
        """Question dialog with Yes/No"""
        reply = QMessageBox.question(self, "Device Reset", 
                                   "Are you sure you want to reset the device?\\n\\n"
                                   "This will:\\n"
                                   "- Clear all sensor data\\n"
                                   "- Reset configuration to defaults\\n"
                                   "- Restart the device",
                                   QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                                   QMessageBox.StandardButton.No)
        
        if reply == QMessageBox.StandardButton.Yes:
            QMessageBox.information(self, "Reset", "Device reset initiated...")
        else:
            QMessageBox.information(self, "Cancelled", "Reset cancelled.")
    
    def show_custom(self):
        """Custom message box with multiple buttons"""
        msg = QMessageBox()
        msg.setWindowTitle("IoT Device Management")
        msg.setText("Device maintenance required!")
        msg.setInformativeText("The device has been running for 30 days. What would you like to do?")
        msg.setDetailedText("Maintenance recommendations:\\n"
                           "- Clean sensor components\\n"
                           "- Check connections\\n"
                           "- Update firmware\\n"
                           "- Calibrate sensors")
        
        # Custom buttons
        restart_btn = msg.addButton("Restart Device", QMessageBox.ButtonRole.ActionRole)
        maintenance_btn = msg.addButton("Schedule Maintenance", QMessageBox.ButtonRole.ActionRole)
        ignore_btn = msg.addButton("Ignore", QMessageBox.ButtonRole.RejectRole)
        
        msg.exec()
        
        if msg.clickedButton() == restart_btn:
            QMessageBox.information(self, "Action", "Device restart scheduled.")
        elif msg.clickedButton() == maintenance_btn:
            QMessageBox.information(self, "Action", "Maintenance reminder set.")
        else:
            QMessageBox.information(self, "Action", "Maintenance reminder ignored.")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MessageBoxDemo()
    window.show()
    app.exec()
```

## Custom Dialogs

For complex input or configuration, create custom dialog windows:

### IoT Device Configuration Dialog

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QDialog, QVBoxLayout, 
                             QHBoxLayout, QFormLayout, QWidget, QPushButton, 
                             QLabel, QLineEdit, QComboBox, QSpinBox, QCheckBox,
                             QDialogButtonBox, QGroupBox, QTextEdit)
from PyQt6.QtCore import Qt

class DeviceConfigDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("IoT Device Configuration")
        self.setModal(True)  # Make dialog modal
        self.resize(400, 500)
        
        # Store configuration data
        self.config_data = {}
        
        self.initUI()
    
    def initUI(self):
        layout = QVBoxLayout()
        
        # Device Information Group
        device_group = QGroupBox("Device Information")
        device_form = QFormLayout()
        
        self.device_name = QLineEdit("Arduino_Sensor_01")
        self.device_type = QComboBox()
        self.device_type.addItems(["Arduino Uno", "Arduino Nano", "ESP32", "Raspberry Pi"])
        self.firmware_version = QLineEdit("1.2.3")
        
        device_form.addRow("Device Name:", self.device_name)
        device_form.addRow("Device Type:", self.device_type)
        device_form.addRow("Firmware Version:", self.firmware_version)
        device_group.setLayout(device_form)
        
        # Network Configuration Group
        network_group = QGroupBox("Network Configuration")
        network_form = QFormLayout()
        
        self.ip_address = QLineEdit("192.168.1.100")
        self.port = QSpinBox()
        self.port.setRange(1, 65535)
        self.port.setValue(8080)
        self.use_dhcp = QCheckBox("Use DHCP")
        self.wifi_ssid = QLineEdit("IoT_Network")
        self.wifi_password = QLineEdit()
        self.wifi_password.setEchoMode(QLineEdit.EchoMode.Password)
        
        network_form.addRow("IP Address:", self.ip_address)
        network_form.addRow("Port:", self.port)
        network_form.addRow("", self.use_dhcp)
        network_form.addRow("WiFi SSID:", self.wifi_ssid)
        network_form.addRow("WiFi Password:", self.wifi_password)
        network_group.setLayout(network_form)
        
        # Sensor Configuration Group
        sensor_group = QGroupBox("Sensor Configuration")
        sensor_form = QFormLayout()
        
        self.sensor_type = QComboBox()
        self.sensor_type.addItems(["DHT22", "BME280", "DS18B20", "BMP180"])
        self.reading_interval = QSpinBox()
        self.reading_interval.setRange(1, 3600)
        self.reading_interval.setValue(60)
        self.reading_interval.setSuffix(" seconds")
        self.enable_logging = QCheckBox("Enable Data Logging")
        self.enable_logging.setChecked(True)
        
        sensor_form.addRow("Sensor Type:", self.sensor_type)
        sensor_form.addRow("Reading Interval:", self.reading_interval)
        sensor_form.addRow("", self.enable_logging)
        sensor_group.setLayout(sensor_form)
        
        # Alert Configuration Group
        alert_group = QGroupBox("Alert Configuration")
        alert_form = QFormLayout()
        
        self.temp_threshold = QSpinBox()
        self.temp_threshold.setRange(-50, 150)
        self.temp_threshold.setValue(30)
        self.temp_threshold.setSuffix("°C")
        
        self.humidity_threshold = QSpinBox()
        self.humidity_threshold.setRange(0, 100)
        self.humidity_threshold.setValue(80)
        self.humidity_threshold.setSuffix("%")
        
        self.enable_email_alerts = QCheckBox("Enable Email Alerts")
        self.alert_email = QLineEdit("admin@example.com")
        
        alert_form.addRow("Temperature Threshold:", self.temp_threshold)
        alert_form.addRow("Humidity Threshold:", self.humidity_threshold)
        alert_form.addRow("", self.enable_email_alerts)
        alert_form.addRow("Alert Email:", self.alert_email)
        alert_group.setLayout(alert_form)
        
        # Notes
        notes_group = QGroupBox("Additional Notes")
        notes_layout = QVBoxLayout()
        self.notes_text = QTextEdit()
        self.notes_text.setPlaceholderText("Enter any additional configuration notes...")
        self.notes_text.setMaximumHeight(80)
        notes_layout.addWidget(self.notes_text)
        notes_group.setLayout(notes_layout)
        
        # Dialog buttons
        button_box = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok | 
            QDialogButtonBox.StandardButton.Cancel |
            QDialogButtonBox.StandardButton.RestoreDefaults
        )
        
        button_box.accepted.connect(self.accept_config)
        button_box.rejected.connect(self.reject)
        button_box.button(QDialogButtonBox.StandardButton.RestoreDefaults).clicked.connect(self.restore_defaults)
        
        # Add all to main layout
        layout.addWidget(device_group)
        layout.addWidget(network_group)
        layout.addWidget(sensor_group)
        layout.addWidget(alert_group)
        layout.addWidget(notes_group)
        layout.addWidget(button_box)
        
        self.setLayout(layout)
        
        # Connect DHCP checkbox to enable/disable IP field
        self.use_dhcp.stateChanged.connect(self.dhcp_changed)
    
    def dhcp_changed(self, state):
        """Handle DHCP checkbox change"""
        if state == Qt.CheckState.Checked.value:
            self.ip_address.setEnabled(False)
            self.ip_address.setText("Auto (DHCP)")
        else:
            self.ip_address.setEnabled(True)
            self.ip_address.setText("192.168.1.100")
    
    def accept_config(self):
        """Validate and accept configuration"""
        # Validate required fields
        if not self.device_name.text().strip():
            from PyQt6.QtWidgets import QMessageBox
            QMessageBox.warning(self, "Validation Error", "Device name is required!")
            return
        
        if not self.wifi_ssid.text().strip():
            from PyQt6.QtWidgets import QMessageBox
            QMessageBox.warning(self, "Validation Error", "WiFi SSID is required!")
            return
        
        # Collect all configuration data
        self.config_data = {
            'device_name': self.device_name.text(),
            'device_type': self.device_type.currentText(),
            'firmware_version': self.firmware_version.text(),
            'ip_address': self.ip_address.text(),
            'port': self.port.value(),
            'use_dhcp': self.use_dhcp.isChecked(),
            'wifi_ssid': self.wifi_ssid.text(),
            'wifi_password': self.wifi_password.text(),
            'sensor_type': self.sensor_type.currentText(),
            'reading_interval': self.reading_interval.value(),
            'enable_logging': self.enable_logging.isChecked(),
            'temp_threshold': self.temp_threshold.value(),
            'humidity_threshold': self.humidity_threshold.value(),
            'enable_email_alerts': self.enable_email_alerts.isChecked(),
            'alert_email': self.alert_email.text(),
            'notes': self.notes_text.toPlainText()
        }
        
        self.accept()  # Close dialog with OK result
    
    def restore_defaults(self):
        """Restore default values"""
        self.device_name.setText("Arduino_Sensor_01")
        self.device_type.setCurrentText("Arduino Uno")
        self.firmware_version.setText("1.0.0")
        self.ip_address.setText("192.168.1.100")
        self.port.setValue(8080)
        self.use_dhcp.setChecked(False)
        self.wifi_ssid.setText("IoT_Network")
        self.wifi_password.setText("")
        self.sensor_type.setCurrentText("DHT22")
        self.reading_interval.setValue(60)
        self.enable_logging.setChecked(True)
        self.temp_threshold.setValue(30)
        self.humidity_threshold.setValue(80)
        self.enable_email_alerts.setChecked(False)
        self.alert_email.setText("admin@example.com")
        self.notes_text.setText("")

class MainApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Manager")
        self.setGeometry(300, 300, 300, 150)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # Current configuration display
        self.config_label = QLabel("No device configured")
        self.config_label.setStyleSheet("padding: 10px; border: 1px solid #ccc; background-color: #f5f5f5;")
        
        # Configure button
        configure_btn = QPushButton("Configure IoT Device")
        configure_btn.clicked.connect(self.open_config_dialog)
        
        layout.addWidget(self.config_label)
        layout.addWidget(configure_btn)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)
    
    def open_config_dialog(self):
        """Open the configuration dialog"""
        dialog = DeviceConfigDialog(self)
        
        if dialog.exec() == QDialog.DialogCode.Accepted:
            # Configuration was accepted
            config = dialog.config_data
            
            # Display summary of configuration
            summary = f"Device: {config['device_name']} ({config['device_type']})\\n"
            summary += f"Network: {config['ip_address']}:{config['port']}\\n"
            summary += f"Sensor: {config['sensor_type']} (every {config['reading_interval']}s)"
            
            self.config_label.setText(summary)
            
            # You could save the configuration to file here
            print("Configuration saved:", config)
        else:
            print("Configuration cancelled")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    app.exec()
```

## File Dialogs

For IoT applications, you often need to save/load configuration files, export sensor data, or import settings:

### File Operations Example

```python
import sys
import json
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QWidget, QPushButton, QTextEdit, QLabel, QFileDialog, QMessageBox)

class IoTFileManager(QMainWindow):
    def __init__(self):
        super().__init__()
        self.current_file = None
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Configuration File Manager")
        self.setGeometry(200, 200, 600, 400)
        
        central_widget = QWidget()
        layout = QVBoxLayout()
        
        # File info
        self.file_info = QLabel("No file loaded")
        self.file_info.setStyleSheet("background-color: #e3f2fd; padding: 8px; border-radius: 4px;")
        
        # Text area for configuration
        self.config_text = QTextEdit()
        self.config_text.setPlaceholderText("Configuration data will appear here...")
        
        # Buttons
        button_layout = QHBoxLayout()
        
        new_btn = QPushButton("New Config")
        open_btn = QPushButton("Open Config")
        save_btn = QPushButton("Save Config")
        save_as_btn = QPushButton("Save As...")
        export_btn = QPushButton("Export Data")
        
        new_btn.clicked.connect(self.new_config)
        open_btn.clicked.connect(self.open_config)
        save_btn.clicked.connect(self.save_config)
        save_as_btn.clicked.connect(self.save_as_config)
        export_btn.clicked.connect(self.export_data)
        
        button_layout.addWidget(new_btn)
        button_layout.addWidget(open_btn)
        button_layout.addWidget(save_btn)
        button_layout.addWidget(save_as_btn)
        button_layout.addWidget(export_btn)
        
        layout.addWidget(self.file_info)
        layout.addWidget(self.config_text)
        layout.addLayout(button_layout)
        
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)
    
    def new_config(self):
        """Create new configuration"""
        template = {
            "device_info": {
                "name": "New_IoT_Device",
                "type": "Arduino",
                "version": "1.0.0"
            },
            "network": {
                "ip": "192.168.1.100",
                "port": 8080,
                "wifi_ssid": "IoT_Network"
            },
            "sensors": [
                {
                    "type": "DHT22",
                    "pin": 2,
                    "interval": 60
                }
            ],
            "thresholds": {
                "temperature_max": 30,
                "humidity_max": 80
            }
        }
        
        self.config_text.setText(json.dumps(template, indent=2))
        self.current_file = None
        self.file_info.setText("New configuration (unsaved)")
    
    def open_config(self):
        """Open configuration file"""
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Open IoT Configuration",
            "",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                with open(file_path, 'r') as file:
                    content = file.read()
                    # Validate JSON
                    json.loads(content)  # This will raise exception if invalid
                    
                    self.config_text.setText(content)
                    self.current_file = file_path
                    self.file_info.setText(f"Loaded: {file_path}")
                    
            except json.JSONDecodeError as e:
                QMessageBox.critical(self, "Error", f"Invalid JSON file:\\n{str(e)}")
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to open file:\\n{str(e)}")
    
    def save_config(self):
        """Save current configuration"""
        if self.current_file:
            self.save_to_file(self.current_file)
        else:
            self.save_as_config()
    
    def save_as_config(self):
        """Save configuration as new file"""
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save IoT Configuration",
            "iot_config.json",
            "JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            self.save_to_file(file_path)
    
    def save_to_file(self, file_path):
        """Save content to specified file"""
        try:
            content = self.config_text.toPlainText()
            # Validate JSON before saving
            json.loads(content)
            
            with open(file_path, 'w') as file:
                file.write(content)
            
            self.current_file = file_path
            self.file_info.setText(f"Saved: {file_path}")
            QMessageBox.information(self, "Success", "Configuration saved successfully!")
            
        except json.JSONDecodeError as e:
            QMessageBox.critical(self, "Error", f"Invalid JSON format:\\n{str(e)}")
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save file:\\n{str(e)}")
    
    def export_data(self):
        """Export sensor data (simulation)"""
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Export Sensor Data",
            "sensor_data.csv",
            "CSV files (*.csv);;JSON files (*.json);;All files (*.*)"
        )
        
        if file_path:
            try:
                # Simulate sensor data export
                if file_path.endswith('.csv'):
                    data = "timestamp,temperature,humidity,pressure\\n"
                    data += "2023-01-01 12:00:00,23.5,65,1013\\n"
                    data += "2023-01-01 12:01:00,23.7,64,1014\\n"
                    data += "2023-01-01 12:02:00,23.6,66,1012\\n"
                else:
                    data = json.dumps({
                        "export_time": "2023-01-01 12:00:00",
                        "device": "Arduino_01",
                        "data": [
                            {"timestamp": "2023-01-01 12:00:00", "temperature": 23.5, "humidity": 65, "pressure": 1013},
                            {"timestamp": "2023-01-01 12:01:00", "temperature": 23.7, "humidity": 64, "pressure": 1014},
                            {"timestamp": "2023-01-01 12:02:00", "temperature": 23.6, "humidity": 66, "pressure": 1012}
                        ]
                    }, indent=2)
                
                with open(file_path, 'w') as file:
                    file.write(data)
                
                QMessageBox.information(self, "Success", f"Data exported to {file_path}")
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to export data:\\n{str(e)}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTFileManager()
    window.show()
    app.exec()
```

## Form Submission and Data Handling

Here's a comprehensive example showing form handling with validation:

```python
import sys
import json
from datetime import datetime
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QFormLayout, QWidget, QPushButton, QLabel, QLineEdit, 
                             QComboBox, QSpinBox, QTextEdit, QCheckBox, QMessageBox,
                             QGroupBox, QProgressBar)
from PyQt6.QtCore import QTimer, Qt

class IoTDeviceRegistration(QMainWindow):
    def __init__(self):
        super().__init__()
        self.devices = []  # Store registered devices
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle("IoT Device Registration System")
        self.setGeometry(150, 150, 500, 600)
        
        central_widget = QWidget()
        main_layout = QVBoxLayout()
        
        # Title
        title = QLabel("Register New IoT Device")
        title.setAlignment(Qt.AlignmentFlag.AlignCenter)
        title.setStyleSheet("font-size: 18px; font-weight: bold; color: #1976D2; margin: 10px;")
        
        # Registration form
        form_group = QGroupBox("Device Information")
        form_layout = QFormLayout()
        
        # Form fields
        self.device_name = QLineEdit()
        self.device_name.setPlaceholderText("e.g., Greenhouse_Sensor_01")
        
        self.device_type = QComboBox()
        self.device_type.addItems([
            "Temperature Sensor",
            "Humidity Sensor", 
            "Pressure Sensor",
            "Light Sensor",
            "Motion Detector",
            "Camera Module",
            "Actuator",
            "Controller"
        ])
        
        self.location = QLineEdit()
        self.location.setPlaceholderText("e.g., Greenhouse Zone A")
        
        self.ip_address = QLineEdit()
        self.ip_address.setPlaceholderText("192.168.1.100")
        
        self.port = QSpinBox()
        self.port.setRange(1, 65535)
        self.port.setValue(8080)
        
        self.manufacturer = QLineEdit()
        self.manufacturer.setPlaceholderText("e.g., Arduino, Raspberry Pi")
        
        self.model = QLineEdit()
        self.model.setPlaceholderText("e.g., Uno R3, Pi 4B")
        
        self.firmware = QLineEdit()
        self.firmware.setPlaceholderText("e.g., 1.2.3")
        
        self.description = QTextEdit()
        self.description.setPlaceholderText("Optional description of the device and its purpose...")
        self.description.setMaximumHeight(80)
        
        self.is_critical = QCheckBox("Critical Device (requires immediate attention if offline)")
        self.enable_monitoring = QCheckBox("Enable continuous monitoring")
        self.enable_monitoring.setChecked(True)
        
        # Add fields to form
        form_layout.addRow("Device Name*:", self.device_name)
        form_layout.addRow("Device Type*:", self.device_type)
        form_layout.addRow("Location*:", self.location)
        form_layout.addRow("IP Address*:", self.ip_address)
        form_layout.addRow("Port:", self.port)
        form_layout.addRow("Manufacturer:", self.manufacturer)
        form_layout.addRow("Model:", self.model)
        form_layout.addRow("Firmware Version:", self.firmware)
        form_layout.addRow("Description:", self.description)
        form_layout.addRow("", self.is_critical)
        form_layout.addRow("", self.enable_monitoring)
        
        form_group.setLayout(form_layout)
        
        # Progress bar for registration process
        self.progress_bar = QProgressBar()
        self.progress_bar.setVisible(False)
        
        # Status label
        self.status_label = QLabel("Fill in the device information and click Register")
        self.status_label.setStyleSheet("padding: 8px; background-color: #e3f2fd; border-radius: 4px;")
        
        # Buttons
        button_layout = QHBoxLayout()
        
        self.register_btn = QPushButton("Register Device")
        self.clear_btn = QPushButton("Clear Form")
        self.view_devices_btn = QPushButton("View Registered Devices")
        
        self.register_btn.setStyleSheet("""
            QPushButton {
                background-color: #4CAF50;
                color: white;
                padding: 10px 20px;
                border: none;
                border-radius: 5px;
                font-size: 14px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        """)
        
        self.register_btn.clicked.connect(self.register_device)
        self.clear_btn.clicked.connect(self.clear_form)
        self.view_devices_btn.clicked.connect(self.view_devices)
        
        button_layout.addWidget(self.register_btn)
        button_layout.addWidget(self.clear_btn)
        button_layout.addWidget(self.view_devices_btn)
        
        # Add to main layout
        main_layout.addWidget(title)
        main_layout.addWidget(form_group)
        main_layout.addWidget(self.progress_bar)
        main_layout.addWidget(self.status_label)
        main_layout.addLayout(button_layout)
        
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)
    
    def register_device(self):
        """Register the device with validation"""
        # Validate required fields
        errors = []
        
        if not self.device_name.text().strip():
            errors.append("Device name is required")
        
        if not self.location.text().strip():
            errors.append("Location is required")
        
        if not self.ip_address.text().strip():
            errors.append("IP address is required")
        elif not self.is_valid_ip(self.ip_address.text().strip()):
            errors.append("Invalid IP address format")
        
        # Check for duplicate device name
        device_name = self.device_name.text().strip()
        if any(device['name'] == device_name for device in self.devices):
            errors.append("Device name already exists")
        
        if errors:
            QMessageBox.warning(self, "Validation Error", "\\n".join(errors))
            return
        
        # Show progress and simulate registration process
        self.progress_bar.setVisible(True)
        self.progress_bar.setValue(0)
        self.register_btn.setEnabled(False)
        self.status_label.setText("Registering device...")
        
        # Simulate registration process with timer
        self.registration_step = 0
        self.registration_timer = QTimer()
        self.registration_timer.timeout.connect(self.update_registration_progress)
        self.registration_timer.start(500)  # Update every 500ms
    
    def update_registration_progress(self):
        """Update registration progress"""
        steps = [
            "Validating device information...",
            "Checking network connectivity...", 
            "Registering device in database...",
            "Setting up monitoring...",
            "Registration complete!"
        ]
        
        if self.registration_step < len(steps):
            self.status_label.setText(steps[self.registration_step])
            self.progress_bar.setValue((self.registration_step + 1) * 20)
            self.registration_step += 1
        else:
            # Registration complete
            self.registration_timer.stop()
            self.complete_registration()
    
    def complete_registration(self):
        """Complete the registration process"""
        # Create device record
        device = {
            'name': self.device_name.text().strip(),
            'type': self.device_type.currentText(),
            'location': self.location.text().strip(),
            'ip_address': self.ip_address.text().strip(),
            'port': self.port.value(),
            'manufacturer': self.manufacturer.text().strip(),
            'model': self.model.text().strip(),
            'firmware': self.firmware.text().strip(),
            'description': self.description.toPlainText().strip(),
            'is_critical': self.is_critical.isChecked(),
            'enable_monitoring': self.enable_monitoring.isChecked(),
            'registration_date': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            'status': 'Registered'
        }
        
        self.devices.append(device)
        
        # Reset UI
        self.progress_bar.setVisible(False)
        self.register_btn.setEnabled(True)
        self.status_label.setText(f"Device '{device['name']}' registered successfully!")
        self.status_label.setStyleSheet("padding: 8px; background-color: #c8e6c9; border-radius: 4px; color: green;")
        
        # Show success message
        QMessageBox.information(self, "Success", 
                               f"Device '{device['name']}' has been registered successfully!\\n\\n"
                               f"Location: {device['location']}\\n"
                               f"IP: {device['ip_address']}:{device['port']}")
        
        # Clear form
        self.clear_form()
    
    def clear_form(self):
        """Clear all form fields"""
        self.device_name.setText("")
        self.device_type.setCurrentIndex(0)
        self.location.setText("")
        self.ip_address.setText("")
        self.port.setValue(8080)
        self.manufacturer.setText("")
        self.model.setText("")
        self.firmware.setText("")
        self.description.setText("")
        self.is_critical.setChecked(False)
        self.enable_monitoring.setChecked(True)
        
        self.status_label.setText("Fill in the device information and click Register")
        self.status_label.setStyleSheet("padding: 8px; background-color: #e3f2fd; border-radius: 4px;")
    
    def view_devices(self):
        """Show registered devices"""
        if not self.devices:
            QMessageBox.information(self, "No Devices", "No devices have been registered yet.")
            return
        
        device_list = "Registered IoT Devices:\\n\\n"
        for i, device in enumerate(self.devices, 1):
            device_list += f"{i}. {device['name']} ({device['type']})\\n"
            device_list += f"   Location: {device['location']}\\n"
            device_list += f"   IP: {device['ip_address']}:{device['port']}\\n"
            device_list += f"   Status: {device['status']}\\n"
            if device['is_critical']:
                device_list += f"   ⚠️ Critical Device\\n"
            device_list += f"   Registered: {device['registration_date']}\\n\\n"
        
        msg = QMessageBox()
        msg.setWindowTitle("Registered Devices")
        msg.setText(f"Total devices: {len(self.devices)}")
        msg.setDetailedText(device_list)
        msg.exec()
    
    def is_valid_ip(self, ip):
        """Validate IP address format"""
        try:
            parts = ip.split('.')
            if len(parts) != 4:
                return False
            for part in parts:
                if not (0 <= int(part) <= 255):
                    return False
            return True
        except:
            return False

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = IoTDeviceRegistration()
    window.show()
    app.exec()
```

## Best Practices

1. **Always validate input** before processing
2. **Provide clear error messages** that tell users how to fix problems
3. **Use appropriate input widgets** (spinboxes for numbers, combo boxes for choices)
4. **Show progress** for long operations
5. **Confirm destructive actions** with dialogs
6. **Save user data** before closing or switching forms
7. **Use modal dialogs** for critical configuration
8. **Provide defaults** for common values

## Practice Exercise

Create a complete IoT sensor calibration system with:

1. **Calibration Dialog** with fields for:
   - Sensor type selection
   - Reference values input
   - Calibration points (multiple)
   - Notes and comments

2. **Validation** for:
   - Numeric ranges
   - Required fields
   - Data consistency

3. **File Operations**:
   - Save/load calibration data
   - Export calibration reports
   - Import reference standards

4. **Progress Tracking**:
   - Multi-step calibration process
   - Progress indication
   - Error handling

## What's Next?

In the next tutorial, we'll learn about:
- Data persistence and storage
- Working with JSON and CSV files
- Database integration basics
- Configuration management

Ready to store and manage data? Let's move to Tutorial 7!