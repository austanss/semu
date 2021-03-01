#pragma once

#include <stdint.h>
#include <stdbool.h>

struct addressable_device {
    uint64_t    start_address;
    uint8_t     *device;
    uint64_t    end_address;
};

struct addressable_device_list_node {
    struct addressable_device           *device;
    struct addressable_device_list_node *next;
    bool                                last;
};

extern struct addressable_device_list_node* devices_list;

uint8_t     address_read_byte(uint64_t address);
uint16_t    address_read_word(uint64_t address);
uint32_t    address_read_dword(uint64_t address);
void        address_write_byte(uint64_t address, uint8_t value);
void        address_write_word(uint64_t address, uint16_t value);
void        address_write_dword(uint64_t address, uint32_t value);

void        addressing_map_device(struct addressable_device *device);
void        addressing_create_address_space();