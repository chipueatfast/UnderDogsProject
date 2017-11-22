#pragma once
#include "GameObject.h";

class CamelPrefab
{
public:
	static void Instantiate(GameObject*,float,float, int, int);
	static void BeBeaten(GameObject* gameObject);
	CamelPrefab();
	~CamelPrefab();
};

