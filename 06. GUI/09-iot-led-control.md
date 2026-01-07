<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# IoT Project 2: Smart LED Control Interface

## Introduction

In this tutorial, we'll build a comprehensive LED control interface that demonstrates device control in IoT applications. This project will simulate controlling multiple LED strips with different patterns, colors, and effects. It showcases advanced PyQt6 controls, real-time device communication simulation, and sophisticated user interfaces.

## Project Overview

Our Smart LED Control System will include:
- Multiple LED strip control
- Color picker and pattern selection
- Real-time preview of LED effects
- Scheduling and automation
- Scene management and presets
- Power consumption monitoring
- Network device discovery

## Project Structure

Create a new folder `smart_led_controller` with these files:
- `led_controller.py` - Main application
- `led_device.py` - LED device simulation
- `color_utils.py` - Color manipulation utilities
- `effects_engine.py` - LED effects and patterns
- `device_manager.py` - Device discovery and management
- `scheduler.py` - Automation and scheduling

## Step 1: Color Utilities and LED Device Simulation

### color_utils.py

```python
import colorsys
import math
from PyQt6.QtGui import QColor
from PyQt6.QtCore import QTimer, QObject, pyqtSignal

class ColorUtils:
    """Utility functions for color manipulation and conversion"""
    
    @staticmethod
    def rgb_to_hsv(r, g, b):
        """Convert RGB to HSV"""
        return colorsys.rgb_to_hsv(r/255.0, g/255.0, b/255.0)
    
    @staticmethod
    def hsv_to_rgb(h, s, v):
        """Convert HSV to RGB"""
        rgb = colorsys.hsv_to_rgb(h, s, v)
        return tuple(int(c * 255) for c in rgb)
    
    @staticmethod
    def color_temperature_to_rgb(temp):
        """Convert color temperature (K) to RGB"""
        # Simplified algorithm for common temperature range
        temp = temp / 100
        
        if temp <= 66:
            red = 255
            green = temp
            green = 99.4708025861 * math.log(green) - 161.1195681661
            
            if temp >= 19:
                blue = temp - 10
                blue = 138.5177312231 * math.log(blue) - 305.0447927307
            else:
                blue = 0
        else:
            red = temp - 60
            red = 329.698727446 * (red ** -0.1332047592)
            
            green = temp - 60
            green = 288.1221695283 * (green ** -0.0755148492)
            
            blue = 255
        
        # Clamp values
        red = max(0, min(255, red))
        green = max(0, min(255, green))
        blue = max(0, min(255, blue))
        
        return int(red), int(green), int(blue)
    
    @staticmethod
    def blend_colors(color1, color2, ratio):
        """Blend two RGB colors with given ratio (0.0 to 1.0)"""
        r1, g1, b1 = color1
        r2, g2, b2 = color2
        
        r = int(r1 * (1 - ratio) + r2 * ratio)
        g = int(g1 * (1 - ratio) + g2 * ratio)
        b = int(b1 * (1 - ratio) + b2 * ratio)
        
        return (r, g, b)
    
    @staticmethod
    def generate_rainbow_colors(num_colors):
        """Generate a list of rainbow colors"""
        colors = []
        for i in range(num_colors):
            hue = i / num_colors
            rgb = ColorUtils.hsv_to_rgb(hue, 1.0, 1.0)
            colors.append(rgb)
        return colors

class LEDDevice(QObject):
    """Simulates an individual LED device/strip"""
    
    status_changed = pyqtSignal(str, dict)  # device_id, status_info
    
    def __init__(self, device_id, name, led_count=60):
        super().__init__()
        self.device_id = device_id
        self.name = name
        self.led_count = led_count
        
        # Device state
        self.is_connected = False
        self.is_on = False
        self.brightness = 100
        self.current_color = (255, 255, 255)
        self.current_pattern = "solid"
        self.pattern_speed = 50
        self.power_consumption = 0.0  # Watts
        
        # LED strip state (each LED has RGB values)
        self.led_strip = [(0, 0, 0) for _ in range(led_count)]
        
        # Network simulation
        self.ip_address = f"192.168.1.{100 + hash(device_id) % 50}"
        self.signal_strength = 85  # dBm
        
        # Update timer for animations
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.update_leds)
        self.animation_frame = 0
    
    def connect_device(self):
        """Simulate device connection"""
        self.is_connected = True
        self.emit_status_update()
        return True
    
    def disconnect_device(self):
        """Simulate device disconnection"""
        self.is_connected = False
        self.is_on = False
        self.update_timer.stop()
        self.emit_status_update()
    
    def power_on(self):
        """Turn on the LED strip"""
        if self.is_connected:
            self.is_on = True
            self.update_timer.start(50)  # 20 FPS
            self.update_leds()
            self.emit_status_update()
    
    def power_off(self):
        """Turn off the LED strip"""
        self.is_on = False
        self.update_timer.stop()
        self.led_strip = [(0, 0, 0) for _ in range(self.led_count)]
        self.power_consumption = 0.0
        self.emit_status_update()
    
    def set_brightness(self, brightness):
        """Set LED brightness (0-100)"""
        self.brightness = max(0, min(100, brightness))
        if self.is_on:
            self.update_leds()
        self.emit_status_update()
    
    def set_color(self, r, g, b):
        """Set solid color"""
        self.current_color = (r, g, b)
        self.current_pattern = "solid"
        if self.is_on:
            self.update_leds()
        self.emit_status_update()
    
    def set_pattern(self, pattern, speed=50):
        """Set LED pattern"""
        self.current_pattern = pattern
        self.pattern_speed = speed
        self.animation_frame = 0
        if self.is_on:
            self.update_leds()
        self.emit_status_update()
    
    def update_leds(self):
        """Update LED strip based on current settings"""
        if not self.is_on:
            return
        
        brightness_factor = self.brightness / 100.0
        
        if self.current_pattern == "solid":
            # Solid color
            color = tuple(int(c * brightness_factor) for c in self.current_color)
            self.led_strip = [color for _ in range(self.led_count)]
        
        elif self.current_pattern == "rainbow":
            # Rainbow pattern
            colors = ColorUtils.generate_rainbow_colors(self.led_count)
            offset = (self.animation_frame * self.pattern_speed // 100) % self.led_count
            
            for i in range(self.led_count):
                color_index = (i + offset) % len(colors)
                color = tuple(int(c * brightness_factor) for c in colors[color_index])
                self.led_strip[i] = color
        
        elif self.current_pattern == "breathing":
            # Breathing effect
            breath_cycle = math.sin(self.animation_frame * 0.1 * self.pattern_speed / 50)
            breath_brightness = (breath_cycle + 1) / 2  # Normalize to 0-1
            final_brightness = brightness_factor * breath_brightness
            
            color = tuple(int(c * final_brightness) for c in self.current_color)
            self.led_strip = [color for _ in range(self.led_count)]
        
        elif self.current_pattern == "strobe":
            # Strobe effect
            strobe_on = (self.animation_frame * self.pattern_speed // 100) % 10 < 2
            if strobe_on:
                color = tuple(int(c * brightness_factor) for c in self.current_color)
            else:
                color = (0, 0, 0)
            self.led_strip = [color for _ in range(self.led_count)]
        
        elif self.current_pattern == "chase":
            # Chase pattern
            chase_position = (self.animation_frame * self.pattern_speed // 100) % self.led_count
            chase_length = 5
            
            for i in range(self.led_count):
                if abs(i - chase_position) < chase_length:
                    fade_factor = 1.0 - (abs(i - chase_position) / chase_length)
                    color = tuple(int(c * brightness_factor * fade_factor) for c in self.current_color)
                else:
                    color = (0, 0, 0)
                self.led_strip[i] = color
        
        elif self.current_pattern == "fire":
            # Fire simulation
            for i in range(self.led_count):
                # Create fire effect with random red/orange colors
                heat = math.sin(i * 0.3 + self.animation_frame * 0.05) * 0.5 + 0.5
                heat += (random.random() - 0.5) * 0.3
                heat = max(0, min(1, heat))
                
                red = int(255 * heat * brightness_factor)
                green = int(128 * heat * heat * brightness_factor)
                blue = int(32 * heat * heat * heat * brightness_factor)
                
                self.led_strip[i] = (red, green, blue)
        
        # Calculate power consumption (simplified)
        total_brightness = sum(sum(led) for led in self.led_strip)
        max_brightness = self.led_count * 255 * 3  # Max possible brightness
        self.power_consumption = (total_brightness / max_brightness) * 15.0  # Max 15W per strip
        
        self.animation_frame += 1
        
        # Emit update for UI
        self.emit_status_update()
    
    def emit_status_update(self):
        """Emit status update signal"""
        status = {
            'name': self.name,
            'connected': self.is_connected,
            'powered_on': self.is_on,
            'brightness': self.brightness,
            'color': self.current_color,
            'pattern': self.current_pattern,
            'pattern_speed': self.pattern_speed,
            'power_consumption': self.power_consumption,
            'led_count': self.led_count,
            'ip_address': self.ip_address,
            'signal_strength': self.signal_strength,
            'led_strip': self.led_strip[:10] if len(self.led_strip) > 10 else self.led_strip  # Send first 10 for preview
        }
        self.status_changed.emit(self.device_id, status)

import random
```

