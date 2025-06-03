#pragma once

#include <Arduino.h>

/**
 * @brief Utility namespace containing helper functions and unions for data manipulation, conversion, and timing.
 *
 * This namespace provides a collection of utility functions for tasks such as bit manipulation,
 * BCD/decimal conversion, timing operations, string manipulation, and array joining/splitting.
 * It also includes unions for flexible data type conversions.
 */
namespace ut {

/**
 * @brief Maximum character lengths for string representations of various integer types.
 */
#define I8_CHR_MAX 5    ///< Maximum characters for int8_t (e.g., "-128").
#define U8_CHR_MAX 4    ///< Maximum characters for uint8_t (e.g., "255").
#define I16_CHR_MAX 7   ///< Maximum characters for int16_t (e.g., "-32768").
#define U16_CHR_MAX 6   ///< Maximum characters for uint16_t (e.g., "65535").
#define I32_CHR_MAX 12  ///< Maximum characters for int32_t (e.g., "-2147483648").
#define U32_CHR_MAX 11  ///< Maximum characters for uint32_t (e.g., "4294967295").
#define I64_CHR_MAX 22  ///< Maximum characters for int64_t (e.g., "-9223372036854775808").
#define U64_CHR_MAX 21  ///< Maximum characters for uint64_t (e.g., "18446744073709551615").

/**
 * @brief Extracts a specified range of bits from a value.
 *
 * @tparam T The type of the input value (e.g., uint8_t, uint16_t, etc.).
 * @param v The input value from which bits are extracted.
 * @param start The starting bit position (0-based).
 * @param count The number of bits to extract.
 * @return The extracted bits as a value of type T.
 */
template <typename T>
static T getBits(T v, uint8_t start, uint8_t count);

/**
 * @brief Union for 16-bit data type conversions.
 *
 * Allows flexible access to a 16-bit value as different data types.
 */
union union16 {
  uint16_t u16;   ///< Unsigned 16-bit integer.
  int16_t i16;    ///< Signed 16-bit integer.
  uint8_t u8[2];  ///< Array of two unsigned 8-bit integers.
  int8_t i8[2];   ///< Array of two signed 8-bit integers.
};

/**
 * @brief Union for 32-bit data type conversions.
 *
 * Allows flexible access to a 32-bit value as different data types, including floating-point.
 */
union union32 {
  uint32_t u32;     ///< Unsigned 32-bit integer.
  int32_t i32;      ///< Signed 32-bit integer.
  uint16_t u16[2];  ///< Array of two unsigned 16-bit integers.
  int16_t i16[2];   ///< Array of two signed 16-bit integers.
  uint8_t u8[4];    ///< Array of four unsigned 8-bit integers.
  int8_t i8[4];     ///< Array of four signed 8-bit integers.
  float f;          ///< 32-bit floating-point value.
};

/**
 * @brief Union for 64-bit data type conversions.
 *
 * Allows flexible access to a 64-bit value as different data types, including double-precision floating-point.
 */
union union64 {
  uint64_t u64;     ///< Unsigned 64-bit integer.
  int64_t i64;      ///< Signed 64-bit integer.
  uint32_t u32[2];  ///< Array of two unsigned 32-bit integers.
  int32_t i32[2];   ///< Array of two signed 32-bit integers.
  uint16_t u16[4];  ///< Array of four unsigned 16-bit integers.
  int16_t i16[4];   ///< Array of four signed 16-bit integers.
  uint8_t u8[8];    ///< Array of eight unsigned 8-bit integers.
  int8_t i8[8];     ///< Array of eight signed 8-bit integers.
  double d;         ///< 64-bit double-precision floating-point value.
};

/**
 * @brief Converts a BCD (Binary-Coded Decimal) value to a decimal value.
 *
 * @param bcd The BCD value to convert.
 * @return The equivalent decimal value.
 */
extern uint8_t BCD2DEC(uint8_t bcd);

/**
 * @brief Converts a decimal value to a BCD (Binary-Coded Decimal) value.
 *
 * @param dec The decimal value to convert.
 * @return The equivalent BCD value.
 */
extern uint8_t DEC2BCD(uint8_t dec);

/**
 * @brief Checks if a specified time (in minutes) has elapsed and optionally resets the timer.
 *
 * @param t Reference to the start time (in milliseconds).
 * @param delayTime The delay time in minutes.
 * @param reset If true, resets the start time when the delay has elapsed.
 * @return 1 if the delay has elapsed, 0 otherwise.
 */
extern uint8_t onTimeMin(uint32_t &t, uint32_t delayTime, bool reset = true);

/**
 * @brief Checks if a specified time (in seconds) has elapsed and optionally resets the timer.
 *
 * @param t Reference to the start time (in milliseconds).
 * @param delayTime The delay time in seconds.
 * @param reset If true, resets the start time when the delay has elapsed.
 * @return 1 if the delay has elapsed, 0 otherwise.
 */
extern uint8_t onTimeSec(uint32_t &t, uint32_t delayTime, bool reset = true);

/**
 * @brief Checks if a specified time (in milliseconds) has elapsed and optionally resets the timer.
 *
 * @param t Reference to the start time (in milliseconds).
 * @param delayTime The delay time in milliseconds.
 * @param reset If true, resets the start time when the delay has elapsed.
 * @return 1 if the delay has elapsed, 0 otherwise.
 */
extern uint8_t onTimeMs(uint32_t &t, uint32_t delayTime, bool reset = true);

/**
 * @brief Checks if a specified time (in microseconds) has elapsed and optionally resets the timer.
 *
 * @param t Reference to the start time (in microseconds).
 * @param delayTime The delay time in microseconds.
 * @param reset If true, resets the start time when the delay has elapsed.
 * @return 1 if the delay has elapsed, 0 otherwise.
 */
extern uint8_t onTimeUs(uint32_t &t, uint32_t delayTime, bool reset = true);

/**
 * @brief Delays execution for a specified time (in microseconds).
 *
 * @param start The start time (in microseconds).
 * @param wait The delay time in microseconds.
 */
extern void delayUs(uint32_t start, uint32_t wait);

/**
 * @brief Delays execution for a specified time (in milliseconds).
 *
 * @param start The start time (in milliseconds).
 * @param wait The delay time in milliseconds.
 */
extern void delayMs(uint32_t start, uint32_t wait);

/**
 * @brief Reverses the characters in a null-terminated string.
 *
 * @param str The input string to reverse.
 * @return Pointer to the reversed string.
 */
extern char *strreverse(char *str);

/**
 * @brief Converts an 8-bit signed integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *i8toa(int8_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts an 8-bit unsigned integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *u8toa(uint8_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 16-bit signed integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *i16toa(int16_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 16-bit unsigned integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *u16toa(uint16_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 32-bit signed integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *i32toa(int32_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 32-bit unsigned integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *u32toa(uint32_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 64-bit signed integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *i64toa(int64_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a 64-bit unsigned integer to a string.
 *
 * @param num The number to convert.
 * @param str The output buffer for the string.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return Pointer to the resulting string.
 */
extern char *u64toa(uint64_t num, char *str, uint8_t base = 10);

/**
 * @brief Converts a float to a string with specified formatting.
 *
 * @param num The float to convert.
 * @param str The output buffer for the string.
 * @param minWidth Minimum field width for formatting.
 * @param len Maximum length of the output string.
 * @param dec Number of decimal places.
 * @return Pointer to the resulting string.
 */
extern char *ftoa(float num, char *str, int8_t minWidth, uint8_t len, uint8_t dec);

/**
 * @brief Converts a double to a string with specified formatting.
 *
 * @param num The double to convert.
 * @param str The output buffer for the string.
 * @param minWidth Minimum field width for formatting.
 * @param len Maximum length of the output string.
 * @param dec Number of decimal places.
 * @return Pointer to the resulting string.
 */
extern char *dtoa(double num, char *str, int8_t minWidth, size_t len, uint8_t dec);

/**
 * @brief Converts a string to an 8-bit signed integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 8-bit signed integer.
 */
extern int8_t atoi8(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to an 8-bit unsigned integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 8-bit unsigned integer.
 */
extern uint8_t atou8(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 16-bit signed integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 16-bit signed integer.
 */
extern int16_t atoi16(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 16-bit unsigned integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 16-bit unsigned integer.
 */
extern uint16_t atou16(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 32-bit signed integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 32-bit signed integer.
 */
extern int32_t atoi32(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 32-bit unsigned integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 32-bit unsigned integer.
 */
extern uint32_t atou32(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 64-bit signed integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 64-bit signed integer.
 */
extern int64_t atoi64(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 64-bit unsigned integer.
 *
 * @param str The input string to convert.
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The converted 64-bit unsigned integer.
 */
extern uint64_t atou64(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a double-precision floating-point number.
 *
 * @param str The input string to convert.
 * @param d The decimal point character (default: '.').
 * @param endptr Optional pointer to store the address of the first invalid character.
 * @return The converted double-precision floating-point number.
 */
extern double atod(const char *str, const char d = '.', const char **endptr = nullptr);

/**
 * @brief Counts occurrences of a character in a string.
 *
 * @param str The input string.
 * @param c The character to count.
 * @return The number of occurrences of the character (including null terminator).
 */
extern size_t chrCount(const char *str, char c);

/**
 * @brief Counts occurrences of a substring in a string.
 *
 * @param str The input string.
 * @param find The substring to count.
 * @return The number of occurrences of the substring.
 */
extern size_t strCount(const char *str, const char *find);

/**
 * @brief Splits a string into an array of substrings based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array of substring pointers.
 * @param delim The delimiter character.
 */
extern void strCut(char *str, char **ar, char delim);

/**
 * @brief Joins an array of strings into a single string with a delimiter.
 *
 * @param arr The input array of strings.
 * @param arrCount The number of strings in the array.
 * @param delimiter The delimiter to use between strings.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinChrArr(const char **arr, size_t arrCount, char delimiter, char *buf, size_t bufSize);

/**
 * @brief Joins an array of booleans into a string with a delimiter.
 *
 * @param arr The input array of booleans.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinBool(const bool *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 8-bit signed integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinInt8(const int8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 8-bit unsigned integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinUint8(const uint8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 16-bit signed integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinInt16(const int16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 16-bit unsigned integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinUint16(const uint16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 32-bit signed integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinInt32(const int32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 32-bit unsigned integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinUint32(const uint32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 64-bit signed integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinInt64(const int64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of 64-bit unsigned integers into a string with a delimiter.
 *
 * @param arr The input array of integers.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinUint64(const uint64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Joins an array of floats into a string with a delimiter.
 *
 * @param arr The input array of floats.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param dec Number of decimal places for each float.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinFloat(const float *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter);

/**
 * @brief Joins an array of doubles into a string with a delimiter.
 *
 * @param arr The input array of doubles.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param dec Number of decimal places for each double.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinDouble(const double *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter);

/**
 * @brief Joins an array of strings into a string with a delimiter.
 *
 * @param arr The input array of strings.
 * @param len The length of the array.
 * @param buf The output buffer for the joined string.
 * @param bufSize The size of the output buffer.
 * @param delimiter The delimiter to use between values.
 * @return Pointer to the joined string, or nullptr if the buffer is too small.
 */
extern char *joinStr(const char **arr, size_t len, char *buf, size_t bufSize, char delimiter);

/**
 * @brief Splits a string into an array of booleans based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the booleans.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern bool *splitb(char *str, bool *ar, char const delim, size_t count);

/**
 * @brief Splits a string into an array of characters based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the characters.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern char *splitc(char *str, char *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 8-bit signed integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern int8_t *spliti8(char *str, int8_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 8-bit unsigned integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern uint8_t *splitu8(char *str, uint8_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 16-bit signed integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern int16_t *spliti16(char *str, int16_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 16-bit unsigned integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern uint16_t *splitu16(char *str, uint16_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 32-bit signed integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern int32_t *spliti32(char *str, int32_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 32-bit unsigned integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern uint32_t *splitu32(char *str, uint32_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 64-bit signed integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern int64_t *spliti64(char *str, int64_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of 64-bit unsigned integers based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the integers.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern uint64_t *splitu64(char *str, uint64_t *ar, const char delim, size_t count);

/**
 * @brief Splits a string into an array of floats based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the floats.
 * @param d The decimal point character.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern float *splitf(char *str, float *ar, const char d, const char delim, size_t count);

/**
 * @brief Splits a string into an array of doubles based on a delimiter.
 *
 * @param str The input string to split.
 * @param ar The output array for the doubles.
 * @param d The decimal point character.
 * @param delim The delimiter character.
 * @param count The number of elements to parse.
 * @return Pointer to the output array.
 */
extern double *splitd(char *str, double *ar, const char d, const char delim, size_t count);

#include "utils.tpp"

}  // namespace ut