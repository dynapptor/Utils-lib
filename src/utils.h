#pragma once

#include <Arduino.h>

/**
 * @def I8_CHR_MAX
 * @brief Maximum number of characters required to represent an int8_t as a string (e.g., "-128").
 */
#define I8_CHR_MAX 5

/**
 * @def U8_CHR_MAX
 * @brief Maximum number of characters required to represent a uint8_t as a string (e.g., "255").
 */
#define U8_CHR_MAX 4

/**
 * @def I16_CHR_MAX
 * @brief Maximum number of characters required to represent an int16_t as a string (e.g., "-32768").
 */
#define I16_CHR_MAX 7

/**
 * @def U16_CHR_MAX
 * @brief Maximum number of characters required to represent a uint16_t as a string (e.g., "65535").
 */
#define U16_CHR_MAX 6

/**
 * @def I32_CHR_MAX
 * @brief Maximum number of characters required to represent an int32_t as a string (e.g., "-2147483648").
 */
#define I32_CHR_MAX 12

/**
 * @def U32_CHR_MAX
 * @brief Maximum number of characters required to represent a uint32_t as a string (e.g., "4294967295").
 */
#define U32_CHR_MAX 11

/**
 * @def I64_CHR_MAX
 * @brief Maximum number of characters required to represent an int64_t as a string (e.g., "-9223372036854775808").
 */
#define I64_CHR_MAX 22

/**
 * @def U64_CHR_MAX
 * @brief Maximum number of characters required to represent a uint64_t as a string (e.g., "18446744073709551615").
 */
#define U64_CHR_MAX 21

/**
 * @brief Extracts a specified bit field from a value of type T.
 * @tparam T The type of the input value (e.g., uint8_t, uint16_t, etc.).
 * @param v The input value from which to extract bits.
 * @param start The starting position of the bit field (0-based index).
 * @param count The number of bits to extract.
 * @return The extracted bit field as a value of type T.
 */
template <typename T>
static T getBits(T v, uint8_t start, uint8_t count);

/**
 * @union union16
 * @brief A 16-bit union for accessing data in different formats within the same memory region.
 */
union union16 {
  uint16_t u16;   ///< Unsigned 16-bit integer.
  int16_t i16;    ///< Signed 16-bit integer.
  uint8_t u8[2];  ///< Array of two unsigned 8-bit integers.
  int8_t i8[2];   ///< Array of two signed 8-bit integers.
};

/**
 * @union union32
 * @brief A 32-bit union for accessing data in different formats within the same memory region.
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
 * @union union64
 * @brief A 64-bit union for accessing data in different formats within the same memory region.
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
 * @brief Checks if the specified time (in minutes) has elapsed since the last timestamp.
 * @param t Pointer to the timestamp (in milliseconds).
 * @param delay_min The delay time in minutes.
 * @param reset If true, updates the timestamp to the current time.
 * @return True if the specified time has elapsed, false otherwise.
 */
extern bool on_min(uint32_t *t, uint32_t delay_min, bool reset = false);

/**
 * @brief Checks if the specified time (in seconds) has elapsed since the last timestamp.
 * @param t Pointer to the timestamp (in milliseconds).
 * @param delay_sec The delay time in seconds.
 * @param reset If true, updates the timestamp to the current time.
 * @return True if the specified time has elapsed, false otherwise.
 */
extern bool on_sec(uint32_t *t, uint32_t delay_sec, bool reset = false);

/**
 * @brief Checks if the specified time (in milliseconds) has elapsed since the last timestamp.
 * @param t Pointer to the timestamp (in milliseconds).
 * @param delay_ms The delay time in milliseconds.
 * @param reset If true, updates the timestamp to the current time.
 * @return True if the specified time has elapsed, false otherwise.
 */
extern bool on_ms(uint32_t *t, uint32_t delay_ms, bool reset = false);

