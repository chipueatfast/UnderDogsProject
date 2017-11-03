//updated on 02-11, chipu

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include"GameManager.h"
#include "dxinput.h"
#include "GameTime.h"
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>

#include "dxgraphics.h"
#include "game.h"
#include "Scene1.h"
#include "dxaudio.h"


//function prototypes
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE);



//window event callback function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		
		dikeyboard->Acquire();
		return 0;
	case WM_DESTROY:
		//release input objects
		Kill_Keyboard();
		if (dinput != NULL)
			dinput->Release();
		//release the Direct3D device
		if (d3ddev != NULL)
			d3ddev->Release();
		//release the Direct3D object
		if (d3d != NULL)
			d3d->Release();
		//call the "front-end" shutdown function
		GameManager::GetInstance()->GetCurrentScene()->Game_End(hWnd);
		//tell Windows to kill this program
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}



//helper function to set up the window properties
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	//fill the struct with info
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;
	//set up the window with the class info
	return RegisterClassEx(&wc);
}

//entry point for a Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	Scene1* scene1 = new Scene1();
	GameManager::GetInstance()->ReplaceScene(scene1);
	int mFPS = 1;
	MSG msg;
	float tickPerFrame = 1.0f / mFPS, delta = 0;
	HWND hWnd;
	// register the class
	MyRegisterClass(hInstance);
	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED;
	//create a new window
	hWnd = CreateWindow(
		APPTITLE, //window class
		APPTITLE, //title bar
		style, //window style
		CW_USEDEFAULT, //x position of window
		CW_USEDEFAULT, //y position of window
		SCREEN_WIDTH, //width of the window
		SCREEN_HEIGHT, //height of the window
		NULL, //parent window
		NULL, //menu
		hInstance, //application instance
		NULL); //window parameters
			   //was there an error creating the window?
	//initialize  DirectInput
	if(!Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error initializing DirectInput", "Error", MB_OK);
		return 0;

	}
	//initialize DirectSound 
	if (!Init_DirectSound(hWnd)) 
	{ 
		MessageBox(hWnd, "Error initializing DirectSound", "Error", MB_OK); 
		return 0; 
	}

	if (!hWnd)
		return FALSE;
	//display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
		return 0;
	//initialize the game
	if (!GameManager::GetInstance()->GetCurrentScene()->Game_Init(hWnd))
	{
		MessageBox(hWnd, "Error initializing the game", "Error", MB_OK);
		return 0;
	}
	// main message loop
	int done = 0;
	while (!done)
	{
		GameTime::GetInstance()->StartCounter();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;
			//decode and pass messages on to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		delta += GameTime::GetInstance()->GetCounter();
		if (delta >= tickPerFrame)
		{
			//process game loop (prevents running after window is closed)
			GameManager::GetInstance()->GetCurrentScene()->Game_Run(hWnd, delta);
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
		
		
		

	}
	return msg.wParam;
}




