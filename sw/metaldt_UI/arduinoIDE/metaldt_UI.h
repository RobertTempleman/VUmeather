#pragma once

#include "resource.h"

#define PROGMEM

typedef unsigned long u32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef unsigned char prog_uchar;

void pc(u8 x,u8 y,DWORD col);
u8 pgm_read_byte_near(const u8 *add);
