#include "preprocessed_data_from_LTSPICE_METALDT_simulation.h"

#define LINE_HEIGHT 6
#define MAX_dBs 30
#define plot_height_in_volts 9


#define GRAPH_STARTY 4
#define GRAPH_HEIGHT (plot_height_in_volts*10)  // must be multiple

#define COL_HGRID_LINES grey14_cr
#define COL_AXIS      goldenrod_cr
#define COL_AXIS_KEY  grey60_cr
#define COL_AXIS_KEY2 yellow3_cr
#define COL_AXIS_KEY3 green2_cr
#define COL_N   grey20_cr
#define COL_50  grey30_cr
#define COL_100 grey50_cr

#ifdef _WINDOWS
  #include <algorithm>
  using namespace std;
#endif

bool once=true;


u16 d_pins_addr[14];
u8 d_pins_mask[14];
bool display_pins=false;
u8 port_d_val=0;
u8 tx_is=128;
u8 rx_is=128;


void plot_numbert_float(u8 orig_x,u8 &y,float n,COLORREF col2,bool int_if_less_than_1000=false);
void draw_display_mode_see_parametric_eq_settings();

//u8 display_mode=SEE_OTHER_DIGI_POT_SETTINGS;
u8 display_mode=DISPLAY_MODE_UNMODIFIED_PEQ_SETTINGS;

#define LOGFN(a) log(a)
#define EXPFN(a) exp(a)
#define xoffset_in_microseconds_since_coil_de_energization 0.0f
#define plot_width_in_microseconds 55.0f
#define plot_scale ((float)GRAPH_WIDTH/plot_width_in_microseconds)
#define plot_scale_y ((float)GRAPH_HALF_HEIGHT/plot_width_in_microseconds)

#define PRINT_INFO_COL_TXT goldenrod1_cr
#define PRINT_INFO_COL_NUM goldenrod_cr
#define PRINT_INFO_COL_SYM goldenrod2_cr

#define PRINT_SPACING 45
#define PRINT_X_FREQ -5

#define PRINT_X_AUX_COLUMN1 (PRINT_X_FREQ+7)
#define PRINT_X_AUX_COLUMN2 (PRINT_X_AUX_COLUMN1+32)

#define PRINT_X_Q (PRINT_X_FREQ+PRINT_SPACING)
#define PRINT_X_DEPTH (PRINT_X_FREQ+PRINT_SPACING*2)

#define PRINT_INFO_COL_DIGI_POT grey40_cr
#define PRINT_DIGI_POT_OFFSET 31
#define PRINT_RAW_DIGI_POT_OFFSET 12
#define INFO_TEXT_START_Y 135

#define PRINT_AUX_FREQ_COL goldenrod_cr
#define PRINT_INFO_FREQ_COL goldenrod1_cr
#define PRINT_INFO_DEPTH_COL magenta1_cr
#define PRINT_INFO_Q_COL lightblue2_cr
#define PRINT_INFO_TITLE_COL grey50_cr
#define PRINT_INFO_TITLE2_COL grey30_cr
#define PRINT_INFO_TITLE2_OPERATOR_COL goldenrod3_cr

float get_plot_index_offset(float time_in_microseconds_since_coil_de_energization){
  // determine index of transfer_fn graph from frequency
  float x=(time_in_microseconds_since_coil_de_energization-(float)xoffset_in_microseconds_since_coil_de_energization)*(float)plot_scale;
  return x;
}




u8 sleep_update_outputs=0;  // dont update outputs & inhibit all digital clocked signals close to the analog components




void print_int(u8 x,u8 y,u16 n,char*format="%03d"){
  char rtt[6];
  sprintf(rtt,format,n);
  print_pretty_byte(x,y,rtt,PRINT_INFO_COL_DIGI_POT,PRINT_INFO_COL_DIGI_POT,PRINT_INFO_COL_DIGI_POT);
}

u8 which_peq_to_redraw_info_for=15;
u8 which_peq_part_to_redraw_info_for=7;
void cycle_display_mode();


