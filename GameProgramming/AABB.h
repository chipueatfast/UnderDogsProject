#pragma once
//new 02-11 chipu
#ifndef _AABB_H
#define _AABB_H
#include"GameObject.h"
RECT GetSweptBroadphaseRect(const RECT&);
float CheckCollision(GameObject*, GameObject*); //moving vs static
class CollisionPair
{
private:
	

	float _collisionIndex;
	GameObject* _obj1, *_obj2;

public:
	GameObject* obj1() const
	{
		return _obj1;
	}

	void set_obj1(GameObject* game_object)
	{
		_obj1 = game_object;
	}

	GameObject* obj2() const
	{
		return _obj2;
	}

	void set_obj2(GameObject* game_object)
	{
		_obj2 = game_object;
	}

	CollisionPair(GameObject*, GameObject*);
	~CollisionPair();
	static bool IsIndentical(CollisionPair* cp1, CollisionPair* cp2);


	float collision_index() const
	{
		return _collisionIndex;
	}

	void set_collision_index(float collision_index)
	{
		_collisionIndex = collision_index;
	}


};


#endif
