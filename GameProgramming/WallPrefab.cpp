#include "WallPrefab.h"
#include "GameObject.h"


void WallPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Wall");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Wall.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\Wall.xml"));
	gameObject->state_manager()->AddToDictState("000", "Wall");
	gameObject->state_manager()->setState("000");*/
}

WallPrefab::WallPrefab()
{
}


WallPrefab::~WallPrefab()
{
}
