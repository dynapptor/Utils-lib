#include "utils.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifdef ARDUINO
#include <Arduino.h>
#endif

uint8_t bcd2dec(uint8_t bcd) {
  return (((bcd >> 4) & 0xf) * 10) + (bcd & 0xf);
}

uint8_t dec2bcd(uint8_t dec) {
  return (((dec / 10) << 4) & 0xf0) + (dec % 10);
}

#ifdef ARDUINO
bool on_min(uint32_t *t, uint32_t delay_min, bool reset) {
  // Validate input
  if (!t) return false;  // Invalid timestamp pointer

  // Calculate elapsed time, handling overflow
  uint32_t current = millis();
  uint32_t diff = current - *t;

  // Convert delay_min (minutes) to milliseconds (60,000 ms per minute)
  uint32_t threshold_ms = delay_min * 60000UL;  // 1000 * 60 = 60000

  // Check if the interval has elapsed
  if (diff >= threshold_ms) {
    // Update timestamp if reset is enabled
    if (reset) *t = current;
    return true;
  }

  return false;
}

bool on_sec(uint32_t *t, uint32_t delay_sec, bool reset) {
  // Validate input
  if (!t) return false;  // Invalid timestamp pointer

  // Calculate elapsed time, handling overflow
  uint32_t current = millis();
  uint32_t diff = current - *t;

  // Convert delay_time (minutes) to milliseconds (60,000 ms per minute)
  uint32_t threshold_ms = delay_sec * 1000UL;  // 1000 * 60 = 60000

  // Check if the interval has elapsed
  if (diff >= threshold_ms) {
    // Update timestamp if reset is enabled
    if (reset) *t = current;
    return true;
  }

  return false;
}

bool on_ms(uint32_t *t, uint32_t delay_ms, bool reset) {
  // Validate input
  if (!t) return false;  // Invalid timestamp pointer

  // Calculate elapsed time, handling overflow
  uint32_t current = millis();
  uint32_t diff = current - *t;

  // Check if the interval has elapsed
  if (diff >= delay_ms) {
    // Update timestamp if reset is enabled
    if (reset) *t = current;
    return true;
  }

  return false;
}

bool on_us(uint32_t *t, uint32_t delay_us, bool reset) {
  // Validate input
  if (!t) return false;  // Invalid timestamp pointer

  // Calculate elapsed time, handling overflow
  uint32_t current = micros();
  uint32_t diff = current - *t;

  // Check if the interval has elapsed
  if (diff >= delay_us) {
    // Update timestamp if reset is enabled
    if (reset) *t = current;
    return true;
  }

  return false;
}

void delay_us(uint32_t start, uint32_t wait_us) {
  // Avoid invalid or excessive delays (e.g., > 71 minutes)
  if (wait_us == 0 || wait_us > 0xFFFFFFFF / 2) {
    return;  // Invalid or too large delay
  }

  // Wait until the specified time has elapsed
  uint32_t diff;
  do {
    diff = micros() - start;  // Handles overflow
    yield();                  // Allow background tasks in Arduino environment
  } while (diff < wait_us);
}

void delay_ms(uint32_t start, uint32_t wait_ms) {
  // Avoid invalid or excessive delays (e.g., > 71 minutes)
  if (wait_ms == 0 || wait_ms > 0xFFFFFFFF / 2) {
    return;  // Invalid or too large delay
  }

  // Wait until the specified time has elapsed
  uint32_t diff;
  do {
    diff = millis() - start;  // Handles overflow
    yield();                  // Allow background tasks in Arduino environment
  } while (diff < wait_ms);
}
#endif

char *bool_to_str(bool num, char *str, uint8_t str_len, const char *t, const char *f) {
  if (!str || str_len == 0) {
    return NULL;  // Invalid buffer or size
  }

  const char *src = num ? (t ? t : "true") : (f ? f : "false");
  size_t src_len = strlen(src) + 1;  // Source string length including null terminator

  if (src_len > str_len) {
    return NULL;  // Buffer too small
  }

  strncpy(str, src, src_len);  // Copy exactly src_len bytes (including \0)
  return str;
}

char *i8_to_str(int8_t num, char *str, uint8_t str_len, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u8_to_str(-num, str + 1, str_len - 1, base) - 1;
  } else {
    return u8_to_str(num, str, str_len - 1, base);
  }
}

