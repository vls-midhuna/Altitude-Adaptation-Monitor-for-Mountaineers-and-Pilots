# Altitude Adaptation Monitor for Mountaineers and Pilots
High-Altitude Health Monitoring – Continuous real-time monitoring of vital signs (pulse, body temperature) and environmental parameters (altitude, atmospheric pressure, humidity, and ambient temperature) to identify early symptoms of altitude sickness, hypoxia, and fatigue during ascent.

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
9. [Working Code](#working-code)
10. [Working Code for plotting](#for-plots)
11. [Testing Graphs](#testing-graphs)
12. [Demonstration](#demonstration-video)
13. [Indian Sensor Substitution Plan](#indian-sensor-substitution-plan)
## Overview
High-altitude environments pose serious health risks due to low oxygen levels, decreased air pressure, and extreme weather conditions. Trekkers, mountaineers, pilots, and military personnel are particularly susceptible to altitude-related illnesses such as acute mountain sickness (AMS), high-altitude pulmonary edema (HAPE), high-altitude cerebral edema (HACE), and decompression sickness. If not detected and managed early, these conditions can quickly become life-threatening.

The proposed solution is a compact, wearable health monitoring system that continuously tracks key physiological parameters and environmental conditions using the following sensors:
- MAX30102 for heart rate monitoring
- MLX90614 for non-contact body temperature measurement
- BME280 for altitude, atmospheric pressure, humidity, and environment temperature
- The system also includes a 0.96-inch OLED display for real-time data visualization, allowing users to immediately view their vital signs and surrounding environmental conditions without needing an external device.

The system helps detect early symptoms of:
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
![image](https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/hardware/circuit_image.png)
## Schematic Diagram
![image](https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/hardware/schematic.png)

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
| ESP32                | 1        | Compute Board                                        | [ESP32](https://robu.in/product/esp32-38pin-development-board-wifibluetooth-ultra-low-power-consumption-dual-core/)           |
| MAX30102            | 1        | SpO₂ & Heart Rate  | [MAX30102](https://robu.in/product/max30102-heart-rate-and-pulse-oximeter-sensor-module-black/)        |
| MLX90614(IR)            | 1        |Temperature Sensor | [MLX90614](https://robu.in/product/mlx90614-esf-non-contact-human-body-infrared-temperature-measurement-module/)       |
| BME280            | 1        | Altimeter  | [BME280](https://robu.in/product/gy-bme280-5v-temperature-and-humidity-sensor/)        |
| 0.96" OLED Display    | 1| Display| [0.96" OLED Display](https://robu.in/product/0-96-oled-display-module/)|
| 5V Piezo Buzzer        | 1|   Buzzer    | [5V Piezo Buzzer](https://robu.in/product/5v-active-alarm-buzzer-module-arduino/)       |
| 3.7V Li-Po Battery         | 1| Battery | [Battery](https://www.amazon.in/Bhajanlal-Greenery-Rechargeable-Lithium-Batteries/dp/B0CYQ6H8FW/ref=sr_1_2_sspa?crid=2NFOCZQ40NE5W&dib=eyJ2IjoiMSJ9.OnAqIhrvsN6XrdG3yugPQGaeXTvkB708agMQ3pN4un5bHFupxT-0Haiyeb3CWMa1OuJoGwLQmbjygzAOmDC7AJq6vL_9z93u3JbfO3ViGRv9UcUZGzkfguYX6lpsL57lqOoRnmAcxPzmiRzC3wEjJloS1SSI2_cuhs-_ypaiOF_9dHka0CAJfwPA_ak6ifWNsK8W02wKp2u_UBTDW76bMcxHAr9lxxGVHTTAmINru-w.ggYwBbw2LCEuiLELBymDRuCwLWsE3pA9a0ZKZeYztBE&dib_tag=se&keywords=li+po+battery+3.7v&qid=1752079402&sprefix=li+po%2Caps%2C287&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)        |

## Working Code
```
#include <MAX3010x.h>
#include <filters.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//symptoms variables
bool low_body_temperature = false;
bool high_body_temperature = false;
bool low_heart_rate = false;
bool high_heart_rate = false;
bool low_SPO2 = false;

// Environment variables
bool high_pressure = false;
bool low_pressure = false;
bool low_humidity = false;
bool high_humidity = false;
bool low_temperature = false;
bool high_temperature = false;
bool altitude_above_2500 = false;
bool altitude_above_4267 = false;
bool rate_of_ascent_stage1 = false;
bool rate_of_ascent_stage2 = false;
bool rate_of_descent_stage1 = false;
bool rate_of_descent_stage2 = false;
bool rate_of_excessive_pressure = false;
bool rate_of_compressive_pressure = false;

//for rate of change calculations
int previous_time = 0;
float previous_altitude_value = 0;
float previous_pressure_value = 0;


// Library instances
MAX30105 sensor;

const auto kSamplingRate = sensor.SAMPLING_RATE_400SPS;
const float kSamplingFrequency = 400.0;

// Finger Detection Threshold and Cooldown
const unsigned long kFingerThreshold = 10000;
const unsigned int kFingerCooldownMs = 500;

// Edge Detection Threshold (decrease for MAX30100)
const float kEdgeThreshold = -2000.0;

// Filters
const float kLowPassCutoff = 5.0;
const float kHighPassCutoff = 0.5;

// Averaging
const bool kEnableAveraging = true;
const int kAveragingSamples = 50;
const int kSampleThreshold = 5;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET -1  // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// MAX30105 particleSensor;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

float beatsPerMinute;
float irValue,SPO2_value;
float temperature;
float Heart_Beat;
float IR_value;
float pressure, altitude, humidity,atm_temperature;

//Put your SSID & Password/
const char* ssid = "vivo Y33T";  // Enter SSID here
const char* password = "qwertyuiop";  //Enter Password here

WebServer server(80); 

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
// connecting to WIFI
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

  if (!bme.begin(0x76)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
		while (1);
	}

  if(sensor.begin() && sensor.setSamplingRate(kSamplingRate)) { 
    Serial.println("Sensor initialized");
  }
  else {
    Serial.println("Sensor not found");  
    while(1);
  }

 }

// Filter Instances
HighPassFilter high_pass_filter(kHighPassCutoff, kSamplingFrequency);
LowPassFilter low_pass_filter_red(kLowPassCutoff, kSamplingFrequency);
LowPassFilter low_pass_filter_ir(kLowPassCutoff, kSamplingFrequency);
//LowPassFilter low_pass_filter(kLowPassCutoff, kSamplingFrequency);
Differentiator differentiator(kSamplingFrequency);
MovingAverageFilter<kAveragingSamples> averager_bpm;
MovingAverageFilter<kAveragingSamples> averager_spo2;

// Statistic for pulse oximetry
MinMaxAvgStatistic stat_red;
MinMaxAvgStatistic stat_ir;

// R value to SpO2 calibration factors
// See https://www.maximintegrated.com/en/design/technical-documents/app-notes/6/6845.html
float kSpO2_A = 1.5958422;
float kSpO2_B = -34.6596622;
float kSpO2_C = 112.6898759;

// Timestamp of the last heartbeat
long last_heartbeat = 0;

// Timestamp for finger detection
long finger_timestamp = 0;
bool finger_detected = false;

// Last diff to detect zero crossing
float last_diff = NAN;
bool crossed = false;
long crossed_time = 0;

 void loop() {

  auto sample = sensor.readSample(1000);
  float current_value_red = sample.red;
  float current_value_ir = sample.ir;
  // Detect Finger using raw sensor value
  if(sample.red > kFingerThreshold) {
    if(millis() - finger_timestamp > kFingerCooldownMs) {
      finger_detected = true;
    }
  }
  else {
    // Reset values if the finger is removed
    differentiator.reset();
    averager_bpm.reset();
   // low_pass_filter.reset();
    high_pass_filter.reset();
    averager_spo2.reset();
    low_pass_filter_red.reset();
    low_pass_filter_ir.reset();
    high_pass_filter.reset();
    stat_red.reset();
    stat_ir.reset();

    finger_detected = false;
    finger_timestamp = millis();
  }

  if(finger_detected) {
    //current_value = low_pass_filter.process(current_value);
    current_value_red = low_pass_filter_red.process(current_value_red);
    current_value_ir = low_pass_filter_ir.process(current_value_ir);

    // Statistics for pulse oximetry
    stat_red.process(current_value_red);
    stat_ir.process(current_value_ir);


    float current_value = high_pass_filter.process(current_value_red);
    float current_diff = differentiator.process(current_value);

    // Valid values?
    if(!isnan(current_diff) && !isnan(last_diff)) {
      
      // Detect Heartbeat - Zero-Crossing
      if(last_diff > 0 && current_diff < 0) {
        crossed = true;
        crossed_time = millis();
      }
      
      if(current_diff > 0) {
        crossed = false;
      }
  
      // Detect Heartbeat - Falling Edge Threshold
      if(crossed && current_diff < kEdgeThreshold) {
        if(last_heartbeat != 0 && crossed_time - last_heartbeat > 300) {
          // Show Results
          int bpm = 60000/(crossed_time - last_heartbeat);
          float rred = (stat_red.maximum()-stat_red.minimum())/stat_red.average();
          float rir = (stat_ir.maximum()-stat_ir.minimum())/stat_ir.average();
          float r = rred/rir;
          float spo2 = kSpO2_A * r * r + kSpO2_B * r + kSpO2_C;
          
          if(bpm > 50 && bpm < 250) {
            // Average?
            if(kEnableAveraging) {
              int average_bpm = averager_bpm.process(bpm);
              int average_spo2 = averager_spo2.process(spo2);

              // Show if enough samples have been collected
              if(averager_bpm.count() > kSampleThreshold) {
                Serial.print("Heart Rate (avg, bpm): ");
                Serial.println(average_bpm);
                beatsPerMinute = average_bpm;
                Serial.print("SpO2 (avg, %): ");
                Serial.println(average_spo2);
                SPO2_value = average_spo2;
              }
            }
            else {
              Serial.print("Heart Rate (current, bpm): ");
              Serial.println(bpm);  
              Serial.print("SpO2 (current, %): ");
              Serial.println(spo2); 
            }
          }
           // Reset statistic
          stat_red.reset();
          stat_ir.reset();

        }
  
        crossed = false;
        last_heartbeat = crossed_time;
      }
    }

    last_diff = current_diff;
  }

  // irValue = particleSensor.getIR();
  pressure = bme.readPressure() / 100.0F;
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = bme.readHumidity();
  atm_temperature = bme.readTemperature();
  temperature = mlx.readObjectTempF();

  //setting up the conditions
  //High Heart Beat
  if (beatsPerMinute > 120){
    high_heart_rate = true;
  }
  else{
    high_heart_rate = false;
  }
  //Low Heart Beat
  if (beatsPerMinute < 55 ){
    low_heart_rate = true;
  }
  else{
    low_heart_rate = false;
  }
  //Low Temperature
  if(temperature < 97){
    low_body_temperature = true;
  }
  else{
    low_body_temperature = false;
  }

  //High Temperature
  if(temperature > 99.5 ){
    high_body_temperature = true;
  }
  else{
    high_body_temperature = false;
  }
  
  //Low SPO2
  if(SPO2_value < 92){
    low_SPO2 = true;
  }

  //Low Pressure
  if ( pressure < 1010){
    low_pressure = true;
  }
  else{
    low_pressure = false;
  }

  // High pressure
  if ( pressure > 1020){
    high_pressure = true;
  }
  else{
    high_pressure = false;
  }
  //Low humidity
  if ( humidity <= 30){
    low_humidity = true;
  }
  else{
    low_humidity = false;
  }

  //High Humidity
  if(humidity > 50 ){
    high_humidity = true;
  }
  else{
    high_humidity = false;
  }
  //Low atmosphere temperature
  if( atm_temperature < 20 ){
    low_temperature = true;
  }
  else{
    low_temperature = false;
  }

  //High atmosphere Temperature
  if(atm_temperature > 32){
    high_temperature = true;
  }
  else{
    high_temperature = false;
  }

  //altitude_parameters
  if(altitude >= 2500 && altitude < 4267){
    altitude_above_2500 = true;
    altitude_above_4267 = false;
  }
  else if(altitude >= 4267){
    altitude_above_2500 = false;
    altitude_above_4267 = true;
  }
  else{
    altitude_above_2500 = false;
    altitude_above_4267 = false;
  }
  // for 12 hour timing calculation
  if(millis()- previous_time >= 43200000){
    previous_time = millis();
    previous_pressure_value = pressure;
    previous_altitude_value = altitude;
  }
  //excessive pressure condition
  if(pressure - previous_pressure_value >= 9){
    rate_of_excessive_pressure = true;
  }
  else{
    rate_of_excessive_pressure = false;
  }
  //compressive pressure condition
  if ( previous_pressure_value - pressure >= 9 ){
    rate_of_compressive_pressure = true;
  }
  else{
    rate_of_compressive_pressure = false;
  }

  //altitude ascent rate
  if(altitude_above_2500){
    if(altitude - previous_altitude_value >= 900 ){
      rate_of_ascent_stage1 = true;
    }
    else{
      rate_of_ascent_stage1 = false;
    }
    if(previous_altitude_value - altitude >=900){
      rate_of_descent_stage1 = true;
    }
    else{
      rate_of_descent_stage1 = false;
    }
  }


  if(altitude_above_4267){
    if(altitude - previous_altitude_value >= 450 ){
      rate_of_ascent_stage2 = true;
    }
    else{
      rate_of_ascent_stage2 = false;
    }
    if(previous_altitude_value - altitude >=450){
      rate_of_descent_stage2 = true;
    }
    else{
      rate_of_descent_stage2 = false;
    }
  }


  //irValue = current_value;
  // if (checkForBeat(irValue) == true)
  // {
  //   //We sensed a beat!
  //   long delta = millis() - lastBeat;
  //   lastBeat = millis();

  //   beatsPerMinute = 60 / (delta / 1000.0);
  // }
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
  display.print("SPO2= ");
  display.println(SPO2_value);
  display.print("Pressure= ");
  display.print(pressure);
  display.println(" hPa");
  display.print("Altitude= ");
  display.print(altitude);
  display.println(" m");
  display.print("Humidity= ");
  display.print(humidity);
  display.println(" %");
  // if (beatsPerMinute > 120 || beatsPerMinute < 55 || temperature > 100.5 || temperature < 97){
  //   display.println("Alert");
  //   display.println("Vitals are dropping.");
  // }
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
  server.send(200, "text/html", SendHTML(temperature,Heart_Beat,SPO2_value,pressure, altitude, humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float temperature,float Heart_Beat,float SPO2_value,float pressure,float altitude,float humidity){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta http-equiv=\"refresh\" content=\"10\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
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
  ptr +="<div class=\"row\"><div class=\"label\"><i class=\"fas fa-wave-square\"></i> SPO2 :</div><div><span id=\"spo2\">";
  ptr +=SPO2_value;
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
  // ptr +="<label>";
  // ptr +="<input type=\"checkbox\" id=\"fatigue\">hi";
  // ptr +="</label>";
  // ptr +="<div id=\"hypoxia\">balaji </div>";
  // ptr +="<div id=\"fatigue1\">hi </div>";
  // ptr +="<div id=\"ams\"> </div>";
  // ptr +="<div id=\"hace\"> </div>";
  // ptr +="<div id=\"hape\"> </div>";
  // ptr +="<div id=\"decompression_sickness\"> </div>";
  //ptr +="<script>";
  // ptr +="let temperatureF = temperature, isFahrenheit = true;";
  // ptr +="function toggleTemperature() {";
  // ptr +="const temp = document.getElementById('temperature');";
  // ptr +="const unit = document.getElementById('tempUnit');";
  // ptr +="if (isFahrenheit) {";
  // ptr +="temp.textContent = ((temperatureF - 32) * 5/9).toFixed(1);";
  // ptr +="unit.textContent = '°C';";
  // ptr +="} else {";
  // ptr +="temp.textContent = temperatureF.toFixed(1);";
  // ptr +="unit.textContent = '°F';";
  // ptr +="}";
  // ptr +="isFahrenheit = !isFahrenheit;";
  // ptr +="}";
  // ptr +="</script><script>";
  // ptr +="const toggleBox = document.getElementById(\"fatigue\");";
  // ptr +="const extraText = document.getElementById(\"hypoxia\");";
  // ptr +="toggleBox.addEventListener(\"change\", function() {";
  // ptr +="extraText.style.display = this.checked ? \"block\" : \"none\";";
  // ptr +="});";
  //fatigue conditions
  if ( high_body_temperature == true && low_SPO2 ==true && high_heart_rate == true  ){
    ptr += "<p> Your symptoms indicate fatigue condition. So please take some rest. </p>";
  }

  //hypoxia
  if ( high_heart_rate == true && low_SPO2 ==true){
    ptr += "<p> Your symptoms indicate Hypoxia condition.If you are having diziness \n please consult a nearby medical care </p>";
  }

  if(rate_of_ascent_stage1 == true  ){
    ptr += "<p> As per your altitude your rate of altitude ascent is high.Please slow down for better condition adaptation and take atleast a day break for 3 days. </p>";
  }

  if(rate_of_ascent_stage2 == true  ){
    ptr += "<p> As per your altitude your rate of altitude ascent is high.Please slow down for better condition adaptation and take atleast a 2-day break for every 1000m ascent. </p>";
  }

  if(rate_of_descent_stage1 == true  ){
    ptr += "<p> As per your altitude your rate of altitude descent is high.Please slow down for better condition adaptation and take atleast a day break for 3 days. </p>";
  }

  if(rate_of_descent_stage2 == true  ){
    ptr += "<p> As per your altitude your rate of altitude descent is high.Please slow down for better condition adaptation and take atleast a 2-day break for every 1000m descent. </p>";
  }

  if(rate_of_compressive_pressure == true && high_heart_rate == true && low_SPO2 ==true ){
    ptr +="<p>Your present environment conditions indicate Decompression Sickness. Please consult a nearby medical support.</p>";
  }

  if ( high_heart_rate == true && low_SPO2 ==true && rate_of_ascent_stage1 == true || rate_of_ascent_stage2 == true ){
    ptr += "<p> Your symptoms indicate Acute Mountain Sickness condition. </p>";
    ptr +="<p> This may lead to  High Altitude Pulminary Edema if breathing gets difficult./n This may lead to  High Altitude Cerebral Edema if you are having headache. </p>";
  }
  
  if(low_heart_rate ==true && low_SPO2 == true){
    ptr +="<p> Please place your finger at the sensor. </p>";
  }
  
  // ptr +="";
  // ptr +="";
  // ptr +="";
  // ptr +="";
  // ptr +="";
  // ptr +="";
  // ptr +="";
  // ptr +="";
 // ptr +="</script>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
```
```
import serial
import csv
import time
import pyautogui
import os

# === Serial Port Setup ===
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    print("✅ Serial port opened.", flush=True)
except serial.SerialException as e:
    print(f"❌ Serial Error: {e}", flush=True)
    exit()

# === CSV Setup ===
filename_csv = f"sensor_data_{time.strftime('%Y%m%d_%H%M%S')}.csv"
csv_file = open(filename_csv, "w", newline='')
writer = csv.writer(csv_file)
writer.writerow(["Millis", "Temperature", "Pressure", "Humidity", "Altitude", "IR Value"])
print(f"📝 Logging to: {filename_csv}", flush=True)

# === Screenshot Setup ===
screenshot_interval = 1800  # every 30 minutes
last_screenshot_time = time.time()
screenshot_dir = "screenshots"
os.makedirs(screenshot_dir, exist_ok=True)

# === Throttle Setup ===
log_interval = 1.0  # log once every second
last_log_time = time.time()

print("📸 Screenshots every 30 minutes → saved to /screenshots")
print("⏱ Logging every 1 second (skipping fast data). Press Ctrl+C to stop.\n", flush=True)

try:
    while True:
        line_bytes = ser.readline()
        try:
            line_raw = line_bytes.decode('utf-8', errors='ignore').strip()
        except Exception as e:
            print(f"⚠ Decode failed: {e}", flush=True)
            continue

        if not line_raw:
            continue

        values = [v.strip() for v in line_raw.split(',')]
        if len(values) == 6:
            current_time = time.time()

            # === Log only once per second ===
            if current_time - last_log_time >= log_interval:
                try:
                    writer.writerow(values)
                    print("✔", values, flush=True)
                    last_log_time = current_time
                except Exception as e:
                    print(f"❌ Write failed: {e}", flush=True)

            # === Screenshot every 30 minutes ===
            if current_time - last_screenshot_time >= screenshot_interval:
                try:
                    ts = time.strftime("%Y%m%d_%H%M%S")
                    screenshot_path = os.path.join(screenshot_dir, f"screenshot_{ts}.png")
                    pyautogui.screenshot(screenshot_path)
                    print(f"📸 Screenshot saved: {screenshot_path}", flush=True)
                    last_screenshot_time = current_time
                except Exception as e:
                    print(f"⚠ Screenshot error: {e}", flush=True)
        else:
            print(f"⚠ Malformed line (got {len(values)} values):", line_raw, flush=True)

except KeyboardInterrupt:
    print("\n🛑 Logging stopped by user.", flush=True)
finally:
    ser.close()
    csv_file.close()
    print("🔒 Serial port and file closed.", flush=True)
```
### For Plots
```
% Load the CSV file
data = readtable('24hrslog.csv');

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
data = readtable('24hrslog.csv');

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
data = readtable('24hrslog.csv');

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
data = readtable('24hrslog.csv');

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
data = readtable('24hrslog.csv');

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
## Testing Graphs
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/Humidity%20vs%20Altitude.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/IRvalue_drift.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/Pressure%20vs%20Altitude.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/Pressure_drift.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/Temperature%20vs%20Altitude.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/Temperature_drift.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/altitude_drift.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/heartbeat_accuracy.png" alt="image" width="600" height="600"/>
<img src="https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/test_graphs/humidity_drift.png" alt="image" width="600" height="600"/>

## Demonstration Video
https://github.com/vls-midhuna/Altitude-Adaptation-Monitor-for-Mountaineers-and-Pilots/blob/main/demo/demo_video.mp4

## Indian Sensor Substitution Plan
 To support Atmanirbhar Bharat, the prototype is designed to work with both imported and future Indian-made sensors.
 - It uses standard interfaces like I2C, UART, and analog input, which allows new sensors to be added or replaced easily without changing the main circuit.
 - The firmware follows a modular structure, so the code for one sensor can be replaced with another with minimal effort.
 - A calibration and validation layer is included to ensure Indian sensor replacements can be fine-tuned and verified for medical accuracy.
   
 Some possible Indian sensor alternatives include:

**SpO₂ & Pulse:** Upcoming biosensors developed by BEL, DRDO, or Indian health-tech startups

 **Temperature:** Analog thermistors or infrared sensors made by Indian electronics suppliers
 
 **Pressure/Altitude:** Sensors built by Indian MSMEs or labs like SAMEER
 
 To encourage local innovation, open hardware documents will be shared with Indian manufacturers so they can easily develop compatible sensor boards.











 
