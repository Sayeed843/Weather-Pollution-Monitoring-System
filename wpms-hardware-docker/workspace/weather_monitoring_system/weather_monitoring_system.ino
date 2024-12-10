#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4         // Temperature and Humidity Sensor Pin (10K Resistor)(ESP32 pin G4)
#define MQ135PIN 36      // Air Quality Sensor Pin (1K Resistor)(ESP32 pin SP)
#define MQ2PIN 39        // Detection LPG, methane, smoke, and hydrogen(1k Resistor)(ESP32 pin SN)
#define MQ4PIN 34        // Detection only methane (ESP32 pin 34)
#define PPD42_PIN 25     // GPIO pin connected to PPD42's DIGITAL pin

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD with address 0x27, 20x4 size

float temp;
float hum;
int MQ135V = 0;   // MQ135 sensor value
int MQ2V = 0;     // MQ2 sensor value
int MQ4V = 0;     // MQ4 sensor value
float dustRatio;  // Dust ratio (LPO in %)
float dustConcentration; // Dust concentration in µg/m³
float curr_dust;

unsigned long duration;
unsigned long startTime;
unsigned long sampleTime = 30000; // 30 seconds for dust sampling

// Function declarations
void dht_sensor();
void mq135_sensor();
void mq2_sensor();
void mq4_sensor();
float dust_sensor();
void display_data(float temperature, float humidity, int mq135, int mq2, int mq4, float dustConc);

void setup() {
  Serial.begin(115200);
  Serial.println("Weather Pollution Monitoring...");
  dht.begin();
  lcd.init(); // Initialize LCD
  lcd.backlight();

  // Display system information on LCD
  lcd.setCursor(2, 0);
  lcd.print("Weather Pollution");
  lcd.setCursor(2, 1);
  lcd.print("Monitoring System");
  lcd.setCursor(0, 2);
  lcd.print("Frankfurt University");
  lcd.setCursor(2, 3);
  lcd.print("Applied Sciences");

  delay(3000);
  lcd.clear();

  startTime = millis(); // Initialize sampling start time for dust sensor
}

void loop() {
  Serial.println("****************");
  
  dht_sensor();
  Serial.println();
  mq135_sensor();
  Serial.println();
  mq2_sensor();
  Serial.println();
  mq4_sensor();
  Serial.println();
  curr_dust = dust_sensor(); // Read PPD42 sensor data
  Serial.println("****************");

  display_data(temp, hum, MQ135V, MQ2V, MQ4V, curr_dust);
  delay(3000);
}

// Function to read DHT sensor data
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

// Function to read MQ135 sensor data
void mq135_sensor() {
  MQ135V = analogRead(MQ135PIN);
  Serial.print("MQ135 Analog Value: ");
  Serial.print(MQ135V);
  Serial.println();
}

// Function to read MQ2 sensor data
void mq2_sensor() {
  MQ2V = analogRead(MQ2PIN);
  Serial.print("MQ2 Analog Value: ");
  Serial.print(MQ2V);
  Serial.println();
}

// Function to read MQ4 sensor data
void mq4_sensor() {
  MQ4V = analogRead(MQ4PIN);
  Serial.print("MQ4 Analog Value: ");
  Serial.print(MQ4V);
  Serial.println();
}

float dust_sensor() {
  static unsigned long dustStartTime = millis();
  static unsigned long dustDuration = 0;
  static bool dustSampling = true;

  // Check if we're in the sampling period
  if (dustSampling) {
    if (millis() - dustStartTime < sampleTime) {
      // Accumulate pulse duration during LOW periods
      dustDuration += pulseIn(PPD42_PIN, LOW);
    } else {
      // End of sampling, calculate dust concentration
      dustSampling = false;

      // Calculate the ratio of LOW pulse time to the total sampling time
      dustRatio = dustDuration / (sampleTime * 10.0); // Normalize ratio
      dustConcentration = 1.1 * pow(dustRatio, 3) - 3.8 * pow(dustRatio, 2) + 520 * dustRatio + 0.62;

      Serial.print("Low Pulse Occupancy (LPO): ");
      Serial.println(dustRatio * 100, 2); // LPO in %
      Serial.print("Dust Concentration: ");
      Serial.print(dustConcentration, 2);
      Serial.println(" µg/m³");

      // Reset variables for the next sampling period
      dustStartTime = millis();
      dustDuration = 0;
    }
  } else {
    // Ready for the next sampling period
    if (millis() - dustStartTime > sampleTime) {
      dustSampling = true; // Restart sampling
    }
  }

  return dustConcentration;
}



// Function to display data on the LCD
void display_data(float temperature, float humidity, int mq135, int mq2, int mq4, float dustConc) {
  lcd.clear(); // Clear the screen

  // Display temperature and humidity on the first row
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print("C Hum:");
  lcd.print(humidity, 1);
  lcd.print("%");

  // Display MQ135 sensor value on the second row
  lcd.setCursor(0, 1);
  lcd.print("MQ135:");
  lcd.print(mq135);

  // Display MQ2 sensor and  MQ4 sensor value on the third row
  lcd.setCursor(0, 2);
  lcd.print("MQ2:");
  lcd.print(mq2);

  // Display dust concentration on the fourth row
  lcd.setCursor(11, 2);
  lcd.print("MQ4:");
  lcd.print(mq4);

  lcd.setCursor(0, 3);
  lcd.print("Dust:");
  lcd.print(dustConc, 1);
  lcd.print("ug");
}
