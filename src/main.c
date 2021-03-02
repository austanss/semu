#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <minifb/minifb.h>
#include "ram.h"
#include "addressing.h"
#include "log.h"
#include "video.h"
#include "registers.h"
#include "rom.h"
#include "info.h"
#include "instructions.h"

uint32_t* window_pixel_buffer;

int run_window();

int main(int argc, char** argv)
{
    thrd_t window_thread;
    thrd_create(&window_thread, run_window, NULL);

    window_pixel_buffer = calloc(4, 800 * 600);

    if (--argc <= 0)
    {
        log_error("rom: no file specified");
        return -1;
    }

    addressing_create_address_space();

    int state = load_flat_rom(fopen(argv[1], "rb"));
    if (state > 0)
        return state;

    initialize_registers();

    memory_start_ram();
    
    video_map_framebuffer(window_pixel_buffer);

    log_set_quiet(true);

    registers[mrp] = 0xfffc0000;

    do
    {
        execute_instruction(((uint64_t)address_read_dword(registers[mrp]) << 32) | address_read_dword(registers[mrp] + 4));
        registers[mrp] += 8;
    } while (true);
    

    return 0;
}

void keyboard_callback(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool is_pressed);

int run_window()
{
    struct mfb_window *window = mfb_open_ex("semu", 800, 600, 0);
    if (!window)
        return -2;

    mfb_set_keyboard_callback(window, keyboard_callback);

    do {
        int state;

        state = mfb_update_ex(window, window_pixel_buffer, 800, 600);

        if (state < 0) {
            window = NULL;
            break;
        }

    } while(mfb_wait_sync(window));

    return 0;
}

void keyboard_callback(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool is_pressed) 
{
    (void)window;
    // QEMU-style Ctrl+Alt+Q to quit
    if (key == KB_KEY_Q && mod == (KB_MOD_CONTROL | KB_MOD_ALT) && is_pressed)
        *(long *)NULL = (long)(NULL); // segmentation fault

    if (key == KB_KEY_R && mod == (KB_MOD_CONTROL | KB_MOD_ALT) && is_pressed)
        info_registers();
}