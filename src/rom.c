#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "rom.h"
#include "addressing.h"

uint8_t* rom;

void map_rom_device();

int load_flat_rom(FILE* file)
{
    if (!file)
    {
        log_error("rom: invalid file specified");
        return -1;
    }

    map_rom_device();

    int bytes_read = fread(rom, sizeof(uint8_t), 256 * 1024, file);

    if (!bytes_read)
    {
        log_error("rom: invalid file specified");
        return -1;
    }

    return 0;
}

void map_rom_device()
{
    rom = calloc(256, 1024);
    struct addressable_device *rom_device = calloc(1, sizeof(struct addressable_device));
    rom_device->start_address = 0xfffc0000;
    rom_device->end_address = 0xffffffff;
    rom_device->device = rom;
    addressing_map_device(rom_device);
}