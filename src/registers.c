#include "log.h"
#include "registers.h"

void initialize_registers()
{
    log_info("cpu: zeroing registers");
    for (int i = 0; i < 33; i++)
        registers[i] = 0;
}

uint32_t registers[33];