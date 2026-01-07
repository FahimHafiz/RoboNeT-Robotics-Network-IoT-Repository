<div align="center">
  <img width="659" alt="Image" src="https://github.com/user-attachments/assets/5c8d7a11-51a1-4184-bf30-c8d81373ee44" />
</div>
# IoT Project 3: Environmental Monitoring System

## Introduction

In this final tutorial, we'll build a comprehensive environmental monitoring system that combines multiple sensors, data logging, alerting, and visualization. This project demonstrates advanced IoT concepts including multi-sensor integration, real-time graphing, threshold monitoring, and automated reporting.

## Project Overview

Our Environmental Monitoring System will include:
- Multi-sensor data collection (temperature, humidity, pressure, air quality, light)
- Real-time data visualization with charts and graphs
- Threshold-based alerting system
- Historical data analysis and reporting
- Data export and backup functionality
- Remote monitoring capabilities
- Automated report generation

## Project Structure

Create a new folder `environmental_monitor` with these files:
- `environmental_monitor.py` - Main application
- `sensor_network.py` - Multi-sensor management
- `data_visualization.py` - Charts and graphs
- `alert_system.py` - Threshold monitoring and alerts
- `report_generator.py` - Automated reporting
- `database_manager.py` - Data persistence
- `config_manager.py` - Configuration management

## Step 1: Sensor Network and Data Management

### sensor_network.py