### effects_engine.py

```python
import math
import random
from PyQt6.QtCore import QObject, QTimer, pyqtSignal

class EffectsEngine(QObject):
    """Advanced LED effects and pattern engine"""
    
    effect_update = pyqtSignal(str, list)  # device_id, led_data
    
    def __init__(self):
        super().__init__()
        self.active_effects = {}  # device_id -> effect_config
        
        # Update timer
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_effects)
        self.timer.start(50)  # 20 FPS
        
        self.frame_count = 0
    
    def add_effect(self, device_id, effect_config):
        """Add or update effect for a device"""
        self.active_effects[device_id] = effect_config
    
    def remove_effect(self, device_id):
        """Remove effect from a device"""
        if device_id in self.active_effects:
            del self.active_effects[device_id]
    
    def update_effects(self):
        """Update all active effects"""
        for device_id, config in self.active_effects.items():
            led_data = self.calculate_effect(config)
            self.effect_update.emit(device_id, led_data)
        
        self.frame_count += 1
    
    def calculate_effect(self, config):
        """Calculate LED data for a specific effect"""
        effect_type = config.get('type', 'solid')
        led_count = config.get('led_count', 60)
        brightness = config.get('brightness', 100) / 100.0
        speed = config.get('speed', 50)
        colors = config.get('colors', [(255, 255, 255)])
        
        led_data = [(0, 0, 0) for _ in range(led_count)]
        
        if effect_type == 'solid':
            color = colors[0] if colors else (255, 255, 255)
            led_data = [tuple(int(c * brightness) for c in color) for _ in range(led_count)]
        
        elif effect_type == 'gradient':
            if len(colors) >= 2:
                for i in range(led_count):
                    ratio = i / (led_count - 1)
                    color = self.interpolate_color(colors[0], colors[1], ratio)
                    led_data[i] = tuple(int(c * brightness) for c in color)
        
        elif effect_type == 'rainbow_wave':
            wavelength = 20
            for i in range(led_count):
                hue = ((i + self.frame_count * speed / 50) % wavelength) / wavelength
                rgb = self.hsv_to_rgb(hue, 1.0, 1.0)
                led_data[i] = tuple(int(c * brightness) for c in rgb)
        
        elif effect_type == 'sparkle':
            # Random sparkles
            base_color = colors[0] if colors else (50, 50, 50)
            sparkle_color = colors[1] if len(colors) > 1 else (255, 255, 255)
            
            for i in range(led_count):
                if random.random() < 0.05:  # 5% chance of sparkle
                    led_data[i] = tuple(int(c * brightness) for c in sparkle_color)
                else:
                    led_data[i] = tuple(int(c * brightness * 0.3) for c in base_color)
        
        elif effect_type == 'comet':
            comet_length = 10
            position = (self.frame_count * speed / 50) % (led_count + comet_length)
            
            for i in range(led_count):
                distance = position - i
                if 0 <= distance < comet_length:
                    intensity = (comet_length - distance) / comet_length
                    color = colors[0] if colors else (255, 255, 255)
                    led_data[i] = tuple(int(c * brightness * intensity) for c in color)
        
        elif effect_type == 'pulse':
            # Pulse effect with multiple colors
            pulse_width = led_count // len(colors) if colors else led_count
            
            for color_idx, color in enumerate(colors):
                center = (color_idx * pulse_width + pulse_width // 2) % led_count
                pulse_intensity = math.sin(self.frame_count * 0.1 * speed / 50) * 0.5 + 0.5
                
                for i in range(led_count):
                    distance = abs(i - center)
                    if distance < pulse_width // 2:
                        intensity = (1 - distance / (pulse_width // 2)) * pulse_intensity
                        current_color = led_data[i]
                        new_color = tuple(int(c * brightness * intensity) for c in color)
                        led_data[i] = tuple(max(current_color[j], new_color[j]) for j in range(3))
        
        elif effect_type == 'matrix':
            # Matrix rain effect
            drops = config.get('matrix_drops', [])
            if not drops:
                # Initialize drops
                drops = [{'position': random.randint(0, led_count), 'speed': random.uniform(0.5, 2.0), 'length': random.randint(5, 15)} for _ in range(led_count // 10)]
                config['matrix_drops'] = drops
            
            # Clear LEDs
            led_data = [(0, 0, 0) for _ in range(led_count)]
            
            # Update drops
            for drop in drops:
                drop['position'] += drop['speed'] * speed / 50
                if drop['position'] > led_count + drop['length']:
                    drop['position'] = -drop['length']
                    drop['speed'] = random.uniform(0.5, 2.0)
                    drop['length'] = random.randint(5, 15)
                
                # Draw drop
                for i in range(drop['length']):
                    led_pos = int(drop['position'] - i)
                    if 0 <= led_pos < led_count:
                        intensity = (drop['length'] - i) / drop['length']
                        green = int(255 * intensity * brightness)
                        led_data[led_pos] = (0, green, 0)
        
        return led_data
    
    def interpolate_color(self, color1, color2, ratio):
        """Interpolate between two colors"""
        r1, g1, b1 = color1
        r2, g2, b2 = color2
        
        r = int(r1 * (1 - ratio) + r2 * ratio)
        g = int(g1 * (1 - ratio) + g2 * ratio)
        b = int(b1 * (1 - ratio) + b2 * ratio)
        
        return (r, g, b)
    
    def hsv_to_rgb(self, h, s, v):
        """Convert HSV to RGB"""
        import colorsys
        rgb = colorsys.hsv_to_rgb(h, s, v)
        return tuple(int(c * 255) for c in rgb)
```

## Step 2: Device Manager and Main Controller

### device_manager.py

