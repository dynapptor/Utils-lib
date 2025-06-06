/*
 * ArrayOperations Example
 * Demonstrates joining and splitting arrays using joinInt16 and spliti16.
 * Part of the ArduinoUtilityLib.
 */

#include <utils.h>

void setup() {
  Serial.begin(9600);

  // Join an array of int16_t
  int16_t arr[] = {10, 20, 30};
  char buffer[20];
  join_i16(arr, 3, buffer, 20, ',');
  Serial.print("Joined array: ");
  Serial.println(buffer);  // Prints "10,20,30"

  // Split a string into an array
  char str[] = "100,200,300";
  int16_t splitArr[3];
  split_i16(str, splitArr, ',', 3);
  Serial.print("Split array: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(splitArr[i]);
    if (i < 2) Serial.print(",");
  }
  Serial.println();  // Prints "100,200,300"
}

void loop() {
  // No periodic tasks needed
}
