

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

void dot_vline(u8 x,u8 y,u8 h);
void dot_hline(u8 x,u8 y,u8 w);
void plot_numbert_float(u8 orig_x,u8 &y,float n,COLORREF col2,bool int_if_less_than_1000=false);


char yaxis_keytext[YAXIS_TICKS][4]={"+30","+25","+20","+15","+10"," +5","dB0"," -5","-10","-15","-20","-25","-30"};

#define LOGFN(a) log(a)
#define EXPFN(a) exp(a)
u16 xaxis_ticks[]={10,20,30,40,50,75,100,200,300,400,500,750,1000,2000,3000,4000,5000,7500,10000,20000};
u8 nxat=sizeof(xaxis_ticks)/sizeof(*xaxis_ticks);
float xoffset=LOGFN((float)xaxis_ticks[0]);
float plot_scale=(float)(GRAPH_WIDTH-1)/(LOGFN((float)xaxis_ticks[nxat-1])-xoffset);

float get_plot_index_offset(float frequency){
  // determine index of transfer_fn graph from frequency
  float x=(LOGFN(frequency)-xoffset)*plot_scale;
  return x;
}


//f q d
s16 potentiometer_analog_reading[NUM_POTENTIOMETERS]={
  0   ,0   ,0  ,
  500 ,511 ,700  ,
  250   ,0   ,130,
  1023 ,511 ,0
};


u8 metaldt_peq::yoffset_peq_singleton=0;

metaldt_peq metaldt_peqs[NUM_PEQS]={
  metaldt_peq(0, 0.0f, 0.0f, 0.0f),
  metaldt_peq(0, 0.0f, 0.0f, 0.0f),
  metaldt_peq(1, 0.0f, 0.0f, 0.0f),
  metaldt_peq(1, 0.0f, 0.0f, 0.0f),
};


void metaldt_peq::set_centre_frequency(float linear_curve_potentiometer_reading_normalized){
  // linearize the setting of the digital potentiometer so that log(centre frequency) varies in linear proportion to the potentiometer setting
  // determine desired frequency
  //  pot_reading=POT_SMOOTH_ALPHA*pot_reading+(1.0f-POT_SMOOTH_ALPHA)*linear_curve_potentiometer_reading_normalized;
  pot_reading=linear_curve_potentiometer_reading_normalized;
  float fs=read_centre_frequencies_from_LTspice_simulation(frequency_curve,0);
  float fe=read_centre_frequencies_from_LTspice_simulation(frequency_curve,10);
  float fr=EXPFN(LOGFN(fs)+LOGFN(fe/fs)*pot_reading);
  //  smoothed_centre_frequency=POT_SMOOTH_ALPHA*smoothed_centre_frequency+(1.0f-POT_SMOOTH_ALPHA)*fr;
  smoothed_centre_frequency=fr;
  // determine normalized digital potentiometer fraction by determining the real index value in the centre_frequencies_from_LTspice_simulation
  //  float index=get_plot_index_offset(fr);
  //  gcol=black_cr;
  //  p((u8)index+GRAPH_STARTX-1,GRAPH_STARTY+1+yoffset_peq);
  //  p((u8)index+GRAPH_STARTX+1,GRAPH_STARTY+1+yoffset_peq);
  //  gcol=white_cr;
  //  p((u8)index+GRAPH_STARTX,GRAPH_STARTY+1+yoffset_peq);
  //  int rt=1;
}



void metaldt_peq::set_depth(float linear_curve_potentiometer_reading_normalized){
  // linearize the setting of the digital potentiometer so that log(centre frequency) varies in linear proportion to the potentiometer setting
  // determine desired frequency
  //  pot_reading=POT_SMOOTH_ALPHA*pot_reading+(1.0f-POT_SMOOTH_ALPHA)*linear_curve_potentiometer_reading_normalized;
  smoothed_depth=linear_curve_potentiometer_reading_normalized;
}



