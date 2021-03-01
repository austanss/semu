#pragma once

#include <stdint.h>

#define hr0 0x00
#define hr1 0x01
#define hr2 0x02
#define hr3 0x03
#define gra 0x04
#define grb 0x05
#define grc 0x06
#define grd 0x07
#define gre 0x08
#define grf 0x09
#define orl 0x0a
#define orr 0x0b
#define nrl 0x0c
#define nrr 0x0d
#define ara 0x0e
#define ars 0x0f
#define arm 0x10
#define ard 0x11
#define aro 0x12
#define bra 0x13
#define bro 0x14
#define brx 0x15
#define brn 0x16
#define srl 0x17
#define srr 0x18
#define nro 0x19
#define prs 0x1a
#define prb 0x1b
#define mrf 0x1c
#define mri 0x1d
#define mre 0x1e
#define mrn 0x1f
#define mrp 0x20

void    initialize_registers();

extern uint32_t registers[33];