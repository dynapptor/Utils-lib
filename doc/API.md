# Arduino Utility Library API Documentation

## Table of Contents

- [Overview](#overview)
- [Macros](#macros)
- [Unions](#unions)
  - [union16](#union16)
  - [union32](#union32)
  - [union64](#union64)
- [Functions](#functions)
  - [Bit Manipulation](#bit-manipulation)
  - [BCD Conversion](#bcd-conversion)
  - [Timing Functions](#timing-functions)
  - [String Manipulation](#string-manipulation)
  - [String Conversion](#string-conversion)
  - [Array Operations](#array-operations)

## Overview

The Arduino Utility Library provides utility functions and unions for data manipulation, conversion, and timing in Arduino projects. It is designed for efficiency in resource-constrained environments.

## Macros

| Macro | Description |
|-------|-------------|
| `I8_CHR_MAX` | Maximum characters for `int8_t` (e.g., "-128"). Value: 5. |
| `U8_CHR_MAX` | Maximum characters for `uint8_t` (e.g., "255"). Value: 4. |
| `I16_CHR_MAX` | Maximum characters for `int16_t` (e.g., "-32768"). Value: 7. |
| `U16_CHR_MAX` | Maximum characters for `uint16_t` (e.g., "65535"). Value: 6. |
| `I32_CHR_MAX` | Maximum characters for `int32_t` (e.g., "-2147483648"). Value: 12. |
| `U32_CHR_MAX` | Maximum characters for `uint32_t` (e.g., "4294967295"). Value: 11. |
| `I64_CHR_MAX` | Maximum characters for `int64_t` (e.g., "-9223372036854775808"). Value: 22. |
| `U64_CHR_MAX` | Maximum characters for `uint64_t` (e.g., "18446744073709551615"). Value: 21. |

## Unions

### union16

**Description**: Union for 16-bit data type conversions, allowing flexible access to a 16-bit value as different types.

**Members**:
- `uint16_t u16`: Unsigned 16-bit integer.
- `int16_t i16`: Signed 16-bit integer.
- `uint8_t u8[2]`: Array of two unsigned 8-bit integers.
- `int8_t i8[2]`: Array of two signed 8-bit integers.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  union16 data;
  data.u16 = 0x1234;
  Serial.print("High byte: ");
  Serial.println(data.u8[1], HEX); // Prints 12
  Serial.print("Low byte: ");
  Serial.println(data.u8[0], HEX); // Prints 34
}

void loop() {}
```

### union32

**Description**: Union for 32-bit data type conversions, including floating-point.

**Members**:
- `uint32_t u32`: Unsigned 32-bit integer.
- `int32_t i32`: Signed 32-bit integer.
- `uint16_t u16[2]`: Array of two unsigned 16-bit integers.
- `int16_t i16[2]`: Array of two signed 16-bit integers.
- `uint8_t u8[4]`: Array of four unsigned 8-bit integers.
- `int8_t i8[4]`: Array of four signed 8-bit integers.
- `float f`: 32-bit floating-point value.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  union32 data;
  data.f = 3.14;
  Serial.print("Float as uint32: ");
  Serial.println(data.u32, HEX); // Prints float as hex
  Serial.print("First byte: ");
  Serial.println(data.u8[0], HEX); // Prints first byte
}

void loop() {}
```

### union64

**Description**: Union for 64-bit data type conversions, including double-precision floating-point.

**Members**:
- `uint64_t u64`: Unsigned 64-bit integer.
- `int64_t i64`: Signed 64-bit integer.
- `uint32_t u32[2]`: Array of two unsigned 32-bit integers.
- `int32_t i32[2]`: Array of two signed 32-bit integers.
- `uint16_t u16[4]`: Array of four unsigned 16-bit integers.
- `int16_t i16[4]`: Array of four signed 16-bit integers.
- `uint8_t u8[8]`: Array of eight unsigned 8-bit integers.
- `int8_t i8[8]`: Array of eight signed 8-bit integers.
- `double d`: 64-bit double-precision floating-point value.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  union64 data;
  data.d = 3.14159;
  Serial.print("Double as uint64: ");
  Serial.println((uint32_t)(data.u64 >> 32), HEX); // Prints high 32 bits
  Serial.println((uint32_t)(data.u64 & 0xFFFFFFFF), HEX); // Prints low 32 bits
}

void loop() {}
```

## Functions

### Bit Manipulation

#### `getBits`

**Signature**: `template <typename T> static T getBits(T v, uint8_t start, uint8_t count)`

**Description**: Extracts a specified range of bits from a value.

**Parameters**:
- `v`: The input value from which bits are extracted.
- `start`: The starting bit position (0-based).
- `count`: The number of bits to extract.

**Returns**: The extracted bits as a value of type `T`.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint16_t value = 0b1010101010101010;
  uint16_t bits = getBits(value, 4, 3);
  Serial.print("Extracted bits: ");
  Serial.println(bits, BIN); // Prints 101
}

void loop() {}
```

### BCD Conversion

#### `bcd2dec`

**Signature**: `uint8_t bcd2dec(uint8_t bcd)`

**Description**: Converts a BCD (Binary-Coded Decimal) value to a decimal value.

**Parameters**:
- `bcd`: The BCD value to convert.

**Returns**: The equivalent decimal value.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint8_t bcd = 0x25; // BCD for 25
  uint8_t dec = bcd2dec(bcd);
  Serial.print("BCD to decimal: ");
  Serial.println(dec); // Prints 25
}

void loop() {}
```

#### `dec2bcd`

**Signature**: `uint8_t dec2bcd(uint8_t dec)`

**Description**: Converts a decimal value to a BCD (Binary-Coded Decimal) value.

**Parameters**:
- `dec`: The decimal value to convert.

**Returns**: The equivalent BCD value.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint8_t dec = 25;
  uint8_t bcd = dec2bcd(dec);
  Serial.print("Decimal to BCD: ");
  Serial.println(bcd, HEX); // Prints 25
}

void loop() {}
```

### Timing Functions

#### `on_min`

**Signature**: `bool on_min(uint32_t *t, uint32_t delay_min, bool reset = false)`

**Description**: Checks if a specified time (in minutes) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Pointer to the start time (in milliseconds).
- `delay_min`: The delay time in minutes.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: `true` if the delay has elapsed, `false` otherwise.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  static uint32_t start = millis();
  if (on_min(&start, 1, true)) {
    Serial.println("1 minute elapsed!");
  }
}
```

#### `on_sec`

**Signature**: `bool on_sec(uint32_t *t, uint32_t delay_sec, bool reset = false)`

**Description**: Checks if a specified time (in seconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Pointer to the start time (in milliseconds).
- `delay_sec`: The delay time in seconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: `true` if the delay has elapsed, `false` otherwise.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  static uint32_t start = millis();
  if (on_sec(&start, 5, true)) {
    Serial.println("5 seconds elapsed!");
  }
}
```

#### `on_ms`

**Signature**: `bool on_ms(uint32_t *t, uint32_t delay_ms, bool reset = false)`

**Description**: Checks if a specified time (in milliseconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Pointer to the start time (in milliseconds).
- `delay_ms`: The delay time in milliseconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: `true` if the delay has elapsed, `false` otherwise.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  static uint32_t start = millis();
  if (on_ms(&start, 1000, true)) {
    Serial.println("1000 ms elapsed!");
  }
}
```

#### `on_us`

**Signature**: `bool on_us(uint32_t *t, uint32_t delay_us, bool reset = false)`

**Description**: Checks if a specified time (in microseconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Pointer to the start time (in microseconds).
- `delay_us`: The delay time in microseconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: `true` if the delay has elapsed, `false` otherwise.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  static uint32_t start = micros();
  if (on_us(&start, 1000, true)) {
    Serial.println("1000 us elapsed!");
  }
}
```

#### `delay_us`

**Signature**: `void delay_us(uint32_t start, uint32_t wait_us)`

**Description**: Delays execution for a specified time (in microseconds).

**Parameters**:
- `start`: The start time (in microseconds).
- `wait_us`: The delay time in microseconds.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint32_t start = micros();
  delay_us(start, 1000);
  Serial.println("Delayed 1000 us");
}

void loop() {}
```

#### `delay_ms`

**Signature**: `void delay_ms(uint32_t start, uint32_t wait_ms)`

**Description**: Delays execution for a specified time (in milliseconds).

**Parameters**:
- `start`: The start time (in milliseconds).
- `wait_ms`: The delay time in milliseconds.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint32_t start = millis();
  delay_ms(start, 1000);
  Serial.println("Delayed 1000 ms");
}

void loop() {}
```

### String Manipulation

#### `str_reverse`

**Signature**: `char *str_reverse(char *str)`

**Description**: Reverses the characters in a null-terminated string.

**Parameters**:
- `str`: The input string to reverse.

**Returns**: Pointer to the reversed string.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "hello";
  str_reverse(str);
  Serial.print("Reversed string: ");
  Serial.println(str); // Prints "olleh"
}

void loop() {}
```

#### `chr_count`

**Signature**: `size_t chr_count(const char *str, char c)`

**Description**: Counts occurrences of a character in a string.

**Parameters**:
- `str`: The input string.
- `c`: The character to count.

**Returns**: The number of occurrences of the character.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "hello";
  size_t count = chr_count(str, 'l');
  Serial.print("Occurrences of 'l': ");
  Serial.println(count); // Prints 2
}

void loop() {}
```

#### `str_count`

**Signature**: `size_t str_count(const char *str, const char *find)`

**Description**: Counts occurrences of a substring in a string.

**Parameters**:
- `str`: The input string.
- `find`: The substring to count.

**Returns**: The number of occurrences of the substring.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "hello hello";
  size_t count = str_count(str, "hello");
  Serial.print("Occurrences of 'hello': ");
  Serial.println(count); // Prints 2
}

void loop() {}
```

#### `str_cut`

**Signature**: `void str_cut(char *str, char **ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of substrings based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array of substring pointers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "a,b,c";
  char *ar[3];
  str_cut(str, ar, 3, ',');
  Serial.println("Split strings:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(ar[i]); // Prints "a", "b", "c"
  }
}

void loop() {}
```

### String Conversion

#### `bool_to_str`

**Signature**: `char *bool_to_str(bool num, char *str, uint8_t str_len, const char *t = nullptr, const char *f = nullptr)`

**Description**: Converts a boolean value to a string.

**Parameters**:
- `num`: The boolean value to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `t`: Optional string to represent true (default: "true").
- `f`: Optional string to represent false (default: "false").

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[10];
  bool_to_str(true, buffer, sizeof(buffer), "yes", "no");
  Serial.print("Boolean to string: ");
  Serial.println(buffer); // Prints "yes"
}

void loop() {}
```

#### `i8_to_str`

**Signature**: `char *i8_to_str(int8_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts an 8-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[10];
  i8_to_str(-128, buffer, sizeof(buffer), 10);
  Serial.print("Int8 to string: ");
  Serial.println(buffer); // Prints "-128"
}

void loop() {}
```

#### `u8_to_str`

**Signature**: `char *u8_to_str(uint8_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts an 8-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[10];
  u8_to_str(255, buffer, sizeof(buffer), 16);
  Serial.print("Uint8 to string: ");
  Serial.println(buffer); // Prints "ff"
}

void loop() {}
```

#### `i16_to_str`

**Signature**: `char *i16_to_str(int16_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 16-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[10];
  i16_to_str(-32768, buffer, sizeof(buffer), 10);
  Serial.print("Int16 to string: ");
  Serial.println(buffer); // Prints "-32768"
}

void loop() {}
```

#### `u16_to_str`

**Signature**: `char *u16_to_str(uint16_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 16-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[10];
  u16_to_str(65535, buffer, sizeof(buffer), 16);
  Serial.print("Uint16 to string: ");
  Serial.println(buffer); // Prints "ffff"
}

void loop() {}
```

#### `i32_to_str`

**Signature**: `char *i32_to_str(int32_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 32-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[12];
  i32_to_str(-2147483648, buffer, sizeof(buffer), 10);
  Serial.print("Int32 to string: ");
  Serial.println(buffer); // Prints "-2147483648"
}

void loop() {}
```

#### `u32_to_str`

**Signature**: `char *u32_to_str(uint32_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 32-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[12];
  u32_to_str(4294967295, buffer, sizeof(buffer), 16);
  Serial.print("Uint32 to string: ");
  Serial.println(buffer); // Prints "ffffffff"
}

void loop() {}
```

#### `i64_to_str`

**Signature**: `char *i64_to_str(int64_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 64-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[22];
  i64_to_str(-9223372036854775807, buffer, sizeof(buffer), 10);
  Serial.print("Int64 to string: ");
  Serial.println(buffer); // Prints "-9223372036854775807"
}

void loop() {}
```

#### `u64_to_str`

**Signature**: `char *u64_to_str(uint64_t num, char *str, uint8_t str_len, uint8_t base = 10)`

**Description**: Converts a 64-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `base`: The numerical base (default: 10).

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[22];
  u64_to_str(18446744073709551615, buffer, sizeof(buffer), 16);
  Serial.print("Uint64 to string: ");
  Serial.println(buffer); // Prints "ffffffffffffffff"
}

void loop() {}
```

#### `float_to_str`

**Signature**: `char *float_to_str(float num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec)`

**Description**: Converts a float to a string with specified formatting.

**Parameters**:
- `num`: The float to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `min_width`: Minimum field width for formatting.
- `dec`: Number of decimal places.

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[32];
  float_to_str(3.14159, buffer, sizeof(buffer), 0, 2);
  Serial.print("Float to string: ");
  Serial.println(buffer); // Prints "3.14"
}

void loop() {}
```

#### `double_to_str`

**Signature**: `char *double_to_str(double num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec)`

**Description**: Converts a double to a string with specified formatting.

**Parameters**:
- `num`: The double to convert.
- `str`: The output buffer for the string.
- `str_len`: The size of the output buffer.
- `min_width`: Minimum field width for formatting.
- `dec`: Number of decimal places.

**Returns**: Pointer to the resulting string, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char buffer[32];
  double_to_str(3.14159, buffer, sizeof(buffer), 0, 3);
  Serial.print("Double to string: ");
  Serial.println(buffer); // Prints "3.142"
}

void loop() {}
```

#### `str_to_bool`

**Signature**: `bool str_to_bool(const char *str, const char **endptr = nullptr, const char *t = nullptr, const char *f = nullptr)`

**Description**: Converts a string to a boolean value.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `t`: Optional string representing true (default: "true").
- `f`: Optional string representing false (default: "false").

**Returns**: The converted boolean value, or `false` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "yes";
  bool value = str_to_bool(str, nullptr, "yes", "no");
  Serial.print("String to boolean: ");
  Serial.println(value); // Prints 1
}

void loop() {}
```

#### `str_to_i8`

**Signature**: `int8_t str_to_i8(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to an 8-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 8-bit signed integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "-128";
  int8_t value = str_to_i8(str);
  Serial.print("String to int8: ");
  Serial.println(value); // Prints -128
}

void loop() {}
```

#### `str_to_u8`

**Signature**: `uint8_t str_to_u8(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to an 8-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 8-bit unsigned integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "255";
  uint8_t value = str_to_u8(str);
  Serial.print("String to uint8: ");
  Serial.println(value); // Prints 255
}

void loop() {}
```

#### `str_to_i16`

**Signature**: `int16_t str_to_i16(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 16-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 16-bit signed integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "-32768";
  int16_t value = str_to_i16(str);
  Serial.print("String to int16: ");
  Serial.println(value); // Prints -32768
}

void loop() {}
```

#### `str_to_u16`

**Signature**: `uint16_t str_to_u16(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 16-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 16-bit unsigned integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "65535";
  uint16_t value = str_to_u16(str);
  Serial.print("String to uint16: ");
  Serial.println(value); // Prints 65535
}

void loop() {}
```

#### `str_to_i32`

**Signature**: `int32_t str_to_i32(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 32-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 32-bit signed integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "-2147483648";
  int32_t value = str_to_i32(str);
  Serial.print("String to int32: ");
  Serial.println(value); // Prints -2147483648
}

void loop() {}
```

#### `str_to_u32`

**Signature**: `uint32_t str_to_u32(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 32-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 32-bit unsigned integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "4294967295";
  uint32_t value = str_to_u32(str);
  Serial.print("String to uint32: ");
  Serial.println(value); // Prints 4294967295
}

void loop() {}
```

#### `str_to_i64`

**Signature**: `int64_t str_to_i64(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 64-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 64-bit signed integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "-9223372036854775807";
  int64_t value = str_to_i64(str);
  Serial.print("String to int64: ");
  Serial.println(value); // Prints -9223372036854775807
}

void loop() {}
```

#### `str_to_u64`

**Signature**: `uint64_t str_to_u64(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 64-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (default: 10).

**Returns**: The converted 64-bit unsigned integer, or 0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "18446744073709551615";
  uint64_t value = str_to_u64(str);
  Serial.print("String to uint64: ");
  Serial.println(value); // Prints 18446744073709551615
}

void loop() {}
```

#### `str_to_double`

**Signature**: `double str_to_double(const char *str, char d = '.', const char **endptr = nullptr)`

**Description**: Converts a string to a double-precision floating-point number.

**Parameters**:
- `str`: The input string to convert.
- `d`: The decimal point character (default: '.').
- `endptr`: Optional pointer to store the address of the first invalid character.

**Returns**: The converted double-precision floating-point number, or 0.0 on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *str = "3.14159";
  double value = str_to_double(str);
  Serial.print("String to double: ");
  Serial.println(value, 5); // Prints 3.14159
}

void loop() {}
```

### Array Operations

#### `join_chr_arr`

**Signature**: `char *join_chr_arr(const char *ar, size_t ar_size, char *buf, size_t buf_size, char delim)`

**Description**: Joins an array of characters into a single string with a delimiter.

**Parameters**:
- `ar`: The input array of characters.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character.

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char arr[] = {'a', 'b', 'c'};
  char buffer[10];
  join_chr_arr(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined characters: ");
  Serial.println(buffer); // Prints "a,b,c"
}

void loop() {}
```

#### `join_bool`

**Signature**: `char *join_bool(const bool *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',', const char *t = nullptr, const char *f = nullptr)`

**Description**: Joins an array of booleans into a string with a delimiter.

**Parameters**:
- `ar`: The input array of booleans.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').
- `t`: Optional string to represent true (default: "true").
- `f`: Optional string to represent false (default: "false").

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  bool arr[] = {true, false, true};
  char buffer[20];
  join_bool(arr, 3, buffer, sizeof(buffer), ',', "1", "0");
  Serial.print("Joined booleans: ");
  Serial.println(buffer); // Prints "1,0,1"
}

void loop() {}
```

#### `join_i8`

**Signature**: `char *join_i8(const int8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 8-bit signed integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  int8_t arr[] = {-128, 0, 127};
  char buffer[20];
  join_i8(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined int8: ");
  Serial.println(buffer); // Prints "-128,0,127"
}

void loop() {}
```

#### `join_u8`

**Signature**: `char *join_u8(const uint8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 8-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint8_t arr[] = {0, 128, 255};
  char buffer[20];
  join_u8(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined uint8: ");
  Serial.println(buffer); // Prints "0,128,255"
}

void loop() {}
```

#### `join_i16`

**Signature**: `char *join_i16(const int16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 16-bit signed integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  int16_t arr[] = {-32768, 0, 32767};
  char buffer[30];
  join_i16(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined int16: ");
  Serial.println(buffer); // Prints "-32768,0,32767"
}

void loop() {}
```

#### `join_u16`

**Signature**: `char *join_u16(const uint16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 16-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint16_t arr[] = {0, 32768, 65535};
  char buffer[30];
  join_u16(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined uint16: ");
  Serial.println(buffer); // Prints "0,32768,65535"
}

void loop() {}
```

#### `join_i32`

**Signature**: `char *join_i32(const int32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 32-bit signed integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  int32_t arr[] = {-2147483648, 0, 2147483647};
  char buffer[50];
  join_i32(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined int32: ");
  Serial.println(buffer); // Prints "-2147483648,0,2147483647"
}

void loop() {}
```

#### `join_u32`

**Signature**: `char *join_u32(const uint32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 32-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint32_t arr[] = {0, 2147483648, 4294967295};
  char buffer[50];
  join_u32(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined uint32: ");
  Serial.println(buffer); // Prints "0,2147483648,4294967295"
}

void loop() {}
```

#### `join_i64`

**Signature**: `char *join_i64(const int64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 64-bit signed integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  int64_t arr[] = {-9223372036854775807, 0, 9223372036854775807};
  char buffer[100];
  join_i64(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined int64: ");
  Serial.println(buffer); // Prints "-9223372036854775807,0,9223372036854775807"
}

void loop() {}
```

#### `join_u64`

**Signature**: `char *join_u64(const uint64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of 64-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `ar`: The input array of integers.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  uint64_t arr[] = {0, 9223372036854775808, 18446744073709551615};
  char buffer[100];
  join_u64(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined uint64: ");
  Serial.println(buffer); // Prints "0,9223372036854775808,18446744073709551615"
}

void loop() {}
```

#### `join_float`

**Signature**: `char *join_float(const float *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim = ',')`

**Description**: Joins an array of floats into a string with a delimiter.

**Parameters**:
- `ar`: The input array of floats.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `dec`: Number of decimal places for each float.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  float arr[] = {3.14159, 2.71828, 1.41421};
  char buffer[50];
  join_float(arr, 3, buffer, sizeof(buffer), 2, ',');
  Serial.print("Joined floats: ");
  Serial.println(buffer); // Prints "3.14,2.72,1.41"
}

void loop() {}
```

#### `join_double`

**Signature**: `char *join_double(const double *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim = ',')`

**Description**: Joins an array of doubles into a string with a delimiter.

**Parameters**:
- `ar`: The input array of doubles.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `dec`: Number of decimal places for each double.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  double arr[] = {3.14159, 2.71828, 1.41421};
  char buffer[50];
  join_double(arr, 3, buffer, sizeof(buffer), 3, ',');
  Serial.print("Joined doubles: ");
  Serial.println(buffer); // Prints "3.142,2.718,1.414"
}

void loop() {}
```

#### `join_str`

**Signature**: `char *join_str(const char **ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',')`

**Description**: Joins an array of strings into a string with a delimiter.

**Parameters**:
- `ar`: The input array of strings.
- `ar_size`: The size of the input array.
- `buf`: The output buffer for the joined string.
- `buf_size`: The size of the output buffer.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the joined string, or `NULL` if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  const char *arr[] = {"red", "green", "blue"};
  char buffer[50];
  join_str(arr, 3, buffer, sizeof(buffer), ',');
  Serial.print("Joined strings: ");
  Serial.println(buffer); // Prints "red,green,blue"
}

void loop() {}
```

#### `split_bool`

**Signature**: `bool *split_bool(const char *str, bool *ar, size_t ar_size, char delim = ',', const char *t = nullptr, const char *f = nullptr)`

**Description**: Splits a string into an array of booleans based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the booleans.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').
- `t`: Optional string to represent true (default: "true").
- `f`: Optional string to represent false (default: "false").

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "1,0,1";
  bool arr[3];
  split_bool(str, arr, 3, ',', "1", "0");
  Serial.println("Split booleans:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 1, 0, 1
  }
}

void loop() {}
```

#### `split_chr`

**Signature**: `char *split_chr(const char *str, char *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of characters based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the characters.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "a,b,c";
  char arr[4];
  split_chr(str, arr, sizeof(arr), ',');
  Serial.println("Split characters:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 'a', 'b', 'c'
  }
}

void loop() {}
```

#### `split_i8`

**Signature**: `int8_t *split_i8(const char *str, int8_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 8-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "-128,0,127";
  int8_t arr[3];
  split_i8(str, arr, 3, ',');
  Serial.println("Split int8:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -128, 0, 127
  }
}

void loop() {}
```

#### `split_u8`

**Signature**: `uint8_t *split_u8(const char *str, uint8_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 8-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "0,128,255";
  uint8_t arr[3];
  split_u8(str, arr, 3, ',');
  Serial.println("Split uint8:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 128, 255
  }
}

void loop() {}
```

#### `split_i16`

**Signature**: `int16_t *split_i16(const char *str, int16_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 16-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "-32768,0,32767";
  int16_t arr[3];
  split_i16(str, arr, 3, ',');
  Serial.println("Split int16:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -32768, 0, 32767
  }
}

void loop() {}
```

#### `split_u16`

**Signature**: `uint16_t *split_u16(const char *str, uint16_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 16-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "0,32768,65535";
  uint16_t arr[3];
  split_u16(str, arr, 3, ',');
  Serial.println("Split uint16:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 32768, 65535
  }
}

void loop() {}
```

#### `split_i32`

**Signature**: `int32_t *split_i32(const char *str, int32_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 32-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "-2147483648,0,2147483647";
  int32_t arr[3];
  split_i32(str, arr, 3, ',');
  Serial.println("Split int32:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -2147483648, 0, 2147483647
  }
}

void loop() {}
```

#### `split_u32`

**Signature**: `uint32_t *split_u32(const char *str, uint32_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 32-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "0,2147483648,4294967295";
  uint32_t arr[3];
  split_u32(str, arr, 3, ',');
  Serial.println("Split uint32:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 2147483648, 4294967295
  }
}

void loop() {}
```

#### `split_i64`

**Signature**: `int64_t *split_i64(const char *str, int64_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 64-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "-9223372036854775807,0,9223372036854775807";
  int64_t arr[3];
  split_i64(str, arr, 3, ',');
  Serial.println("Split int64:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -9223372036854775807, 0, 9223372036854775807
  }
}

void loop() {}
```

#### `split_u64`

**Signature**: `uint64_t *split_u64(const char *str, uint64_t *ar, size_t ar_size, char delim = ',')`

**Description**: Splits a string into an array of 64-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `ar_size`: The size of the output array.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "0,9223372036854775808,18446744073709551615";
  uint64_t arr[3];
  split_u64(str, arr, 3, ',');
  Serial.println("Split uint64:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 9223372036854775808, 18446744073709551615
  }
}

void loop() {}
```

#### `split_float`

**Signature**: `float *split_float(const char *str, float *ar, size_t ar_size, char d, char delim = ',')`

**Description**: Splits a string into an array of floats based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the floats.
- `ar_size`: The size of the output array.
- `d`: The decimal point character.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "3.14,2.72,1.41";
  float arr[3];
  split_float(str, arr, 3, '.', ',');
  Serial.println("Split floats:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i], 2); // Prints 3.14, 2.72, 1.41
  }
}

void loop() {}
```

#### `split_double`

**Signature**: `double *split_double(const char *str, double *ar, size_t ar_size, char d, char delim = ',')`

**Description**: Splits a string into an array of doubles based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the doubles.
- `ar_size`: The size of the output array.
- `d`: The decimal point character.
- `delim`: The delimiter character (default: ',').

**Returns**: Pointer to the output array, or `NULL` on error.

**Arduino Example**:
```cpp
#include <utils.h>

void setup() {
  Serial.begin(115200);
  char str[] = "3.14159,2.71828,1.41421";
  double arr[3];
  split_double(str, arr, 3, '.', ',');
  Serial.println("Split doubles:");
  for (size_t i = 0; i < 3; i++) {
    Serial.println(arr[i], 5); // Prints 3.14159, 2.71828, 1.41421
  }
}

void loop() {}
```