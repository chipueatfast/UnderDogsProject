#include "ApplePrefab.h"
#include "GameObject.h"


void ApplePrefab::Instantiate(GameObject* gameObject, int x, int y)
{
	gameObject->set_name("apple");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\apple.png", 11, 12));
	gameObject->set_state_manager(new StateManager("Res\\Apple.xml"));
	gameObject->state_manager()->AddToDictState("0", "Apple");
}

ApplePrefab::ApplePrefab()
{
}


ApplePrefab::~ApplePrefab()
{
}
