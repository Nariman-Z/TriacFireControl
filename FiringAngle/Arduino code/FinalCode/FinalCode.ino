///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//                               CLOSED LOOP CONTROL                                 //
//                            TRIAC FIRING ANGLE SYSTEM                              //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//=================== LCD ===================//
// LCD connect to Arduino I2C (A4 = SDA, A5 = SCL)
LiquidCrystal_I2C lcd(0x27,16,2);

//============== Zero-Crossing ==============//
#define Interrupt0 2
#define Interrupt1 3

//============ Measure Frequency ============//
// period of pulse accumulation and serial output, milliseconds
const int MainPeriod = 100;
long previousMillis = 0; // will store last time of the cycle end

volatile unsigned long previousMicros = 0;
volatile unsigned long duration = 0;  // accumulates pulse width
volatile unsigned int pulsecount = 0; // accumulates pulse count

//================== TRIAC ==================//
#define TriacTrigger 10

// Firing angle in degrees
volatile int firingAngle = 90;

// Time per degree calculation (~55.56us for 50Hz & 46.29us for 60Hz)
volatile float freq = 50;
volatile float timePerDegree = 55.56;

// Delay corresponding to chosen degrees
volatile unsigned long delayTime = firingAngle * timePerDegree;  // in microseconds

//================= ZMPT10B =================//
#define zmptPin A0
int zmptSensor = 0;
int voltageRef = 220;
int measuredVoltage = 0;

//-------------------------------------------------------------------------------------
// External Interrupt 1 (Zero-Crossing detection) service routine
void freqCounterCallback() {
  unsigned long currentMicros = micros();
  duration += currentMicros - previousMicros;
  previousMicros = currentMicros;
  pulsecount++;
}

//-------------------------------------------------------------------------------------
void reportFrequency() {
    freq = 1e6 / float(duration) * float(pulsecount/2);

    Serial.print("duration: ");
    Serial.println(float(duration) , 2);
    Serial.print("pulsecount: ");
    Serial.println(float(pulsecount/2) , 2);
    Serial.print("Freq: ");
    Serial.print(freq , 2);
    Serial.println(" Hz");

    lcd.setCursor ( 0, 1 ); 
    lcd.print("Freq: ");
    lcd.print(freq , 2);
    lcd.print(" Hz");

    // clear counters
    duration = 0;
    pulsecount = 0;

    // Time per degree calculation (based on the full AC cycle)
    timePerDegree = (1e6 / freq) / 360; // in microseconds
}

//-------------------------------------------------------------------------------------
// External Interrupt 0 (Zero-Crossing detection) service routine
void fireTriacCallback() {
  // Read the voltage from the ZMPT10B sensor
  zmptSensor = analogRead(zmptPin);

  // Map the sensor reading to a voltage range (adjust based on your sensor calibration)
  measuredVoltage = (zmptSensor / 1023.0) * voltageRef; // Assuming 0-220V mapped to ADC

  // Adjust firing angle based on the voltage range
  switch (measuredVoltage)
  {
  case 0 ... 100:
    firingAngle -= 5;
    if (firingAngle < 30) firingAngle = 30; // Prevent negative firing angles
  break;

  case 120 ... 220:
    firingAngle += 5;
    if (firingAngle > 150) firingAngle = 150; // Prevent firing angle beyond 180 degrees
  break;

  default:
    firingAngle = 90;
  break;
  }

  // Delay corresponding to reference voltage
  delayTime = firingAngle * timePerDegree;

  // Generate TRIAC trigger pulse
  delayMicroseconds(delayTime); // Delay before firing TRIAC
  digitalWrite(TriacTrigger, HIGH);
  delayMicroseconds(50);        // 50us pulse to trigger TRIAC
  digitalWrite(TriacTrigger, LOW);
}

//=====================================================================================
void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  //initialize lcd screen
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Set zero-crossing pin as input with internal pull-up
  pinMode(Interrupt0, INPUT_PULLUP);
  pinMode(Interrupt1, INPUT_PULLUP);

  // Set TriacTrigger pin as output (TRIAC control)
  pinMode(TriacTrigger, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(Interrupt1), freqCounterCallback, FALLING);

  // Allow time to collect pulses before reporting frequency
  lcd.setCursor(0,0);
  lcd.print("Processing...");
  delay(30000); // Adjust delay as needed to accumulate a meaningful number of pulses
  reportFrequency();
  delay(5000);
  lcd.clear();
}

//=====================================================================================
void loop() {
  
  // Print debug information
  Serial.print("Voltage: ");
  Serial.print(measuredVoltage);
  Serial.print("V, Firing Angle: ");
  Serial.print(firingAngle);
  Serial.print(" degrees, Delay: ");
  Serial.print(delayTime);
  Serial.println("us");

  lcd.setCursor(0,0);
  lcd.print("Voltage: ");
  lcd.print(measuredVoltage);
  lcd.print(" v");
  lcd.setCursor(0,1);
  lcd.print((char)0xF2);
  lcd.print("=");
  lcd.print(firingAngle);
  lcd.print((char)0xDF);
  lcd.print(" , ");
  lcd.print(delayTime);
  lcd.print("us");

  // Attach interrupt handler for zero-crossing detection (FALLING edge)
  attachInterrupt(digitalPinToInterrupt(Interrupt0), fireTriacCallback, FALLING);
}

///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//                 © 2019 - 2024 Nariman Ziaie, All rights reserved                  //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////
//               see: https://github.com/Nariman-Z for more information              //
///////////////////////////////////////////////////////////////////////////////////////