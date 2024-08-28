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
extern bool display_pins;

extern u8 tx_is;
extern u8 rx_is;

extern u8 port_d_val;

#define PIN_TEST_CAPCITOR A1
#define PIN_COIL_ENERGIZE A2
#define PIN_COIL_DEENERGIZE A3
#define PIN_ENABLE_74HC244 A0
#define PIN_BUTTHOLMES A4

void setup(){
  tft.initR();   // initialize a ST7735S chip for 128x160 display
  tft.fillScreen(ST7735_BLACK);

  draw_graph();
  for(u8 i=0;i<8;i++){
//    pinMode(i,INPUT);
    pinMode(i,INPUT_PULLUP);
  }
  pinMode(8,OUTPUT);
  pinMode(PIN_ENABLE_74HC244,OUTPUT);
  pinMode(PIN_TEST_CAPCITOR,OUTPUT);
  pinMode(PIN_COIL_ENERGIZE,OUTPUT);
  pinMode(PIN_COIL_DEENERGIZE,OUTPUT);
  digitalWrite(PIN_ENABLE_74HC244,HIGH); // disable driving of serial rx & tx pins by 74244 buffer
  digitalWrite(PIN_COIL_ENERGIZE,LOW);
  digitalWrite(PIN_COIL_DEENERGIZE,LOW);

  for(u8 i=0;i<14;i++){
    d_pins_addr[i]=(u16)portInputRegister(digitalPinToPort(i));
    d_pins_mask[i]=digitalPinToBitMask(i);
  }
  display_pins=true;
}


int RTTdigitalRead(uint8_t pin)
{
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


void RTT_digitalWrite(uint8_t pin, uint8_t val)
{
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


void RTT_digitalWrite_noclis(uint8_t pin, uint8_t val)
{
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
extern u8 speed_test_countdown;
extern bool do_speed_test;

extern u8 adc0820_readings[NUM_SAMPLES_TO_TAKE];


// ADC0820 in standalone mode
// so need to wait 800ns after !WR is pulled high before conversion is ready

#define NOP\
  asm volatile("nop\n\t"::);

#if 0
// 800ns=12.8 16Mhz cycles
#define ONE_FULL_READ\
  PORTB=0;\
  NOP;\
  temp=*d0_in;\
  PORTB=1;\
  *(pds++)=temp;\
  NOP;NOP;NOP;NOP;\
  NOP;NOP;NOP;NOP;\
  NOP;NOP;NOP;NOP;\
  NOP;\
  NOP;\
  NOP;
#else
#define ONE_FULL_READ\
  PORTB=0;\
  NOP;\
  temp=*d0_in;\
  PORTB=1;\
  *(pds++)=temp;\
  NOP;NOP;NOP;NOP;\
  NOP;NOP;NOP;NOP;\
  NOP;NOP;NOP;NOP;\
  NOP;\
  NOP;

#endif
#define NUM_PORTD_READ_TESTS (1000000/40)


#define WAIT_ONE_TICK for(u8 i=0;i<12;i++){NOP;};

// switch coil driving mosfet on
inline void energize_coil(){
  RTT_digitalWrite_noclis(PIN_COIL_ENERGIZE,HIGH);  // energize coil for real
  WAIT_ONE_TICK;
  RTT_digitalWrite_noclis(PIN_COIL_ENERGIZE,LOW);  // energize coil for real
}

// switch coil driving mosfet off
inline void deenergize_coil(){
  RTT_digitalWrite_noclis(PIN_COIL_DEENERGIZE,HIGH);  // energize coil for real
  WAIT_ONE_TICK;
  RTT_digitalWrite_noclis(PIN_COIL_DEENERGIZE,LOW);  // energize coil for real
}

// coil enegize delay
inline void RTT_delay(u8 wait){
  for(u8 i=0;i<wait;i++){
    WAIT_ONE_TICK;
  }
}


void loop(){
  buttholmes_anal_value=analogRead(PIN_BUTTHOLMES);
  if (do_speed_test){
    delay(1);
    digitalWrite(PIN_ENABLE_74HC244,LOW);  // enable buffer to drive all D0-D7 pins
    uint8_t oldSREG = SREG;
    uint8_t d8_bit = digitalPinToBitMask(8);
    uint8_t d8_port = digitalPinToPort(8);
    volatile uint8_t *d8_out;
    d8_out = portOutputRegister(d8_port);

    uint8_t d0_bit = digitalPinToBitMask(0);
    uint8_t d0_port = digitalPinToPort(0);
    //	volatile uint8_t *d0_out;
    //	d0_out = portOutputRegister(d0_port);

    volatile uint8_t *d0_in;
    d0_in = portInputRegister(d0_port);
    do_speed_test=false;
    num_speed_tests++;
    u8 temp;
    u8* pds=adc0820_readings;
    cli();
    energize_coil();
    RTT_delay(coil_energise_delay_microseconds);
    deenergize_coil();
    RTT_delay(sampling_delay_microseconds);
    RTT_digitalWrite_noclis(PIN_TEST_CAPCITOR,LOW);  // stop charging capacitor
    PORTB=0;
    NOP;
    *(pds)=*d0_in;
    NOP;
    PORTB=1;
    NOP;NOP;NOP;NOP;
    NOP;NOP;NOP;NOP;
    NOP;NOP;NOP;NOP;
    NOP;NOP;NOP;NOP;
    NOP;NOP;NOP;NOP;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;ONE_FULL_READ;
    port_d_val=*(u8*)d0_in;

    SREG = oldSREG;
    digitalWrite(PIN_ENABLE_74HC244,HIGH);  // disable driving of all D0-D7 pins to re-enable serial operations
  }
  RTT_digitalWrite_noclis(PIN_TEST_CAPCITOR,HIGH); // start charging capacitor
  draw_graph();

  static bool debounce_mode_change_button=false;
  if (input_potentiometer_readings[INPUT_POT_NUMBER_AUX_CONTROL_MODESELECT]==LOW){
    if (debounce_mode_change_button){
//      need_to_cycle_mode=true;
    }
    debounce_mode_change_button=false;
  }else{
    debounce_mode_change_button=true;
  }

  static bool debounce_toggle_func_button=false;
  if (input_potentiometer_readings[INPUT_POT_NUMBER_AUX_CONTROL_TOGGLEFUNCS]==LOW){
    if (debounce_toggle_func_button){
      need_to_toggle_func=true;
    }
    debounce_toggle_func_button=false;
  }else{
    debounce_toggle_func_button=true;
  }
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

