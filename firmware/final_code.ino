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
const char* ssid = "vivo Y33T";  // Enter SSID here
const char* password = "qwertyuiop";  //Enter Password here

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