#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef _WINDOWS










// Pass 8-bit (each) R,G,B, get back 16-bit packed color
u16 Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


u16 col_trans(u32 col_in){
  u8 r=(u8)col_in;
  u8 g=(u8)(col_in>>8);
  u8 b=(u8)(col_in>>16);
  return Color565(r,g,b);
}



void trans_cols_to_16buit_for_arduino(){
  FILE*fp;
  fopen_s(&fp,"RTTcolours16bit.h","w");
  fprintf_s(fp,"#define aliceblue_16cr 0x%04x\n",col_trans( 0xfff8f0));
  fprintf_s(fp,"#define antiquewhite_16cr 0x%04x\n",col_trans( 0xd7ebfa));
  fprintf_s(fp,"#define antiquewhite1_16cr 0x%04x\n",col_trans( 0xdbefff));
  fprintf_s(fp,"#define antiquewhite2_16cr 0x%04x\n",col_trans( 0xccdfee));
  fprintf_s(fp,"#define antiquewhite3_16cr 0x%04x\n",col_trans( 0xb0c0cd));
  fprintf_s(fp,"#define antiquewhite4_16cr 0x%04x\n",col_trans( 0x78838b));
  fprintf_s(fp,"#define aquamarine_16cr 0x%04x\n",col_trans( 0xd4ff7f));
  fprintf_s(fp,"#define aquamarine1_16cr 0x%04x\n",col_trans( 0xd4ff7f));
  fprintf_s(fp,"#define aquamarine2_16cr 0x%04x\n",col_trans( 0xc6ee76));
  fprintf_s(fp,"#define aquamarine3_16cr 0x%04x\n",col_trans( 0xaacd66));
  fprintf_s(fp,"#define aquamarine4_16cr 0x%04x\n",col_trans( 0x748b45));
  fprintf_s(fp,"#define azure_16cr 0x%04x\n",col_trans( 0xfffff0));
  fprintf_s(fp,"#define azure1_16cr 0x%04x\n",col_trans( 0xfffff0));
  fprintf_s(fp,"#define azure2_16cr 0x%04x\n",col_trans( 0xeeeee0));
  fprintf_s(fp,"#define azure3_16cr 0x%04x\n",col_trans( 0xcdcdc1));
  fprintf_s(fp,"#define azure4_16cr 0x%04x\n",col_trans( 0x8b8b83));
  fprintf_s(fp,"#define beige_16cr 0x%04x\n",col_trans( 0xdcf5f5));
  fprintf_s(fp,"#define bisque_16cr 0x%04x\n",col_trans( 0xc4e4ff));
  fprintf_s(fp,"#define bisque1_16cr 0x%04x\n",col_trans( 0xc4e4ff));
  fprintf_s(fp,"#define bisque2_16cr 0x%04x\n",col_trans( 0xb7d5ee));
  fprintf_s(fp,"#define bisque3_16cr 0x%04x\n",col_trans( 0x9eb7cd));
  fprintf_s(fp,"#define bisque4_16cr 0x%04x\n",col_trans( 0x6b7d8b));
  fprintf_s(fp,"#define black_16cr 0x%04x\n",col_trans( 0x000000));
  fprintf_s(fp,"#define blanchedalmond_16cr 0x%04x\n",col_trans( 0xcdebff));
  fprintf_s(fp,"#define blue_16cr 0x%04x\n",col_trans( 0xff0000));
  fprintf_s(fp,"#define blue1_16cr 0x%04x\n",col_trans( 0xff0000));
  fprintf_s(fp,"#define blue2_16cr 0x%04x\n",col_trans( 0xee0000));
  fprintf_s(fp,"#define blue3_16cr 0x%04x\n",col_trans( 0xcd0000));
  fprintf_s(fp,"#define blue4_16cr 0x%04x\n",col_trans( 0x8b0000));
  fprintf_s(fp,"#define blueviolet_16cr 0x%04x\n",col_trans( 0xe22b8a));
  fprintf_s(fp,"#define brown_16cr 0x%04x\n",col_trans( 0x2a2aa5));
  fprintf_s(fp,"#define brown1_16cr 0x%04x\n",col_trans( 0x4040ff));
  fprintf_s(fp,"#define brown2_16cr 0x%04x\n",col_trans( 0x3b3bee));
  fprintf_s(fp,"#define brown3_16cr 0x%04x\n",col_trans( 0x3333cd));
  fprintf_s(fp,"#define brown4_16cr 0x%04x\n",col_trans( 0x23238b));
  fprintf_s(fp,"#define burlywood_16cr 0x%04x\n",col_trans( 0x87b8de));
  fprintf_s(fp,"#define burlywood1_16cr 0x%04x\n",col_trans( 0x9bd3ff));
  fprintf_s(fp,"#define burlywood2_16cr 0x%04x\n",col_trans( 0x91c5ee));
  fprintf_s(fp,"#define burlywood3_16cr 0x%04x\n",col_trans( 0x7daacd));
  fprintf_s(fp,"#define burlywood4_16cr 0x%04x\n",col_trans( 0x55738b));
  fprintf_s(fp,"#define cadetblue_16cr 0x%04x\n",col_trans( 0xa09e5f));
  fprintf_s(fp,"#define cadetblue1_16cr 0x%04x\n",col_trans( 0xfff598));
  fprintf_s(fp,"#define cadetblue2_16cr 0x%04x\n",col_trans( 0xeee58e));
  fprintf_s(fp,"#define cadetblue3_16cr 0x%04x\n",col_trans( 0xcdc57a));
  fprintf_s(fp,"#define cadetblue4_16cr 0x%04x\n",col_trans( 0x8b8653));
  fprintf_s(fp,"#define chartreuse_16cr 0x%04x\n",col_trans( 0x00ff7f));
  fprintf_s(fp,"#define chartreuse1_16cr 0x%04x\n",col_trans( 0x00ff7f));
  fprintf_s(fp,"#define chartreuse2_16cr 0x%04x\n",col_trans( 0x00ee76));
  fprintf_s(fp,"#define chartreuse3_16cr 0x%04x\n",col_trans( 0x00cd66));
  fprintf_s(fp,"#define chartreuse4_16cr 0x%04x\n",col_trans( 0x008b45));
  fprintf_s(fp,"#define chocolate_16cr 0x%04x\n",col_trans( 0x1e69d2));
  fprintf_s(fp,"#define chocolate1_16cr 0x%04x\n",col_trans( 0x247fff));
  fprintf_s(fp,"#define chocolate2_16cr 0x%04x\n",col_trans( 0x2176ee));
  fprintf_s(fp,"#define chocolate3_16cr 0x%04x\n",col_trans( 0x1d66cd));
  fprintf_s(fp,"#define chocolate4_16cr 0x%04x\n",col_trans( 0x13458b));
  fprintf_s(fp,"#define coral_16cr 0x%04x\n",col_trans( 0x507fff));
  fprintf_s(fp,"#define coral1_16cr 0x%04x\n",col_trans( 0x5672ff));
  fprintf_s(fp,"#define coral2_16cr 0x%04x\n",col_trans( 0x506aee));
  fprintf_s(fp,"#define coral3_16cr 0x%04x\n",col_trans( 0x455bcd));
  fprintf_s(fp,"#define coral4_16cr 0x%04x\n",col_trans( 0x2f3e8b));
  fprintf_s(fp,"#define cornflowerblue_16cr 0x%04x\n",col_trans( 0xed9564));
  fprintf_s(fp,"#define cornsilk_16cr 0x%04x\n",col_trans( 0xdcf8ff));
  fprintf_s(fp,"#define cornsilk1_16cr 0x%04x\n",col_trans( 0xdcf8ff));
  fprintf_s(fp,"#define cornsilk2_16cr 0x%04x\n",col_trans( 0xcde8ee));
  fprintf_s(fp,"#define cornsilk3_16cr 0x%04x\n",col_trans( 0xb1c8cd));
  fprintf_s(fp,"#define cornsilk4_16cr 0x%04x\n",col_trans( 0x78888b));
  fprintf_s(fp,"#define crimson_16cr 0x%04x\n",col_trans( 0x3C14DC              ));
  fprintf_s(fp,"#define cyan_16cr 0x%04x\n",col_trans( 0xffff00));
  fprintf_s(fp,"#define cyan1_16cr 0x%04x\n",col_trans( 0xffff00));
  fprintf_s(fp,"#define cyan2_16cr 0x%04x\n",col_trans( 0xeeee00));
  fprintf_s(fp,"#define cyan3_16cr 0x%04x\n",col_trans( 0xcdcd00));
  fprintf_s(fp,"#define cyan4_16cr 0x%04x\n",col_trans( 0x8b8b00));
  fprintf_s(fp,"#define darkblue_16cr 0x%04x\n",col_trans( 0x8b0000));
  fprintf_s(fp,"#define darkcyan_16cr 0x%04x\n",col_trans( 0x8b8b00));
  fprintf_s(fp,"#define darkgoldenrod_16cr 0x%04x\n",col_trans( 0x0b86b8));
  fprintf_s(fp,"#define darkgoldenrod1_16cr 0x%04x\n",col_trans( 0x0fb9ff));
  fprintf_s(fp,"#define darkgoldenrod2_16cr 0x%04x\n",col_trans( 0x0eadee));
  fprintf_s(fp,"#define darkgoldenrod3_16cr 0x%04x\n",col_trans( 0x0c95cd));
  fprintf_s(fp,"#define darkgoldenrod4_16cr 0x%04x\n",col_trans( 0x08658b));
  fprintf_s(fp,"#define darkgray_16cr 0x%04x\n",col_trans( 0xa9a9a9));
  fprintf_s(fp,"#define darkgreen_16cr 0x%04x\n",col_trans( 0x006400));
  fprintf_s(fp,"#define darkgrey_16cr 0x%04x\n",col_trans( 0xa9a9a9));
  fprintf_s(fp,"#define darkkhaki_16cr 0x%04x\n",col_trans( 0x6bb7bd));
  fprintf_s(fp,"#define darkmagenta_16cr 0x%04x\n",col_trans( 0x8b008b));
  fprintf_s(fp,"#define darkolivegreen_16cr 0x%04x\n",col_trans( 0x2f6b55));
  fprintf_s(fp,"#define darkolivegreen1_16cr 0x%04x\n",col_trans( 0x70ffca));
  fprintf_s(fp,"#define darkolivegreen2_16cr 0x%04x\n",col_trans( 0x68eebc));
  fprintf_s(fp,"#define darkolivegreen3_16cr 0x%04x\n",col_trans( 0x5acda2));
  fprintf_s(fp,"#define darkolivegreen4_16cr 0x%04x\n",col_trans( 0x3d8b6e));
  fprintf_s(fp,"#define darkorange_16cr 0x%04x\n",col_trans( 0x008cff));
  fprintf_s(fp,"#define darkorange1_16cr 0x%04x\n",col_trans( 0x007fff));
  fprintf_s(fp,"#define darkorange2_16cr 0x%04x\n",col_trans( 0x0076ee));
  fprintf_s(fp,"#define darkorange3_16cr 0x%04x\n",col_trans( 0x0066cd));
  fprintf_s(fp,"#define darkorange4_16cr 0x%04x\n",col_trans( 0x00458b));
  fprintf_s(fp,"#define darkorchid_16cr 0x%04x\n",col_trans( 0xcc3299));
  fprintf_s(fp,"#define darkorchid1_16cr 0x%04x\n",col_trans( 0xff3ebf));
  fprintf_s(fp,"#define darkorchid2_16cr 0x%04x\n",col_trans( 0xee3ab2));
  fprintf_s(fp,"#define darkorchid3_16cr 0x%04x\n",col_trans( 0xcd329a));
  fprintf_s(fp,"#define darkorchid4_16cr 0x%04x\n",col_trans( 0x8b2268));
  fprintf_s(fp,"#define darkred_16cr 0x%04x\n",col_trans( 0x00008b));
  fprintf_s(fp,"#define darksalmon_16cr 0x%04x\n",col_trans( 0x7a96e9));
  fprintf_s(fp,"#define darkseagreen_16cr 0x%04x\n",col_trans( 0x8fbc8f));
  fprintf_s(fp,"#define darkseagreen1_16cr 0x%04x\n",col_trans( 0xc1ffc1));
  fprintf_s(fp,"#define darkseagreen2_16cr 0x%04x\n",col_trans( 0xb4eeb4));
  fprintf_s(fp,"#define darkseagreen3_16cr 0x%04x\n",col_trans( 0x9bcd9b));
  fprintf_s(fp,"#define darkseagreen4_16cr 0x%04x\n",col_trans( 0x698b69));
  fprintf_s(fp,"#define darkslateblue_16cr 0x%04x\n",col_trans( 0x8b3d48));
  fprintf_s(fp,"#define darkslategray_16cr 0x%04x\n",col_trans( 0x4f4f2f));
  fprintf_s(fp,"#define darkslategray1_16cr 0x%04x\n",col_trans( 0xffff97));
  fprintf_s(fp,"#define darkslategray2_16cr 0x%04x\n",col_trans( 0xeeee8d));
  fprintf_s(fp,"#define darkslategray3_16cr 0x%04x\n",col_trans( 0xcdcd79));
  fprintf_s(fp,"#define darkslategray4_16cr 0x%04x\n",col_trans( 0x8b8b52));
  fprintf_s(fp,"#define darkslategrey_16cr 0x%04x\n",col_trans( 0x4f4f2f));
  fprintf_s(fp,"#define darkslategrey1_16cr 0x%04x\n",col_trans( 0xffff97));
  fprintf_s(fp,"#define darkslategrey2_16cr 0x%04x\n",col_trans( 0xeeee8d));
  fprintf_s(fp,"#define darkslategrey3_16cr 0x%04x\n",col_trans( 0xcdcd79));
  fprintf_s(fp,"#define darkslategrey4_16cr 0x%04x\n",col_trans( 0x8b8b52));
  fprintf_s(fp,"#define darkslategrey5_16cr 0x%04x\n",col_trans( 0x666649));
  fprintf_s(fp,"#define darkslategrey6_16cr 0x%04x\n",col_trans( 0x464629));
  fprintf_s(fp,"#define darkslategrey7_16cr 0x%04x\n",col_trans( 0x262617));
  fprintf_s(fp,"#define darkturquoise_16cr 0x%04x\n",col_trans( 0xd1ce00));
  fprintf_s(fp,"#define darkviolet_16cr 0x%04x\n",col_trans( 0xd30094));
  fprintf_s(fp,"#define deeppink_16cr 0x%04x\n",col_trans( 0x9314ff));
  fprintf_s(fp,"#define deeppink1_16cr 0x%04x\n",col_trans( 0x9314ff));
  fprintf_s(fp,"#define deeppink2_16cr 0x%04x\n",col_trans( 0x8912ee));
  fprintf_s(fp,"#define deeppink3_16cr 0x%04x\n",col_trans( 0x7610cd));
  fprintf_s(fp,"#define deeppink4_16cr 0x%04x\n",col_trans( 0x500a8b));
  fprintf_s(fp,"#define deepskyblue_16cr 0x%04x\n",col_trans( 0xffbf00));
  fprintf_s(fp,"#define deepskyblue1_16cr 0x%04x\n",col_trans( 0xffbf00));
  fprintf_s(fp,"#define deepskyblue2_16cr 0x%04x\n",col_trans( 0xeeb200));
  fprintf_s(fp,"#define deepskyblue3_16cr 0x%04x\n",col_trans( 0xcd9a00));
  fprintf_s(fp,"#define deepskyblue4_16cr 0x%04x\n",col_trans( 0x8b6800));
  fprintf_s(fp,"#define dimgray_16cr 0x%04x\n",col_trans( 0x696969));
  fprintf_s(fp,"#define dimgrey_16cr 0x%04x\n",col_trans( 0x696969));
  fprintf_s(fp,"#define dodgerblue_16cr 0x%04x\n",col_trans( 0xff901e));
  fprintf_s(fp,"#define dodgerblue1_16cr 0x%04x\n",col_trans( 0xff901e));
  fprintf_s(fp,"#define dodgerblue2_16cr 0x%04x\n",col_trans( 0xee861c));
  fprintf_s(fp,"#define dodgerblue3_16cr 0x%04x\n",col_trans( 0xcd7418));
  fprintf_s(fp,"#define dodgerblue4_16cr 0x%04x\n",col_trans( 0x8b4e10));
  fprintf_s(fp,"#define firebrick_16cr 0x%04x\n",col_trans( 0x2222b2));
  fprintf_s(fp,"#define firebrick1_16cr 0x%04x\n",col_trans( 0x3030ff));
  fprintf_s(fp,"#define firebrick2_16cr 0x%04x\n",col_trans( 0x2c2cee));
  fprintf_s(fp,"#define firebrick3_16cr 0x%04x\n",col_trans( 0x2626cd));
  fprintf_s(fp,"#define firebrick4_16cr 0x%04x\n",col_trans( 0x1a1a8b));
  fprintf_s(fp,"#define floralwhite_16cr 0x%04x\n",col_trans( 0xf0faff));
  fprintf_s(fp,"#define forestgreen_16cr 0x%04x\n",col_trans( 0x228b22));
  fprintf_s(fp,"#define gainsboro_16cr 0x%04x\n",col_trans( 0xdcdcdc));
  fprintf_s(fp,"#define ghostwhite_16cr 0x%04x\n",col_trans( 0xfff8f8));
  fprintf_s(fp,"#define gold_16cr 0x%04x\n",col_trans( 0x00d7ff));
  fprintf_s(fp,"#define gold1_16cr 0x%04x\n",col_trans( 0x00d7ff));
  fprintf_s(fp,"#define gold2_16cr 0x%04x\n",col_trans( 0x00c9ee));
  fprintf_s(fp,"#define gold3_16cr 0x%04x\n",col_trans( 0x00adcd));
  fprintf_s(fp,"#define gold4_16cr 0x%04x\n",col_trans( 0x00758b));
  fprintf_s(fp,"#define goldenrod_16cr 0x%04x\n",col_trans( 0x20a5da));
  fprintf_s(fp,"#define goldenrod1_16cr 0x%04x\n",col_trans( 0x25c1ff));
  fprintf_s(fp,"#define goldenrod2_16cr 0x%04x\n",col_trans( 0x22b4ee));
  fprintf_s(fp,"#define goldenrod3_16cr 0x%04x\n",col_trans( 0x1d9bcd));
  fprintf_s(fp,"#define goldenrod4_16cr 0x%04x\n",col_trans( 0x14698b));
  fprintf_s(fp,"#define gray_16cr 0x%04x\n",col_trans( 0xbebebe));
  fprintf_s(fp,"#define gray0_16cr 0x%04x\n",col_trans( 0x000000));
  fprintf_s(fp,"#define gray1_16cr 0x%04x\n",col_trans( 0x030303));
  fprintf_s(fp,"#define gray2_16cr 0x%04x\n",col_trans( 0x050505));
  fprintf_s(fp,"#define gray3_16cr 0x%04x\n",col_trans( 0x080808));
  fprintf_s(fp,"#define gray4_16cr 0x%04x\n",col_trans( 0x0a0a0a));
  fprintf_s(fp,"#define gray5_16cr 0x%04x\n",col_trans( 0x0d0d0d));
  fprintf_s(fp,"#define gray6_16cr 0x%04x\n",col_trans( 0x0f0f0f));
  fprintf_s(fp,"#define gray7_16cr 0x%04x\n",col_trans( 0x121212));
  fprintf_s(fp,"#define gray8_16cr 0x%04x\n",col_trans( 0x141414));
  fprintf_s(fp,"#define gray9_16cr 0x%04x\n",col_trans( 0x171717));
  fprintf_s(fp,"#define gray10_16cr 0x%04x\n",col_trans( 0x1a1a1a));
  fprintf_s(fp,"#define gray11_16cr 0x%04x\n",col_trans( 0x1c1c1c));
  fprintf_s(fp,"#define gray12_16cr 0x%04x\n",col_trans( 0x1f1f1f));
  fprintf_s(fp,"#define gray13_16cr 0x%04x\n",col_trans( 0x212121));
  fprintf_s(fp,"#define gray14_16cr 0x%04x\n",col_trans( 0x242424));
  fprintf_s(fp,"#define gray15_16cr 0x%04x\n",col_trans( 0x262626));
  fprintf_s(fp,"#define gray16_16cr 0x%04x\n",col_trans( 0x292929));
  fprintf_s(fp,"#define gray17_16cr 0x%04x\n",col_trans( 0x2b2b2b));
  fprintf_s(fp,"#define gray18_16cr 0x%04x\n",col_trans( 0x2e2e2e));
  fprintf_s(fp,"#define gray19_16cr 0x%04x\n",col_trans( 0x303030));
  fprintf_s(fp,"#define gray20_16cr 0x%04x\n",col_trans( 0x333333));
  fprintf_s(fp,"#define gray21_16cr 0x%04x\n",col_trans( 0x363636));
  fprintf_s(fp,"#define gray22_16cr 0x%04x\n",col_trans( 0x383838));
  fprintf_s(fp,"#define gray23_16cr 0x%04x\n",col_trans( 0x3b3b3b));
  fprintf_s(fp,"#define gray24_16cr 0x%04x\n",col_trans( 0x3d3d3d));
  fprintf_s(fp,"#define gray25_16cr 0x%04x\n",col_trans( 0x404040));
  fprintf_s(fp,"#define gray26_16cr 0x%04x\n",col_trans( 0x424242));
  fprintf_s(fp,"#define gray27_16cr 0x%04x\n",col_trans( 0x454545));
  fprintf_s(fp,"#define gray28_16cr 0x%04x\n",col_trans( 0x474747));
  fprintf_s(fp,"#define gray29_16cr 0x%04x\n",col_trans( 0x4a4a4a));
  fprintf_s(fp,"#define gray30_16cr 0x%04x\n",col_trans( 0x4d4d4d));
  fprintf_s(fp,"#define gray31_16cr 0x%04x\n",col_trans( 0x4f4f4f));
  fprintf_s(fp,"#define gray32_16cr 0x%04x\n",col_trans( 0x525252));
  fprintf_s(fp,"#define gray33_16cr 0x%04x\n",col_trans( 0x545454));
  fprintf_s(fp,"#define gray34_16cr 0x%04x\n",col_trans( 0x575757));
  fprintf_s(fp,"#define gray35_16cr 0x%04x\n",col_trans( 0x595959));
  fprintf_s(fp,"#define gray36_16cr 0x%04x\n",col_trans( 0x5c5c5c));
  fprintf_s(fp,"#define gray37_16cr 0x%04x\n",col_trans( 0x5e5e5e));
  fprintf_s(fp,"#define gray38_16cr 0x%04x\n",col_trans( 0x616161));
  fprintf_s(fp,"#define gray39_16cr 0x%04x\n",col_trans( 0x636363));
  fprintf_s(fp,"#define gray40_16cr 0x%04x\n",col_trans( 0x666666));
  fprintf_s(fp,"#define gray41_16cr 0x%04x\n",col_trans( 0x696969));
  fprintf_s(fp,"#define gray42_16cr 0x%04x\n",col_trans( 0x6b6b6b));
  fprintf_s(fp,"#define gray43_16cr 0x%04x\n",col_trans( 0x6e6e6e));
  fprintf_s(fp,"#define gray44_16cr 0x%04x\n",col_trans( 0x707070));
  fprintf_s(fp,"#define gray45_16cr 0x%04x\n",col_trans( 0x737373));
  fprintf_s(fp,"#define gray46_16cr 0x%04x\n",col_trans( 0x757575));
  fprintf_s(fp,"#define gray47_16cr 0x%04x\n",col_trans( 0x787878));
  fprintf_s(fp,"#define gray48_16cr 0x%04x\n",col_trans( 0x7a7a7a));
  fprintf_s(fp,"#define gray49_16cr 0x%04x\n",col_trans( 0x7d7d7d));
  fprintf_s(fp,"#define gray50_16cr 0x%04x\n",col_trans( 0x7f7f7f));
  fprintf_s(fp,"#define gray51_16cr 0x%04x\n",col_trans( 0x828282));
  fprintf_s(fp,"#define gray52_16cr 0x%04x\n",col_trans( 0x858585));
  fprintf_s(fp,"#define gray53_16cr 0x%04x\n",col_trans( 0x878787));
  fprintf_s(fp,"#define gray54_16cr 0x%04x\n",col_trans( 0x8a8a8a));
  fprintf_s(fp,"#define gray55_16cr 0x%04x\n",col_trans( 0x8c8c8c));
  fprintf_s(fp,"#define gray56_16cr 0x%04x\n",col_trans( 0x8f8f8f));
  fprintf_s(fp,"#define gray57_16cr 0x%04x\n",col_trans( 0x919191));
  fprintf_s(fp,"#define gray58_16cr 0x%04x\n",col_trans( 0x949494));
  fprintf_s(fp,"#define gray59_16cr 0x%04x\n",col_trans( 0x969696));
  fprintf_s(fp,"#define gray60_16cr 0x%04x\n",col_trans( 0x999999));
  fprintf_s(fp,"#define gray61_16cr 0x%04x\n",col_trans( 0x9c9c9c));
  fprintf_s(fp,"#define gray62_16cr 0x%04x\n",col_trans( 0x9e9e9e));
  fprintf_s(fp,"#define gray63_16cr 0x%04x\n",col_trans( 0xa1a1a1));
  fprintf_s(fp,"#define gray64_16cr 0x%04x\n",col_trans( 0xa3a3a3));
  fprintf_s(fp,"#define gray65_16cr 0x%04x\n",col_trans( 0xa6a6a6));
  fprintf_s(fp,"#define gray66_16cr 0x%04x\n",col_trans( 0xa8a8a8));
  fprintf_s(fp,"#define gray67_16cr 0x%04x\n",col_trans( 0xababab));
  fprintf_s(fp,"#define gray68_16cr 0x%04x\n",col_trans( 0xadadad));
  fprintf_s(fp,"#define gray69_16cr 0x%04x\n",col_trans( 0xb0b0b0));
  fprintf_s(fp,"#define gray70_16cr 0x%04x\n",col_trans( 0xb3b3b3));
  fprintf_s(fp,"#define gray71_16cr 0x%04x\n",col_trans( 0xb5b5b5));
  fprintf_s(fp,"#define gray72_16cr 0x%04x\n",col_trans( 0xb8b8b8));
  fprintf_s(fp,"#define gray73_16cr 0x%04x\n",col_trans( 0xbababa));
  fprintf_s(fp,"#define gray74_16cr 0x%04x\n",col_trans( 0xbdbdbd));
  fprintf_s(fp,"#define gray75_16cr 0x%04x\n",col_trans( 0xbfbfbf));
  fprintf_s(fp,"#define gray76_16cr 0x%04x\n",col_trans( 0xc2c2c2));
  fprintf_s(fp,"#define gray77_16cr 0x%04x\n",col_trans( 0xc4c4c4));
  fprintf_s(fp,"#define gray78_16cr 0x%04x\n",col_trans( 0xc7c7c7));
  fprintf_s(fp,"#define gray79_16cr 0x%04x\n",col_trans( 0xc9c9c9));
  fprintf_s(fp,"#define gray80_16cr 0x%04x\n",col_trans( 0xcccccc));
  fprintf_s(fp,"#define gray81_16cr 0x%04x\n",col_trans( 0xcfcfcf));
  fprintf_s(fp,"#define gray82_16cr 0x%04x\n",col_trans( 0xd1d1d1));
  fprintf_s(fp,"#define gray83_16cr 0x%04x\n",col_trans( 0xd4d4d4));
  fprintf_s(fp,"#define gray84_16cr 0x%04x\n",col_trans( 0xd6d6d6));
  fprintf_s(fp,"#define gray85_16cr 0x%04x\n",col_trans( 0xd9d9d9));
  fprintf_s(fp,"#define gray86_16cr 0x%04x\n",col_trans( 0xdbdbdb));
  fprintf_s(fp,"#define gray87_16cr 0x%04x\n",col_trans( 0xdedede));
  fprintf_s(fp,"#define gray88_16cr 0x%04x\n",col_trans( 0xe0e0e0));
  fprintf_s(fp,"#define gray89_16cr 0x%04x\n",col_trans( 0xe3e3e3));
  fprintf_s(fp,"#define gray90_16cr 0x%04x\n",col_trans( 0xe5e5e5));
  fprintf_s(fp,"#define gray91_16cr 0x%04x\n",col_trans( 0xe8e8e8));
  fprintf_s(fp,"#define gray92_16cr 0x%04x\n",col_trans( 0xebebeb));
  fprintf_s(fp,"#define gray93_16cr 0x%04x\n",col_trans( 0xededed));
  fprintf_s(fp,"#define gray94_16cr 0x%04x\n",col_trans( 0xf0f0f0));
  fprintf_s(fp,"#define gray95_16cr 0x%04x\n",col_trans( 0xf2f2f2));
  fprintf_s(fp,"#define gray96_16cr 0x%04x\n",col_trans( 0xf5f5f5));
  fprintf_s(fp,"#define gray97_16cr 0x%04x\n",col_trans( 0xf7f7f7));
  fprintf_s(fp,"#define gray98_16cr 0x%04x\n",col_trans( 0xfafafa));
  fprintf_s(fp,"#define gray99_16cr 0x%04x\n",col_trans( 0xfcfcfc));
  fprintf_s(fp,"#define gray100_16cr 0x%04x\n",col_trans( 0xffffff));
  fprintf_s(fp,"#define green_16cr 0x%04x\n",col_trans( 0x00ff00));
  fprintf_s(fp,"#define green1_16cr 0x%04x\n",col_trans( 0x00ff00));
  fprintf_s(fp,"#define green2_16cr 0x%04x\n",col_trans( 0x00ee00));
  fprintf_s(fp,"#define green3_16cr 0x%04x\n",col_trans( 0x00cd00));
  fprintf_s(fp,"#define green4_16cr 0x%04x\n",col_trans( 0x008b00));
  fprintf_s(fp,"#define green5_16cr 0x%04x\n",col_trans( 0x006b00));
  fprintf_s(fp,"#define green6_16cr 0x%04x\n",col_trans( 0x004b00));
  fprintf_s(fp,"#define green7_16cr 0x%04x\n",col_trans( 0x002b00));
  fprintf_s(fp,"#define green8_16cr 0x%04x\n",col_trans( 0x001800));
  fprintf_s(fp,"#define green9_16cr 0x%04x\n",col_trans( 0x000800));
  fprintf_s(fp,"#define greenyellow_16cr 0x%04x\n",col_trans( 0x2fffad));
  fprintf_s(fp,"#define grey_16cr 0x%04x\n",col_trans( 0xbebebe));
  fprintf_s(fp,"#define grey0_16cr 0x%04x\n",col_trans( 0x000000));
  fprintf_s(fp,"#define grey1_16cr 0x%04x\n",col_trans( 0x030303));
  fprintf_s(fp,"#define grey2_16cr 0x%04x\n",col_trans( 0x050505));
  fprintf_s(fp,"#define grey3_16cr 0x%04x\n",col_trans( 0x080808));
  fprintf_s(fp,"#define grey4_16cr 0x%04x\n",col_trans( 0x0a0a0a));
  fprintf_s(fp,"#define grey5_16cr 0x%04x\n",col_trans( 0x0d0d0d));
  fprintf_s(fp,"#define grey6_16cr 0x%04x\n",col_trans( 0x0f0f0f));
  fprintf_s(fp,"#define grey7_16cr 0x%04x\n",col_trans( 0x121212));
  fprintf_s(fp,"#define grey8_16cr 0x%04x\n",col_trans( 0x141414));
  fprintf_s(fp,"#define grey9_16cr 0x%04x\n",col_trans( 0x171717));
  fprintf_s(fp,"#define grey10_16cr 0x%04x\n",col_trans( 0x1a1a1a));
  fprintf_s(fp,"#define grey11_16cr 0x%04x\n",col_trans( 0x1c1c1c));
  fprintf_s(fp,"#define grey12_16cr 0x%04x\n",col_trans( 0x1f1f1f));
  fprintf_s(fp,"#define grey13_16cr 0x%04x\n",col_trans( 0x212121));
  fprintf_s(fp,"#define grey14_16cr 0x%04x\n",col_trans( 0x242424));
  fprintf_s(fp,"#define grey15_16cr 0x%04x\n",col_trans( 0x262626));
  fprintf_s(fp,"#define grey16_16cr 0x%04x\n",col_trans( 0x292929));
  fprintf_s(fp,"#define grey17_16cr 0x%04x\n",col_trans( 0x2b2b2b));
  fprintf_s(fp,"#define grey18_16cr 0x%04x\n",col_trans( 0x2e2e2e));
  fprintf_s(fp,"#define grey19_16cr 0x%04x\n",col_trans( 0x303030));
  fprintf_s(fp,"#define grey20_16cr 0x%04x\n",col_trans( 0x333333));
  fprintf_s(fp,"#define grey21_16cr 0x%04x\n",col_trans( 0x363636));
  fprintf_s(fp,"#define grey22_16cr 0x%04x\n",col_trans( 0x383838));
  fprintf_s(fp,"#define grey23_16cr 0x%04x\n",col_trans( 0x3b3b3b));
  fprintf_s(fp,"#define grey24_16cr 0x%04x\n",col_trans( 0x3d3d3d));
  fprintf_s(fp,"#define grey25_16cr 0x%04x\n",col_trans( 0x404040));
  fprintf_s(fp,"#define grey26_16cr 0x%04x\n",col_trans( 0x424242));
  fprintf_s(fp,"#define grey27_16cr 0x%04x\n",col_trans( 0x454545));
  fprintf_s(fp,"#define grey28_16cr 0x%04x\n",col_trans( 0x474747));
  fprintf_s(fp,"#define grey29_16cr 0x%04x\n",col_trans( 0x4a4a4a));
  fprintf_s(fp,"#define grey30_16cr 0x%04x\n",col_trans( 0x4d4d4d));
  fprintf_s(fp,"#define grey31_16cr 0x%04x\n",col_trans( 0x4f4f4f));
  fprintf_s(fp,"#define grey32_16cr 0x%04x\n",col_trans( 0x525252));
  fprintf_s(fp,"#define grey33_16cr 0x%04x\n",col_trans( 0x545454));
  fprintf_s(fp,"#define grey34_16cr 0x%04x\n",col_trans( 0x575757));
  fprintf_s(fp,"#define grey35_16cr 0x%04x\n",col_trans( 0x595959));
  fprintf_s(fp,"#define grey36_16cr 0x%04x\n",col_trans( 0x5c5c5c));
  fprintf_s(fp,"#define grey37_16cr 0x%04x\n",col_trans( 0x5e5e5e));
  fprintf_s(fp,"#define grey38_16cr 0x%04x\n",col_trans( 0x616161));
  fprintf_s(fp,"#define grey39_16cr 0x%04x\n",col_trans( 0x636363));
  fprintf_s(fp,"#define grey40_16cr 0x%04x\n",col_trans( 0x666666));
  fprintf_s(fp,"#define grey41_16cr 0x%04x\n",col_trans( 0x696969));
  fprintf_s(fp,"#define grey42_16cr 0x%04x\n",col_trans( 0x6b6b6b));
  fprintf_s(fp,"#define grey43_16cr 0x%04x\n",col_trans( 0x6e6e6e));
  fprintf_s(fp,"#define grey44_16cr 0x%04x\n",col_trans( 0x707070));
  fprintf_s(fp,"#define grey45_16cr 0x%04x\n",col_trans( 0x737373));
  fprintf_s(fp,"#define grey46_16cr 0x%04x\n",col_trans( 0x757575));
  fprintf_s(fp,"#define grey47_16cr 0x%04x\n",col_trans( 0x787878));
  fprintf_s(fp,"#define grey48_16cr 0x%04x\n",col_trans( 0x7a7a7a));
  fprintf_s(fp,"#define grey49_16cr 0x%04x\n",col_trans( 0x7d7d7d));
  fprintf_s(fp,"#define grey50_16cr 0x%04x\n",col_trans( 0x7f7f7f));
  fprintf_s(fp,"#define grey51_16cr 0x%04x\n",col_trans( 0x828282));
  fprintf_s(fp,"#define grey52_16cr 0x%04x\n",col_trans( 0x858585));
  fprintf_s(fp,"#define grey53_16cr 0x%04x\n",col_trans( 0x878787));
  fprintf_s(fp,"#define grey54_16cr 0x%04x\n",col_trans( 0x8a8a8a));
  fprintf_s(fp,"#define grey55_16cr 0x%04x\n",col_trans( 0x8c8c8c));
  fprintf_s(fp,"#define grey56_16cr 0x%04x\n",col_trans( 0x8f8f8f));
  fprintf_s(fp,"#define grey57_16cr 0x%04x\n",col_trans( 0x919191));
  fprintf_s(fp,"#define grey58_16cr 0x%04x\n",col_trans( 0x949494));
  fprintf_s(fp,"#define grey59_16cr 0x%04x\n",col_trans( 0x969696));
  fprintf_s(fp,"#define grey60_16cr 0x%04x\n",col_trans( 0x999999));
  fprintf_s(fp,"#define grey61_16cr 0x%04x\n",col_trans( 0x9c9c9c));
  fprintf_s(fp,"#define grey62_16cr 0x%04x\n",col_trans( 0x9e9e9e));
  fprintf_s(fp,"#define grey63_16cr 0x%04x\n",col_trans( 0xa1a1a1));
  fprintf_s(fp,"#define grey64_16cr 0x%04x\n",col_trans( 0xa3a3a3));
  fprintf_s(fp,"#define grey65_16cr 0x%04x\n",col_trans( 0xa6a6a6));
  fprintf_s(fp,"#define grey66_16cr 0x%04x\n",col_trans( 0xa8a8a8));
  fprintf_s(fp,"#define grey67_16cr 0x%04x\n",col_trans( 0xababab));
  fprintf_s(fp,"#define grey68_16cr 0x%04x\n",col_trans( 0xadadad));
  fprintf_s(fp,"#define grey69_16cr 0x%04x\n",col_trans( 0xb0b0b0));
  fprintf_s(fp,"#define grey70_16cr 0x%04x\n",col_trans( 0xb3b3b3));
  fprintf_s(fp,"#define grey71_16cr 0x%04x\n",col_trans( 0xb5b5b5));
  fprintf_s(fp,"#define grey72_16cr 0x%04x\n",col_trans( 0xb8b8b8));
  fprintf_s(fp,"#define grey73_16cr 0x%04x\n",col_trans( 0xbababa));
  fprintf_s(fp,"#define grey74_16cr 0x%04x\n",col_trans( 0xbdbdbd));
  fprintf_s(fp,"#define grey75_16cr 0x%04x\n",col_trans( 0xbfbfbf));
  fprintf_s(fp,"#define grey76_16cr 0x%04x\n",col_trans( 0xc2c2c2));
  fprintf_s(fp,"#define grey77_16cr 0x%04x\n",col_trans( 0xc4c4c4));
  fprintf_s(fp,"#define grey78_16cr 0x%04x\n",col_trans( 0xc7c7c7));
  fprintf_s(fp,"#define grey79_16cr 0x%04x\n",col_trans( 0xc9c9c9));
  fprintf_s(fp,"#define grey80_16cr 0x%04x\n",col_trans( 0xcccccc));
  fprintf_s(fp,"#define grey81_16cr 0x%04x\n",col_trans( 0xcfcfcf));
  fprintf_s(fp,"#define grey82_16cr 0x%04x\n",col_trans( 0xd1d1d1));
  fprintf_s(fp,"#define grey83_16cr 0x%04x\n",col_trans( 0xd4d4d4));
  fprintf_s(fp,"#define grey84_16cr 0x%04x\n",col_trans( 0xd6d6d6));
  fprintf_s(fp,"#define grey85_16cr 0x%04x\n",col_trans( 0xd9d9d9));
  fprintf_s(fp,"#define grey86_16cr 0x%04x\n",col_trans( 0xdbdbdb));
  fprintf_s(fp,"#define grey87_16cr 0x%04x\n",col_trans( 0xdedede));
  fprintf_s(fp,"#define grey88_16cr 0x%04x\n",col_trans( 0xe0e0e0));
  fprintf_s(fp,"#define grey89_16cr 0x%04x\n",col_trans( 0xe3e3e3));
  fprintf_s(fp,"#define grey90_16cr 0x%04x\n",col_trans( 0xe5e5e5));
  fprintf_s(fp,"#define grey91_16cr 0x%04x\n",col_trans( 0xe8e8e8));
  fprintf_s(fp,"#define grey92_16cr 0x%04x\n",col_trans( 0xebebeb));
  fprintf_s(fp,"#define grey93_16cr 0x%04x\n",col_trans( 0xededed));
  fprintf_s(fp,"#define grey94_16cr 0x%04x\n",col_trans( 0xf0f0f0));
  fprintf_s(fp,"#define grey95_16cr 0x%04x\n",col_trans( 0xf2f2f2));
  fprintf_s(fp,"#define grey96_16cr 0x%04x\n",col_trans( 0xf5f5f5));
  fprintf_s(fp,"#define grey97_16cr 0x%04x\n",col_trans( 0xf7f7f7));
  fprintf_s(fp,"#define grey98_16cr 0x%04x\n",col_trans( 0xfafafa));
  fprintf_s(fp,"#define grey99_16cr 0x%04x\n",col_trans( 0xfcfcfc));
  fprintf_s(fp,"#define grey100_16cr 0x%04x\n",col_trans( 0xffffff));
  fprintf_s(fp,"#define honeydew_16cr 0x%04x\n",col_trans( 0xf0fff0));
  fprintf_s(fp,"#define honeydew1_16cr 0x%04x\n",col_trans( 0xf0fff0));
  fprintf_s(fp,"#define honeydew2_16cr 0x%04x\n",col_trans( 0xe0eee0));
  fprintf_s(fp,"#define honeydew3_16cr 0x%04x\n",col_trans( 0xc1cdc1));
  fprintf_s(fp,"#define honeydew4_16cr 0x%04x\n",col_trans( 0x838b83));
  fprintf_s(fp,"#define hotpink_16cr 0x%04x\n",col_trans( 0xb469ff));
  fprintf_s(fp,"#define hotpink1_16cr 0x%04x\n",col_trans( 0xb46eff));
  fprintf_s(fp,"#define hotpink2_16cr 0x%04x\n",col_trans( 0xa76aee));
  fprintf_s(fp,"#define hotpink3_16cr 0x%04x\n",col_trans( 0x9060cd));
  fprintf_s(fp,"#define hotpink4_16cr 0x%04x\n",col_trans( 0x623a8b));
  fprintf_s(fp,"#define indianred_16cr 0x%04x\n",col_trans( 0x5c5ccd));
  fprintf_s(fp,"#define indianred1_16cr 0x%04x\n",col_trans( 0x6a6aff));
  fprintf_s(fp,"#define indianred2_16cr 0x%04x\n",col_trans( 0x6363ee));
  fprintf_s(fp,"#define indianred3_16cr 0x%04x\n",col_trans( 0x5555cd));
  fprintf_s(fp,"#define indianred4_16cr 0x%04x\n",col_trans( 0x3a3a8b));
  fprintf_s(fp,"#define ivory_16cr 0x%04x\n",col_trans( 0xf0ffff));
  fprintf_s(fp,"#define ivory1_16cr 0x%04x\n",col_trans( 0xf0ffff));
  fprintf_s(fp,"#define ivory2_16cr 0x%04x\n",col_trans( 0xe0eeee));
  fprintf_s(fp,"#define ivory3_16cr 0x%04x\n",col_trans( 0xc1cdcd));
  fprintf_s(fp,"#define ivory4_16cr 0x%04x\n",col_trans( 0x838b8b));
  fprintf_s(fp,"#define khaki_16cr 0x%04x\n",col_trans( 0x8ce6f0));
  fprintf_s(fp,"#define khaki1_16cr 0x%04x\n",col_trans( 0x8ff6ff));
  fprintf_s(fp,"#define khaki2_16cr 0x%04x\n",col_trans( 0x85e6ee));
  fprintf_s(fp,"#define khaki3_16cr 0x%04x\n",col_trans( 0x73c6cd));
  fprintf_s(fp,"#define khaki4_16cr 0x%04x\n",col_trans( 0x4e868b));
  fprintf_s(fp,"#define lavender_16cr 0x%04x\n",col_trans( 0xfae6e6));
  fprintf_s(fp,"#define lavenderblush_16cr 0x%04x\n",col_trans( 0xf5f0ff));
  fprintf_s(fp,"#define lavenderblush1_16cr 0x%04x\n",col_trans( 0xf5f0ff));
  fprintf_s(fp,"#define lavenderblush2_16cr 0x%04x\n",col_trans( 0xe5e0ee));
  fprintf_s(fp,"#define lavenderblush3_16cr 0x%04x\n",col_trans( 0xc5c1cd));
  fprintf_s(fp,"#define lavenderblush4_16cr 0x%04x\n",col_trans( 0x86838b));
  fprintf_s(fp,"#define lawngreen_16cr 0x%04x\n",col_trans( 0x00fc7c));
  fprintf_s(fp,"#define lemonchiffon_16cr 0x%04x\n",col_trans( 0xcdfaff));
  fprintf_s(fp,"#define lemonchiffon1_16cr 0x%04x\n",col_trans( 0xcdfaff));
  fprintf_s(fp,"#define lemonchiffon2_16cr 0x%04x\n",col_trans( 0xbfe9ee));
  fprintf_s(fp,"#define lemonchiffon3_16cr 0x%04x\n",col_trans( 0xa5c9cd));
  fprintf_s(fp,"#define lemonchiffon4_16cr 0x%04x\n",col_trans( 0x70898b));
  fprintf_s(fp,"#define lightblue_16cr 0x%04x\n",col_trans( 0xe6d8ad));
  fprintf_s(fp,"#define lightblue1_16cr 0x%04x\n",col_trans( 0xffefbf));
  fprintf_s(fp,"#define lightblue2_16cr 0x%04x\n",col_trans( 0xeedfb2));
  fprintf_s(fp,"#define lightblue3_16cr 0x%04x\n",col_trans( 0xcdc09a));
  fprintf_s(fp,"#define lightblue4_16cr 0x%04x\n",col_trans( 0x8b8368));
  fprintf_s(fp,"#define lightcoral_16cr 0x%04x\n",col_trans( 0x8080f0));
  fprintf_s(fp,"#define lightcyan_16cr 0x%04x\n",col_trans( 0xffffe0));
  fprintf_s(fp,"#define lightcyan1_16cr 0x%04x\n",col_trans( 0xffffe0));
  fprintf_s(fp,"#define lightcyan2_16cr 0x%04x\n",col_trans( 0xeeeed1));
  fprintf_s(fp,"#define lightcyan3_16cr 0x%04x\n",col_trans( 0xcdcdb4));
  fprintf_s(fp,"#define lightcyan4_16cr 0x%04x\n",col_trans( 0x8b8b7a));
  fprintf_s(fp,"#define lightgoldenrod_16cr 0x%04x\n",col_trans( 0x82ddee));
  fprintf_s(fp,"#define lightgoldenrod1_16cr 0x%04x\n",col_trans( 0x8becff));
  fprintf_s(fp,"#define lightgoldenrod2_16cr 0x%04x\n",col_trans( 0x82dcee));
  fprintf_s(fp,"#define lightgoldenrod3_16cr 0x%04x\n",col_trans( 0x70becd));
  fprintf_s(fp,"#define lightgoldenrod4_16cr 0x%04x\n",col_trans( 0x4c818b));
  fprintf_s(fp,"#define lightgoldenrodyellow_16cr 0x%04x\n",col_trans( 0xd2fafa));
  fprintf_s(fp,"#define lightgray_16cr 0x%04x\n",col_trans( 0xd3d3d3));
  fprintf_s(fp,"#define lightgreen_16cr 0x%04x\n",col_trans( 0x90ee90));
  fprintf_s(fp,"#define lightgrey_16cr 0x%04x\n",col_trans( 0xd3d3d3));
  fprintf_s(fp,"#define lightpink_16cr 0x%04x\n",col_trans( 0xc1b6ff));
  fprintf_s(fp,"#define lightpink1_16cr 0x%04x\n",col_trans( 0xb9aeff));
  fprintf_s(fp,"#define lightpink2_16cr 0x%04x\n",col_trans( 0xada2ee));
  fprintf_s(fp,"#define lightpink3_16cr 0x%04x\n",col_trans( 0x958ccd));
  fprintf_s(fp,"#define lightpink4_16cr 0x%04x\n",col_trans( 0x655f8b));
  fprintf_s(fp,"#define lightsalmon_16cr 0x%04x\n",col_trans( 0x7aa0ff));
  fprintf_s(fp,"#define lightsalmon1_16cr 0x%04x\n",col_trans( 0x7aa0ff));
  fprintf_s(fp,"#define lightsalmon2_16cr 0x%04x\n",col_trans( 0x7295ee));
  fprintf_s(fp,"#define lightsalmon3_16cr 0x%04x\n",col_trans( 0x6281cd));
  fprintf_s(fp,"#define lightsalmon4_16cr 0x%04x\n",col_trans( 0x42578b));
  fprintf_s(fp,"#define lightseagreen_16cr 0x%04x\n",col_trans( 0xaab220));
  fprintf_s(fp,"#define lightskyblue_16cr 0x%04x\n",col_trans( 0xface87));
  fprintf_s(fp,"#define lightskyblue1_16cr 0x%04x\n",col_trans( 0xffe2b0));
  fprintf_s(fp,"#define lightskyblue2_16cr 0x%04x\n",col_trans( 0xeed3a4));
  fprintf_s(fp,"#define lightskyblue3_16cr 0x%04x\n",col_trans( 0xcdb68d));
  fprintf_s(fp,"#define lightskyblue4_16cr 0x%04x\n",col_trans( 0x8b7b60));
  fprintf_s(fp,"#define lightslateblue_16cr 0x%04x\n",col_trans( 0xff7084));
  fprintf_s(fp,"#define lightslategray_16cr 0x%04x\n",col_trans( 0x998877));
  fprintf_s(fp,"#define lightslategrey_16cr 0x%04x\n",col_trans( 0x998877));
  fprintf_s(fp,"#define lightsteelblue_16cr 0x%04x\n",col_trans( 0xdec4b0));
  fprintf_s(fp,"#define lightsteelblue1_16cr 0x%04x\n",col_trans( 0xffe1ca));
  fprintf_s(fp,"#define lightsteelblue2_16cr 0x%04x\n",col_trans( 0xeed2bc));
  fprintf_s(fp,"#define lightsteelblue3_16cr 0x%04x\n",col_trans( 0xcdb5a2));
  fprintf_s(fp,"#define lightsteelblue4_16cr 0x%04x\n",col_trans( 0x8b7b6e));
  fprintf_s(fp,"#define lightyellow_16cr 0x%04x\n",col_trans( 0xe0ffff));
  fprintf_s(fp,"#define lightyellow1_16cr 0x%04x\n",col_trans( 0xe0ffff));
  fprintf_s(fp,"#define lightyellow2_16cr 0x%04x\n",col_trans( 0xd1eeee));
  fprintf_s(fp,"#define lightyellow3_16cr 0x%04x\n",col_trans( 0xb4cdcd));
  fprintf_s(fp,"#define lightyellow4_16cr 0x%04x\n",col_trans( 0x7a8b8b));
  fprintf_s(fp,"#define limegreen_16cr 0x%04x\n",col_trans( 0x32cd32));
  fprintf_s(fp,"#define linen_16cr 0x%04x\n",col_trans( 0xe6f0fa));
  fprintf_s(fp,"#define magenta_16cr 0x%04x\n",col_trans( 0xff00ff));
  fprintf_s(fp,"#define magenta1_16cr 0x%04x\n",col_trans( 0xff00ff));
  fprintf_s(fp,"#define magenta2_16cr 0x%04x\n",col_trans( 0xee00ee));
  fprintf_s(fp,"#define magenta3_16cr 0x%04x\n",col_trans( 0xcd00cd));
  fprintf_s(fp,"#define magenta4_16cr 0x%04x\n",col_trans( 0x8b008b));
  fprintf_s(fp,"#define maroon_16cr 0x%04x\n",col_trans( 0x6030b0));
  fprintf_s(fp,"#define maroon1_16cr 0x%04x\n",col_trans( 0xb334ff));
  fprintf_s(fp,"#define maroon2_16cr 0x%04x\n",col_trans( 0xa730ee));
  fprintf_s(fp,"#define maroon3_16cr 0x%04x\n",col_trans( 0x9029cd));
  fprintf_s(fp,"#define maroon4_16cr 0x%04x\n",col_trans( 0x621c8b));
  fprintf_s(fp,"#define mediumaquamarine_16cr 0x%04x\n",col_trans( 0xaacd66));
  fprintf_s(fp,"#define mediumblue_16cr 0x%04x\n",col_trans( 0xcd0000));
  fprintf_s(fp,"#define mediumorchid_16cr 0x%04x\n",col_trans( 0xd355ba));
  fprintf_s(fp,"#define mediumorchid1_16cr 0x%04x\n",col_trans( 0xff66e0));
  fprintf_s(fp,"#define mediumorchid2_16cr 0x%04x\n",col_trans( 0xee5fd1));
  fprintf_s(fp,"#define mediumorchid3_16cr 0x%04x\n",col_trans( 0xcd52b4));
  fprintf_s(fp,"#define mediumorchid4_16cr 0x%04x\n",col_trans( 0x8b377a));
  fprintf_s(fp,"#define mediumpurple_16cr 0x%04x\n",col_trans( 0xdb7093));
  fprintf_s(fp,"#define mediumpurple1_16cr 0x%04x\n",col_trans( 0xff82ab));
  fprintf_s(fp,"#define mediumpurple2_16cr 0x%04x\n",col_trans( 0xee799f));
  fprintf_s(fp,"#define mediumpurple3_16cr 0x%04x\n",col_trans( 0xcd6889));
  fprintf_s(fp,"#define mediumpurple4_16cr 0x%04x\n",col_trans( 0x8b475d));
  fprintf_s(fp,"#define mediumseagreen_16cr 0x%04x\n",col_trans( 0x71b33c));
  fprintf_s(fp,"#define mediumslateblue_16cr 0x%04x\n",col_trans( 0xee687b));
  fprintf_s(fp,"#define mediumspringgreen_16cr 0x%04x\n",col_trans( 0x9afa00));
  fprintf_s(fp,"#define mediumturquoise_16cr 0x%04x\n",col_trans( 0xccd148));
  fprintf_s(fp,"#define mediumvioletred_16cr 0x%04x\n",col_trans( 0x8515c7));
  fprintf_s(fp,"#define midnightblue_16cr 0x%04x\n",col_trans( 0x701919));
  fprintf_s(fp,"#define mintcream_16cr 0x%04x\n",col_trans( 0xfafff5));
  fprintf_s(fp,"#define mistyrose_16cr 0x%04x\n",col_trans( 0xe1e4ff));
  fprintf_s(fp,"#define mistyrose1_16cr 0x%04x\n",col_trans( 0xe1e4ff));
  fprintf_s(fp,"#define mistyrose2_16cr 0x%04x\n",col_trans( 0xd2d5ee));
  fprintf_s(fp,"#define mistyrose3_16cr 0x%04x\n",col_trans( 0xb5b7cd));
  fprintf_s(fp,"#define mistyrose4_16cr 0x%04x\n",col_trans( 0x7b7d8b));
  fprintf_s(fp,"#define moccasin_16cr 0x%04x\n",col_trans( 0xb5e4ff));
  fprintf_s(fp,"#define navajowhite_16cr 0x%04x\n",col_trans( 0xaddeff));
  fprintf_s(fp,"#define navajowhite1_16cr 0x%04x\n",col_trans( 0xaddeff));
  fprintf_s(fp,"#define navajowhite2_16cr 0x%04x\n",col_trans( 0xa1cfee));
  fprintf_s(fp,"#define navajowhite3_16cr 0x%04x\n",col_trans( 0x8bb3cd));
  fprintf_s(fp,"#define navajowhite4_16cr 0x%04x\n",col_trans( 0x5e798b));
  fprintf_s(fp,"#define navy_16cr 0x%04x\n",col_trans( 0x800000));
  fprintf_s(fp,"#define navyblue_16cr 0x%04x\n",col_trans( 0x800000));
  fprintf_s(fp,"#define oldlace_16cr 0x%04x\n",col_trans( 0xe6f5fd));
  fprintf_s(fp,"#define olivedrab_16cr 0x%04x\n",col_trans( 0x238e6b));
  fprintf_s(fp,"#define olivedrab1_16cr 0x%04x\n",col_trans( 0x3effc0));
  fprintf_s(fp,"#define olivedrab2_16cr 0x%04x\n",col_trans( 0x3aeeb3));
  fprintf_s(fp,"#define olivedrab3_16cr 0x%04x\n",col_trans( 0x32cd9a));
  fprintf_s(fp,"#define olivedrab4_16cr 0x%04x\n",col_trans( 0x228b69));
  fprintf_s(fp,"#define orange0_16cr 0x%04x\n",col_trans( 0x00c5ff));
  fprintf_s(fp,"#define orange_16cr 0x%04x\n",col_trans( 0x00a5ff));
  fprintf_s(fp,"#define orange1_16cr 0x%04x\n",col_trans( 0x00a5ff));
  fprintf_s(fp,"#define orange2_16cr 0x%04x\n",col_trans( 0x009aee));
  fprintf_s(fp,"#define orange3_16cr 0x%04x\n",col_trans( 0x0085cd));
  fprintf_s(fp,"#define orange4_16cr 0x%04x\n",col_trans( 0x005a8b));
  fprintf_s(fp,"#define orangered_16cr 0x%04x\n",col_trans( 0x0045ff));
  fprintf_s(fp,"#define orangered1_16cr 0x%04x\n",col_trans( 0x0045ff));
  fprintf_s(fp,"#define orangered2_16cr 0x%04x\n",col_trans( 0x0040ee));
  fprintf_s(fp,"#define orangered3_16cr 0x%04x\n",col_trans( 0x0037cd));
  fprintf_s(fp,"#define orangered4_16cr 0x%04x\n",col_trans( 0x00258b));
  fprintf_s(fp,"#define orchid_16cr 0x%04x\n",col_trans( 0xd670da));
  fprintf_s(fp,"#define orchid1_16cr 0x%04x\n",col_trans( 0xfa83ff));
  fprintf_s(fp,"#define orchid2_16cr 0x%04x\n",col_trans( 0xe97aee));
  fprintf_s(fp,"#define orchid3_16cr 0x%04x\n",col_trans( 0xc969cd));
  fprintf_s(fp,"#define orchid4_16cr 0x%04x\n",col_trans( 0x89478b));
  fprintf_s(fp,"#define palegoldenrod_16cr 0x%04x\n",col_trans( 0xaae8ee));
  fprintf_s(fp,"#define palegreen_16cr 0x%04x\n",col_trans( 0x98fb98));
  fprintf_s(fp,"#define palegreen1_16cr 0x%04x\n",col_trans( 0x9aff9a));
  fprintf_s(fp,"#define palegreen2_16cr 0x%04x\n",col_trans( 0x90ee90));
  fprintf_s(fp,"#define palegreen3_16cr 0x%04x\n",col_trans( 0x7ccd7c));
  fprintf_s(fp,"#define palegreen4_16cr 0x%04x\n",col_trans( 0x548b54));
  fprintf_s(fp,"#define paleturquoise_16cr 0x%04x\n",col_trans( 0xeeeeaf));
  fprintf_s(fp,"#define paleturquoise1_16cr 0x%04x\n",col_trans( 0xffffbb));
  fprintf_s(fp,"#define paleturquoise2_16cr 0x%04x\n",col_trans( 0xeeeeae));
  fprintf_s(fp,"#define paleturquoise3_16cr 0x%04x\n",col_trans( 0xcdcd96));
  fprintf_s(fp,"#define paleturquoise4_16cr 0x%04x\n",col_trans( 0x8b8b66));
  fprintf_s(fp,"#define palevioletred_16cr 0x%04x\n",col_trans( 0x9370db));
  fprintf_s(fp,"#define palevioletred1_16cr 0x%04x\n",col_trans( 0xab82ff));
  fprintf_s(fp,"#define palevioletred2_16cr 0x%04x\n",col_trans( 0x9f79ee));
  fprintf_s(fp,"#define palevioletred3_16cr 0x%04x\n",col_trans( 0x8968cd));
  fprintf_s(fp,"#define palevioletred4_16cr 0x%04x\n",col_trans( 0x5d478b));
  fprintf_s(fp,"#define papayawhip_16cr 0x%04x\n",col_trans( 0xd5efff));
  fprintf_s(fp,"#define peachpuff_16cr 0x%04x\n",col_trans( 0xb9daff));
  fprintf_s(fp,"#define peachpuff1_16cr 0x%04x\n",col_trans( 0xb9daff));
  fprintf_s(fp,"#define peachpuff2_16cr 0x%04x\n",col_trans( 0xadcbee));
  fprintf_s(fp,"#define peachpuff3_16cr 0x%04x\n",col_trans( 0x95afcd));
  fprintf_s(fp,"#define peachpuff4_16cr 0x%04x\n",col_trans( 0x65778b));
  fprintf_s(fp,"#define peru_16cr 0x%04x\n",col_trans( 0x3f85cd));
  fprintf_s(fp,"#define pink_16cr 0x%04x\n",col_trans( 0xcbc0ff));
  fprintf_s(fp,"#define pink1_16cr 0x%04x\n",col_trans( 0xc5b5ff));
  fprintf_s(fp,"#define pink2_16cr 0x%04x\n",col_trans( 0xb8a9ee));
  fprintf_s(fp,"#define pink3_16cr 0x%04x\n",col_trans( 0x9e91cd));
  fprintf_s(fp,"#define pink4_16cr 0x%04x\n",col_trans( 0x6c638b));
  fprintf_s(fp,"#define plum_16cr 0x%04x\n",col_trans( 0xdda0dd));
  fprintf_s(fp,"#define plum1_16cr 0x%04x\n",col_trans( 0xffbbff));
  fprintf_s(fp,"#define plum2_16cr 0x%04x\n",col_trans( 0xeeaeee));
  fprintf_s(fp,"#define plum3_16cr 0x%04x\n",col_trans( 0xcd96cd));
  fprintf_s(fp,"#define plum4_16cr 0x%04x\n",col_trans( 0x8b668b));
  fprintf_s(fp,"#define powderblue_16cr 0x%04x\n",col_trans( 0xe6e0b0));
  fprintf_s(fp,"#define purple_16cr 0x%04x\n",col_trans( 0xf020a0));
  fprintf_s(fp,"#define purple1_16cr 0x%04x\n",col_trans( 0xff309b));
  fprintf_s(fp,"#define purple2_16cr 0x%04x\n",col_trans( 0xee2c91));
  fprintf_s(fp,"#define purple3_16cr 0x%04x\n",col_trans( 0xcd267d));
  fprintf_s(fp,"#define purple4_16cr 0x%04x\n",col_trans( 0x8b1a55));
  fprintf_s(fp,"#define red_16cr 0x%04x\n",col_trans( 0x0000ff));
  fprintf_s(fp,"#define red1_16cr 0x%04x\n",col_trans( 0x0000ff));
  fprintf_s(fp,"#define red2_16cr 0x%04x\n",col_trans( 0x0000ee));
  fprintf_s(fp,"#define red3_16cr 0x%04x\n",col_trans( 0x0000cd));
  fprintf_s(fp,"#define red4_16cr 0x%04x\n",col_trans( 0x00008b));
  fprintf_s(fp,"#define red5_16cr 0x%04x\n",col_trans( 0x00007b));
  fprintf_s(fp,"#define red6_16cr 0x%04x\n",col_trans( 0x00006b));
  fprintf_s(fp,"#define red7_16cr 0x%04x\n",col_trans( 0x00005b));
  fprintf_s(fp,"#define red8_16cr 0x%04x\n",col_trans( 0x00004b));
  fprintf_s(fp,"#define rosybrown_16cr 0x%04x\n",col_trans( 0x8f8fbc));
  fprintf_s(fp,"#define rosybrown1_16cr 0x%04x\n",col_trans( 0xc1c1ff));
  fprintf_s(fp,"#define rosybrown2_16cr 0x%04x\n",col_trans( 0xb4b4ee));
  fprintf_s(fp,"#define rosybrown3_16cr 0x%04x\n",col_trans( 0x9b9bcd));
  fprintf_s(fp,"#define rosybrown4_16cr 0x%04x\n",col_trans( 0x69698b));
  fprintf_s(fp,"#define royalblue_16cr 0x%04x\n",col_trans( 0xe16941));
  fprintf_s(fp,"#define royalblue1_16cr 0x%04x\n",col_trans( 0xff7648));
  fprintf_s(fp,"#define royalblue2_16cr 0x%04x\n",col_trans( 0xee6e43));
  fprintf_s(fp,"#define royalblue3_16cr 0x%04x\n",col_trans( 0xcd5f3a));
  fprintf_s(fp,"#define royalblue4_16cr 0x%04x\n",col_trans( 0x8b4027));
  fprintf_s(fp,"#define saddlebrown_16cr 0x%04x\n",col_trans( 0x13458b));
  fprintf_s(fp,"#define salmon_16cr 0x%04x\n",col_trans( 0x7280fa));
  fprintf_s(fp,"#define salmon1_16cr 0x%04x\n",col_trans( 0x698cff));
  fprintf_s(fp,"#define salmon2_16cr 0x%04x\n",col_trans( 0x6282ee));
  fprintf_s(fp,"#define salmon3_16cr 0x%04x\n",col_trans( 0x5470cd));
  fprintf_s(fp,"#define salmon4_16cr 0x%04x\n",col_trans( 0x394c8b));
  fprintf_s(fp,"#define sandybrown_16cr 0x%04x\n",col_trans( 0x60a4f4));
  fprintf_s(fp,"#define seagreen_16cr 0x%04x\n",col_trans( 0x578b2e));
  fprintf_s(fp,"#define seagreen1_16cr 0x%04x\n",col_trans( 0x9fff54));
  fprintf_s(fp,"#define seagreen2_16cr 0x%04x\n",col_trans( 0x94ee4e));
  fprintf_s(fp,"#define seagreen3_16cr 0x%04x\n",col_trans( 0x80cd43));
  fprintf_s(fp,"#define seagreen4_16cr 0x%04x\n",col_trans( 0x578b2e));
  fprintf_s(fp,"#define seashell_16cr 0x%04x\n",col_trans( 0xeef5ff));
  fprintf_s(fp,"#define seashell1_16cr 0x%04x\n",col_trans( 0xeef5ff));
  fprintf_s(fp,"#define seashell2_16cr 0x%04x\n",col_trans( 0xdee5ee));
  fprintf_s(fp,"#define seashell3_16cr 0x%04x\n",col_trans( 0xbfc5cd));
  fprintf_s(fp,"#define seashell4_16cr 0x%04x\n",col_trans( 0x82868b));
  fprintf_s(fp,"#define sienna_16cr 0x%04x\n",col_trans( 0x2d52a0));
  fprintf_s(fp,"#define sienna1_16cr 0x%04x\n",col_trans( 0x4782ff));
  fprintf_s(fp,"#define sienna2_16cr 0x%04x\n",col_trans( 0x4279ee));
  fprintf_s(fp,"#define sienna3_16cr 0x%04x\n",col_trans( 0x3968cd));
  fprintf_s(fp,"#define sienna4_16cr 0x%04x\n",col_trans( 0x26478b));
  fprintf_s(fp,"#define skyblue_16cr 0x%04x\n",col_trans( 0xebce87));
  fprintf_s(fp,"#define skyblue1_16cr 0x%04x\n",col_trans( 0xffce87));
  fprintf_s(fp,"#define skyblue2_16cr 0x%04x\n",col_trans( 0xeec07e));
  fprintf_s(fp,"#define skyblue3_16cr 0x%04x\n",col_trans( 0xcda66c));
  fprintf_s(fp,"#define skyblue4_16cr 0x%04x\n",col_trans( 0x8b704a));
  fprintf_s(fp,"#define slateblue_16cr 0x%04x\n",col_trans( 0xcd5a6a));
  fprintf_s(fp,"#define slateblue1_16cr 0x%04x\n",col_trans( 0xff6f83));
  fprintf_s(fp,"#define slateblue2_16cr 0x%04x\n",col_trans( 0xee677a));
  fprintf_s(fp,"#define slateblue3_16cr 0x%04x\n",col_trans( 0xcd5969));
  fprintf_s(fp,"#define slateblue4_16cr 0x%04x\n",col_trans( 0x8b3c47));
  fprintf_s(fp,"#define slategray_16cr 0x%04x\n",col_trans( 0x908070));
  fprintf_s(fp,"#define slategray1_16cr 0x%04x\n",col_trans( 0xffe2c6));
  fprintf_s(fp,"#define slategray2_16cr 0x%04x\n",col_trans( 0xeed3b9));
  fprintf_s(fp,"#define slategray3_16cr 0x%04x\n",col_trans( 0xcdb69f));
  fprintf_s(fp,"#define slategray4_16cr 0x%04x\n",col_trans( 0x8b7b6c));
  fprintf_s(fp,"#define slategrey_16cr 0x%04x\n",col_trans( 0x908070));
  fprintf_s(fp,"#define slategrey1_16cr 0x%04x\n",col_trans( 0xffe2c6));
  fprintf_s(fp,"#define slategrey2_16cr 0x%04x\n",col_trans( 0xeed3b9));
  fprintf_s(fp,"#define slategrey3_16cr 0x%04x\n",col_trans( 0xcdb69f));
  fprintf_s(fp,"#define slategrey4_16cr 0x%04x\n",col_trans( 0x8b7b6c));
  fprintf_s(fp,"#define snow_16cr 0x%04x\n",col_trans( 0xfafaff));
  fprintf_s(fp,"#define snow1_16cr 0x%04x\n",col_trans( 0xfafaff));
  fprintf_s(fp,"#define snow2_16cr 0x%04x\n",col_trans( 0xe9e9ee));
  fprintf_s(fp,"#define snow3_16cr 0x%04x\n",col_trans( 0xc9c9cd));
  fprintf_s(fp,"#define snow4_16cr 0x%04x\n",col_trans( 0x89898b));
  fprintf_s(fp,"#define springgreen_16cr 0x%04x\n",col_trans( 0x7fff00));
  fprintf_s(fp,"#define springgreen1_16cr 0x%04x\n",col_trans( 0x7fff00));
  fprintf_s(fp,"#define springgreen2_16cr 0x%04x\n",col_trans( 0x76ee00));
  fprintf_s(fp,"#define springgreen3_16cr 0x%04x\n",col_trans( 0x66cd00));
  fprintf_s(fp,"#define springgreen4_16cr 0x%04x\n",col_trans( 0x458b00));
  fprintf_s(fp,"#define steelblue_16cr 0x%04x\n",col_trans( 0xb48246));
  fprintf_s(fp,"#define steelblue1_16cr 0x%04x\n",col_trans( 0xffb863));
  fprintf_s(fp,"#define steelblue2_16cr 0x%04x\n",col_trans( 0xeeac5c));
  fprintf_s(fp,"#define steelblue3_16cr 0x%04x\n",col_trans( 0xcd944f));
  fprintf_s(fp,"#define steelblue4_16cr 0x%04x\n",col_trans( 0x8b6436));
  fprintf_s(fp,"#define tan_16cr 0x%04x\n",col_trans( 0x8cb4d2));
  fprintf_s(fp,"#define tan1_16cr 0x%04x\n",col_trans( 0x4fa5ff));
  fprintf_s(fp,"#define tan2_16cr 0x%04x\n",col_trans( 0x499aee));
  fprintf_s(fp,"#define tan3_16cr 0x%04x\n",col_trans( 0x3f85cd));
  fprintf_s(fp,"#define tan4_16cr 0x%04x\n",col_trans( 0x2b5a8b));
  fprintf_s(fp,"#define thistle_16cr 0x%04x\n",col_trans( 0xd8bfd8));
  fprintf_s(fp,"#define thistle1_16cr 0x%04x\n",col_trans( 0xffe1ff));
  fprintf_s(fp,"#define thistle2_16cr 0x%04x\n",col_trans( 0xeed2ee));
  fprintf_s(fp,"#define thistle3_16cr 0x%04x\n",col_trans( 0xcdb5cd));
  fprintf_s(fp,"#define thistle4_16cr 0x%04x\n",col_trans( 0x8b7b8b));
  fprintf_s(fp,"#define tomato_16cr 0x%04x\n",col_trans( 0x4763ff));
  fprintf_s(fp,"#define tomato1_16cr 0x%04x\n",col_trans( 0x4763ff));
  fprintf_s(fp,"#define tomato2_16cr 0x%04x\n",col_trans( 0x425cee));
  fprintf_s(fp,"#define tomato3_16cr 0x%04x\n",col_trans( 0x394fcd));
  fprintf_s(fp,"#define tomato4_16cr 0x%04x\n",col_trans( 0x26368b));
  fprintf_s(fp,"#define turquoise_16cr 0x%04x\n",col_trans( 0xd0e040));
  fprintf_s(fp,"#define turquoise1_16cr 0x%04x\n",col_trans( 0xfff500));
  fprintf_s(fp,"#define turquoise2_16cr 0x%04x\n",col_trans( 0xeee500));
  fprintf_s(fp,"#define turquoise3_16cr 0x%04x\n",col_trans( 0xcdc500));
  fprintf_s(fp,"#define turquoise4_16cr 0x%04x\n",col_trans( 0x8b8600));
  fprintf_s(fp,"#define violet_16cr 0x%04x\n",col_trans( 0xee82ee));
  fprintf_s(fp,"#define violetred_16cr 0x%04x\n",col_trans( 0x9020d0));
  fprintf_s(fp,"#define violetred1_16cr 0x%04x\n",col_trans( 0x963eff));
  fprintf_s(fp,"#define violetred2_16cr 0x%04x\n",col_trans( 0x8c3aee));
  fprintf_s(fp,"#define violetred3_16cr 0x%04x\n",col_trans( 0x7832cd));
  fprintf_s(fp,"#define violetred4_16cr 0x%04x\n",col_trans( 0x52228b));
  fprintf_s(fp,"#define wheat_16cr 0x%04x\n",col_trans( 0xb3def5));
  fprintf_s(fp,"#define wheat1_16cr 0x%04x\n",col_trans( 0xbae7ff));
  fprintf_s(fp,"#define wheat2_16cr 0x%04x\n",col_trans( 0xaed8ee));
  fprintf_s(fp,"#define wheat3_16cr 0x%04x\n",col_trans( 0x96bacd));
  fprintf_s(fp,"#define wheat4_16cr 0x%04x\n",col_trans( 0x667e8b));
  fprintf_s(fp,"#define white_16cr 0x%04x\n",col_trans( 0xffffff));
  fprintf_s(fp,"#define whitesmoke_16cr 0x%04x\n",col_trans( 0xf5f5f5));
  fprintf_s(fp,"#define yellow_16cr 0x%04x\n",col_trans( 0x00ffff));
  fprintf_s(fp,"#define yellow1_16cr 0x%04x\n",col_trans( 0x00ffff));
  fprintf_s(fp,"#define yellow2_16cr 0x%04x\n",col_trans( 0x00eeee));
  fprintf_s(fp,"#define yellow3_16cr 0x%04x\n",col_trans( 0x00cdcd));
  fprintf_s(fp,"#define yellow4_16cr 0x%04x\n",col_trans( 0x008b8b));
  fprintf_s(fp,"#define yellow5_16cr 0x%04x\n",col_trans( 0x007b7b));
  fprintf_s(fp,"#define yellow6_16cr 0x%04x\n",col_trans( 0x006b6b));
  fprintf_s(fp,"#define yellow7_16cr 0x%04x\n",col_trans( 0x005b5b));
  fprintf_s(fp,"#define yellow8_16cr 0x%04x\n",col_trans( 0x004b4b));
  fprintf_s(fp,"#define yellowgreen_16cr 0x%04x\n",col_trans( 0x32cd9a));
  fprintf_s(fp,"#define ultramarineblue_16cr 0x%04x\n",col_trans( 0xF56641));
  fprintf_s(fp,"#define electricultramarine_16cr 0x%04x\n",col_trans( 0xFF003F));
  fprintf_s(fp,"#define ultramarine_16cr 0x%04x\n",col_trans( 0x8F0A12));
  fclose(fp);
}

