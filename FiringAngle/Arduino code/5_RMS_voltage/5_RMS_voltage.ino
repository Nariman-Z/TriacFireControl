// Calibration values obtained from the sketch: volt_ac_cal
int adc_max = 760;                // Maximum sensor value during calibration
int adc_min = 261;                // Minimum sensor value during calibration

float volt_multi = 231;           // RMS voltage obtained from a multimeter
float volt_multi_p;               // Peak voltage
float volt_multi_n;               // Negative peak voltage

void setup() {
  Serial.begin(115200);

  volt_multi_p = volt_multi * 1.4142;   // Peak voltage = RMS voltage * 1.4142 
  volt_multi_n = -volt_multi_p;         // Negative peak voltage
}

void loop() {
  float volt_rms = get_voltage();       // Root Mean Square voltage (V-RMS)

  Serial.print("Vrms: ");
  Serial.print(volt_rms, 3);
  Serial.println(" VAC");

  // Delay for a certain interval if needed
  //delay(100);
}

float get_voltage() {
  float adc_sample;
  float volt_inst = 0;
  float sum = 0;
  float volt;
  long init_time = millis();
  int N = 0;

     // Duration of 0.5 seconds
  while ((millis() - init_time) < 500) {
    adc_sample = analogRead(A0);            // Sensor voltage
    volt_inst = map(adc_sample, adc_min, adc_max, volt_multi_n, volt_multi_p);
    sum += sq(volt_inst);                    // Sum of Squares
    N++;
    delay(1);
  }

  //Serial.print("N: ");
  //Serial.println(N);

  volt = sqrt(sum / N);                     // RMS equation
  return volt;
}