void metaldt_peq::set_q(float linear_curve_potentiometer_reading_normalized){
  // linearize the setting of the digital potentiometer so that log(centre frequency) varies in linear proportion to the potentiometer setting
  // determine desired frequency
  //  pot_reading=POT_SMOOTH_ALPHA*pot_reading+(1.0f-POT_SMOOTH_ALPHA)*linear_curve_potentiometer_reading_normalized;
  smoothed_Q=linear_curve_potentiometer_reading_normalized;
}


void pp(u8 x,u8 y){
  gcol=black_cr;
  y=GRAPH_STARTY+GRAPH_HALF_HEIGHT-y;
  x+=GRAPH_STARTX;
  s16 ym6=(s16)y-6;
  if (ym6<0){
    ym6=0;
  }
  s16 yp6=(s16)y+6;
  if (yp6>GRAPH_HALF_HEIGHT*2-1){
    yp6=GRAPH_HALF_HEIGHT*2-1;
  }
  vline(x,(u8)yp6,(u8)(yp6-ym6));
  gcol=white_cr;
  p(x,y);
}


u8 last_y_plotted[GRAPH_WIDTH];
s16 total_transfer_function[GRAPH_WIDTH];

u8 y_coords[GRAPH_WIDTH*3];
u8 *pixels[GRAPH_WIDTH];




void metaldt_peq::update_transfer_fn(){
  if (last_smoothed_centre_frequency!=smoothed_centre_frequency || last_smoothed_Q!=smoothed_Q || last_smoothed_depth!=smoothed_depth){
    float index=get_plot_index_offset(smoothed_centre_frequency);
    float st_xfrac=index-(float)(int)index;
    float en_xfrac=1.0f-st_xfrac;

    // 2 dimensional area-wise linear-interpolation between q & depth data points
    // q     = 1
    // depth = 2
    u8 iindex=(u8)index;

    float frac1_lo=(float)(NUM_QS-1)*smoothed_Q;
    int index1_lo=(int)frac1_lo;
    int index1_hi=index1_lo+1;
    if (index1_hi>=NUM_QS){
      index1_hi=NUM_QS-1;
    }
    frac1_lo-=(float)index1_lo;
    float frac1_hi=frac1_lo;
    frac1_lo=1.0f-frac1_lo;

    float frac2_lo=(float)(2*NUM_DEPTHS)*smoothed_depth;
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
        transfer_function[x1]=v_interpolated;
        if (v_interpolated!=0){
          non_zero_graph_index_en=x1;
        }
      }
      if (x2>=0 && x2<GRAPH_WIDTH && x1!=x2){
        assert(x2>=0);
        assert(x2<GRAPH_WIDTH);
        assert(v_interpolated<16384);
        transfer_function[x2]=v_interpolated;
        if (v_interpolated!=0){
          non_zero_graph_index_st=x2;
        }
      }
    }
//    non_zero_graph_index_st=iindex-(NUM_FOLDED_AVR_UI_XCOORDS-1);
//    non_zero_graph_index_en=iindex+(NUM_FOLDED_AVR_UI_XCOORDS-1);
//    if (non_zero_graph_index_st<0) non_zero_graph_index_st=0;
//    if (non_zero_graph_index_en>=GRAPH_WIDTH) non_zero_graph_index_en=GRAPH_WIDTH-1;
  }
  for(u8 i=non_zero_graph_index_st;i<=non_zero_graph_index_en;i++){
    total_transfer_function[i]+=transfer_function[i];
  }
  last_smoothed_centre_frequency=smoothed_centre_frequency;
  last_smoothed_Q               =smoothed_Q;               
  last_smoothed_depth           =smoothed_depth;           
}


