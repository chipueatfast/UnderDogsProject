#ifndef  _SCENE_H_
#define _SCENE_H_

#include <d3d9.h>
#include <d3dx9.h>


class Scene 
{
protected:

	int                     width,height;
	static bool              isDone;

public:
	Scene();
	void Init();
	virtual void InitGraphics() = 0;
	virtual void Update(int t) = 0;

	~Scene();
};

#endif //  _SCENE_H_
