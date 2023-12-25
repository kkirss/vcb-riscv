#pragma once
#include "sprite.h"

// Co-ordinates originate from top-left

constexpr unsigned int WORD_SIZE = 32;

inline unsigned int frame_buffer_pointer __attribute__((used, section (".display_pointer")));

void display_frame_buffer(const unsigned int* frame_buffer);

template<unsigned int WIDTH, unsigned int HEIGHT, unsigned int COLOR_DEPTH>
class Display {
public:
    // TODO: What if pixels don't align with word boundaries?
    // TODO: Ensure that display dimensions are multiples of word size

    static constexpr unsigned int FRAME_BUFFER_SIZE = (WIDTH * HEIGHT * COLOR_DEPTH) / WORD_SIZE;
    static inline unsigned int frame_buffer_a[FRAME_BUFFER_SIZE] __attribute__((used, section(".display_buffers")));
    static inline unsigned int frame_buffer_b[FRAME_BUFFER_SIZE] __attribute__((used, section(".display_buffers"))); // For future use

    static void set_pixel_1b(const unsigned int x, const unsigned int y, const unsigned int new_color, unsigned int *frame_buffer) {
        // Calculate the sequential pixel number within the frame buffer
        const unsigned int sequential_pixel_number = x + (y * WIDTH);

        // Calculate the word address within the frame buffer
        const unsigned int mem_word_address = sequential_pixel_number / WORD_SIZE;

        // Get reference to the word where the pixel is located
        unsigned int &pixel_word = frame_buffer[mem_word_address];

        // Calculate the bit mask for the pixel, within the word
        const unsigned int mem_pixel_mask = 1 << (WORD_SIZE - (sequential_pixel_number % WORD_SIZE) - 1);

        // Set or clear the pixel based on new_color
        if (new_color == 1) {
            pixel_word |= mem_pixel_mask;
        } else {
            pixel_word &= ~mem_pixel_mask;
        }
    }

    template<IsSprite SpriteType>
    static void draw_sprite(const unsigned int x_pos, const unsigned int y_pos, const SpriteType& sprite, unsigned int *frame_buffer) {
        for (unsigned int y = 0; y < SpriteType::height; ++y) {
            for (unsigned int x = 0; x < SpriteType::width; ++x) {
                set_pixel_1b(x_pos + x, y_pos + y, sprite.pixels[y][x], frame_buffer);
            }
        }
    }
};
