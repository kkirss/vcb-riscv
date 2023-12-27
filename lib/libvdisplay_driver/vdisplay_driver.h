#pragma once

// Co-ordinates originate from top-left

constexpr unsigned int WORD_SIZE = 32;

inline unsigned int frame_buffer_pointer __attribute__((used, section(".display_pointer")));

void display_frame_buffer(const unsigned int *frame_buffer);

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

    const unsigned int pixel_mask_lsb = (1 << color_depth) - 1;
    const unsigned int pixel_mask_msb = pixel_mask_lsb << (WORD_SIZE - color_depth);
};

template <DisplayConfig DISPLAY_CONFIG>
struct DisplayBuffers {
    static constexpr DisplayConfig display_config = DISPLAY_CONFIG;

    static constexpr unsigned int frame_buffer_size =
        (display_config.width * display_config.height) / display_config.pixels_per_word;

    static inline unsigned int a[frame_buffer_size];
    static inline unsigned int b[frame_buffer_size]; // For future use

    static_assert(display_config.color_depth >= 1 && display_config.color_depth <= 8 ||
                      display_config.color_depth == 24,
                  "Color depth must be 1-8 or 24");

    static_assert(display_config.width % display_config.pixels_per_word == 0,
                  "Display width must be a multiple of the number of pixels per word");
};

template <DisplayConfig display_config>
void draw_pixel(const unsigned int x,
                const unsigned int y,
                const unsigned int new_color,
                unsigned int *frame_buffer) {
    // Calculate the sequential pixel number within the frame buffer
    const unsigned int sequential_pixel_number = x + (y * display_config.width);

    // Calculate the word address within the frame buffer
    const unsigned int mem_word_address = sequential_pixel_number / display_config.pixels_per_word;

    // Get reference to the word where the pixel is located
    unsigned int &pixel_word = frame_buffer[mem_word_address];

    // Calculate the index of the pixel within the word
    const unsigned int pixel_word_index = sequential_pixel_number % display_config.pixels_per_word;

    // Calculate the masks for the pixel within the word (MSB is left-most pixel)
    const unsigned int shift_amount =
        WORD_SIZE - (display_config.color_depth * (pixel_word_index + 1));
    const unsigned int pixel_mask = display_config.pixel_mask_lsb << shift_amount;
    const unsigned int shifted_color = new_color << shift_amount;

    pixel_word = (pixel_word & ~pixel_mask) | shifted_color;
}