```python
import random
import math
import json
import sqlite3
from datetime import datetime, timedelta
from PyQt6.QtCore import QThread, QTimer, QObject, pyqtSignal
from PyQt6.QtWidgets import QMessageBox

class SensorNode(QObject):
    """Represents a single sensor node with multiple sensors"""
    
    data_received = pyqtSignal(str, dict)  # node_id, sensor_data
    node_status_changed = pyqtSignal(str, str)  # node_id, status
    
    def __init__(self, node_id, name, location, sensors):
        super().__init__()
        self.node_id = node_id
        self.name = name
        self.location = location
        self.sensors = sensors  # List of sensor types
        
        # Node status
        self.is_online = False
        self.battery_level = 100
        self.signal_strength = -65  # dBm
        self.last_update = None
        
        # Sensor readings
        self.current_readings = {}
        
        # Sensor characteristics for realistic simulation
        self.sensor_configs = {
            'temperature': {'min': -10, 'max': 45, 'unit': '°C', 'precision': 0.1},
            'humidity': {'min': 20, 'max': 95, 'unit': '%', 'precision': 0.5},
            'pressure': {'min': 980, 'max': 1050, 'unit': 'hPa', 'precision': 0.1},
            'air_quality': {'min': 0, 'max': 500, 'unit': 'AQI', 'precision': 1},
            'light': {'min': 0, 'max': 100000, 'unit': 'lux', 'precision': 1},
            'noise': {'min': 30, 'max': 120, 'unit': 'dB', 'precision': 0.1},
            'co2': {'min': 400, 'max': 5000, 'unit': 'ppm', 'precision': 1},
            'pm25': {'min': 0, 'max': 500, 'unit': 'μg/m³', 'precision': 0.1}
        }
        
        # Initialize sensor states for realistic simulation
        self.sensor_states = {}
        for sensor in self.sensors:
            if sensor in self.sensor_configs:
                config = self.sensor_configs[sensor]
                mid_range = (config['min'] + config['max']) / 2
                self.sensor_states[sensor] = {
                    'value': mid_range,
                    'trend': 0.0,
                    'last_change': datetime.now()
                }
        
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.update_readings)
    
    def connect_node(self):
        """Connect the sensor node"""
        self.is_online = True
        self.node_status_changed.emit(self.node_id, "online")
        self.update_timer.start(5000)  # Update every 5 seconds
        
    def disconnect_node(self):
        """Disconnect the sensor node"""
        self.is_online = False
        self.node_status_changed.emit(self.node_id, "offline")
        self.update_timer.stop()
    
    def update_readings(self):
        """Generate and emit new sensor readings"""
        if not self.is_online:
            return
        
        timestamp = datetime.now()
        self.last_update = timestamp
        
        # Simulate battery drain
        if self.battery_level > 0:
            self.battery_level -= random.uniform(0.01, 0.05)
            self.battery_level = max(0, self.battery_level)
        
        # Update sensor readings
        readings = {}
        for sensor in self.sensors:
            if sensor in self.sensor_states:
                reading = self.simulate_sensor_reading(sensor)
                readings[sensor] = reading
        
        # Add node metadata
        node_data = {
            'timestamp': timestamp.isoformat(),
            'node_id': self.node_id,
            'name': self.name,
            'location': self.location,
            'battery_level': self.battery_level,
            'signal_strength': self.signal_strength,
            'readings': readings
        }
        
        self.current_readings = readings
        self.data_received.emit(self.node_id, node_data)
        
        # Simulate occasional connection issues
        if random.random() < 0.02:  # 2% chance of temporary disconnection
            self.simulate_connection_issue()
    
    def simulate_sensor_reading(self, sensor_type):
        """Simulate realistic sensor reading"""
        if sensor_type not in self.sensor_states:
            return None
        
        state = self.sensor_states[sensor_type]
        config = self.sensor_configs[sensor_type]
        
        # Environmental factors simulation
        hour = datetime.now().hour
        
        if sensor_type == 'temperature':
            # Daily temperature cycle
            daily_factor = 5 * math.sin((hour - 6) * math.pi / 12)
            base_change = daily_factor * 0.1
            
            # Random walk with trend
            if random.random() < 0.1:  # 10% chance to change trend
                state['trend'] = random.uniform(-0.2, 0.2)
            
            change = base_change + state['trend'] + random.uniform(-0.5, 0.5)
            
        elif sensor_type == 'humidity':
            # Inverse correlation with temperature
            temp_influence = -0.5 if 'temperature' in self.current_readings else 0
            change = temp_influence + state['trend'] + random.uniform(-2, 2)
            
            if random.random() < 0.08:
                state['trend'] = random.uniform(-0.3, 0.3)
        
        elif sensor_type == 'pressure':
            # Slow changes in atmospheric pressure
            change = state['trend'] + random.uniform(-0.3, 0.3)
            
            if random.random() < 0.05:
                state['trend'] = random.uniform(-0.1, 0.1)
        
        elif sensor_type == 'air_quality':
            # Rush hour and weather effects
            if 7 <= hour <= 9 or 17 <= hour <= 19:  # Rush hours
                pollution_factor = random.uniform(10, 30)
            else:
                pollution_factor = random.uniform(-5, 5)
            
            change = pollution_factor * 0.1 + state['trend'] + random.uniform(-5, 5)
            
            if random.random() < 0.12:
                state['trend'] = random.uniform(-2, 2)
        
        elif sensor_type == 'light':
            # Day/night cycle
            if 6 <= hour <= 18:  # Daytime
                target = 20000 + 30000 * math.sin((hour - 6) * math.pi / 12)
                if random.random() < 0.3:  # Cloud cover
                    target *= 0.3
            else:  # Nighttime
                target = random.uniform(0, 100)
            
            # Move towards target
            current_value = state['value']
            change = (target - current_value) * 0.1 + random.uniform(-1000, 1000)
        
        elif sensor_type == 'noise':
            # Urban noise patterns
            if 6 <= hour <= 22:  # Day time
                base_level = 55 + random.uniform(-5, 15)
            else:  # Night time
                base_level = 35 + random.uniform(-5, 10)
            
            change = (base_level - state['value']) * 0.2 + random.uniform(-2, 2)
        
        elif sensor_type == 'co2':
            # Indoor CO2 simulation
            occupancy_factor = 1.0
            if 9 <= hour <= 17:  # Work hours
                occupancy_factor = 3.0
            elif 18 <= hour <= 22:  # Evening
                occupancy_factor = 2.0
            
            target = 400 + occupancy_factor * 200
            change = (target - state['value']) * 0.05 + random.uniform(-10, 10)
        
        elif sensor_type == 'pm25':
            # PM2.5 pollution simulation
            base_level = 15  # μg/m³
            if 7 <= hour <= 9 or 17 <= hour <= 19:  # Rush hours
                base_level = 35
            
            weather_factor = random.uniform(0.5, 2.0)  # Wind/rain effects
            change = (base_level * weather_factor - state['value']) * 0.1 + random.uniform(-2, 2)
        
        else:
            # Generic sensor simulation
            change = state['trend'] + random.uniform(-1, 1)
            if random.random() < 0.1:
                state['trend'] = random.uniform(-0.5, 0.5)
        
        # Apply change
        state['value'] += change
        
        # Keep within bounds
        state['value'] = max(config['min'], min(config['max'], state['value']))
        
        # Round to precision
        precision = config['precision']
        if precision >= 1:
            value = round(state['value'])
        else:
            decimals = len(str(precision).split('.')[-1])
            value = round(state['value'], decimals)
        
        return {
            'value': value,
            'unit': config['unit'],
            'timestamp': datetime.now().isoformat(),
            'quality': random.choice(['good', 'good', 'good', 'fair', 'poor'])  # Mostly good readings
        }
    
    def simulate_connection_issue(self):
        """Simulate temporary connection issues"""
        self.signal_strength = random.randint(-90, -70)
        
        # Brief disconnection
        QTimer.singleShot(random.randint(2000, 8000), self.recover_connection)
        self.node_status_changed.emit(self.node_id, "connection_issue")
    
    def recover_connection(self):
        """Recover from connection issue"""
        self.signal_strength = random.randint(-65, -45)
        self.node_status_changed.emit(self.node_id, "recovered")

class SensorNetwork(QObject):
    """Manages a network of sensor nodes"""
    
    network_data_received = pyqtSignal(dict)  # aggregated network data
    node_added = pyqtSignal(str)  # node_id
    node_removed = pyqtSignal(str)  # node_id
    network_status_changed = pyqtSignal(str)  # network status
    
    def __init__(self):
        super().__init__()
        self.nodes = {}
        self.network_config = self.load_network_config()
        self.is_active = False
        
        # Data aggregation
        self.latest_data = {}
        self.data_history = {}  # node_id -> list of readings
        
        # Network statistics
        self.total_packets_received = 0
        self.packet_loss_rate = 0.0
        self.average_signal_strength = 0.0
    
    def load_network_config(self):
        """Load network configuration"""
        default_config = {
            "nodes": [
                {
                    "node_id": "ENV001",
                    "name": "Living Room Monitor",
                    "location": "Living Room",
                    "sensors": ["temperature", "humidity", "co2", "light", "noise"]
                },
                {
                    "node_id": "ENV002", 
                    "name": "Outdoor Weather Station",
                    "location": "Garden",
                    "sensors": ["temperature", "humidity", "pressure", "light", "pm25"]
                },
                {
                    "node_id": "ENV003",
                    "name": "Office Air Quality Monitor", 
                    "location": "Home Office",
                    "sensors": ["temperature", "humidity", "co2", "air_quality", "noise"]
                },
                {
                    "node_id": "ENV004",
                    "name": "Bedroom Climate Sensor",
                    "location": "Master Bedroom", 
                    "sensors": ["temperature", "humidity", "light", "noise"]
                },
                {
                    "node_id": "ENV005",
                    "name": "Kitchen Environment Monitor",
                    "location": "Kitchen",
                    "sensors": ["temperature", "humidity", "air_quality", "co2"]
                }
            ]
        }
        
        try:
            with open('network_config.json', 'r') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            with open('network_config.json', 'w') as f:
                json.dump(default_config, f, indent=2)
            return default_config
    
    def initialize_network(self):
        """Initialize all sensor nodes from configuration"""
        for node_config in self.network_config.get('nodes', []):
            self.add_sensor_node(
                node_config['node_id'],
                node_config['name'], 
                node_config['location'],
                node_config['sensors']
            )
        
        self.network_status_changed.emit("initialized")
    
    def add_sensor_node(self, node_id, name, location, sensors):
        """Add a new sensor node to the network"""
        if node_id in self.nodes:
            return False
        
        node = SensorNode(node_id, name, location, sensors)
        node.data_received.connect(self.handle_node_data)
        node.node_status_changed.connect(self.handle_node_status)
        
        self.nodes[node_id] = node
        self.data_history[node_id] = []
        
        self.node_added.emit(node_id)
        return True
    
    def remove_sensor_node(self, node_id):
        """Remove a sensor node from the network"""
        if node_id in self.nodes:
            self.nodes[node_id].disconnect_node()
            del self.nodes[node_id]
            
            if node_id in self.data_history:
                del self.data_history[node_id]
            
            self.node_removed.emit(node_id)
            return True
        return False
    
    def start_network(self):
        """Start the sensor network"""
        self.is_active = True
        
        for node in self.nodes.values():
            node.connect_node()
        
        self.network_status_changed.emit("active")
    
    def stop_network(self):
        """Stop the sensor network"""
        self.is_active = False
        
        for node in self.nodes.values():
            node.disconnect_node()
        
        self.network_status_changed.emit("inactive")
    
    def handle_node_data(self, node_id, node_data):
        """Handle data received from a sensor node"""
        self.latest_data[node_id] = node_data
        
        # Add to history (keep last 1000 readings per node)
        if node_id in self.data_history:
            self.data_history[node_id].append(node_data)
            if len(self.data_history[node_id]) > 1000:
                self.data_history[node_id].pop(0)
        
        # Update network statistics
        self.total_packets_received += 1
        
        # Calculate average signal strength
        signal_strengths = [data.get('signal_strength', -100) 
                          for data in self.latest_data.values()]
        if signal_strengths:
            self.average_signal_strength = sum(signal_strengths) / len(signal_strengths)
        
        # Emit aggregated network data
        self.emit_network_data()
    
    def handle_node_status(self, node_id, status):
        """Handle node status changes"""
        print(f"Node {node_id} status: {status}")
        
        # Update packet loss calculation
        if status == "connection_issue":
            # Simulate packet loss
            pass
    
    def emit_network_data(self):
        """Emit aggregated network data"""
        network_summary = {
            'timestamp': datetime.now().isoformat(),
            'nodes_online': sum(1 for node in self.nodes.values() if node.is_online),
            'total_nodes': len(self.nodes),
            'total_packets': self.total_packets_received,
            'average_signal_strength': self.average_signal_strength,
            'node_data': dict(self.latest_data)
        }
        
        self.network_data_received.emit(network_summary)
    
    def get_node_history(self, node_id, hours=24):
        """Get historical data for a specific node"""
        if node_id not in self.data_history:
            return []
        
        cutoff_time = datetime.now() - timedelta(hours=hours)
        history = []
        
        for data_point in self.data_history[node_id]:
            timestamp_str = data_point.get('timestamp', '')
            try:
                timestamp = datetime.fromisoformat(timestamp_str)
                if timestamp >= cutoff_time:
                    history.append(data_point)
            except ValueError:
                continue
        
        return history
    
    def get_sensor_statistics(self, sensor_type, hours=24):
        """Get statistics for a specific sensor type across all nodes"""
        values = []
        
        for node_id in self.nodes:
            history = self.get_node_history(node_id, hours)
            for data_point in history:
                readings = data_point.get('readings', {})
                if sensor_type in readings:
                    value = readings[sensor_type].get('value')
                    if value is not None:
                        values.append(value)
        
        if not values:
            return None
        
        return {
            'count': len(values),
            'min': min(values),
            'max': max(values),
            'average': sum(values) / len(values),
            'latest': values[-1] if values else None
        }
    
    def export_network_data(self, filename, hours=24):
        """Export network data to JSON file"""
        export_data = {
            'export_info': {
                'timestamp': datetime.now().isoformat(),
                'hours_included': hours,
                'total_nodes': len(self.nodes)
            },
            'nodes': {}
        }
        
        for node_id in self.nodes:
            node_info = self.nodes[node_id]
            export_data['nodes'][node_id] = {
                'info': {
                    'name': node_info.name,
                    'location': node_info.location,
                    'sensors': node_info.sensors
                },
                'history': self.get_node_history(node_id, hours)
            }
        
        try:
            with open(filename, 'w') as f:
                json.dump(export_data, f, indent=2)
            return True
        except Exception as e:
            print(f"Export failed: {e}")
            return False
```

