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
    int state = load_flat_rom(fopen(argv[1], "rb"));
    if (state & 1)
        return state;

    initialize_registers();

    memory_start_ram();

    addressing_create_address_space();
    
    video_map_framebuffer(window_pixel_buffer);

    log_set_quiet(true);

    do
    {
        (void)argv;
    } while (true);
    

    return 0;
}

int run_window()
{
    struct mfb_window *window = mfb_open_ex("semu", 800, 600, 0);
    if (!window)
        return -2;

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