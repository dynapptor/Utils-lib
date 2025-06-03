# Arduino Utility Library API Documentation

## Table of Contents

- [Namespace `ut`](#namespace-ut)
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

## Namespace `ut`

The `ut` namespace contains utility functions and unions for data manipulation, conversion, and timing in Arduino projects. It is designed for efficiency in resource-constrained environments.

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
using namespace ut;

void setup() {
  Serial.begin(9600);
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
using namespace ut;

void setup() {
  Serial.begin(9600);
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
using namespace ut;

void setup() {
  Serial.begin(9600);
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
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint16_t value = 0b1010101010101010;
  uint16_t bits = getBits(value, 4, 3);
  Serial.print("Extracted bits: ");
  Serial.println(bits, BIN); // Prints 101
}

void loop() {}
```

### BCD Conversion

#### `BCD2DEC`

**Signature**: `uint8_t BCD2DEC(uint8_t bcd)`

**Description**: Converts a BCD (Binary-Coded Decimal) value to a decimal value.

**Parameters**:
- `bcd`: The BCD value to convert.

**Returns**: The equivalent decimal value.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint8_t bcd = 0x25; // BCD for 25
  uint8_t dec = BCD2DEC(bcd);
  Serial.print("BCD to decimal: ");
  Serial.println(dec); // Prints 25
}

void loop() {}
```

#### `DEC2BCD`

**Signature**: `uint8_t DEC2BCD(uint8_t dec)`

**Description**: Converts a decimal value to a BCD (Binary-Coded Decimal) value.

**Parameters**:
- `dec`: The decimal value to convert.

**Returns**: The equivalent BCD value.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint8_t dec = 25;
  uint8_t bcd = DEC2BCD(dec);
  Serial.print("Decimal to BCD: ");
  Serial.println(bcd, HEX); // Prints 25
}

void loop() {}
```

### Timing Functions

#### `onTimeMin`

**Signature**: `uint8_t onTimeMin(uint32_t &t, uint32_t delayTime, bool reset = true)`

**Description**: Checks if a specified time (in minutes) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Reference to the start time (in milliseconds).
- `delayTime`: The delay time in minutes.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: 1 if the delay has elapsed, 0 otherwise.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static uint32_t start = millis();
  if (onTimeMin(start, 1)) {
    Serial.println("1 minute elapsed!");
  }
}
```

#### `onTimeSec`

**Signature**: `uint8_t onTimeSec(uint32_t &t, uint32_t delayTime, bool reset = true)`

**Description**: Checks if a specified time (in seconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Reference to the start time (in milliseconds).
- `delayTime`: The delay time in seconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: 1 if the delay has elapsed, 0 otherwise.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static uint32_t start = millis();
  if (onTimeSec(start, 5)) {
    Serial.println("5 seconds elapsed!");
  }
}
```

#### `onTimeMs`

**Signature**: `uint8_t onTimeMs(uint32_t &t, uint32_t delayTime, bool reset = true)`

**Description**: Checks if a specified time (in milliseconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Reference to the start time (in milliseconds).
- `delayTime`: The delay time in milliseconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: 1 if the delay has elapsed, 0 otherwise.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static uint32_t start = millis();
  if (onTimeMs(start, 1000)) {
    Serial.println("1000 ms elapsed!");
  }
}
```

#### `onTimeUs`

**Signature**: `uint8_t onTimeUs(uint32_t &t, uint32_t delayTime, bool reset = true)`

**Description**: Checks if a specified time (in microseconds) has elapsed and optionally resets the timer.

**Parameters**:
- `t`: Reference to the start time (in microseconds).
- `delayTime`: The delay time in microseconds.
- `reset`: If true, resets the start time when the delay has elapsed.

**Returns**: 1 if the delay has elapsed, 0 otherwise.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
}

void loop() {
  static uint32_t start = micros();
  if (onTimeUs(start, 1000)) {
    Serial.println("1000 us elapsed!");
  }
}
```

#### `delayUs`

**Signature**: `void delayUs(uint32_t start, uint32_t wait)`

**Description**: Delays execution for a specified time (in microseconds).

**Parameters**:
- `start`: The start time (in microseconds).
- `wait`: The delay time in microseconds.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint32_t start = micros();
  delayUs(start, 1000);
  Serial.println("Delayed 1000 us");
}

void loop() {}
```

#### `delayMs`

**Signature**: `void delayMs(uint32_t start, uint32_t wait)`

**Description**: Delays execution for a specified time (in milliseconds).

**Parameters**:
- `start`: The start time (in milliseconds).
- `wait`: The delay time in milliseconds.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint32_t start = millis();
  delayMs(start, 1000);
  Serial.println("Delayed 1000 ms");
}

