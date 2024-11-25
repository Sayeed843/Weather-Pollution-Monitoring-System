#include "DHT.h"

#define DHTPIN 4      // Temperature and Humidity Sensor Pin (10K Resistor)
#define MQ135PIN 36   // Air Quality Sensor Pin (1K Resistor)

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

float temp;
float hum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Weather Pollution Monitoring...");
  dht.begin();
  delay(200);

}

void loop() {
  // put your main code here, to run repeatedly:
  dht_sensor();
  mq135_sensor();
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
  int MQ135V = analogRead(MQ135PIN);

  Serial.print("MQ135 Analong Value:");
  Serial.print(MQ135V);
  Serial.println();
}