char *u8_to_str(uint8_t num, char *str, uint8_t str_len, uint8_t base) {
  if (!str || str_len < 2 || base < 2 || base > 36) {
    return NULL;
  }
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }
  uint8_t i = 0;
  uint8_t rem;
  while (num != 0 && i < str_len - 1) {
    rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num /= base;
  }
  if (num != 0) {
    return NULL;
  }
  str[i] = '\0';
  str_reverse(str);
  return str;
}

char *i16_to_str(int16_t num, char *str, uint8_t str_len, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u16_to_str(-num, str + 1, str_len - 1, base) - 1;
  } else {
    return u16_to_str(num, str, str_len - 1, base);
  }
}

char *u16_to_str(uint16_t num, char *str, uint8_t str_len, uint8_t base) {
  if (!str || str_len < 2 || base < 2 || base > 36) {
    return NULL;
  }
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }
  uint8_t i = 0;
  uint16_t rem;
  while (num != 0 && i < str_len - 1) {
    rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (num != 0) {
    return NULL;
  }

  str[i] = '\0';

  str_reverse(str);

  return str;
}

char *i32_to_str(int32_t num, char *str, uint8_t str_len, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u32_to_str(-num, str + 1, str_len - 1, base) - 1;
  } else {
    return u32_to_str(num, str, str_len - 1, base);
  }
}

char *u32_to_str(uint32_t num, char *str, uint8_t str_len, uint8_t base) {
  if (!str || str_len < 2 || base < 2 || base > 36) {
    return NULL;
  }

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }
  uint8_t i = 0;
  uint32_t rem;

  while (num != 0 && i < str_len - 1) {
    rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (num != 0) {
    return NULL;
  }

  str[i] = '\0';

  str_reverse(str);

  return str;
}

char *i64_to_str(int64_t num, char *str, uint8_t str_len, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u64_to_str(-num, str + 1, str_len - 1, base) - 1;
  } else {
    return u64_to_str(num, str, str_len - 1, base);
  }
}