```python
import json
import time
from datetime import datetime
from PyQt6.QtCore import QObject, QTimer, pyqtSignal

class DeviceManager(QObject):
    """Manages multiple LED devices and their discovery"""
    
    device_discovered = pyqtSignal(dict)  # device_info
    device_lost = pyqtSignal(str)  # device_id
    device_status_changed = pyqtSignal(str, dict)  # device_id, status
    
    def __init__(self):
        super().__init__()
        self.devices = {}
        self.device_configs = {}
        
        # Discovery simulation
        self.discovery_timer = QTimer()
        self.discovery_timer.timeout.connect(self.simulate_discovery)
        
        # Load saved configurations
        self.load_device_configs()
    
    def start_discovery(self):
        """Start device discovery"""
        self.discovery_timer.start(5000)  # Check every 5 seconds
        self.simulate_discovery()  # Initial discovery
    
    def stop_discovery(self):
        """Stop device discovery"""
        self.discovery_timer.stop()
    
    def simulate_discovery(self):
        """Simulate discovering new devices on the network"""
        # Simulate finding devices
        simulated_devices = [
            {
                'device_id': 'led_strip_001',
                'name': 'Living Room LED Strip',
                'ip_address': '192.168.1.101',
                'mac_address': '00:1B:44:11:3A:B7',
                'model': 'WS2812B',
                'led_count': 60,
                'firmware_version': '1.2.3'
            },
            {
                'device_id': 'led_strip_002',
                'name': 'Kitchen Under-Cabinet LEDs',
                'ip_address': '192.168.1.102',
                'mac_address': '00:1B:44:11:3A:B8',
                'model': 'SK6812',
                'led_count': 144,
                'firmware_version': '1.2.3'
            },
            {
                'device_id': 'led_strip_003',
                'name': 'Bedroom Accent Lighting',
                'ip_address': '192.168.1.103',
                'mac_address': '00:1B:44:11:3A:B9',
                'model': 'WS2811',
                'led_count': 30,
                'firmware_version': '1.1.8'
            }
        ]
        
        for device_info in simulated_devices:
            device_id = device_info['device_id']
            if device_id not in self.devices:
                # New device discovered
                self.device_discovered.emit(device_info)
    
    def add_device(self, device_info):
        """Add a new device to management"""
        device_id = device_info['device_id']
        self.devices[device_id] = device_info
        
        # Load saved configuration if exists
        if device_id in self.device_configs:
            device_info.update(self.device_configs[device_id])
        
        return device_id
    
    def remove_device(self, device_id):
        """Remove a device from management"""
        if device_id in self.devices:
            del self.devices[device_id]
            self.device_lost.emit(device_id)
    
    def get_device_info(self, device_id):
        """Get device information"""
        return self.devices.get(device_id, {})
    
    def get_all_devices(self):
        """Get all managed devices"""
        return dict(self.devices)
    
    def save_device_config(self, device_id, config):
        """Save device configuration"""
        self.device_configs[device_id] = config
        self.save_device_configs()
    
    def load_device_configs(self):
        """Load saved device configurations"""
        try:
            with open('device_configs.json', 'r') as f:
                self.device_configs = json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            self.device_configs = {}
    
    def save_device_configs(self):
        """Save device configurations to file"""
        try:
            with open('device_configs.json', 'w') as f:
                json.dump(self.device_configs, f, indent=2)
        except Exception as e:
            print(f"Failed to save device configs: {e}")
    
    def create_device_preset(self, name, devices_config):
        """Create a preset configuration for multiple devices"""
        preset = {
            'name': name,
            'created': datetime.now().isoformat(),
            'devices': devices_config
        }
        
        # Save preset
        try:
            with open('presets.json', 'r') as f:
                presets = json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            presets = {}
        
        presets[name] = preset
        
        with open('presets.json', 'w') as f:
            json.dump(presets, f, indent=2)
        
        return preset
    
    def load_device_presets(self):
        """Load all device presets"""
        try:
            with open('presets.json', 'r') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}
    
    def apply_preset(self, preset_name):
        """Apply a preset to all devices"""
        presets = self.load_device_presets()
        if preset_name in presets:
            preset = presets[preset_name]
            return preset.get('devices', {})
        return {}
```

### scheduler.py

```python
import json
import time
from datetime import datetime, timedelta
from PyQt6.QtCore import QObject, QTimer, pyqtSignal

class LEDScheduler(QObject):
    """Handles scheduling and automation for LED devices"""
    
    schedule_triggered = pyqtSignal(str, dict)  # schedule_id, action
    
    def __init__(self):
        super().__init__()
        self.schedules = {}
        self.active_schedules = {}
        
        # Check timer
        self.check_timer = QTimer()
        self.check_timer.timeout.connect(self.check_schedules)
        self.check_timer.start(60000)  # Check every minute
        
        self.load_schedules()
    
    def add_schedule(self, schedule_config):
        """Add a new schedule"""
        schedule_id = f"schedule_{int(time.time())}"
        schedule_config['id'] = schedule_id
        schedule_config['created'] = datetime.now().isoformat()
        
        self.schedules[schedule_id] = schedule_config
        self.save_schedules()
        
        return schedule_id
    
    def remove_schedule(self, schedule_id):
        """Remove a schedule"""
        if schedule_id in self.schedules:
            del self.schedules[schedule_id]
            self.save_schedules()
    
    def enable_schedule(self, schedule_id, enabled=True):
        """Enable or disable a schedule"""
        if schedule_id in self.schedules:
            self.schedules[schedule_id]['enabled'] = enabled
            self.save_schedules()
    
    def check_schedules(self):
        """Check if any schedules should be triggered"""
        now = datetime.now()
        current_time = now.strftime("%H:%M")
        current_day = now.strftime("%A").lower()
        
        for schedule_id, schedule in self.schedules.items():
            if not schedule.get('enabled', True):
                continue
            
            schedule_type = schedule.get('type', 'time')
            
            if schedule_type == 'time':
                trigger_time = schedule.get('time', '00:00')
                days = schedule.get('days', ['monday', 'tuesday', 'wednesday', 'thursday', 'friday', 'saturday', 'sunday'])
                
                if current_time == trigger_time and current_day in days:
                    # Check if not already triggered today
                    last_triggered = schedule.get('last_triggered', '')
                    if not last_triggered.startswith(now.strftime("%Y-%m-%d")):
                        self.trigger_schedule(schedule_id, schedule)
            
            elif schedule_type == 'sunset':
                # Simplified sunset calculation (would use actual sunset API in real app)
                sunset_time = "18:30"  # Hardcoded for demo
                if current_time == sunset_time:
                    self.trigger_schedule(schedule_id, schedule)
            
            elif schedule_type == 'sunrise':
                # Simplified sunrise calculation
                sunrise_time = "06:30"  # Hardcoded for demo
                if current_time == sunrise_time:
                    self.trigger_schedule(schedule_id, schedule)
    
    def trigger_schedule(self, schedule_id, schedule):
        """Trigger a schedule"""
        # Update last triggered time
        self.schedules[schedule_id]['last_triggered'] = datetime.now().isoformat()
        
        action = schedule.get('action', {})
        self.schedule_triggered.emit(schedule_id, action)
        
        self.save_schedules()
    
    def create_time_schedule(self, name, time_str, days, action, devices):
        """Create a time-based schedule"""
        schedule = {
            'name': name,
            'type': 'time',
            'time': time_str,
            'days': days,
            'action': action,
            'devices': devices,
            'enabled': True
        }
        return self.add_schedule(schedule)
    
    def create_sunrise_sunset_schedule(self, name, event_type, offset_minutes, action, devices):
        """Create sunrise/sunset schedule"""
        schedule = {
            'name': name,
            'type': event_type,  # 'sunrise' or 'sunset'
            'offset_minutes': offset_minutes,
            'action': action,
            'devices': devices,
            'enabled': True
        }
        return self.add_schedule(schedule)
    
    def get_schedules(self):
        """Get all schedules"""
        return dict(self.schedules)
    
    def load_schedules(self):
        """Load schedules from file"""
        try:
            with open('schedules.json', 'r') as f:
                self.schedules = json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            self.schedules = {}
    
    def save_schedules(self):
        """Save schedules to file"""
        try:
            with open('schedules.json', 'w') as f:
                json.dump(self.schedules, f, indent=2)
        except Exception as e:
            print(f"Failed to save schedules: {e}")
```

## Step 3: Main LED Controller Application

### led_controller.py

