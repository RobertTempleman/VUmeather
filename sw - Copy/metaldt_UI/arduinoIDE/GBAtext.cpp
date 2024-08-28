#include "stdafx.h"
#ifdef _WINDOWS
  #include "metaldt__codeblocks.ino.h"
  #include "metaldt_UI_WIN.h"
  #include <vector>
  #include <algorithm>
  using namespace std;
  using std::vector;
#else
  #include "metaldt__codeblocks.ino.h"
  #include "metaldt_UI_AVR.h"
  #include <avr/pgmspace.h>
#endif


extern COLORREF gcol;
extern COLORREF alt_gcol;

// the debug font 3x5 glyphs upper & lowercase+numerals+symbols
#define FONT_CHAR_WIDTH 3
#define FONT_CHAR_HEIGHT 5
PROGMEM uint8_t debug_font_new_compressed[]={0,0,73,16,240,22,136,4,180,42,149,162,125,158,243,148,68,145,84,117,21,186,0,128,2,12,0,128,72,37,111,123,77,210,249,252,60,223,158,124,206,63,239,79,146,239,251,247,60,4,1,4,69,69,196,113,68,84,70,65,239,115,245,237,186,206,73,188,182,123,150,63,75,156,214,237,219,75,58,201,170,93,155,36,239,223,246,127,213,86,235,18,181,243,186,214,17,119,73,106,219,183,173,218,191,173,218,86,210,169,220,146,156,136,52,73,171,0,0,224,128,1,184,117,222,30,79,206,183,199,187,59,79,222,115,201,91,8,146,32,45,233,42,73,66,223,98,109,241,246,239,147,247,36,44,9,31,159,39,70,219,163,173,208,190,168,212,246,52,78,221,154,44,73,154,172,1,7,174,235,0};
// 4=lower like tail of y
// 8=dont remove space if no_space is set
// 16=dont alternate colours if no_space is set
PROGMEM const uint8_t colour_index[96]={
  0  , 0  , 0+16, 0  , 0+8, 0  , 0+8, 0  ,
  0  , 0  , 0   , 0  , 0  , 0  , 0  , 0  ,
  2  , 2  , 2   , 2  , 2  , 2  , 2  , 2  ,
  2  , 2  , 0   , 0  , 0  , 0  , 0  , 0  ,
  0  , 1  , 1   , 1  , 1  , 1  , 1  , 1  ,
  1  , 1  , 1   , 1  , 1  , 1  , 1  , 1  ,
  1  , 1  , 1   , 1  , 1  , 1  , 1  , 1  ,
  1  , 1  , 1   , 0  , 0  , 0  , 0  , 1  ,
  0+8, 1  , 1   , 1+8, 1  , 1  , 1  , 1+4,
  1  , 1  , 1+4 , 1  , 1  , 1  , 1  , 1  ,
  1+4, 1+4, 1   , 1  , 1  , 1  , 1  , 1  ,
  1  , 1+4, 1   , 0  , 0  , 0  , 0  , 0
};
#define CHARS_PER_LINE 8
#define ROWS_OF_CHARS 12
#define POW_CHARS_PER_LINE 3
#define FONT_LINE_WIDTH (CHARS_PER_LINE*FONT_CHAR_WIDTH)




// bookman_oldstyle chars 0123456789uSvph
#define CHAR_IMAGE_WIDTH 13
#define CHAR_PLOT_WIDTH 10
#define CHAR_PLOT_HEIGHT 13
#define CHAR_IMAGE_STRIDE 182
//PROGMEM prog_uchar big_font_compressed[];



#define INCLUDE_ORIGINAL_FONT_PROCESSING 0 // set to enable windows build to recreate compressed font data above


// set data to set drawing mask
u8 mask_x;
u8 mask_y;
s8* mask_txt=0;
u8 mask_txt_len=0;
u8 mask_lookup_draw_key_line=1;
void set_mask_data(u8 x,u8 y,s8*txt,u8 _mask_lookup_draw_key_line){
  mask_lookup_draw_key_line=_mask_lookup_draw_key_line;
  mask_x=x;
  mask_y=y;
  mask_txt=txt;

  mask_txt_len=0;
  while(*(txt++)){mask_txt_len++;}
}



uint8_t pgm_read_byte_near_font_compressed(uint16_t pos){
  u8 byte=pgm_read_byte_near(debug_font_new_compressed+(pos>>3));
  u8 mask=1<<(pos&7);
  u8 kok2=byte&mask;
  return kok2;
}


