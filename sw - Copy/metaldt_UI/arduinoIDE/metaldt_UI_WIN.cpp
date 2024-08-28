// metaldt_UI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "metaldt__codeblocks.ino.h"
#include "metaldt_UI_WIN.h"
#include "GBAtext.h"
#include "RTTcolours.h"
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <bitset>

#define NUM_PEQS_WINDWS 5
//#include "preprocessed_data_from_LTSPICE_METALDT_simulation.h"

// plot extra graphs under windows to verify that ATMEGA memory optimisations are valid
#define WINDOWS_DEBUG_DISPLAY 1

#define MAX_LOADSTRING 100

#define TIMER_FAKE_INERRUPTS 13
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

bool preprocess_and_save=false;

int current_peq=0;

u8 pgm_read_byte_near(const u8 *add){
  return *add;
}

u32 pgm_read_dword_near(const u32 *add){
  return *(u32*)add;
}

u16 pgm_read_word_near(const u16 *add){
  return *(u16*)add;
}

#ifdef _WINDOWS
  u32 pgm_read_COLORREF_near(const u32 *add){
    return *(u32*)add;
  }
#else
  u16 pgm_read_COLORREF_near(const u16 *add){
    return *(u16*)add;
  }
#endif

float pgm_read_float_near(const u8 *f){
  return *(float*)f;
}



s8 display_brightness=10;

void set_display_brightness(s8 inc){
  display_brightness+=inc;
  if (display_brightness<0){
    display_brightness=0;
  }
  if (display_brightness>16){
    display_brightness=16;
  }
}

#define eigen 1

int base_offx=300;
int offx=base_offx;
int offy=50;
HDC ghdc;
DWORD gcol;
DWORD alt_gcol;
void pc(u8 _x,u8 _y,DWORD col){
  int x=(int)_x;
  int y=(int)_y;
  x*=eigen;
  y*=eigen;
  x+=offx;
  y+=offy;
//  SetPixelV(ghdc,x,y,col);
  for(int i=0;i<eigen;i++){
    for(int j=0;j<eigen;j++){
      SetPixelV(ghdc,x+i,y+j,col);
    }
  }
}


class eeprom{
public:
  eeprom(){
    load();
  }
  void load(){
    FILE *f;
    fopen_s(&f,"EEPROM_DATA.DAT","rb");
    if (f){
      fread(data,1,1024,f);
      fclose(f);
    }
  }
  void save(){
    FILE *f;
    fopen_s(&f,"EEPROM_DATA.DAT","wb");
    if (f){
      fwrite(data,1,1024,f);
      fclose(f);
    }
  }
  u8 read(u16 i){
    i=i&1023;
    return data[i];
  }
  void write(u16 i,u8 _data){
    i=i&1023;
    data[i]=_data;
    save();
  }
  u8 data[1024];
};

eeprom EEPROM;


void draw_graph();

void win_drawit(HDC hdc){
  ghdc=hdc;
  HPEN stock_dc_pen=CreatePen(PS_SOLID, 1, green6_cr);
  HGDIOBJ old_pen=SelectObject(hdc,stock_dc_pen);
  HBRUSH stock_dc_brush=CreateSolidBrush(0);
  HGDIOBJ old=SelectObject(hdc,stock_dc_brush);
  static int once=1;
  if (once){
    once=0;
    Rectangle(hdc,0,0,1600,1000);
  }
  draw_graph();
  SelectObject(hdc,old_pen);
  SelectObject(hdc,old);
  DeleteObject(stock_dc_brush);
  DeleteObject(stock_dc_pen);
}



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
  AllocConsole();
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_metaldt_UI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_metaldt_UI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_metaldt_UI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_metaldt_UI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}






s16 input_potentiometer_readings_WINDOPES[128];



//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd,10,50,0); // DISPLAY UODATE
   memcpy(input_potentiometer_readings_WINDOPES,input_potentiometer_readings,sizeof(input_potentiometer_readings));
   return TRUE;
}


