#pragma once



#define assert(a)
typedef u16 COLORREF;

void p(u8 x, u8 y);
void vline_2p(u8 x, u8 y,COLORREF gcol2);
void pc(u8 x,u8 y,COLORREF col);
void plot_char_3x5(u8 xp,u8 yp,u16 offset,COLORREF col);
void drawit();
void metaldt__processing_loop(u8 only_do_radio=0);
void RTT_wang_it_down_the_hardware_SPI(u8 potentiometer, u8 data_byte);

