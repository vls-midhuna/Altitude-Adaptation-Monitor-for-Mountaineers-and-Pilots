# Altitude Adaptation Monitor for Mountaineers and Pilots
High-Altitude Health Monitoring – Continuous real-time monitoring of vital signs (pulse, body temperature) and environmental parameters (altitude, atmospheric pressure, humidity, and ambient temperature) to identify early signs of altitude sickness, hypoxia, and fatigue during ascent.

<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/product.png" alt="image" width="600" height="600"/>
 ## Table of Contents
1. [Overview](#overview)
2. [List of Sensors used](#list-of-sensors-used)
3. [Testing Plan (TRL-8 Readiness)](#testing-plan-trl-8-readiness)
4. [Setup Steps](#setup-steps)
5. [Circuit Diagram](#circuit-diagram)
6. [Schematic Diagram](#schematic-diagram)
7. [Circuit Connections & Pinout Table](#circuit-connections--pinout-table)
8. [Components Required with Bill of Materials](#components-required-with-bill-of-materials)
## Overview
High-altitude environments pose serious health risks due to low oxygen levels, decreased air pressure, and extreme weather conditions. Trekkers, mountaineers, pilots, and military personnel are particularly susceptible to altitude-related illnesses such as acute mountain sickness (AMS), high-altitude pulmonary edema (HAPE), high-altitude cerebral edema (HACE), hypoxia, severe fatigue, and decompression sickness. If not detected and managed early, these conditions can quickly become life-threatening.

The proposed solution is a compact, wearable health monitoring system that continuously tracks key physiological parameters and environmental conditions using the following sensors:
- MAX30102 for heart rate monitoring
- MLX90614 for non-contact body temperature measurement
- BME280 for altitude, atmospheric pressure, humidity, and environment temperature
- The system also includes a 0.96-inch OLED display for real-time data visualization, allowing users to immediately view their vital signs and surrounding environmental conditions without needing an external device.

The system helps detect early signs of:
- Hypoxia: Reflected through abnormal heart rate and body temperature fluctuations at increasing altitudes
- Fatigue and Overexertion: Indicated by sustained elevated heart rate and rising body temperature
- Decompression Sickness: Assessed by correlating sudden altitude changes with vital sign variations
- High-altitude illnesses (AMS, HAPE, HACE): Identified through combined trends in physiological stress and environmental conditions

For remote monitoring, a mobile application hosts an internet-based web server that provides continuous access to live health data from any connected location. This enables real-time awareness, facilitating timely actions such as rest, descent, or medical support before symptoms worsen.

By integrating accurate sensors and real-time feedback mechanisms, this system enhances safety, supports performance, and enables early intervention in high-risk, high-altitude environments.
 ## List of Sensors used
- **ESP32**              : Main controller with Bluetooth + Wi-Fi
- **MAX30102**            : Measures blood oxygen saturation and pulse rate
- **MLX90614(IR)**        : Non-contact body temperature measurement
- **BME280**              : Measures altitude and atmospheric pressure
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

**3. Start Web Dashboard**: Connect the device to Wi-Fi and access a built-in web server via browser to monitor live vitals and download data logs.

**4. Calibrate Sensors:** Use known reference values to fine-tune sensor readings for accuracy.

**5. Power the System:** Use a Li-ion battery with TP4056 charging module or USB power.

**6. Test Outputs:** Verify vitals on the OLED and app, and test alert triggers for abnormal conditions.
## Circuit Diagram
![image](https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/circuit_image.png)
## Schematic Diagram
![image](https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/schematic.png)
## Working Code
```
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET -1  // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MAX30105 particleSensor;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

int beatsperMin = 72;
float beatsPerMinute,irValue;
long lastBeat = 0;
float temperature,Heart_Beat,IR_value;
float pressure, altitude, humidity;

//Put your SSID & Password/
const char* ssid = "ssid";  // Enter SSID here
const char* password = "password";  //Enter Password here

WebServer server(80); 

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");


  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  if (!mlx.begin()) {
		Serial.println("Error connecting to MLX sensor. Check wiring.");
		while (1);
	};

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  if (!bme.begin(0x76)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		while (1);
	}

 }

 void loop() {
  irValue = particleSensor.getIR();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = bme.readHumidity();
  //atm_temperature = bme.readTemperature();
  temperature = mlx.readObjectTempF();
  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
  }
   // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperature= ");
  display.print(temperature);
  display.println(" F");
  display.print("Heart Beat= ");
  display.print(beatsPerMinute);
  display.println(" bpm");
  display.print("IR value= ");
  display.println(irValue);
  display.print("Pressure= ");
  display.print(pressure);
  display.println(" hPa");
  display.print("Altitude= ");
  display.print(altitude);
  display.println(" m");
  display.print("Humidity= ");
  display.print(humidity);
  display.println(" %");
  if (beatsPerMinute > 120 || beatsPerMinute < 55 || temperature > 100.5 || temperature < 97){
    display.println("Alert");
    display.println("Vitals are dropping.");
  }
  display.display();
  
  display.clearDisplay();

  server.handleClient();
  // int x=millis();

  // Serial.print(x);Serial.print(",");
  // Serial.print(temperature);Serial.print(",");
  // Serial.print(beatsPerMinute);Serial.print(",");
  // Serial.print(pressure);Serial.print(",");
  // Serial.print(humidity);Serial.print(",");
  // Serial.print(altitude);Serial.print(",");
  // Serial.println(irValue);    //Temperature \t Heart Beat \t Pressure \t Humidity \t Altitude \t IR_value

  
}


void handle_OnConnect() {
  Heart_Beat = beatsPerMinute;
  IR_value = irValue;
  server.send(200, "text/html", SendHTML(temperature,Heart_Beat,IR_value,pressure, altitude, humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float temperature,float Heart_Beat,float IR_value,float pressure,float altitude,float humidity){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta http-equiv=\"refresh\" content=\"1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Altitude adaptation monitor</title>\n";
  ptr +="<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.0/css/all.min.css\">";
  ptr +="<style>";
  ptr +="body {";
  ptr +="margin: 0;";
  ptr +="font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;";
  ptr +="background: linear-gradient(to right, #00c6ff, #0072ff);";
  ptr +="color: #fff;";
  ptr +="display: flex;";
  ptr +="justify-content: center;";
  ptr +="align-items: center;";
  ptr +="min-height: 100vh;";
  ptr +="}";
  ptr +=".container {";
  ptr +="background: rgba(0, 0, 0, 0.2);";
  ptr +="padding: 30px;";
  ptr +="border-radius: 15px;";
  ptr +="box-shadow: 0 0 20px rgba(0, 0, 0, 0.3);";
  ptr +="max-width: 480px;";
  ptr +="width: 90%;";
  ptr +="text-align: center;";
  ptr +="}";
  ptr +="h1 {";
  ptr +="margin-bottom: 25px;";
  ptr +="font-size: 24px;";
  ptr +=" }";
  ptr +=".section {";
  ptr +="margin-bottom: 20px;";
  ptr +="border-bottom: 1px solid rgba(255,255,255,0.2);";
  ptr +="padding-bottom: 10px;";
  ptr +="}";
  ptr +=".row {";
  ptr +="display: flex;";
  ptr +="justify-content: space-between;";
  ptr +="margin: 10px 0;";
  ptr +="font-size: 18px;";
  ptr +="}";
  ptr +=".label {";
  ptr +="display: flex;";
  ptr +="align-items: center;";
  ptr +="} button {";
  ptr +="margin-top: 15px;";
  ptr +="padding: 8px 16px;";
  ptr +="font-size: 15px;";
  ptr +="border: none;";
  ptr +="border-radius: 6px;";
  ptr +="background: #fff;";
  ptr +="color: #0072ff;";
  ptr +="cursor: pointer;";
  ptr +="}";
  ptr +="button:hover {";
  ptr +="background: #e0e0e0;";
  ptr +="}";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div class=\"container\">\n";
  ptr +="<h1><i class=\"fas fa-mountain\"></i> Altitude Adaptation Monitor</h1>\n";
  ptr +="<div class=\"section\"> \n";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-thermometer-half\"></i> Temperature:</div><div><span id=\"temperature\">";
  ptr +=temperature;
  ptr +="</span> <span id=\"tempUnit\">°F</span></div></div>";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-heartbeat\"></i> Heart Beat:</div><div><span id=\"heartbeat\">";
  ptr +=Heart_Beat;
  ptr +="</span> bpm</div></div>";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-wave-square\"></i> IR Value:</div><div><span id=\"irvalue\">";
  ptr +=IR_value;
  ptr +="</span></div></div>";
  ptr +="</div>";
  ptr +="<div class=\"section\">";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-tachometer-alt\"></i> Pressure:</div><div><span id=\"pressure\">";
  ptr +=pressure;
  ptr +="</span> hPa</div></div>";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-arrows-alt-v\"></i> Altitude:</div><div><span id=\"altitude\">";
  ptr +=altitude;
  ptr +="</span> m</div></div>";
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-water\"></i> Humidity:</div><div><span id=\"humidity\">";
  ptr +=humidity;
  ptr +="</span> %</div></div>";
  ptr +="</div>";
  ptr +="<script>";
  ptr +="let temperatureF = temperature, isFahrenheit = true;";
  ptr +="function toggleTemperature() {";
  ptr +="const temp = document.getElementById('temperature');";
  ptr +="const unit = document.getElementById('tempUnit');";
  ptr +="if (isFahrenheit) {";
  ptr +="temp.textContent = ((temperatureF - 32) * 5/9).toFixed(1);";
  ptr +="unit.textContent = '°C';";
  ptr +="} else {";
  ptr +="temp.textContent = temperatureF.toFixed(1);";
  ptr +="unit.textContent = '°F';";
  ptr +="}";
  ptr +="isFahrenheit = !isFahrenheit;";
  ptr +="}";
  ptr +="</script>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
```
### For Plots
```
% Load the CSV file
data = readtable('travis.csv');

% Convert Time from milliseconds to hours
time_hours = data.Millis / (1000 * 60 * 60);  % ms → hours

% Extract altitude data
altitude = data.Altitude;

% Plot altitude drift
figure('Color', 'w');
plot(time_hours, altitude, 'm-', 'LineWidth', 1.5);
xlabel('Time (hours)', 'FontSize', 14);
ylabel('Altitude (m)', 'FontSize', 14);
title('Altitude Drift Over Time (in Hours)', 'FontSize', 16, 'FontWeight', 'bold');
grid on;

% Beautify axes
set(gca, 'FontSize', 12);
xlim([0 max(time_hours)]);
box on;
```
```
% Load the CSV file
data = readtable('travis.csv');

% Convert Time from milliseconds to hours
time_hours = data.Millis / (1000 * 60 * 60);  % ms → hours

% Extract humidity data
humidity = data.Humidity;

% Plot humidity drift
figure('Color', 'w');
plot(time_hours, humidity, 'g-', 'LineWidth', 1.5);
xlabel('Time (hours)', 'FontSize', 14);
ylabel('Humidity (%)', 'FontSize', 14);
title('Humidity Drift Over Time (in Hours)', 'FontSize', 16, 'FontWeight', 'bold');
grid on;

% Beautify axes
set(gca, 'FontSize', 12);
xlim([0 max(time_hours)]);
box on;
```
```
% Load the CSV file
data = readtable('travis.csv');

% Convert Time from milliseconds to hours
time_hours = data.Millis / (1000 * 60 * 60);  % ms → hours

% Extract IR Value data
ir_value = data.IRValue;

% Plot IR Value drift
figure('Color', 'w');
plot(time_hours, ir_value, 'k-', 'LineWidth', 1.5);
xlabel('Time (hours)', 'FontSize', 14);
ylabel('IR Value', 'FontSize', 14);
title('IR Sensor Drift Over Time (in Hours)', 'FontSize', 16, 'FontWeight', 'bold');
grid on;

% Beautify axes
set(gca, 'FontSize', 12);
xlim([0 max(time_hours)]);
box on;
```
```
% Load the CSV file
data = readtable('travis.csv');

% Convert Time from milliseconds to hours
time_hours = data.Millis / (1000 * 60 * 60);  % ms → hours

% Extract pressure data
pressure = data.Pressure;

% Plot pressure drift
figure('Color', 'w');
plot(time_hours, pressure, 'b-', 'LineWidth', 1.5);
xlabel('Time (hours)', 'FontSize', 14);
ylabel('Pressure (hPa)', 'FontSize', 14);
title('Pressure Drift Over Time (in Hours)', 'FontSize', 16, 'FontWeight', 'bold');
grid on;

% Beautify axes
set(gca, 'FontSize', 12);
xlim([0 max(time_hours)]);
box on;
```
```
% Load the CSV file
data = readtable('travis.csv');

% Display column names (optional)
% disp(data.Properties.VariableNames)

% Convert Time from milliseconds to hours
time_hours = data.Millis / (1000 * 60 * 60);  % ms → hours

% Extract temperature data
temperature = data.Temperature;

% Plot temperature drift
figure('Color', 'w');
plot(time_hours, temperature, 'r-', 'LineWidth', 1.5);
xlabel('Time (hours)', 'FontSize', 14);
ylabel('Temperature (°C)', 'FontSize', 14);
title('Temperature Drift Over Time (in Hours)', 'FontSize', 16, 'FontWeight', 'bold');
grid on;

% Beautify axes
set(gca, 'FontSize', 12);
xlim([0 max(time_hours)]);
box on;
```
## Circuit Connections & Pinout Table
| Sensor/Module                             | Microcontroller Pin (ESP32)                            | Function                                               |
|-------------------------------------------|--------------------------------------------------------|--------------------------------------------------------|
| **MAX30102**                              | SDA → GPIO21                                           | I2C Data (SpO₂ & Pulse)                                |
|                                           | SCL → GPIO22                                           | I2C Clock                                              |
|                                           | VIN → 3.3V                                             | Power Supply                                           |
|                                           | GND → GND                                              | Ground                                                 |
| **MLX90614**                              | SDA → GPIO21                                           | I2C Data (Temperature)                                 |
|                                           | SCL → GPIO22                                           | I2C Clock                                              |
|                                           | VIN → 3.3V                                             | Power Supply                                           |
|                                           | GND → GND                                              | Ground                                                 |
| **BME280**                                | SDA → GPIO21                                           | I2C Data (Altitude)                                    |
|                                           | SCL → GPIO22                                           | I2C Clock                                              |
|                                           | VIN → 3.3V                                             | Power Supply                                           |
|                                           | GND → GND                                              | Ground                                                 |
| **OLED Display**                          | SDA → GPIO21                                           | I2C Data (Display)                                     |
|                                           | SCL → GPIO22                                           | I2C Clock                                              |
| **Buzzer**                                | GPIO5                                                  | Alert Signal Output                                    |
|                                           | VCC → 3.3V                                             | Power Supply                                           |
|                                           | GND → GND                                              | Ground                                                 |
| **Battery (LiPo)**                        | VIN → 5V                                               | Main Power Input                                       |
|                                           | GND → GND                                              | Common Ground                                          |
## Components Required with Bill of Materials
| Item                   | Quantity | Component Type                                                  | Links to Products                                      |
|------------------------|----------|---------------------------------------------------------------|---------------------------------------------------|
| ESP32                | 1        | Compute Board                                        | [ESP32](https://www.amazon.in/SquadPixel-ESP-32-Bluetooth-Development-Board/dp/B071XP56LM/ref=sr_1_3?crid=30OQ5YCZ7Q4KW&dib=eyJ2IjoiMSJ9.T_X5Nbn2mH9dvueGcGZsRnpQ3ld-76jj025S_E4B1hx1ijLrgyL_MqLj3ZU8IanjZI4xvPXs0Y9rN4BZ09s50feUMPRKnqJ_n-L8xLixFu8scZX_-tTMVspW0pFff4rdfPQ58Pjcu9g1mEGBDamzlQTKpMXK5WyJ5Iqw_A_TxaM1b7qDIwLaswDF4N9mztGcv76mVskriXcr6FF9txQwp-2jIfWcw4naIKjp1o0g_dM.WDVWcdLAfxQ2A5v6M3I7pJrT7izNHQz-rF6vF3qEtjM&dib_tag=se&keywords=esp32+board&qid=1752078531&sprefix=%2Caps%2C375&sr=8-3)           |
| MAX30102            | 1        | SpO₂ & Heart Rate  | [MAX30102](https://robu.in/product/max30102-heart-rate-and-pulse-oximeter-sensor-module-black/)        |
| MLX90614(IR)            | 1        |Temperature Sensor | [MLX90614](https://robu.in/product/mlx90614-esf-non-contact-human-body-infrared-temperature-measurement-module/)       |
| BME280            | 1        | Altimeter  | [BME280](https://robu.in/product/gy-bme280-5v-temperature-and-humidity-sensor/)        |
| 0.96" OLED Display    | 1| Display| [0.96" OLED Display](https://robu.in/product/0-96-oled-display-module/)|
| 5V Piezo Buzzer        | 1|   Buzzer    | [5V Piezo Buzzer](https://robu.in/product/5v-active-alarm-buzzer-module-arduino/)       |
| 3.7V Li-Po Battery         | 1| Battery | [Battery](https://www.amazon.in/Bhajanlal-Greenery-Rechargeable-Lithium-Batteries/dp/B0CYQ6H8FW/ref=sr_1_2_sspa?crid=2NFOCZQ40NE5W&dib=eyJ2IjoiMSJ9.OnAqIhrvsN6XrdG3yugPQGaeXTvkB708agMQ3pN4un5bHFupxT-0Haiyeb3CWMa1OuJoGwLQmbjygzAOmDC7AJq6vL_9z93u3JbfO3ViGRv9UcUZGzkfguYX6lpsL57lqOoRnmAcxPzmiRzC3wEjJloS1SSI2_cuhs-_ypaiOF_9dHka0CAJfwPA_ak6ifWNsK8W02wKp2u_UBTDW76bMcxHAr9lxxGVHTTAmINru-w.ggYwBbw2LCEuiLELBymDRuCwLWsE3pA9a0ZKZeYztBE&dib_tag=se&keywords=li+po+battery+3.7v&qid=1752079402&sprefix=li+po%2Caps%2C287&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)        |














 
