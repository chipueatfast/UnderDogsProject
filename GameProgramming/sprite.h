#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
	
private:
	LPDIRECT3DTEXTURE9 _image;
	int _width, _height, 
		_curframe, _lastframe, 
		_animdelay, _animcount;
	int _spritesPerRow, _index, _count;
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

	int sprites_per_row() const
	{
		return _spritesPerRow;
	}

	void set_sprites_per_row(int sprites_per_row)
	{
		_spritesPerRow = sprites_per_row;
	}

	int index() const
	{
		return _index;
	}

	void set_index(int index)
	{
		_index = index;
	}

	int count() const
	{
		return _count;
	}

	void set_count(int count)
	{
		_count = count;
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

	
	int curframe() const
	{
		return _curframe;
	}

	void set_curframe(int curframe)
	{
		_curframe = curframe;
	}

	int lastframe() const
	{
		return _lastframe;
	}

	void set_lastframe(int lastframe)
	{
		_lastframe = lastframe;
	}

	int animdelay() const
	{
		return _animdelay;
	}

	void set_animdelay(int animdelay)
	{
		_animdelay = animdelay;
	}

	int animcount() const
	{
		return _animcount;
	}

	void set_animcount(int animcount)
	{
		_animcount = animcount;
	}
#pragma endregion 
	Sprite(LPCSTR FilePath, int Width, int Height, int Count, int SpritesPerRow);
	void Next();
	void Next2();//this next wont come back from the end to start
	

	Sprite();
	~Sprite();
};