// use mask text to return whether pixel is inside the font data (return a bounding box 1pixel larger than font
// also plot dotted horizontal line
u8 mask_lookup(u8 x_screen,u8 y_screen){
  if (y_screen<mask_y-1){
    return 0;
  }
  s8 y=y_screen-mask_y;
  if (y>=FONT_CHAR_HEIGHT+1){
    return 0;
  }
  u8 x=x_screen-mask_x;
  u8 char_pos=x>>2;
  if (char_pos>=mask_txt_len){
    if (mask_lookup_draw_key_line){
      if (y==5 && (x&3)>1){
        return 2;
      }
    }
    return 0;
  }
  if (y==-1 || y>=FONT_CHAR_HEIGHT){
    return 2;
  }
  x=x-(char_pos<<2); // char spacing is 4 pixels
  if (x==3) return 2; // last line is char spacing
  u16 char_offset=(mask_txt[char_pos]-32)*FONT_CHAR_WIDTH*FONT_CHAR_HEIGHT;
  char_offset+=x+y*FONT_CHAR_WIDTH;
  if (pgm_read_byte_near_font_compressed(char_offset)){
    return 1;
  }
  return 2;
}


#if INCLUDE_ORIGINAL_FONT_PROCESSING==1
  void convert_to_bitmaps();
  void convert_font_to_vertical_spans();
#endif


