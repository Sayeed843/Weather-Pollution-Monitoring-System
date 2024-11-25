const int MQ135AV = 36;   // mq135 sensor for analong value (ESP SP Pin with 1k Resistor and 5V(not with sensor pin))

void setup() {
  Serial.begin(115200);
} 

void loop() {
  // put your main code here, to run repeatedly:
  MQ135AV = analogRead(MQ135AV);

  Serial.print("MQ135 Analong Value:");
  Serial.print(MQ135AV);
  Serial.println();

  delay(1000);

}
