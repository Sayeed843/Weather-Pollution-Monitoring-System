#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// WiFi credentials
const char* ssid = "From Zero";
const char* password = "xxxxx";
const char* serverUrl = "http://192.168.216.109:8000/pollution/data/";

// DHT22 Sensor Configuration
#define DHTPIN 4          // Temperature and Humidity Sensor Pin (ESP32 pin G4)
#define DHTTYPE DHT22

// MQ Sensors Configuration
#define MQ135PIN 36       // Air Quality Sensor Pin (ESP32 pin SP)
#define MQ2PIN 39         // Detection LPG, methane, smoke (ESP32 pin SN)
#define MQ4PIN 34         // Detection only methane (ESP32 pin 34)

// PPD42 Sensor Configuration
#define PPD42_PIN 25      // GPIO pin connected to PPD42's DIGITAL pin

// Initialize DHT and LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD with address 0x27, 20x4 size

// Sensor Values
float temp;
float hum;
int MQ135V = 0;
int MQ2V = 0;
int MQ4V = 0;
float dustRatio;
float dustConcentration;
float curr_dust;

unsigned long duration;
unsigned long startTime;
unsigned long sampleTime = 30000; // 30 seconds for dust sampling

// Function Declarations
void connect_to_wifi();
void dht_sensor();
void mq135_sensor();
void mq2_sensor();
void mq4_sensor();
float dust_sensor();
void display_data(float temperature, float humidity, int mq135, int mq2, int mq4, float dustConc);
void send_data_to_server();

void setup() {
  Serial.begin(115200);
  Serial.println("Weather Pollution Monitoring...");

  // Initialize DHT sensor
  dht.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Connect to WiFi
  connect_to_wifi();

  // Initialize Dust Sensor
  startTime = millis();
}

void loop() {
  Serial.println("****************");

  dht_sensor();
  mq135_sensor();
  mq2_sensor();
  mq4_sensor();
  curr_dust = dust_sensor();

  Serial.println("****************");

  display_data(temp, hum, MQ135V, MQ2V, MQ4V, curr_dust);
  send_data_to_server();

  delay(3000);
}

// Function to Connect to WiFi
void connect_to_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");

  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.print(".");
    delay(500);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("My Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
  delay(3000);
  lcd.clear();
}

// Function to Read DHT Sensor Data
void dht_sensor() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println("%");
}

// Function to Read MQ135 Sensor Data
void mq135_sensor() {
  MQ135V = analogRead(MQ135PIN);
  Serial.print("MQ135 Analog Value: ");
  Serial.println(MQ135V);
}

// Function to Read MQ2 Sensor Data
void mq2_sensor() {
  MQ2V = analogRead(MQ2PIN);
  Serial.print("MQ2 Analog Value: ");
  Serial.println(MQ2V);
}

// Function to Read MQ4 Sensor Data
void mq4_sensor() {
  MQ4V = analogRead(MQ4PIN);
  Serial.print("MQ4 Analog Value: ");
  Serial.println(MQ4V);
}

// Function to Read Dust Sensor Data
float dust_sensor() {
  static unsigned long dustStartTime = millis();
  static unsigned long dustDuration = 0;

  if (millis() - dustStartTime < sampleTime) {
    dustDuration += pulseIn(PPD42_PIN, LOW);
  } else {
    dustRatio = dustDuration / (sampleTime * 10.0);
    dustConcentration = 1.1 * pow(dustRatio, 3) - 3.8 * pow(dustRatio, 2) + 520 * dustRatio + 0.62;

    Serial.print("Dust Concentration: ");
    Serial.print(dustConcentration, 2);
    Serial.println(" µg/m³");

    dustStartTime = millis();
    dustDuration = 0;
  }

  return dustConcentration;
}

// Function to Send Data to the Server
void send_data_to_server() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    StaticJsonDocument<256> jsonDoc;
    jsonDoc["temperature"] = temp;
    jsonDoc["humidity"] = hum;
    jsonDoc["air_quality"] = MQ135V;
    jsonDoc["gas_mq2"] = MQ2V;
    jsonDoc["gas_mq4"] = MQ4V;
    jsonDoc["dust"] = curr_dust;

    String payload;
    serializeJson(jsonDoc, payload);

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected, unable to send data.");
  }
}

// Function to Display Data on the LCD
void display_data(float temperature, float humidity, int mq135, int mq2, int mq4, float dustConc) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print("C Hum:");
  lcd.print(humidity, 1);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("MQ135:");
  lcd.print(mq135);

  lcd.setCursor(0, 2);
  lcd.print("MQ2:");
  lcd.print(mq2);
  lcd.setCursor(11, 2);
  lcd.print("MQ4:");
  lcd.print(mq4);

  lcd.setCursor(0, 3);
  lcd.print("Dust:");
  lcd.print(dustConc, 1);
  lcd.print("ug");
}
