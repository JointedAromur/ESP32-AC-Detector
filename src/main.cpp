#include <Arduino.h>  // Required for PlatformIO
#include <math.h>     // Required for the sqrt function

/* * ESP32 Non-Contact AC Detector 
 * Based on the "Theory to Thing" experiment
 */

// 1. PIN CONFIGURATION
// Connect a 10cm jumper wire to GPIO 34. This is your antenna.
const int antennaPin = 34; 
const int ledPin = 2; // Most ESP32s have a built-in LED on GPIO 2

// 2. SETTINGS
const int numSamples = 150; // How many readings to take per batch
const int threshold = 40;   // Adjust this: Higher = less sensitive, Lower = more sensitive

void setup() {
  // Start Serial at 115200 baud for the Plotter
  Serial.begin(115200);
  
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Set ADC resolution (0 to 4095)
  analogReadResolution(12);
  
  Serial.println("Detector Starting... Open Serial Plotter");
}

void loop() {
  long sum = 0;
  float average = 0;
  long sqSum = 0;
  float rms = 0;
  int rawSamples[numSamples];

  // STEP 1: Capture a burst of samples
  for (int i = 0; i < numSamples; i++) {
    rawSamples[i] = analogRead(antennaPin);
    sum += rawSamples[i];
    delayMicroseconds(500); // 2000Hz sample rate
  }

  // STEP 2: Calculate the average (DC baseline)
  average = (float)sum / numSamples;

  // STEP 3: Calculate the RMS (AC Signal Strength)
  for (int i = 0; i < numSamples; i++) {
    float diff = (float)rawSamples[i] - average;
    sqSum += (diff * diff);
  }
  rms = sqrt((float)sqSum / numSamples);

  // STEP 4: OUTPUT TO SERIAL PLOTTER
  Serial.print("Baseline:0,Max:200,AC_Strength:");
  Serial.println(rms);

  // STEP 5: VISUAL FEEDBACK
  if (rms > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(30);
}
