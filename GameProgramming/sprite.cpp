#include "sprite.h"
#include "game.h"

Sprite::Sprite(LPCSTR FilePath, int Width, int Height, int Count, int SpritesPerRow)
{
	RECT _boundingBox;
	D3DXIMAGE_INFO info;
	HRESULT result;
	_image = NULL;
	_width = Width;
	_height = Height;
	_count = Count;
	_spritesPerRow = SpritesPerRow;
	_index = 0;
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
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_image
	);
	if (result != D3D_OK)
	{
		return;
	}
}

void Sprite::Next()
{
	_index = (_index + 1) % _spritesPerRow;
}

void Sprite::Next2()
{
	if (_index >= _count)
		_index = -1;
	else if (_index != -1)
		_index++;
}


void Sprite::Render(int X, int Y, D3DXVECTOR3* AnchorPoint)
{
	RECT cameraSheet;
	cameraSheet.top = (_index / _spritesPerRow)*_height + 1;
	cameraSheet.bottom = cameraSheet.top + _height + 1;
	cameraSheet.left = 2 + (_index%_spritesPerRow)* _width;
	cameraSheet.right = cameraSheet.left + _width - 2;

	D3DXVECTOR3 position((float)X, (float)Y, 0);
	sprite_handler->Draw(
		_image,
		&cameraSheet,
		AnchorPoint,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);


}


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}
