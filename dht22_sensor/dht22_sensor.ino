#include "DHT.h"

#define DHTPIN 2   // Temperature and humidity sensor pin
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

float temp;
float hum;

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  Serial.println("Temperature and Humidity Sensor Initialized");
  dht.begin();  // Initialize the DHT sensor
}

void loop() {
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

  // Wait for 5 seconds before reading again
  delay(5000);
}
