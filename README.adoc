# Arduino Utility Library

## Overview

The Arduino Utility Library provides a collection of helper functions and unions in the `ut` namespace for Arduino-based projects. It includes utilities for bit manipulation, BCD/decimal conversion, timing operations, string manipulation, and array joining/splitting. The library is designed to be lightweight and efficient, suitable for resource-constrained microcontroller environments.

## Features

- **Bit Manipulation**: Extract specific bits from integer types.
- **BCD Conversion**: Convert between Binary-Coded Decimal (BCD) and decimal formats.
- **Timing Functions**: Non-blocking delays and elapsed time checks in microseconds, milliseconds, seconds, and minutes.
- **String Conversion**: Convert integers and floating-point numbers to strings and vice versa, supporting multiple numerical bases.
- **Array Operations**: Join and split arrays of various types (e.g., integers, floats, strings) with delimiters.
- **Data Type Unions**: Flexible unions for 16-bit, 32-bit, and 64-bit data type conversions.

## Installation

1. **Clone or Download**:
   ```bash
   git clone https://github.com/dynapptor/arduino-utility-lib.git
   ```
   Alternatively, download the ZIP file and extract it.

2. **Add to Arduino IDE**:
   - Copy the library folder to your Arduino `libraries` directory (e.g., `~/Documents/Arduino/libraries/`).
   - Restart the Arduino IDE.

3. **Include in Your Sketch**:
   ```cpp
   #include <utils.h>
   using namespace ut;
   ```

## Usage Example

Below is an Arduino sketch demonstrating several features of the library, including bit manipulation, string conversion, timing, and array operations.

```cpp
#include <utils.h>
using namespace ut;

void setup() {
  Serial.begin(9600);

  // Bit manipulation
  uint16_t value = 0b1010101010101010;
  uint16_t bits = getBits(value, 4, 3);
  Serial.print("Extracted bits: ");
  Serial.println(bits, BIN); // Prints 101

  // BCD conversion
  uint8_t bcd = DEC2BCD(25);
  uint8_t dec = BCD2DEC(bcd);
  Serial.print("BCD 25 to decimal: ");
  Serial.println(dec); // Prints 25

  // Timing
  static uint32_t startTime = millis();
  if (onTimeSec(startTime, 5)) {
    Serial.println("5 seconds elapsed!");
  }

  // String conversion
  char buffer[20];
  i16toa(-1234, buffer, 10);
  Serial.print("Int16 to string: ");
  Serial.println(buffer); // Prints -1234

  // Array joining
  int16_t arr[] = {10, 20, 30};
  char joinBuffer[20];
  joinInt16(arr, 3, joinBuffer, 20, ',');
  Serial.print("Joined array: ");
  Serial.println(joinBuffer); // Prints 10,20,30

  // Array splitting
  char str[] = "100,200,300";
  int16_t splitArr[3];
  spliti16(str, splitArr, ',', 3);
  Serial.print("Split array: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(splitArr[i]);
    if (i < 2) Serial.print(",");
  }
  Serial.println(); // Prints 100,200,300
}

void loop() {
  // Add periodic tasks here if needed
}
```

## 📁 Directory Structure

```
ArduinoUtilityLib/
├── examples/
│   ├── BitManipulation/
│   │   └── BitManipulation.ino
│   ├── BCDConversion/
│   │   └── BCDConversion.ino
│   ├── TimingFunctions/
│   │   └── TimingFunctions.ino
│   ├── StringConversion/
│   │   └── StringConversion.ino
│   ├── ArrayOperations/
│   │   └── ArrayOperations.ino
├── utils.h
├── utils.cpp
├── utils.tpp
├── keywords.txt
├── library.properties
├── README.md
├── API.md
```

## Documentation

For detailed API documentation with Arduino examples for each function and union, see [API.md](API.md). The library is documented using Doxygen, and you can generate HTML documentation by running:

```bash
doxygen Doxyfile
```

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m "Add your feature"`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a Pull Request.

Please ensure your code follows the existing style and includes appropriate tests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For issues or suggestions, please open an issue on the [GitHub repository](https://github.com/dynapptor/Utility-lib).
