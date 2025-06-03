#pragma once
#include "utils.h"

namespace ut {

template <typename T>
static T getBits(T v, uint8_t start, uint8_t count) {
  return (v >> start) & ((1 << count) - 1);
}

}  // namespace ut