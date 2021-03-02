#include <stdint.h>
#include <stdbool.h>
#include "instructions.h"
#include "registers.h"
#include "addressing.h"

void execute_instruction(uint64_t instruction)
{
    uint8_t opcode = (instruction >> 56) & 0xFF;
    if (opcode != 0xF0)
        return; // invalid operands error placeholder

    uint8_t destination_type = (instruction >> 48) & 0xFF;

    bool we_already_addressed_memory = false;

    if ((destination_type < 0x04 || destination_type > 0x20) && destination_type < 0x27)
        we_already_addressed_memory = true;
    else if (destination_type > 0x26)
        return; // invalid operands error placeholder    

    uint8_t source_type;

    if (we_already_addressed_memory)
        source_type = (instruction >> 8) & 0xFF;
    else
        source_type = (instruction >> 40) & 0xFF;
    
    if ((source_type < 0x04 || source_type > 0x20) && we_already_addressed_memory)
        return; // invalid operands error placeholder

    uint64_t destination_value = 0;
    uint64_t source_value = 0;

    switch (destination_type)
    {
        case 0x0:
            return; // invalid operands error placeholder

        case 0x1:
        case 0x2:
        case 0x3:
            destination_value = (instruction >> 16) & 0xFFFFFFFF;
            break;

        case 0x21:
        case 0x22:
        case 0x23:
            destination_value = registers[(instruction >> 40) & 0xFF];
            destination_value += (instruction >> 16) & 0xFFFFFF;
            break;    

        case 0x24:
        case 0x25:
        case 0x26:
            destination_value = registers[(instruction >> 40) & 0xFF];
            destination_value -= (instruction >> 16) & 0xFFFFFF;
            if (destination_value > 0xFFFFFFFF)
            {
                destination_value -= 0xFFFFFFFF;
                destination_value = 0xFFFFFFFF - destination_value;
            }
            break;

        default: break;
    }

    switch (source_type)
    {
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
            source_value = (instruction >> 8) & 0xFFFFFFFF;
            break;

        case 0x21:
        case 0x22:
        case 0x23:
            source_value = registers[(instruction >> 32) & 0xFF];
            source_value += (instruction >> 8) & 0xFFFFFF;
            break;    

        case 0x24:
        case 0x25:
        case 0x26:
            source_value = registers[(instruction >> 32) & 0xFF];
            source_value -= (instruction >> 8) & 0xFFFFFF;
            if (source_value > 0xFFFFFFFF)
            {
                source_value -= 0xFFFFFFFF;
                source_value = 0xFFFFFFFF - source_value;
            }
            break;

        default: break;    
    }

    if (destination_type > 0x03 && destination_type < 0x21) // is a register destination
    {
        if (source_type > 0x03 && source_type < 0x21) // is a register destination
        {
            registers[destination_type] = registers[source_type];
            return;
        }
        if (source_type == 0x0) // is an immediate value
        {
            registers[destination_type] = source_value;
            return;
        }
        if (source_type < 0x04 || source_type > 0x20)
        {
            if (source_type == 0x01 || source_type == 0x21 || source_type == 0x24)
            {
                registers[destination_type] = address_read_byte(source_value);
                return;
            }
            if (source_type == 0x02 || source_type == 0x22 || source_type == 0x25)
            {
                registers[destination_type] = address_read_word(source_value);
                return;
            }
            if (source_type == 0x03 || source_type == 0x23 || source_type == 0x26)
            {
                registers[destination_type] = address_read_dword(source_value);
                return;
            }
        }
    }
    if (destination_type < 0x04 || destination_type > 0x20)
    {
        if (destination_type == 0x01 || destination_type == 0x21 || destination_type == 0x24)
        {
            address_write_byte(destination_value, registers[source_type]);
            return;
        }
        if (destination_type == 0x02 || destination_type == 0x22 || destination_type == 0x25)
        {
            address_write_word(destination_value, registers[source_type]);
            return;
        }
        if (destination_type == 0x03 || destination_type == 0x23 || destination_type == 0x26)
        {
            address_write_dword(destination_value, registers[source_type]);
            return;
        }   
    }
}