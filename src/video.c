#include <stdlib.h>
#include "video.h"
#include "addressing.h"

void video_map_framebuffer(uint32_t *framebuffer)
{
    struct addressable_device *framebuffer_device = malloc(sizeof(struct addressable_device));
    framebuffer_device->start_address = 0x100009FFF;
    framebuffer_device->device = (uint8_t *)framebuffer;
    framebuffer_device->end_address = framebuffer_device->start_address + 800 * 600 * 4;
    addressing_map_device(framebuffer_device);
}