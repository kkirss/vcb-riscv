#include "simple_font.h"

namespace SimpleFont {
    const Sprite<unsigned int, 4, 5> H = {{
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1}
    }};
    const Sprite<unsigned int, 4, 5> I = {{
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0}
    }};
}