#define POT_STEP 17
#define RAND_POTTY 3
void chp(){
  for(int i=0;i<NUM_POTENTIOMETERS;i++){
    s16 rand_dithering=0;
    if (rand()>((RAND_MAX*2)/3)){
      rand_dithering=1;
    }else if (rand()>(RAND_MAX/2)){
      rand_dithering=-1;
    }
    if (i!=INPUT_POT_NUMBER_ENABLE_PEQ_1 && i!=INPUT_POT_NUMBER_ENABLE_PEQ_2 && i!=INPUT_POT_NUMBER_ENABLE_PEQ_3 && i!=INPUT_POT_NUMBER_ENABLE_PEQ_4 && i!=INPUT_POT_NUMBER_ENABLE_PEQ_5){
      input_potentiometer_readings[i]=input_potentiometer_readings_WINDOPES[i]+rand_dithering;
    }
    if (input_potentiometer_readings[i]<0){
      input_potentiometer_readings[i]=0;
    }
    if (input_potentiometer_readings[i]>1023){
      input_potentiometer_readings[i]=1023;
    }
    if (input_potentiometer_readings_WINDOPES[i]<0){
      input_potentiometer_readings_WINDOPES[i]=0;
    }
    if (input_potentiometer_readings_WINDOPES[i]>1023){
      input_potentiometer_readings_WINDOPES[i]=1023;
    }
  }
}


void fill_with_test_data();

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//  trans_cols_to_16buit_for_arduino();

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
  static float a=0;

	switch (message)
	{
  	case WM_COMMAND:
      wmId    = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
        case IDM_ABOUT:
          DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
          break;
        case IDM_EXIT:
          DestroyWindow(hWnd);
          break;
        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code here...
      {
        char rtt[128];
        int peq_offset=current_peq*3;
        if (current_peq==4){
          peq_offset=16;
        }
				sprintf_s(rtt,128,"1: f=%5.3f q=%5.3f depth=%5.3f",(float)potentiometer_analog_reading[peq_offset]/1023.0f,(float)potentiometer_analog_reading[peq_offset+1]/1023.0f,(float)potentiometer_analog_reading[peq_offset+2]/1023.0f);
        RECT r;
        r.top=400;
        r.left=200;
        r.bottom=r.top+16;
        r.right=r.left+strlen(rtt)*8;
        DrawText(hdc,rtt,strlen(rtt),&r,DT_LEFT);
				sprintf_s(rtt,128,"2: current peq=%d",current_peq);
				r.top-=16;
				r.bottom-=16;
				DrawText(hdc,rtt,strlen(rtt),&r,DT_LEFT);

        win_drawit(hdc);
        EndPaint(hWnd, &ps);
      }
      break;
    case WM_TIMER:
      switch(wParam){
        case 10:
          chp();
          InvalidateRect(hWnd,0,FALSE);
          break;
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_KEYDOWN:
      {
        int peq_offset=current_peq*3;
        if (current_peq==4){
          peq_offset=16;
        }
        switch (wParam){ 
          case 'Q':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'A':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_SUBBASS]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'W':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'S':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASS]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'E':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'D':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_MID]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'R':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'F':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_HIGH]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'T':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'G':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_GAIN]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'Y':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'H':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BALANCE]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'U':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'J':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_BASSBALANCE]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'I':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]+=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]>1023){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]=1023;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case 'K':
            input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]-=POT_STEP;
            if (input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]<0){
              input_potentiometer_readings_WINDOPES[INPUT_POT_NUMBER_AUX_CONTROL_WIDTH]=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD1:
            input_potentiometer_readings_WINDOPES[peq_offset]-=POT_STEP;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD2:
            input_potentiometer_readings_WINDOPES[peq_offset]+=POT_STEP;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD4:
            input_potentiometer_readings_WINDOPES[peq_offset+1]-=POT_STEP;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD5:
            input_potentiometer_readings_WINDOPES[peq_offset+1]+=POT_STEP;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD7:
            input_potentiometer_readings_WINDOPES[peq_offset+2]-=POT_STEP;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_NUMPAD8:
            input_potentiometer_readings_WINDOPES[peq_offset+2]+=POT_STEP;
            break;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
          case '1':
            input_potentiometer_readings[INPUT_POT_NUMBER_ENABLE_PEQ_1]^=HIGH;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case '2':
            input_potentiometer_readings[INPUT_POT_NUMBER_ENABLE_PEQ_2]^=HIGH;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case '3':
            input_potentiometer_readings[INPUT_POT_NUMBER_ENABLE_PEQ_3]^=HIGH;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case '4':
            input_potentiometer_readings[INPUT_POT_NUMBER_ENABLE_PEQ_4]^=HIGH;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case '5':
            input_potentiometer_readings[INPUT_POT_NUMBER_ENABLE_PEQ_5]^=HIGH;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_RETURN:
            //          one_second_update_counter();
            break;
          case VK_SPACE:
            need_to_cycle_mode=true;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_LCONTROL:
            need_to_toggle_func=true;
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_RIGHT:
            current_peq++;
            if (current_peq>=NUM_PEQS_WINDWS){
              current_peq=0;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
          case VK_LEFT:
            current_peq--;
            if (current_peq<0){
              current_peq=NUM_PEQS_WINDWS-1;
            }
            sleep_update_outputs=SLEEP_UPDATE_OUTPUT_LINE_WIDTH;
            break;
//          case 'T':
//            SetTimer(hWnd,5,5,0); // second update
//            //        fill_with_test_data();
//            break;
//          case 'Y':
//            SetTimer(hWnd,5,1000,0); // second update
//            //        fill_with_test_data();
//            break;
            //        case 'R':
            //          rescale_temp_min_history_to_fit_history_view();
            //          break;
        }
      }
      chp();
      break;
    case WM_KEYUP:
      switch (wParam){ 
        case VK_SPACE:
          break;
        case VK_RIGHT:
          break;
        case VK_LEFT:
          break;
        case 'T':
          break;
        case 'Y':
          break;
        case 'R':
          break;
      }
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



