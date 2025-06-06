/*
 * TimingFunctions Example
 * Demonstrates non-blocking timing with onTimeSec and blocking delay with delayMs.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>

void setup() {
  Serial.begin(9600);

  // Demonstrate blocking delay
  Serial.println("Starting 1000ms delay...");
  uint32_t start = millis();
  delay_ms(start, 1000);
  Serial.println("Delay complete!");
}

void loop() {
  // Non-blocking timing check
  static uint32_t startTime = millis();
  if (on_sec(&startTime, 5, true)) {
    Serial.println("5 seconds elapsed!");
  }
}