/**
 * @brief Checks if the specified time (in microseconds) has elapsed since the last timestamp.
 * @param t Pointer to the timestamp (in microseconds).
 * @param delay_us The delay time in microseconds.
 * @param reset If true, updates the timestamp to the current time.
 * @return True if the specified time has elapsed, false otherwise.
 */
extern bool on_us(uint32_t *t, uint32_t delay_us, bool reset = false);

/**
 * @brief Delays execution for the specified number of microseconds from the start time.
 * @param start The start time (in microseconds, typically obtained from micros()).
 * @param wait_us The delay time in microseconds.
 */
extern void delay_us(uint32_t start, uint32_t wait_us);

/**
 * @brief Delays execution for the specified number of milliseconds from the start time.
 * @param start The start time (in milliseconds, typically obtained from millis()).
 * @param wait_ms The delay time in milliseconds.
 */
extern void delay_ms(uint32_t start, uint32_t wait_ms);

/**
 * @brief Converts a Binary-Coded Decimal (BCD) number to a decimal number.
 * @param bcd The BCD input number.
 * @return The decimal equivalent.
 */
extern uint8_t bcd2dec(uint8_t bcd);

/**
 * @brief Converts a decimal number to a Binary-Coded Decimal (BCD) number.
 * @param dec The decimal input number.
 * @return The BCD equivalent.
 */
extern uint8_t dec2bcd(uint8_t dec);

/**
 * @brief Converts a boolean value to a string.
 * @param num The boolean value (true/false).
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param t Optional string to represent true (default: "true").
 * @param f Optional string to represent false (default: "false").
 * @return Pointer to the output string, or NULL on error.
 */
extern char *bool_to_str(bool num, char *str, uint8_t str_len, const char *t = nullptr, const char *f = nullptr);

/**
 * @brief Converts an 8-bit signed integer to a string.
 * @param num The int8_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *i8_to_str(int8_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts an 8-bit unsigned integer to a string.
 * @param num The uint8_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *u8_to_str(uint8_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 16-bit signed integer to a string.
 * @param num The int16_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *i16_to_str(int16_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 16-bit unsigned integer to a string.
 * @param num The uint16_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *u16_to_str(uint16_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 32-bit signed integer to a string.
 * @param num The int32_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *i32_to_str(int32_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 32-bit unsigned integer to a string.
 * @param num The uint32_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *u32_to_str(uint32_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 64-bit signed integer to a string.
 * @param num The int64_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *i64_to_str(int64_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a 64-bit unsigned integer to a string.
 * @param num The uint64_t number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param base The numerical base (default: 10).
 * @return Pointer to the output string, or NULL on error.
 */
extern char *u64_to_str(uint64_t num, char *str, uint8_t str_len, uint8_t base = 10);

/**
 * @brief Converts a float to a string with specified formatting.
 * @param num The float number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param min_width The minimum field width for formatting.
 * @param dec The number of decimal places.
 * @return Pointer to the output string, or NULL on error.
 */
extern char *float_to_str(float num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec);

/**
 * @brief Converts a double to a string with specified formatting.
 * @param num The double number to convert.
 * @param str The output string buffer.
 * @param str_len The size of the buffer.
 * @param min_width The minimum field width for formatting.
 * @param dec The number of decimal places.
 * @return Pointer to the output string, or NULL on error.
 */
extern char *double_to_str(double num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec);

/**
 * @brief Converts a string to a boolean value.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param t Optional string representing true (default: "true").
 * @param f Optional string representing false (default: "false").
 * @return The parsed boolean value, or false on error.
 */
extern bool str_to_bool(const char *str, const char **endptr = nullptr, const char *t = nullptr, const char *f = nullptr);

/**
 * @brief Converts a string to an 8-bit signed integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed int8_t value, or 0 on error.
 */
