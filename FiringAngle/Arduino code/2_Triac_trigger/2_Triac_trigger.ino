// Define the input/output pins
#define zeroCrossingPin 2
#define TriacTrigger 10

// Firing angle in degrees
const int firingAngle = 60;
const float timePerDegree = 55.56; // Time per degree in microseconds (for 50 Hz)

// Delay corresponding to 60 degrees
const unsigned long delayTime = firingAngle * timePerDegree;  // in microseconds 

// Flag to indicate when to fire TRIAC
volatile bool fireTriac = false;	

// interrupt handler
void fireTriacCallback() {
  // Set the flag to fire the TRIAC after the calculated delay
  fireTriac = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(TriacTrigger, OUTPUT);
  pinMode(zeroCrossingPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zeroCrossingPin), fireTriacCallback, RISING);
}

void loop() {
  if (fireTriac) {
    // After detecting the zero-crossing, delay for 60 degrees (3.33 ms)
    delayMicroseconds(delayTime);

    // Trigger the TRIAC (fire it by setting the pin HIGH briefly)
    digitalWrite(TriacTrigger, HIGH);
    delayMicroseconds(10);  // Fire pulse width to trigger TRIAC (adjust as needed)
    digitalWrite(TriacTrigger, LOW);
    
    // Reset the flag
    fireTriac = false;
  }
}
