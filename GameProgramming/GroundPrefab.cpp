#include "GroundPrefab.h"
#include "GameObject.h"


void GroundPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Ground");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Ground.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\Ground.xml"));
	gameObject->state_manager()->AddToDictState("000", "Ground");
	gameObject->state_manager()->setState("000");*/
}

GroundPrefab::GroundPrefab()
{
}


GroundPrefab::~GroundPrefab()
{
}