char *u64_to_str(uint64_t num, char *str, uint8_t str_len, uint8_t base) {
  if (!str || str_len < 2 || base < 2 || base > 36) {
    return NULL;
  }

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  uint8_t i = 0;
  uint64_t rem;
  while (num != 0 && i < str_len - 1) {
    rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (num != 0) {
    return NULL;
  }

  str[i] = '\0';

  str_reverse(str);

  return str;
}

char *float_to_str(float num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec) {
  return double_to_str(num, str, str_len, min_width, dec);
}

char *double_to_str(double num, char *str, uint8_t str_len, int8_t min_width, uint8_t dec) {
  if (!str || str_len == 0) return NULL;

#ifdef __AVR__
  if (min_width > 15 || min_width < -15 || dec > MAX_DECIMAL) return NULL;
#else
  if (min_width > 32 || min_width < -32 || dec > MAX_DECIMAL) return NULL;
#endif

#ifdef __AVR__
  // AVR: double == float, using dtostrf
  dtostrf(num, min_width, dec, str);
  if (strlen(str) >= str_len) {
    return NULL;
  }
#else
  // ESP32: snprintf használata 64-bites double-hoz
  char fmt[12];
  snprintf(fmt, sizeof(fmt), "%%%d.%dlf", min_width, dec);
  if (snprintf(ret.data(), ret.size(), fmt, num) >= ret.size()) {
    return NULL;
  }
#endif
  return str;
}

bool str_to_bool(const char *str, const char **endptr, const char *t, const char *f) {
  // Validate input
  if (!str) {
    if (endptr) *endptr = NULL;
    return false;  // Invalid input string
  }

  // Use default values if t or f is NULL
  const char *true_str = t ? t : "true";
  const char *false_str = f ? f : "false";

  // Compare with true string
  size_t true_len = strlen(true_str);
  if (strncmp(str, true_str, true_len) == 0) {
    if (endptr) *endptr = str + true_len;
    return true;
  }

  // Compare with false string
  size_t false_len = strlen(false_str);
  if (strncmp(str, false_str, false_len) == 0) {
    if (endptr) *endptr = str + false_len;
    return false;
  }

  // No match, invalid string
  if (endptr) *endptr = str;
  return false;
}

uint8_t str_to_u8(const char *str, const char **endptr, uint8_t base) {
  // Use str_to_i8 and validate the result
  return (uint8_t)str_to_i8(str, endptr, base);
}
int8_t str_to_i8(const char *str, const char **endptr, uint8_t base) {
  // Validate input
  if (!str || !*str || base > 36 || (base < 2 && base != 0)) {
    if (endptr) *endptr = str;
    return 0;  // Invalid input or base
  }

  const char *s = str;
  int16_t acc = 0;  // Use int16_t to detect overflow
  uint8_t neg = 0;

  // Skip whitespace
  while (isspace(*s)) s++;

  // Handle sign
  if (*s == '-') {
    neg = 1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  // Auto-detect base for 0x prefix
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X') && (base == 0 || base == 16)) {
    base = 16;
    s += 2;
  } else if (base == 0) {
    base = 10;  // Default to decimal
  }

  // Parse digits
  uint8_t valid = 0;
  while (1) {
    char c = *s;
    uint8_t val;
    if (isdigit(c)) {
      val = c - '0';
    } else if (isalpha(c)) {
      val = tolower(c) - 'a' + 10;
    } else {
      break;
    }
    if (val >= base) break;

    acc = acc * base + val;
    valid = 1;
    s++;
  }

  // Set endptr
  if (endptr) *endptr = valid ? s : str;

  // Apply sign and return
  if (!valid) return 0;  // No valid digits
  return neg ? -acc : acc;
}

uint16_t str_to_u16(const char *str, const char **endptr, uint8_t base) {
  // Use str_to_i16 and validate the result
  return (uint16_t)str_to_i16(str, endptr, base);
}
int16_t str_to_i16(const char *str, const char **endptr, uint8_t base) {
  // Validate input
  if (!str || !*str || base > 36 || (base < 2 && base != 0)) {
    if (endptr) *endptr = str;
    return 0;  // Invalid input or base
  }

  const char *s = str;
  int32_t acc = 0;  // Use int32_t to detect overflow
  uint8_t neg = 0;

  // Skip whitespace
  while (isspace(*s)) s++;

  // Handle sign
  if (*s == '-') {
    neg = 1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  // Auto-detect base for 0x prefix
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X') && (base == 0 || base == 16)) {
    base = 16;
    s += 2;
  } else if (base == 0) {
    base = 10;  // Default to decimal
  }

  // Parse digits
  uint8_t valid = 0;
  while (1) {
    char c = *s;
    uint8_t val;
    if (isdigit(c)) {
      val = c - '0';
    } else if (isalpha(c)) {
      val = tolower(c) - 'a' + 10;
    } else {
      break;
    }
    if (val >= base) break;

    acc = acc * base + val;
    valid = 1;
    s++;
  }

  // Set endptr
  if (endptr) *endptr = valid ? s : str;

  // Apply sign and return
  if (!valid) return 0;  // No valid digits
  return neg ? -acc : acc;
}

uint32_t str_to_u32(const char *str, const char **endptr, uint8_t base) {
  // Use str_to_i32 and validate the result
  return (uint32_t)str_to_i32(str, endptr, base);
}
int32_t str_to_i32(const char *str, const char **endptr, uint8_t base) {
  // Validate input
  if (!str || !*str || base > 36 || (base < 2 && base != 0)) {
    if (endptr) *endptr = str;
    return 0;  // Invalid input or base
  }

  const char *s = str;
  int64_t acc = 0;  // Use int64_t to detect overflow
  uint8_t neg = 0;

  // Skip whitespace
  while (isspace(*s)) s++;

  // Handle sign
  if (*s == '-') {
    neg = 1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  // Auto-detect base for 0x prefix
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X') && (base == 0 || base == 16)) {
    base = 16;
    s += 2;
  } else if (base == 0) {
    base = 10;  // Default to decimal
  }

  // Parse digits
  uint8_t valid = 0;
  while (1) {
    char c = *s;
    uint8_t val;
    if (isdigit(c)) {
      val = c - '0';
    } else if (isalpha(c)) {
      val = tolower(c) - 'a' + 10;
    } else {
      break;
    }
    if (val >= base) break;

    acc = acc * base + val;
    valid = 1;
    s++;
  }

  // Set endptr
  if (endptr) *endptr = valid ? s : str;

  // Apply sign and return
  if (!valid) return 0;  // No valid digits
  return neg ? -acc : acc;
}

uint64_t str_to_u64(const char *str, const char **endptr, uint8_t base) {
  // Use str_to_i64 and validate the result
  return (uint64_t)str_to_i64(str, endptr, base);
}
int64_t str_to_i64(const char *str, const char **endptr, uint8_t base) {
  // Validate input
  if (!str || !*str || base > 36 || (base < 2 && base != 0)) {
    if (endptr) *endptr = str;
    return 0;  // Invalid input or base
  }

  const char *s = str;
  int64_t acc = 0;  // Use int64_t as accumulator
  uint8_t neg = 0;

  // Skip whitespace
  while (isspace(*s)) s++;

  // Handle sign
  if (*s == '-') {
    neg = 1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  // Auto-detect base for 0x prefix
  if (*s == '0' && (s[1] == 'x' || s[1] == 'X') && (base == 0 || base == 16)) {
    base = 16;
    s += 2;
  } else if (base == 0) {
    base = 10;  // Default to decimal
  }

  // Parse digits
  uint8_t valid = 0;
  while (1) {
    char c = *s;
    uint8_t val;
    if (isdigit(c)) {
      val = c - '0';
    } else if (isalpha(c)) {
      val = tolower(c) - 'a' + 10;
    } else {
      break;
    }
    if (val >= base) break;

    acc = acc * base + val;
    valid = 1;
    s++;
  }

  // Set endptr
  if (endptr) *endptr = valid ? s : str;

  // Apply sign and return
  if (!valid) return 0;  // No valid digits
  return neg ? -acc : acc;
}

double str_to_double(const char *str, char d, const char **endptr) {
  // Validate input
  if (!str || !*str || (d != '.' && d != ',')) {
    if (endptr) *endptr = str;
    return 0.0;  // Invalid input or decimal separator
  }

  const char *s = str;
  double result = 0.0;
  int8_t sign = 1;

  // Skip whitespace
  while (isspace(*s)) s++;

  // Handle sign
  if (*s == '-') {
    sign = -1;
    s++;
  } else if (*s == '+') {
    s++;
  }

  // Handle special cases: inf, nan
  if (strncmp(s, "inf", 3) == 0 || strncmp(s, "INF", 3) == 0) {
    if (endptr) *endptr = s + 3;
    return sign == 1 ? INFINITY : -INFINITY;
  }
  if (strncmp(s, "nan", 3) == 0 || strncmp(s, "NAN", 3) == 0) {
    if (endptr) *endptr = s + 3;
    return sign == 1 ? NAN : -NAN;
  }

  int64_t integer_part = 0;
  int64_t fractional_part = 0;
  int64_t fractional_divisor = 1;
  uint8_t has_fraction = 0;

  // Parse integer part
  while (isdigit(*s)) {
    int digit = *s - '0';
    if (integer_part > INT64_MAX / 10) {
      if (endptr) *endptr = s;
      return sign == 1 ? INFINITY : -INFINITY;
    }
    integer_part = integer_part * 10 + digit;
    s++;
  }

  // Parse fractional part
  if (*s == d) {
    has_fraction = 1;
    s++;
    while (isdigit(*s)) {
      int digit = *s - '0';
      if (fractional_divisor > INT64_MAX / 10) {
        break;
      }
      fractional_part = fractional_part * 10 + digit;
      fractional_divisor *= 10;
      s++;
    }
  }

  // Parse exponent
  int32_t exponent = 0;
  uint8_t has_exponent = 0;
  if (*s == 'e' || *s == 'E') {
    has_exponent = 1;
    s++;
    int8_t exp_sign = 1;
    if (*s == '-') {
      exp_sign = -1;
      s++;
    } else if (*s == '+') {
      s++;
    }
    while (isdigit(*s)) {
      int digit = *s - '0';
      if (exponent > 1000) {  // Limit exponent to avoid overflow
        if (endptr) *endptr = s;
        return sign == 1 ? INFINITY : -INFINITY;
      }
      exponent = exponent * 10 + digit;
      s++;
    }
    exponent *= exp_sign;
  }

  // Compute result
  result = (double)integer_part;
  if (has_fraction) {
    result += (double)fractional_part / fractional_divisor;
  }
  if (has_exponent) {
    // Use multiplication/division to avoid pow for small exponents
    if (exponent >= -20 && exponent <= 20) {
      double factor = 1.0;
      int32_t abs_exp = exponent < 0 ? -exponent : exponent;
      while (abs_exp--) factor *= 10.0;
      result *= (exponent >= 0) ? factor : 1.0 / factor;
    } else {
      result *= pow(10.0, exponent);
    }
  }
  result *= sign;

  // Check for special cases
  if (result > 3.4e38 || result < -3.4e38) {  // Approximate float limits
    if (endptr) *endptr = s;
    return sign == 1 ? INFINITY : -INFINITY;
  }
  if (result != result) {  // NaN check
    if (endptr) *endptr = s;
    return NAN;
  }

  if (endptr) *endptr = s;
  return result;
}

char *str_reverse(char *str) {
  // Validate input
  if (!str) {
    return NULL;  // Invalid string pointer
  }

  // Get string length
  size_t len = strlen(str);
  size_t i, j;
  char temp;

  // Swap characters from start and end until meeting in the middle
  for (i = 0, j = len - 1; i < j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }

  return str;
}

size_t chr_count(const char *str, char c) {
  if (!str) return 0;
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == c) count++;
  }
  return count;
}