void update_graph(){
  memset(total_transfer_function,0,sizeof(total_transfer_function));
  metaldt_peqs[0].set_centre_frequency((float)potentiometer_analog_reading[PEQ_1_FREQ]/1023.0f);
  metaldt_peqs[0].set_depth((float)potentiometer_analog_reading[PEQ_1_depth]/1023.0f);
  metaldt_peqs[0].set_q((float)potentiometer_analog_reading[PEQ_1_Q]/1023.0f);
  metaldt_peqs[0].update_transfer_fn();

  metaldt_peqs[1].set_centre_frequency((float)potentiometer_analog_reading[PEQ_2_FREQ]/1023.0f);
  metaldt_peqs[1].set_depth((float)potentiometer_analog_reading[PEQ_2_depth]/1023.0f);
  metaldt_peqs[1].set_q((float)potentiometer_analog_reading[PEQ_2_Q]/1023.0f);
  metaldt_peqs[1].update_transfer_fn();

  metaldt_peqs[2].set_centre_frequency((float)potentiometer_analog_reading[PEQ_3_FREQ]/1023.0f);
  metaldt_peqs[2].set_depth((float)potentiometer_analog_reading[PEQ_3_depth]/1023.0f);
  metaldt_peqs[2].set_q((float)potentiometer_analog_reading[PEQ_3_Q]/1023.0f);
  metaldt_peqs[2].update_transfer_fn();

  metaldt_peqs[3].set_centre_frequency((float)potentiometer_analog_reading[PEQ_4_FREQ]/1023.0f);
  metaldt_peqs[3].set_depth((float)potentiometer_analog_reading[PEQ_4_depth]/1023.0f);
  metaldt_peqs[3].set_q((float)potentiometer_analog_reading[PEQ_4_Q]/1023.0f);
  metaldt_peqs[3].update_transfer_fn();

//  char rtt[64];
//  sprintf(rtt,"1:f=%d q=%d d=%d     ",potentiometer_analog_reading[PEQ_1_FREQ],potentiometer_analog_reading[PEQ_1_Q],potentiometer_analog_reading[PEQ_1_depth]);
//  print_pretty_byte(20,138,rtt,white_cr,white_cr,white_cr);
#define PRINT_INFO_COL_TXT goldenrod1_cr
#define PRINT_INFO_COL_NUM goldenrod_cr
#define PRINT_INFO_COL_SYM goldenrod2_cr
#define PRINT_SPACING 44
#define PRINT_X_FREQ 8
#define PRINT_X_Q (PRINT_X_FREQ+PRINT_SPACING)
#define PRINT_X_DEPTH (PRINT_X_FREQ+PRINT_SPACING*2)
  u8 y=136;
//  for(u8 i=0;i<NUM_PEQS;i++){
//    plot_numbert_float(PRINT_X_FREQ  ,y,metaldt_peqs[i].smoothed_centre_frequency ,goldenrod1_cr,false);y-=LINE_HEIGHT;
//    plot_numbert_float(PRINT_X_Q     ,y,metaldt_peqs[i].smoothed_Q                ,lightblue2_cr,false);y-=LINE_HEIGHT;
//    plot_numbert_float(PRINT_X_DEPTH ,y,metaldt_peqs[i].smoothed_depth            ,magenta2_cr,false);
//  }
}


#if WINDOWS_DEBUG_DISPLAY==1

void hline_preprocess(u8 x,u8 y,u8 w){
  for(u8 i=x;i<=x+w;i++){
    pigsmells[i].push_back(preprocessed_pixels(y,gcol));
//    p(i,y);
  }
}

// delete lines from being rendered
void hline_clr(u8 x,u8 y,u8 w){
  gcol=black_cr;
  for(u8 i=x;i<=x+w;i++){
    u32 j=0;
    while(j<pigsmells[i].size()){
      if (pigsmells[i][j].y==y){
        pigsmells[i].erase(pigsmells[i].begin()+j);
      }else{
        j++;
      }
    }
//    p(i,y);
  }
}

void vline_preprocess(u8 x,u8 y,u8 h){
  for(u8 i=y;i<=y+h;i++){
    pigsmells[x].push_back(preprocessed_pixels(i,gcol));
//    p(x,i);
  }
}



void dot_vline(u8 x,u8 y,u8 h){
  h+=y;
  while(y<=h){
    pigsmells[x].push_back(preprocessed_pixels(y,gcol));
//    p(x,y);
    y+=2;
  }
}

void dot_hline(u8 x,u8 y,u8 w){
  w+=y;
  while(x<=w){
    pigsmells[x].push_back(preprocessed_pixels(y,gcol));
//    p(x,y);
    x+=2;
  }
}

