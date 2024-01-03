#pragma once

#include <array>

#include "vinput_key.h"

using std::array;

namespace VInputKeys {

struct VInputKeyMap {
    unsigned int scan_code;
    Key key;
};

static constexpr inline array<VInputKeyMap, 102> virtual_input_map = {{
    {0x04, Keys::A},
    {0x05, Keys::B},
    {0x06, Keys::C},
    {0x07, Keys::D},
    {0x08, Keys::E},
    {0x09, Keys::F},
    {0x0a, Keys::G},
    {0x0b, Keys::H},
    {0x0c, Keys::I},
    {0x0d, Keys::J},
    {0x0e, Keys::K},
    {0x0f, Keys::L},
    {0x10, Keys::M},
    {0x11, Keys::N},
    {0x12, Keys::O},
    {0x13, Keys::P},
    {0x14, Keys::Q},
    {0x15, Keys::R},
    {0x16, Keys::S},
    {0x17, Keys::T},
    {0x18, Keys::U},
    {0x19, Keys::V},
    {0x1a, Keys::W},
    {0x1b, Keys::X},
    {0x1c, Keys::Y},
    {0x1d, Keys::Z},
    {0x1e, Keys::_1},
    {0x1f, Keys::_2},
    {0x20, Keys::_3},
    {0x21, Keys::_4},
    {0x22, Keys::_5},
    {0x23, Keys::_6},
    {0x24, Keys::_7},
    {0x25, Keys::_8},
    {0x26, Keys::_9},
    {0x27, Keys::_0},
    {0x28, Keys::ENTER},
    {0x29, Keys::ESCAPE},
    {0x2a, Keys::BACKSPACE},
    {0x2b, Keys::TAB},
    {0x2c, Keys::SPACE},
    {0x2d, Keys::MINUS},
    {0x2e, Keys::EQUAL},
    {0x2f, Keys::BRACKETLEFT},
    {0x30, Keys::BRACKETRIGHT},
    {0x31, Keys::BACKSLASH},
    {0x33, Keys::SEMICOLON},
    {0x34, Keys::APOSTROPHE},
    {0x35, Keys::QUOTELEFT},
    {0x36, Keys::COMMA},
    {0x37, Keys::PERIOD},
    {0x38, Keys::SLASH},
    {0x39, Keys::CAPSLOCK},
    {0x3a, Keys::F1},
    {0x3b, Keys::F2},
    {0x3c, Keys::F3},
    {0x3d, Keys::F4},
    {0x3e, Keys::F5},
    {0x3f, Keys::F6},
    {0x40, Keys::F7},
    {0x41, Keys::F8},
    {0x42, Keys::F9},
    {0x43, Keys::F10},
    {0x44, Keys::F11},
    {0x45, Keys::F12},
    {0x46, Keys::PRINT},
    {0x47, Keys::SCROLLLOCK},
    {0x48, Keys::PAUSE},
    {0x49, Keys::INSERT},
    {0x4a, Keys::HOME},
    {0x4b, Keys::PAGEUP},
    {0x4c, Keys::DELETE},
    {0x4d, Keys::END},
    {0x4e, Keys::PAGEDOWN},
    {0x4f, Keys::RIGHT},
    {0x50, Keys::LEFT},
    {0x51, Keys::DOWN},
    {0x52, Keys::UP},
    {0x53, Keys::NUMLOCK},
    {0x54, Keys::KEYPAD_DIVIDE},
    {0x55, Keys::KEYPAD_MULTIPLY},
    {0x56, Keys::KEYPAD_SUBTRACT},
    {0x57, Keys::KEYPAD_ADD},
    {0x58, Keys::KEYPAD_ENTER},
    {0x59, Keys::KEYPAD_1},
    {0x5a, Keys::KEYPAD_2},
    {0x5b, Keys::KEYPAD_3},
    {0x5c, Keys::KEYPAD_4},
    {0x5d, Keys::KEYPAD_5},
    {0x5e, Keys::KEYPAD_6},
    {0x5f, Keys::KEYPAD_7},
    {0x60, Keys::KEYPAD_8},
    {0x61, Keys::KEYPAD_9},
    {0x62, Keys::KEYPAD_0},
    {0x63, Keys::KEYPAD_PERIOD},
    {0x68, Keys::F13},
    {0x69, Keys::F14},
    {0x6a, Keys::F15},
    {0x6b, Keys::F16},
    {0xe0, Keys::CONTROL},
    {0xe1, Keys::SHIFT},
    {0xe2, Keys::ALT},
}};

typedef array<Key, 0xFF> VirtualInputKeys;

static constexpr VirtualInputKeys VIRTUAL_INPUT_KEYS = [] {
    VirtualInputKeys virtual_input_keys{};
    for (const auto [scan_code, key] : virtual_input_map) {
        virtual_input_keys[scan_code] = key;
    }
    return virtual_input_keys;
}();

} // namespace VInputKeys