void redraw_info_text();



u8 coil_energise_delay_microseconds=50;
u8 sampling_delay_microseconds=50;
u16 buttholmes_anal_value=0;

u8 last_y_plotted[GRAPH_WIDTH];
s8 total_transfer_function[GRAPH_WIDTH];

#if WINDOWS_DEBUG_DISPLAY==1
int max_transfer_fn=0;
#endif

s32 num_speed_tests=0;


#define CON1 220.0f
#define ECON1 -0.1f
#define CON2 3.0f
#define ECON2 -0.2f


void update_graph(){
  gcol=blue3_cr;
  gcol=0;
  p(sleep_update_outputs,0); // animate sleep digital update countdown
  if (sleep_update_outputs!=0){
    sleep_update_outputs--;
  }

  char rtt[32];
  u8 y=118;
  sprintf(rtt,"n=%ld ",num_speed_tests++);
  print_pretty_byte(PRINT_X_FREQ+8,y,rtt,PRINT_INFO_TITLE_COL ,PRINT_INFO_TITLE_COL,PRINT_INFO_TITLE_COL);y+=7;
  sprintf(rtt,"Big Bob and Lovely Meral=%d ",buttholmes_anal_value);
  print_pretty_byte(PRINT_X_FREQ+8,y,rtt,goldenrod_cr,white_cr,hotpink_cr);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if WINDOWS_DEBUG_DISPLAY==1

void dot_vline(u8 x,u8 y,u8 h);
void dot_hline(u8 x,u8 y,u8 w);

//char yaxis_keytext[YAXIS_TICKS][4]={"+30","+25","+20","+15","+10"," +5","dB0"," -5","-10","-15","-20","-25","-30"};
u16 xaxis_ticks[]={0,5,10,15,20,21,22,23,24,25,26,27,28,29,30,35,40,45,50,55};
u8 nxat=sizeof(xaxis_ticks)/sizeof(*xaxis_ticks);

//float xoffset=LOGFN((float)xaxis_ticks[0]);
//float plot_scale=(float)(GRAPH_WIDTH-1)/(LOGFN((float)xaxis_ticks[nxat-1])-xoffset);
//float plot_scale=(float)(GRAPH_WIDTH-1)/(LOGFN((float)xaxis_ticks[nxat-1])-xoffset);

void hline_preprocess(u8 x,u8 y,u8 w){
  for(u8 i=x;i<=x+w;i++){
    prepro_pixels[i].push_back(preprocessed_pixels(y,gcol));
//    p(i,y);
  }
}

// delete lines from being rendered
void hline_clr(u8 x,u8 y,u8 w){
  gcol=black_cr;
  for(u8 i=x;i<=x+w;i++){
    u32 j=0;
    while(j<prepro_pixels[i].size()){
      if (prepro_pixels[i][j].y==y){
        prepro_pixels[i].erase(prepro_pixels[i].begin()+j);
      }else{
        j++;
      }
    }
//    p(i,y);
  }
}


void vline_preprocess(u8 x,u8 y,u8 h){
  for(u8 i=y;i<=y+h;i++){
    prepro_pixels[x].push_back(preprocessed_pixels(i,gcol));
//    p(x,i);
  }
}


void dot_vline(u8 x,u8 y,u8 h){
  h+=y;
  while(y<=h){
    prepro_pixels[x].push_back(preprocessed_pixels(y,gcol));
//    p(x,y);
    y+=2;
  }
}


void dot_hline(u8 x,u8 y,u8 w){
  w+=y;
  while(x<=w){
    prepro_pixels[x].push_back(preprocessed_pixels(y,gcol));
//    p(x,y);
    x+=2;
  }
}


void draw_parametric_info_display_key(){
  u8 y=INFO_TEXT_START_Y-29;
  print_pretty_byte(PRINT_X_FREQ +8,y,"PULSE INDUCTION METAL DETECTOR",PRINT_INFO_TITLE_COL ,PRINT_INFO_TITLE_COL,PRINT_INFO_TITLE_COL);
//  y+=7;
//  print_pretty_byte(PRINT_X_FREQ +14,y,"METALDT ACTIVE FILTER STAGES:",PRINT_INFO_TITLE2_COL ,PRINT_INFO_TITLE2_COL,PRINT_INFO_TITLE2_COL);
//  y+=8;
//  print_pretty_byte(PRINT_X_FREQ +7,y,"FREQUENCY",PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL );
//  print_pretty_byte(PRINT_X_DEPTH+7,y,"DEPTH"    ,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);
//  y+=6;
//  print_pretty_byte(PRINT_X_FREQ +7,y,"(HZ)",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
//  print_pretty_byte(PRINT_X_Q    +7,y,"STAGE Q"  ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    );
//  print_pretty_byte(PRINT_X_DEPTH+7,y,"(DB)",PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);
  //    print_pretty_byte(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y++,"FREQUENCY",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
  //    print_pretty_byte(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y,"HZ",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
  //    print_int(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y,donkeys);
  //    plot_numbert_float(PRINT_X_Q     ,y,Q ,lightblue2_cr,false);
}

vector<preprocessed_pixels> prepro_pixels[DISPLAY_WIDTH];
#endif


#if WINDOWS_DEBUG_DISPLAY==1
  #define PREPROCESSED_PIXEL_NUM 16384
  #define NUM_PRE_GCOLS 32
  u16 preprocessed_x_index[DISPLAY_WIDTH];
  u8 preprocessed_num_gcols=0;
  COLORREF preprocessed_gcols[NUM_PRE_GCOLS];
  u16 preprocessed_index_num=0;
  u8 preprocessed_pix_data[PREPROCESSED_PIXEL_NUM];
#else
  #include "preprocessed_graph_pixels.cpp"
#endif


bool initial_render=true;
bool display_input_or_output_potentiometers=false;

void draw_graph(){
  if (need_to_cycle_mode){
    cycle_display_mode();
    need_to_cycle_mode=false;
  }
  if (need_to_toggle_func){
    need_to_toggle_func=false;
    display_input_or_output_potentiometers^=true;
  }
  u8 yt=128;
  update_graph();

#if WINDOWS_DEBUG_DISPLAY==1
  if (once){
    preprocess_and_save=true;
    for(int i=0;i<GRAPH_WIDTH;i++){
      prepro_pixels[i].clear();
    }

    gcol=grey34_cr;
    gcol=COL_AXIS;
    u8 ystep;
    u8 x=0;
    u8 y;

    y=GRAPH_STARTY+GRAPH_HEIGHT+1;
    for(u8 i=0;i<nxat;i++){
      u16 f=xaxis_ticks[i];
      u8 x=(u8)get_plot_index_offset((float)f);
      if (x>=0){
        char str[64];
        gcol=COL_N;
        sprintf_s(str,64,"%d",int(f));
        if (int(f)%5==0){
          print_pretty_byte(x+7,y+2,str,COL_AXIS_KEY,COL_AXIS_KEY,COL_AXIS_KEY2);
        }
        gcol=COL_N;
        if (int(f)%5==0){
          gcol=COL_50;
        }
        if (int(f)%10==0){
          gcol=COL_100;
        }
        dot_vline(GRAPH_STARTX+x,GRAPH_STARTY,GRAPH_HEIGHT);
      }
    }

    ystep=GRAPH_HEIGHT/plot_height_in_volts;
    x=0;
    y=GRAPH_STARTY-2;
    char rtt[64];
    for(u8 yi=0;yi<=plot_height_in_volts;yi++){
      sprintf_s(rtt,64,"%d",plot_height_in_volts-yi);
      print_pretty_byte(x,y,rtt,COL_AXIS,COL_AXIS_KEY,COL_AXIS_KEY2);
      gcol=COL_AXIS;
      prepro_pixels[GRAPH_STARTX-2].push_back(preprocessed_pixels(y+2,gcol));
      dot_hline(GRAPH_STARTX,y+2,GRAPH_WIDTH);
      y+=ystep;
    }

    gcol=white_cr;
    y=GRAPH_STARTY+GRAPH_HEIGHT+1;
    for(u8 i=0;i<GRAPH_WIDTH;i++){
      u16 f=xaxis_ticks[i];
      if (once){
        _cprintf("%d,%20.20lf\n",i,EXPFN(LOGFN(10.0)+LOGFN(20000.0/10.0)*(double)i/(double)(GRAPH_WIDTH-1)));
      }
    }

    draw_parametric_info_display_key();


    once=false;
    preprocess_and_save=false;


    ///////////////////////////////////// preprocess //////////////////////////////////////
    // remove duplicate coords
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      vector<preprocessed_pixels> &pp=prepro_pixels[x];
      sort(pp.begin(),pp.end());
      pp.erase(unique(pp.begin(),pp.end()),pp.end());
    }
    preprocessed_index_num=0;
    preprocessed_num_gcols=0;
    memset(preprocessed_x_index,0,sizeof(preprocessed_x_index));
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      vector<preprocessed_pixels> &pp=prepro_pixels[x];
      assert(preprocessed_num_gcols<NUM_PRE_GCOLS);
      for(int j=0;j<(int)pp.size();j++){
        bool new_col=true;
        for(int k=0;k<preprocessed_num_gcols;k++){
          if (preprocessed_gcols[k]==pp[j].gcol){
            new_col=false;
            break;
          }
        }
        if (new_col){
          preprocessed_gcols[preprocessed_num_gcols++]=pp[j].gcol;
        }
      }
    }

    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      vector<preprocessed_pixels> &pp=prepro_pixels[x];
      assert(preprocessed_index_num-4<PREPROCESSED_PIXEL_NUM);
      for(int j=0;j<(int)pp.size();j++){
        COLORREF gcol=pp[j].gcol;
        u8 y=pp[j].y;
        s8 gcol_index=-1;
        for(int k=0;k<preprocessed_num_gcols;k++){
          if (preprocessed_gcols[k]==gcol){
            gcol_index=k;
            break;
          }
        }
        assert(gcol_index!=-1);
        preprocessed_pix_data[preprocessed_index_num++]=y;
        preprocessed_pix_data[preprocessed_index_num++]=(u8)gcol_index;
      }
      preprocessed_x_index[x]=preprocessed_index_num;
    }

    // save preprocessed data as cpp
    int rt=1;
    FILE *fp;
    fopen_s(&fp,"preprocessed_graph_pixels.cpp","w");
    u16 st_ind=0;
    fprintf_s(fp,"PROGMEM uint16_t preprocessed_x_index[%d]={\n  ",DISPLAY_WIDTH);
    bool dc=false;
    int breakl=16;
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      if (dc) fprintf_s(fp,",");
      if (breakl<0){
        breakl=16;
        fprintf_s(fp,"\n  ");
      }
      breakl--;
      fprintf_s(fp,"0x%04X",preprocessed_x_index[x]);
      dc=true;
    }
    fprintf_s(fp,"\n};\n");

    fprintf_s(fp,"PROGMEM uint16_t preprocessed_gcols[%d]={\n  ",preprocessed_num_gcols);
    dc=false;
    for(u8 x=0;x<preprocessed_num_gcols;x++){
      if (dc) fprintf_s(fp,",");
      fprintf_s(fp,"0x%04X",col_trans(preprocessed_gcols[x]));
      dc=true;
    }
    fprintf_s(fp,"\n};\n");

    fprintf_s(fp,"PROGMEM uint8_t preprocessed_pix_data[%d]={\n  ",preprocessed_index_num);
    dc=false;
    breakl=32;
    for(u16 j=0;j<preprocessed_index_num;j++){
      if (dc) fprintf_s(fp,",");
      if (breakl<0){
        breakl=32;
        fprintf_s(fp,"\n  ");
      }
      breakl--;
      fprintf_s(fp,"0x%02X",preprocessed_pix_data[j]);
      dc=true;
    }
    fprintf_s(fp,"\n};\n");
    fclose(fp);
  }
