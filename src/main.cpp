#include <Arduino.h>
#include <utils.h>

void setup() {
  Serial.begin(115200);

  const char c[] = "178.55,33.678,55.66666,40,44,199";
  float buf[6]{};
  split_float(c, buf, 6, '.', ',');

  for (size_t i = 0; i < 6; i++) {
    Serial.println(buf[i]);
  }
}

void loop() {
}
