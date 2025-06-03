#include "utils.h"

namespace ut {

uint8_t BCD2DEC(uint8_t bcd) {
  return (((bcd >> 4) & 0xf) * 10) + (bcd & 0xf);
}

uint8_t DEC2BCD(uint8_t dec) {
  return (((dec / 10) << 4) & 0xf0) + (dec % 10);
}

uint8_t onTimeMin(uint32_t &t, uint32_t delayTime, bool reset) {
  uint32_t diff = millis() - t;
  if (diff >= delayTime * 1000 * 60) {
    if (reset) t = millis();
    return 1;
  }
  return 0;
}
uint8_t onTimeSec(uint32_t &t, uint32_t delayTime, bool reset) {
  uint32_t diff = millis() - t;
  if (diff >= delayTime * 1000) {
    if (reset) t = millis();
    return 1;
  }
  return 0;
}
uint8_t onTimeMs(uint32_t &t, uint32_t delayTime, bool reset) {
  uint32_t diff = millis() - t;
  if (diff >= delayTime) {
    if (reset) t = millis();
    return 1;
  }
  return 0;
}
uint8_t onTimeUs(uint32_t &t, uint32_t delayTime, bool reset) {
  uint32_t diff = micros() - t;
  if (diff >= delayTime) {
    if (reset) t = micros();
    return 1;
  }
  return 0;
}
void delayUs(uint32_t start, uint32_t wait) {
  uint32_t diff;
  diff = micros() - start;
  while (diff < wait) {
    diff = micros() - start;
    yield();
  }
}
void delayMs(uint32_t start, uint32_t wait) {
  uint32_t diff;
  diff = millis() - start;
  while (diff < wait) {
    diff = millis() - start;
    yield();
  }
}

char *strreverse(char *str) {
  uint8_t i, j;
  char a;
  uint8_t len = strlen(str);
  for (i = 0, j = len - 1; i < j; i++, j--) {
    a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
  return str;
}

char *i8toa(int8_t num, char *str, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u8toa(-num, str + 1, base) - 1;
  } else {
    return u8toa(num, str, base);
  }
}

char *u8toa(uint8_t num, char *str, uint8_t base) {
  uint8_t i = 0, rem;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (num != 0) {
    rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';
  strreverse(str);
  return str;
}

char *i16toa(int16_t num, char *str, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u16toa(-num, str + 1, base) - 1;
  } else {
    return u16toa(num, str, base);
  }
}

char *u16toa(uint16_t num, char *str, uint8_t base) {
  uint8_t i = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (num != 0) {
    uint16_t rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';

  strreverse(str);

  return str;
}

char *i32toa(int32_t num, char *str, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u32toa(-num, str + 1, base) - 1;
  } else {
    return u32toa(num, str, base);
  }
}

char *u32toa(uint32_t num, char *str, uint8_t base) {
  uint8_t i = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (num != 0) {
    uint32_t rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';

  strreverse(str);

  return str;
}

char *i64toa(int64_t num, char *str, uint8_t base) {
  if (num < 0) {
    str[0] = '-';
    return u64toa(-num, str + 1, base) - 1;
  } else {
    return u64toa(num, str, base);
  }
}

char *u64toa(uint64_t num, char *str, uint8_t base) {
  uint8_t i = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (num != 0) {
    uint64_t rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';

  strreverse(str);

  return str;
}

char *ftoa(float num, char *str, int8_t minWidth, uint8_t len, uint8_t dec) {
  return dtoa(num, str, minWidth, len, dec);
}

char *dtoa(double num, char *str, int8_t minWidth, size_t len, uint8_t dec) {
  char fmt[len];
  sprintf(fmt, "%%%d.%df", minWidth, dec);
  sprintf(str, fmt, num);
  return str;
}

uint8_t atou8(const char *str, const char **endptr, uint8_t base) {
  return atoi8(str, endptr, base);
}
int8_t atoi8(const char *str, const char **endptr, uint8_t base) {
  const char *s = str;
  uint8_t acc = 0;
  uint8_t neg = 0;
  char c;
  if (s[0] == '-') {
    neg = 1;
    s++;
  } else if (s[0] == '+') {
    s++;
  }
  if ((s[0] == '0') && (s[1] == 'x')) {
    base = 16;
    s += 2;
  }
  do {
    c = *s++;
    if (isDigit(c))
      c -= '0';
    else if (isAlpha(c))
      c -= isUpperCase(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    acc *= base;
    acc += c;
  } while (1);
  if (endptr != nullptr)
    *endptr = (char *)(s - 1);
  if (neg)
    acc = -acc;
  return (acc);
}

uint16_t atou16(const char *str, const char **endptr, uint8_t base) {
  return atoi16(str, endptr, base);
}
int16_t atoi16(const char *str, const char **endptr, uint8_t base) {
  const char *s = str;
  uint16_t acc = 0;
  uint8_t neg = 0;
  char c;
  if (s[0] == '-') {
    neg = 1;
    s++;
  } else if (s[0] == '+') {
    s++;
  }
  if ((s[0] == '0') && (s[1] == 'x')) {
    base = 16;
    s += 2;
  }
  do {
    c = *s++;
    if (isDigit(c))
      c -= '0';
    else if (isAlpha(c))
      c -= isUpperCase(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    acc *= base;
    acc += c;
  } while (1);
  if (endptr != nullptr)
    *endptr = (char *)(s - 1);
  if (neg)
    acc = -acc;
  return (acc);
}

uint32_t atou32(const char *str, const char **endptr, uint8_t base) {
  return atoi32(str, endptr, base);
}
int32_t atoi32(const char *str, const char **endptr, uint8_t base) {
  const char *s = str;
  uint32_t acc = 0;
  uint8_t neg = 0;
  char c;
  if (s[0] == '-') {
    neg = 1;
    s++;
  } else if (s[0] == '+') {
    s++;
  }
  if ((s[0] == '0') && (s[1] == 'x')) {
    base = 16;
    s += 2;
  }
  do {
    c = *s++;
    if (isDigit(c))
      c -= '0';
    else if (isAlpha(c))
      c -= isUpperCase(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    acc *= base;
    acc += c;
  } while (1);
  if (endptr != nullptr)
    *endptr = (char *)(s - 1);
  if (neg)
    acc = -acc;
  return (acc);
}

uint64_t atou64(const char *str, const char **endptr, uint8_t base) {
  return atoi64(str, endptr, base);
}
int64_t atoi64(const char *str, const char **endptr, uint8_t base) {
  const char *s = str;
  uint64_t acc = 0;
  uint8_t neg = 0;
  char c;
  if (s[0] == '-') {
    neg = 1;
    s++;
  } else if (s[0] == '+') {
    s++;
  }
  if ((s[0] == '0') && (s[1] == 'x')) {
    base = 16;
    s += 2;
  }
  do {
    c = *s++;
    if (isDigit(c))
      c -= '0';
    else if (isAlpha(c))
      c -= isUpperCase(c) ? 'A' - 10 : 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    acc *= base;
    acc += c;
  } while (1);
  if (endptr != nullptr)
    *endptr = (char *)(s - 1);
  if (neg)
    acc = -acc;
  return (acc);
}

double atod(const char *str, char decimalPoint, const char **endptr) {
  if (!str || !decimalPoint) {
    if (endptr) *endptr = str;
    return 0.0;
  }

  while (isspace(*str)) str++;

  int8_t sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  if (strncasecmp(str, "inf", 3) == 0) {
    if (endptr) *endptr = str + 3;
    return sign == 1 ? INFINITY : -INFINITY;
  }
  if (strncasecmp(str, "nan", 3) == 0) {
    if (endptr) *endptr = str + 3;
    return sign == 1 ? NAN : -NAN;
  }

  double result = 0.0;
  int64_t integer_part = 0;
  int64_t fractional_part = 0;
  int64_t fractional_divisor = 1;
  bool has_fraction = false;

  while (isdigit(*str)) {
    int digit = *str - '0';
    if (integer_part > INT64_MAX / 10) {
      if (endptr) *endptr = str;
      return sign == 1 ? INFINITY : -INFINITY;
    }
    integer_part = integer_part * 10 + digit;
    str++;
  }

  if (*str == decimalPoint) {
    has_fraction = true;
    str++;
    while (isdigit(*str)) {
      int digit = *str - '0';
      if (fractional_divisor > INT64_MAX / 10) {
        break;
      }
      fractional_part = fractional_part * 10 + digit;
      fractional_divisor *= 10;
      str++;
    }
  }

  int32_t exponent = 0;
  bool has_exponent = false;
  if (*str == 'e' || *str == 'E') {
    has_exponent = true;
    str++;
    int8_t exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      str++;
    } else if (*str == '+') {
      str++;
    }
    while (isdigit(*str)) {
      int digit = *str - '0';
      if (exponent > INT32_MAX / 10) {
        if (endptr) *endptr = str;
        return sign == 1 ? INFINITY : -INFINITY;
      }
      exponent = exponent * 10 + digit;
      str++;
    }
    exponent *= exp_sign;
  }

  result = (double)integer_part;
  if (has_fraction) {
    result += (double)fractional_part / fractional_divisor;
  }
  if (has_exponent) {
    result *= pow(10.0, exponent);
  }
  result *= sign;

  if (isinf(result)) {
    if (endptr) *endptr = str;
    return sign == 1 ? INFINITY : -INFINITY;
  }
  if (isnan(result)) {
    if (endptr) *endptr = str;
    return NAN;
  }

  if (endptr) *endptr = str;
  return result;
}

size_t chrCount(const char *str, char c) {
  size_t count = 0;
  while (*str != '\0')
    if (*str++ == c)
      count++;
  count++;
  return count;
}

void strCut(char *str, char **ar, char delim) {
  if (!str || !ar) {
    return;
  }
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

size_t strCount(const char *str, const char *find) {
  size_t count = 0;
  size_t len = strlen(find);

  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == find[0]) {
      if (!strncmp(str, find, len)) {
        count++;
        i += len - 1;
      }
    }
  }
  return count;
}

char *joinChrArr(const char **arr, size_t arrCount, char delimiter, char *buf, size_t bufSize) {
  if (!arr || !buf || arrCount == 0 || bufSize == 0) {
    return nullptr;
  }

  size_t totalLen = 0;
  for (size_t i = 0; i < arrCount; i++) {
    if (arr[i]) {
      totalLen += strlen(arr[i]);
    }
    if (i < arrCount - 1) {
      totalLen++;
    }
  }

  if (totalLen + 1 > bufSize) {
    return nullptr;
  }

  char *ptr = buf;
  for (size_t i = 0; i < arrCount; i++) {
    if (arr[i]) {
      size_t len = strlen(arr[i]);
      memcpy(ptr, arr[i], len);
      ptr += len;
    }
    if (i < arrCount - 1) {
      *ptr++ = delimiter;
    }
  }
  *ptr = '\0';

  return buf;
}

char *joinBool(const bool *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[2];
    temp[0] = arr[i] ? '1' : '0';
    temp[1] = '\0';

    size_t temp_len = 1;
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    *ptr++ = temp[0];
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinInt8(const int8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[I8_CHR_MAX];
    i8toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return ptr;
}

char *joinUint8(const uint8_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[U8_CHR_MAX];
    u8toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinInt16(const int16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[I16_CHR_MAX];
    i16toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinUint16(const uint16_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[U16_CHR_MAX];
    u16toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinInt32(const int32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[I32_CHR_MAX];
    i32toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinUint32(const uint32_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[U32_CHR_MAX];
    u32toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinInt64(const int64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[I64_CHR_MAX];
    i64toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinUint64(const uint64_t *arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[U64_CHR_MAX];
    u64toa(arr[i], temp, 10);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinFloat(const float *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[32];
    ftoa(arr[i], temp, 1, sizeof(temp), dec);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinDouble(const double *arr, size_t len, char *buf, size_t bufSize, uint8_t dec, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    char temp[32];
    dtoa(arr[i], temp, 1, sizeof(temp), dec);

    size_t temp_len = strlen(temp);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, temp, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

char *joinStr(const char **arr, size_t len, char *buf, size_t bufSize, char delimiter) {
  if (!arr || !buf || len == 0 || bufSize == 0) {
    return 0;
  }

  char *ptr = buf;
  size_t remaining = bufSize;

  for (size_t i = 0; i < len; i++) {
    const char *str = arr[i] ? arr[i] : "";
    size_t temp_len = strlen(str);
    bool needs_delimiter = (i < len - 1);

    if (temp_len + (needs_delimiter ? 1 : 0) + 1 > remaining) {
      *ptr = '\0';
      return 0;
    }

    memcpy(ptr, str, temp_len);
    ptr += temp_len;
    remaining -= temp_len;

    if (needs_delimiter) {
      *ptr++ = delimiter;
      remaining--;
    }
  }

  *ptr = '\0';
  return buf;
}

bool *splitb(char *str, bool *ar, char const delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi8(p, &p, 10);
    p++;
  }
  return ar;
}

char *splitc(char *str, char *ar, const char delim, size_t count) {
  char *s[count];
  strCut(str, s, delim);
  for (size_t i = 0; i < count; i++) {
    ar[i] = s[i][0];
  }
  return ar;
}

extern bool *splitc(char *str, bool *ar, char const delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi8(p, &p, 10);
    p++;
  }
  return ar;
}

int8_t *spliti8(char *str, int8_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi8(p, &p, 10);
    p++;
  }
  return ar;
}

uint8_t *splitu8(char *str, uint8_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi8(p, &p, 10);
    p++;
  }
  return ar;
}

int16_t *spliti16(char *str, int16_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi16(p, &p, 10);
    p++;
  }
  return ar;
}
uint16_t *splitu16(char *str, uint16_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi16(p, &p, 10);
    p++;
  }
  return ar;
}
int32_t *spliti32(char *str, int32_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi32(p, &p, 10);
    p++;
  }
  return ar;
}
uint32_t *splitu32(char *str, uint32_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi32(p, &p, 10);
    p++;
  }
  return ar;
}
int64_t *spliti64(char *str, int64_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi64(p, &p, 10);
    p++;
  }
  return ar;
}
uint64_t *splitu64(char *str, uint64_t *ar, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atoi64(p, &p, 10);
    p++;
  }
  return ar;
}

float *splitf(char *str, float *ar, const char d, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atod(p, d, &p);
    p++;
  }
  return ar;
}

double *splitd(char *str, double *ar, const char d, const char delim, size_t count) {
  const char *p = str;
  for (size_t i = 0; i < count; i++) {
    ar[i] = atod(p, d, &p);
    p++;
  }
  return ar;
}

}  // namespace ut