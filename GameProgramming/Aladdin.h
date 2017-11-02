#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "PlayerState.h"
using namespace std;


class Aladdin : public GameObject
{
private:
	int _health;
	#pragma region State_Data
	PlayerState* _PlayerStateData;
#pragma endregion

	
	State_Name _state;

	float vx, vy;
	int width, height;
public:
	Aladdin();
	~Aladdin();

	void Init();
	void Update();
	void Render();

	void setState(PlayerState newState);
	void Move(int keycode);

	void BeHitted();
};

#endif //  _ALADDIN_H_