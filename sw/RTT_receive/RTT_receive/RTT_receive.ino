#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef char s8;
typedef short s16;
typedef long s32;
typedef unsigned long COLORREF;


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/// tx parameters //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
#define RADIO_TICK_TIME 1
#define RADIO_TICKS_FOR_LOW 1
#define RADIO_TICKS_FOR_HIGH 4

#define RADIO_MSG_PAYLOAD_BYTES 12

#define NUM_SYNC_SET_BITS 15   // num 1's followed by 0 for sync data
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
#define RADIO_MSG_NUM_BITS_IN_MSG ((RADIO_MSG_PAYLOAD_BYTES+1)*8)  // extra 8 bits is check byte (initial sync is removed automatically)

////////////////////////////////////////////////////////////////////


#define PIN_RADIO_RX_DATA 4
#define PIN_ECHO_RX_DATA_LED 2

#define REC_BUFFER_PACKET_SIZE_BYTES 80
char bits[REC_BUFFER_PACKET_SIZE_BYTES+1];
u8 msg_bytes[REC_BUFFER_PACKET_SIZE_BYTES +1]="                                                                                ";
u16 num_bits=0;
u16 msg_num_bytes=0;




#define POLLS_PER_TICK (RADIO_TICK_TIME*8)  // 8khz timer update, so 8 polls per ms


#define PULSE_WIDTH_LOW_TEST  ((RADIO_TICKS_FOR_LOW*POLLS_PER_TICK)/2)
//#define PULSE_WIDTH_HIGH_TEST ((RADIO_TICKS_FOR_HIGH*POLLS_PER_TICK+RADIO_TICKS_FOR_LOW*POLLS_PER_TICK)/2)
#define PULSE_WIDTH_HIGH_TEST ((RADIO_TICKS_FOR_HIGH-1)*POLLS_PER_TICK)


void add_byte(u8 byte){
  msg_bytes[msg_num_bytes]=byte;
  msg_num_bytes++;
  if (msg_num_bytes>=REC_BUFFER_PACKET_SIZE_BYTES){
    msg_num_bytes=0;
  }
  msg_bytes[msg_num_bytes]=0;
}

u32 syncs=0;
u8 have_valid_sync=1;
u16 set_bit_counter=0;
u16 msg_data_bit_position=65535; // big value indicates not in msg yet
u16 data_byte=0;
u8  probably_recevied_all_of_msg=0;

void add_bit(u8 bit){
  static u8 we_got_8_msg_bits_so_ignore_0=0;
  if (msg_data_bit_position<=RADIO_MSG_NUM_BITS_IN_MSG){
    we_got_8_msg_bits_so_ignore_0++;
    if (we_got_8_msg_bits_so_ignore_0==8){
      we_got_8_msg_bits_so_ignore_0=0;
    }else{
      u8 bit_pos=msg_data_bit_position&7;
      if (bit){
        data_byte|=1<<bit_pos;
      }
      if (bit_pos==7){
        add_byte(data_byte);
        data_byte=0;
      }

      msg_data_bit_position++;
    }
    probably_recevied_all_of_msg=0;
  }else{
    probably_recevied_all_of_msg=1;
  }

  if (bit){
    set_bit_counter++;
  }else{
    if (set_bit_counter>=NUM_SYNC_SET_BITS){
      have_valid_sync=1;
      msg_data_bit_position=0;
      msg_num_bytes=0;
      syncs++;
      we_got_8_msg_bits_so_ignore_0=0;
    }
    set_bit_counter=0;
  }

  bits[num_bits]=bit?'1':'0';
  num_bits++;
  if(num_bits>=REC_BUFFER_PACKET_SIZE_BYTES){
    num_bits=0;
    for(int i=0;i<sizeof(bits);i++){
      bits[i]=0;
    }
  }
}



u32 pulse_width=0;
ISR(TIMER2_COMPA_vect){
  u8 val=digitalRead(PIN_RADIO_RX_DATA);
  digitalWrite(PIN_ECHO_RX_DATA_LED,val);
  if (val==HIGH){
    pulse_width++;
  }else{
    if (pulse_width>PULSE_WIDTH_HIGH_TEST){
      add_bit(1);
    }else if (pulse_width>PULSE_WIDTH_LOW_TEST){
      add_bit(0);
    }
    pulse_width=0;
  }
}