size_t chr_count(const char *str, size_t str_len, char c) {
  // Validate input
  if (!str) return 0;

  size_t count = 0;
  // Iterate up to str_len characters or until null terminator
  for (size_t i = 0; i < str_len && str[i] != '\0'; i++) {
    if (str[i] == c) count++;
  }

  return count;
}

void str_count(char *str, char **ar, char delim) {
  if (!str || !ar) return;
  uint8_t it = 0;
  uint16_t l = strlen(str);
  char *tmp = str;
  ar[it++] = tmp;
  for (size_t i = 0; i < l; i++) {
    if (str[i] == delim) {
      str[i] = '\0';
      ar[it++] = tmp + 1;
    }
    tmp++;
  }
}

size_t str_count(const char *str, const char *find) {
  if (!str || !find) return 0;  // NULL check
  size_t count = 0;
  size_t len = strlen(find);
  size_t str_len = strlen(str);

  if (len == 0) return 0;  // empty

  for (size_t i = 0; i <= str_len - len; i++) {
    if (!strncmp(str + i, find, len)) {
      count++;
      i += len - 1;  // Jump to the next posizition
    }
  }
  return count;
}

const char **str_cut(char *str, const char **ar, size_t ar_size, char delim) {
  // Check for NULL pointers or invalid max_ar_size
  if (!str || !ar || ar_size == 0) return NULL;

  size_t it = 0;           // Index for the array of substring pointers
  size_t l = strlen(str);  // Length of the input string
  char *tmp = str;         // Pointer to the start of the current substring

  // Store the first substring pointer
  ar[it++] = tmp;

  // Iterate through the string to find delimiters
  for (size_t i = 0; i < l && it < ar_size; i++) {
    if (str[i] == delim) {
      // Replace delimiter with null terminator
      str[i] = '\0';
      // If not at the end, store the next substring pointer
      if (i + 1 < l) {
        ar[it++] = str + i + 1;
      }
    }
  }
  return ar;
}