### database_manager.py

```python
import sqlite3
import json
from datetime import datetime, timedelta
from PyQt6.QtCore import QThread, pyqtSignal

class DatabaseManager(QThread):
    """Manages SQLite database for sensor data storage"""
    
    data_saved = pyqtSignal(int)  # number of records saved
    database_error = pyqtSignal(str)  # error message
    
    def __init__(self, db_path="sensor_data.db"):
        super().__init__()
        self.db_path = db_path
        self.data_queue = []
        self.running = False
        
        self.init_database()
    
    def init_database(self):
        """Initialize database tables"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            # Create sensor_readings table
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS sensor_readings (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    timestamp TEXT NOT NULL,
                    node_id TEXT NOT NULL,
                    node_name TEXT,
                    location TEXT,
                    sensor_type TEXT NOT NULL,
                    value REAL NOT NULL,
                    unit TEXT,
                    quality TEXT,
                    battery_level REAL,
                    signal_strength REAL,
                    created_at TEXT DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Create sensor_nodes table
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS sensor_nodes (
                    node_id TEXT PRIMARY KEY,
                    name TEXT NOT NULL,
                    location TEXT,
                    sensors TEXT,  -- JSON list of sensor types
                    last_seen TEXT,
                    status TEXT,
                    created_at TEXT DEFAULT CURRENT_TIMESTAMP,
                    updated_at TEXT DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Create alerts table
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS alerts (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    timestamp TEXT NOT NULL,
                    node_id TEXT,
                    sensor_type TEXT,
                    alert_type TEXT,
                    threshold_value REAL,
                    actual_value REAL,
                    message TEXT,
                    acknowledged BOOLEAN DEFAULT FALSE,
                    created_at TEXT DEFAULT CURRENT_TIMESTAMP
                )
            ''')
            
            # Create indexes for better performance
            cursor.execute('CREATE INDEX IF NOT EXISTS idx_readings_timestamp ON sensor_readings(timestamp)')
            cursor.execute('CREATE INDEX IF NOT EXISTS idx_readings_node_sensor ON sensor_readings(node_id, sensor_type)')
            cursor.execute('CREATE INDEX IF NOT EXISTS idx_alerts_timestamp ON alerts(timestamp)')
            
            conn.commit()
            conn.close()
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Database initialization error: {str(e)}")
    
    def add_data_to_queue(self, node_data):
        """Add node data to the processing queue"""
        self.data_queue.append(node_data)
    
    def run(self):
        """Main database processing thread"""
        self.running = True
        
        while self.running:
            if self.data_queue:
                batch = self.data_queue.copy()
                self.data_queue.clear()
                
                records_saved = self.save_batch_data(batch)
                if records_saved > 0:
                    self.data_saved.emit(records_saved)
            
            self.msleep(1000)  # Check every second
    
    def save_batch_data(self, batch_data):
        """Save a batch of sensor data to database"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            records_saved = 0
            
            for node_data in batch_data:
                node_id = node_data.get('node_id')
                timestamp = node_data.get('timestamp')
                name = node_data.get('name')
                location = node_data.get('location')
                battery_level = node_data.get('battery_level')
                signal_strength = node_data.get('signal_strength')
                readings = node_data.get('readings', {})
                
                # Update node information
                cursor.execute('''
                    INSERT OR REPLACE INTO sensor_nodes 
                    (node_id, name, location, sensors, last_seen, status, updated_at)
                    VALUES (?, ?, ?, ?, ?, ?, ?)
                ''', (
                    node_id, name, location, 
                    json.dumps(list(readings.keys())),
                    timestamp, 'online',
                    datetime.now().isoformat()
                ))
                
                # Insert sensor readings
                for sensor_type, reading in readings.items():
                    cursor.execute('''
                        INSERT INTO sensor_readings
                        (timestamp, node_id, node_name, location, sensor_type, 
                         value, unit, quality, battery_level, signal_strength)
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                    ''', (
                        timestamp, node_id, name, location, sensor_type,
                        reading.get('value'), reading.get('unit'),
                        reading.get('quality'), battery_level, signal_strength
                    ))
                    records_saved += 1
            
            conn.commit()
            conn.close()
            
            return records_saved
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Database save error: {str(e)}")
            return 0
    
    def get_recent_readings(self, node_id=None, sensor_type=None, hours=24):
        """Get recent sensor readings"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cutoff_time = (datetime.now() - timedelta(hours=hours)).isoformat()
            
            query = '''
                SELECT timestamp, node_id, node_name, location, sensor_type, 
                       value, unit, quality, battery_level, signal_strength
                FROM sensor_readings 
                WHERE timestamp >= ?
            '''
            params = [cutoff_time]
            
            if node_id:
                query += ' AND node_id = ?'
                params.append(node_id)
            
            if sensor_type:
                query += ' AND sensor_type = ?'
                params.append(sensor_type)
            
            query += ' ORDER BY timestamp DESC'
            
            cursor.execute(query, params)
            
            columns = [desc[0] for desc in cursor.description]
            results = []
            
            for row in cursor.fetchall():
                record = dict(zip(columns, row))
                results.append(record)
            
            conn.close()
            return results
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Database query error: {str(e)}")
            return []
    
    def get_sensor_statistics(self, sensor_type, hours=24):
        """Get statistics for a sensor type"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cutoff_time = (datetime.now() - timedelta(hours=hours)).isoformat()
            
            cursor.execute('''
                SELECT COUNT(*) as count,
                       MIN(value) as min_value,
                       MAX(value) as max_value,
                       AVG(value) as avg_value,
                       unit
                FROM sensor_readings 
                WHERE sensor_type = ? AND timestamp >= ?
                GROUP BY unit
            ''', (sensor_type, cutoff_time))
            
            result = cursor.fetchone()
            conn.close()
            
            if result:
                return {
                    'count': result[0],
                    'min': result[1],
                    'max': result[2],
                    'average': result[3],
                    'unit': result[4]
                }
            
            return None
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Statistics query error: {str(e)}")
            return None
    
    def save_alert(self, node_id, sensor_type, alert_type, threshold_value, actual_value, message):
        """Save an alert to the database"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cursor.execute('''
                INSERT INTO alerts
                (timestamp, node_id, sensor_type, alert_type, 
                 threshold_value, actual_value, message)
                VALUES (?, ?, ?, ?, ?, ?, ?)
            ''', (
                datetime.now().isoformat(), node_id, sensor_type,
                alert_type, threshold_value, actual_value, message
            ))
            
            conn.commit()
            conn.close()
            
            return True
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Alert save error: {str(e)}")
            return False
    
    def get_unacknowledged_alerts(self):
        """Get all unacknowledged alerts"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cursor.execute('''
                SELECT id, timestamp, node_id, sensor_type, alert_type,
                       threshold_value, actual_value, message
                FROM alerts 
                WHERE acknowledged = FALSE
                ORDER BY timestamp DESC
            ''')
            
            columns = [desc[0] for desc in cursor.description]
            results = []
            
            for row in cursor.fetchall():
                record = dict(zip(columns, row))
                results.append(record)
            
            conn.close()
            return results
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Alerts query error: {str(e)}")
            return []
    
    def acknowledge_alert(self, alert_id):
        """Acknowledge an alert"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cursor.execute('''
                UPDATE alerts 
                SET acknowledged = TRUE 
                WHERE id = ?
            ''', (alert_id,))
            
            conn.commit()
            conn.close()
            
            return True
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Alert acknowledge error: {str(e)}")
            return False
    
    def cleanup_old_data(self, days_to_keep=30):
        """Clean up old data to manage database size"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            
            cutoff_time = (datetime.now() - timedelta(days=days_to_keep)).isoformat()
            
            # Delete old readings
            cursor.execute('DELETE FROM sensor_readings WHERE timestamp < ?', (cutoff_time,))
            readings_deleted = cursor.rowcount
            
            # Delete old acknowledged alerts
            cursor.execute('DELETE FROM alerts WHERE timestamp < ? AND acknowledged = TRUE', (cutoff_time,))
            alerts_deleted = cursor.rowcount
            
            conn.commit()
            conn.close()
            
            return readings_deleted, alerts_deleted
            
        except sqlite3.Error as e:
            self.database_error.emit(f"Cleanup error: {str(e)}")
            return 0, 0
    
    def export_data_csv(self, filename, node_id=None, sensor_type=None, hours=24):
        """Export data to CSV file"""
        import csv
        
        try:
            readings = self.get_recent_readings(node_id, sensor_type, hours)
            
            if not readings:
                return False
            
            with open(filename, 'w', newline='') as csvfile:
                fieldnames = ['timestamp', 'node_id', 'node_name', 'location',
                             'sensor_type', 'value', 'unit', 'quality',
                             'battery_level', 'signal_strength']
                
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                writer.writeheader()
                
                for reading in readings:
                    writer.writerow(reading)
            
            return True
            
        except Exception as e:
            self.database_error.emit(f"CSV export error: {str(e)}")
            return False
    
    def stop(self):
        """Stop the database manager"""
        self.running = False
        
        # Process any remaining data
        if self.data_queue:
            self.save_batch_data(self.data_queue)
            self.data_queue.clear()
        
        self.wait()  # Wait for thread to finish
```

