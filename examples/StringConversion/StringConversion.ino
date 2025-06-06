/*
 * StringConversion Example
 * Demonstrates converting numbers to strings and strings to doubles using i16toa, u16toa, and atod.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>

void setup() {
  Serial.begin(9600);

  // Convert int16_t to string
  char buffer[10];
  i16_to_str(-1234, buffer, 10);
  Serial.print("Int16 to string: ");
  Serial.println(buffer);  // Prints "-1234"

  // Convert uint16_t to string (hex)
  u16_to_str(1234, buffer, 10, 16);
  Serial.print("Uint16 to string (hex): ");
  Serial.println(buffer);  // Prints "4d2"

  // Convert string to double
  const char *str = "3.14159";
  double d = str_to_double(str);
  Serial.print("String to double: ");
  Serial.println(d, 6);  // Prints 3.141590
}

void loop() {
  // No periodic tasks needed
}
