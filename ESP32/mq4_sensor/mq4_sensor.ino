int MQ4Pin = 34;  // Define the analog pin for the MQ4 sensor(detect methane (CH₄))(ESP32 pin 34)
int MQ4Value = 0; // Variable to store the analog reading

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the MQ4 sensor
  MQ4Value = analogRead(MQ4Pin);

  // Display the analog value in the Serial Monitor
  Serial.print("MQ4 Analog Value: ");
  Serial.println(MQ4Value);

  // Delay for stability
  delay(1000);
}