char *join_chr_arr(const char *ar, size_t ar_size, char *buf, size_t buf_size, char delim) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  for (size_t i = 0; i < ar_size; i++) {
    bool needs_delimiter = (i < ar_size - 1);
    *ptr++ = ar[i];
    if (needs_delimiter) {
      *ptr++ = delim;
    }
  }

  *ptr = '\0';
  return ptr;
}

char *join_bool(const bool *ar, size_t ar_size, char *buf, size_t buf_size, char delim, const char *t, const char *f) {
  // Check for invalid inputs: NULL array, NULL buffer, zero sizes
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return NULL;
  }

  char *ptr = buf;              // Current position in the buffer
  size_t remaining = buf_size;  // Remaining space in the buffer

  // Iterate through the boolean array
  for (size_t i = 0; i < ar_size; i++) {
    // Temporary buffer for bool_to_str output (large enough for typical true/false strings)
    char temp[32];
    // Convert boolean to string using bool_to_str
    if (!bool_to_str(ar[i], temp, sizeof(temp), t, f)) {
      *ptr = '\0';  // Terminate the string
      return NULL;  // Conversion failed
    }

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    // Check if there's enough space for the string, delimiter (if needed), and null terminator
    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';  // Terminate the string
      return NULL;  // Buffer overflow
    }

    // Copy the converted string to the buffer
    strcpy(ptr, temp);
    ptr += temp_len;
    remaining -= temp_len;

    // Add delimiter if not the last element
    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  // Null-terminate the final string
  *ptr = '\0';
  return buf;
}

