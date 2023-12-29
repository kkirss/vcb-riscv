#pragma once

#include "vinput_key_map.h"

inline volatile unsigned int VIRTUAL_INPUT __attribute__((used, section(".virtual_input")));

namespace VInputKeys {

inline Key read_virtual_input_key() { return VIRTUAL_INPUT_KEYS[VIRTUAL_INPUT]; }

} // namespace VInputKeys
