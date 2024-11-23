int MQ135AV;   // mq135 sensor for analong value
//int MQ135DV;   // mq135 sensor for digital value

void setup() {
  // put your setup code here, to run once:
  // pinMode(4, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  MQ135AV = analogRead(A0);
  //MQ135DV = digitalRead(2);

  Serial.print("MQ135 Analong Value:");
  Serial.print(MQ135AV);
  Serial.println();

  /*
  Serial.print("MQ135 Digital Value:");
  Serial.print(MQ135DV);
  Serial.println();
  */
  delay(1000);

}