#define aliceblue_cr 0xfff8f0
#define antiquewhite_cr 0xd7ebfa
#define antiquewhite1_cr 0xdbefff
#define antiquewhite2_cr 0xccdfee
#define antiquewhite3_cr 0xb0c0cd
#define antiquewhite4_cr 0x78838b
#define aquamarine_cr 0xd4ff7f
#define aquamarine1_cr 0xd4ff7f
#define aquamarine2_cr 0xc6ee76
#define aquamarine3_cr 0xaacd66
#define aquamarine4_cr 0x748b45
#define azure_cr 0xfffff0
#define azure1_cr 0xfffff0
#define azure2_cr 0xeeeee0
#define azure3_cr 0xcdcdc1
#define azure4_cr 0x8b8b83
#define beige_cr 0xdcf5f5
#define bisque_cr 0xc4e4ff
#define bisque1_cr 0xc4e4ff
#define bisque2_cr 0xb7d5ee
#define bisque3_cr 0x9eb7cd
#define bisque4_cr 0x6b7d8b
#define black_cr 0x000000
#define blanchedalmond_cr 0xcdebff
#define blue_cr 0xff0000
#define blue1_cr 0xff0000
#define blue2_cr 0xee0000
#define blue3_cr 0xcd0000
#define blue4_cr 0x8b0000
#define blueviolet_cr 0xe22b8a
#define brown_cr 0x2a2aa5
#define brown1_cr 0x4040ff
#define brown2_cr 0x3b3bee
#define brown3_cr 0x3333cd
#define brown4_cr 0x23238b
#define burlywood_cr 0x87b8de
#define burlywood1_cr 0x9bd3ff
#define burlywood2_cr 0x91c5ee
#define burlywood3_cr 0x7daacd
#define burlywood4_cr 0x55738b
#define cadetblue_cr 0xa09e5f
#define cadetblue1_cr 0xfff598
#define cadetblue2_cr 0xeee58e
#define cadetblue3_cr 0xcdc57a
#define cadetblue4_cr 0x8b8653
#define chartreuse_cr 0x00ff7f
#define chartreuse1_cr 0x00ff7f
#define chartreuse2_cr 0x00ee76
#define chartreuse3_cr 0x00cd66
#define chartreuse4_cr 0x008b45
#define chocolate_cr 0x1e69d2
#define chocolate1_cr 0x247fff
#define chocolate2_cr 0x2176ee
#define chocolate3_cr 0x1d66cd
#define chocolate4_cr 0x13458b
#define coral_cr 0x507fff
#define coral1_cr 0x5672ff
#define coral2_cr 0x506aee
#define coral3_cr 0x455bcd
#define coral4_cr 0x2f3e8b
#define cornflowerblue_cr 0xed9564
#define cornsilk_cr 0xdcf8ff
#define cornsilk1_cr 0xdcf8ff
#define cornsilk2_cr 0xcde8ee
#define cornsilk3_cr 0xb1c8cd
#define cornsilk4_cr 0x78888b
#define crimson_cr 0x3C14DC              
#define cyan_cr 0xffff00
#define cyan1_cr 0xffff00
#define cyan2_cr 0xeeee00
#define cyan3_cr 0xcdcd00
#define cyan4_cr 0x8b8b00
#define darkblue_cr 0x8b0000
#define darkcyan_cr 0x8b8b00
#define darkgoldenrod_cr 0x0b86b8
#define darkgoldenrod1_cr 0x0fb9ff
#define darkgoldenrod2_cr 0x0eadee
#define darkgoldenrod3_cr 0x0c95cd
#define darkgoldenrod4_cr 0x08658b
#define darkgray_cr 0xa9a9a9
#define darkgreen_cr 0x006400
#define darkgrey_cr 0xa9a9a9
#define darkkhaki_cr 0x6bb7bd
#define darkmagenta_cr 0x8b008b
#define darkolivegreen_cr 0x2f6b55
#define darkolivegreen1_cr 0x70ffca
#define darkolivegreen2_cr 0x68eebc
#define darkolivegreen3_cr 0x5acda2
#define darkolivegreen4_cr 0x3d8b6e
#define darkorange_cr 0x008cff
#define darkorange1_cr 0x007fff
#define darkorange2_cr 0x0076ee
#define darkorange3_cr 0x0066cd
#define darkorange4_cr 0x00458b
#define darkorchid_cr 0xcc3299
#define darkorchid1_cr 0xff3ebf
#define darkorchid2_cr 0xee3ab2
#define darkorchid3_cr 0xcd329a
#define darkorchid4_cr 0x8b2268
#define darkred_cr 0x00008b
#define darksalmon_cr 0x7a96e9
#define darkseagreen_cr 0x8fbc8f
#define darkseagreen1_cr 0xc1ffc1
#define darkseagreen2_cr 0xb4eeb4
#define darkseagreen3_cr 0x9bcd9b
#define darkseagreen4_cr 0x698b69
#define darkslateblue_cr 0x8b3d48
#define darkslategray_cr 0x4f4f2f
#define darkslategray1_cr 0xffff97
#define darkslategray2_cr 0xeeee8d
#define darkslategray3_cr 0xcdcd79
#define darkslategray4_cr 0x8b8b52
#define darkslategrey_cr 0x4f4f2f
#define darkslategrey1_cr 0xffff97
#define darkslategrey2_cr 0xeeee8d
#define darkslategrey3_cr 0xcdcd79
#define darkslategrey4_cr 0x8b8b52
#define darkslategrey5_cr 0x666649
#define darkslategrey6_cr 0x464629
#define darkslategrey7_cr 0x262617
#define darkturquoise_cr 0xd1ce00
#define darkviolet_cr 0xd30094
#define deeppink_cr 0x9314ff
#define deeppink1_cr 0x9314ff
#define deeppink2_cr 0x8912ee
#define deeppink3_cr 0x7610cd
#define deeppink4_cr 0x500a8b
#define deepskyblue_cr 0xffbf00
#define deepskyblue1_cr 0xffbf00
#define deepskyblue2_cr 0xeeb200
#define deepskyblue3_cr 0xcd9a00
#define deepskyblue4_cr 0x8b6800
#define dimgray_cr 0x696969
#define dimgrey_cr 0x696969
#define dodgerblue_cr 0xff901e
#define dodgerblue1_cr 0xff901e
#define dodgerblue2_cr 0xee861c
#define dodgerblue3_cr 0xcd7418
#define dodgerblue4_cr 0x8b4e10
#define firebrick_cr 0x2222b2
#define firebrick1_cr 0x3030ff
#define firebrick2_cr 0x2c2cee
#define firebrick3_cr 0x2626cd
#define firebrick4_cr 0x1a1a8b
#define floralwhite_cr 0xf0faff
#define forestgreen_cr 0x228b22
#define gainsboro_cr 0xdcdcdc
#define ghostwhite_cr 0xfff8f8
#define gold_cr 0x00d7ff
#define gold1_cr 0x00d7ff
#define gold2_cr 0x00c9ee
#define gold3_cr 0x00adcd
#define gold4_cr 0x00758b
#define goldenrod_cr 0x20a5da
#define goldenrod1_cr 0x25c1ff
#define goldenrod2_cr 0x22b4ee
#define goldenrod3_cr 0x1d9bcd
#define goldenrod4_cr 0x14698b
#define gray_cr 0xbebebe
#define gray0_cr 0x000000
#define gray1_cr 0x030303
#define gray2_cr 0x050505
#define gray3_cr 0x080808
#define gray4_cr 0x0a0a0a
#define gray5_cr 0x0d0d0d
#define gray6_cr 0x0f0f0f
#define gray7_cr 0x121212
#define gray8_cr 0x141414
#define gray9_cr 0x171717
#define gray10_cr 0x1a1a1a
#define gray11_cr 0x1c1c1c
#define gray12_cr 0x1f1f1f
#define gray13_cr 0x212121
#define gray14_cr 0x242424
#define gray15_cr 0x262626
#define gray16_cr 0x292929
#define gray17_cr 0x2b2b2b
#define gray18_cr 0x2e2e2e
#define gray19_cr 0x303030
#define gray20_cr 0x333333
#define gray21_cr 0x363636
#define gray22_cr 0x383838
#define gray23_cr 0x3b3b3b
#define gray24_cr 0x3d3d3d
#define gray25_cr 0x404040
#define gray26_cr 0x424242
#define gray27_cr 0x454545
#define gray28_cr 0x474747
#define gray29_cr 0x4a4a4a
#define gray30_cr 0x4d4d4d
#define gray31_cr 0x4f4f4f
#define gray32_cr 0x525252
#define gray33_cr 0x545454
#define gray34_cr 0x575757
#define gray35_cr 0x595959
#define gray36_cr 0x5c5c5c
#define gray37_cr 0x5e5e5e
#define gray38_cr 0x616161
#define gray39_cr 0x636363
#define gray40_cr 0x666666
#define gray41_cr 0x696969
#define gray42_cr 0x6b6b6b
#define gray43_cr 0x6e6e6e
#define gray44_cr 0x707070
#define gray45_cr 0x737373
#define gray46_cr 0x757575
#define gray47_cr 0x787878
#define gray48_cr 0x7a7a7a
#define gray49_cr 0x7d7d7d
#define gray50_cr 0x7f7f7f
#define gray51_cr 0x828282
#define gray52_cr 0x858585
#define gray53_cr 0x878787
#define gray54_cr 0x8a8a8a
#define gray55_cr 0x8c8c8c
#define gray56_cr 0x8f8f8f
#define gray57_cr 0x919191
#define gray58_cr 0x949494
#define gray59_cr 0x969696
#define gray60_cr 0x999999
#define gray61_cr 0x9c9c9c
#define gray62_cr 0x9e9e9e
#define gray63_cr 0xa1a1a1
#define gray64_cr 0xa3a3a3
#define gray65_cr 0xa6a6a6
#define gray66_cr 0xa8a8a8
#define gray67_cr 0xababab
#define gray68_cr 0xadadad
#define gray69_cr 0xb0b0b0
#define gray70_cr 0xb3b3b3
#define gray71_cr 0xb5b5b5
#define gray72_cr 0xb8b8b8
#define gray73_cr 0xbababa
#define gray74_cr 0xbdbdbd
#define gray75_cr 0xbfbfbf
#define gray76_cr 0xc2c2c2
#define gray77_cr 0xc4c4c4
#define gray78_cr 0xc7c7c7
#define gray79_cr 0xc9c9c9
#define gray80_cr 0xcccccc
#define gray81_cr 0xcfcfcf
#define gray82_cr 0xd1d1d1
#define gray83_cr 0xd4d4d4
#define gray84_cr 0xd6d6d6
#define gray85_cr 0xd9d9d9
#define gray86_cr 0xdbdbdb
#define gray87_cr 0xdedede
#define gray88_cr 0xe0e0e0
#define gray89_cr 0xe3e3e3
#define gray90_cr 0xe5e5e5
#define gray91_cr 0xe8e8e8
#define gray92_cr 0xebebeb
#define gray93_cr 0xededed
#define gray94_cr 0xf0f0f0
#define gray95_cr 0xf2f2f2
#define gray96_cr 0xf5f5f5
#define gray97_cr 0xf7f7f7
#define gray98_cr 0xfafafa
#define gray99_cr 0xfcfcfc
#define gray100_cr 0xffffff
#define green_cr 0x00ff00
#define green1_cr 0x00ff00
#define green2_cr 0x00ee00
#define green3_cr 0x00cd00
#define green4_cr 0x008b00
#define green5_cr 0x006b00
#define green6_cr 0x004b00
#define green7_cr 0x002b00
#define green8_cr 0x001800
#define green9_cr 0x000800
#define greenyellow_cr 0x2fffad
#define grey_cr 0xbebebe
#define grey0_cr 0x000000
#define grey1_cr 0x030303
#define grey2_cr 0x050505
#define grey3_cr 0x080808
#define grey4_cr 0x0a0a0a
#define grey5_cr 0x0d0d0d
#define grey6_cr 0x0f0f0f
#define grey7_cr 0x121212
#define grey8_cr 0x141414
#define grey9_cr 0x171717
#define grey10_cr 0x1a1a1a
#define grey11_cr 0x1c1c1c
#define grey12_cr 0x1f1f1f
#define grey13_cr 0x212121
#define grey14_cr 0x242424
#define grey15_cr 0x262626
#define grey16_cr 0x292929
#define grey17_cr 0x2b2b2b
#define grey18_cr 0x2e2e2e
#define grey19_cr 0x303030
#define grey20_cr 0x333333
#define grey21_cr 0x363636
#define grey22_cr 0x383838
#define grey23_cr 0x3b3b3b
#define grey24_cr 0x3d3d3d
#define grey25_cr 0x404040
#define grey26_cr 0x424242
#define grey27_cr 0x454545
#define grey28_cr 0x474747
#define grey29_cr 0x4a4a4a
#define grey30_cr 0x4d4d4d
#define grey31_cr 0x4f4f4f
#define grey32_cr 0x525252
#define grey33_cr 0x545454
#define grey34_cr 0x575757
#define grey35_cr 0x595959
#define grey36_cr 0x5c5c5c
#define grey37_cr 0x5e5e5e
#define grey38_cr 0x616161
#define grey39_cr 0x636363
#define grey40_cr 0x666666
#define grey41_cr 0x696969
#define grey42_cr 0x6b6b6b
#define grey43_cr 0x6e6e6e
#define grey44_cr 0x707070
#define grey45_cr 0x737373
#define grey46_cr 0x757575
#define grey47_cr 0x787878
#define grey48_cr 0x7a7a7a
#define grey49_cr 0x7d7d7d
#define grey50_cr 0x7f7f7f
#define grey51_cr 0x828282
#define grey52_cr 0x858585
#define grey53_cr 0x878787
#define grey54_cr 0x8a8a8a
#define grey55_cr 0x8c8c8c
#define grey56_cr 0x8f8f8f
#define grey57_cr 0x919191
#define grey58_cr 0x949494
#define grey59_cr 0x969696
#define grey60_cr 0x999999
#define grey61_cr 0x9c9c9c
#define grey62_cr 0x9e9e9e
#define grey63_cr 0xa1a1a1
#define grey64_cr 0xa3a3a3
#define grey65_cr 0xa6a6a6
#define grey66_cr 0xa8a8a8
#define grey67_cr 0xababab
#define grey68_cr 0xadadad
#define grey69_cr 0xb0b0b0
#define grey70_cr 0xb3b3b3
#define grey71_cr 0xb5b5b5
#define grey72_cr 0xb8b8b8
#define grey73_cr 0xbababa
#define grey74_cr 0xbdbdbd
#define grey75_cr 0xbfbfbf
#define grey76_cr 0xc2c2c2
#define grey77_cr 0xc4c4c4
#define grey78_cr 0xc7c7c7
#define grey79_cr 0xc9c9c9
#define grey80_cr 0xcccccc
#define grey81_cr 0xcfcfcf
#define grey82_cr 0xd1d1d1
#define grey83_cr 0xd4d4d4
#define grey84_cr 0xd6d6d6
#define grey85_cr 0xd9d9d9
#define grey86_cr 0xdbdbdb
#define grey87_cr 0xdedede
#define grey88_cr 0xe0e0e0
#define grey89_cr 0xe3e3e3
#define grey90_cr 0xe5e5e5
#define grey91_cr 0xe8e8e8
#define grey92_cr 0xebebeb
#define grey93_cr 0xededed
#define grey94_cr 0xf0f0f0
#define grey95_cr 0xf2f2f2
#define grey96_cr 0xf5f5f5
#define grey97_cr 0xf7f7f7
#define grey98_cr 0xfafafa
#define grey99_cr 0xfcfcfc
#define grey100_cr 0xffffff
#define honeydew_cr 0xf0fff0
#define honeydew1_cr 0xf0fff0
#define honeydew2_cr 0xe0eee0
#define honeydew3_cr 0xc1cdc1
#define honeydew4_cr 0x838b83
#define hotpink_cr 0xb469ff
#define hotpink1_cr 0xb46eff
#define hotpink2_cr 0xa76aee
#define hotpink3_cr 0x9060cd
#define hotpink4_cr 0x623a8b
#define indianred_cr 0x5c5ccd
#define indianred1_cr 0x6a6aff
#define indianred2_cr 0x6363ee
#define indianred3_cr 0x5555cd
#define indianred4_cr 0x3a3a8b
#define ivory_cr 0xf0ffff
#define ivory1_cr 0xf0ffff
#define ivory2_cr 0xe0eeee
#define ivory3_cr 0xc1cdcd
#define ivory4_cr 0x838b8b
#define khaki_cr 0x8ce6f0
#define khaki1_cr 0x8ff6ff
#define khaki2_cr 0x85e6ee
#define khaki3_cr 0x73c6cd
#define khaki4_cr 0x4e868b
#define lavender_cr 0xfae6e6
#define lavenderblush_cr 0xf5f0ff
#define lavenderblush1_cr 0xf5f0ff
#define lavenderblush2_cr 0xe5e0ee
#define lavenderblush3_cr 0xc5c1cd
#define lavenderblush4_cr 0x86838b
#define lawngreen_cr 0x00fc7c
#define lemonchiffon_cr 0xcdfaff
#define lemonchiffon1_cr 0xcdfaff
#define lemonchiffon2_cr 0xbfe9ee
#define lemonchiffon3_cr 0xa5c9cd
#define lemonchiffon4_cr 0x70898b
#define lightblue_cr 0xe6d8ad
#define lightblue1_cr 0xffefbf
#define lightblue2_cr 0xeedfb2
#define lightblue3_cr 0xcdc09a
#define lightblue4_cr 0x8b8368
#define lightcoral_cr 0x8080f0
#define lightcyan_cr 0xffffe0
#define lightcyan1_cr 0xffffe0
#define lightcyan2_cr 0xeeeed1
#define lightcyan3_cr 0xcdcdb4
#define lightcyan4_cr 0x8b8b7a
#define lightgoldenrod_cr 0x82ddee
#define lightgoldenrod1_cr 0x8becff
#define lightgoldenrod2_cr 0x82dcee
#define lightgoldenrod3_cr 0x70becd
#define lightgoldenrod4_cr 0x4c818b
#define lightgoldenrodyellow_cr 0xd2fafa
#define lightgray_cr 0xd3d3d3
#define lightgreen_cr 0x90ee90
#define lightgrey_cr 0xd3d3d3
#define lightpink_cr 0xc1b6ff
#define lightpink1_cr 0xb9aeff
#define lightpink2_cr 0xada2ee
#define lightpink3_cr 0x958ccd
#define lightpink4_cr 0x655f8b
#define lightsalmon_cr 0x7aa0ff
#define lightsalmon1_cr 0x7aa0ff
#define lightsalmon2_cr 0x7295ee
#define lightsalmon3_cr 0x6281cd
#define lightsalmon4_cr 0x42578b
#define lightseagreen_cr 0xaab220
#define lightskyblue_cr 0xface87
#define lightskyblue1_cr 0xffe2b0
#define lightskyblue2_cr 0xeed3a4
#define lightskyblue3_cr 0xcdb68d
#define lightskyblue4_cr 0x8b7b60
#define lightslateblue_cr 0xff7084
#define lightslategray_cr 0x998877
#define lightslategrey_cr 0x998877
#define lightsteelblue_cr 0xdec4b0
#define lightsteelblue1_cr 0xffe1ca
#define lightsteelblue2_cr 0xeed2bc
#define lightsteelblue3_cr 0xcdb5a2
#define lightsteelblue4_cr 0x8b7b6e
#define lightyellow_cr 0xe0ffff
#define lightyellow1_cr 0xe0ffff
#define lightyellow2_cr 0xd1eeee
#define lightyellow3_cr 0xb4cdcd
#define lightyellow4_cr 0x7a8b8b
#define limegreen_cr 0x32cd32
#define linen_cr 0xe6f0fa
#define magenta_cr 0xff00ff
#define magenta1_cr 0xff00ff
#define magenta2_cr 0xee00ee
#define magenta3_cr 0xcd00cd
#define magenta4_cr 0x8b008b
#define maroon_cr 0x6030b0
#define maroon1_cr 0xb334ff
#define maroon2_cr 0xa730ee
#define maroon3_cr 0x9029cd
#define maroon4_cr 0x621c8b
#define mediumaquamarine_cr 0xaacd66
#define mediumblue_cr 0xcd0000
#define mediumorchid_cr 0xd355ba
#define mediumorchid1_cr 0xff66e0
#define mediumorchid2_cr 0xee5fd1
#define mediumorchid3_cr 0xcd52b4
#define mediumorchid4_cr 0x8b377a
#define mediumpurple_cr 0xdb7093
#define mediumpurple1_cr 0xff82ab
#define mediumpurple2_cr 0xee799f
#define mediumpurple3_cr 0xcd6889
#define mediumpurple4_cr 0x8b475d
#define mediumseagreen_cr 0x71b33c
#define mediumslateblue_cr 0xee687b
#define mediumspringgreen_cr 0x9afa00
#define mediumturquoise_cr 0xccd148
#define mediumvioletred_cr 0x8515c7
#define midnightblue_cr 0x701919
#define mintcream_cr 0xfafff5
#define mistyrose_cr 0xe1e4ff
#define mistyrose1_cr 0xe1e4ff
#define mistyrose2_cr 0xd2d5ee
#define mistyrose3_cr 0xb5b7cd
#define mistyrose4_cr 0x7b7d8b
#define moccasin_cr 0xb5e4ff
#define navajowhite_cr 0xaddeff
#define navajowhite1_cr 0xaddeff
#define navajowhite2_cr 0xa1cfee
#define navajowhite3_cr 0x8bb3cd
#define navajowhite4_cr 0x5e798b
#define navy_cr 0x800000
#define navyblue_cr 0x800000
#define oldlace_cr 0xe6f5fd
#define olivedrab_cr 0x238e6b
#define olivedrab1_cr 0x3effc0
#define olivedrab2_cr 0x3aeeb3
#define olivedrab3_cr 0x32cd9a
#define olivedrab4_cr 0x228b69
#define orange0_cr 0x00c5ff
#define orange_cr 0x00a5ff
#define orange1_cr 0x00a5ff
#define orange2_cr 0x009aee
#define orange3_cr 0x0085cd
#define orange4_cr 0x005a8b
#define orangered_cr 0x0045ff
#define orangered1_cr 0x0045ff
#define orangered2_cr 0x0040ee
#define orangered3_cr 0x0037cd
#define orangered4_cr 0x00258b
#define orchid_cr 0xd670da
#define orchid1_cr 0xfa83ff
#define orchid2_cr 0xe97aee
#define orchid3_cr 0xc969cd
#define orchid4_cr 0x89478b
#define palegoldenrod_cr 0xaae8ee
#define palegreen_cr 0x98fb98
#define palegreen1_cr 0x9aff9a
#define palegreen2_cr 0x90ee90
#define palegreen3_cr 0x7ccd7c
#define palegreen4_cr 0x548b54
#define paleturquoise_cr 0xeeeeaf
#define paleturquoise1_cr 0xffffbb
#define paleturquoise2_cr 0xeeeeae
#define paleturquoise3_cr 0xcdcd96
#define paleturquoise4_cr 0x8b8b66
#define palevioletred_cr 0x9370db
#define palevioletred1_cr 0xab82ff
#define palevioletred2_cr 0x9f79ee
#define palevioletred3_cr 0x8968cd
#define palevioletred4_cr 0x5d478b
#define papayawhip_cr 0xd5efff
#define peachpuff_cr 0xb9daff
#define peachpuff1_cr 0xb9daff
#define peachpuff2_cr 0xadcbee
#define peachpuff3_cr 0x95afcd
#define peachpuff4_cr 0x65778b
#define peru_cr 0x3f85cd
#define pink_cr 0xcbc0ff
#define pink1_cr 0xc5b5ff
#define pink2_cr 0xb8a9ee
#define pink3_cr 0x9e91cd
#define pink4_cr 0x6c638b
#define plum_cr 0xdda0dd
#define plum1_cr 0xffbbff
#define plum2_cr 0xeeaeee
#define plum3_cr 0xcd96cd
#define plum4_cr 0x8b668b
#define powderblue_cr 0xe6e0b0
#define purple_cr 0xf020a0
#define purple1_cr 0xff309b
#define purple2_cr 0xee2c91
#define purple3_cr 0xcd267d
#define purple4_cr 0x8b1a55
#define red_cr 0x0000ff
#define red1_cr 0x0000ff
#define red2_cr 0x0000ee
#define red3_cr 0x0000cd
#define red4_cr 0x00008b
#define red5_cr 0x00007b
#define red6_cr 0x00006b
#define red7_cr 0x00005b
#define red8_cr 0x00004b
#define rosybrown_cr 0x8f8fbc
#define rosybrown1_cr 0xc1c1ff
#define rosybrown2_cr 0xb4b4ee
#define rosybrown3_cr 0x9b9bcd
#define rosybrown4_cr 0x69698b
#define royalblue_cr 0xe16941
#define royalblue1_cr 0xff7648
#define royalblue2_cr 0xee6e43
#define royalblue3_cr 0xcd5f3a
#define royalblue4_cr 0x8b4027
#define saddlebrown_cr 0x13458b
#define salmon_cr 0x7280fa
#define salmon1_cr 0x698cff
#define salmon2_cr 0x6282ee
#define salmon3_cr 0x5470cd
#define salmon4_cr 0x394c8b
#define sandybrown_cr 0x60a4f4
#define seagreen_cr 0x578b2e
#define seagreen1_cr 0x9fff54
#define seagreen2_cr 0x94ee4e
#define seagreen3_cr 0x80cd43
#define seagreen4_cr 0x578b2e
#define seashell_cr 0xeef5ff
#define seashell1_cr 0xeef5ff
#define seashell2_cr 0xdee5ee
#define seashell3_cr 0xbfc5cd
#define seashell4_cr 0x82868b
#define sienna_cr 0x2d52a0
#define sienna1_cr 0x4782ff
#define sienna2_cr 0x4279ee
#define sienna3_cr 0x3968cd
#define sienna4_cr 0x26478b
#define skyblue_cr 0xebce87
#define skyblue1_cr 0xffce87
#define skyblue2_cr 0xeec07e
#define skyblue3_cr 0xcda66c
#define skyblue4_cr 0x8b704a
#define slateblue_cr 0xcd5a6a
#define slateblue1_cr 0xff6f83
#define slateblue2_cr 0xee677a
#define slateblue3_cr 0xcd5969
#define slateblue4_cr 0x8b3c47
#define slategray_cr 0x908070
#define slategray1_cr 0xffe2c6
#define slategray2_cr 0xeed3b9
#define slategray3_cr 0xcdb69f
#define slategray4_cr 0x8b7b6c
#define slategrey_cr 0x908070
#define slategrey1_cr 0xffe2c6
#define slategrey2_cr 0xeed3b9
#define slategrey3_cr 0xcdb69f
#define slategrey4_cr 0x8b7b6c
#define snow_cr 0xfafaff
#define snow1_cr 0xfafaff
#define snow2_cr 0xe9e9ee
#define snow3_cr 0xc9c9cd
#define snow4_cr 0x89898b
#define springgreen_cr 0x7fff00
#define springgreen1_cr 0x7fff00
#define springgreen2_cr 0x76ee00
#define springgreen3_cr 0x66cd00
#define springgreen4_cr 0x458b00
#define steelblue_cr 0xb48246
#define steelblue1_cr 0xffb863
#define steelblue2_cr 0xeeac5c
#define steelblue3_cr 0xcd944f
#define steelblue4_cr 0x8b6436
#define tan_cr 0x8cb4d2
#define tan1_cr 0x4fa5ff
#define tan2_cr 0x499aee
#define tan3_cr 0x3f85cd
#define tan4_cr 0x2b5a8b
#define thistle_cr 0xd8bfd8
#define thistle1_cr 0xffe1ff
#define thistle2_cr 0xeed2ee
#define thistle3_cr 0xcdb5cd
#define thistle4_cr 0x8b7b8b
#define tomato_cr 0x4763ff
#define tomato1_cr 0x4763ff
#define tomato2_cr 0x425cee
#define tomato3_cr 0x394fcd
#define tomato4_cr 0x26368b
#define turquoise_cr 0xd0e040
#define turquoise1_cr 0xfff500
#define turquoise2_cr 0xeee500
#define turquoise3_cr 0xcdc500
#define turquoise4_cr 0x8b8600
#define violet_cr 0xee82ee
#define violetred_cr 0x9020d0
#define violetred1_cr 0x963eff
#define violetred2_cr 0x8c3aee
#define violetred3_cr 0x7832cd
#define violetred4_cr 0x52228b
#define wheat_cr 0xb3def5
#define wheat1_cr 0xbae7ff
#define wheat2_cr 0xaed8ee
#define wheat3_cr 0x96bacd
#define wheat4_cr 0x667e8b
#define white_cr 0xffffff
#define whitesmoke_cr 0xf5f5f5
#define yellow_cr 0x00ffff
#define yellow1_cr 0x00ffff
#define yellow2_cr 0x00eeee
#define yellow3_cr 0x00cdcd
#define yellow4_cr 0x008b8b
#define yellow5_cr 0x007b7b
#define yellow6_cr 0x006b6b
#define yellow7_cr 0x005b5b
#define yellow8_cr 0x004b4b
#define yellowgreen_cr 0x32cd9a

