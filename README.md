# Altitude Adaptation Monitor for Mountaineers and Pilots
 High-Altitude Health Monitoring– Continuous real-time tracking of SpO2, pulse, and temperature in  climbers, trekkers, pilots, and military personnel to detect early signs of altitude sickness, hypoxia, or  fatigue during ascent.
## Overview
High-altitude environments pose significant health risks due to reduced oxygen levels and extreme weather conditions. Individuals such as trekkers, mountaineers, pilots, and military personnel are especially vulnerable to hypoxia, fatigue, and altitude sickness, which can lead to life-threatening situations if not detected early. Currently, there is a lack lightweight, real-time, wearable solutions that monitor vital signs specifically for such conditions.
 
The proposed solution is a compact, wearable health monitoring system that continuously tracks SpO₂ (oxygen saturation), heart rate, and body temperature to assess the user's physiological adaptation to high altitudes. Optional integration of an altimeter (BMP390) allows for altitude-aware alerts, enhancing the contextual relevance of health data. The system provides real-time feedback through LEDs, buzzers, and a Bluetooth-connected mobile app for immediate awareness and action.
 
The monitoring goal is to offer users an easy-to-use, reliable system that helps prevent altitude related health risks by issuing threshold-based alerts before symptoms become severe. This ensures safer ascents, improved performance, and timely interventions in remote environments.
 ## List of Sensors used
 - **ESP32**              : Main controller with Bluetooth + Wi-Fi
- **MAX30102**            : Measures blood oxygen saturation and pulse rate
- **MLX90614(IR)**        : Non-contact body temperature measurement
- **BMP390**              : Measures altitude and atmospheric pressure
- **0.96" OLED Display**  : Shows real-time vitals on-device
- **5V Piezo Buzzer**     : Audio alert for critical conditions
- **3.7V Li-Po + TP4056** :  Power supply with rechargeable module
 ## Testing Plan (TRL-8 Readiness)
 **1. Sensor Accuracy Validation:** Compare readings from MAX30102 (SpO₂, HR) and MLX90614(temperature) against clinical-grade pulse oximeters and thermometers under resting and active conditions.
 
 **2. Drift Assessment:** Monitor each sensor’s output for 24 hours to assess long-term stability andthermal drift, especially during ambient temperature changes.
 
 **3. Altitude Simulation Tests:** Use controlled elevation environments (e.g., staircases, drone lift, pressure chamber if available) to simulate altitude changes and observe variations vitals.
 
**4. Threshold Alert Testing:** Simulate abnormal vitals (e.g., finger off sensor, warm surface contact) to verify alert triggering for low SpO₂, high HR, or abnormal temperature.
 
 **5.Bluetooth & App Reliability:** Test wireless transmission latency, data loss, and real-time display across varying distances and interference conditions.
 
 **6. Field Deployment:** Use the device during outdoor treks/hikes or in high-altitude areas (e.g., hill stations) to validate performance in real-world conditions.
 
 **7. Battery Runtime & Load Test:** Record power consumption with all modules active to evaluate continuous usage time and charging cycle stability.
## Setup Steps
**1. Assemble Hardware:** Connect all sensors (SpO₂, temperature, pressure) and modules (OLED, buzzer, GSM/Bluetooth) to the microcontroller as per the schematic.

**2. Flash Firmware:** Upload the modular ESP32 code using the Arduino IDE.

**3. Install Mobile App (optional):** Pair the device with the companion Bluetooth app to view live vitals and export data.

**4. Calibrate Sensors:** Use known reference values to fine-tune sensor readings for accuracy.

**5. Power the System:** Use a Li-ion battery with TP4056 charging module or USB power.

**6. Test Outputs:** Verify vitals on the OLED and app, and test alert triggers for abnormal conditions.
## Circuit Diagram
![image](https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/circuit_image.png)
## Circuit Connections & Pinout Table
### Sensor/Module Pinout Table – ESP32
| Sensor/Module     | Microcontroller Pin (ESP32) | Function                   |
|-------------------|-----------------------------|----------------------------|
| **MAX30102**      | SDA → GPIO21                | I2C Data (SpO₂ & Pulse)    |
|                   | SCL → GPIO22                | I2C Clock                  |
|                   | VIN → 3.3V                  | Power Supply               |
|                   | GND → GND                   | Ground                     |
| **MLX90614**      | SDA → GPIO21                | I2C Data (Temperature)     |
|                   | SCL → GPIO22                | I2C Clock                  |
|                   | VIN → 3.3V                  | Power Supply               |
|                   | GND → GND                   | Ground                     |
| **BMP390**        | SDA → GPIO21                | I2C Data (Altitude)        |
|                   | SCL → GPIO22                | I2C Clock                  |
|                   | VIN → 3.3V                  | Power Supply               |
|                   | GND → GND                   | Ground                     |
| **OLED Display**  | SDA → GPIO21                | I2C Data (Display)         |
|                   | SCL → GPIO22                | I2C Clock                  |
| **Buzzer**        | GPIO5                       | Alert Signal Output        |
|                   | VCC → 3.3V                  | Power Supply               |
|                   | GND → GND                   | Ground                     |
| **Battery (LiPo)**| VIN → 5V                    | Main Power Input           |
|                   | GND → GND                   | Common Ground              |
















 
