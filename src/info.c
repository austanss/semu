#include <stdio.h>
#include "info.h"
#include "registers.h"

void info_registers() 
{
    printf( "-=-=-\n\tGRA: %x GRB: %x GRC: %x\n\tGRD: %x GRE: %x GRF: %x\n\n"
            "\tORL: %x ORR: %x \n\tNRL: %x NRR: %x\n\n"
            "\tMRF: %x\n\tMRI: %x\n\tMRE: %x\n\tMRP: %x\n"
            "-=-=-\n", 
        registers[gra],
        registers[grb],
        registers[grc],
        registers[grd],
        registers[gre],
        registers[grf],

        registers[orl],
        registers[orr],
        registers[nrl],
        registers[nrr],
        
        registers[mrf],
        registers[mri],
        registers[mre],
        registers[mrp]);
}
void info_memory()
{}
void info_devices()
{}
void info_video()
{}
void info_interrupts()
{}