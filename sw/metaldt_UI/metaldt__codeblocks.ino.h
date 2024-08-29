// ID of the settings block
#define EEPROM_CONFIG_VERSION "RTT"

// Tell it where to store your config data in EEPROM
#define CONFIG_START 32

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef char s8;
typedef short s16;
typedef long s32;

#ifndef _WINDOWS 
  typedef u16 COLORREF;
  #define pgm_read_COLORREF_near pgm_read_word_near
#endif

class persistent_settings{
public:
  // This is for mere detection if they are your settings
  char version[4];
  // The variables of your settings
  float required_gm_tube_hv;
  float atmega328_external_reference_voltage;
};

#define NUM_SAMPLES_TO_TAKE 50
extern bool need_to_cycle_mode;
extern bool need_to_toggle_func;

extern u8 coil_energise_delay_microseconds;
extern u8 sampling_delay_microseconds;
extern u16 buttholmes_anal_value;

extern persistent_settings settings;
extern u8 display_mode;
extern float required_gm_tube_hv;

#define DISPLAY_MODE_UNMODIFIED_PEQ_SETTINGS 0
#define DISPLAY_MODE_MAIN_CONTROLS 1
#define DISPLAY_MODE_DEBUG_SEE_RAW_PEQ_POT_N_DIGIPOT_SETTINGS 2
#define DISPLAY_MODE_NUM_MODES 3

#define INFO_TEXT_REDRAW_FREQ 1
#define INFO_TEXT_REDRAW_DEPTH 2
#define INFO_TEXT_REDRAW_Q 4

#define DISPLAY_WIDTH 128

#define NUM_POTENTIOMETERS 30
#define NUM_CENTRE_FREQUENCIES 21

#define NUM_HARDWARE_POTENTIOMETER_INPUTS 30

#define PEQ_1_FREQ  0
#define PEQ_1_Q     1
#define PEQ_1_depth 2
#define PEQ_2_FREQ  3
#define PEQ_2_Q     4
#define PEQ_2_depth 5
#define PEQ_3_FREQ  6
#define PEQ_3_Q     7
#define PEQ_3_depth 8
#define PEQ_4_FREQ  9
#define PEQ_4_Q     10
#define PEQ_4_depth 11
#define PEQ_5_FREQ  12
#define PEQ_5_Q     13
#define PEQ_5_depth 14
#define AUX_CONTROL_SUBBASS       15
#define AUX_CONTROL_BASS          16
#define AUX_CONTROL_MID           17
#define AUX_CONTROL_HIGH          18
#define AUX_CONTROL_GAIN          19
#define AUX_CONTROL_BALANCE       20
#define AUX_CONTROL_BASSBALANCE   21
#define AUX_CONTROL_WIDTH         22

#define INPUT_POT_NUMBER_PEQ_1_Q      0
#define INPUT_POT_NUMBER_PEQ_1_FREQ   1
#define INPUT_POT_NUMBER_PEQ_1_depth  2
#define INPUT_POT_NUMBER_PEQ_2_Q      3
#define INPUT_POT_NUMBER_PEQ_2_FREQ   4
#define INPUT_POT_NUMBER_PEQ_2_depth  5
#define INPUT_POT_NUMBER_PEQ_3_Q      6
#define INPUT_POT_NUMBER_PEQ_3_FREQ   7
#define INPUT_POT_NUMBER_PEQ_3_depth  8
#define INPUT_POT_NUMBER_PEQ_4_Q      9
#define INPUT_POT_NUMBER_PEQ_4_FREQ   10
#define INPUT_POT_NUMBER_PEQ_4_depth  11
#define INPUT_POT_NUMBER_ENABLE_PEQ_1              12
#define INPUT_POT_NUMBER_ENABLE_PEQ_2              13
#define INPUT_POT_NUMBER_ENABLE_PEQ_3              14
#define INPUT_POT_NUMBER_ENABLE_PEQ_4              15
#define INPUT_POT_NUMBER_PEQ_5_Q      16
#define INPUT_POT_NUMBER_PEQ_5_FREQ   17
#define INPUT_POT_NUMBER_PEQ_5_depth  18
#define INPUT_POT_NUMBER_ENABLE_PEQ_5              19
#define INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS       20
#define INPUT_POT_NUMBER_AUX_CONTROL_BASS          21
#define INPUT_POT_NUMBER_AUX_CONTROL_MID           22
#define INPUT_POT_NUMBER_AUX_CONTROL_HIGH          23
#define INPUT_POT_NUMBER_AUX_CONTROL_GAIN          24
#define INPUT_POT_NUMBER_AUX_CONTROL_BALANCE       25
#define INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE   26
#define INPUT_POT_NUMBER_AUX_CONTROL_WIDTH         27
#define INPUT_POT_NUMBER_AUX_CONTROL_TOGGLEFUNCS   28
#define INPUT_POT_NUMBER_AUX_CONTROL_MODESELECT    29

//#define DIGITAL_POT_PEQ_1_Q      0
//#define DIGITAL_POT_PEQ_1_FREQ   1
//#define DIGITAL_POT_PEQ_1_depth  2
//#define DIGITAL_POT_PEQ_2_Q      3
//#define DIGITAL_POT_PEQ_2_FREQ   4
//#define DIGITAL_POT_PEQ_2_depth  5
//#define DIGITAL_POT_PEQ_3_Q      6
//#define DIGITAL_POT_PEQ_3_FREQ   7
//#define DIGITAL_POT_PEQ_3_depth  8
//#define DIGITAL_POT_PEQ_4_Q      9
//#define DIGITAL_POT_PEQ_4_FREQ   10
//#define DIGITAL_POT_PEQ_4_depth  11
//#define DIGITAL_POT_PEQ_5_Q      12
//#define DIGITAL_POT_PEQ_5_FREQ   13
//#define DIGITAL_POT_PEQ_5_depth  14
//#define DIGITAL_POT_GAIN_LEFT    15
//#define DIGITAL_POT_GAIN_RIGHT   16
//#define DIGITAL_POT_BASS_LEFT    17
//#define DIGITAL_POT_BASS_RIGHT   18

#define DIGITAL_POT_GAIN_LEFT    0
#define DIGITAL_POT_GAIN_RIGHT   1
#define DIGITAL_POT_PEQ_1_Q      2
#define DIGITAL_POT_PEQ_1_FREQ   3
#define DIGITAL_POT_PEQ_1_depth  4
#define DIGITAL_POT_PEQ_2_Q      5
#define DIGITAL_POT_PEQ_2_FREQ   6
#define DIGITAL_POT_PEQ_2_depth  7
#define DIGITAL_POT_PEQ_3_Q      8
#define DIGITAL_POT_PEQ_3_FREQ   9
#define DIGITAL_POT_PEQ_3_depth  10
#define DIGITAL_POT_PEQ_4_Q      11
#define DIGITAL_POT_PEQ_4_FREQ   12
#define DIGITAL_POT_PEQ_4_depth  13
#define DIGITAL_POT_PEQ_5_Q      14
#define DIGITAL_POT_PEQ_5_FREQ   15
#define DIGITAL_POT_PEQ_5_depth  16
#define DIGITAL_POT_BASS_LEFT    17
#define DIGITAL_POT_BASS_RIGHT   18


#define CONTROL_CHANGE_AMMOUNT_THRESHOLD 2
#define SLEEP_UPDATE_OUTPUT_LINE_WIDTH 255

extern u8 sleep_update_outputs;  // potentiometer reading has changed significantly

void RTT_hardware_digi_pot_spi_out(u8 data_byte);