#endif
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  if (initial_render){
    initial_render=false;
    u16 st_ind=0;
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      u16 en_ind=pgm_read_word_near(preprocessed_x_index+x);
      for(u16 j=st_ind;j<en_ind;j+=2){
        u8 y=pgm_read_byte_near(preprocessed_pix_data+j);
        u8 gcol_index=pgm_read_byte_near(preprocessed_pix_data+j+1);
        gcol=pgm_read_COLORREF_near(preprocessed_gcols+gcol_index);
        p(x,y);
      }
      st_ind=en_ind;
    }
    draw_display_mode_see_parametric_eq_settings();
  }


  for(u8 i=0;i<GRAPH_WIDTH;i++){
    u8 y=GRAPH_STARTY+GRAPH_HEIGHT-total_transfer_function[i];
    u8 ytest=last_y_plotted[i];
    if (y!=ytest){
      u8 x=i+GRAPH_STARTX;
      u16 st_ind=0;
      if (x>0){
        st_ind=pgm_read_word_near(preprocessed_x_index+x-1);
      }
      u16 en_ind=pgm_read_word_near(preprocessed_x_index+x);
      gcol=black_cr;
      for(u16 j=st_ind;j<en_ind;j+=2){
        u8 ye=pgm_read_byte_near(preprocessed_pix_data+j);
        if (ye==ytest){
          u8 gcol_index=pgm_read_byte_near(preprocessed_pix_data+j+1);
          gcol=pgm_read_COLORREF_near(preprocessed_gcols+gcol_index);
          break;
        }
      }
      // check for a 2 line vline to ~double SPI TFT rendering speed
      if (y-ytest==1){
        vline_2p(x,ytest,white_cr);
      }else{
        // two separated pixels
        p(x,ytest);
        gcol=white_cr;
        p(x,y);
      }
      last_y_plotted[i]=y;
    }
  }

}