void print_pretty_byte(u8 screen_x,u8 screen_y,const char *string, COLORREF colour_alpha, COLORREF colour_number, COLORREF colour_operators,bool auto_kern,bool no_output,bool no_space){
#if INCLUDE_ORIGINAL_FONT_PROCESSING==1
  static bool once=true;
  if (once){
    once=0;
    convert_to_bitmaps();
    convert_font_to_vertical_spans();
  }
#endif
  do{
    const u8 c=*string-32;
    u16 offset_base=c*FONT_CHAR_HEIGHT*FONT_CHAR_WIDTH;
    u8 index=pgm_read_byte_near(colour_index+c);
    COLORREF colour;
    if ((index&3)==1){
      colour=colour_alpha;
    }else if ((index&3)==2){
      colour=colour_number;
    }else{
      colour=colour_operators;
    }
    u8 screen_y_use=screen_y;
    if (index&4){
      screen_y_use++;
    }
    u8 empty_last_column=0;
    if (auto_kern && colour!=colour_number){
      // autokern only text to stop varying numbers messing up text (needs fixed pitch numeric output)
      empty_last_column=1;
      u16 offset=offset_base;
      u8 empty_first_column=1;
      for(u8 y=0;y<FONT_CHAR_HEIGHT;y++){
        u8 ys=y+screen_y_use;
        if (pgm_read_byte_near_font_compressed(offset)!=0){
          empty_first_column=0;
        }
        if (pgm_read_byte_near_font_compressed(offset+2)!=0){
          empty_last_column=0;
        }
        offset+=FONT_CHAR_WIDTH;
      }
      if (empty_first_column){
        screen_x-=1;
      }
    }
    plot_char_3x5(screen_x,screen_y_use,offset_base,colour);
    if (no_space){
      screen_x+=3;
      if (index&8){
        // dont remove space if index has 8 set
        screen_x++;
      }
      if (!(index&16)){
        COLORREF temp=colour_number;
        colour_number=colour_operators;
        colour_operators=temp;
      }
    }else{
      if (auto_kern && empty_last_column){
        screen_x+=3;
      }else{
        screen_x+=4;
      }
    }
  }while(*++string!=0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#if INCLUDE_ORIGINAL_FONT_PROCESSING==1

PROGMEM prog_uchar debugfont[1440]={
  0 , 0 , 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 , 255, 0 ,255,  0 , 0 , 0 ,255,255,255,  // [ ] [!] ["] [#]  [&] [%] ['] [$]
  0 , 0 , 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255, 255, 0 ,255,255 , 0 , 0 ,
  0 , 0 , 0 ,  0 ,255, 0 , 255,255,255, 255, 0 , 0 , 255, 0 ,255,  0 ,255, 0 , 255, 0 ,255,255 ,255,255,
  0 , 0 , 0 ,  0 , 0 , 0 , 255, 0 ,255,  0 ,255, 0 , 255, 0 ,255, 255, 0 , 0 , 255,255,255,  0 , 0 ,255,
  0 , 0 , 0 ,  0 ,255, 0 , 255, 0 ,255,  0 ,255, 0 ,  0 ,255, 0 , 255, 0 ,255, 255, 0 , 0 ,255 ,255,255,

  0 , 0 ,255,  0 ,255, 0 , 255, 0 ,255,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255,
  0 ,255, 0 ,  0 , 0 ,255,  0 ,255, 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255,
  0 ,255, 0 ,  0 , 0 ,255, 255,255,255, 255,255,255,  0 , 0 , 0 ,  0 ,255,255,  0 , 0 , 0 ,  0 ,255, 0 ,
  0 ,255, 0 ,  0 , 0 ,255,  0 ,255, 0 ,  0 ,255, 0 ,  0 , 0 ,255,  0 , 0 , 0 ,  0 , 0 , 0 , 255, 0 , 0 ,
  0 , 0 ,255,  0 ,255, 0 , 255, 0 ,255,  0 , 0 , 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 ,255, 0 , 255, 0 , 0 ,

  255,255,255,  0 ,255, 0 , 255,255,255, 255,255,255, 255, 0 ,255, 255,255,255, 255,255,255, 255,255,255,
  255, 0 ,255, 255,255, 0 ,  0 , 0 ,255,  0 , 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 , 0 ,  0 , 0 ,255,
  255, 0 ,255,  0 ,255, 0 , 255,255,255, 255,255,255, 255,255,255, 255,255,255, 255,255,255,  0 , 0 ,255,
  255, 0 ,255,  0 ,255, 0 , 255, 0 , 0 ,  0 , 0 ,255,  0 , 0 ,255,  0 , 0 ,255, 255, 0 ,255,  0 , 0 ,255,
  255,255,255,  0 ,255, 0 , 255,255,255, 255,255,255,  0 , 0 ,255, 255,255,255, 255,255,255,  0 , 0 ,255,

  255,255,255, 255,255,255,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255,  0 , 0 , 0 , 255, 0 , 0 , 255,255, 0 ,
  255, 0 ,255, 255, 0 ,255,  0 ,255, 0 ,  0 , 0 ,255,  0 ,255, 0 , 255,255,255,  0 ,255, 0 ,  0 , 0 ,255,
  255,255,255, 255,255,255,  0 , 0 , 0 ,  0 , 0 , 0 , 255, 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255,  0 ,255, 0 ,
  255, 0 ,255,  0 , 0 ,255,  0 ,255, 0 ,  0 , 0 ,255,  0 ,255, 0 , 255,255,255,  0 ,255, 0 ,  0 , 0 , 0 ,
  255,255,255, 255,255,255,  0 , 0 , 0 ,  0 ,255, 0 ,  0 , 0 ,255,  0 , 0 , 0 , 255, 0 , 0 ,  0 ,255, 0 ,

  255,255,255,  0 ,255, 0 , 255,255, 0 ,  0 ,255,255, 255,255, 0 , 255,255,255, 255,255,255,  0 ,255,255,
  255, 0 ,255, 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255, 0 , 0 , 255, 0 , 0 , 255, 0 , 0 ,
  255,255,255, 255,255,255, 255,255, 0 , 255, 0 , 0 , 255, 0 ,255, 255,255, 0 , 255,255, 0 , 255, 0 ,255,
  255, 0 , 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255, 0 , 0 , 255, 0 , 0 , 255, 0 ,255,
  255,255,255, 255, 0 ,255, 255,255, 0 ,  0 ,255,255, 255,255, 0 , 255,255,255, 255, 0 , 0 ,  0 ,255,255,

  255, 0 ,255, 255,255,255,  0 , 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255, 0 ,255,  0 ,255, 0 ,
  255, 0 ,255,  0 ,255, 0 ,  0 , 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255,255,255, 255,255,255, 255, 0 ,255,
  255,255,255,  0 ,255, 0 ,  0 , 0 ,255, 255,255, 0 , 255, 0 , 0 , 255,255,255, 255,255,255, 255, 0 ,255,
  255, 0 ,255,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255,255,255, 255, 0 ,255,
  255, 0 ,255, 255,255,255,  0 ,255, 0 , 255, 0 ,255, 255,255,255, 255, 0 ,255, 255, 0 ,255,  0 ,255, 0 ,

  255,255, 0 ,  0 ,255, 0 , 255,255, 0 ,  0 ,255,255, 255,255,255, 255, 0 ,255, 255, 0 ,255, 255, 0 ,255,
  255, 0 ,255, 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 ,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 ,255,
  255,255, 0 , 255, 0 ,255, 255,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255,255,255,
  255, 0 , 0 , 255,255, 0 , 255, 0 ,255,  0 , 0 ,255,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255,255,255,
  255, 0 , 0 ,  0 ,255,255, 255, 0 ,255, 255,255, 0 ,  0 ,255, 0 , 255,255,255,  0 ,255, 0 , 255, 0 ,255,

  255, 0 ,255, 255, 0 ,255, 255,255,255,  0 ,255,255, 255, 0 , 0 ,  0 ,255,255,  0 ,255, 0 ,  0 , 0 , 0 ,
  255, 0 ,255, 255, 0 ,255,  0 , 0 ,255,  0 ,255, 0 , 255, 0 , 0 ,  0 , 0 ,255, 255, 0 ,255,  0 , 0 , 0 ,
  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 , 0 ,255,  0 , 0 , 0 ,  0 , 0 , 0 ,
  255, 0 ,255,  0 ,255, 0 , 255, 0 , 0 ,  0 ,255, 0 ,  0 , 0 ,255,  0 , 0 ,255,  0 , 0 , 0 ,  0 , 0 , 0 ,
  255, 0 ,255,  0 ,255, 0 , 255,255,255,  0 ,255,255,  0 , 0 ,255,  0 ,255,255,  0 , 0 , 0 , 255,255,255,

  0 , 0 , 0 ,  0 , 0 , 0 , 255, 0 , 0 ,  0 , 0 , 0 ,  0 , 0 ,255,  0 , 0 , 0 ,  0 ,255,255, 255,255,255,
  0 , 0 , 0 ,  0 ,255,255, 255,255,255, 255,255,255, 255,255,255, 255,255,255, 255, 0 , 0 , 255, 0 ,255,
  0 ,255,255, 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255, 0 ,255, 255,255,255, 255,255,255,
  0 , 0 , 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 , 0 , 255, 0 ,255, 255,255, 0 , 255, 0 , 0 ,  0 , 0 ,255,
  0 , 0 , 0 ,  0 ,255,255, 255,255,255, 255,255,255, 255,255,255, 255,255,255, 255, 0 , 0 , 255,255, 0 ,

  255, 0 , 0 ,  0 , 0 , 0 ,  0 ,255, 0 , 255, 0 , 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,
  255, 0 , 0 ,  0 ,255, 0 ,  0 , 0 , 0 , 255, 0 , 0 ,  0 ,255, 0 , 255, 0 ,255, 255,255, 0 , 255,255,255,
  255,255,255,  0 , 0 , 0 ,  0 ,255, 0 , 255, 0 ,255,  0 ,255, 0 , 255,255,255, 255, 0 ,255, 255, 0 ,255,
  255, 0 ,255,  0 ,255, 0 ,  0 ,255, 0 , 255,255, 0 ,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 ,255,
  255, 0 ,255,  0 ,255, 0 , 255,255, 0 , 255, 0 ,255,  0 ,255, 0 , 255, 0 ,255, 255, 0 ,255, 255,255,255,

  255,255,255, 255,255,255,  0 , 0 , 0 ,  0 , 0 , 0 ,  255, 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,  0 , 0 , 0 ,
  255, 0 ,255, 255, 0 ,255,  0 ,255,255, 255,255,255,  255,255,255, 255, 0 ,255, 255, 0 ,255, 255, 0 ,255,
  255,255,255, 255,255,255,  0 ,255, 0 , 255,255, 0 ,  255, 0 , 0 , 255, 0 ,255, 255, 0 ,255, 255, 0 ,255,
  255, 0 , 0 ,  0 , 0 ,255,  0 ,255, 0 ,  0 , 0 ,255,  255, 0 , 0 , 255, 0 ,255, 255, 0 ,255, 255,255,255,
  255, 0 , 0 ,  0 , 0 ,255,  0 ,255, 0 , 255,255,255,   0 ,255,255, 255,255,255,  0 ,255, 0 , 255, 0 ,255,

  0 , 0 , 0 , 255, 0 ,255,  0 , 0 , 0 ,  0 ,255,255,  0 ,255, 0 , 255,255, 0 ,  0 , 0 , 0 , 255,255,255,
  255, 0 ,255, 255, 0 ,255, 255,255,255,  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 ,255, 0 ,
  0 ,255, 0 , 255,255,255,  0 , 0 ,255, 255,255, 0 ,  0 ,255, 0 ,  0 ,255,255, 255,255,255, 255,255,255,
  0 ,255, 0 ,  0 , 0 ,255,  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 ,255, 0 ,  0 , 0 , 0 ,  0 ,255, 0 ,
  255, 0 ,255,  0 ,255,255, 255,255,255,  0 ,255,255,  0 ,255, 0 , 255,255, 0 ,  0 , 0 , 0 , 255,255,255,
};



// bookman_oldstyle chars 0123456789uSvph
PROGMEM prog_uchar big_font[]={
  0x00,0x00,0x10,0x58,0x86,0x72,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x41,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x64,0x84,0x74,0x36
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x67,0x86,0x78,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x47,0x14,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x0f,0x67,0x50,0x30,0x24,0x35,0x67,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1a,0x64,0x86,0x6d,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x6b,0x51,0x4f,0x4f
  ,0x4f,0x51,0x41,0x03,0x00,0x00,0x00,0x00,0x00,0x0a,0x54,0x84,0x81,0x4a,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x5e,0x86,0x72,0x28,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0xa6,0xe6,0xa0,0xc6,0xda,0x42,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x1d,0x52,0x80,0xcc,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0xc9,0xc3,0xa5,0xd2,0xea,0x73,0x02,0x00,0x00,0x00,0x00,0x00,0x2a,0xc1,0xbf
  ,0x9b,0xc7,0xe9,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6c,0xe6,0x2a,0x00,0x00,0x00,0x00,0x00,0x00,0x16,0xe3,0xf6,0xe5,0xe2,0xf3,0xbf,0x13,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x39,0xce,0xd4,0x9c,0xd9,0xcc,0x2d,0x00,0x00,0x00,0x00,0x00,0x82,0xff,0xf9,0xf8,0xf8,0xf5,0xf5,0xa8,0x05,0x00,0x00,0x00,0x00,0x16,0xa5
  ,0xd3,0x95,0xa4,0xe8,0x95,0x0f,0x00,0x00,0x00,0x00,0x00,0x22,0xbb,0xe4,0x9f,0xc6,0xdf,0x4b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xfb,0x58,0x00,0x1b,0xd0,0xd3,0x1d,0x00,0x00,0x00,0x00,0x00,0x4d,0xce,0xd7,0xef,0xc4,0x11,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x0e,0xbc,0x91,0x05,0x00,0x1d,0xca,0xed,0x3b,0x00,0x00,0x00,0x00,0x00,0x8a,0xf3,0x3b,0x00,0x1a,0xd1,0xe1,0x26,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x32,0xe3,0xe1,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xd3,0xb2,0xc0,0xc1,0x91,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0xd4,0xd0,0x21,0x00,0xc7
  ,0xff,0x75,0x00,0x00,0x00,0x00,0x00,0xa0,0xc9,0x71,0x70,0x70,0x83,0xe7,0x49,0x00,0x00,0x00,0x00,0x00,0x75,0xe9,0x2b,0x00,0x00,0x6e,0xf7,0x4e,0x00,0x00,0x00,0x00
  ,0x0a,0xa5,0xf6,0x51,0x00,0x16,0xbf,0xde,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x16,0xd2,0xd5,0x14,0x00,0x00,0x80,0xff,0x62,0x00,0x00,0x00,0x00,0x00,0x09,0x12,0x1c,0xd1,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0xe3,0xb5,0x33,0x00
  ,0x00,0x93,0xfd,0x67,0x00,0x00,0x00,0x00,0x00,0x9a,0xff,0x87,0x00,0x00,0xa3,0xf3,0x46,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0xb4,0xf3,0xdb,0x27,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x2d,0xc2,0x0e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x79,0xfd,0x62,0x00,0x07,0xab,0xe1,0x47,0x00,0x00,0x00,0x00,0x0e,0xc9,0x66,0x00
  ,0x00,0x00,0x71,0xb4,0x05,0x00,0x00,0x00,0x00,0x00,0xaa,0xd3,0x02,0x00,0x00,0x38,0xf3,0x6a,0x00,0x00,0x00,0x00,0x2f,0xe7,0xcf,0x12,0x00,0x00,0x65,0xfe,0x6a,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1d,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3d,0xed,0xb3,0x05,0x00,0x00,0x5c,0xfb,0x95
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0xca,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0xd5,0xff,0x8e,0x00,0x00,0xb4,0xf8,0x5d,0x00,0x00,0x00,0x00,0x00,0x3c
  ,0x9b,0x37,0x00,0x00,0xb4,0xed,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xcd,0xbf,0xe1,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x3b,0xba,0x44,0x5e,0x4f,0x1e,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x11,0xc7,0xe2,0x1c,0x00,0x11,0x13,0x17,0x00,0x00,0x00,0x00,0x00,0x14,0xae,0x31,0x00,0x00,0x20,0xda,0x53,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x9c,0xf6,0x8c,0x25,0x02,0x78,0xea,0x36,0x00,0x00,0x00,0x00,0x49,0xee,0xbe,0x08,0x00,0x00,0x51,0xf8,0x98,0x00,0x00,0x00,0x00,0x00,0x2a,0x00,0x00,0x2a,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0xa7,0x99,0x91,0xb7,0x56,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x31,0x56,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x59,0xf6,0xa2,0x00,0x00,0x00,0x4d,0xf2,0xb0,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0xcb,0xc9
  ,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x58,0xac,0x3f,0x00,0x41,0xee,0xda,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x46,0x79,0xe2,0x73,0x02,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x44,0xe4,0x45,0xa4,0xe4,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x4b,0xe8,0xd5,0xc9,0xea,0xd6,0x52,0x00,0x00,0x00,0x00,0x00,0x2f,0xe6,0xc6,0x56,0xb6
  ,0xd1,0xac,0x44,0x00,0x00,0x00,0x00,0x00,0x03,0x10,0x00,0x00,0x00,0x74,0xd1,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x49,0xe2,0xf1,0xd3,0xab,0xe3,0x60,0x00,0x00,0x00
  ,0x00,0x00,0x3d,0xea,0xd7,0x1a,0x00,0x00,0x79,0xf9,0xac,0x03,0x00,0x00,0x00,0x18,0xbd,0x15,0x00,0xbc,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb3,0x72,0x00
  ,0x00,0x63,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x87,0x9a,0x9a,0x23,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x62,0xf9,0x9c,0x00,0x00,0x00,0x47,0xee,0xb7,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0xcb,0xca,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x19,0xc2,0xf4,0x5c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xc8,0xcc,0xe1,0xdd,0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x1d,0xd2,0x7c,0x00,0xb0,0xe5,0x28,0x00
  ,0x00,0x00,0x00,0x00,0x00,0xa5,0xc2,0x25,0x11,0x45,0xe1,0xe6,0x39,0x00,0x00,0x00,0x00,0x44,0xe7,0xe1,0xda,0x87,0x7c,0xe1,0xeb,0x47,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x14,0xd2,0x8a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7d,0xf5,0xf3,0xf6,0xea,0xa6,0x21,0x00,0x00,0x00,0x00,0x14,0xc0,0xf8,0x91,0x2e,0x54,0xdd,0xf0
  ,0xad,0x05,0x00,0x00,0x00,0x18,0xb9,0x15,0x00,0xb8,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0xc8,0x44,0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x93,0x17,0xb8,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5e,0xf9,0xa0,0x00,0x00,0x00,0x49
  ,0xf0,0xb4,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0xcb,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0xa3,0xf8,0x6b,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x12,0x14,0x25,0xc4,0xe7,0x3a,0x00,0x00,0x00,0x00,0x05,0x96,0xb3,0x00,0x00,0xad,0xe4,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x58,0x3e,0x00,0x00,0x00
  ,0x8d,0xff,0x86,0x00,0x00,0x00,0x00,0x45,0xe6,0xee,0x64,0x00,0x00,0x6b,0xfc,0xa9,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0xf3,0x52,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x59,0xdd,0x98,0x61,0xa9,0xe7,0xfa,0x91,0x02,0x00,0x00,0x00,0x00,0x38,0xc8,0xf4,0xe6,0xd8,0xac,0xea,0xa3,0x00,0x00,0x00,0x00,0x1b,0xb8,0x12,0x00,0xb6
  ,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xba,0xba,0x69,0x4a,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5c,0x5b,0x26,0x49,0x60,0x0b,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x5f,0x55,0x00,0xa8,0x7c,0x7f,0x2b,0x00,0x00,0x00,0x00,0x00,0x4c,0xf1,0xac,0x02,0x00,0x00,0x54,0xf7,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11
  ,0xcb,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0xeb,0x59,0x00,0x2b,0x2f,0x00,0x00,0x00,0x00,0x07,0x71,0x99,0x1e,0x00,0x00,0x73,0xff,0x8e,0x00
  ,0x00,0x00,0x00,0x47,0xf8,0xa7,0x7f,0x81,0xcd,0xe3,0x92,0x73,0x0e,0x00,0x00,0x00,0x05,0x6e,0xa0,0x27,0x00,0x00,0x6b,0xfe,0x9b,0x00,0x00,0x00,0x00,0x36,0xe5,0xdb
  ,0x1f,0x00,0x00,0x36,0xe8,0xc6,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xa5,0xea,0x2e,0x00,0x00,0x00,0x00,0x00,0x00,0x22,0xe2,0xae,0x02,0x00,0x02,0x49,0xda,0xd0
  ,0x12,0x00,0x00,0x00,0x00,0x00,0x13,0x49,0x59,0x29,0x50,0xfa,0x85,0x00,0x00,0x00,0x00,0x23,0xc0,0x1b,0x18,0xc0,0x2e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33
  ,0x99,0xba,0xc4,0xcd,0x8b,0x00,0x00,0x00,0x00,0x00,0x00,0x9c,0xc8,0x19,0x87,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x96,0x00,0x00,0xb2,0x79,0x74,0xaf
  ,0x00,0x00,0x00,0x00,0x00,0x25,0xe1,0xc9,0x0f,0x00,0x00,0x6f,0xff,0x75,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0xcb,0xc9,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x76,0xcc,0x35,0x00,0x00,0xa3,0x7f,0x00,0x00,0x00,0x00,0x26,0xe5,0xfe,0x58,0x00,0x00,0x65,0xfd,0xa0,0x00,0x00,0x00,0x00,0x3e,0xa0,0xa3,0xaa,0xaa,0xd6,0xe3
  ,0xb6,0x98,0x10,0x00,0x00,0x00,0x1e,0xe0,0xfe,0x5f,0x00,0x00,0x76,0xff,0x90,0x00,0x00,0x00,0x00,0x17,0xd2,0xdf,0x1c,0x00,0x00,0x33,0xea,0xbb,0x0a,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x26,0xdf,0xdb,0x1a,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0xf7,0x6e,0x00,0x00,0x00,0x00,0x95,0xda,0x14,0x00,0x00,0x00,0x00,0x4a,0x94,0x29,0x00,0x00
  ,0x81,0xfc,0x50,0x00,0x00,0x00,0x00,0x34,0xc9,0xa6,0xa1,0xc5,0x93,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x72,0xca,0x19,0x00,0x00,0x00,0x00
  ,0x00,0x21,0xbe,0x1e,0x85,0x2c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x80,0x00,0x00,0xae,0x13,0x00,0xb0,0x00,0x00,0x00,0x00,0x00,0x03,0x9e,0xf4,0x39,0x00
  ,0x00,0xb0,0xe8,0x2d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcc,0xc8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xeb,0x81,0x3f,0x40,0x52,0xe1,0x69,0x00,0x00
  ,0x00,0x00,0x22,0xe5,0xb9,0x18,0x00,0x00,0x8b,0xff,0x7b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaf,0xe6,0x1b,0x00,0x00,0x00,0x00,0x00,0x19,0xde,0xbb,0x1a
  ,0x00,0x00,0xb3,0xf9,0x53,0x00,0x00,0x00,0x00,0x00,0x84,0xf9,0x4f,0x00,0x00,0x60,0xfe,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0xf0,0xce,0x13,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x2a,0xec,0xa0,0x00,0x00,0x00,0x0f,0xc7,0xa1,0x03,0x00,0x00,0x00,0x07,0xbb,0xff,0x7a,0x00,0x1c,0xd8,0xc5,0x14,0x00,0x00,0x00,0x00,0x58,0xa1,0x4d
  ,0x1a,0x29,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x73,0x00,0x00,0x00,0x35,0xc6,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x96,0xa9,0x8d,0x00,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x34,0x1c,0x00,0x00,0xb4,0x1e,0x14,0xb3,0x00,0x00,0x00,0x00,0x00,0x00,0x2c,0xd9,0xc9,0x50,0x7f,0xf2,0x6d,0x00,0x00,0x00,0x00,0x00,0x00,0x18
  ,0x76,0x8a,0xec,0xe7,0x85,0x78,0x23,0x00,0x00,0x00,0x00,0x3b,0xeb,0xf6,0xf1,0xf3,0xf0,0xf5,0xfb,0x5c,0x00,0x00,0x00,0x00,0x05,0x95,0xce,0x58,0x42,0x72,0xed,0xc3
  ,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34,0x85,0xdf,0xf2,0x9d,0x45,0x00,0x00,0x00,0x00,0x00,0x81,0xd4,0x5f,0x4d,0x9a,0xf9,0x93,0x09,0x00,0x00,0x00,0x00,0x00
  ,0x22,0xcd,0xd8,0x57,0x5b,0xe0,0xbf,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x62,0xfe,0xc6,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x82,0xf5,0x92,0x4d,0x58,0xb4
  ,0xd7,0x2f,0x00,0x00,0x00,0x00,0x02,0x96,0xfe,0x85,0x51,0xbd,0xe3,0x3e,0x00,0x00,0x00,0x00,0x00,0x66,0x8d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  ,0x00,0xbd,0x48,0x11,0x29,0xa9,0x6d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0xd7,0x4b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4c,0xb8,0x77
  ,0x22,0xb2,0x4c,0x00,0x00,0x00,0x00,0x00,0x00,0x2f,0x9e,0xc2,0xb7,0x5c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x98,0x9f,0x90,0x90,0x9f,0x9d,0x2b,0x00,0x00,0x00
  ,0x00,0x44,0x99,0x8f,0x90,0x91,0x91,0x91,0x91,0x33,0x00,0x00,0x00,0x00,0x00,0x11,0x72,0xb4,0xbd,0xbd,0x81,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0xa4
  ,0x92,0x8f,0xa5,0x59,0x00,0x00,0x00,0x00,0x00,0x0a,0x6c,0xba,0xc1,0xb3,0x63,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x94,0xc0,0xbf,0x8c,0x20,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x30,0xbc,0x78,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x60,0xb1,0xc0,0xbd,0x96,0x2d,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x8a,0xbc
  ,0xbf,0x9a,0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x9b,0x9a,0x90,0x4e,0x00,0x00,0x00,0x00
  ,0x00,0x00,0x00,0x00,0x00,0x61,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};




class font_vspan{
public:
  font_vspan(u8 x,u8 _start,u8 _end):span_start(_start),span_length(_end){}
  u8 x:2;
  u8 span_start:3;
  u8 span_length:3;
};

#define NUM_CHARS (CHARS_PER_LINE*ROWS_OF_CHARS)

u16 span_set_pixels_indices[NUM_CHARS+1];
u16 span_unset_pixels_indices[NUM_CHARS+1];
vector<font_vspan> spans_set;
vector<font_vspan> spans_unset;

void convert_font_to_vertical_spans(){
  int ss=sizeof(font_vspan);
  span_set_pixels_indices[0]=0;
  span_unset_pixels_indices[0]=0;
  for(int i=0;i<NUM_CHARS;i++){
    int font_offset_y=i/CHARS_PER_LINE;
    int font_offset_x=i-font_offset_y*CHARS_PER_LINE;
    int char_address=font_offset_x*3+font_offset_y*FONT_LINE_WIDTH*FONT_CHAR_HEIGHT;
    for(int x=0;x<FONT_CHAR_WIDTH;x++){
      int op=debugfont[char_address+x];  // get start pixel for first span
      int span_start_y=0;
      for(int y=1;y<=FONT_CHAR_HEIGHT;y++){
        int p=debugfont[char_address+x+y*FONT_LINE_WIDTH];
        if (p!=op||y==FONT_CHAR_HEIGHT){
          if (op){
            spans_set.push_back(font_vspan(x,span_start_y,y-span_start_y));
          }else{
            spans_unset.push_back(font_vspan(x,span_start_y,y-span_start_y));
          }
          op=p;
          span_start_y=y;
        }
      }
    }
    span_set_pixels_indices[i+1]=spans_set.size();
    span_unset_pixels_indices[i+1]=spans_unset.size();
  }
}


//u8 debug_font_data_ST7735[FONT_CHAR_WIDTH*FONT_CHAR_HEIGHT*CHARS_PER_LINE*ROWS_OF_CHARS*2];

int bit_pos=0;
bool add_bit(u8 &byte,int bit){
  if (bit){
    bit=1;
  }
  byte|=bit<<bit_pos++;
  if (bit_pos>=8){
    bit_pos=0;
    return true;
  }
  return false;
}

#define CHAR_IMAGE_WIDTH 13
#define CHAR_PLOT_WIDTH 10
#define CHAR_PLOT_HEIGHT 13
#define CHAR_IMAGE_STRIDE 182


void convert_to_bitmaps(){
  FILE*fil=fopen("c:\\fff.txt","wb");
  u8 byte=0;
  for(int i=0;i<NUM_CHARS;i++){
    int font_offset_y=i/CHARS_PER_LINE;
    int font_offset_x=i-font_offset_y*CHARS_PER_LINE;
    int char_address=font_offset_x*3+font_offset_y*FONT_LINE_WIDTH*FONT_CHAR_HEIGHT;
    for(int y=0;y<FONT_CHAR_HEIGHT;y++){
      for(int x=0;x<FONT_CHAR_WIDTH;x++){
        int p=debugfont[char_address+x+y*FONT_LINE_WIDTH];
        if (add_bit(byte,p)){
          fprintf(fil,"%d,",byte);
          byte=0;
        }
      }
    }
  }
  fprintf(fil,"%d};\n",byte);
  fclose(fil);

  fil=fopen("c:\\fffBIG.txt","wb");
  for(int i=0;i<sizeof(big_font);i+=2){
    u32 val0=(u32)((float)big_font[i]*1.25f);
    u32 val1=(u32)((float)big_font[i+1]*1.25f);
    if (val0>255){
      val0=255;
    }
    if (val1>255){
      val1=255;
    }

    u8 val=(big_font[i+1]&0xF0)|(big_font[i]>>4);
    fprintf(fil,"0x%x,",val);
  }
  fprintf(fil,"\n");
  fclose(fil);

//  fil=fopen("c:\\fffBIG_II.txt","wb");
//  bool toggle=false;
//  u8 val=0;
//  for(int i=0;i<14;i++){
//    for(u8 y=0;y<CHAR_PLOT_HEIGHT;y++){
//      for(u8 x=0;x<char_plot_width;x++){
//        u32 offset=xo+x+y*CHAR_IMAGE_STRIDE;
//        u32 c=big_font[offset];
//        toggle^=true;
//        if (toggle){
//          val=c>>4;
//        }else{
//          val|=c&0xF0;
//          fprintf(fil,"0x%x,",val);
//        }
//      }
//    }
//  }
//  fclose(fil);
}
#endif