vector<preprocessed_pixels> pigsmells[DISPLAY_WIDTH];
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
      pigsmells[i].clear();
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
      pigsmells[GRAPH_STARTX-2].push_back(preprocessed_pixels(y+2,gcol));
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

    once=false;
    preprocess_and_save=false;


    ///////////////////////////////////// preprocess //////////////////////////////////////
    // remove duplicate coords
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      vector<preprocessed_pixels> &pp=pigsmells[x];
      sort(pp.begin(),pp.end());
      pp.erase(unique(pp.begin(),pp.end()),pp.end());
    }
    preprocessed_index_num=0;
    preprocessed_num_gcols=0;
    memset(preprocessed_x_index,0,sizeof(preprocessed_x_index));
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      vector<preprocessed_pixels> &pp=pigsmells[x];
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
      vector<preprocessed_pixels> &pp=pigsmells[x];
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

    fprintf_s(fp,"PROGMEM uint32_t preprocessed_gcols[%d]={\n  ",preprocessed_num_gcols);
    dc=false;
    for(u8 x=0;x<preprocessed_num_gcols;x++){
      if (dc) fprintf_s(fp,",");
      fprintf_s(fp,"0x%06X",preprocessed_gcols[x]);
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

  if (initial_render){
    initial_render=false;
    u16 st_ind=0;
    for(u8 x=0;x<DISPLAY_WIDTH;x++){
      u16 en_ind=pgm_read_word_near(preprocessed_x_index+x);
      for(u16 j=st_ind;j<en_ind;j+=2){
        u8 y=pgm_read_byte_near(preprocessed_pix_data+j);
        u8 gcol_index=pgm_read_byte_near(preprocessed_pix_data+j+1);
        gcol=pgm_read_dword_near(preprocessed_gcols+gcol_index);
        p(x,y);
      }
      st_ind=en_ind;
    }
  }

  for(u8 i=0;i<GRAPH_WIDTH;i++){
    u8 y=GRAPH_STARTY+GRAPH_HALF_HEIGHT-(u8)((((GRAPH_HALF_HEIGHT*(s32)total_transfer_function[i])/MAX_dBs)+128)>>8);
    u8 ytest=last_y_plotted[i];
    if (y!=ytest){
      u8 x=i+GRAPH_STARTX;
      bool need_clear=true;
      u16 st_ind=0;
      if (x>0){
        st_ind=pgm_read_word_near(preprocessed_x_index+x-1);
      }
      u16 en_ind=pgm_read_word_near(preprocessed_x_index+x);
      for(u16 j=st_ind;j<en_ind;j+=2){
        u8 ye=pgm_read_byte_near(preprocessed_pix_data+j);
        if (ye==ytest){
          u8 gcol_index=pgm_read_byte_near(preprocessed_pix_data+j+1);
          gcol=pgm_read_dword_near(preprocessed_gcols+gcol_index);
          p(x,ye);
          need_clear=false;
          break;
        }
      }
      if (need_clear){
        gcol=black_cr;
        p(x,ytest);
      }
      gcol=white_cr;
      p(x,y);
      last_y_plotted[i]=y;
    }
  }

  static u8 bendy=3;
  static s8 dbend=17;
  if (((u32)rand()*100)/(u32)RAND_MAX<3){
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
}








void clear_screen(){
  gcol=black_cr;
#define CLEAR_GRANULES 32
  for(u8 yp=0;yp<CLEAR_GRANULES;yp++){
    for(u8 big_y=0;big_y<159;big_y+=CLEAR_GRANULES){
      hline(0,yp+big_y,128);
    }
  }
}






void line(s16 x0, s16 y0, s16 x1, s16 y1) {
  s16 dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  s16 dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  s16 err = (dx>dy ? dx : -dy)/2, e2;

  for(;;){
    p((u8)x0,(u8)y0);
    if (x0==x1 && y0==y1) return;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}



u32 int_part;
void sprintf_positive_float(char* buffer,float n,u8 chars_total,u8 digits_after_dp){
  // lack of formatted float on arduino
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
  print_pretty_byte(orig_x,y,rtt,grey65_cr,col2,green3_cr);y+=LINE_HEIGHT;
}




