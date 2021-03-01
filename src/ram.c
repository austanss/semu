#include <stdlib.h>
#include "ram.h"
#include "log.h"

uint8_t *ram;
uint64_t ram_size;

void memory_start_ram()
{
    ram_size = 16 * 1024 * 1024;
    log_info("ram: allocating %lum ram\n", ram_size / 1024 / 1024);
    ram = calloc(16, 1024 * 1024);
}