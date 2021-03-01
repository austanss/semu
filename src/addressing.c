#include <stdlib.h>
#include <stdio.h>
#include "addressing.h"
#include "ram.h"
#include "log.h"

struct addressable_device_list_node* devices_list;

void addressing_create_device_list()
{
    struct addressable_device_list_node* null_device_list_node = calloc(1, sizeof(struct addressable_device_list_node));
    null_device_list_node->last = true;
    null_device_list_node->device = calloc(1, sizeof(struct addressable_device));
    devices_list = null_device_list_node;
    log_info("addressing: creating null device 0");
}

void addressing_map_device(struct addressable_device *device)
{
    (void)device;

    struct addressable_device_list_node* last_device_list_node = devices_list;

    int device_list_index;

    for (device_list_index = 0; !last_device_list_node->last; device_list_index++)
        last_device_list_node = last_device_list_node->next;

    last_device_list_node->last = false;
    last_device_list_node->next = calloc(1, sizeof(struct addressable_device_list_node));
    last_device_list_node = last_device_list_node->next;

    last_device_list_node->device = device;
    last_device_list_node->last = true;

    device_list_index++;

    log_info("addressing: mapping device %d:", device_list_index);
    log_info("\taddress: %lx", last_device_list_node->device->start_address);
    log_info("\tend: %lx", last_device_list_node->device->end_address);
}

void addressing_create_address_space()
{
    addressing_create_device_list();
    struct addressable_device *ram_device = malloc(sizeof(struct addressable_device));
    ram_device->start_address = 0x0;
    ram_device->end_address = 0x0 + 16 * 1024 * 1024;
    ram_device->device = ram;
    addressing_map_device(ram_device);
}

uint8_t address_read_byte(uint64_t address)
{
    struct addressable_device_list_node *addressed_device;

    for (addressed_device = devices_list; !addressed_device->last; addressed_device = addressed_device->next)
        if (address >= addressed_device->device->start_address && address <= addressed_device->device->end_address)
            break;

    if (!(address >= addressed_device->device->start_address && address <= addressed_device->device->end_address))
        addressed_device = NULL;

    if (addressed_device == NULL)
        return 0x0; // we should raise #AF exception, but we haven't set up exceptions yet

    uint64_t device_data_index = address - addressed_device->device->start_address;    

    return addressed_device->device->device[device_data_index];
}

void address_write_byte(uint64_t address, uint8_t value)
{
    struct addressable_device_list_node *addressed_device;

    for (addressed_device = devices_list; !addressed_device->last; addressed_device = addressed_device->next)
        if (address >= addressed_device->device->start_address && address <= addressed_device->device->end_address)
            break;

    if (!(address >= addressed_device->device->start_address && address <= addressed_device->device->end_address))
        addressed_device = NULL;

    if (addressed_device == NULL)
        {} // we should raise #AF exception, but we haven't set up exceptions yet

    uint64_t device_data_index = address - addressed_device->device->start_address;    

    addressed_device->device->device[device_data_index] = value;
}