```python
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
                             QGridLayout, QWidget, QPushButton, QLabel, QSlider,
                             QComboBox, QSpinBox, QCheckBox, QColorDialog, QListWidget,
                             QListWidgetItem, QGroupBox, QTabWidget, QTextEdit,
                             QProgressBar, QTableWidget, QTableWidgetItem,
                             QScrollArea, QFrame, QSplitter, QMessageBox,
                             QInputDialog, QTimeEdit, QCalendarWidget)
from PyQt6.QtCore import Qt, QTimer, pyqtSlot, QTime
from PyQt6.QtGui import QColor, QPainter, QBrush, QPen, QPixmap

from color_utils import LEDDevice, ColorUtils
from effects_engine import EffectsEngine
from device_manager import DeviceManager
from scheduler import LEDScheduler

class LEDPreviewWidget(QWidget):
    """Widget to show LED strip preview"""
    
    def __init__(self, led_count=60):
        super().__init__()
        self.led_count = led_count
        self.led_data = [(0, 0, 0) for _ in range(led_count)]
        self.setMinimumHeight(40)
        self.setMaximumHeight(40)
    
    def update_leds(self, led_data):
        """Update LED data and redraw"""
        self.led_data = led_data[:self.led_count]
        self.update()
    
    def paintEvent(self, event):
        """Paint the LED strip preview"""
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        
        width = self.width()
        height = self.height()
        led_width = width / self.led_count
        
        for i, (r, g, b) in enumerate(self.led_data):
            x = i * led_width
            
            # LED background (always show position)
            painter.setBrush(QBrush(QColor(30, 30, 30)))
            painter.setPen(QPen(QColor(100, 100, 100), 1))
            painter.drawEllipse(int(x + 1), 5, int(led_width - 2), height - 10)
            
            # LED color (if any)
            if r > 0 or g > 0 or b > 0:
                painter.setBrush(QBrush(QColor(r, g, b)))
                painter.setPen(QPen(QColor(min(255, r + 50), min(255, g + 50), min(255, b + 50)), 1))
                painter.drawEllipse(int(x + 2), 6, int(led_width - 4), height - 12)

class DeviceControlWidget(QWidget):
    """Widget for controlling a single LED device"""
    
    def __init__(self, device_id, device_info, led_device):
        super().__init__()
        self.device_id = device_id
        self.device_info = device_info
        self.led_device = led_device
        
        self.initUI()
        self.connect_signals()
    
    def initUI(self):
        """Initialize the device control interface"""
        layout = QVBoxLayout()
        
        # Device header
        header_layout = QHBoxLayout()
        
        self.device_name = QLabel(self.device_info.get('name', 'Unknown Device'))
        self.device_name.setStyleSheet("font-weight: bold; font-size: 14px;")
        
        self.connection_status = QLabel("Disconnected")
        self.connection_status.setStyleSheet("color: red; font-size: 12px;")
        
        self.connect_btn = QPushButton("Connect")
        self.connect_btn.clicked.connect(self.toggle_connection)
        
        header_layout.addWidget(self.device_name)
        header_layout.addStretch()
        header_layout.addWidget(self.connection_status)
        header_layout.addWidget(self.connect_btn)
        
        # Device info
        info_layout = QHBoxLayout()
        info_layout.addWidget(QLabel(f"IP: {self.device_info.get('ip_address', 'Unknown')}"))
        info_layout.addWidget(QLabel(f"LEDs: {self.device_info.get('led_count', 0)}"))
        info_layout.addWidget(QLabel(f"Model: {self.device_info.get('model', 'Unknown')}"))
        
        # Power control
        power_layout = QHBoxLayout()
        
        self.power_btn = QPushButton("Power On")
        self.power_btn.setEnabled(False)
        self.power_btn.clicked.connect(self.toggle_power)
        
        self.brightness_slider = QSlider(Qt.Orientation.Horizontal)
        self.brightness_slider.setRange(0, 100)
        self.brightness_slider.setValue(100)
        self.brightness_slider.setEnabled(False)
        self.brightness_slider.valueChanged.connect(self.brightness_changed)
        
        self.brightness_label = QLabel("100%")
        
        power_layout.addWidget(self.power_btn)
        power_layout.addWidget(QLabel("Brightness:"))
        power_layout.addWidget(self.brightness_slider)
        power_layout.addWidget(self.brightness_label)
        
        # Color control
        color_layout = QHBoxLayout()
        
        self.color_btn = QPushButton("Choose Color")
        self.color_btn.setEnabled(False)
        self.color_btn.clicked.connect(self.choose_color)
        
        self.current_color = QLabel()
        self.current_color.setFixedSize(30, 30)
        self.current_color.setStyleSheet("background-color: white; border: 1px solid black;")
        
        color_layout.addWidget(self.color_btn)
        color_layout.addWidget(self.current_color)
        
        # Pattern control
        pattern_layout = QHBoxLayout()
        
        self.pattern_combo = QComboBox()
        self.pattern_combo.addItems(["solid", "rainbow", "breathing", "strobe", "chase", "fire"])
        self.pattern_combo.setEnabled(False)
        self.pattern_combo.currentTextChanged.connect(self.pattern_changed)
        
        self.speed_slider = QSlider(Qt.Orientation.Horizontal)
        self.speed_slider.setRange(1, 100)
        self.speed_slider.setValue(50)
        self.speed_slider.setEnabled(False)
        self.speed_slider.valueChanged.connect(self.speed_changed)
        
        self.speed_label = QLabel("50%")
        
        pattern_layout.addWidget(QLabel("Pattern:"))
        pattern_layout.addWidget(self.pattern_combo)
        pattern_layout.addWidget(QLabel("Speed:"))
        pattern_layout.addWidget(self.speed_slider)
        pattern_layout.addWidget(self.speed_label)
        
        # LED preview
        self.led_preview = LEDPreviewWidget(self.device_info.get('led_count', 60))
        
        # Status info
        status_layout = QHBoxLayout()
        
        self.power_consumption = QLabel("Power: 0.0W")
        self.signal_strength = QLabel("Signal: -85dBm")
        
        status_layout.addWidget(self.power_consumption)
        status_layout.addWidget(self.signal_strength)
        status_layout.addStretch()
        
        # Add all to main layout
        layout.addLayout(header_layout)
        layout.addLayout(info_layout)
        layout.addLayout(power_layout)
        layout.addLayout(color_layout)
        layout.addLayout(pattern_layout)
        layout.addWidget(self.led_preview)
        layout.addLayout(status_layout)
        
        # Add frame border
        self.setFrameStyle(QFrame.Shape.Box)
        self.setStyleSheet("QFrame { border: 1px solid #cccccc; border-radius: 5px; padding: 5px; }")
        
        self.setLayout(layout)
    
    def connect_signals(self):
        """Connect LED device signals"""
        self.led_device.status_changed.connect(self.update_status)
    
    def toggle_connection(self):
        """Toggle device connection"""
        if self.led_device.is_connected:
            self.led_device.disconnect_device()
        else:
            self.led_device.connect_device()
    
    def toggle_power(self):
        """Toggle device power"""
        if self.led_device.is_on:
            self.led_device.power_off()
        else:
            self.led_device.power_on()
    
    def brightness_changed(self, value):
        """Handle brightness change"""
        self.brightness_label.setText(f"{value}%")
        self.led_device.set_brightness(value)
    
    def choose_color(self):
        """Open color picker dialog"""
        color = QColorDialog.getColor(QColor(*self.led_device.current_color), self)
        if color.isValid():
            r, g, b, _ = color.getRgb()
            self.led_device.set_color(r, g, b)
            self.current_color.setStyleSheet(f"background-color: rgb({r}, {g}, {b}); border: 1px solid black;")
    
    def pattern_changed(self, pattern):
        """Handle pattern change"""
        self.led_device.set_pattern(pattern, self.speed_slider.value())
    
    def speed_changed(self, value):
        """Handle speed change"""
        self.speed_label.setText(f"{value}%")
        self.led_device.set_pattern(self.led_device.current_pattern, value)
    
    @pyqtSlot(str, dict)
    def update_status(self, device_id, status):
        """Update device status display"""
        if device_id != self.device_id:
            return
        
        # Update connection status
        if status['connected']:
            self.connection_status.setText("Connected")
            self.connection_status.setStyleSheet("color: green; font-size: 12px;")
            self.connect_btn.setText("Disconnect")
            
            # Enable controls
            self.power_btn.setEnabled(True)
            self.brightness_slider.setEnabled(status['powered_on'])
            self.color_btn.setEnabled(status['powered_on'])
            self.pattern_combo.setEnabled(status['powered_on'])
            self.speed_slider.setEnabled(status['powered_on'])
        else:
            self.connection_status.setText("Disconnected")
            self.connection_status.setStyleSheet("color: red; font-size: 12px;")
            self.connect_btn.setText("Connect")
            
            # Disable controls
            self.power_btn.setEnabled(False)
            self.brightness_slider.setEnabled(False)
            self.color_btn.setEnabled(False)
            self.pattern_combo.setEnabled(False)
            self.speed_slider.setEnabled(False)
        
        # Update power status
        if status['powered_on']:
            self.power_btn.setText("Power Off")
        else:
            self.power_btn.setText("Power On")
        
        # Update other displays
        self.power_consumption.setText(f"Power: {status['power_consumption']:.1f}W")
        self.signal_strength.setText(f"Signal: {status['signal_strength']}dBm")
        
        # Update LED preview
        if 'led_strip' in status:
            self.led_preview.update_leds(status['led_strip'])

class LEDControllerApp(QMainWindow):
    """Main LED Controller Application"""
    
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Smart LED Controller")
        self.setGeometry(100, 100, 1400, 900)
        
        # Initialize components
        self.device_manager = DeviceManager()
        self.effects_engine = EffectsEngine()
        self.scheduler = LEDScheduler()
        
        # Device storage
        self.led_devices = {}  # device_id -> LEDDevice
        self.device_widgets = {}  # device_id -> DeviceControlWidget
        
        self.initUI()
        self.connect_signals()
        
        # Start device discovery
        self.device_manager.start_discovery()
    
    def initUI(self):
        """Initialize the main user interface"""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Create main layout
        main_layout = QHBoxLayout()
        
        # Left panel - Device list and controls
        left_panel = self.create_left_panel()
        
        # Right panel - Effects, scheduling, and advanced controls
        right_panel = self.create_right_panel()
        
        # Use splitter for resizable panels
        splitter = QSplitter(Qt.Orientation.Horizontal)
        splitter.addWidget(left_panel)
        splitter.addWidget(right_panel)
        splitter.setSizes([800, 600])
        
        main_layout.addWidget(splitter)
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
            QPushButton:disabled {
                background-color: #cccccc;
                color: #666666;
            }
        """)
    
    def create_left_panel(self):
        """Create the left panel with device controls"""
        panel = QWidget()
        layout = QVBoxLayout()
        
        # Device discovery and management
        discovery_group = QGroupBox("Device Management")
        discovery_layout = QHBoxLayout()
        
        self.discovery_btn = QPushButton("Start Discovery")
        self.discovery_btn.clicked.connect(self.toggle_discovery)
        
        self.add_device_btn = QPushButton("Add Manual Device")
        self.add_device_btn.clicked.connect(self.add_manual_device)
        
        self.refresh_btn = QPushButton("Refresh All")
        self.refresh_btn.clicked.connect(self.refresh_all_devices)
        
        discovery_layout.addWidget(self.discovery_btn)
        discovery_layout.addWidget(self.add_device_btn)
        discovery_layout.addWidget(self.refresh_btn)
        discovery_layout.addStretch()
        
        discovery_group.setLayout(discovery_layout)
        
        # Device list (scrollable)
        devices_group = QGroupBox("Connected Devices")
        devices_layout = QVBoxLayout()
        
        self.devices_scroll = QScrollArea()
        self.devices_scroll.setWidgetResizable(True)
        self.devices_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        
        self.devices_container = QWidget()
        self.devices_container_layout = QVBoxLayout()
        self.devices_container.setLayout(self.devices_container_layout)
        
        self.devices_scroll.setWidget(self.devices_container)
        
        devices_layout.addWidget(self.devices_scroll)
        devices_group.setLayout(devices_layout)
        
        # Global controls
        global_group = QGroupBox("Global Controls")
        global_layout = QVBoxLayout()
        
        # All on/off
        all_controls_layout = QHBoxLayout()
        
        self.all_on_btn = QPushButton("All On")
        self.all_on_btn.clicked.connect(self.all_devices_on)
        
        self.all_off_btn = QPushButton("All Off")
        self.all_off_btn.clicked.connect(self.all_devices_off)
        
        all_controls_layout.addWidget(self.all_on_btn)
        all_controls_layout.addWidget(self.all_off_btn)
        
        # Sync controls
        sync_layout = QHBoxLayout()
        
        sync_layout.addWidget(QLabel("Sync All:"))
        
        self.sync_color_btn = QPushButton("Sync Color")
        self.sync_color_btn.clicked.connect(self.sync_all_color)
        
        self.sync_pattern_btn = QPushButton("Sync Pattern")
        self.sync_pattern_btn.clicked.connect(self.sync_all_pattern)
        
        sync_layout.addWidget(self.sync_color_btn)
        sync_layout.addWidget(self.sync_pattern_btn)
        
        global_layout.addLayout(all_controls_layout)
        global_layout.addLayout(sync_layout)
        
        global_group.setLayout(global_layout)
        
        # Add all to panel
        layout.addWidget(discovery_group)
        layout.addWidget(devices_group, 1)  # Give most space to devices
        layout.addWidget(global_group)
        
        panel.setLayout(layout)
        return panel
    
    def create_right_panel(self):
        """Create the right panel with advanced features"""
        panel = QTabWidget()
        
        # Effects tab
        effects_tab = self.create_effects_tab()
        panel.addTab(effects_tab, "Effects & Scenes")
        
        # Scheduling tab
        scheduling_tab = self.create_scheduling_tab()
        panel.addTab(scheduling_tab, "Scheduling")
        
        # Statistics tab
        stats_tab = self.create_statistics_tab()
        panel.addTab(stats_tab, "Statistics")
        
        return panel
    
    def create_effects_tab(self):
        """Create the effects and scenes tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Preset scenes
        scenes_group = QGroupBox("Preset Scenes")
        scenes_layout = QGridLayout()
        
        scenes = [
            ("Party Mode", self.scene_party),
            ("Relaxation", self.scene_relax),
            ("Focus", self.scene_focus),
            ("Movie Night", self.scene_movie),
            ("Wake Up", self.scene_wake_up),
            ("Sleep", self.scene_sleep)
        ]
        
        for i, (name, callback) in enumerate(scenes):
            btn = QPushButton(name)
            btn.clicked.connect(callback)
            scenes_layout.addWidget(btn, i // 2, i % 2)
        
        scenes_group.setLayout(scenes_layout)
        
        # Custom effects
        effects_group = QGroupBox("Custom Effects")
        effects_layout = QVBoxLayout()
        
        # Effect selection
        effect_selection_layout = QHBoxLayout()
        
        effect_selection_layout.addWidget(QLabel("Effect:"))
        self.effect_combo = QComboBox()
        self.effect_combo.addItems(["solid", "gradient", "rainbow_wave", "sparkle", "comet", "pulse", "matrix"])
        
        self.apply_effect_btn = QPushButton("Apply to All")
        self.apply_effect_btn.clicked.connect(self.apply_custom_effect)
        
        effect_selection_layout.addWidget(self.effect_combo)
        effect_selection_layout.addWidget(self.apply_effect_btn)
        
        # Effect parameters
        params_layout = QGridLayout()
        
        params_layout.addWidget(QLabel("Speed:"), 0, 0)
        self.effect_speed = QSlider(Qt.Orientation.Horizontal)
        self.effect_speed.setRange(1, 100)
        self.effect_speed.setValue(50)
        params_layout.addWidget(self.effect_speed, 0, 1)
        
        params_layout.addWidget(QLabel("Brightness:"), 1, 0)
        self.effect_brightness = QSlider(Qt.Orientation.Horizontal)
        self.effect_brightness.setRange(10, 100)
        self.effect_brightness.setValue(100)
        params_layout.addWidget(self.effect_brightness, 1, 1)
        
        # Color selection for effects
        colors_layout = QHBoxLayout()
        
        self.effect_color1_btn = QPushButton("Color 1")
        self.effect_color1_btn.clicked.connect(lambda: self.choose_effect_color(1))
        self.effect_color1_btn.setStyleSheet("background-color: red;")
        
        self.effect_color2_btn = QPushButton("Color 2")
        self.effect_color2_btn.clicked.connect(lambda: self.choose_effect_color(2))
        self.effect_color2_btn.setStyleSheet("background-color: blue;")
        
        colors_layout.addWidget(self.effect_color1_btn)
        colors_layout.addWidget(self.effect_color2_btn)
        
        effects_layout.addLayout(effect_selection_layout)
        effects_layout.addLayout(params_layout)
        effects_layout.addLayout(colors_layout)
        
        effects_group.setLayout(effects_layout)
        
        # Scene management
        scene_mgmt_group = QGroupBox("Scene Management")
        scene_mgmt_layout = QVBoxLayout()
        
        # Save current scene
        save_layout = QHBoxLayout()
        
        self.scene_name_input = QTextEdit()
        self.scene_name_input.setMaximumHeight(30)
        self.scene_name_input.setPlaceholderText("Enter scene name...")
        
        self.save_scene_btn = QPushButton("Save Current Scene")
        self.save_scene_btn.clicked.connect(self.save_current_scene)
        
        save_layout.addWidget(self.scene_name_input)
        save_layout.addWidget(self.save_scene_btn)
        
        # Saved scenes list
        self.saved_scenes_list = QListWidget()
        self.load_saved_scenes()
        
        scene_buttons_layout = QHBoxLayout()
        
        self.load_scene_btn = QPushButton("Load Scene")
        self.load_scene_btn.clicked.connect(self.load_selected_scene)
        
        self.delete_scene_btn = QPushButton("Delete Scene")
        self.delete_scene_btn.clicked.connect(self.delete_selected_scene)
        
        scene_buttons_layout.addWidget(self.load_scene_btn)
        scene_buttons_layout.addWidget(self.delete_scene_btn)
        
        scene_mgmt_layout.addLayout(save_layout)
        scene_mgmt_layout.addWidget(self.saved_scenes_list)
        scene_mgmt_layout.addLayout(scene_buttons_layout)
        
        scene_mgmt_group.setLayout(scene_mgmt_layout)
        
        # Add all to tab
        layout.addWidget(scenes_group)
        layout.addWidget(effects_group)
        layout.addWidget(scene_mgmt_group)
        
        tab.setLayout(layout)
        return tab
    
    def create_scheduling_tab(self):
        """Create the scheduling tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Schedule creation
        create_group = QGroupBox("Create Schedule")
        create_layout = QGridLayout()
        
        create_layout.addWidget(QLabel("Schedule Name:"), 0, 0)
        self.schedule_name = QTextEdit()
        self.schedule_name.setMaximumHeight(30)
        create_layout.addWidget(self.schedule_name, 0, 1)
        
        create_layout.addWidget(QLabel("Time:"), 1, 0)
        self.schedule_time = QTimeEdit()
        self.schedule_time.setTime(QTime.currentTime())
        create_layout.addWidget(self.schedule_time, 1, 1)
        
        create_layout.addWidget(QLabel("Action:"), 2, 0)
        self.schedule_action = QComboBox()
        self.schedule_action.addItems(["Turn On", "Turn Off", "Set Scene", "Set Color", "Set Brightness"])
        create_layout.addWidget(self.schedule_action, 2, 1)
        
        # Days selection
        days_layout = QHBoxLayout()
        self.day_checkboxes = {}
        days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        
        for day in days:
            checkbox = QCheckBox(day[:3])
            self.day_checkboxes[day.lower()] = checkbox
            days_layout.addWidget(checkbox)
        
        create_layout.addWidget(QLabel("Days:"), 3, 0)
        create_layout.addLayout(days_layout, 3, 1)
        
        self.create_schedule_btn = QPushButton("Create Schedule")
        self.create_schedule_btn.clicked.connect(self.create_schedule)
        create_layout.addWidget(self.create_schedule_btn, 4, 1)
        
        create_group.setLayout(create_layout)
        
        # Active schedules
        schedules_group = QGroupBox("Active Schedules")
        schedules_layout = QVBoxLayout()
        
        self.schedules_table = QTableWidget()
        self.schedules_table.setColumnCount(5)
        self.schedules_table.setHorizontalHeaderLabels(["Name", "Time", "Days", "Action", "Enabled"])
        
        self.load_schedules()
        
        schedule_buttons_layout = QHBoxLayout()
        
        self.enable_schedule_btn = QPushButton("Toggle Enabled")
        self.enable_schedule_btn.clicked.connect(self.toggle_schedule_enabled)
        
        self.delete_schedule_btn = QPushButton("Delete Schedule")
        self.delete_schedule_btn.clicked.connect(self.delete_schedule)
        
        schedule_buttons_layout.addWidget(self.enable_schedule_btn)
        schedule_buttons_layout.addWidget(self.delete_schedule_btn)
        
        schedules_layout.addWidget(self.schedules_table)
        schedules_layout.addLayout(schedule_buttons_layout)
        
        schedules_group.setLayout(schedules_layout)
        
        # Add to tab
        layout.addWidget(create_group)
        layout.addWidget(schedules_group)
        
        tab.setLayout(layout)
        return tab
    
    def create_statistics_tab(self):
        """Create the statistics tab"""
        tab = QWidget()
        layout = QVBoxLayout()
        
        # Power consumption
        power_group = QGroupBox("Power Consumption")
        power_layout = QVBoxLayout()
        
        self.total_power_label = QLabel("Total Power: 0.0W")
        self.total_power_label.setStyleSheet("font-size: 16px; font-weight: bold;")
        
        self.power_breakdown = QTextEdit()
        self.power_breakdown.setMaximumHeight(150)
        self.power_breakdown.setReadOnly(True)
        
        power_layout.addWidget(self.total_power_label)
        power_layout.addWidget(self.power_breakdown)
        
        power_group.setLayout(power_layout)
        
        # Device status summary
        status_group = QGroupBox("Device Status")
        status_layout = QVBoxLayout()
        
        self.status_summary = QTextEdit()
        self.status_summary.setReadOnly(True)
        
        status_layout.addWidget(self.status_summary)
        status_group.setLayout(status_layout)
        
        # Update timer for statistics
        self.stats_timer = QTimer()
        self.stats_timer.timeout.connect(self.update_statistics)
        self.stats_timer.start(2000)  # Update every 2 seconds
        
        layout.addWidget(power_group)
        layout.addWidget(status_group)
        
        tab.setLayout(layout)
        return tab
    
    def connect_signals(self):
        """Connect signals from various components"""
        # Device manager signals
        self.device_manager.device_discovered.connect(self.add_discovered_device)
        self.device_manager.device_lost.connect(self.remove_device)
        
        # Scheduler signals
        self.scheduler.schedule_triggered.connect(self.handle_schedule_trigger)
    
    @pyqtSlot(dict)
    def add_discovered_device(self, device_info):
        """Add a newly discovered device"""
        device_id = device_info['device_id']
        
        if device_id not in self.led_devices:
            # Create LED device instance
            led_device = LEDDevice(
                device_id=device_id,
                name=device_info.get('name', f'Device {device_id}'),
                led_count=device_info.get('led_count', 60)
            )
            
            self.led_devices[device_id] = led_device
            
            # Create control widget
            control_widget = DeviceControlWidget(device_id, device_info, led_device)
            self.device_widgets[device_id] = control_widget
            
            # Add to device container
            self.devices_container_layout.addWidget(control_widget)
            
            # Add device to manager
            self.device_manager.add_device(device_info)
            
            print(f"Added device: {device_info['name']} ({device_id})")
    
    def remove_device(self, device_id):
        """Remove a device"""
        if device_id in self.device_widgets:
            widget = self.device_widgets[device_id]
            self.devices_container_layout.removeWidget(widget)
            widget.deleteLater()
            del self.device_widgets[device_id]
        
        if device_id in self.led_devices:
            self.led_devices[device_id].disconnect_device()
            del self.led_devices[device_id]
    
    def toggle_discovery(self):
        """Toggle device discovery"""
        if self.discovery_btn.text() == "Start Discovery":
            self.device_manager.start_discovery()
            self.discovery_btn.setText("Stop Discovery")
        else:
            self.device_manager.stop_discovery()
            self.discovery_btn.setText("Start Discovery")
    
    def add_manual_device(self):
        """Add a device manually"""
        name, ok = QInputDialog.getText(self, "Add Device", "Enter device name:")
        if ok and name:
            device_info = {
                'device_id': f'manual_{len(self.led_devices)}',
                'name': name,
                'ip_address': '192.168.1.200',
                'mac_address': 'AA:BB:CC:DD:EE:FF',
                'model': 'Manual',
                'led_count': 60,
                'firmware_version': '1.0.0'
            }
            self.add_discovered_device(device_info)
    
    def refresh_all_devices(self):
        """Refresh all device connections"""
        for device_id, led_device in self.led_devices.items():
            if led_device.is_connected:
                led_device.emit_status_update()
    
    def all_devices_on(self):
        """Turn on all connected devices"""
        for led_device in self.led_devices.values():
            if led_device.is_connected and not led_device.is_on:
                led_device.power_on()
    
    def all_devices_off(self):
        """Turn off all connected devices"""
        for led_device in self.led_devices.values():
            if led_device.is_connected and led_device.is_on:
                led_device.power_off()
    
    def sync_all_color(self):
        """Sync color across all devices"""
        if not self.led_devices:
            return
        
        # Get color from first device or choose new one
        color = QColorDialog.getColor(QColor(255, 255, 255), self)
        if color.isValid():
            r, g, b, _ = color.getRgb()
            for led_device in self.led_devices.values():
                if led_device.is_connected and led_device.is_on:
                    led_device.set_color(r, g, b)
    
    def sync_all_pattern(self):
        """Sync pattern across all devices"""
        patterns = ["solid", "rainbow", "breathing", "strobe", "chase", "fire"]
        pattern, ok = QInputDialog.getItem(self, "Sync Pattern", "Choose pattern:", patterns, 0, False)
        
        if ok and pattern:
            for led_device in self.led_devices.values():
                if led_device.is_connected and led_device.is_on:
                    led_device.set_pattern(pattern)
    
    # Scene methods
    def scene_party(self):
        """Apply party scene"""
        colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (255, 0, 255)]
        for i, led_device in enumerate(self.led_devices.values()):
            if led_device.is_connected:
                if not led_device.is_on:
                    led_device.power_on()
                color = colors[i % len(colors)]
                led_device.set_color(*color)
                led_device.set_pattern("strobe", 80)
                led_device.set_brightness(100)
    
    def scene_relax(self):
        """Apply relaxation scene"""
        for led_device in self.led_devices.values():
            if led_device.is_connected:
                if not led_device.is_on:
                    led_device.power_on()
                led_device.set_color(100, 150, 255)  # Soft blue
                led_device.set_pattern("breathing", 20)
                led_device.set_brightness(40)
    
    def scene_focus(self):
        """Apply focus scene"""
        for led_device in self.led_devices.values():
            if led_device.is_connected:
                if not led_device.is_on:
                    led_device.power_on()
                led_device.set_color(255, 255, 255)  # White
                led_device.set_pattern("solid")
                led_device.set_brightness(85)
    
    def scene_movie(self):
        """Apply movie night scene"""
        for led_device in self.led_devices.values():
            if led_device.is_connected:
                if not led_device.is_on:
                    led_device.power_on()
                led_device.set_color(128, 0, 128)  # Purple
                led_device.set_pattern("solid")
                led_device.set_brightness(20)
    
    def scene_wake_up(self):
        """Apply wake up scene"""
        for led_device in self.led_devices.values():
            if led_device.is_connected:
                if not led_device.is_on:
                    led_device.power_on()
                led_device.set_color(255, 200, 100)  # Warm white
                led_device.set_pattern("breathing", 30)
                led_device.set_brightness(70)
    
    def scene_sleep(self):
        """Apply sleep scene"""
        for led_device in self.led_devices.values():
            if led_device.is_connected and led_device.is_on:
                led_device.power_off()
    
    def apply_custom_effect(self):
        """Apply custom effect to all devices"""
        effect_config = {
            'type': self.effect_combo.currentText(),
            'speed': self.effect_speed.value(),
            'brightness': self.effect_brightness.value(),
            'colors': [(255, 0, 0), (0, 0, 255)]  # Default colors
        }
        
        for device_id, led_device in self.led_devices.items():
            if led_device.is_connected and led_device.is_on:
                effect_config['led_count'] = led_device.led_count
                self.effects_engine.add_effect(device_id, effect_config)
    
    def choose_effect_color(self, color_num):
        """Choose color for effects"""
        color = QColorDialog.getColor(QColor(255, 0, 0 if color_num == 1 else 255), self)
        if color.isValid():
            r, g, b, _ = color.getRgb()
            btn = self.effect_color1_btn if color_num == 1 else self.effect_color2_btn
            btn.setStyleSheet(f"background-color: rgb({r}, {g}, {b});")
    
    def save_current_scene(self):
        """Save current device states as a scene"""
        scene_name = self.scene_name_input.toPlainText().strip()
        if not scene_name:
            QMessageBox.warning(self, "Error", "Please enter a scene name.")
            return
        
        scene_data = {}
        for device_id, led_device in self.led_devices.items():
            if led_device.is_connected:
                scene_data[device_id] = {
                    'powered_on': led_device.is_on,
                    'brightness': led_device.brightness,
                    'color': led_device.current_color,
                    'pattern': led_device.current_pattern,
                    'pattern_speed': led_device.pattern_speed
                }
        
        preset = self.device_manager.create_device_preset(scene_name, scene_data)
        self.load_saved_scenes()
        
        QMessageBox.information(self, "Success", f"Scene '{scene_name}' saved successfully!")
    
    def load_saved_scenes(self):
        """Load saved scenes into the list"""
        self.saved_scenes_list.clear()
        presets = self.device_manager.load_device_presets()
        
        for preset_name in presets.keys():
            self.saved_scenes_list.addItem(preset_name)
    
    def load_selected_scene(self):
        """Load the selected scene"""
        current_item = self.saved_scenes_list.currentItem()
        if not current_item:
            return
        
        scene_name = current_item.text()
        scene_data = self.device_manager.apply_preset(scene_name)
        
        for device_id, config in scene_data.items():
            if device_id in self.led_devices:
                led_device = self.led_devices[device_id]
                if led_device.is_connected:
                    if config.get('powered_on', False):
                        if not led_device.is_on:
                            led_device.power_on()
                        led_device.set_brightness(config.get('brightness', 100))
                        led_device.set_color(*config.get('color', (255, 255, 255)))
                        led_device.set_pattern(
                            config.get('pattern', 'solid'),
                            config.get('pattern_speed', 50)
                        )
                    else:
                        led_device.power_off()
    
    def delete_selected_scene(self):
        """Delete the selected scene"""
        current_item = self.saved_scenes_list.currentItem()
        if not current_item:
            return
        
        scene_name = current_item.text()
        reply = QMessageBox.question(self, "Delete Scene", f"Delete scene '{scene_name}'?")
        
        if reply == QMessageBox.StandardButton.Yes:
            # Remove from file (would need to implement in device_manager)
            self.load_saved_scenes()
    
    def create_schedule(self):
        """Create a new schedule"""
        name = self.schedule_name.toPlainText().strip()
        if not name:
            QMessageBox.warning(self, "Error", "Please enter a schedule name.")
            return
        
        time_str = self.schedule_time.time().toString("HH:mm")
        action_type = self.schedule_action.currentText()
        
        # Get selected days
        selected_days = []
        for day_name, checkbox in self.day_checkboxes.items():
            if checkbox.isChecked():
                selected_days.append(day_name)
        
        if not selected_days:
            QMessageBox.warning(self, "Error", "Please select at least one day.")
            return
        
        # Create action config
        action_config = {'type': action_type.lower().replace(' ', '_')}
        
        # Create schedule
        schedule_id = self.scheduler.create_time_schedule(
            name=name,
            time_str=time_str,
            days=selected_days,
            action=action_config,
            devices=list(self.led_devices.keys())
        )
        
        self.load_schedules()
        QMessageBox.information(self, "Success", f"Schedule '{name}' created successfully!")
    
    def load_schedules(self):
        """Load schedules into the table"""
        schedules = self.scheduler.get_schedules()
        
        self.schedules_table.setRowCount(len(schedules))
        
        for row, (schedule_id, schedule) in enumerate(schedules.items()):
            self.schedules_table.setItem(row, 0, QTableWidgetItem(schedule.get('name', 'Unknown')))
            self.schedules_table.setItem(row, 1, QTableWidgetItem(schedule.get('time', 'Unknown')))
            self.schedules_table.setItem(row, 2, QTableWidgetItem(', '.join(schedule.get('days', []))))
            self.schedules_table.setItem(row, 3, QTableWidgetItem(schedule.get('action', {}).get('type', 'Unknown')))
            
            enabled_item = QTableWidgetItem("Yes" if schedule.get('enabled', True) else "No")
            self.schedules_table.setItem(row, 4, enabled_item)
            
            # Store schedule ID in first column for reference
            self.schedules_table.item(row, 0).setData(Qt.ItemDataRole.UserRole, schedule_id)
    
    def toggle_schedule_enabled(self):
        """Toggle enabled state of selected schedule"""
        current_row = self.schedules_table.currentRow()
        if current_row >= 0:
            schedule_id_item = self.schedules_table.item(current_row, 0)
            if schedule_id_item:
                schedule_id = schedule_id_item.data(Qt.ItemDataRole.UserRole)
                # Toggle in scheduler
                schedules = self.scheduler.get_schedules()
                if schedule_id in schedules:
                    current_state = schedules[schedule_id].get('enabled', True)
                    self.scheduler.enable_schedule(schedule_id, not current_state)
                    self.load_schedules()
    
    def delete_schedule(self):
        """Delete selected schedule"""
        current_row = self.schedules_table.currentRow()
        if current_row >= 0:
            schedule_id_item = self.schedules_table.item(current_row, 0)
            if schedule_id_item:
                schedule_id = schedule_id_item.data(Qt.ItemDataRole.UserRole)
                schedule_name = schedule_id_item.text()
                
                reply = QMessageBox.question(self, "Delete Schedule", f"Delete schedule '{schedule_name}'?")
                if reply == QMessageBox.StandardButton.Yes:
                    self.scheduler.remove_schedule(schedule_id)
                    self.load_schedules()
    
    @pyqtSlot(str, dict)
    def handle_schedule_trigger(self, schedule_id, action):
        """Handle triggered schedule"""
        action_type = action.get('type', '')
        
        if action_type == 'turn_on':
            self.all_devices_on()
        elif action_type == 'turn_off':
            self.all_devices_off()
        elif action_type == 'set_scene':
            scene_name = action.get('scene_name', '')
            if scene_name:
                # Load scene (would need scene name in action config)
                pass
        # Add more action types as needed
        
        print(f"Schedule triggered: {schedule_id}, action: {action}")
    
    def update_statistics(self):
        """Update statistics display"""
        total_power = 0.0
        device_status = []
        connected_count = 0
        powered_on_count = 0
        
        breakdown_text = "Device Power Breakdown:\\n"
        status_text = "Device Status Summary:\\n\\n"
        
        for device_id, led_device in self.led_devices.items():
            device_info = self.device_manager.get_device_info(device_id)
            device_name = device_info.get('name', device_id)
            
            if led_device.is_connected:
                connected_count += 1
                if led_device.is_on:
                    powered_on_count += 1
                    total_power += led_device.power_consumption
                    breakdown_text += f"  {device_name}: {led_device.power_consumption:.1f}W\\n"
                else:
                    breakdown_text += f"  {device_name}: 0.0W (off)\\n"
                
                status_text += f"📱 {device_name}\\n"
                status_text += f"   Status: {'🟢 Online' if led_device.is_connected else '🔴 Offline'}\\n"
                status_text += f"   Power: {'🟢 On' if led_device.is_on else '⚫ Off'}\\n"
                status_text += f"   Pattern: {led_device.current_pattern}\\n"
                status_text += f"   Brightness: {led_device.brightness}%\\n\\n"
            else:
                breakdown_text += f"  {device_name}: Disconnected\\n"
                status_text += f"📱 {device_name}: 🔴 Disconnected\\n\\n"
        
        # Update displays
        self.total_power_label.setText(f"Total Power: {total_power:.1f}W")
        
        breakdown_text += f"\\nTotal Devices: {len(self.led_devices)}\\n"
        breakdown_text += f"Connected: {connected_count}\\n"
        breakdown_text += f"Powered On: {powered_on_count}"
        
        self.power_breakdown.setText(breakdown_text)
        self.status_summary.setText(status_text)
    
    def closeEvent(self, event):
        """Handle application close"""
        # Stop all devices
        for led_device in self.led_devices.values():
            if led_device.is_connected:
                led_device.disconnect_device()
        
        # Stop discovery
        self.device_manager.stop_discovery()
        
        event.accept()

def main():
    app = QApplication(sys.argv)
    
    # Set application properties
    app.setApplicationName("Smart LED Controller")
    app.setApplicationVersion("1.0")
    app.setOrganizationName("IoT Solutions")
    
    controller = LEDControllerApp()
    controller.show()
    
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
```