void loop() {}
```

### String Manipulation

#### `strreverse`

**Signature**: `char *strreverse(char *str)`

**Description**: Reverses the characters in a null-terminated string.

**Parameters**:
- `str`: The input string to reverse.

**Returns**: Pointer to the reversed string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "hello";
  strreverse(str);
  Serial.print("Reversed string: ");
  Serial.println(str); // Prints "olleh"
}

void loop() {}
```

#### `chrCount`

**Signature**: `size_t chrCount(const char *str, char c)`

**Description**: Counts occurrences of a character in a string.

**Parameters**:
- `str`: The input string.
- `c`: The character to count.

**Returns**: The number of occurrences of the character (including null terminator).

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "hello";
  size_t count = chrCount(str, 'l');
  Serial.print("Occurrences of 'l': ");
  Serial.println(count); // Prints 3
}

void loop() {}
```

#### `strCount`

**Signature**: `size_t strCount(const char *str, const char *find)`

**Description**: Counts occurrences of a substring in a string.

**Parameters**:
- `str`: The input string.
- `find`: The substring to count.

**Returns**: The number of occurrences of the substring.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "hello hello";
  size_t count = strCount(str, "hello");
  Serial.print("Occurrences of 'hello': ");
  Serial.println(count); // Prints 2
}

void loop() {}
```

#### `strCut`

**Signature**: `void strCut(char *str, char **ar, char delim)`

**Description**: Splits a string into an array of substrings based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array of substring pointers.
- `delim`: The delimiter character.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "a,b,c";
  char *ar[3];
  strCut(str, ar, ',');
  Serial.println("Split strings:");
  for (int i = 0; i < 3; i++) {
    Serial.println(ar[i]); // Prints "a", "b", "c"
  }
}

void loop() {}
```

### String Conversion

#### `i8toa`

**Signature**: `char *i8toa(int8_t num, char *str, uint8_t base = 10)`

**Description**: Converts an 8-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[10];
  i8toa(-128, buffer, 10);
  Serial.print("Int8 to string: ");
  Serial.println(buffer); // Prints "-128"
}

void loop() {}
```

#### `u8toa`

**Signature**: `char *u8toa(uint8_t num, char *str, uint8_t base = 10)`

**Description**: Converts an 8-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[10];
  u8toa(255, buffer, 16);
  Serial.print("Uint8 to string: ");
  Serial.println(buffer); // Prints "ff"
}

void loop() {}
```

#### `i16toa`

**Signature**: `char *i16toa(int16_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 16-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[10];
  i16toa(-32768, buffer, 10);
  Serial.print("Int16 to string: ");
  Serial.println(buffer); // Prints "-32768"
}

void loop() {}
```

#### `u16toa`

**Signature**: `char *u16toa(uint16_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 16-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[10];
  u16toa(65535, buffer, 16);
  Serial.print("Uint16 to string: ");
  Serial.println(buffer); // Prints "ffff"
}

void loop() {}
```

#### `i32toa`

**Signature**: `char *i32toa(int32_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 32-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[12];
  i32toa(-2147483648, buffer, 10);
  Serial.print("Int32 to string: ");
  Serial.println(buffer); // Prints "-2147483648"
}

