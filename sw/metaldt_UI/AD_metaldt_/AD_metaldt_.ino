#include <Arduino.h>
/*
  Arduino TFT text example

  This example demonstrates how to draw text on the
  TFT with an Arduino. The Arduino reads the value
  of an analog sensor attached to pin A0, and writes
  the value to the LCD screen, updating every
  quarter second.

  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/TFTDisplayText

 */

//#include <UTFT.h>  // Arduino LCD library
#include <SPI.h>
#include "libraries/Adafruit-GFX/Adafruit_GFX.h"
#include "libraries/Adafruit_ST7735/Adafruit_ST7735.h"
#include "AD_metaldt_UI.h"
#include "AD_GBAtext.h"



void TFT_test(){

}

// char array to print to the screen
char sensorPrintout[4];


const u8 metaldt__tube_digital_input_pins[NUM_SBM20S]={3,4,5,6};


#define HANDLE_INTERRUPT_CONDITION_CLEARING 1
void interrupt(){
  detachInterrupt(0);
#if HANDLE_INTERRUPT_CONDITION_CLEARING==1
  for(u8 i=0;i<NUM_SBM20S;i++){
    u8 pin=metaldt__tube_digital_input_pins[i];
    if (digitalRead(pin)==LOW){
      counts[i]++;
      while(digitalRead(pin)==0){}
    }
  }
  #endif
  attachInterrupt(0,interrupt,LOW);
}




void setup() {


////////////////////////////////////////////////////////////////////////
/////////////// setup metaldt_ HW control and input //////////////////////
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
//  attachInterrupt(0, interrupt, LOW);

//  pinMode(3, OUTPUT);
//  pinMode(11, OUTPUT);
//  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
//  TCCR2B = _BV(CS21);
//  OCR2A = 180;
//  OCR2B = 50;
  TCCR2B = TCCR2B & 0b11111000|2;

}


bool doing_display=false;
int pwm=230;

int pwm_dir=1;
void loop() {

  // Read the value of the sensor on A0
  String sensorVal = String(analogRead(A0));

  // convert the reading to a char array
  sensorVal.toCharArray(sensorPrintout, 4);


  u32 time_ms=millis();
  static u32 test_ms=time_ms;
  if (time_ms-test_ms>=1000){
    test_ms=time_ms;
    static u8 toggle=1;
    toggle^=1;
    if (toggle){
      digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
    }else{
      digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
    one_second_update_counter();
    digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    draw_background();
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
    drawit();
    digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
    TFT_test();
  }


  delay(100);
//  analogWrite(11, pwm);
  analogWrite(11, pwm);

//  OCR2A = 255-pwm;
//  OCR2B = pwm;
//  pwm+=pwm_dir;
//  if (pwm>244||pwm<100){
//    pwm_dir=-pwm_dir;
//    pwm+=pwm_dir;
//  }

  /*
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
  digitalWrite(2, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
  digitalWrite(3, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
  digitalWrite(4, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(50);              // wait for a second
*/

}


