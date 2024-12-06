#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

#define DHTPIN 4         // Temperature and Humidity Sensor Pin (10K Resistor)(ESP32 pin G4)
#define MQ135PIN 36      // Air Quality Sensor Pin (1K Resistor)(ESP32 pin SP)
#define MQ2PIN 39        // Detection LPG, methane, smoke, and hydrogen(1k Resistor)(ESP32 pin SN)
#define MQ4PIN 34        // Detection only methane (ESP32 pin 34)

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); 

float temp;
float hum;
int MQ135V = 0;  // MQ135 sensor value
int MQ2V = 0;   // MQ2 sensor value
int MQ4V = 0;   // MQ4 sensor value


// Function declarations
void dht_sensor();
void mq135_sensor();
void mq2_sensor();
void mq4_sensor();
void display_data(float temperature, float humidity, int mq135, int mq2, int mq4);


// main code
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Weather Pollution Monitoring...");
  dht.begin();
  lcd.init();             // Initialize LCD
  lcd.backlight();  

  lcd.setCursor(2,0);
  lcd.print("Weather Pollution");
  lcd.setCursor(2,1);
  lcd.print("Monitoring System");
  lcd.setCursor(0,2);
  lcd.print("Frankfurt University");
  lcd.setCursor(2,3);
  lcd.print("Applied Sciences");

  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("****************");
  dht_sensor();
  Serial.println();
  mq135_sensor();
  Serial.println();
  mq2_sensor();
  Serial.println();
  mq4_sensor();
  Serial.println("****************");
  display_data(temp, hum, MQ135V, MQ2V, MQ4V);
  delay(3000);

}


void dht_sensor(){
  // Read humidity and temperature
  hum = dht.readHumidity();
  temp = dht.readTemperature(); // Read temperature in Celsius


  // Check if the readings are valid
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("°C");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
  }
}



void mq135_sensor(){
  MQ135V = analogRead(MQ135PIN);

  Serial.print("MQ135 Analong Value:");
  Serial.print(MQ135V);
  Serial.println();
}


void mq2_sensor(){
  MQ2V = analogRead(MQ2PIN);

  Serial.print("MQ2PIN Analong Value:");
  Serial.print(MQ2V);
  Serial.println();
}

void mq4_sensor(){
  MQ4V = analogRead(MQ4PIN);

  Serial.print("MQ4PIN Analong Value:");
  Serial.print(MQ4V);
  Serial.println();
}



void display_data(float temperature, float humidity, int mq135, int mq2, int mq4) {
  lcd.clear(); // Clear the screen

  // Display temperature and humidity on the first row
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Temp:");
  lcd.print(temperature, 1); // Display temperature with 1 decimal
  lcd.print("C ");

  lcd.setCursor(10, 0);
  lcd.print("Hum:");
  lcd.print(humidity, 1); // Display humidity with 1 decimal
  lcd.print("%");

  // Display MQ135 sensor value on the second row
  lcd.setCursor(0, 1);
  lcd.print("MQ135:");
  lcd.print(mq135);

  // Display MQ2 sensor value on the third row
  lcd.setCursor(0, 2);
  lcd.print("MQ2:");
  lcd.print(mq2);

  // Display MQ4 sensor value on the fourth row
  lcd.setCursor(0, 3);
  lcd.print("MQ4:");
  lcd.print(mq4);
}