void sprintf_positive_float(char* buffer,float n,u8 chars_total,u8 digits_after_dp){
  // lack of formatted float on arduino
  u32 int_part;
  char form[8];
  sprintf(form,"%%%dd",(u32)(chars_total-digits_after_dp-1));
  int_part=(u32)n;
  sprintf(buffer,form,int_part);
  if (digits_after_dp){
    sprintf(form,"%%0%dd",(u32)digits_after_dp);
    double fraction=(double)n-(double)int_part;
    while(digits_after_dp--){
      fraction*=10.0;
    }
    strcat(buffer,".");
    char rtt[6];
    sprintf(rtt,form,(u32)fraction);
    strcat(buffer,rtt);
  }
}



void plot_numbert_float(u8 orig_x,u8 &y,float n,COLORREF col2,bool int_if_less_than_1000){
  // formatted floating point no. plotter
  bool negative=false;
  if (n<0){
    n=-n;
    negative=true;
  }
  char rtt[16];
  if (n<1000.0f){
    if (int_if_less_than_1000){
      sprintf(rtt,"%6d  ",(u32)n);
    }else{
      if (n<1.0f)
        sprintf_positive_float(rtt,n,6,3);
      if (n<10.0f){
        sprintf_positive_float(rtt,n,6,2);
      }else if (n<100.0f){
        sprintf_positive_float(rtt,n,6,1);
      }else if (n<1000.f){
        sprintf_positive_float(rtt,n,6,0);
      }
      strcat(rtt," ");
    }
  }else{
    n*=0.001f;
    if (n<1.0f){
      sprintf_positive_float(rtt,n,6,3);
      strcat(rtt,"k ");
    }else if (n<10.0f){
      sprintf_positive_float(rtt,n,6,2);
      strcat(rtt,"k ");
    }else if (n<100.0f){
      sprintf_positive_float(rtt,n,6,1);
      strcat(rtt,"k ");
    }else if (n<1000.f){
      sprintf_positive_float(rtt,n,6,0);
      strcat(rtt,"k ");
    }else{
      sprintf_positive_float(rtt,n,6,3);
      strcat(rtt,"k ");
    }
  }
  if (negative){
    char *rt2=rtt;
    while(*++rt2==' '){}
    *(rt2-1)='-';
  }

  print_pretty_byte(orig_x,y,rtt,grey65_cr,col2,green3_cr);y+=LINE_HEIGHT;
}


