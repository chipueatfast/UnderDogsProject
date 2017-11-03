#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
	
private:
	LPDIRECT3DTEXTURE9 _image;
	int	_width, _height;
	public:
	#pragma region  Properties
	LPDIRECT3DTEXTURE9 image() const
	{
		return _image;
	}

	void set_image(LPDIRECT3DTEXTURE9 direct3_d_texture9)
	{
		_image = direct3_d_texture9;
	}




	int width() const
	{
		return _width;
	}

	void set_width(int width)
	{
		_width = width;
	}

	int height() const
	{
		return _height;
	}

	void set_height(int height)
	{
		_height = height;
	}
#pragma endregion 
	Sprite(LPCSTR FilePath, int Width, int Height);

	Sprite();
	~Sprite();
};

