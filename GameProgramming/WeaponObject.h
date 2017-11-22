#pragma once
#include "GameObject.h"
#include "GameObjectMove.h"

class WeaponObject: public GameObject
{
	GameObjectMove* _ownerObj;
public:
	GameObjectMove* owner_obj() const
	{
		return _ownerObj;
	}

	void set_owner_obj(GameObjectMove* game_object_move)
	{
		_ownerObj = game_object_move;
	}


	WeaponObject();
	~WeaponObject();
};

