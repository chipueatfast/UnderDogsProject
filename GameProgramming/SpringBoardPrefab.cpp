#include "SpringBoardPrefab.h"
#include "GameObject.h"


void SpringBoardPrefab::Instantiate(GameObject* gameObject, float x,float y,int width, int height)
{
	gameObject->set_name("SpringBoard");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\SpringBoard.png",width, height));
	/*gameObject->set_state_manager(new StateManager("Res\\SpringBoard.xml"));
	gameObject->state_manager()->AddToDictState("000", "SpringBoard");
	gameObject->state_manager()->setState("000");*/
}

SpringBoardPrefab::SpringBoardPrefab()
{
}


SpringBoardPrefab::~SpringBoardPrefab()
{
}
