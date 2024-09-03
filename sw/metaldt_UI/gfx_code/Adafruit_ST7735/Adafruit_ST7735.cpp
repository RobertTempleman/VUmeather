/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_ST7735.h"
#include <limits.h>
#include "pins_arduino.h"
#include "wiring_private.h"

#define CS_PIN 10
#define RS_PIN 9


// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80
static const uint8_t PROGMEM
  Bcmd[] = {                  // Initialization commands for 7735B screens
    18,                       // 18 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
      50,                     //     50 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
      255,                    //     255 = 500 ms delay
    ST7735_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
      0x05,                   //     16-bit color
      10,                     //     10 ms delay
    ST7735_FRMCTR1, 3+DELAY,  //  4: Frame rate control, 3 args + delay:
      0x00,                   //     fastest refresh
      0x06,                   //     6 lines front porch
      0x03,                   //     3 lines back porch
      10,                     //     10 ms delay
    ST7735_MADCTL , 1      ,  //  5: Memory access ctrl (directions), 1 arg:
      0x08,                   //     Row addr/col addr, bottom to top refresh
    ST7735_DISSET5, 2      ,  //  6: Display settings #5, 2 args, no delay:
      0x15,                   //     1 clk cycle nonoverlap, 2 cycle gate
                              //     rise, 3 cycle osc equalize
      0x02,                   //     Fix on VTL
    ST7735_INVCTR , 1      ,  //  7: Display inversion control, 1 arg:
      0x0,                    //     Line inversion
    ST7735_PWCTR1 , 2+DELAY,  //  8: Power control, 2 args + delay:
      0x02,                   //     GVDD = 4.7V
      0x70,                   //     1.0uA
      10,                     //     10 ms delay
    ST7735_PWCTR2 , 1      ,  //  9: Power control, 1 arg, no delay:
      0x05,                   //     VGH = 14.7V, VGL = -7.35V
    ST7735_PWCTR3 , 2      ,  // 10: Power control, 2 args, no delay:
      0x01,                   //     Opamp current small
      0x02,                   //     Boost frequency
    ST7735_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
      0x3C,                   //     VCOMH = 4V
      0x38,                   //     VCOML = -1.1V
      10,                     //     10 ms delay
    ST7735_PWCTR6 , 2      ,  // 12: Power control, 2 args, no delay:
      0x11, 0x15,
    ST7735_GMCTRP1,16      ,  // 13: Magical unicorn dust, 16 args, no delay:
      0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
      0x21, 0x1B, 0x13, 0x19, //      these config values represent)
      0x17, 0x15, 0x1E, 0x2B,
      0x04, 0x05, 0x02, 0x0E,
    ST7735_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
      0x0B, 0x14, 0x08, 0x1E, //     (ditto)
      0x22, 0x1D, 0x18, 0x1E,
      0x1B, 0x1A, 0x24, 0x2B,
      0x06, 0x06, 0x02, 0x0F,
      10,                     //     10 ms delay
    ST7735_CASET  , 4      ,  // 15: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 2
      0x00, 0x81,             //     XEND = 129
    ST7735_RASET  , 4      ,  // 16: Row addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 1
      0x00, 0x81,             //     XEND = 160
    ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
      10 },                  //     255 = 500 ms delay

  Rcmd1[] = {                 // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      0xC8,                   //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

  Rcmd2green[] = {            // Init for 7735R, part 2 (green tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 0
      0x00, 0x7F+0x02,        //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x01,             //     XSTART = 0
      0x00, 0x9F+0x01 },      //     XEND = 159
  Rcmd2red[] = {              // Init for 7735R, part 2 (red tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F },           //     XEND = 159

  Rcmd2green144[] = {              // Init for 7735R, part 2 (green 1.44 tab)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127

  Rcmd3[] = {                 // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      10 };                  //     100 ms delay


// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void Adafruit_ST7735::commandList(const uint8_t *addr) {
  uint8_t  numCommands, numArgs;
  uint16_t ms;

  numCommands = pgm_read_byte(addr++);   // Number of commands to follow
  while(numCommands--) {                 // For each command...
    writecommand(pgm_read_byte(addr++)); //   Read, issue command
    numArgs  = pgm_read_byte(addr++);    //   Number of args to follow
    ms       = numArgs & DELAY;          //   If hibit set, delay follows args
    numArgs &= ~DELAY;                   //   Mask out delay bit
    while(numArgs--) {                   //   For each argument...
      writedata(pgm_read_byte(addr++));  //     Read, issue argument
    }

    if(ms) {
      ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
      if(ms == 255) ms = 500;     // If 255, delay for 500 ms
      delay(ms);
    }
  }
}







void settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode){
  // Clock settings are defined as follows. Note that this shows SPI2X
  // inverted, so the bits form increasing numbers. Also note that
  // fosc/64 appears twice
  // SPR1 SPR0 ~SPI2X Freq
  //   0    0     0   fosc/2
  //   0    0     1   fosc/4
  //   0    1     0   fosc/8
  //   0    1     1   fosc/16
  //   1    0     0   fosc/32
  //   1    0     1   fosc/64
  //   1    1     0   fosc/64
  //   1    1     1   fosc/128

  // We find the fastest clock that is less than or equal to the
  // given clock rate. The clock divider that results in clock_setting
  // is 2 ^^ (clock_div + 1). If nothing is slow enough, we'll use the
  // slowest (128 == 2 ^^ 7, so clock_div = 6).
  uint8_t clockDiv;

  // When the clock is known at compiletime, use this if-then-else
  // cascade, which the compiler knows how to completely optimize
  // away. When clock is not known, use a loop instead, which generates
  // shorter code.
  clockDiv = 0;

  // Invert the SPI2X bit
  clockDiv ^= 0x1;

  // Pack into the SPISettings class
  SPCR = _BV(SPE) | _BV(MSTR) | ((bitOrder == LSBFIRST) ? _BV(DORD) : 0) |
    (dataMode & SPI_MODE_MASK) | ((clockDiv >> 1) & SPI_CLOCK_MASK);
  SPSR = 1;//clockDiv & SPI_2XCLOCK_MASK;
}





// Initialization code common to both 'B' and 'R' type displays
void Adafruit_ST7735::commonInit(const uint8_t *cmdList) {
  //  colstart  = rowstart = 0; // May be overridden in init func

  pinMode(RS_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  csport    = portOutputRegister(digitalPinToPort(CS_PIN));
  rsport    = portOutputRegister(digitalPinToPort(RS_PIN));
  cspinmask = digitalPinToBitMask(CS_PIN);
  rspinmask = digitalPinToBitMask(RS_PIN);


  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4); // 4 MHz (half speed)
  //Due defaults to 4mHz (clock divider setting of 21)
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  //    settings(16000000,MSBFIRST,SPI_MODE0);

  // toggle RST low to reset; CS low so it'll listen to us
  *csport &= ~cspinmask;

  if(cmdList) commandList(cmdList);
}


// Initialization for ST7735R screens (green or red tabs)
void Adafruit_ST7735::initR() {
  commonInit(Rcmd1);
  commandList(Rcmd2red);
  commandList(Rcmd3);
  writecommand(ST7735_MADCTL);
  writedata(0xC0);
}


void metaldt__processing_loop(uint8_t only_do_radio);


//#define __SFR_OFFSET 0x20
//extern uint8_t SIM_MEM[];
//#define _MMIO_BYTE(mem_addr) SIM_MEM[mem_addr]
//#define _SFR_IO8(io_addr) _MMIO_BYTE(__SFR_OFFSET +(io_addr))
//#define SPSR _SFR_IO8(0x2D)
//
//
//1. _MMIO_BYTE(0x20 +(0x2D))
//2. SIM_MEM[0x4D]

//u16 max_bungs=0;

//void SPIWRITE(u8 c){
//  SPDR = c;
//  u8 bungs=0;
//  while(!(*(u8*)0x4D & 0x80)){
//    bungs++;
//  }
//  if (bungs>max_bungs){
//    max_bungs=bungs;
//  }
//}
// *(u8*)0x4E=(c);\

//#define SPIWRITE(c) *((u8*)0x4E) = (c);while(!(*(u8*)0x4D&0x80));

//#define SPIWRITE(c)\
//  SPDR = c;\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");\
//  asm volatile("nop");


#define SPIWRITE(c)\
 SPDR = c;\
 while(!(*(u8*)0x4D&0x80));

//#define SPIWRITE(c)\
//  SPDR = c;\
//  while(!(SPSR & _BV(SPIF)));


inline void Adafruit_ST7735::spiwrite(uint8_t c) {
  SPDR = c;
  while(!(SPSR & _BV(SPIF)));
}


inline void Adafruit_ST7735::writecommand(uint8_t c) {
  *rsport &= ~rspinmask;
  *csport &= ~cspinmask;
  spiwrite(c);
  *csport |= cspinmask;
}


void Adafruit_ST7735::writedata(uint8_t c) {
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  spiwrite(c);
  *csport |= cspinmask;
}

inline void Adafruit_ST7735::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

  *rsport &= ~rspinmask;
  SPIWRITE(ST7735_CASET);

  *rsport |=  rspinmask;
  SPIWRITE(0x00);
  SPIWRITE(x0);
  SPIWRITE(0x00);
  SPIWRITE(x1);

  *rsport &= ~rspinmask;
  SPIWRITE(ST7735_RASET);

  *rsport |=  rspinmask;
  SPIWRITE(0x00);
  SPIWRITE(y0);
  SPIWRITE(0x00);
  SPIWRITE(y1);

  *rsport &= ~rspinmask;
  SPIWRITE(ST7735_RAMWR);
}



void Adafruit_ST7735::drawPixel(uint8_t x, uint8_t y, uint16_t color)
{
  *csport &= ~cspinmask;
  setAddrWindow(x,y,x,y);
  *rsport |=  rspinmask;
  SPIWRITE(color >> 8);
  SPIWRITE(color);
  *csport |= cspinmask;
}



void Adafruit_ST7735::drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color)
{
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x, y+h-1);
  uint8_t hi = color >> 8, lo = color;
  *rsport |=  rspinmask;
  while (h--) {
    SPIWRITE(hi);
    SPIWRITE(lo);
  }
  *csport |= cspinmask;
}



