#include <Arduino.h>
#include <utils.h>

void setup() {
  Serial.begin(115200);
  delay(10);
  char xx[] = "\"one\",\"two\",\"tree\"";

  const char *ar[3]{};

  split_str(xx, xx, 18, ar, 3, ',');
  for (size_t i = 0; i < 3; i++)
  {
    Serial.println(ar[i]);
  }
  

}

void loop() {
}