void loop() {}
```

#### `u32toa`

**Signature**: `char *u32toa(uint32_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 32-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[12];
  u32toa(4294967295, buffer, 16);
  Serial.print("Uint32 to string: ");
  Serial.println(buffer); // Prints "ffffffff"
}

void loop() {}
```

#### `i64toa`

**Signature**: `char *i64toa(int64_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 64-bit signed integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[22];
  i64toa(-9223372036854775807, buffer, 10);
  Serial.print("Int64 to string: ");
  Serial.println(buffer); // Prints "-9223372036854775807"
}

void loop() {}
```

#### `u64toa`

**Signature**: `char *u64toa(uint64_t num, char *str, uint8_t base = 10)`

**Description**: Converts a 64-bit unsigned integer to a string.

**Parameters**:
- `num`: The number to convert.
- `str`: The output buffer for the string.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[22];
  u64toa(18446744073709551615, buffer, 16);
  Serial.print("Uint64 to string: ");
  Serial.println(buffer); // Prints "ffffffffffffffff"
}

void loop() {}
```

#### `ftoa`

**Signature**: `char *ftoa(float num, char *str, int8_t minWidth, uint8_t len, uint8_t dec)`

**Description**: Converts a float to a string with specified formatting.

**Parameters**:
- `num`: The float to convert.
- `str`: The output buffer for the string.
- `minWidth`: Minimum field width for formatting.
- `len`: Maximum length of the output string.
- `dec`: Number of decimal places.

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[32];
  ftoa(3.14159, buffer, 1, 32, 2);
  Serial.print("Float to string: ");
  Serial.println(buffer); // Prints "3.14"
}

void loop() {}
```

#### `dtoa`

**Signature**: `char *dtoa(double num, char *str, int8_t minWidth, size_t len, uint8_t dec)`

**Description**: Converts a double to a string with specified formatting.

**Parameters**:
- `num`: The double to convert.
- `str`: The output buffer for the string.
- `minWidth`: Minimum field width for formatting.
- `len`: Maximum length of the output string.
- `dec`: Number of decimal places.

**Returns**: Pointer to the resulting string.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char buffer[32];
  dtoa(3.14159, buffer, 1, 32, 3);
  Serial.print("Double to string: ");
  Serial.println(buffer); // Prints "3.142"
}

void loop() {}
```

#### `atoi8`

**Signature**: `int8_t atoi8(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to an 8-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 8-bit signed integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "-128";
  int8_t value = atoi8(str);
  Serial.print("String to int8: ");
  Serial.println(value); // Prints -128
}

void loop() {}
```

#### `atou8`

**Signature**: `uint8_t atou8(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to an 8-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 8-bit unsigned integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "255";
  uint8_t value = atou8(str);
  Serial.print("String to uint8: ");
  Serial.println(value); // Prints 255
}

void loop() {}
```

#### `atoi16`

**Signature**: `int16_t atoi16(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 16-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 16-bit signed integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "-32768";
  int16_t value = atoi16(str);
  Serial.print("String to int16: ");
  Serial.println(value); // Prints -32768
}

void loop() {}
```

#### `atou16`

**Signature**: `uint16_t atou16(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 16-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 16-bit unsigned integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "65535";
  uint16_t value = atou16(str);
  Serial.print("String to uint16: ");
  Serial.println(value); // Prints 65535
}

void loop() {}
```

#### `atoi32`

**Signature**: `int32_t atoi32(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 32-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 32-bit signed integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "-2147483648";
  int32_t value = atoi32(str);
  Serial.print("String to int32: ");
  Serial.println(value); // Prints -2147483648
}

void loop() {}
```

#### `atou32`

**Signature**: `uint32_t atou32(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 32-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 32-bit unsigned integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "4294967295";
  uint32_t value = atou32(str);
  Serial.print("String to uint32: ");
  Serial.println(value); // Prints 4294967295
}

void loop() {}
```

#### `atoi64`