void setup_timer2_rx(){
  cli();//stop interrupts //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0 // set compare match register for 8khz increments
  OCR2A = 249; //  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  TCCR2A |= (1 << WGM21);// turn on CTC mode
  TCCR2B |= (1 << CS21);// Set CS21 bit for 8 prescaler
  TIMSK2 |= (1 << OCIE2A);// enable timer compare interrupt
  sei();//allow interrupts
}



void setup(){
  Serial.begin(57600*2);
//Serial.begin(57600);
  setup_timer2_rx();
  pinMode(4, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(PIN_ECHO_RX_DATA_LED, OUTPUT);
}



char rtt[256];
#define NUM_SBM20S 4
u32 counts_per_min[NUM_SBM20S]={0,0,0,0};
u32 counts_per_min2[NUM_SBM20S]={0,0,0,0};
u32 counts_per_min3[NUM_SBM20S]={0,0,0,0};
//u32 byte_errors=0;
//u32 bit_errors=0;
char msg_prt[REC_BUFFER_PACKET_SIZE_BYTES]="LOADED";

u16 eeprom_receive_byte_pos=0;

void loop(){
  Serial.flush();
  msg_bytes[REC_BUFFER_PACKET_SIZE_BYTES]=0;
  bits[REC_BUFFER_PACKET_SIZE_BYTES]=0;
//  for(u8 n=0;n<REC_BUFFER_PACKET_SIZE_BYTES;n++){
//    u8 v=msg_bytes[n];
//    if (v==0 || (v>=32 && v<='z')){
//      msg_prt[n]=v;
//    }else{
//      msg_prt[n]='+';
//    }
//  }
//
//  Serial.println();
//  Serial.println((char*)msg_prt);
//  Serial.println(bits);

  static u8 crc_fails=0;
  if (probably_recevied_all_of_msg && syncs>1 && have_valid_sync==1){
    have_valid_sync=0;  // to indicate this message has been parsed

    u8 check_byte=0;
    for(u8 n=0;n<RADIO_MSG_PAYLOAD_BYTES;n++){
      check_byte^=msg_bytes[n];
    }
    if (check_byte!=msg_bytes[RADIO_MSG_PAYLOAD_BYTES]){
      crc_fails++;
      Serial.println("---------------CRC failure:-----------------");
      rtt[0]=0;
      char dik[32];
      for(u8 i=0;i<=RADIO_MSG_PAYLOAD_BYTES;i++){
        sprintf(dik,"%02x,",msg_bytes[i]);
        strcat(rtt,dik);
      }
      Serial.println(rtt);
      Serial.println("--------------------------------------------");
    }


    // detect eeprom dump by 12 0xff's as the message
    u8 eeprom_dump_count=0;
    for(u8 i=0;i<12;i++){
      if (msg_bytes[i]==0xFF){
        eeprom_dump_count++;
      }
    }
//    if (eeprom_dump_count==12){
    if (eeprom_dump_count>10){
      Serial.println("--------------- Receiving EEPROM dump -----------------");
      eeprom_receive_byte_pos=1023;
    }else{
      // receive data
      if (eeprom_receive_byte_pos){
        s16 end=eeprom_receive_byte_pos-12;
        if (end<0){
          end=0;
        }
        sprintf(rtt,"EEPROM %04d to %04d =",end,eeprom_receive_byte_pos);
        rtt[0]=0;
        char dik[32];
        for(u8 i=0;i<=RADIO_MSG_PAYLOAD_BYTES;i++){
          sprintf(dik,"%02x,",msg_bytes[i]);
          strcat(rtt,dik);
        }
        Serial.println(rtt);
        eeprom_receive_byte_pos=end;
      }else{
        u8 j=0;
        for(u8 i=0;i<NUM_SBM20S;i++){
          u32 b1=msg_bytes[j];
          u32 b2=msg_bytes[j+1];
          u32 b3=msg_bytes[j+2];
          counts_per_min[i]=b1|(b2<<8)|(b3<<16);
          j+=3;
        }
        Serial.println("--------------- Receiving Counts per minute data -----------------");
        sprintf(rtt,"%lu  %lu  %lu  %lu",counts_per_min[0],counts_per_min[1],counts_per_min[2],counts_per_min[3]);
        Serial.println(rtt);
        Serial.println("------------------------------------------------------------------");
      }
    }
    probably_recevied_all_of_msg=0;
  }else{
    u32 time_ms=millis();
    static u32 report_ms=0;
    if (time_ms-report_ms>1000){
      report_ms=time_ms;
      Serial.println(bits);
      sprintf(rtt,"syncs %lu crc=%d ",syncs,crc_fails);
      Serial.println(rtt);
    }
  }
//	delay(1000);
}
