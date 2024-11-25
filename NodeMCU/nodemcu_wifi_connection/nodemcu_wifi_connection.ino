#include <ESP8266WiFi.h>
 
const char *ssid =  "XXXXX";  
const char *pass =  "XXXXX";
  
void setup() 
{
       Serial.begin(115200);
       delay(10);
                
       Serial.println("Connecting to ");
       Serial.println(ssid); 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}
  
void loop() 
{ 
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  
  delay(1000);   
   
}