void draw_display_mode_see_parametric_eq_settings(){
  u8 y=INFO_TEXT_START_Y-29;
//  y+=7;
//  print_pretty_byte(PRINT_X_FREQ +14,y,"METALDT ACTIVE FILTER STAGES:",PRINT_INFO_TITLE2_COL ,PRINT_INFO_TITLE2_COL,PRINT_INFO_TITLE2_COL);
//   y+=8;
//   print_pretty_byte(PRINT_X_FREQ +7,y,"SAMPLE RATE",PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL );
//   print_pretty_byte(PRINT_X_DEPTH+7,y,"&S DELAY"    ,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);
//   y+=6;
//   print_pretty_byte(PRINT_X_FREQ +7,y,"(HZ)",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
//   print_pretty_byte(PRINT_X_Q    +7,y,"STAGE Q"  ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    );
//   print_pretty_byte(PRINT_X_DEPTH+7,y,"(DB)",PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);

//   y+=8;
//   u8 xx=4;
//   char rtt[64];
//   for(u8 i=0;i<14;i++){
//     sprintf(rtt,"D%d %d %d",i,d_pins_addr[i],d_pins_mask[i]);
//     print_pretty_byte(xx,y,rtt,PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL );
//     if (i==5 || i==11){
//       xx+=45;
//       y=INFO_TEXT_START_Y-29;
//     }
//     y+=6;
//   }


}


