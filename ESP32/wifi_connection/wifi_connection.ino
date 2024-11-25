#include <WiFi.h>

const char* ssid = "MagentaWLAN-U0YS";
const char* password = "XXXXXXXXXXX";

void setup(){
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("My Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){
  Serial.print("MY Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

}