**Signature**: `int64_t atoi64(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 64-bit signed integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 64-bit signed integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "-9223372036854775807";
  int64_t value = atoi64(str);
  Serial.print("String to int64: ");
  Serial.println(value); // Prints -9223372036854775807
}

void loop() {}
```

#### `atou64`

**Signature**: `uint64_t atou64(const char *str, const char **endptr = nullptr, uint8_t base = 10)`

**Description**: Converts a string to a 64-bit unsigned integer.

**Parameters**:
- `str`: The input string to convert.
- `endptr`: Optional pointer to store the address of the first invalid character.
- `base`: The numerical base (e.g., 10 for decimal, 16 for hexadecimal).

**Returns**: The converted 64-bit unsigned integer.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "18446744073709551615";
  uint64_t value = atou64(str);
  Serial.print("String to uint64: ");
  Serial.println(value); // Prints 18446744073709551615
}

void loop() {}
```

#### `atod`

**Signature**: `double atod(const char *str, const char d = '.', const char **endptr = nullptr)`

**Description**: Converts a string to a double-precision floating-point number.

**Parameters**:
- `str`: The input string to convert.
- `d`: The decimal point character (default: '.').
- `endptr`: Optional pointer to store the address of the first invalid character.

**Returns**: The converted double-precision floating-point number.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *str = "3.14159";
  double value = atod(str);
  Serial.print("String to double: ");
  Serial.println(value, 5); // Prints 3.14159
}

void loop() {}
```

### Array Operations

#### `joinChrArr`

**Signature**: `char *joinChrArr(const char **arr, size_t arrCount, char delimiter, char *buf, size_t bufSize)`

**Description**: Joins an array of strings into a single string with a delimiter.

**Parameters**:
- `arr`: The input array of strings.
- `arrCount`: The number of strings in the array.
- `delimiter`: The delimiter to use between strings.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *arr[] = {"apple", "banana", "cherry"};
  char buffer[50];
  joinChrArr(arr, 3, ',', buffer, 50);
  Serial.print("Joined strings: ");
  Serial.println(buffer); // Prints "apple,banana,cherry"
}

void loop() {}
```

#### `joinBool`

**Signature**: `char *joinBool(const bool *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of booleans into a string with a delimiter.

**Parameters**:
- `arr`: The input array of booleans.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  bool arr[] = {true, false, true};
  char buffer[10];
  joinBool(arr, 3, buffer, 10, ',');
  Serial.print("Joined booleans: ");
  Serial.println(buffer); // Prints "1,0,1"
}

void loop() {}
```

#### `joinInt8`

**Signature**: `char *joinInt8(const int8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 8-bit signed integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  int8_t arr[] = {-128, 0, 127};
  char buffer[20];
  joinInt8(arr, 3, buffer, 20, ',');
  Serial.print("Joined int8: ");
  Serial.println(buffer); // Prints "-128,0,127"
}

void loop() {}
```

#### `joinUint8`

**Signature**: `char *joinUint8(const uint8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 8-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint8_t arr[] = {0, 128, 255};
  char buffer[20];
  joinUint8(arr, 3, buffer, 20, ',');
  Serial.print("Joined uint8: ");
  Serial.println(buffer); // Prints "0,128,255"
}

void loop() {}
```

#### `joinInt16`

**Signature**: `char *joinInt16(const int16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 16-bit signed integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  int16_t arr[] = {-32768, 0, 32767};
  char buffer[30];
  joinInt16(arr, 3, buffer, 30, ',');
  Serial.print("Joined int16: ");
  Serial.println(buffer); // Prints "-32768,0,32767"
}

void loop() {}
```

#### `joinUint16`

**Signature**: `char *joinUint16(const uint16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 16-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint16_t arr[] = {0, 32768, 65535};
  char buffer[30];
  joinUint16(arr, 3, buffer, 30, ',');
  Serial.print("Joined uint16: ");
  Serial.println(buffer); // Prints "0,32768,65535"
}

