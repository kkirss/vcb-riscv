#pragma once

#include <array>

using std::array;

// Co-ordinates originate from top-left

constexpr unsigned int WORD_SIZE = 32;

struct DisplayConfig {
    constexpr DisplayConfig(const unsigned int width,
                            const unsigned int height,
                            const unsigned int color_depth)
        : width(width),
          height(height),
          color_depth(color_depth) {}

    const unsigned int width;
    const unsigned int height;
    const unsigned int color_depth;

    const unsigned int pixels_per_word = WORD_SIZE / color_depth;
    const unsigned int words_per_row = width / pixels_per_word;

    const unsigned int pixel_mask_lsb = (1 << color_depth) - 1;
    const unsigned int pixel_mask_msb = pixel_mask_lsb << (WORD_SIZE - color_depth);
};

#define FrameBufferRow array<unsigned int, display_config.words_per_row>
#define FrameBuffer array<array<unsigned int, display_config.words_per_row>, display_config.height>

template <DisplayConfig DISPLAY_CONFIG>
struct DisplayBuffers {
    static constexpr DisplayConfig display_config = DISPLAY_CONFIG;

    static constexpr unsigned int frame_buffer_size =
        (display_config.width * display_config.height) / display_config.pixels_per_word;

    static inline FrameBuffer a = {};
    static inline FrameBuffer b = {};

    static_assert(display_config.color_depth >= 1 && display_config.color_depth <= 8 ||
                      display_config.color_depth == 24,
                  "Color depth must be 1-8 or 24");

    static_assert(display_config.width % display_config.pixels_per_word == 0,
                  "Display width must be a multiple of the number of pixels per word");
};

inline unsigned int frame_buffer_pointer __attribute__((used, section(".display_pointer")));

template <DisplayConfig display_config>
void display_frame_buffer(FrameBuffer &frame_buffer) {
    // Divide by 4 as VMEM address is in words
    frame_buffer_pointer = reinterpret_cast<unsigned int>(&frame_buffer) >> 2;
}

template <DisplayConfig display_config>
void draw_pixel(const unsigned int x,
                const unsigned int y,
                const unsigned int new_color,
                FrameBuffer &frame_buffer) {
    // Calculate the column and word index
    const unsigned int column = x / display_config.pixels_per_word;
    const unsigned int word_index = x % display_config.pixels_per_word;

    // Shift the mask and color to the correct position within the word
    const unsigned int shift_amount = WORD_SIZE - (display_config.color_depth * (word_index + 1));
    const unsigned int pixel_mask = display_config.pixel_mask_lsb << shift_amount;
    const unsigned int shifted_color = new_color << shift_amount;

    // Update the pixel word
    unsigned int &pixel_word = frame_buffer[y][column];
    pixel_word = (pixel_word & ~pixel_mask) | shifted_color;
}
