#include "resource.h"
#include <assert.h>
#include <vector>
using std::vector;

#define PROGMEM

#define HIGH 0x1
#define LOW  0x0

typedef unsigned char prog_uchar;
typedef u32 prog_uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;


void pc(u8 x,u8 y,DWORD col);
u8 pgm_read_byte_near(const u8 *add);
u32 pgm_read_dword_near(const u32 *add);
float pgm_read_float_near(const u8* f);
void plot_char_3x5(u8 xp,u8 yp,u16 offset,COLORREF col);
void RTT_wang_it_down_the_hardware_SPI(u8 potentiometer, u8 data_byte);

void p(u8 x, u8 y);
u16 analogRead(u8 p);
u16 digitalRead(u8 p);
u16 analogWrite(u8 p);
u16 digitalWrite(u8,u8);
void pinMode(u8,u8);

class preprocessed_pixels{
public:
  preprocessed_pixels(u8 _y,COLORREF _gcol):y(_y),gcol(_gcol){};
  preprocessed_pixels(){};

  bool operator < (const preprocessed_pixels& v){
    const u8 r1=(u8)gcol;
    const u8 g1=(u8)(gcol>>8);
    const u8 b1=(u8)(gcol>>16);
    const u8 r2=(u8)v.gcol;
    const u8 g2=(u8)(v.gcol>>8);
    const u8 b2=(u8)(v.gcol>>16);
    const u8 max1=r1|g1|b1;
    const u8 max2=r2|g2|b2;
    if (y==v.y){
      if (max1>max2){
        return true;
      }
    }
    if (y<v.y){
      return true;
    }
    return false;
  }
  bool operator==(const preprocessed_pixels& v){
    if (y==v.y){
      return true;
    }
    return false;
  }
  u8 y;
  COLORREF gcol;
};

extern vector<preprocessed_pixels> prepro_pixels[DISPLAY_WIDTH];