char *join_i8(const int8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;
  char temp[I8_CHR_MAX];
  for (size_t i = 0; i < ar_size; i++) {
    i8_to_str(ar[i], temp, I8_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return ptr;
}

char *join_u8(const uint8_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;
  char temp[U8_CHR_MAX];
  for (size_t i = 0; i < ar_size; i++) {
    u8_to_str(ar[i], temp, U8_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_i16(const int16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[I16_CHR_MAX];
    i16_to_str(ar[i], temp, I16_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_u16(const uint16_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[U16_CHR_MAX];
    u16_to_str(ar[i], temp, U16_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_i32(const int32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[I32_CHR_MAX];
    i32_to_str(ar[i], temp, I32_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_u32(const uint32_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[U32_CHR_MAX];
    u32_to_str(ar[i], temp, U32_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_i64(const int64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[I64_CHR_MAX];
    i64_to_str(ar[i], temp, I64_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_u64(const uint64_t *ar, size_t ar_size, char *buf, size_t buf_size, char delim, uint8_t base) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[U64_CHR_MAX];
    u64_to_str(ar[i], temp, U64_CHR_MAX, base);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_float(const float *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  char temp[32];
  for (size_t i = 0; i < ar_size; i++) {
    float_to_str(ar[i], temp, 1, sizeof(temp), dec);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_double(const double *ar, size_t ar_size, char *buf, size_t buf_size, uint8_t dec, char delim) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    char temp[32];
    double_to_str(ar[i], temp, 1, sizeof(temp), dec);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *join_str(const char **ar, size_t ar_size, char *buf, size_t buf_size, char delim) {
  if (!ar || !buf || ar_size == 0 || buf_size == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = buf_size;

  for (size_t i = 0; i < ar_size; i++) {
    const char *str = ar[i] ? ar[i] : "";
    size_t temp_len = strlen(str);
    bool needs_delimiter = (i < ar_size - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, str, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delim;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

bool *split_bool(const char *str, bool *ar, size_t ar_size, char delim, const char *t, const char *f) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to boolean using str_to_bool
    const char *endptr;
    ar[i] = str_to_bool(token, &endptr, t, f);

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid boolean value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;  // Explicit cast to avoid warning
    if (next) *next = delim;                   // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

char *split_quoted_str(const char *str, char *dest, size_t dest_size, const char **ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || !dest || ar_size == 0 || dest_size == 0) {
    return NULL;  // Invalid inputs
  }

  // Initialize ar to NULL
  for (size_t i = 0; i < ar_size; i++) {
    ar[i] = NULL;
  }

  // Check if dest buffer is large enough
  // size_t str_len = strlen(str) + 1;  // Include null terminator
  size_t token = 0;
  size_t current = 0;
  bool in_marked = false;  // Track if inside marked string
  const char *p = str;
  char *d = dest;
  while (*p) {
    if (current + 1 > dest_size) {
      *d++ = '\0';
      if (in_marked) ar[token] = NULL;
      return dest;
    }
    if (!in_marked && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t' || *p == '[' || *p == ']')) {
      // continue;
    } else {
      if (*p == '\"') {
        if (!in_marked) {
          in_marked = true;
          ar[token] = d;
        } else {
          in_marked = false;
          *d++ = '\0';
          current++;
        }
      } else if (*p == '\\') {
        if (in_marked) {
          if (p[1] == '\"') {
            *d++ = '\"';
            current++;
            p++;
          } else {
            *d++ = '\\';
            current++;
          }
        }
      } else if (*p == delim && !in_marked) {
        if (token < ar_size) {
          token++;
        } else {
          return dest;
        }
      } else if (in_marked) {
        *d++ = *p;
        current++;
      }
    }
    p++;
  }
  if (in_marked && current <= dest_size) *d = '\0';
  return dest;
}

const char **split_str(const char *str, char *dest, size_t dest_size, const char **ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || !dest || ar_size == 0 || dest_size == 0) return NULL;  // Invalid inputs

  size_t str_len = strlen(str);
  const char *token = str;
  size_t i = 0;
  size_t ai = 0;
  *ar = dest;
  // Process tokens until end of string or array limit
  while (*token && ai < ar_size) {
    // Find next delimiter or end of string
    *dest = *token;
    token++;
    dest++;
    i++;
    if (i == str_len) {
      *dest = '\0';
      return ar;
    }

    if (*token == delim) {
      *dest = '\0';
      token++;
      dest++;
      i++;
      ai++;
      ar[ai] = dest;
    } else if (*token == '\0') {
      *dest = '\0';
      return ar;
    }
  }
  return ar;
}

char *split_chr(const char *str, char *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size <= 1) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  // Copy non-delimiter characters
  size_t pos = 0;
  for (size_t i = 0; str[i] != '\0' && pos < ar_size - 1; i++) {
    if (str[i] != delim) {
      ar[pos++] = str[i];
    }
  }

  // Ensure null termination
  ar[pos] = '\0';

  // Return NULL if no characters were copied
  if (pos == 0) {
    return NULL;  // No valid characters
  }

  return ar;
}

int8_t *split_i8(const char *str, int8_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_i8(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

uint8_t *split_u8(const char *str, uint8_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_u8(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

int16_t *split_i16(const char *str, int16_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_i16(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

uint16_t *split_u16(const char *str, uint16_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_u16(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

int32_t *split_i32(const char *str, int32_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_i32(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

uint32_t *split_u32(const char *str, uint32_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_u32(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

int64_t *split_i64(const char *str, int64_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_i64(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

uint64_t *split_u64(const char *str, uint64_t *ar, size_t ar_size, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_u64(token, &endptr, 10);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

float *split_float(const char *str, float *ar, size_t ar_size, char d, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_double(token, d, &endptr);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

double *split_double(const char *str, double *ar, size_t ar_size, char d, char delim) {
  // Validate inputs
  if (!str || !ar || ar_size == 0) {
    return NULL;  // Invalid string, array, or size
  }
  if (*str == '[') str++;
  const char *token = str;
  size_t i = 0;

  // Process tokens until end of string or array limit
  while (*token && i < ar_size) {
    // Find next delimiter or end of string
    char *next = strchr(token, delim);
    if (next) {
      *next = '\0';  // Temporarily terminate token
    }

    // Parse token to int8_t using str_to_i8
    const char *endptr;
    ar[i] = str_to_double(token, d, &endptr);  // Base 10 for decimal

    // Check if parsing was successful (endptr moved)
    if (endptr == token) {
      if (next) *next = delim;  // Restore delimiter
      return NULL;              // Invalid int8_t value
    }

    // Move to next token
    token = next ? next + 1 : (char *)endptr;
    if (next) *next = delim;  // Restore delimiter
    i++;
  }

  // Return NULL if no valid values were parsed
  if (i == 0) {
    return NULL;  // No valid values parsed
  }

  return ar;
}

bool is_number(const char *str, size_t len) {
  if (!str || len == 0) return false;

  size_t i = 0;

  if (str[i] == '+' || str[i] == '-') {
    i++;
    if (i == len) return false;
  }

  bool has_digit = false;

  for (; i < len; i++) {
    if (!isdigit((unsigned char)str[i])) {
      return false;
    }
    has_digit = true;
  }

  return has_digit;
}

const char *str_end(const char *str) {
  if (!str) return NULL;
  const char *p = str;
  bool instr = false;
  while (*p) {
    if (*p == '\\' && p[1] == '"') {
      p++;
    } else {
      if (*p == '"') {
        if (!instr) {
          instr = true;
          p++;
        } else {
          p++;
          return p;
        }
      }
    }
    p++;
  }
  return NULL;
}

const char *str_ignore(const char *str) {
  if (!str) return NULL;
  const char *p = str;
  while (*p && (*p == ' ' || *p == '\r' || *p == '\n' || *p == '\t')) p++;
  return p;
}

const char *br_end(const char *str) {
  if (!str) return NULL;
  size_t level = 0;
  const char *p = str_ignore(str);
  while (*p) {
    if (*p == '[' || *p == '{') {
      level++;
    } else if (*p == ']' || *p == '}') {
      level--;
      if (level == 0) return p;
    }
    p++;
  }
  return NULL;
}

const char *coma_end(const char *str) {
  if (!str) return NULL;
  const char *p = str;
  while (*p) {
    if (*p == ',' || *p == '}' || *p == ']') return p;
    p++;
  }
  return NULL;
}