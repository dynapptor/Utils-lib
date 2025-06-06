/*
 * BCDConversion Example
 * Demonstrates BCD to decimal and decimal to BCD conversion using BCD2DEC and DEC2BCD.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>

void setup() {
  Serial.begin(9600);
  
  // Convert decimal to BCD
  uint8_t decimal = 25;
  uint8_t bcd = dec2bcd(decimal);
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" -> BCD: 0x");
  Serial.println(bcd, HEX); // Should print 0x25
  
  // Convert BCD back to decimal
  uint8_t convertedDecimal = bcd2dec(bcd);
  Serial.print("BCD: 0x");
  Serial.print(bcd, HEX);
  Serial.print(" -> Decimal: ");
  Serial.println(convertedDecimal); // Should print 25
}

void loop() {
  // No periodic tasks needed
}
