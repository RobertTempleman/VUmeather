#include <Arduino.h>
#include "metaldt__codeblocks.ino.h"
#include <EEPROM.h>
#include "GBAtext.h"
#include "RTTcolours.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <SPI.h>
#include "../gfx_code/Adafruit_ST7735/Adafruit_ST7735.h"
#include "metaldt_UI_AVR.h"
#include "GBAtext.h"
#include "preprocessed_data_from_LTSPICE_METALDT_simulation.h"


Adafruit_ST7735 tft;
// hardware SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK).
// pinout on 128x160   left    VCC   GND   CS    RESET A0    SDA   SCK   LED
//                              |     |     |     |     |     |     |     |
//                     arduino  5v    gnd   D10   RST   D9    D11   D13   5v

void draw_graph();

extern u16 d_pins_addr[14];
extern u8 d_pins_mask[14];

#define PIN_TEST_CAPCITOR A1
#define PIN_COIL_ENERGIZE A2
#define PIN_COIL_DEENERGIZE A3
#define PIN_ENABLE_74HC244 A0
#define PIN_BUTTHOLMES A4

#define PIN_MUXER_ANALOG A0

#define PIN_MUXER_ADDRESS0 2
#define PIN_MUXER_ADDRESS1 3
#define PIN_MUXER_ADDRESS2 4
#define PIN_MUXER_ADDRESS3 5
#define PIN_MUXER_ENABLE 6

void setup(){
  tft.initR();   // initialize a ST7735S chip for 128x160 display
  tft.fillScreen(ST7735_BLACK);

  draw_graph();
//  for(u8 i=0;i<8;i++){
////    pinMode(i,INPUT);
//    pinMode(i,INPUT_PULLUP);
//  }
//  pinMode(8,OUTPUT);
//  pinMode(PIN_ENABLE_74HC244,OUTPUT);
//  pinMode(PIN_TEST_CAPCITOR,OUTPUT);
//  pinMode(PIN_COIL_ENERGIZE,OUTPUT);
//  pinMode(PIN_COIL_DEENERGIZE,OUTPUT);
//  digitalWrite(PIN_ENABLE_74HC244,HIGH); // disable driving of serial rx & tx pins by 74244 buffer
//	digitalWrite(PIN_COIL_ENERGIZE,LOW);
//	digitalWrite(PIN_COIL_DEENERGIZE,LOW);

	pinMode(PIN_MUXER_ADDRESS0 , OUTPUT);
	pinMode(PIN_MUXER_ADDRESS1 , OUTPUT);
	pinMode(PIN_MUXER_ADDRESS2 , OUTPUT);
	pinMode(PIN_MUXER_ADDRESS3 , OUTPUT);
	pinMode(PIN_MUXER_ENABLE   , OUTPUT);

  for(u8 i=0;i<14;i++){
    d_pins_addr[i]=(u16)portInputRegister(digitalPinToPort(i));
    d_pins_mask[i]=digitalPinToBitMask(i);
  }
}


int read_multiplexer_analog_channel(u8 channel){
	digitalWrite(PIN_MUXER_ADDRESS0 ,channel&1);
	digitalWrite(PIN_MUXER_ADDRESS1 ,channel&2);
	digitalWrite(PIN_MUXER_ADDRESS2 ,channel&4);
	digitalWrite(PIN_MUXER_ADDRESS3 ,channel&8);
	digitalWrite(PIN_MUXER_ENABLE   ,LOW);
	return analogRead(PIN_MUXER_ANALOG);

}


int RTTdigitalRead(uint8_t pin){
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == NOT_A_PIN) return LOW;

	// If the pin that support PWM output, we need to turn it off
	// before getting a digital reading.
//	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	if (*portInputRegister(port) & bit) return HIGH;
	return LOW;
}

#define COL_AXIS      goldenrod_cr
#define COL_AXIS_KEY  grey60_cr
#define COL_AXIS_KEY2 yellow3_cr
#define COL_AXIS_KEY3 green2_cr


void RTT_digitalWrite(uint8_t pin, uint8_t val){
//	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

//	if (port == NOT_A_PIN) return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
//	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
}


void RTT_digitalWrite_noclis(uint8_t pin, uint8_t val){
//	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

//	if (port == NOT_A_PIN) return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
//	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	out = portOutputRegister(port);

//	uint8_t oldSREG = SREG;
//	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

//	SREG = oldSREG;
}



void do_bit(u8 &output,u8 bit_mask,u8 bit){
	if (bit==LOW) {
		output&=~bit_mask;
	} else {
		output|=bit_mask;
	}
}


void program_and_select_correct_output_muxer(u8 muxed_input){
}


extern s32 num_speed_tests;



void loop(){
  buttholmes_anal_value=analogRead(PIN_BUTTHOLMES);
	volume_main=read_multiplexer_analog_channel(0);
  draw_graph();
}


#define DIGITAL_POTS_ARE_MCP41010 0
#define DIGITAL_POTS_ARE_MCP41HV51 1


#if DIGITAL_POTS_ARE_MCP41010==1
  #define cmd_byte2 B00010001  // Command byte
  #define initial_value 100    // Setting up the initial value
#endif

#if DIGITAL_POTS_ARE_MCP41HV51==1
  #define cmd_byte2 B00000000  // Command byte
  #define initial_value 100    // Setting up the initial value
#endif

inline void spiwrite(uint8_t c){
  SPDR = c;
  while(!(SPSR & _BV(SPIF)));
}


void RTT_wang_it_down_the_hardware_SPI(u8 potentiometer, u8 data_byte){
  program_and_select_correct_output_muxer(potentiometer);
  spiwrite(cmd_byte2);
  spiwrite(data_byte);
}


void RTT_hardware_digi_pot_spi_out(byte data_byte){
  spiwrite(cmd_byte2);
  spiwrite(data_byte);
}