## Key Features Demonstrated

### Advanced Device Control
- Individual LED device management
- Real-time LED strip preview
- Multiple pattern and effect support
- Color picker integration
- Brightness and speed controls

### Effects Engine
- Custom effect patterns (rainbow, breathing, strobe, etc.)
- Real-time effect preview
- Configurable effect parameters
- Multi-color effects support

### Scene Management
- Preset scene buttons
- Save/load custom scenes
- Scene synchronization across devices
- Scene configuration persistence

### Scheduling System
- Time-based scheduling
- Day-of-week selection
- Schedule enable/disable functionality
- Automated scene activation

### Device Management
- Automatic device discovery simulation
- Manual device addition
- Device connection status monitoring
- Network information display

### Statistics and Monitoring
- Real-time power consumption tracking
- Device status summaries
- Connection monitoring
- Performance statistics

## Extension Ideas

1. **Real Hardware Integration**: Connect to actual LED controllers via WiFi/Bluetooth
2. **Music Visualization**: Sync LED effects with audio input
3. **Web Interface**: Add REST API for remote control
4. **Mobile App**: Create companion mobile application
5. **Voice Control**: Add voice command support
6. **Advanced Effects**: Implement more complex visual effects
7. **Energy Management**: Add power usage optimization
8. **Integration**: Connect with smart home systems

## What's Next?

In the next tutorial, we'll build:
- Temperature Monitoring System
- Environmental sensor integration
- Alerts and notifications
- Data visualization and analytics

This project demonstrates advanced PyQt6 techniques including custom widgets, real-time updates, complex layouts, and sophisticated device simulation. It serves as a foundation for building professional IoT control applications.

Ready to monitor environmental data? Let's move to Tutorial 10!