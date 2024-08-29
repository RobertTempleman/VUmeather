

#define NUM_QS 4
#define NUM_DEPTHS 4
#define NUM_FOLDED_AVR_UI_XCOORDS 69

#define ACTUAL_DEPTH_VALUES (NUM_DEPTHS*2+1)  // because the depth is exactly 0.5 on & symmetrical about the x-axis actual depths is this  

#define GRAPH_STARTX 7
#define GRAPH_WIDTH (128-GRAPH_STARTX) // the width that is updated with the transfer fn.


float read_float_array(float* array,u8 i);
float read_preprocessed_dayturds_float_matrix(u8 Q,u8 depth,u8 index);
float read_centre_frequencies_from_LTspice_simulation(u8 peq,u8 i);
s8 read_folded_preprocessed_AVR_UI_data(u8 q,u8 depth,u8 i);
void redraw_info_text();

extern s8 folded_preprocessed_AVR_UI_data[NUM_QS][NUM_DEPTHS][NUM_FOLDED_AVR_UI_XCOORDS];

extern float depth_potentiometer_values[NUM_DEPTHS*2+1];
extern float stage_depth_in_dBs[ACTUAL_DEPTH_VALUES];
extern float Q_potentiometer_values[NUM_QS];
