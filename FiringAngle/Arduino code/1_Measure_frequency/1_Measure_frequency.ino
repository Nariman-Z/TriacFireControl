// Define the input/output pins
#define zeroCrossingPin 2

// period of pulse accumulation and serial output, milliseconds
const int MainPeriod = 100;
long previousMillis = 0;  // will store last time of the cycle end

volatile unsigned long previousMicros = 0;
volatile unsigned long duration = 0;  // accumulates pulse width
volatile unsigned int pulsecount = 0; // accumulates pulse count

// interrupt handler
void freqCounterCallback() {
  unsigned long currentMicros = micros();
  duration += currentMicros - previousMicros;
  previousMicros = currentMicros;
  pulsecount++;
}

void reportFrequency() {
    float freq = 1e6 / float(duration) * float(pulsecount/2);
    Serial.print("Freq:");
    Serial.print(freq , 2);
    Serial.println(" Hz");

    // clear counters
    duration = 0;
    pulsecount = 0;
}

void setup() {
  Serial.begin(115200); 
  pinMode(zeroCrossingPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zeroCrossingPin), freqCounterCallback, RISING);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= MainPeriod) 
  {
    previousMillis = currentMillis;    
    reportFrequency();
  }
}
