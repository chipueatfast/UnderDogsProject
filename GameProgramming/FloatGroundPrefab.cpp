#include "FloatGroundPrefab.h"
#include "GameObject.h"


void FloatGroundPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("FloatGround");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\FloatGround.png", width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\FloatGround.xml"));
	gameObject->state_manager()->AddToDictState("000", "FloatGround");
	gameObject->state_manager()->setState("000");*/
}

FloatGroundPrefab::FloatGroundPrefab()
{
}


FloatGroundPrefab::~FloatGroundPrefab()
{
}
