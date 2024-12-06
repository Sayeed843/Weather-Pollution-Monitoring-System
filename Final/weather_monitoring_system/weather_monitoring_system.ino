#include "DHT.h"

#define DHTPIN 4         // Temperature and Humidity Sensor Pin (10K Resistor)(ESP32 pin G4)
#define MQ135PIN 36      // Air Quality Sensor Pin (1K Resistor)(ESP32 pin SP)
#define MQ2PIN 39        // Detection LPG, methane, smoke, and hydrogen(1k Resistor)(ESP32 pin SN)
#define MQ4PIN 34        // Detection only methane (ESP32 pin 34)

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

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


// main code
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Weather Pollution Monitoring...");
  dht.begin();
  delay(200);

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
  int MQ2V = analogRead(MQ2PIN);

  Serial.print("MQ2PIN Analong Value:");
  Serial.print(MQ2V);
  Serial.println();
}

void mq4_sensor(){
  int MQ4V = analogRead(MQ4PIN);

  Serial.print("MQ4PIN Analong Value:");
  Serial.print(MQ4V);
  Serial.println();
}