#pragma once
#include <string>
#include "GameObject.h"
class GameObject;

namespace BulletPrefab
{
	void Instantiate(GameObject*, char*, int, int, GameObject::Face);
}

