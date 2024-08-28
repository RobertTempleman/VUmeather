#pragma once


#define NUM_SBM20S 4
#define NUM_TUBES (NUM_SBM20S+1)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long COLORREF;

void pc(u8 x,u8 y,COLORREF col);
void draw_tube_background(u8 orig_x,u8 orig_y,u8 wx,u8 wy,u8 tube);
void draw_tube(u8 orig_x,u8 orig_y,u8 wx,u8 wy,u8 tube);
void one_second_update_counter();
void draw_background();
void drawit();

extern u32 counts[NUM_TUBES];
