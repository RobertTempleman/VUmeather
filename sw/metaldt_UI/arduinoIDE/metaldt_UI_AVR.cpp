// metaldt_UI.cpp : Defines the entry point for the application.
//

#include <stdio.h>
#include <SPI.h>
#include "../gfx_code/Adafruit_ST7735/Adafruit_ST7735.h"
#include "metaldt__codeblocks.ino.h"
#include "metaldt_UI_AVR.h"
#include "GBAtext.h"
#include "RTTcolours.h"
#include <avr/pgmspace.h>
#include <EEPROM.h>

extern Adafruit_ST7735 tft;


#define MAX_LOADSTRING 100


COLORREF gcol;
COLORREF alt_gcol;

//inline u16 tft_col(){
//  u8 r=(u8)gcol;
//  u8 g=(u8)(gcol>>8);
//  u8 b=(u8)(gcol>>16);
//  u16 col2=tft.Color565(r,g,b);
//}

inline void p(u8 x, u8 y){
  tft.drawPixel(x,y,gcol);
}


void two_pixel_vline(u8 x, u8 y,COLORREF gcol2){
  tft.drawPixel(x,y,gcol);
//  gcol=gcol2;
  tft.drawPixel(x,y,gcol2);
//  u16 col1=tft_col();
//  gcol=gcol2;
//  u16 col2=tft_col();
//  tft.draw_colored_two_pixel_vline(x,y,col1,col2);
}

inline void hline(u8 x,u8 y,u8 w){
  tft.drawFastHLine(x,y,w+1,gcol);
//  metaldt__processing_loop();
//  for(u8 i=x;i<=x+w;i++){
//    p(i,y);
//  }
}



void vline_with_masked_text(u8 x,u8 y,u8 h,COLORREF new_col){

}

void vline(u8 x,u8 y,u8 h){
  tft.drawFastVLine(x,y-h,h+1,gcol);
  metaldt__processing_loop();
//  for(u8 i=y-h;i<=y;i++){
//    p(x,i);
//  }
}


void vline_2p(u8 x, u8 y,COLORREF gcol2)
{
  u16 col1=gcol;
//  gcol=gcol2;
  tft.draw_colored_2_pixel_vline(x,y,col1,gcol2);
}

void rectfill(u8 x,u8 y,u8 w,u8 h){
  tft.fillRect(x,y-h,w,h+1,gcol);
//  for(u8 i=x;i<=x+w;i++){
//    vline(i,y,h);
//  }
}

void rect(u8 x,u8 y,u8 w,u8 h){
  hline(x  ,y  ,w);
  hline(x  ,y+h,w);
  vline(x  ,y+h-1,h-2);
  vline(x+w,y+h-1,h-2);
}

void plot_char_3x5(u8 xp,u8 yp,u16 offset,COLORREF col){
//  u8 r=(u8)col;
//  u8 g=(u8)(col>>8);
//  u8 b=(u8)(col>>16);
//  u16 colu16=tft.Color565(r,g,b);

//  metaldt__processing_loop();
  tft.draw_coloured_char(xp,yp,3,5,offset,col);
}
//void plot_char_3x5(u8 xp,u8 yp,u8*cols,COLORREF col){
//  for(int x=0;x<3;x++){
//    for(int y=0;y<5;y++){
//      if (cols[x+y*3]){
//        gcol=col;
//      }else{
//        gcol=0;
//      }
//      p(x+xp,y+yp);
//    }
//  }
//}
#include "metaldt__code.cpp"



