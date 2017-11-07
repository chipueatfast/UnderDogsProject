#include "GameObjectList1.h"

GameObjectList1* GameObjectList1::_mInstance = nullptr;

GameObjectList1* GameObjectList1::GetInstance()
{
	if (!_mInstance)
		_mInstance = new GameObjectList1();
	return _mInstance;
}

void GameObjectList1::Add(GameObject* gameObject)
{
	_list->push_back(gameObject);
	return;
}

void GameObjectList1::Remove(GameObject* gameObject)
{
	_list->remove(gameObject);
	return;
}

std::list<GameObject*>* GameObjectList1::GetGOList()
{
	return _list;
}

GameObjectList1::GameObjectList1()
{
	_list = new std::list<GameObject*>();
}


GameObjectList1::~GameObjectList1()
{
}
