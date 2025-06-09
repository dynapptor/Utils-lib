#include <Arduino.h>
#include <utils.h>

char *getItem(size_t ix, char *ar, size_t size) {
  if (ix == 0) return ar;
  char *p = ar;
  size_t i = 0;
  size_t counter = 0;

  while (i != size) {
    if (*p++ == '\0') counter++;
    if (ix == counter) return p;
    i++;
  }
  return '\0';
}

void setup() {
  Serial.begin(115200);

  char val[] = "one\0two\0tree\0for\0";

  Serial.println(getItem(0, val, 18));
  Serial.println(getItem(1, val, 18));
  Serial.println(getItem(2, val, 18));
  Serial.println(getItem(3, val, 18));

  return;
  bool i8a[] = {1, 0, 1, 1, 0, 1};
  char buf[100]{};
  join_bool(i8a, 6, buf, 100, ',', "\"ON\"", "\"OFF\"");

  Serial.println(buf);

  char xx[] = "\"one\",\"two\",\"tree\"";

  char i8[] = "[\"ON\",\"OFF\"]";
  bool v[2];
  split_bool(i8, v, 2, ',', "\"ON\"", "\"OFF\"");

  char in[] = "[1,2,3,4,5,6]";
  uint32_t ina[6];
  split_u32(in, ina, 6, ',');

  for (size_t i = 0; i < 6; i++) {
    Serial.println(ina[i]);
  }

  // const char *ar[3]{};

  // split_str(xx, xx, 18, ar, 3, ',');
}

void loop() {
}
