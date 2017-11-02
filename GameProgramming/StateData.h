#ifndef _STATE_DATA_H_
#define _STATEi_DATA_H_

#include "d3dx9.h"

class StateData
{

public:
	StateData();
	StateData(int state, LPWSTR fileXML);
	~StateData();


	int _maxindex;
	RECT* _drawRect;
};

#endif // !_PLAYER_DATA_H_
