#include "vdisplay_driver.h"

void display_frame_buffer(const unsigned int *frame_buffer) {
    // Divide by 4 as VMEM address is in words
    frame_buffer_pointer = reinterpret_cast<unsigned int>(frame_buffer) >> 2;
}
