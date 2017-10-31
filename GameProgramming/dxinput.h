#ifndef _DXINPUT_H 
#define _DXINPUT_H 1
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include <d3d9.h>
//function prototypes 
int Init_DirectInput(HWND); 
int Init_Keyboard(HWND); 
void Poll_Keyboard(); 
int Key_Hold(int); 
void Kill_Keyboard();
//DirectInput objects, devices, and states 
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
#endif

