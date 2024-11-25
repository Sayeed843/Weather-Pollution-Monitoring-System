int MQ2Pin = 39;  // Define the analog pin for the MQ2 sensor(detect LPG, methane, smoke, and hydrogen)
int MQ2Value = 0; // Variable to store the analog reading

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the MQ2 sensor
  MQ2Value = analogRead(MQ2Pin);

  // Display the analog value in the Serial Monitor
  Serial.print("MQ2 Analog Value: ");
  Serial.println(MQ2Value);

  // Delay for stability
  delay(1000);
}