s8 wang_into_nice_plotval(s16 val){
  val=(val-511)/5;
  if (val>100) val=100;
  if (val<-100) val=-100;
  return (s8)val;
}



bool need_to_cycle_mode=false;
bool need_to_toggle_func=false;

void cycle_display_mode(){
  display_mode++;
  if (display_mode>=DISPLAY_MODE_NUM_MODES){
    display_mode=DISPLAY_MODE_UNMODIFIED_PEQ_SETTINGS;
  }
#define INFO_TEXT_START_YMABIT (INFO_TEXT_START_Y-22)
  u8 h=160-INFO_TEXT_START_YMABIT;
//    gcol=darkslateblue_cr;
  gcol=black_cr;
  rectfill(0,INFO_TEXT_START_YMABIT+h,128,h);
  switch(display_mode){
    case DISPLAY_MODE_DEBUG_SEE_RAW_PEQ_POT_N_DIGIPOT_SETTINGS:
      break;
  }
}



void redraw_info_text(){

  u8 y=INFO_TEXT_START_Y-7;
  switch(display_mode){
    case DISPLAY_MODE_UNMODIFIED_PEQ_SETTINGS:
      {
        // draw the parameteric eq settings & digi pot settings
        u8 peq_index=255;
        if (which_peq_to_redraw_info_for&1) peq_index=0;
        if (which_peq_to_redraw_info_for&2) peq_index=1;
        if (which_peq_to_redraw_info_for&4) peq_index=2;
				if (which_peq_to_redraw_info_for&8) peq_index=3;
				if (which_peq_to_redraw_info_for&16) peq_index=4;
        if (peq_index==255){
          return;
        }
        y+=peq_index*LINE_HEIGHT;
      }
      break;
  }
}


//
// real controls:
// 1  gain
// 2  balance
// 3  bass balance
// 4  widening
//
// virtual controls:
// 1. sub-bass
// 2. bass
// 3. mid
// 4. top
//
// Misc extras
// 1. noise magnitude
// 2. white or pink noise
//



#define INPUT_VALUE_GAIN (16+8)

