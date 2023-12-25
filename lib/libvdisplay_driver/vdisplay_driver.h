#pragma once

#include <type_traits>

// Co-ordinates originate from top-left

constexpr unsigned int WORD_SIZE = 32;

inline unsigned int frame_buffer_pointer __attribute__((used, section(".display_pointer")));

void display_frame_buffer(const unsigned int *frame_buffer);

template <unsigned int WIDTH, unsigned int HEIGHT, unsigned int COLOR_DEPTH>
class Display {
public:
    static_assert(COLOR_DEPTH >= 1 && COLOR_DEPTH <= 8 || COLOR_DEPTH == 24,
                  "Color depth must be 1-8 or 24");

    static constexpr unsigned int PIXELS_PER_WORD = WORD_SIZE / COLOR_DEPTH;
    static_assert(WIDTH % PIXELS_PER_WORD == 0,
                  "Display width must be a multiple of the number of pixels per word");

    static constexpr unsigned int PIXEL_MASK_LSB = (1 << COLOR_DEPTH) - 1;
    static constexpr unsigned int PIXEL_MASK_MSB = PIXEL_MASK_LSB << (WORD_SIZE - COLOR_DEPTH);

    static constexpr unsigned int FRAME_BUFFER_SIZE = (WIDTH * HEIGHT * COLOR_DEPTH) / WORD_SIZE;
    static inline unsigned int frame_buffer_a[FRAME_BUFFER_SIZE];
    static inline unsigned int frame_buffer_b[FRAME_BUFFER_SIZE]; // For future use

    static void draw_pixel(const unsigned int x,
                           const unsigned int y,
                           const unsigned int new_color,
                           unsigned int *frame_buffer) {
        // Calculate the sequential pixel number within the frame buffer
        const unsigned int sequential_pixel_number = x + (y * WIDTH);

        // Calculate the word address within the frame buffer
        const unsigned int mem_word_address = sequential_pixel_number / PIXELS_PER_WORD;

        // Get reference to the word where the pixel is located
        unsigned int &pixel_word = frame_buffer[mem_word_address];

        // Calculate the index of the pixel within the word
        const unsigned int pixel_word_index = sequential_pixel_number % PIXELS_PER_WORD;

        // Calculate the masks for the pixel within the word (MSB is left-most pixel)
        const unsigned int shift_amount = WORD_SIZE - (COLOR_DEPTH * (pixel_word_index + 1));
        const unsigned int pixel_mask = PIXEL_MASK_LSB << shift_amount;
        const unsigned int shifted_color = new_color << shift_amount;

        pixel_word = (pixel_word & ~pixel_mask) | shifted_color;
    }
};

template <typename T>
struct is_display : std::false_type {};

template <unsigned int WIDTH, unsigned int HEIGHT, unsigned int COLOR_DEPTH>
struct is_display<Display<WIDTH, HEIGHT, COLOR_DEPTH>> : std::true_type {};

template <typename T>
concept IsDisplay = is_display<T>::value;
