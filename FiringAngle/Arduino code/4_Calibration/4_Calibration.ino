int adc_max = 0;       // Variable to store the maximum sensor value
int adc_min = 1023;    // Variable to store the minimum sensor value
long tiempo_init;      // Variable to store the initial time

void setup() {
  Serial.begin(115200);   // Initialize the serial communication
  tiempo_init = millis(); // Get the current time in milliseconds
}

void loop() {
     // Check if 500 milliseconds have passed
  if ((millis() - tiempo_init) > 500) {
    adc_max = 0;         // Reset the maximum sensor value
    adc_min = 1023;      // Reset the minimum sensor value
    tiempo_init = millis(); // Update the initial time
  }

  int sensorValue = analogRead(A0); // Read the analog input from pin A0

  if (sensorValue > adc_max) {
    adc_max = sensorValue; // Update the maximum value if a new maximum is found
  } else if (sensorValue < adc_min) {
    adc_min = sensorValue; // Update the minimum value if a new minimum is found
  }

  // Print the maximum and minimum values to the serial monitor
  Serial.print("adc_max: ");
  Serial.print(adc_max);
  Serial.print("   adc_min: ");
  Serial.println(adc_min);

  delay(1); // Small delay for stability between each iteration
}
