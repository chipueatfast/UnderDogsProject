#include "ApplePrefab.h"
#include "GameObject.h"


void ApplePrefab::Instantiate(GameObject* gameObject,float x, float y,int width, int height)
{
	gameObject->set_name("Apple");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\apple.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\Apple.xml"));
	gameObject->state_manager()->AddToDictState("000", "Apple");
	gameObject->state_manager()->setState("000"); 
}

ApplePrefab::ApplePrefab()
{
}


ApplePrefab::~ApplePrefab()
{
}
