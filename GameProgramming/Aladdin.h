#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include "Apple.h"
#include <iostream>
#include <vector>

using namespace std;
enum State
{

};

class Aladdin : public GameObject
{
private:
	int _health;
	State _state;
	vector <Apple> _listAplle;
	float vx, vy;
	int width, height;
public:
	Aladdin();
	~Aladdin();

	void Init();
	void Update();
	void Render();

	void setState(State state);
	void Move(int keycode);

	void BeHitted();
};

#endif //  _ALADDIN_H_