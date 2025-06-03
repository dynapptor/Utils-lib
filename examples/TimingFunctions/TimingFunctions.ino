/*
 * TimingFunctions Example
 * Demonstrates non-blocking timing with onTimeSec and blocking delay with delayMs.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  
  // Demonstrate blocking delay
  Serial.println("Starting 1000ms delay...");
  uint32_t start = millis();
  delayMs(start, 1000);
  Serial.println("Delay complete!");
}

void loop() {
  // Non-blocking timing check
  static uint32_t startTime = millis();
  if (onTimeSec(startTime, 5)) {
    Serial.println("5 seconds elapsed!");
  }
}
