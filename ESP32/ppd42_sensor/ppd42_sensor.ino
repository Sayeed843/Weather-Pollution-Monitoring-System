#define PPD42_PIN 25 // GPIO pin connected to PPD42's DIGITAL pin

unsigned long duration;
unsigned long startTime;
unsigned long sampleTime = 30000; // 30 seconds
float ratio;
float concentration;

void setup() {
  Serial.begin(115200);
  pinMode(PPD42_PIN, INPUT);
  startTime = millis(); // Start time for sampling
}

void loop() {
  duration = 0; // Reset pulse duration
  unsigned long currentTime = millis();

  // Sample for a defined time period
  while ((currentTime - startTime) < sampleTime) {
    duration += pulseIn(PPD42_PIN, LOW); // Measure the duration of LOW pulses
    currentTime = millis();
  }

  // Calculate the ratio of LOW pulse time to the total sampling time
  ratio = duration / (sampleTime * 10.0); // Normalize ratio
  concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // Formula for PM concentration

  // Output results
  Serial.print("Low Pulse Occupancy (LPO): ");
  Serial.println(ratio * 100, 2); // LPO in %
  Serial.print("Dust Concentration: ");
  Serial.print(concentration, 2);
  Serial.println(" ug/m3");

  startTime = millis(); // Reset sampling start time
}