void Adafruit_ST7735::draw_colored_2_pixel_vline(uint8_t x, uint8_t y, uint16_t color1, uint16_t color2)
{
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x, y+1);
  *rsport |=  rspinmask;
  SPIWRITE(color1>>8);
  SPIWRITE((uint8_t)color1);
  SPIWRITE(color2>>8);
  SPIWRITE((uint8_t)color2);
  *csport |= cspinmask;
}



void Adafruit_ST7735::drawFastHLine(int16_t x, int16_t y, int16_t w,uint16_t color) {
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x+w-1, y);
  uint8_t hi = color >> 8, lo = color;
  *rsport |=  rspinmask;
  while (w--) {
    SPIWRITE(hi);
    SPIWRITE(lo);
  }
  *csport |= cspinmask;
}

uint8_t pgm_read_byte_near_font_compressed(uint16_t pos);


void Adafruit_ST7735::draw_coloured_char(int16_t x, int16_t y,int16_t w, int16_t h, uint16_t offset,uint16_t colour) {
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x+w-1, y+h-1);
  *rsport |=  rspinmask;
  uint8_t n=w*h;
  uint8_t lo=colour;
  uint8_t hi=colour>>8;
  while(n--){
    if (pgm_read_byte_near_font_compressed(offset++)){
      SPIWRITE(hi);
      SPIWRITE(lo);
    }else{
      SPIWRITE(0);
      SPIWRITE(0);
    }
  }
  *csport |= cspinmask;
}



