#include "sprite.h"
#include "game.h"

Sprite::Sprite(LPCSTR FilePath, int Width, int Height)
{
	D3DXIMAGE_INFO info;
	HRESULT result;
	_image = NULL;
	_width = Width;
	_height = Height;
	result = D3DXGetImageInfoFromFile(FilePath, &info);

	if (result != D3D_OK)
	{
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&_image
	);
	if (result != D3D_OK)
	{
		return;
	}
}

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}