extern int8_t str_to_i8(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to an 8-bit unsigned integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed uint8_t value, or 0 on error.
 */
extern uint8_t str_to_u8(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 16-bit signed integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed int16_t value, or 0 on error.
 */
extern int16_t str_to_i16(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 16-bit unsigned integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed uint16_t value, or 0 on error.
 */
extern uint16_t str_to_u16(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 32-bit signed integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed int32_t value, or 0 on error.
 */
extern int32_t str_to_i32(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 32-bit unsigned integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed uint32_t value, or 0 on error.
 */
extern uint32_t str_to_u32(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 64-bit signed integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed int64_t value, or 0 on error.
 */
extern int64_t str_to_i64(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a 64-bit unsigned integer.
 * @param str The input string to parse.
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @param base The numerical base (default: 10).
 * @return The parsed uint64_t value, or 0 on error.
 */
extern uint64_t str_to_u64(const char *str, const char **endptr = nullptr, uint8_t base = 10);

/**
 * @brief Converts a string to a double-precision floating-point number.
 * @param str The input string to parse.
 * @param d The decimal separator character (e.g., '.' or ',').
 * @param endptr Optional pointer to store the address of the first unparsed character.
 * @return The parsed double value, or 0.0 on error.
 */
extern double str_to_double(const char *str, char d = '.', const char **endptr = nullptr);

/**
 * @brief Reverses the characters in a string.
 * @param str The input string to reverse.
 * @return Pointer to the reversed string, or NULL on error.
 */
extern char *str_reverse(char *str);

/**
 * @brief Counts occurrences of a character in a string.
 * @param str The input string to search.
 * @param c The character to count.
 * @return The number of occurrences of the character.
 */
extern size_t chr_count(const char *str, char c);

/**
 * @brief Counts occurrences of a substring in a string.
 * @param str The input string to search.
 * @param find The substring to count.
 * @return The number of occurrences of the substring.
 */
extern size_t str_count(const char *str, const char *find);

/**
 * @brief Splits a string into an array of substrings based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store substring pointers.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 */
extern void str_cut(char *str, char **ar, size_t ar_size, char delim = ',');

/**
 * @brief Joins an array of characters into a string with a delimiter.
 * @param ar The input array of characters.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character.
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_chr_arr(const char *ar, size_t ar_size, char *buf, size_t buf_size, char delim);

/**
 * @brief Joins an array of boolean values into a string with a delimiter.
 * @param ar The input array of boolean values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @param t Optional string to represent true (default: "true").
 * @param f Optional string to represent false (default: "false").
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_bool(const bool *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',', const char *t = nullptr, const char *f = nullptr);

/**
 * @brief Joins an array of 8-bit signed integers into a string with a delimiter.
 * @param ar The input array of int8_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_i8(const int8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 8-bit unsigned integers into a string with a delimiter.
 * @param ar The input array of uint8_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_u8(const uint8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 16-bit signed integers into a string with a delimiter.
 * @param ar The input array of int16_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_i16(const int16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 16-bit unsigned integers into a string with a delimiter.
 * @param ar The input array of uint16_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_u16(const uint16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 32-bit signed integers into a string with a delimiter.
 * @param ar The input array of int32_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_i32(const int32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 32-bit unsigned integers into a string with a delimiter.
 * @param ar The input array of uint32_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_u32(const uint32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 64-bit signed integers into a string with a delimiter.
 * @param ar The input array of int64_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_i64(const int64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of 64-bit unsigned integers into a string with a delimiter.
 * @param ar The input array of uint64_t values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_u64(const uint64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Joins an array of floats into a string with a delimiter.
 * @param ar The input array of float values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param dec The number of decimal places.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_float(const float *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim = ',');

/**
 * @brief Joins an array of doubles into a string with a delimiter.
 * @param ar The input array of double values.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param dec The number of decimal places.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_double(const double *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim = ',');

/**
 * @brief Joins an array of strings into a single string with a delimiter.
 * @param ar The input array of strings.
 * @param ar_size The size of the input array.
 * @param buf The output string buffer.
 * @param buf_size The size of the buffer.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output string, or NULL on error.
 */
extern char *join_str(const char **ar, size_t ar_size, char *buf, size_t buf_size, char delim = ',');

/**
 * @brief Splits a string into an array of boolean values based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store boolean values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @param t Optional string to represent true (default: "true").
 * @param f Optional string to represent false (default: "false").
 * @return Pointer to the output array, or NULL on error.
 */
extern bool *split_bool(const char *str, bool *ar, size_t ar_size, char delim = ',', const char *t = nullptr, const char *f = nullptr);

/**
 * @brief Splits a string into an array of characters based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store characters.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern char *split_chr(const char *str, char *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into tokens based on a delimiter, extracting only quoted substrings.
 *
 * This function processes an input string, extracts substrings enclosed in double quotes (`"`), and stores them in a destination buffer.
 * The extracted tokens are referenced by an array of pointers (`ar`). Non-quoted parts of the string are ignored, and the function supports
 * escaped quotes (`\"`) and backslashes (`\\`) within quoted strings. The destination buffer can be the same as the input string for in-place processing.
 *
 * @param str The input string to process (null-terminated).
 * @param dest The destination buffer where extracted tokens are stored.
 * @param dest_size The size of the destination buffer (including space for null terminators).
 * @param ar Array of pointers to store the starting addresses of extracted tokens.
 * @param ar_size The size of the `ar` array (maximum number of tokens to extract).
 * @param delim The delimiter character to separate tokens (default: ',').
 *
 * @return Pointer to the destination buffer (`dest`) on success, or `NULL` if any input parameter is invalid
 *         (`str`, `dest`, or `ar` is `NULL`, or `dest_size` or `ar_size` is 0).
 *
 * @note The function modifies the `dest` buffer and may overwrite the input string if `str` and `dest` are the same.
 * @note The caller must ensure `dest_size` is sufficient to hold all extracted tokens plus null terminators.
 * @note Tokens exceeding `ar_size` are ignored, and the function stops processing if the `dest` buffer is full.
 * @warning Ensure `dest_size` is large enough to avoid buffer overflow, especially in memory-constrained environments like Arduino.
 */
extern char *split_str(const char *str, char *dest, size_t dest_size, const char **ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 8-bit signed integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store int8_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern int8_t *split_i8(const char *str, int8_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 8-bit unsigned integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store uint8_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern uint8_t *split_u8(const char *str, uint8_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 16-bit signed integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store int16_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern int16_t *split_i16(const char *str, int16_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 16-bit unsigned integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store uint16_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern uint16_t *split_u16(const char *str, uint16_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 32-bit signed integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store int32_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern int32_t *split_i32(const char *str, int32_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 32-bit unsigned integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store uint32_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern uint32_t *split_u32(const char *str, uint32_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 64-bit signed integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store int64_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern int64_t *split_i64(const char *str, int64_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of 64-bit unsigned integers based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store uint64_t values.
 * @param ar_size The size of the output array.
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern uint64_t *split_u64(const char *str, uint64_t *ar, size_t ar_size, char delim = ',');

/**
 * @brief Splits a string into an array of floats based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store float values.
 * @param ar_size The size of the output array.
 * @param d The decimal separator character (e.g., '.' or ',').
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern float *split_float(const char *str, float *ar, size_t ar_size, char d, char delim = ',');

/**
 * @brief Splits a string into an array of doubles based on a delimiter.
 * @param str The input string to split.
 * @param ar The output array to store double values.
 * @param ar_size The size of the output array.
 * @param d The decimal separator character (e.g., '.' or ',').
 * @param delim The delimiter character (default: ',').
 * @return Pointer to the output array, or NULL on error.
 */
extern double *split_double(const char *str, double *ar, size_t ar_size, char d, char delim = ',');

#include "utils.tpp"