#pragma once
#include <list>
class GameObject;

class GameObjectList1
{
	static GameObjectList1* _mInstance;
	std::list<GameObject*>* _list;
	

public:
	static GameObjectList1* GetInstance();
	void Add(GameObject* gameObject);
	void Remove(GameObject* gameObject);
	std::list<GameObject*>* GetGOList();

	GameObjectList1();
	~GameObjectList1();
};

