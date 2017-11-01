#include "game.h"
#include <math.h>
#include <limits>
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//simple move

LPDIRECT3DSURFACE9 kitty_image[2];
SPRITE kitty;
//collision check
int width, height;
int vx, vy;
D3DRECT movingRect, staticRect;
//timing variable
long start = GetTickCount();
//initializes the game
int Game_Init(HWND hwnd)
{
	vy = 1.0f;
	vx = 1.0f;
	width = 20.0f;
	height = 20.0f;
	movingRect.x1 = 40.0f;
	movingRect.y1 = 20.0f;
	movingRect.x2 = movingRect.x1+width;
	movingRect.y2 = movingRect.y1 + height;
	staticRect.x1 = 400.0f;
	staticRect.x2 = 420.0f;
	staticRect.y1 = 0.0f;
	staticRect.y2 = 400.0f;
	return 1;
}

void PhysicsUpdate(int delta);
//the main game loop
void Game_Run(HWND hwnd, int delta)
{	
	int timestep = 2;
	while( delta - timestep > 0)
	{
		delta -= timestep;
		
	}
	PhysicsUpdate(timestep);
	
	
	
	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, NULL);
	//start rendering
	d3ddev->BeginScene();
	
	movingRect.x2 = movingRect.x1 + width;
	movingRect.y2 = movingRect.y1 + height;
	d3ddev->Clear(1, &movingRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 255), 1.0f, NULL);
	d3ddev->Clear(1, &staticRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, NULL);
	d3ddev->EndScene();
	
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)
	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}
 
 //như bị lỗi vậy, để tao chạy lại bên máy

void PhysicsUpdate(int delta)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;
	float tEntry, tExit;

	if (vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = -std::numeric_limits<float>::infinity();
		if (staticRect.y1 > movingRect.y2 || staticRect.y2 < movingRect.y1)
		{
			movingRect.x1 += vx;			
			return;
		}
	}
	if (vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = -std::numeric_limits<float>::infinity();
		if (staticRect.x1 > movingRect.x2 || staticRect.x2 < movingRect.x1)
		{
			movingRect.y1 += vy;

			return;
		}
	}
		
	if (vx > 0)
	{
		//distance of near side with vx > 0
		dxEntry = staticRect.x1 - movingRect.x2;
		//distance of far side with vx > 0
		dxExit = staticRect.x2 - movingRect.x1;
		//time moving enter static
		txEntry = dxEntry / vx;
		txExit = dxExit / vx;	

	}
	if (vx < 0)
	{
		dxEntry = movingRect.x1 - staticRect.x2;
		dxExit = movingRect.x2 - staticRect.x1;

		txEntry = dxEntry / vx;
		txExit = dxExit / vx;
	}
	if (vy > 0)
	{
		//distance of near side with vx > 0
		dyEntry = staticRect.y1 - movingRect.y2;
		//distance of far side with vx > 0
		dyExit = staticRect.y2 - movingRect.y1;
		//time moving enter static
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;	
		if (tyEntry<0)
		{
			tyEntry = 0;
			
		}
	}
	if (vy < 0)
	{
		//distance of near side with vx > 0
		dyEntry =  movingRect.y1 - staticRect.y2;
		//distance of far side with vx > 0
		dyExit = movingRect.y2 - staticRect.y1;
		//time moving enter static
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;
		if (tyEntry>0)
		{
			tyEntry = 0;
		}
	}

	if (tyEntry != -std::numeric_limits<float>::infinity() && txEntry != -std::numeric_limits<float>::infinity())
		tEntry = max(fabs(txEntry), fabs(tyEntry));
	else tEntry = (txEntry == -std::numeric_limits<float>::infinity()) ? tyEntry : txEntry;
	if (tyExit != std::numeric_limits<float>::infinity() && txEntry != std::numeric_limits<float>::infinity())
		tExit = min(fabs(tyExit), fabs(txExit));
	else tExit = (txExit == std::numeric_limits<float>::infinity()) ? tyExit : txExit;
	if ( fabs(tEntry) <1.0f && fabs(tEntry)<fabs(tExit))
	{
		movingRect.x1 += vx*tEntry;
		movingRect.y1 += vy*tEntry;
		return;
	}
	movingRect.x1 += vx;
	movingRect.y1 += vy;
			
		
	
	
	 
}
//frees memory and cleans up before the game ends
void Game_End(HWND hwnd)
{

}