#define ultramarineblue_cr 0xF56641
#define electricultramarine_cr 0xFF003F
#define ultramarine_cr 0x8F0A12




#define aliceblue_c 0xfff0f8ff
#define antiquewhite_c 0xfffaebd7
#define antiquewhite1_c 0xffffefdb
#define antiquewhite2_c 0xffeedfcc
#define antiquewhite3_c 0xffcdc0b0
#define antiquewhite4_c 0xff8b8378
#define aquamarine_c 0xff7fffd4
#define aquamarine1_c 0xff7fffd4
#define aquamarine2_c 0xff76eec6
#define aquamarine3_c 0xff66cdaa
#define aquamarine4_c 0xff458b74
#define azure_c 0xfff0ffff
#define azure1_c 0xfff0ffff
#define azure2_c 0xffe0eeee
#define azure3_c 0xffc1cdcd
#define azure4_c 0xff838b8b
#define beige_c 0xfff5f5dc
#define bisque_c 0xffffe4c4
#define bisque1_c 0xffffe4c4
#define bisque2_c 0xffeed5b7
#define bisque3_c 0xffcdb79e
#define bisque4_c 0xff8b7d6b
#define black_c 0xff000000
#define blanchedalmond_c 0xffffebcd
#define blue_c 0xff0000ff
#define blue1_c 0xff0000ff
#define blue2_c 0xff0000ee
#define blue3_c 0xff0000cd
#define blue4_c 0xff00008b
#define blueviolet_c 0xff8a2be2
#define brown_c 0xffa52a2a
#define brown1_c 0xffff4040
#define brown2_c 0xffee3b3b
#define brown3_c 0xffcd3333
#define brown4_c 0xff8b2323
#define burlywood_c 0xffdeb887
#define burlywood1_c 0xffffd39b
#define burlywood2_c 0xffeec591
#define burlywood3_c 0xffcdaa7d
#define burlywood4_c 0xff8b7355
#define cadetblue_c 0xff5f9ea0
#define cadetblue1_c 0xff98f5ff
#define cadetblue2_c 0xff8ee5ee
#define cadetblue3_c 0xff7ac5cd
#define cadetblue4_c 0xff53868b
#define chartreuse_c 0xff7fff00
#define chartreuse1_c 0xff7fff00
#define chartreuse2_c 0xff76ee00
#define chartreuse3_c 0xff66cd00
#define chartreuse4_c 0xff458b00
#define chocolate_c 0xffd2691e
#define chocolate1_c 0xffff7f24
#define chocolate2_c 0xffee7621
#define chocolate3_c 0xffcd661d
#define chocolate4_c 0xff8b4513
#define coral_c 0xffff7f50
#define coral1_c 0xffff7256
#define coral2_c 0xffee6a50
#define coral3_c 0xffcd5b45
#define coral4_c 0xff8b3e2f
#define cornflowerblue_c 0xff6495ed
#define cornsilk_c 0xfffff8dc
#define cornsilk1_c 0xfffff8dc
#define cornsilk2_c 0xffeee8cd
#define cornsilk3_c 0xffcdc8b1
#define cornsilk4_c 0xff8b8878
#define cyan_c 0xff00ffff
#define cyan1_c 0xff00ffff
#define cyan2_c 0xff00eeee
#define cyan3_c 0xff00cdcd
#define cyan4_c 0xff008b8b
#define darkblue_c 0xff00008b
#define darkcyan_c 0xff008b8b
#define darkgoldenrod_c 0xffb8860b
#define darkgoldenrod1_c 0xffffb90f
#define darkgoldenrod2_c 0xffeead0e
#define darkgoldenrod3_c 0xffcd950c
#define darkgoldenrod4_c 0xff8b6508
#define darkgray_c 0xffa9a9a9
#define darkgreen_c 0xff006400
#define darkgrey_c 0xffa9a9a9
#define darkkhaki_c 0xffbdb76b
#define darkmagenta_c 0xff8b008b
#define darkolivegreen_c 0xff556b2f
#define darkolivegreen1_c 0xffcaff70
#define darkolivegreen2_c 0xffbcee68
#define darkolivegreen3_c 0xffa2cd5a
#define darkolivegreen4_c 0xff6e8b3d
#define darkorange_c 0xffff8c00
#define darkorange1_c 0xffff7f00
#define darkorange2_c 0xffee7600
#define darkorange3_c 0xffcd6600
#define darkorange4_c 0xff8b4500
#define darkorchid_c 0xff9932cc
#define darkorchid1_c 0xffbf3eff
#define darkorchid2_c 0xffb23aee
#define darkorchid3_c 0xff9a32cd
#define darkorchid4_c 0xff68228b
#define darkred_c 0xff8b0000
#define darksalmon_c 0xffe9967a
#define darkseagreen_c 0xff8fbc8f
#define darkseagreen1_c 0xffc1ffc1
#define darkseagreen2_c 0xffb4eeb4
#define darkseagreen3_c 0xff9bcd9b
#define darkseagreen4_c 0xff698b69
#define darkslateblue_c 0xff483d8b
#define darkslategray_c 0xff2f4f4f
#define darkslategray1_c 0xff97ffff
#define darkslategray2_c 0xff8deeee
#define darkslategray3_c 0xff79cdcd
#define darkslategray4_c 0xff528b8b
#define darkslategrey_c 0xff2f4f4f
#define darkslategrey1_c 0xff97ffff
#define darkslategrey2_c 0xff8deeee
#define darkslategrey3_c 0xff79cdcd
#define darkslategrey4_c 0xff528b8b
#define darkturquoise_c 0xff00ced1
#define darkviolet_c 0xff9400d3
#define deeppink_c 0xffff1493
#define deeppink1_c 0xffff1493
#define deeppink2_c 0xffee1289
#define deeppink3_c 0xffcd1076
#define deeppink4_c 0xff8b0a50
#define deepskyblue_c 0xff00bfff
#define deepskyblue1_c 0xff00bfff
#define deepskyblue2_c 0xff00b2ee
#define deepskyblue3_c 0xff009acd
#define deepskyblue4_c 0xff00688b
#define dimgray_c 0xff696969
#define dimgrey_c 0xff696969
#define dodgerblue_c 0xff1e90ff
#define dodgerblue1_c 0xff1e90ff
#define dodgerblue2_c 0xff1c86ee
#define dodgerblue3_c 0xff1874cd
#define dodgerblue4_c 0xff104e8b
#define firebrick_c 0xffb22222
#define firebrick1_c 0xffff3030
#define firebrick2_c 0xffee2c2c
#define firebrick3_c 0xffcd2626
#define firebrick4_c 0xff8b1a1a
#define floralwhite_c 0xfffffaf0
#define forestgreen_c 0xff228b22
#define gainsboro_c 0xffdcdcdc
#define ghostwhite_c 0xfff8f8ff
#define gold_c 0xffffd700
#define gold1_c 0xffffd700
#define gold2_c 0xffeec900
#define gold3_c 0xffcdad00
#define gold4_c 0xff8b7500
#define goldenrod_c 0xffdaa520
#define goldenrod1_c 0xffffc125
#define goldenrod2_c 0xffeeb422
#define goldenrod3_c 0xffcd9b1d
#define goldenrod4_c 0xff8b6914
#define gray_c 0xffbebebe
#define gray0_c 0xff000000
#define gray1_c 0xff030303
#define gray2_c 0xff050505
#define gray3_c 0xff080808
#define gray4_c 0xff0a0a0a
#define gray5_c 0xff0d0d0d
#define gray6_c 0xff0f0f0f
#define gray7_c 0xff121212
#define gray8_c 0xff141414
#define gray9_c 0xff171717
#define gray10_c 0xff1a1a1a
#define gray11_c 0xff1c1c1c
#define gray12_c 0xff1f1f1f
#define gray13_c 0xff212121
#define gray14_c 0xff242424
#define gray15_c 0xff262626
#define gray16_c 0xff292929
#define gray17_c 0xff2b2b2b
#define gray18_c 0xff2e2e2e
#define gray19_c 0xff303030
#define gray20_c 0xff333333
#define gray21_c 0xff363636
#define gray22_c 0xff383838
#define gray23_c 0xff3b3b3b
#define gray24_c 0xff3d3d3d
#define gray25_c 0xff404040
#define gray26_c 0xff424242
#define gray27_c 0xff454545
#define gray28_c 0xff474747
#define gray29_c 0xff4a4a4a
#define gray30_c 0xff4d4d4d
#define gray31_c 0xff4f4f4f
#define gray32_c 0xff525252
#define gray33_c 0xff545454
#define gray34_c 0xff575757
#define gray35_c 0xff595959
#define gray36_c 0xff5c5c5c
#define gray37_c 0xff5e5e5e
#define gray38_c 0xff616161
#define gray39_c 0xff636363
#define gray40_c 0xff666666
#define gray41_c 0xff696969
#define gray42_c 0xff6b6b6b
#define gray43_c 0xff6e6e6e
#define gray44_c 0xff707070
#define gray45_c 0xff737373
#define gray46_c 0xff757575
#define gray47_c 0xff787878
#define gray48_c 0xff7a7a7a
#define gray49_c 0xff7d7d7d
#define gray50_c 0xff7f7f7f
#define gray51_c 0xff828282
#define gray52_c 0xff858585
#define gray53_c 0xff878787
#define gray54_c 0xff8a8a8a
#define gray55_c 0xff8c8c8c
#define gray56_c 0xff8f8f8f
#define gray57_c 0xff919191
#define gray58_c 0xff949494
#define gray59_c 0xff969696
#define gray60_c 0xff999999
#define gray61_c 0xff9c9c9c
#define gray62_c 0xff9e9e9e
#define gray63_c 0xffa1a1a1
#define gray64_c 0xffa3a3a3
#define gray65_c 0xffa6a6a6
#define gray66_c 0xffa8a8a8
#define gray67_c 0xffababab
#define gray68_c 0xffadadad
#define gray69_c 0xffb0b0b0
#define gray70_c 0xffb3b3b3
#define gray71_c 0xffb5b5b5
#define gray72_c 0xffb8b8b8
#define gray73_c 0xffbababa
#define gray74_c 0xffbdbdbd
#define gray75_c 0xffbfbfbf
#define gray76_c 0xffc2c2c2
#define gray77_c 0xffc4c4c4
#define gray78_c 0xffc7c7c7
#define gray79_c 0xffc9c9c9
#define gray80_c 0xffcccccc
#define gray81_c 0xffcfcfcf
#define gray82_c 0xffd1d1d1
#define gray83_c 0xffd4d4d4
#define gray84_c 0xffd6d6d6
#define gray85_c 0xffd9d9d9
#define gray86_c 0xffdbdbdb
#define gray87_c 0xffdedede
#define gray88_c 0xffe0e0e0
#define gray89_c 0xffe3e3e3
#define gray90_c 0xffe5e5e5
#define gray91_c 0xffe8e8e8
#define gray92_c 0xffebebeb
#define gray93_c 0xffededed
#define gray94_c 0xfff0f0f0
#define gray95_c 0xfff2f2f2
#define gray96_c 0xfff5f5f5
#define gray97_c 0xfff7f7f7
#define gray98_c 0xfffafafa
#define gray99_c 0xfffcfcfc
#define gray100_c 0xffffffff
#define green_c 0xff00ff00
#define green1_c 0xff00ff00
#define green2_c 0xff00ee00
#define green3_c 0xff00cd00
#define green4_c 0xff008b00
#define greenyellow_c 0xffadff2f
#define grey_c 0xffbebebe
#define grey0_c 0xff000000
#define grey1_c 0xff030303
#define grey2_c 0xff050505
#define grey3_c 0xff080808
#define grey4_c 0xff0a0a0a
#define grey5_c 0xff0d0d0d
#define grey6_c 0xff0f0f0f
#define grey7_c 0xff121212
#define grey8_c 0xff141414
#define grey9_c 0xff171717
#define grey10_c 0xff1a1a1a
#define grey11_c 0xff1c1c1c
#define grey12_c 0xff1f1f1f
#define grey13_c 0xff212121
#define grey14_c 0xff242424
#define grey15_c 0xff262626
#define grey16_c 0xff292929
#define grey17_c 0xff2b2b2b
#define grey18_c 0xff2e2e2e
#define grey19_c 0xff303030
#define grey20_c 0xff333333
#define grey21_c 0xff363636
#define grey22_c 0xff383838
#define grey23_c 0xff3b3b3b
#define grey24_c 0xff3d3d3d
#define grey25_c 0xff404040
#define grey26_c 0xff424242
#define grey27_c 0xff454545
#define grey28_c 0xff474747
#define grey29_c 0xff4a4a4a
#define grey30_c 0xff4d4d4d
#define grey31_c 0xff4f4f4f
#define grey32_c 0xff525252
#define grey33_c 0xff545454
#define grey34_c 0xff575757
#define grey35_c 0xff595959
#define grey36_c 0xff5c5c5c
#define grey37_c 0xff5e5e5e
#define grey38_c 0xff616161
#define grey39_c 0xff636363
#define grey40_c 0xff666666
#define grey41_c 0xff696969
#define grey42_c 0xff6b6b6b
#define grey43_c 0xff6e6e6e
#define grey44_c 0xff707070
#define grey45_c 0xff737373
#define grey46_c 0xff757575
#define grey47_c 0xff787878
#define grey48_c 0xff7a7a7a
#define grey49_c 0xff7d7d7d
#define grey50_c 0xff7f7f7f
#define grey51_c 0xff828282
#define grey52_c 0xff858585
#define grey53_c 0xff878787
#define grey54_c 0xff8a8a8a
#define grey55_c 0xff8c8c8c
#define grey56_c 0xff8f8f8f
#define grey57_c 0xff919191
#define grey58_c 0xff949494
#define grey59_c 0xff969696
#define grey60_c 0xff999999
#define grey61_c 0xff9c9c9c
#define grey62_c 0xff9e9e9e
#define grey63_c 0xffa1a1a1
#define grey64_c 0xffa3a3a3
#define grey65_c 0xffa6a6a6
#define grey66_c 0xffa8a8a8
#define grey67_c 0xffababab
#define grey68_c 0xffadadad
#define grey69_c 0xffb0b0b0
#define grey70_c 0xffb3b3b3
#define grey71_c 0xffb5b5b5
#define grey72_c 0xffb8b8b8
#define grey73_c 0xffbababa
#define grey74_c 0xffbdbdbd
#define grey75_c 0xffbfbfbf
#define grey76_c 0xffc2c2c2
#define grey77_c 0xffc4c4c4
#define grey78_c 0xffc7c7c7
#define grey79_c 0xffc9c9c9
#define grey80_c 0xffcccccc
#define grey81_c 0xffcfcfcf
#define grey82_c 0xffd1d1d1
#define grey83_c 0xffd4d4d4
#define grey84_c 0xffd6d6d6
#define grey85_c 0xffd9d9d9
#define grey86_c 0xffdbdbdb
#define grey87_c 0xffdedede
#define grey88_c 0xffe0e0e0
#define grey89_c 0xffe3e3e3
#define grey90_c 0xffe5e5e5
#define grey91_c 0xffe8e8e8
#define grey92_c 0xffebebeb
#define grey93_c 0xffededed
#define grey94_c 0xfff0f0f0
#define grey95_c 0xfff2f2f2
#define grey96_c 0xfff5f5f5
#define grey97_c 0xfff7f7f7
#define grey98_c 0xfffafafa
#define grey99_c 0xfffcfcfc
#define grey100_c 0xffffffff
#define honeydew_c 0xfff0fff0
#define honeydew1_c 0xfff0fff0
#define honeydew2_c 0xffe0eee0
#define honeydew3_c 0xffc1cdc1
#define honeydew4_c 0xff838b83
#define hotpink_c 0xffff69b4
#define hotpink1_c 0xffff6eb4
#define hotpink2_c 0xffee6aa7
#define hotpink3_c 0xffcd6090
#define hotpink4_c 0xff8b3a62
#define indianred_c 0xffcd5c5c
#define indianred1_c 0xffff6a6a
#define indianred2_c 0xffee6363
#define indianred3_c 0xffcd5555
#define indianred4_c 0xff8b3a3a
#define ivory_c 0xfffffff0
#define ivory1_c 0xfffffff0
#define ivory2_c 0xffeeeee0
#define ivory3_c 0xffcdcdc1
#define ivory4_c 0xff8b8b83
#define khaki_c 0xfff0e68c
#define khaki1_c 0xfffff68f
#define khaki2_c 0xffeee685
#define khaki3_c 0xffcdc673
#define khaki4_c 0xff8b864e
#define lavender_c 0xffe6e6fa
#define lavenderblush_c 0xfffff0f5
#define lavenderblush1_c 0xfffff0f5
#define lavenderblush2_c 0xffeee0e5
#define lavenderblush3_c 0xffcdc1c5
#define lavenderblush4_c 0xff8b8386
#define lawngreen_c 0xff7cfc00
#define lemonchiffon_c 0xfffffacd
#define lemonchiffon1_c 0xfffffacd
#define lemonchiffon2_c 0xffeee9bf
#define lemonchiffon3_c 0xffcdc9a5
#define lemonchiffon4_c 0xff8b8970
#define lightblue_c 0xffadd8e6
#define lightblue1_c 0xffbfefff
#define lightblue2_c 0xffb2dfee
#define lightblue3_c 0xff9ac0cd
#define lightblue4_c 0xff68838b
#define lightcoral_c 0xfff08080
#define lightcyan_c 0xffe0ffff
#define lightcyan1_c 0xffe0ffff
#define lightcyan2_c 0xffd1eeee
#define lightcyan3_c 0xffb4cdcd
#define lightcyan4_c 0xff7a8b8b
#define lightgoldenrod_c 0xffeedd82
#define lightgoldenrod1_c 0xffffec8b
#define lightgoldenrod2_c 0xffeedc82
#define lightgoldenrod3_c 0xffcdbe70
#define lightgoldenrod4_c 0xff8b814c
#define lightgoldenrodyellow_c 0xfffafad2
#define lightgray_c 0xffd3d3d3
#define lightgreen_c 0xff90ee90
#define lightgrey_c 0xffd3d3d3
#define lightpink_c 0xffffb6c1
#define lightpink1_c 0xffffaeb9
#define lightpink2_c 0xffeea2ad
#define lightpink3_c 0xffcd8c95
#define lightpink4_c 0xff8b5f65
#define lightsalmon_c 0xffffa07a
#define lightsalmon1_c 0xffffa07a
#define lightsalmon2_c 0xffee9572
#define lightsalmon3_c 0xffcd8162
#define lightsalmon4_c 0xff8b5742
#define lightseagreen_c 0xff20b2aa
#define lightskyblue_c 0xff87cefa
#define lightskyblue1_c 0xffb0e2ff
#define lightskyblue2_c 0xffa4d3ee
#define lightskyblue3_c 0xff8db6cd
#define lightskyblue4_c 0xff607b8b
#define lightslateblue_c 0xff8470ff
#define lightslategray_c 0xff778899
#define lightslategrey_c 0xff778899
#define lightsteelblue_c 0xffb0c4de
#define lightsteelblue1_c 0xffcae1ff
#define lightsteelblue2_c 0xffbcd2ee
#define lightsteelblue3_c 0xffa2b5cd
#define lightsteelblue4_c 0xff6e7b8b
#define lightyellow_c 0xffffffe0
#define lightyellow1_c 0xffffffe0
#define lightyellow2_c 0xffeeeed1
#define lightyellow3_c 0xffcdcdb4
#define lightyellow4_c 0xff8b8b7a
#define limegreen_c 0xff32cd32
#define linen_c 0xfffaf0e6
#define magenta_c 0xffff00ff
#define magenta1_c 0xffff00ff
#define magenta2_c 0xffee00ee
#define magenta3_c 0xffcd00cd
#define magenta4_c 0xff8b008b
#define maroon_c 0xffb03060
#define maroon1_c 0xffff34b3
#define maroon2_c 0xffee30a7
#define maroon3_c 0xffcd2990
#define maroon4_c 0xff8b1c62
#define mediumaquamarine_c 0xff66cdaa
#define mediumblue_c 0xff0000cd
#define mediumorchid_c 0xffba55d3
#define mediumorchid1_c 0xffe066ff
#define mediumorchid2_c 0xffd15fee
#define mediumorchid3_c 0xffb452cd
#define mediumorchid4_c 0xff7a378b
#define mediumpurple_c 0xff9370db
#define mediumpurple1_c 0xffab82ff
#define mediumpurple2_c 0xff9f79ee
#define mediumpurple3_c 0xff8968cd
#define mediumpurple4_c 0xff5d478b
#define mediumseagreen_c 0xff3cb371
#define mediumslateblue_c 0xff7b68ee
#define mediumspringgreen_c 0xff00fa9a
#define mediumturquoise_c 0xff48d1cc
#define mediumvioletred_c 0xffc71585
#define midnightblue_c 0xff191970
#define mintcream_c 0xfff5fffa
#define mistyrose_c 0xffffe4e1
#define mistyrose1_c 0xffffe4e1
#define mistyrose2_c 0xffeed5d2
#define mistyrose3_c 0xffcdb7b5
#define mistyrose4_c 0xff8b7d7b
#define moccasin_c 0xffffe4b5
#define navajowhite_c 0xffffdead
#define navajowhite1_c 0xffffdead
#define navajowhite2_c 0xffeecfa1
#define navajowhite3_c 0xffcdb38b
#define navajowhite4_c 0xff8b795e
#define navy_c 0xff000080
#define navyblue_c 0xff000080
#define oldlace_c 0xfffdf5e6
#define olivedrab_c 0xff6b8e23
#define olivedrab1_c 0xffc0ff3e
#define olivedrab2_c 0xffb3ee3a
#define olivedrab3_c 0xff9acd32
#define olivedrab4_c 0xff698b22
#define orange_c 0xffffa500
#define orange1_c 0xffffa500
#define orange2_c 0xffee9a00
#define orange3_c 0xffcd8500
#define orange4_c 0xff8b5a00
#define orangered_c 0xffff4500
#define orangered1_c 0xffff4500
#define orangered2_c 0xffee4000
#define orangered3_c 0xffcd3700
#define orangered4_c 0xff8b2500
#define orchid_c 0xffda70d6
#define orchid1_c 0xffff83fa
#define orchid2_c 0xffee7ae9
#define orchid3_c 0xffcd69c9
#define orchid4_c 0xff8b4789
#define palegoldenrod_c 0xffeee8aa
#define palegreen_c 0xff98fb98
#define palegreen1_c 0xff9aff9a
#define palegreen2_c 0xff90ee90
#define palegreen3_c 0xff7ccd7c
#define palegreen4_c 0xff548b54
#define paleturquoise_c 0xffafeeee
#define paleturquoise1_c 0xffbbffff
#define paleturquoise2_c 0xffaeeeee
#define paleturquoise3_c 0xff96cdcd
#define paleturquoise4_c 0xff668b8b
#define palevioletred_c 0xffdb7093
#define palevioletred1_c 0xffff82ab
#define palevioletred2_c 0xffee799f
#define palevioletred3_c 0xffcd6889
#define palevioletred4_c 0xff8b475d
#define papayawhip_c 0xffffefd5
#define peachpuff_c 0xffffdab9
#define peachpuff1_c 0xffffdab9
#define peachpuff2_c 0xffeecbad
#define peachpuff3_c 0xffcdaf95
#define peachpuff4_c 0xff8b7765
#define peru_c 0xffcd853f
#define pink_c 0xffffc0cb
#define pink1_c 0xffffb5c5
#define pink2_c 0xffeea9b8
#define pink3_c 0xffcd919e
#define pink4_c 0xff8b636c
#define plum_c 0xffdda0dd
#define plum1_c 0xffffbbff
#define plum2_c 0xffeeaeee
#define plum3_c 0xffcd96cd
#define plum4_c 0xff8b668b
#define powderblue_c 0xffb0e0e6
#define purple_c 0xffa020f0
#define purple1_c 0xff9b30ff
#define purple2_c 0xff912cee
#define purple3_c 0xff7d26cd
#define purple4_c 0xff551a8b
#define red_c 0xffff0000
#define red1_c 0xffff0000
#define red2_c 0xffee0000
#define red3_c 0xffcd0000
#define red4_c 0xff8b0000
#define rosybrown_c 0xffbc8f8f
#define rosybrown1_c 0xffffc1c1
#define rosybrown2_c 0xffeeb4b4
#define rosybrown3_c 0xffcd9b9b
#define rosybrown4_c 0xff8b6969
#define royalblue_c 0xff4169e1
#define royalblue1_c 0xff4876ff
#define royalblue2_c 0xff436eee
#define royalblue3_c 0xff3a5fcd
#define royalblue4_c 0xff27408b
#define saddlebrown_c 0xff8b4513
#define salmon_c 0xfffa8072
#define salmon1_c 0xffff8c69
#define salmon2_c 0xffee8262
#define salmon3_c 0xffcd7054
#define salmon4_c 0xff8b4c39
#define sandybrown_c 0xfff4a460
#define seagreen_c 0xff2e8b57
#define seagreen1_c 0xff54ff9f
#define seagreen2_c 0xff4eee94
#define seagreen3_c 0xff43cd80
#define seagreen4_c 0xff2e8b57
#define seashell_c 0xfffff5ee
#define seashell1_c 0xfffff5ee
#define seashell2_c 0xffeee5de
#define seashell3_c 0xffcdc5bf
#define seashell4_c 0xff8b8682
#define sienna_c 0xffa0522d
#define sienna1_c 0xffff8247
#define sienna2_c 0xffee7942
#define sienna3_c 0xffcd6839
#define sienna4_c 0xff8b4726
#define skyblue_c 0xff87ceeb
#define skyblue1_c 0xff87ceff
#define skyblue2_c 0xff7ec0ee
#define skyblue3_c 0xff6ca6cd
#define skyblue4_c 0xff4a708b
#define slateblue_c 0xff6a5acd
#define slateblue1_c 0xff836fff
#define slateblue2_c 0xff7a67ee
#define slateblue3_c 0xff6959cd
#define slateblue4_c 0xff473c8b
#define slategray_c 0xff708090
#define slategray1_c 0xffc6e2ff
#define slategray2_c 0xffb9d3ee
#define slategray3_c 0xff9fb6cd
#define slategray4_c 0xff6c7b8b
#define slategrey_c 0xff708090
#define slategrey1_c 0xffc6e2ff
#define slategrey2_c 0xffb9d3ee
#define slategrey3_c 0xff9fb6cd
#define slategrey4_c 0xff6c7b8b
#define snow_c 0xfffffafa
#define snow1_c 0xfffffafa
#define snow2_c 0xffeee9e9
#define snow3_c 0xffcdc9c9
#define snow4_c 0xff8b8989
#define springgreen_c 0xff00ff7f
#define springgreen1_c 0xff00ff7f
#define springgreen2_c 0xff00ee76
#define springgreen3_c 0xff00cd66
#define springgreen4_c 0xff008b45
#define steelblue_c 0xff4682b4
#define steelblue1_c 0xff63b8ff
#define steelblue2_c 0xff5cacee
#define steelblue3_c 0xff4f94cd
#define steelblue4_c 0xff36648b
#define tan_c 0xffd2b48c
#define tan1_c 0xffffa54f
#define tan2_c 0xffee9a49
#define tan3_c 0xffcd853f
#define tan4_c 0xff8b5a2b
#define thistle_c 0xffd8bfd8
#define thistle1_c 0xffffe1ff
#define thistle2_c 0xffeed2ee
#define thistle3_c 0xffcdb5cd
#define thistle4_c 0xff8b7b8b
#define tomato_c 0xffff6347
#define tomato1_c 0xffff6347
#define tomato2_c 0xffee5c42
#define tomato3_c 0xffcd4f39
#define tomato4_c 0xff8b3626
#define turquoise_c 0xff40e0d0
#define turquoise1_c 0xff00f5ff
#define turquoise2_c 0xff00e5ee
#define turquoise3_c 0xff00c5cd
#define turquoise4_c 0xff00868b
#define violet_c 0xffee82ee
#define violetred_c 0xffd02090
#define violetred1_c 0xffff3e96
#define violetred2_c 0xffee3a8c
#define violetred3_c 0xffcd3278
#define violetred4_c 0xff8b2252
#define wheat_c 0xfff5deb3
#define wheat1_c 0xffffe7ba
#define wheat2_c 0xffeed8ae
#define wheat3_c 0xffcdba96
#define wheat4_c 0xff8b7e66
#define white_c 0xffffffff
#define whitesmoke_c 0xfff5f5f5
#define yellow_c 0xffffff00
#define yellow1_c 0xffffff00
#define yellow2_c 0xffeeee00
#define yellow3_c 0xffcdcd00
#define yellow4_c 0xff8b8b00
#define yellowgreen_c 0xff9acd32
#define ultramarineblue_c 0x4166F5
#define electricultramarine_c 0x3F00FF
#define ultramarine_c 0x120A8F

