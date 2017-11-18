#include "RopePrefab.h"
#include "GameObject.h"


void RopePrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Rope");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Rope.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\Rope.xml"));
	gameObject->state_manager()->AddToDictState("000", "Rope");
	gameObject->state_manager()->setState("000");*/
}

RopePrefab::RopePrefab()
{
}


RopePrefab::~RopePrefab()
{
}
