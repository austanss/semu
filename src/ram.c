#include <stdlib.h>
#include "ram.h"
#include "log.h"
#include "addressing.h"

uint8_t *ram;
uint64_t ram_size;

void memory_start_ram()
{
    ram_size = 16 * 1024 * 1024;
    log_info("ram: allocating %lum ram\n", ram_size / 1024 / 1024);
    ram = calloc(16, 1024 * 1024);

    struct addressable_device *ram_device = malloc(sizeof(struct addressable_device));
    ram_device->start_address = 0x0;
    ram_device->end_address = 0x0 + 16 * 1024 * 1024;
    ram_device->device = ram;
    addressing_map_device(ram_device);
}