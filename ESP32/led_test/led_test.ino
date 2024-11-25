void setup() {
  Serial.begin(115200);
  Serial.println("My first ESP32 program");
  pinMode(4,OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH); // Blue LED on
  delay(500); // wait during 500 ms
  digitalWrite(4, LOW); // Blue LED off
  delay(500); // wait during 500 ms
}