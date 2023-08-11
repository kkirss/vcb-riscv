
const unsigned int WORD_SIZE = 32;

// TODO: Make this more dynamic/portable
const unsigned int FRAME_BUFFER_POINTER_ADDR = 0x200000 * (8 / WORD_SIZE);

void configure_display(unsigned int x, unsigned int y, unsigned int color_depth);
unsigned int* allocate_frame_buffer();
void display_frame_buffer(unsigned int* frame_buffer);

void set_pixel_1b(unsigned int x, unsigned int y, unsigned int new_color, unsigned int* frame_buffer);