void loop() {}
```

#### `joinInt32`

**Signature**: `char *joinInt32(const int32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 32-bit signed integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  int32_t arr[] = {-2147483648, 0, 2147483647};
  char buffer[50];
  joinInt32(arr, 3, buffer, 50, ',');
  Serial.print("Joined int32: ");
  Serial.println(buffer); // Prints "-2147483648,0,2147483647"
}

void loop() {}
```

#### `joinUint32`

**Signature**: `char *joinUint32(const uint32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 32-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint32_t arr[] = {0, 2147483648, 4294967295};
  char buffer[50];
  joinUint32(arr, 3, buffer, 50, ',');
  Serial.print("Joined uint32: ");
  Serial.println(buffer); // Prints "0,2147483648,4294967295"
}

void loop() {}
```

#### `joinInt64`

**Signature**: `char *joinInt64(const int64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 64-bit signed integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  int64_t arr[] = {-9223372036854775807, 0, 9223372036854775807};
  char buffer[100];
  joinInt64(arr, 3, buffer, 100, ',');
  Serial.print("Joined int64: ");
  Serial.println(buffer); // Prints "-9223372036854775807,0,9223372036854775807"
}

void loop() {}
```

#### `joinUint64`

**Signature**: `char *joinUint64(const uint64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of 64-bit unsigned integers into a string with a delimiter.

**Parameters**:
- `arr`: The input array of integers.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  uint64_t arr[] = {0, 9223372036854775808, 18446744073709551615};
  char buffer[100];
  joinUint64(arr, 3, buffer, 100, ',');
  Serial.print("Joined uint64: ");
  Serial.println(buffer); // Prints "0,9223372036854775808,18446744073709551615"
}

void loop() {}
```

#### `joinFloat`

**Signature**: `char *joinFloat(const float *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter)`

**Description**: Joins an array of floats into a string with a delimiter.

**Parameters**:
- `arr`: The input array of floats.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `dec`: Number of decimal places for each float.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  float arr[] = {3.14159, 2.71828, 1.41421};
  char buffer[50];
  joinFloat(arr, 3, buffer, 50, 2, ',');
  Serial.print("Joined floats: ");
  Serial.println(buffer); // Prints "3.14,2.72,1.41"
}

void loop() {}
```

#### `joinDouble`

**Signature**: `char *joinDouble(const double *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter)`

**Description**: Joins an array of doubles into a string with a delimiter.

**Parameters**:
- `arr`: The input array of doubles.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `dec`: Number of decimal places for each double.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  double arr[] = {3.14159, 2.71828, 1.41421};
  char buffer[50];
  joinDouble(arr, 3, buffer, 50, 3, ',');
  Serial.print("Joined doubles: ");
  Serial.println(buffer); // Prints "3.142,2.718,1.414"
}

void loop() {}
```

#### `joinStr`

**Signature**: `char *joinStr(const char **arr, size_t len, char *buf, size_t bufSize, char delimiter)`

**Description**: Joins an array of strings into a string with a delimiter.

**Parameters**:
- `arr`: The input array of strings.
- `len`: The length of the array.
- `buf`: The output buffer for the joined string.
- `bufSize`: The size of the output buffer.
- `delimiter`: The delimiter to use between values.

**Returns**: Pointer to the joined string, or nullptr if the buffer is too small.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  const char *arr[] = {"red", "green", "blue"};
  char buffer[50];
  joinStr(arr, 3, buffer, 50, ',');
  Serial.print("Joined strings: ");
  Serial.println(buffer); // Prints "red,green,blue"
}

void loop() {}
```

#### `splitb`

**Signature**: `bool *splitb(char *str, bool *ar, char const delim, size_t count)`

**Description**: Splits a string into an array of booleans based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the booleans.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "1,0,1";
  bool arr[3];
  splitb(str, arr, ',', 3);
  Serial.println("Split booleans:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 1, 0, 1
  }
}

void loop() {}
```

#### `splitc`

**Signature**: `char *splitc(char *str, char *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of characters based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the characters.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "a,b,c";
  char arr[3];
  splitc(str, arr, ',', 3);
  Serial.println("Split characters:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 'a', 'b', 'c'
  }
}

