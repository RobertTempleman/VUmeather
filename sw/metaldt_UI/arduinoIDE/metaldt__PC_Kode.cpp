#include "stdafx.h"




/*
#include "preprocessed_data_from_LTSPICE_METALDT_simulation.h"
#define LINE_HEIGHT 6
#define MAX_dBs 30
#define YAXIS_TICKS 13
#define GRAPH_INDEX_0 ((YAXIS_TICKS-1)/2)


#define GRAPH_STARTY 4
#define GRAPH_HALF_HEIGHT (GRAPH_INDEX_0*8)  // must be multiple

#define COL_HGRID_LINES grey14_cr
#define COL_AXIS      goldenrod_cr
#define COL_AXIS_KEY  grey60_cr
#define COL_AXIS_KEY2 yellow3_cr
#define COL_AXIS_KEY3 green2_cr
#define COL_N   grey20_cr
#define COL_50  grey30_cr
#define COL_100 grey40_cr

#ifdef _WINDOWS
  #include <algorithm>
  using namespace std;
#endif

bool once=true;

void plot_numbert_float(u8 orig_x,u8 &y,float n,COLORREF col2,bool int_if_less_than_1000=false);


#define LOGFN(a) log(a)
#define EXPFN(a) exp(a)
#define xoffset 2.3025850929940456840179914546844
#define plot_scale 14.866655716406562580527770923342

#define PRINT_INFO_COL_TXT goldenrod1_cr
#define PRINT_INFO_COL_NUM goldenrod_cr
#define PRINT_INFO_COL_SYM goldenrod2_cr

#define PRINT_SPACING 45
#define PRINT_X_FREQ -5
#define PRINT_X_Q (PRINT_X_FREQ+PRINT_SPACING)
#define PRINT_X_DEPTH (PRINT_X_FREQ+PRINT_SPACING*2)

#define PRINT_INFO_COL_DIGI_POT grey40_cr
#define PRINT_DIGI_POT_OFFSET 31
#define INFO_TEXT_START_Y 135

#define PRINT_INFO_FREQ_COL goldenrod1_cr
#define PRINT_INFO_DEPTH_COL magenta1_cr
#define PRINT_INFO_Q_COL lightblue2_cr
#define PRINT_INFO_TITLE_COL grey50_cr
#define PRINT_INFO_TITLE2_COL grey30_cr

//#define GRAPH_STARTX 14
//#define GRAPH_WIDTH (128-GRAPH_STARTX) // the width that is updated with the transfer fn.
//float xoffset=LOGFN(10.0f);
//float plot_scale=(float)(GRAPH_WIDTH-1)/(LOGFN(20000.0f)-xoffset);


float get_plot_index_offset(float frequency){
  // determine index of transfer_fn graph from frequency
  float x=(LOGFN(frequency)-(float)xoffset)*(float)plot_scale;
  return x;
}


u8 stage_enabled[NUM_PEQS]={1,1,1,1};
//f q d
s16 potentiometer_analog_reading[NUM_POTENTIOMETERS]={
  0    ,600  ,0    ,
  500  ,511  ,450  ,
  250  ,0    ,750  ,
  1023 ,1023 ,1023
};


//u8 digital_potentiometer_outputs[NUM_POTENTIOMETERS];


u8 metaldt_peq::peq_index_singleton=0;

metaldt_peq metaldt_peqs[NUM_PEQS]={
  metaldt_peq(0, 0.0f, 0.0f, 0.0f),
  metaldt_peq(0, 0.0f, 0.0f, 0.0f),
  metaldt_peq(1, 0.0f, 0.0f, 0.0f),
  metaldt_peq(1, 0.0f, 0.0f, 0.0f),
};


void print_int(u8 x,u8 y,u8 n){
  char rtt[6];
  sprintf(rtt,"%03d",n);
  print_pretty_byte(x,y,rtt,PRINT_INFO_COL_DIGI_POT,PRINT_INFO_COL_DIGI_POT,PRINT_INFO_COL_DIGI_POT);
}

u8 which_peq_to_redraw_info_for=15;
u8 which_peq_part_to_redraw_info_for=7;


bool metaldt_peq::set_centre_frequency(s16 potentiometer_reading){
  // determine desired frequency
  if (last_freq_pot_reading==potentiometer_reading){
    return false;
  }
  if (abs(last_freq_pot_reading-potentiometer_reading)<2){
    // help kill potentiometer jitter
    return false;
  }
  last_freq_pot_reading=potentiometer_reading;
  float potentiometer_reading_normalised=(float)last_freq_pot_reading/1023.0f;
  if (potentiometer_reading_normalised==1.0f){
    int rt=1;
  }
  float fs=read_centre_frequencies_from_LTspice_simulation(frequency_curve,0);
  float fe=read_centre_frequencies_from_LTspice_simulation(frequency_curve,NUM_CENTRE_FREQUENCIES-1);
  float frequency_start_index=get_plot_index_offset(fs);
  float frequency_end_index=get_plot_index_offset(fe);
  frequency_plot_index=frequency_start_index+potentiometer_reading_normalised*(frequency_end_index-frequency_start_index);

  // determine normalized digital potentiometer fraction by lerping through the LTspice centre_frequencies_from_LTspice_simulation LUT
  frequency_wanted=EXPFN(LOGFN(fs)+LOGFN(fe/fs)*potentiometer_reading_normalised);
  u8 index=0;
  for(u8 i=0;i<NUM_CENTRE_FREQUENCIES;i++){
    if (frequency_wanted>=read_centre_frequencies_from_LTspice_simulation(frequency_curve,i)){
      index=i;
    }else{
      break;
    }
  }
  u8 y=INFO_TEXT_START_Y+peq_index*LINE_HEIGHT;
  float digital_pot_setting=0;
  u8 index1=index+1;
  if (index1>=NUM_CENTRE_FREQUENCIES){
    // at the end
    digital_pot_setting=1.0f;
  }else{
    // LERP between the two values
    float st_freq=read_centre_frequencies_from_LTspice_simulation(frequency_curve,index);
    float en_freq=read_centre_frequencies_from_LTspice_simulation(frequency_curve,index1);
    float d_freq=en_freq-st_freq;
    float frac=(frequency_wanted-st_freq)/d_freq;
    assert(frac>=0 && frac<1.0f);
    digital_pot_setting=((float)index+frac)/(float)(NUM_CENTRE_FREQUENCIES-1);
  }
  assert(digital_pot_setting<=1.0f && digital_pot_setting>=0);
  digital_potentiometer_frequency=(u8)(digital_pot_setting*255.0f+0.5f);

  which_peq_to_redraw_info_for|=1<<peq_index;
  which_peq_part_to_redraw_info_for|=1;
  return true;
}



bool metaldt_peq::set_depth(s16 potentiometer_reading){
  if (last_depth_pot_reading==potentiometer_reading){
    return false;
  }
  if (abs(last_depth_pot_reading-potentiometer_reading)<2){
    // help kill potentiometer jitter
    return false;
  }
  last_depth_pot_reading=potentiometer_reading;
  float potentiometer_reading_normalised=(float)last_depth_pot_reading/1023.0f;
  depth=potentiometer_reading_normalised;

  float index_f=(float)(ACTUAL_DEPTH_VALUES-1)*depth;
  depth_array_index=(u8)index_f;
  float digital_pot_setting;
  if (depth_array_index>=ACTUAL_DEPTH_VALUES-1){
    digital_pot_setting=1.0f;
    depth_interpolate_fraction=0;
    electrical_depth=read_float_array(stage_depth_in_dBs,ACTUAL_DEPTH_VALUES-1);
  }else{
    depth_interpolate_fraction=index_f-(float)depth_array_index;
    assert(depth_interpolate_fraction>=0 && depth_interpolate_fraction<1.0f);
    // LERP between the two values
    float st_depth_pot=read_float_array(depth_potentiometer_values,depth_array_index);
    float en_depth_pot=read_float_array(depth_potentiometer_values,depth_array_index+1);
    float d_depth=en_depth_pot-st_depth_pot;
    digital_pot_setting=st_depth_pot+depth_interpolate_fraction*d_depth;

    float st_depth=read_float_array(stage_depth_in_dBs,depth_array_index);
    float en_depth=read_float_array(stage_depth_in_dBs,depth_array_index+1);
    d_depth=en_depth-st_depth;
    electrical_depth=st_depth+depth_interpolate_fraction*d_depth;

    assert(digital_pot_setting<=1.0f && digital_pot_setting>=0);
  }
//  u8 y=INFO_TEXT_START_Y+peq_index*LINE_HEIGHT;
  digital_potentiometer_depth=(u8)(digital_pot_setting*255.0f+0.5f);
  which_peq_to_redraw_info_for|=1<<peq_index;
  which_peq_part_to_redraw_info_for|=2;
  return true;
}



bool metaldt_peq::set_q(s16 potentiometer_reading){
  if (last_Q_pot_reading==potentiometer_reading){
    return false;
  }
  if (abs(last_Q_pot_reading-potentiometer_reading)<2){
    // help kill potentiometer jitter
    return false;
  }
  last_Q_pot_reading=potentiometer_reading;
  float potentiometer_reading_normalised=(float)last_Q_pot_reading/1023.0f;




  float index_f=(float)(NUM_QS-1)*potentiometer_reading_normalised;
  u8 index=(u8)index_f;
  float digital_pot_setting;
  if (index>=ACTUAL_DEPTH_VALUES-1){
    digital_pot_setting=1.0f;
    depth_interpolate_fraction=0;
//    Q=read_float_array(stage_depth_in_dBs,ACTUAL_DEPTH_VALUES-1);
  }else{
    depth_interpolate_fraction=index_f-(float)index;
    assert(depth_interpolate_fraction>=0 && depth_interpolate_fraction<1.0f);
    // LERP between the two values
    float st_Q_pot=read_float_array(Q_potentiometer_values,index);
    float en_Q_pot=read_float_array(Q_potentiometer_values,index+1);
    float d_Q=en_Q_pot-st_Q_pot;
    digital_pot_setting=st_Q_pot+depth_interpolate_fraction*d_Q;

//    Q=st_depth+depth_interpolate_fraction*d_depth;

    assert(digital_pot_setting<=1.0f && digital_pot_setting>=0);
  }
//  u8 y=INFO_TEXT_START_Y+peq_index*LINE_HEIGHT;




  Q=potentiometer_reading_normalised;
  digital_potentiometer_Q=(u8)(digital_pot_setting*255.0f+0.5f);
  which_peq_to_redraw_info_for|=1<<peq_index;
  which_peq_part_to_redraw_info_for|=4;
  return true;
}




void redraw_info_text(){
  u8 peq_index=255;
  if (which_peq_to_redraw_info_for&1) peq_index=0;
  if (which_peq_to_redraw_info_for&2) peq_index=1;
  if (which_peq_to_redraw_info_for&4) peq_index=2;
  if (which_peq_to_redraw_info_for&8) peq_index=3;
  if (peq_index==255){
    return;
  }
  u8 y=INFO_TEXT_START_Y+peq_index*LINE_HEIGHT;
  metaldt_peq &p=metaldt_peqs[peq_index];
  if (which_peq_part_to_redraw_info_for&1){
    print_int(PRINT_X_FREQ+PRINT_DIGI_POT_OFFSET,y,p.digital_potentiometer_frequency);
    plot_numbert_float(PRINT_X_FREQ  ,y,p.frequency_wanted ,PRINT_INFO_FREQ_COL,false);
    which_peq_part_to_redraw_info_for&=(255^1);
  }else if (which_peq_part_to_redraw_info_for&2){
    print_int(PRINT_X_DEPTH+PRINT_DIGI_POT_OFFSET,y,p.digital_potentiometer_depth);
    plot_numbert_float(PRINT_X_DEPTH  ,y,p.electrical_depth ,PRINT_INFO_DEPTH_COL,false);
    which_peq_part_to_redraw_info_for&=(255^2);
  }else if (which_peq_part_to_redraw_info_for&4){
    print_int(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y,p.digital_potentiometer_Q);
    plot_numbert_float(PRINT_X_Q     ,y,p.Q ,PRINT_INFO_Q_COL,false);
    which_peq_part_to_redraw_info_for&=(255^4);
  }
  if (which_peq_part_to_redraw_info_for==0){
    which_peq_to_redraw_info_for&=255^(1<<peq_index);
  }
}



u8 last_y_plotted[GRAPH_WIDTH];
s16 total_transfer_function[GRAPH_WIDTH];

#if WINDOWS_DEBUG_DISPLAY==1
int max_transfer_fn=0;
#endif

void metaldt_peq::write_and_scale_transfer_fn(s16 index,s16 value){
#if WINDOWS_DEBUG_DISPLAY==1
  if (value>max_transfer_fn){
    max_transfer_fn=value;
    _cprintf("max transfer fn=%d\n",max_transfer_fn);
  }
#endif
  s8 value_8;
  if (value>=0){
    value_8=value>>6;
    if (value_8>127){
      value_8=127;
    }
  }else{
    value_8=-((-value)>>6);
    if (value_8<-128){
      value_8=-128;
    }
  }
  transfer_function[index]=value_8;
}


void metaldt_peq::update_transfer_fn(bool recalc){
  if (recalc){
//    float st_xfrac=frequency_plot_index-(float)(int)frequency_plot_index;
//    float en_xfrac=1.0f-st_xfrac;

    // 2 dimensional area-wise linear-interpolation between q & depth data points
    // q     = 1
    // depth = 2
    u8 iindex=(u8)frequency_plot_index;

    float frac1_lo=(float)(NUM_QS-1)*Q;
    int index1_lo=(int)frac1_lo;
    int index1_hi=index1_lo+1;
    if (index1_hi>=NUM_QS){
      index1_hi=NUM_QS-1;
    }
    frac1_lo-=(float)index1_lo;
    float frac1_hi=frac1_lo;
    frac1_lo=1.0f-frac1_lo;

    float frac2_lo=(float)(2*NUM_DEPTHS)*depth;
    int index2_lo=(int)frac2_lo;
    int index2_hi=index2_lo+1;
    if (index2_hi>=2*NUM_DEPTHS){
      index2_hi=2*NUM_DEPTHS;
    }
    frac2_lo-=(float)index2_lo;
    float frac2_hi=frac2_lo;
    frac2_lo=1.0f-frac2_lo;

    u8 frac_lo_lo=(u8)(64.0f*frac1_lo*frac2_lo+0.5f);
    u8 frac_hi_lo=(u8)(64.0f*frac1_hi*frac2_lo+0.5f);
    u8 frac_lo_hi=(u8)(64.0f*frac1_lo*frac2_hi+0.5f);
    u8 frac_hi_hi=(u8)(64.0f*frac1_hi*frac2_hi+0.5f);

    bool invert_depth=false;
    if (index2_lo>NUM_DEPTHS){
      index2_lo=2*NUM_DEPTHS-index2_lo;
      invert_depth=true;
    }
    if (index2_hi>NUM_DEPTHS){
      index2_hi=2*NUM_DEPTHS-index2_hi;
      invert_depth=true;
    }


    for(u8 i=0;i<NUM_FOLDED_AVR_UI_XCOORDS;i++){
      s16 x1=iindex+i;
      s16 x2=iindex-i;
      s8 v_lo_lo;
      s8 v_hi_lo;
      if (index2_lo==NUM_DEPTHS){
        v_lo_lo=0;
        v_hi_lo=0;
      }else{
        v_lo_lo=read_folded_preprocessed_AVR_UI_data(index1_lo,index2_lo,i);
        v_hi_lo=read_folded_preprocessed_AVR_UI_data(index1_hi,index2_lo,i);
        if (invert_depth){
          v_lo_lo=-v_lo_lo;
          v_hi_lo=-v_hi_lo;
        }
      }
      s8 v_lo_hi;
      s8 v_hi_hi;
      if (index2_hi==NUM_DEPTHS){
        v_lo_hi=0;
        v_hi_hi=0;
      }else{
        v_lo_hi=read_folded_preprocessed_AVR_UI_data(index1_lo,index2_hi,i);
        v_hi_hi=read_folded_preprocessed_AVR_UI_data(index1_hi,index2_hi,i);
        if (invert_depth){
          v_lo_hi=-v_lo_hi;
          v_hi_hi=-v_hi_hi;
        }
      }
      s16 v_interpolated=(s16)v_lo_lo*(s16)frac_lo_lo + (s16)v_hi_lo*(s16)frac_hi_lo + (s16)v_lo_hi*(s16)frac_lo_hi + (s16)v_hi_hi*(s16)frac_hi_hi;
      if (x1<GRAPH_WIDTH){
        assert(x1>=0 && x1<GRAPH_WIDTH);
        assert(x1<GRAPH_WIDTH);
        assert(v_interpolated<16384);
        write_and_scale_transfer_fn(x1,v_interpolated);
//        transfer_function[x1]=v_interpolated;
        if (v_interpolated!=0){
          non_zero_graph_index_en=(u8)x1;
        }
      }else{
        non_zero_graph_index_en=GRAPH_WIDTH-1;
      }
      if (x2>=0 && x2<GRAPH_WIDTH && x1!=x2){
        assert(x2>=0);
        assert(x2<GRAPH_WIDTH);
        assert(v_interpolated<16384);
        write_and_scale_transfer_fn(x2,v_interpolated);
        if (v_interpolated!=0){
          non_zero_graph_index_st=(u8)x2;
        }
      }
    }
  }
  for(u8 i=non_zero_graph_index_st;i<=non_zero_graph_index_en;i++){
    total_transfer_function[i]+=transfer_function[i]<<6;
  }
}

#define POTENTIOMETER_READING_DEPTH_STAGE_DISABLED 511
#define POTENTIOMETER_READING_FREQ_STAGE_DISABLED 511
#define POTENTIOMETER_READING_Q_STAGE_DISABLED 511

void update_graph(){
  memset(total_transfer_function,0,sizeof(total_transfer_function));
  for(u8 i=0;i<NUM_PEQS;i++){
    bool recalc;
    if (stage_enabled[i]){
      u8 j=i*3;
      recalc=metaldt_peqs[i].set_centre_frequency(potentiometer_analog_reading[PEQ_1_FREQ+j]);
      recalc|=metaldt_peqs[i].set_depth(potentiometer_analog_reading[PEQ_1_depth+j]);
      recalc|=metaldt_peqs[i].set_q(potentiometer_analog_reading[PEQ_1_Q+j]);
    }else{
      recalc=metaldt_peqs[i].set_centre_frequency(POTENTIOMETER_READING_FREQ_STAGE_DISABLED);
      recalc|=metaldt_peqs[i].set_depth(POTENTIOMETER_READING_DEPTH_STAGE_DISABLED);
      recalc|=metaldt_peqs[i].set_q(POTENTIOMETER_READING_Q_STAGE_DISABLED);
    }
    metaldt_peqs[i].update_transfer_fn(recalc);
  }
  static u8 flippy=1;
  if (--flippy==0){
    flippy=7;
    redraw_info_text();
  }
}





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

#if WINDOWS_DEBUG_DISPLAY==1

void dot_vline(u8 x,u8 y,u8 h);
void dot_hline(u8 x,u8 y,u8 w);

char yaxis_keytext[YAXIS_TICKS][4]={"+30","+25","+20","+15","+10"," +5","dB0"," -5","-10","-15","-20","-25","-30"};
u16 xaxis_ticks[]={10,20,30,40,50,75,100,200,300,400,500,750,1000,2000,3000,4000,5000,7500,10000,20000};
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

void draw_graph(){
  u8 yt=128;
  update_graph();

#if WINDOWS_DEBUG_DISPLAY==1
  if (once){
    preprocess_and_save=true;
    for(int i=0;i<GRAPH_WIDTH;i++){
      prepro_pixels[i].clear();
    }

    gcol=grey34_cr;
    //  hline_preprocess(0,0,127);
    //  hline_preprocess(0,159,127);
    //  vline(0,159,159);
    //  vline(127,159,159);
    gcol=COL_AXIS;
//    hline_preprocess(GRAPH_STARTX,GRAPH_STARTY+GRAPH_HALF_HEIGHT,GRAPH_WIDTH-1);
//    vline(GRAPH_STARTX-1,GRAPH_STARTY+GRAPH_HALF_HEIGHT*2+1,GRAPH_HALF_HEIGHT*2+2);
    u8 ystep;
    u8 x=0;
    u8 y;

    y=GRAPH_STARTY+GRAPH_HALF_HEIGHT+1;
    for(u8 i=0;i<nxat;i++){
      u16 f=xaxis_ticks[i];
      u8 x=(u8)get_plot_index_offset((float)f);
      char *str=0;
      gcol=COL_N;
      switch(f){
      case 10:gcol=black_cr;str="10";break;
      case 100:gcol=COL_100;str="100";break;
      case 1000:gcol=COL_100;str="1k";break;
      case 10000:gcol=COL_100;str="10k";break;
      }
      if (str){
        print_pretty_byte(x+13,y+2,str,COL_AXIS_KEY,COL_AXIS_KEY,COL_AXIS_KEY2);
      }
    }

    for(u8 i=0;i<nxat;i++){
      u16 f=xaxis_ticks[i];
      u8 x=(u8)get_plot_index_offset((float)f);
      gcol=COL_N;
      switch(f){
      case 10:gcol=black_cr;break;
      case 50:gcol=COL_50;break;
      case 100:gcol=COL_100;break;
      case 500:gcol=COL_50;break;
      case 1000:gcol=COL_100;break;
      case 5000:gcol=COL_50;break;
      case 10000:gcol=COL_100;break;
      }
      dot_vline(GRAPH_STARTX+x,GRAPH_STARTY,GRAPH_HALF_HEIGHT*2);
    }

    ystep=2*GRAPH_HALF_HEIGHT/(YAXIS_TICKS-1);
    x=0;
    y=GRAPH_STARTY-2;
    for(u8 yi=0;yi<YAXIS_TICKS;yi++){
      print_pretty_byte(x,y,yaxis_keytext[yi],COL_AXIS,yi==GRAPH_INDEX_0?grey80_cr:COL_AXIS_KEY,yi>GRAPH_INDEX_0?COL_AXIS_KEY2:COL_AXIS_KEY3);
      gcol=COL_AXIS;
      prepro_pixels[GRAPH_STARTX-2].push_back(preprocessed_pixels(y+2,gcol));
      if (yi==GRAPH_INDEX_0){
        gcol=grey35_cr;
      }else{
        gcol=COL_HGRID_LINES;
      }
      dot_hline(GRAPH_STARTX,y+2,GRAPH_WIDTH);
      y+=ystep;
    }

    gcol=white_cr;
    y=GRAPH_STARTY+GRAPH_HALF_HEIGHT+1;
    for(u8 i=0;i<GRAPH_WIDTH;i++){
      u16 f=xaxis_ticks[i];
      if (once){
        _cprintf("%d,%20.20lf\n",i,EXPFN(LOGFN(10.0)+LOGFN(20000.0/10.0)*(double)i/(double)(GRAPH_WIDTH-1)));
      }
    }


    y=INFO_TEXT_START_Y-29;
    print_pretty_byte(PRINT_X_FREQ +8,y,"FOUR-STAGE PARAMETRIC EQUALIZER",PRINT_INFO_TITLE_COL ,PRINT_INFO_TITLE_COL,PRINT_INFO_TITLE_COL);
    y+=7;
    print_pretty_byte(PRINT_X_FREQ +14,y,"METALDT ACTIVE FILTER STAGES:",PRINT_INFO_TITLE2_COL ,PRINT_INFO_TITLE2_COL,PRINT_INFO_TITLE2_COL);
    y+=8;

    print_pretty_byte(PRINT_X_FREQ +7,y,"FREQUENCY",PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL ,PRINT_INFO_FREQ_COL );
    print_pretty_byte(PRINT_X_DEPTH+7,y,"DEPTH"    ,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);
    y+=6;
    print_pretty_byte(PRINT_X_FREQ +7,y,"(HZ)",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
    print_pretty_byte(PRINT_X_Q    +7,y,"STAGE Q"  ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    ,PRINT_INFO_Q_COL    );
    print_pretty_byte(PRINT_X_DEPTH+7,y,"(DB)",PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL,PRINT_INFO_DEPTH_COL);
//    print_pretty_byte(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y++,"FREQUENCY",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
//    print_pretty_byte(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y,"HZ",PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL,PRINT_INFO_FREQ_COL);
//    print_int(PRINT_X_Q+PRINT_DIGI_POT_OFFSET,y,donkeys);
//    plot_numbert_float(PRINT_X_Q     ,y,Q ,lightblue2_cr,false);


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
    for(u8 peqi=0;peqi<NUM_PEQS;peqi++){
      which_peq_to_redraw_info_for=1<<peqi;
      which_peq_part_to_redraw_info_for=7;
      for(u8 i=0;i<3;i++){
        redraw_info_text();
      }
    }

  }

  for(u8 i=0;i<GRAPH_WIDTH;i++){
    u8 y=GRAPH_STARTY+GRAPH_HALF_HEIGHT-(u8)((((GRAPH_HALF_HEIGHT*(s32)total_transfer_function[i])/MAX_dBs)+128)>>8);
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

#define AUTO_WIGGLE 0
#if AUTO_WIGGLE==1
  static u8 bendy=3;
  static s8 dbend=17;
  if (((u32)rand()*100)/(u32)RAND_MAX<7){
    bendy=3+(u8)(((u32)rand()*9)/(u32)RAND_MAX);
  }
  potentiometer_analog_reading[bendy]+=dbend;
  if (potentiometer_analog_reading[bendy]>1023){
    potentiometer_analog_reading[bendy]=1023;
    dbend=-dbend;
  }
  if (potentiometer_analog_reading[bendy]<0){
    potentiometer_analog_reading[bendy]=0;
    dbend=-dbend;
  }
#endif
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




*/