## Step 2: Data Visualization and Alert System

### data_visualization.py

```python
import sys
from datetime import datetime, timedelta
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import numpy as np
from PyQt6.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QComboBox, QLabel
from PyQt6.QtCore import QTimer, pyqtSlot

class SensorChartWidget(QWidget):
    """Widget for displaying sensor data charts"""
    
    def __init__(self, title="Sensor Data"):
        super().__init__()
        self.title = title
        self.data_points = {}  # sensor_type -> [(timestamp, value), ...]
        self.max_points = 100
        
        self.initUI()
        self.setup_chart()
    
    def initUI(self):
        """Initialize the user interface"""
        layout = QVBoxLayout()
        
        # Chart controls
        controls_layout = QHBoxLayout()
        
        controls_layout.addWidget(QLabel("Sensor:"))
        self.sensor_combo = QComboBox()
        self.sensor_combo.currentTextChanged.connect(self.sensor_changed)
        controls_layout.addWidget(self.sensor_combo)
        
        controls_layout.addWidget(QLabel("Time Range:"))
        self.time_range_combo = QComboBox()
        self.time_range_combo.addItems(["Last Hour", "Last 6 Hours", "Last 24 Hours", "Last Week"])
        self.time_range_combo.currentTextChanged.connect(self.time_range_changed)
        controls_layout.addWidget(self.time_range_combo)
        
        controls_layout.addStretch()
        
        # Chart area
        self.figure = Figure(figsize=(12, 6))
        self.canvas = FigureCanvas(self.figure)
        
        layout.addLayout(controls_layout)
        layout.addWidget(self.canvas)
        
        self.setLayout(layout)
    
    def setup_chart(self):
        """Setup the matplotlib chart"""
        self.figure.clear()
        self.ax = self.figure.add_subplot(111)
        
        self.ax.set_title(self.title)
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Value")
        self.ax.grid(True, alpha=0.3)
        
        # Format x-axis for time
        self.ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
        self.ax.xaxis.set_major_locator(mdates.HourLocator(interval=1))
        
        self.figure.tight_layout()
        self.canvas.draw()
    
    def add_data_point(self, sensor_type, timestamp, value, unit=""):
        """Add a new data point"""
        if sensor_type not in self.data_points:
            self.data_points[sensor_type] = []
            self.sensor_combo.addItem(f"{sensor_type} ({unit})")
        
        # Convert timestamp to datetime if it's a string
        if isinstance(timestamp, str):
            timestamp = datetime.fromisoformat(timestamp.replace('Z', '+00:00'))
        
        self.data_points[sensor_type].append((timestamp, value))
        
        # Keep only recent points
        if len(self.data_points[sensor_type]) > self.max_points:
            self.data_points[sensor_type].pop(0)
        
        # Update chart if this sensor is currently selected
        current_sensor = self.sensor_combo.currentText().split(' (')[0]
        if sensor_type == current_sensor:
            self.update_chart()
    
    def sensor_changed(self, sensor_text):
        """Handle sensor selection change"""
        if sensor_text:
            self.update_chart()
    
    def time_range_changed(self, time_range):
        """Handle time range change"""
        self.update_chart()
    
    def update_chart(self):
        """Update the chart with current data"""
        current_sensor_text = self.sensor_combo.currentText()
        if not current_sensor_text:
            return
        
        sensor_type = current_sensor_text.split(' (')[0]
        
        if sensor_type not in self.data_points:
            return
        
        # Get time range
        time_range = self.time_range_combo.currentText()
        now = datetime.now()
        
        if time_range == "Last Hour":
            cutoff = now - timedelta(hours=1)
        elif time_range == "Last 6 Hours":
            cutoff = now - timedelta(hours=6)
        elif time_range == "Last 24 Hours":
            cutoff = now - timedelta(hours=24)
        else:  # Last Week
            cutoff = now - timedelta(days=7)
        
        # Filter data points
        filtered_data = [(ts, val) for ts, val in self.data_points[sensor_type] if ts >= cutoff]
        
        if not filtered_data:
            return
        
        # Extract timestamps and values
        timestamps, values = zip(*filtered_data)
        
        # Clear and redraw
        self.ax.clear()
        
        # Plot data
        self.ax.plot(timestamps, values, 'b-', linewidth=2, marker='o', markersize=4)
        
        # Customize chart
        self.ax.set_title(f"{sensor_type.title()} - {time_range}")
        self.ax.set_xlabel("Time")
        
        # Get unit from combo box text
        unit_part = current_sensor_text.split(' (')
        if len(unit_part) > 1:
            unit = unit_part[1].rstrip(')')
            self.ax.set_ylabel(f"Value ({unit})")
        
        self.ax.grid(True, alpha=0.3)
        
        # Format x-axis
        if time_range == "Last Hour":
            self.ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
            self.ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=10))
        elif time_range in ["Last 6 Hours", "Last 24 Hours"]:
            self.ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M'))
            self.ax.xaxis.set_major_locator(mdates.HourLocator(interval=2))
        else:  # Last Week
            self.ax.xaxis.set_major_formatter(mdates.DateFormatter('%m/%d'))
            self.ax.xaxis.set_major_locator(mdates.DayLocator(interval=1))
        
        # Rotate x-axis labels
        plt.setp(self.ax.xaxis.get_majorticklabels(), rotation=45)
        
        self.figure.tight_layout()
        self.canvas.draw()

class MultiSensorDashboard(QWidget):
    """Dashboard widget showing multiple sensor charts"""
    
    def __init__(self):
        super().__init__()
        self.charts = {}
        self.initUI()
    
    def initUI(self):
        """Initialize the dashboard UI"""
        self.main_layout = QVBoxLayout()
        self.setLayout(self.main_layout)
    
    def add_sensor_chart(self, sensor_type, title=None):
        """Add a chart for a specific sensor type"""
        if sensor_type in self.charts:
            return
        
        chart_title = title or f"{sensor_type.title()} Monitor"
        chart = SensorChartWidget(chart_title)
        
        self.charts[sensor_type] = chart
        self.main_layout.addWidget(chart)
    
    def update_sensor_data(self, network_data):
        """Update all charts with new network data"""
        node_data = network_data.get('node_data', {})
        
        for node_id, data in node_data.items():
            readings = data.get('readings', {})
            timestamp = data.get('timestamp')
            
            for sensor_type, reading in readings.items():
                if sensor_type not in self.charts:
                    self.add_sensor_chart(sensor_type)
                
                value = reading.get('value')
                unit = reading.get('unit', '')
                
                if value is not None:
                    self.charts[sensor_type].add_data_point(sensor_type, timestamp, value, unit)

class NetworkStatusWidget(QWidget):
    """Widget showing network status and statistics"""
    
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        """Initialize the network status UI"""
        layout = QVBoxLayout()
        
        # Network status chart
        self.figure = Figure(figsize=(8, 4))
        self.canvas = FigureCanvas(self.figure)
        
        # Setup status chart
        self.ax1 = self.figure.add_subplot(121)
        self.ax2 = self.figure.add_subplot(122)
        
        layout.addWidget(self.canvas)
        self.setLayout(layout)
        
        # Initialize empty charts
        self.update_network_status({'nodes_online': 0, 'total_nodes': 0, 'total_packets': 0, 'average_signal_strength': -100})
    
    def update_network_status(self, network_data):
        """Update network status display"""
        nodes_online = network_data.get('nodes_online', 0)
        total_nodes = network_data.get('total_nodes', 0)
        total_packets = network_data.get('total_packets', 0)
        avg_signal = network_data.get('average_signal_strength', -100)
        
        # Clear previous plots
        self.ax1.clear()
        self.ax2.clear()
        
        # Node status pie chart
        if total_nodes > 0:
            nodes_offline = total_nodes - nodes_online
            labels = ['Online', 'Offline']
            sizes = [nodes_online, nodes_offline]
            colors = ['#4CAF50', '#f44336']
            
            self.ax1.pie(sizes, labels=labels, colors=colors, autopct='%1.0f%%', startangle=90)
            self.ax1.set_title(f'Node Status\\n({nodes_online}/{total_nodes} Online)')
        
        # Signal strength bar chart
        if avg_signal != -100:
            signal_categories = ['Excellent\\n(>-50dBm)', 'Good\\n(-50 to -60dBm)', 
                               'Fair\\n(-60 to -80dBm)', 'Poor\\n(<-80dBm)']
            
            # Determine signal quality
            if avg_signal > -50:
                signal_quality = [1, 0, 0, 0]
            elif avg_signal > -60:
                signal_quality = [0, 1, 0, 0] 
            elif avg_signal > -80:
                signal_quality = [0, 0, 1, 0]
            else:
                signal_quality = [0, 0, 0, 1]
            
            colors = ['#4CAF50', '#FFEB3B', '#FF9800', '#f44336']
            bars = self.ax2.bar(signal_categories, signal_quality, color=colors)
            
            self.ax2.set_title(f'Signal Strength\\n({avg_signal:.1f} dBm)')
            self.ax2.set_ylim(0, 1)
            self.ax2.tick_params(axis='x', rotation=45)
        
        self.figure.tight_layout()
        self.canvas.draw()
```

