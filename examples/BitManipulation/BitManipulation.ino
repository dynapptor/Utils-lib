/*
 * BitManipulation Example
 * Demonstrates the use of the getBits function to extract a range of bits from a value.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>

void setup() {
  Serial.begin(9600);

  // Example value
  uint16_t value = 0b1010101010101010;  // 0xAAAA

  // Extract 3 bits starting from position 4
  uint16_t bits = getBits(value, 4, 3);

  Serial.print("Original value (binary): ");
  Serial.println(value, BIN);
  Serial.print("Extracted bits (4-6): ");
  Serial.println(bits, BIN);  // Should print 101
}

void loop() {
  // No periodic tasks needed
}