void p(u8 x, u8 y){
  pc(x,y,gcol);
}


void vline_2p(u8 x, u8 y,COLORREF gcol2)
{
  pc(x,y,gcol);
  gcol=gcol2;
  pc(x,y+1,gcol);
}

void hline(u8 _x,u8 _y,u8 w){
  s32 x=_x+offx;
  s32 y=_y+offy;
  SetDCPenColor(ghdc,gcol);
  HGDIOBJ pen=GetStockObject(DC_PEN);
  SelectObject(ghdc,pen);
  w++;
  MoveToEx(ghdc,x,y,0);
  LineTo(ghdc,x+(s32)w,y);
//  for(u8 i=x;i<=x+w;i++){
//    p(i,y);
//  }
}


void set_alt_gcol(COLORREF col){
  alt_gcol=col;
}


void dump_EEPROM_over_radio(){
}




void schedule_minute_data_transmission(){}


void metaldt__processing_loop(u8){
}


void vline_with_masked_text(u8 x,u8 y,u8 h,COLORREF new_col){
  COLORREF ogcol=gcol;
  for(u8 i=y-h;i<=y;i++){
    switch(mask_lookup(x,i)){
      case 2:
        gcol=alt_gcol;
        break;
      case 1:
        gcol=new_col;
        break;
      case 0:
        gcol=ogcol;
    }
    p(x,i);
  }
}


void vline(u8 _x,u8 _y,u8 h){
  s32 x=(s32)_x+offx;
  s32 y=(s32)_y+offy;
  SetDCPenColor(ghdc,gcol);
  HGDIOBJ pen=GetStockObject(DC_PEN);
  SelectObject(ghdc,pen);
  MoveToEx(ghdc,x,y,0);
  h++;
  LineTo(ghdc,x,y-(s32)h);
//  RECT rr;
//  rr.left=x;
//  rr.right=x+1;
//  rr.top=y;
//  rr.bottom=y-(s32)h;
//  InvalidateRect(ghwn,&rr,false);
  if (h<0 || h>160){
    int rt=1;
  }
}

void rectfill(u8 x,u8 y,u8 w,u8 h){
  for(u8 i=x;i<=x+w;i++){
    vline(i,y,h);
  }
}

void rect(u8 x,u8 y,u8 w,u8 h){
  hline(x  ,y  ,w);
  hline(x  ,y+h,w);
  vline(x  ,y+h-1,h-2);
  vline(x+w,y+h-1,h-2);
}

 


void plot_char_3x5(u8 xp,u8 yp,u16 offset,COLORREF col){
  for(int x=0;x<3;x++){
    for(int y=0;y<5;y++){
      if (pgm_read_byte_near_font_compressed(offset+x+y*3)){
        gcol=col;
      }else{
        gcol=0;
      }
      p(x+xp,y+yp);
      if (preprocess_and_save){
        prepro_pixels[x+xp].push_back(preprocessed_pixels(y+yp,gcol));
      }
    }
  }
}

void draw_nice_borders_for_virtual_tube_event_led(){
}

float required_gm_tube_hv=400.0f;

#include "metaldt__code.cpp"

void RTT_wang_it_down_the_hardware_SPI(u8 potentiometer, u8 data_byte){
}