### alert_system.py

```python
import json
from datetime import datetime
from PyQt6.QtCore import QObject, QTimer, pyqtSignal
from PyQt6.QtWidgets import QMessageBox

class AlertRule:
    """Represents an alert rule for sensor monitoring"""
    
    def __init__(self, rule_id, name, sensor_type, condition, threshold, nodes=None):
        self.rule_id = rule_id
        self.name = name
        self.sensor_type = sensor_type
        self.condition = condition  # 'greater_than', 'less_than', 'equal_to'
        self.threshold = threshold
        self.nodes = nodes or []  # Empty list means all nodes
        self.enabled = True
        self.last_triggered = None
        self.cooldown_minutes = 5  # Minimum time between alerts
    
    def check_condition(self, value):
        """Check if the value triggers this alert rule"""
        if not self.enabled:
            return False
        
        # Check cooldown
        if self.last_triggered:
            time_since_last = (datetime.now() - self.last_triggered).total_seconds() / 60
            if time_since_last < self.cooldown_minutes:
                return False
        
        # Check condition
        if self.condition == 'greater_than':
            return value > self.threshold
        elif self.condition == 'less_than':
            return value < self.threshold
        elif self.condition == 'equal_to':
            return abs(value - self.threshold) < 0.1  # Small tolerance for equality
        elif self.condition == 'not_equal_to':
            return abs(value - self.threshold) >= 0.1
        
        return False
    
    def trigger(self):
        """Mark this rule as triggered"""
        self.last_triggered = datetime.now()

class AlertSystem(QObject):
    """Manages alert rules and notifications"""
    
    alert_triggered = pyqtSignal(dict)  # alert_info
    alert_resolved = pyqtSignal(str)    # alert_id
    
    def __init__(self):
        super().__init__()
        self.alert_rules = {}
        self.active_alerts = {}
        self.alert_history = []
        
        self.load_alert_rules()
        
        # Check for resolved alerts periodically
        self.resolution_timer = QTimer()
        self.resolution_timer.timeout.connect(self.check_alert_resolutions)
        self.resolution_timer.start(30000)  # Check every 30 seconds
    
    def load_alert_rules(self):
        """Load alert rules from configuration"""
        default_rules = [
            {
                'rule_id': 'temp_high',
                'name': 'High Temperature Alert',
                'sensor_type': 'temperature',
                'condition': 'greater_than',
                'threshold': 30.0,
                'nodes': []
            },
            {
                'rule_id': 'temp_low',
                'name': 'Low Temperature Alert',
                'sensor_type': 'temperature',
                'condition': 'less_than',
                'threshold': 15.0,
                'nodes': []
            },
            {
                'rule_id': 'humidity_high',
                'name': 'High Humidity Alert',
                'sensor_type': 'humidity',
                'condition': 'greater_than',
                'threshold': 80.0,
                'nodes': []
            },
            {
                'rule_id': 'humidity_low',
                'name': 'Low Humidity Alert',
                'sensor_type': 'humidity',
                'condition': 'less_than',
                'threshold': 30.0,
                'nodes': []
            },
            {
                'rule_id': 'air_quality_poor',
                'name': 'Poor Air Quality Alert',
                'sensor_type': 'air_quality',
                'condition': 'greater_than',
                'threshold': 150.0,
                'nodes': []
            },
            {
                'rule_id': 'co2_high',
                'name': 'High CO2 Alert',
                'sensor_type': 'co2',
                'condition': 'greater_than',
                'threshold': 1000.0,
                'nodes': []
            }
        ]
        
        try:
            with open('alert_rules.json', 'r') as f:
                rules_data = json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            rules_data = {'rules': default_rules}
            self.save_alert_rules(rules_data)
        
        # Create AlertRule objects
        for rule_data in rules_data.get('rules', []):
            rule = AlertRule(
                rule_data['rule_id'],
                rule_data['name'],
                rule_data['sensor_type'],
                rule_data['condition'],
                rule_data['threshold'],
                rule_data.get('nodes', [])
            )
            self.alert_rules[rule.rule_id] = rule
    
    def save_alert_rules(self, rules_data=None):
        """Save alert rules to configuration"""
        if rules_data is None:
            # Convert AlertRule objects back to dict format
            rules_data = {
                'rules': [
                    {
                        'rule_id': rule.rule_id,
                        'name': rule.name,
                        'sensor_type': rule.sensor_type,
                        'condition': rule.condition,
                        'threshold': rule.threshold,
                        'nodes': rule.nodes,
                        'enabled': rule.enabled
                    }
                    for rule in self.alert_rules.values()
                ]
            }
        
        try:
            with open('alert_rules.json', 'w') as f:
                json.dump(rules_data, f, indent=2)
        except Exception as e:
            print(f"Failed to save alert rules: {e}")
    
    def add_alert_rule(self, name, sensor_type, condition, threshold, nodes=None):
        """Add a new alert rule"""
        rule_id = f"{sensor_type}_{condition}_{len(self.alert_rules)}"
        
        rule = AlertRule(rule_id, name, sensor_type, condition, threshold, nodes)
        self.alert_rules[rule_id] = rule
        
        self.save_alert_rules()
        return rule_id
    
    def remove_alert_rule(self, rule_id):
        """Remove an alert rule"""
        if rule_id in self.alert_rules:
            del self.alert_rules[rule_id]
            self.save_alert_rules()
            return True
        return False
    
    def enable_alert_rule(self, rule_id, enabled=True):
        """Enable or disable an alert rule"""
        if rule_id in self.alert_rules:
            self.alert_rules[rule_id].enabled = enabled
            self.save_alert_rules()
            return True
        return False
    
    def check_sensor_data(self, node_data):
        """Check sensor data against all alert rules"""
        node_id = node_data.get('node_id')
        readings = node_data.get('readings', {})
        timestamp = node_data.get('timestamp')
        
        for sensor_type, reading in readings.items():
            value = reading.get('value')
            unit = reading.get('unit', '')
            
            if value is None:
                continue
            
            # Check all rules for this sensor type
            for rule in self.alert_rules.values():
                if rule.sensor_type != sensor_type:
                    continue
                
                # Check if rule applies to this node (empty list means all nodes)
                if rule.nodes and node_id not in rule.nodes:
                    continue
                
                if rule.check_condition(value):
                    self.trigger_alert(rule, node_data, value, unit)
    
    def trigger_alert(self, rule, node_data, actual_value, unit):
        """Trigger an alert"""
        rule.trigger()
        
        alert_id = f"{rule.rule_id}_{node_data['node_id']}_{int(datetime.now().timestamp())}"
        
        alert_info = {
            'alert_id': alert_id,
            'rule_id': rule.rule_id,
            'rule_name': rule.name,
            'timestamp': datetime.now().isoformat(),
            'node_id': node_data['node_id'],
            'node_name': node_data.get('name', 'Unknown'),
            'location': node_data.get('location', 'Unknown'),
            'sensor_type': rule.sensor_type,
            'condition': rule.condition,
            'threshold_value': rule.threshold,
            'actual_value': actual_value,
            'unit': unit,
            'severity': self.determine_severity(rule, actual_value),
            'message': self.generate_alert_message(rule, node_data, actual_value, unit)
        }
        
        # Add to active alerts
        self.active_alerts[alert_id] = alert_info
        
        # Add to history
        self.alert_history.append(alert_info)
        
        # Keep history size manageable
        if len(self.alert_history) > 1000:
            self.alert_history = self.alert_history[-500:]  # Keep last 500
        
        # Emit signal
        self.alert_triggered.emit(alert_info)
    
    def determine_severity(self, rule, actual_value):
        """Determine alert severity based on how far the value is from threshold"""
        threshold = rule.threshold
        
        if rule.condition in ['greater_than', 'less_than']:
            # Calculate percentage deviation from threshold
            if threshold != 0:
                deviation = abs((actual_value - threshold) / threshold) * 100
            else:
                deviation = abs(actual_value - threshold)
            
            if deviation < 10:
                return 'low'
            elif deviation < 25:
                return 'medium'
            else:
                return 'high'
        
        return 'medium'  # Default severity
    
    def generate_alert_message(self, rule, node_data, actual_value, unit):
        """Generate a human-readable alert message"""
        node_name = node_data.get('name', 'Unknown Device')
        location = node_data.get('location', 'Unknown Location')
        
        condition_text = {
            'greater_than': 'exceeded',
            'less_than': 'fallen below',
            'equal_to': 'equals',
            'not_equal_to': 'deviates from'
        }.get(rule.condition, 'triggered')
        
        message = (f"{node_name} in {location}: "
                  f"{rule.sensor_type.title()} has {condition_text} "
                  f"threshold of {rule.threshold}{unit}. "
                  f"Current value: {actual_value}{unit}")
        
        return message
    
    def check_alert_resolutions(self):
        """Check if any active alerts should be resolved"""
        # This would typically check if sensor values have returned to normal
        # For now, we'll implement a simple time-based resolution
        current_time = datetime.now()
        resolved_alerts = []
        
        for alert_id, alert_info in list(self.active_alerts.items()):
            alert_time = datetime.fromisoformat(alert_info['timestamp'])
            
            # Auto-resolve alerts after 1 hour if not manually resolved
            if (current_time - alert_time).total_seconds() > 3600:
                resolved_alerts.append(alert_id)
        
        for alert_id in resolved_alerts:
            self.resolve_alert(alert_id, "Auto-resolved after 1 hour")
    
    def resolve_alert(self, alert_id, resolution_note=""):
        """Resolve an active alert"""
        if alert_id in self.active_alerts:
            alert_info = self.active_alerts[alert_id]
            alert_info['resolved_at'] = datetime.now().isoformat()
            alert_info['resolution_note'] = resolution_note
            
            del self.active_alerts[alert_id]
            self.alert_resolved.emit(alert_id)
            
            return True
        return False
    
    def get_active_alerts(self):
        """Get all active alerts"""
        return dict(self.active_alerts)
    
    def get_alert_history(self, hours=24):
        """Get alert history for specified time period"""
        cutoff_time = datetime.now() - timedelta(hours=hours)
        
        recent_alerts = []
        for alert in self.alert_history:
            alert_time = datetime.fromisoformat(alert['timestamp'])
            if alert_time >= cutoff_time:
                recent_alerts.append(alert)
        
        return recent_alerts
    
    def get_alert_statistics(self, hours=24):
        """Get alert statistics"""
        recent_alerts = self.get_alert_history(hours)
        
        if not recent_alerts:
            return {
                'total_alerts': 0,
                'by_severity': {'low': 0, 'medium': 0, 'high': 0},
                'by_sensor_type': {},
                'by_node': {}
            }
        
        # Count by severity
        severity_counts = {'low': 0, 'medium': 0, 'high': 0}
        sensor_type_counts = {}
        node_counts = {}
        
        for alert in recent_alerts:
            severity = alert.get('severity', 'medium')
            severity_counts[severity] += 1
            
            sensor_type = alert.get('sensor_type', 'unknown')
            sensor_type_counts[sensor_type] = sensor_type_counts.get(sensor_type, 0) + 1
            
            node_name = alert.get('node_name', 'Unknown')
            node_counts[node_name] = node_counts.get(node_name, 0) + 1
        
        return {
            'total_alerts': len(recent_alerts),
            'by_severity': severity_counts,
            'by_sensor_type': sensor_type_counts,
            'by_node': node_counts
        }
```

This comprehensive environmental monitoring system demonstrates:

1. **Multi-Sensor Network Management**: Realistic sensor node simulation with multiple sensor types
2. **Database Integration**: SQLite database for persistent data storage
3. **Real-Time Visualization**: Matplotlib charts for sensor data trends
4. **Alert System**: Configurable threshold-based alerts with severity levels
5. **Data Export**: CSV and JSON export capabilities
6. **Network Monitoring**: Connection status and signal strength tracking

The system provides a solid foundation for building production IoT monitoring applications with advanced features like automated reporting, historical analysis, and comprehensive alerting.

## Conclusion

These three IoT projects demonstrate progressively advanced PyQt6 concepts:

1. **Project 1** - Basic sensor display with real-time updates
2. **Project 2** - Device control with complex interactions and effects
3. **Project 3** - Comprehensive monitoring with data persistence and analytics

Each project builds upon previous concepts while introducing new techniques for building professional IoT applications. The projects serve as templates that can be adapted for real hardware integration and production deployment.

The combination of these tutorials provides a complete foundation for building sophisticated IoT interfaces using PyQt6, covering everything from basic widgets to advanced data visualization and device management systems.