// scrollher2View.h : interface of the Cscrollher2View class
//


#pragma once
//void print_pretty(int screen_x,int screen_y,const char *string, COLORREF colour_alpha, COLORREF colour_number, COLORREF colour_operators,bool auto_kern=false,bool no_output=false,bool no_space=false,bool masked=false);
void print_pretty_byte(u8 screen_x,u8 screen_y,const char *string, COLORREF colour_alpha, COLORREF colour_number, COLORREF colour_operators,bool auto_kern=false,bool no_output=false,bool no_space=false);
void set_mask_data(u8 x,u8 y,s8*txt,u8 _mask_lookup_draw_key_line=1);
u8 mask_lookup(u8 x_screen,u8 y_screen);
u8 pgm_read_byte_near_font_compressed(u16 pos);

#define CHAR_IMAGE_WIDTH 13
#define CHAR_PLOT_WIDTH 10
#define CHAR_PLOT_HEIGHT 13
#define CHAR_IMAGE_STRIDE 182
extern PROGMEM prog_uchar big_font[];