void Adafruit_ST7735::fillScreen(uint16_t color) {
  fillRect(0, 0,  DISPLAY_WIDTH, DISPLAY_HEIGHT, color);
}
//
//void Adafruit_ST7735::rectfill_down_screen(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color){
//  *csport &= ~cspinmask;
//  setAddrWindow(x, y, x+w-1, y+h-1);
//  uint8_t hi = color >> 8, lo = color;
//  *rsport |=  rspinmask;
//  uint16_t q=w*h;
//  while(q--){
//    SPIWRITE(hi);
//    SPIWRITE(lo);
//  }
//  *csport |= cspinmask;
//}
//
//
//void Adafruit_ST7735::fillRect_up_screen(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color){
//  *csport &= ~cspinmask;
//  setAddrWindow(x, y, x+w-1, y+h-1);
//  uint8_t hi = color >> 8, lo = color;
//  *rsport |=  rspinmask;
//  uint16_t q=w*h;
//  while(q--){
//    SPIWRITE(hi);
//    SPIWRITE(lo);
//  }
//  *csport |= cspinmask;
//}
//
//
void Adafruit_ST7735::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color){
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x+w-1, y+h-1);
  uint8_t hi = color >> 8, lo = color;
  *rsport |=  rspinmask;
  uint16_t q=w*h;
  while(q--){
    SPIWRITE(hi);
    SPIWRITE(lo);
  }
  *csport |= cspinmask;
}


void Adafruit_ST7735::fillRect_8(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color){
  *csport &= ~cspinmask;
  setAddrWindow(x, y, x+w-1, y+h-1);
  uint8_t hi = color >> 8, lo = color;
  *rsport |=  rspinmask;
  uint16_t q=(w*h)>>1;
  uint16_t a=0;
  while(q--){
    SPIWRITE(hi);SPIWRITE(lo);
    a++;
    a++;
    //    asm volatile("nop");
//    asm volatile("nop");
//    asm volatile("nop");
//    asm volatile("nop");
    SPIWRITE(hi);SPIWRITE(lo);
  }
  *csport |= cspinmask;
}

//void Adafruit_ST7735::fillRect_8(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color){
//  *csport &= ~cspinmask;
//  setAddrWindow(x, y, x+w-1, y+h-1);
//  uint8_t hi = color >> 8, lo = color;
//  *rsport |=  rspinmask;
//  uint16_t q=(w*h)>>3;
//  while(q--){
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//    SPIWRITE(hi);SPIWRITE(lo);
//  }
//  *csport |= cspinmask;
//}


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Adafruit_ST7735::Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}