void loop() {}
```

#### `spliti8`

**Signature**: `int8_t *spliti8(char *str, int8_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 8-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "-128,0,127";
  int8_t arr[3];
  spliti8(str, arr, ',', 3);
  Serial.println("Split int8:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -128, 0, 127
  }
}

void loop() {}
```

#### `splitu8`

**Signature**: `uint8_t *splitu8(char *str, uint8_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 8-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "0,128,255";
  uint8_t arr[3];
  splitu8(str, arr, ',', 3);
  Serial.println("Split uint8:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 128, 255
  }
}

void loop() {}
```

#### `spliti16`

**Signature**: `int16_t *spliti16(char *str, int16_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 16-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "-32768,0,32767";
  int16_t arr[3];
  spliti16(str, arr, ',', 3);
  Serial.println("Split int16:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -32768, 0, 32767
  }
}

void loop() {}
```

#### `splitu16`

**Signature**: `uint16_t *splitu16(char *str, uint16_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 16-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "0,32768,65535";
  uint16_t arr[3];
  splitu16(str, arr, ',', 3);
  Serial.println("Split uint16:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 32768, 65535
  }
}

void loop() {}
```

#### `spliti32`

**Signature**: `int32_t *spliti32(char *str, int32_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 32-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "-2147483648,0,2147483647";
  int32_t arr[3];
  spliti32(str, arr, ',', 3);
  Serial.println("Split int32:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -2147483648, 0, 2147483647
  }
}

void loop() {}
```

#### `splitu32`

**Signature**: `uint32_t *splitu32(char *str, uint32_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 32-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "0,2147483648,4294967295";
  uint32_t arr[3];
  splitu32(str, arr, ',', 3);
  Serial.println("Split uint32:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 2147483648, 4294967295
  }
}

void loop() {}
```

#### `spliti64`

**Signature**: `int64_t *spliti64(char *str, int64_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 64-bit signed integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "-9223372036854775807,0,9223372036854775807";
  int64_t arr[3];
  spliti64(str, arr, ',', 3);
  Serial.println("Split int64:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints -9223372036854775807, 0, 9223372036854775807
  }
}

void loop() {}
```

#### `splitu64`

**Signature**: `uint64_t *splitu64(char *str, uint64_t *ar, const char delim, size_t count)`

**Description**: Splits a string into an array of 64-bit unsigned integers based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the integers.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "0,9223372036854775808,18446744073709551615";
  uint64_t arr[3];
  splitu64(str, arr, ',', 3);
  Serial.println("Split uint64:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i]); // Prints 0, 9223372036854775808, 18446744073709551615
  }
}

void loop() {}
```

#### `splitf`

**Signature**: `float *splitf(char *str, float *ar, const char d, const char delim, size_t count)`

**Description**: Splits a string into an array of floats based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the floats.
- `d`: The decimal point character.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "3.14,2.72,1.41";
  float arr[3];
  splitf(str, arr, '.', ',', 3);
  Serial.println("Split floats:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i], 2); // Prints 3.14, 2.72, 1.41
  }
}

void loop() {}
```

#### `splitd`

**Signature**: `double *splitd(char *str, double *ar, const char d, const char delim, size_t count)`

**Description**: Splits a string into an array of doubles based on a delimiter.

**Parameters**:
- `str`: The input string to split.
- `ar`: The output array for the doubles.
- `d`: The decimal point character.
- `delim`: The delimiter character.
- `count`: The number of elements to parse.

**Returns**: Pointer to the output array.

**Arduino Example**:
```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);
  char str[] = "3.14159,2.71828,1.41421";
  double arr[3];
  splitd(str, arr, '.', ',', 3);
  Serial.println("Split doubles:");
  for (int i = 0; i < 3; i++) {
    Serial.println(arr[i], 5); // Prints 3.14159, 2.71828, 1.41421
  }
}

void loop() {}
```