#define awesome_cplus4_pink_c 0xffffc4de
#define awesome_cplus4_pink_cr 0xdec4ff

#else


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define aliceblue_cr   0xf7df
#define antiquewhite_cr   0xff5a
#define antiquewhite1_cr   0xff7b
#define antiquewhite2_cr   0xeef9
#define antiquewhite3_cr   0xce16
#define antiquewhite4_cr   0x8c0f
#define aquamarine_cr   0x7ffa
#define aquamarine1_cr   0x7ffa
#define aquamarine2_cr   0x7778
#define aquamarine3_cr   0x6675
#define aquamarine4_cr   0x444e
#define azure_cr   0xf7ff
#define azure1_cr   0xf7ff
#define azure2_cr   0xe77d
#define azure3_cr   0xc679
#define azure4_cr   0x8451
#define beige_cr   0xf7bb
#define bisque_cr   0xff38
#define bisque1_cr   0xff38
#define bisque2_cr   0xeeb6
#define bisque3_cr   0xcdb3
#define bisque4_cr   0x8bed
#define black_cr   0x0000
#define blanchedalmond_cr   0xff59
#define blue_cr   0x001f
#define blue1_cr   0x001f
#define blue2_cr   0x001d
#define blue3_cr   0x0019
#define blue4_cr   0x0011
#define blueviolet_cr   0x895c
#define brown_cr   0xa145
#define brown1_cr   0xfa08
#define brown2_cr   0xe9c7
#define brown3_cr   0xc986
#define brown4_cr   0x8904
#define burlywood_cr   0xddd0
#define burlywood1_cr   0xfe93
#define burlywood2_cr   0xee32
#define burlywood3_cr   0xcd4f
#define burlywood4_cr   0x8b8a
#define cadetblue_cr   0x5cf4
#define cadetblue1_cr   0x9fbf
#define cadetblue2_cr   0x8f3d
#define cadetblue3_cr   0x7e39
#define cadetblue4_cr   0x5431
#define chartreuse_cr   0x7fe0
#define chartreuse1_cr   0x7fe0
#define chartreuse2_cr   0x7760
#define chartreuse3_cr   0x6660
#define chartreuse4_cr   0x4440
#define chocolate_cr   0xd343
#define chocolate1_cr   0xfbe4
#define chocolate2_cr   0xeba4
#define chocolate3_cr   0xcb23
#define chocolate4_cr   0x8a22
#define coral_cr   0xfbea
#define coral1_cr   0xfb8a
#define coral2_cr   0xeb4a
#define coral3_cr   0xcac8
#define coral4_cr   0x89e5
#define cornflowerblue_cr   0x64bd
#define cornsilk_cr   0xffdb
#define cornsilk1_cr   0xffdb
#define cornsilk2_cr   0xef59
#define cornsilk3_cr   0xce56
#define cornsilk4_cr   0x8c4f
#define crimson_cr   0xd8a7
#define cyan_cr   0x07ff
#define cyan1_cr   0x07ff
#define cyan2_cr   0x077d
#define cyan3_cr   0x0679
#define cyan4_cr   0x0451
#define darkblue_cr   0x0011
#define darkcyan_cr   0x0451
#define darkgoldenrod_cr   0xbc21
#define darkgoldenrod1_cr   0xfdc1
#define darkgoldenrod2_cr   0xed61
#define darkgoldenrod3_cr   0xcca1
#define darkgoldenrod4_cr   0x8b21
#define darkgray_cr   0xad55
#define darkgreen_cr   0x0320
#define darkgrey_cr   0xad55
#define darkkhaki_cr   0xbdad
#define darkmagenta_cr   0x8811
#define darkolivegreen_cr   0x5345
#define darkolivegreen1_cr   0xcfee
#define darkolivegreen2_cr   0xbf6d
#define darkolivegreen3_cr   0xa66b
#define darkolivegreen4_cr   0x6c47
#define darkorange_cr   0xfc60
#define darkorange1_cr   0xfbe0
#define darkorange2_cr   0xeba0
#define darkorange3_cr   0xcb20
#define darkorange4_cr   0x8a20
#define darkorchid_cr   0x9999
#define darkorchid1_cr   0xb9ff
#define darkorchid2_cr   0xb1dd
#define darkorchid3_cr   0x9999
#define darkorchid4_cr   0x6911
#define darkred_cr   0x8800
#define darksalmon_cr   0xecaf
#define darkseagreen_cr   0x8df1
#define darkseagreen1_cr   0xc7f8
#define darkseagreen2_cr   0xb776
#define darkseagreen3_cr   0x9e73
#define darkseagreen4_cr   0x6c4d
#define darkslateblue_cr   0x49f1
#define darkslategray_cr   0x2a69
#define darkslategray1_cr   0x97ff
#define darkslategray2_cr   0x8f7d
#define darkslategray3_cr   0x7e79
#define darkslategray4_cr   0x5451
#define darkslategrey_cr   0x2a69
#define darkslategrey1_cr   0x97ff
#define darkslategrey2_cr   0x8f7d
#define darkslategrey3_cr   0x7e79
#define darkslategrey4_cr   0x5451
#define darkslategrey5_cr   0x4b2c
#define darkslategrey6_cr   0x2a28
#define darkslategrey7_cr   0x1124
#define darkturquoise_cr   0x067a
#define darkviolet_cr   0x901a
#define deeppink_cr   0xf8b2
#define deeppink1_cr   0xf8b2
#define deeppink2_cr   0xe891
#define deeppink3_cr   0xc88e
#define deeppink4_cr   0x884a
#define deepskyblue_cr   0x05ff
#define deepskyblue1_cr   0x05ff
#define deepskyblue2_cr   0x059d
#define deepskyblue3_cr   0x04d9
#define deepskyblue4_cr   0x0351
#define dimgray_cr   0x6b4d
#define dimgrey_cr   0x6b4d
#define dodgerblue_cr   0x1c9f
#define dodgerblue1_cr   0x1c9f
#define dodgerblue2_cr   0x1c3d
#define dodgerblue3_cr   0x1bb9
#define dodgerblue4_cr   0x1271
#define firebrick_cr   0xb104
#define firebrick1_cr   0xf986
#define firebrick2_cr   0xe965
#define firebrick3_cr   0xc924
#define firebrick4_cr   0x88c3
#define floralwhite_cr   0xffde
#define forestgreen_cr   0x2444
#define gainsboro_cr   0xdefb
#define ghostwhite_cr   0xffdf
#define gold_cr   0xfea0
#define gold1_cr   0xfea0
#define gold2_cr   0xee40
#define gold3_cr   0xcd60
#define gold4_cr   0x8ba0
#define goldenrod_cr   0xdd24
#define goldenrod1_cr   0xfe04
#define goldenrod2_cr   0xeda4
#define goldenrod3_cr   0xccc3
#define goldenrod4_cr   0x8b42
#define gray_cr   0xbdf7
#define gray0_cr   0x0000
#define gray1_cr   0x0000
#define gray2_cr   0x0020
#define gray3_cr   0x0841
#define gray4_cr   0x0841
#define gray5_cr   0x0861
#define gray6_cr   0x0861
#define gray7_cr   0x1082
#define gray8_cr   0x10a2
#define gray9_cr   0x10a2
#define gray10_cr   0x18c3
#define gray11_cr   0x18e3
#define gray12_cr   0x18e3
#define gray13_cr   0x2104
#define gray14_cr   0x2124
#define gray15_cr   0x2124
#define gray16_cr   0x2945
#define gray17_cr   0x2945
#define gray18_cr   0x2965
#define gray19_cr   0x3186
#define gray20_cr   0x3186
#define gray21_cr   0x31a6
#define gray22_cr   0x39c7
#define gray23_cr   0x39c7
#define gray24_cr   0x39e7
#define gray25_cr   0x4208
#define gray26_cr   0x4208
#define gray27_cr   0x4228
#define gray28_cr   0x4228
#define gray29_cr   0x4a49
#define gray30_cr   0x4a69
#define gray31_cr   0x4a69
#define gray32_cr   0x528a
#define gray33_cr   0x52aa
#define gray34_cr   0x52aa
#define gray35_cr   0x5acb
#define gray36_cr   0x5aeb
#define gray37_cr   0x5aeb
#define gray38_cr   0x630c
#define gray39_cr   0x630c
#define gray40_cr   0x632c
#define gray41_cr   0x6b4d
#define gray42_cr   0x6b4d
#define gray43_cr   0x6b6d
#define gray44_cr   0x738e
#define gray45_cr   0x738e
#define gray46_cr   0x73ae
#define gray47_cr   0x7bcf
#define gray48_cr   0x7bcf
#define gray49_cr   0x7bef
#define gray50_cr   0x7bef
#define gray51_cr   0x8410
#define gray52_cr   0x8430
#define gray53_cr   0x8430
#define gray54_cr   0x8c51
#define gray55_cr   0x8c71
#define gray56_cr   0x8c71
#define gray57_cr   0x9492
#define gray58_cr   0x94b2
#define gray59_cr   0x94b2
#define gray60_cr   0x9cd3
#define gray61_cr   0x9cf3
#define gray62_cr   0x9cf3
#define gray63_cr   0xa514
#define gray64_cr   0xa514
#define gray65_cr   0xa534
#define gray66_cr   0xad55
#define gray67_cr   0xad55
#define gray68_cr   0xad75
#define gray69_cr   0xb596
#define gray70_cr   0xb596
#define gray71_cr   0xb5b6
#define gray72_cr   0xbdd7
#define gray73_cr   0xbdd7
#define gray74_cr   0xbdf7
#define gray75_cr   0xbdf7
#define gray76_cr   0xc618
#define gray77_cr   0xc638
#define gray78_cr   0xc638
#define gray79_cr   0xce59
#define gray80_cr   0xce79
#define gray81_cr   0xce79
#define gray82_cr   0xd69a
#define gray83_cr   0xd6ba
#define gray84_cr   0xd6ba
#define gray85_cr   0xdedb
#define gray86_cr   0xdedb
#define gray87_cr   0xdefb
#define gray88_cr   0xe71c
#define gray89_cr   0xe71c
#define gray90_cr   0xe73c
#define gray91_cr   0xef5d
#define gray92_cr   0xef5d
#define gray93_cr   0xef7d
#define gray94_cr   0xf79e
#define gray95_cr   0xf79e
#define gray96_cr   0xf7be
#define gray97_cr   0xf7be
#define gray98_cr   0xffdf
#define gray99_cr   0xffff
#define gray100_cr   0xffff
#define green_cr   0x07e0
#define green1_cr   0x07e0
#define green2_cr   0x0760
#define green3_cr   0x0660
#define green4_cr   0x0440
#define green5_cr   0x0340
#define green6_cr   0x0240
#define green7_cr   0x0140
#define green8_cr   0x00c0
#define green9_cr   0x0040
#define greenyellow_cr   0xafe5
#define grey_cr   0xbdf7
#define grey0_cr   0x0000
#define grey1_cr   0x0000
#define grey2_cr   0x0020
#define grey3_cr   0x0841
#define grey4_cr   0x0841
#define grey5_cr   0x0861
#define grey6_cr   0x0861
#define grey7_cr   0x1082
#define grey8_cr   0x10a2
#define grey9_cr   0x10a2
#define grey10_cr   0x18c3
#define grey11_cr   0x18e3
#define grey12_cr   0x18e3
#define grey13_cr   0x2104
#define grey14_cr   0x2124
#define grey15_cr   0x2124
#define grey16_cr   0x2945
#define grey17_cr   0x2945
#define grey18_cr   0x2965
#define grey19_cr   0x3186
#define grey20_cr   0x3186
#define grey21_cr   0x31a6
#define grey22_cr   0x39c7
#define grey23_cr   0x39c7
#define grey24_cr   0x39e7
#define grey25_cr   0x4208
#define grey26_cr   0x4208
#define grey27_cr   0x4228
#define grey28_cr   0x4228
#define grey29_cr   0x4a49
#define grey30_cr   0x4a69
#define grey31_cr   0x4a69
#define grey32_cr   0x528a
#define grey33_cr   0x52aa
#define grey34_cr   0x52aa
#define grey35_cr   0x5acb
#define grey36_cr   0x5aeb
#define grey37_cr   0x5aeb
#define grey38_cr   0x630c
#define grey39_cr   0x630c
#define grey40_cr   0x632c
#define grey41_cr   0x6b4d
#define grey42_cr   0x6b4d
#define grey43_cr   0x6b6d
#define grey44_cr   0x738e
#define grey45_cr   0x738e
#define grey46_cr   0x73ae
#define grey47_cr   0x7bcf
#define grey48_cr   0x7bcf
#define grey49_cr   0x7bef
#define grey50_cr   0x7bef
#define grey51_cr   0x8410
#define grey52_cr   0x8430
#define grey53_cr   0x8430
#define grey54_cr   0x8c51
#define grey55_cr   0x8c71
#define grey56_cr   0x8c71
#define grey57_cr   0x9492
#define grey58_cr   0x94b2
#define grey59_cr   0x94b2
#define grey60_cr   0x9cd3
#define grey61_cr   0x9cf3
#define grey62_cr   0x9cf3
#define grey63_cr   0xa514
#define grey64_cr   0xa514
#define grey65_cr   0xa534
#define grey66_cr   0xad55
#define grey67_cr   0xad55
#define grey68_cr   0xad75
#define grey69_cr   0xb596
#define grey70_cr   0xb596
#define grey71_cr   0xb5b6
#define grey72_cr   0xbdd7
#define grey73_cr   0xbdd7
#define grey74_cr   0xbdf7
#define grey75_cr   0xbdf7
#define grey76_cr   0xc618
#define grey77_cr   0xc638
#define grey78_cr   0xc638
#define grey79_cr   0xce59
#define grey80_cr   0xce79
#define grey81_cr   0xce79
#define grey82_cr   0xd69a
#define grey83_cr   0xd6ba
#define grey84_cr   0xd6ba
#define grey85_cr   0xdedb
#define grey86_cr   0xdedb
#define grey87_cr   0xdefb
#define grey88_cr   0xe71c
#define grey89_cr   0xe71c
#define grey90_cr   0xe73c
#define grey91_cr   0xef5d
#define grey92_cr   0xef5d
#define grey93_cr   0xef7d
#define grey94_cr   0xf79e
#define grey95_cr   0xf79e
#define grey96_cr   0xf7be
#define grey97_cr   0xf7be
#define grey98_cr   0xffdf
#define grey99_cr   0xffff
#define grey100_cr   0xffff
#define honeydew_cr   0xf7fe
#define honeydew1_cr   0xf7fe
#define honeydew2_cr   0xe77c
#define honeydew3_cr   0xc678
#define honeydew4_cr   0x8450
#define hotpink_cr   0xfb56
#define hotpink1_cr   0xfb76
#define hotpink2_cr   0xeb54
#define hotpink3_cr   0xcb12
#define hotpink4_cr   0x89cc
#define indianred_cr   0xcaeb
#define indianred1_cr   0xfb4d
#define indianred2_cr   0xeb0c
#define indianred3_cr   0xcaaa
#define indianred4_cr   0x89c7
#define ivory_cr   0xfffe
#define ivory1_cr   0xfffe
#define ivory2_cr   0xef7c
#define ivory3_cr   0xce78
#define ivory4_cr   0x8c50
#define khaki_cr   0xf731
#define khaki1_cr   0xffb1
#define khaki2_cr   0xef30
#define khaki3_cr   0xce2e
#define khaki4_cr   0x8c29
#define lavender_cr   0xe73f
#define lavenderblush_cr   0xff9e
#define lavenderblush1_cr   0xff9e
#define lavenderblush2_cr   0xef1c
#define lavenderblush3_cr   0xce18
#define lavenderblush4_cr   0x8c10
#define lawngreen_cr   0x7fe0
#define lemonchiffon_cr   0xffd9
#define lemonchiffon1_cr   0xffd9
#define lemonchiffon2_cr   0xef57
#define lemonchiffon3_cr   0xce54
#define lemonchiffon4_cr   0x8c4e
#define lightblue_cr   0xaedc
#define lightblue1_cr   0xbf7f
#define lightblue2_cr   0xb6fd
#define lightblue3_cr   0x9e19
#define lightblue4_cr   0x6c11
#define lightcoral_cr   0xf410
#define lightcyan_cr   0xe7ff
#define lightcyan1_cr   0xe7ff
#define lightcyan2_cr   0xd77d
#define lightcyan3_cr   0xb679
#define lightcyan4_cr   0x7c51
#define lightgoldenrod_cr   0xeef0
#define lightgoldenrod1_cr   0xff71
#define lightgoldenrod2_cr   0xeef0
#define lightgoldenrod3_cr   0xcdee
#define lightgoldenrod4_cr   0x8c09
#define lightgoldenrodyellow_cr   0xffda
#define lightgray_cr   0xd69a
#define lightgreen_cr   0x9772
#define lightgrey_cr   0xd69a
#define lightpink_cr   0xfdb8
#define lightpink1_cr   0xfd77
#define lightpink2_cr   0xed15
#define lightpink3_cr   0xcc72
#define lightpink4_cr   0x8aec
#define lightsalmon_cr   0xfd0f
#define lightsalmon1_cr   0xfd0f
#define lightsalmon2_cr   0xecae
#define lightsalmon3_cr   0xcc0c
#define lightsalmon4_cr   0x8aa8
#define lightseagreen_cr   0x2595
#define lightskyblue_cr   0x867f
#define lightskyblue1_cr   0xb71f
#define lightskyblue2_cr   0xa69d
#define lightskyblue3_cr   0x8db9
#define lightskyblue4_cr   0x63d1
#define lightslateblue_cr   0x839f
#define lightslategray_cr   0x7453
#define lightslategrey_cr   0x7453
#define lightsteelblue_cr   0xb63b
#define lightsteelblue1_cr   0xcf1f
#define lightsteelblue2_cr   0xbe9d
#define lightsteelblue3_cr   0xa5b9
#define lightsteelblue4_cr   0x6bd1
#define lightyellow_cr   0xfffc
#define lightyellow1_cr   0xfffc
#define lightyellow2_cr   0xef7a
#define lightyellow3_cr   0xce76
#define lightyellow4_cr   0x8c4f
#define limegreen_cr   0x3666
#define linen_cr   0xff9c
#define magenta_cr   0xf81f
#define magenta1_cr   0xf81f
#define magenta2_cr   0xe81d
#define magenta3_cr   0xc819
#define magenta4_cr   0x8811
#define maroon_cr   0xb18c
#define maroon1_cr   0xf9b6
#define maroon2_cr   0xe994
#define maroon3_cr   0xc952
#define maroon4_cr   0x88ec
#define mediumaquamarine_cr   0x6675
#define mediumblue_cr   0x0019
#define mediumorchid_cr   0xbaba
#define mediumorchid1_cr   0xe33f
#define mediumorchid2_cr   0xd2fd
#define mediumorchid3_cr   0xb299
#define mediumorchid4_cr   0x79b1
#define mediumpurple_cr   0x939b
#define mediumpurple1_cr   0xac1f
#define mediumpurple2_cr   0x9bdd
#define mediumpurple3_cr   0x8b59
#define mediumpurple4_cr   0x5a31
#define mediumseagreen_cr   0x3d8e
#define mediumslateblue_cr   0x7b5d
#define mediumspringgreen_cr   0x07d3
#define mediumturquoise_cr   0x4e99
#define mediumvioletred_cr   0xc0b0
#define midnightblue_cr   0x18ce
#define mintcream_cr   0xf7ff
#define mistyrose_cr   0xff3c
#define mistyrose1_cr   0xff3c
#define mistyrose2_cr   0xeeba
#define mistyrose3_cr   0xcdb6
#define mistyrose4_cr   0x8bef
#define moccasin_cr   0xff36
#define navajowhite_cr   0xfef5
#define navajowhite1_cr   0xfef5
#define navajowhite2_cr   0xee74
#define navajowhite3_cr   0xcd91
#define navajowhite4_cr   0x8bcb
#define navy_cr   0x0010
#define navyblue_cr   0x0010
#define oldlace_cr   0xffbc
#define olivedrab_cr   0x6c64
#define olivedrab1_cr   0xc7e7
#define olivedrab2_cr   0xb767
#define olivedrab3_cr   0x9e66
#define olivedrab4_cr   0x6c44
#define orange0_cr   0xfe20
#define orange_cr   0xfd20
#define orange1_cr   0xfd20
#define orange2_cr   0xecc0
#define orange3_cr   0xcc20
#define orange4_cr   0x8ac0
#define orangered_cr   0xfa20
#define orangered1_cr   0xfa20
#define orangered2_cr   0xea00
#define orangered3_cr   0xc9a0
#define orangered4_cr   0x8920
#define orchid_cr   0xdb9a
#define orchid1_cr   0xfc1f
#define orchid2_cr   0xebdd
#define orchid3_cr   0xcb59
#define orchid4_cr   0x8a31
#define palegoldenrod_cr   0xef55
#define palegreen_cr   0x9fd3
#define palegreen1_cr   0x9ff3
#define palegreen2_cr   0x9772
#define palegreen3_cr   0x7e6f
#define palegreen4_cr   0x544a
#define paleturquoise_cr   0xaf7d
#define paleturquoise1_cr   0xbfff
#define paleturquoise2_cr   0xaf7d
#define paleturquoise3_cr   0x9679
#define paleturquoise4_cr   0x6451
#define palevioletred_cr   0xdb92
#define palevioletred1_cr   0xfc15
#define palevioletred2_cr   0xebd3
#define palevioletred3_cr   0xcb51
#define palevioletred4_cr   0x8a2b
#define papayawhip_cr   0xff7a
#define peachpuff_cr   0xfed7
#define peachpuff1_cr   0xfed7
#define peachpuff2_cr   0xee55
#define peachpuff3_cr   0xcd72
#define peachpuff4_cr   0x8bac
#define peru_cr   0xcc27
#define pink_cr   0xfe19
#define pink1_cr   0xfdb8
#define pink2_cr   0xed57
#define pink3_cr   0xcc93
#define pink4_cr   0x8b0d
#define plum_cr   0xdd1b
#define plum1_cr   0xfddf
#define plum2_cr   0xed7d
#define plum3_cr   0xccb9
#define plum4_cr   0x8b31
#define powderblue_cr   0xb71c
#define purple_cr   0xa11e
#define purple1_cr   0x999f
#define purple2_cr   0x917d
#define purple3_cr   0x7939
#define purple4_cr   0x50d1
#define red_cr   0xf800
#define red1_cr   0xf800
#define red2_cr   0xe800
#define red3_cr   0xc800
#define red4_cr   0x8800
#define red5_cr   0x7800
#define red6_cr   0x6800
#define red7_cr   0x5800
#define red8_cr   0x4800
#define rosybrown_cr   0xbc71
#define rosybrown1_cr   0xfe18
#define rosybrown2_cr   0xedb6
#define rosybrown3_cr   0xccd3
#define rosybrown4_cr   0x8b4d
#define royalblue_cr   0x435c
#define royalblue1_cr   0x4bbf
#define royalblue2_cr   0x437d
#define royalblue3_cr   0x3af9
#define royalblue4_cr   0x2211
#define saddlebrown_cr   0x8a22
#define salmon_cr   0xfc0e
#define salmon1_cr   0xfc6d
#define salmon2_cr   0xec0c
#define salmon3_cr   0xcb8a
#define salmon4_cr   0x8a67
#define sandybrown_cr   0xf52c
#define seagreen_cr   0x2c4a
#define seagreen1_cr   0x57f3
#define seagreen2_cr   0x4f72
#define seagreen3_cr   0x4670
#define seagreen4_cr   0x2c4a
#define seashell_cr   0xffbd
#define seashell1_cr   0xffbd
#define seashell2_cr   0xef3b
#define seashell3_cr   0xce37
#define seashell4_cr   0x8c30
#define sienna_cr   0xa285
#define sienna1_cr   0xfc08
#define sienna2_cr   0xebc8
#define sienna3_cr   0xcb47
#define sienna4_cr   0x8a24
#define skyblue_cr   0x867d
#define skyblue1_cr   0x867f
#define skyblue2_cr   0x7e1d
#define skyblue3_cr   0x6d39
#define skyblue4_cr   0x4b91
#define slateblue_cr   0x6ad9
#define slateblue1_cr   0x837f
#define slateblue2_cr   0x7b3d
#define slateblue3_cr   0x6ad9
#define slateblue4_cr   0x41f1
#define slategray_cr   0x7412
#define slategray1_cr   0xc71f
#define slategray2_cr   0xbe9d
#define slategray3_cr   0x9db9
#define slategray4_cr   0x6bd1
#define slategrey_cr   0x7412
#define slategrey1_cr   0xc71f
#define slategrey2_cr   0xbe9d
#define slategrey3_cr   0x9db9
#define slategrey4_cr   0x6bd1
#define snow_cr   0xffdf
#define snow1_cr   0xffdf
#define snow2_cr   0xef5d
#define snow3_cr   0xce59
#define snow4_cr   0x8c51
#define springgreen_cr   0x07ef
#define springgreen1_cr   0x07ef
#define springgreen2_cr   0x076e
#define springgreen3_cr   0x066c
#define springgreen4_cr   0x0448
#define steelblue_cr   0x4416
#define steelblue1_cr   0x65df
#define steelblue2_cr   0x5d7d
#define steelblue3_cr   0x4cb9
#define steelblue4_cr   0x3331
#define tan_cr   0xd5b1
#define tan1_cr   0xfd29
#define tan2_cr   0xecc9
#define tan3_cr   0xcc27
#define tan4_cr   0x8ac5
#define thistle_cr   0xddfb
#define thistle1_cr   0xff1f
#define thistle2_cr   0xee9d
#define thistle3_cr   0xcdb9
#define thistle4_cr   0x8bd1
#define tomato_cr   0xfb08
#define tomato1_cr   0xfb08
#define tomato2_cr   0xeae8
#define tomato3_cr   0xca67
#define tomato4_cr   0x89a4
#define turquoise_cr   0x471a
#define turquoise1_cr   0x07bf
#define turquoise2_cr   0x073d
#define turquoise3_cr   0x0639
#define turquoise4_cr   0x0431
#define violet_cr   0xec1d
#define violetred_cr   0xd112
#define violetred1_cr   0xf9f2
#define violetred2_cr   0xe9d1
#define violetred3_cr   0xc98f
#define violetred4_cr   0x890a
#define wheat_cr   0xf6f6
#define wheat1_cr   0xff37
#define wheat2_cr   0xeed5
#define wheat3_cr   0xcdd2
#define wheat4_cr   0x8bec
#define white_cr   0xffff
#define whitesmoke_cr   0xf7be
#define yellow_cr   0xffe0
#define yellow1_cr   0xffe0
#define yellow2_cr   0xef60
#define yellow3_cr   0xce60
#define yellow4_cr   0x8c40
#define yellow5_cr   0x7bc0
#define yellow6_cr   0x6b40
#define yellow7_cr   0x5ac0
#define yellow8_cr   0x4a40
#define yellowgreen_cr   0x9e66
#define ultramarineblue_cr   0x433e
#define electricultramarine_cr   0x381f
#define ultramarine_cr   0x1051


#endif