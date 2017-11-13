#include "StateManager.h"


State StateManager::GetStateByCode(string stateCode)
{
	return _mapState[(_dictState[stateCode])];
}

StateManager::StateManager()
{
	_curState = State();
}
StateManager::~StateManager()
{

}

void StateManager::AddToDictState(string key, string data)
{
	_dictState[key] = data;
	return;
}

StateManager::StateManager(char* xmlpath)
{
	xml_document fileXml;
	xml_parse_result result = fileXml.load_file(xmlpath);
	xml_node root = fileXml.child("Animations");

	for (xml_node nodeAnimation = root.first_child(); nodeAnimation; nodeAnimation = nodeAnimation.next_sibling())
	{

		string name = nodeAnimation.attribute("name").value();
		vector <RECT> srcRect;
		for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
		{
			RECT rect;
			rect.top = atoi(nodeRec.attribute("y").value());
			rect.left = atoi(nodeRec.attribute("x").value());
			rect.bottom = atoi(nodeRec.attribute("h").value()) + rect.top;
			rect.right = atoi(nodeRec.attribute("w").value()) + rect.left;
			srcRect.push_back(rect); 
		}
		_mapState[name] = State(name, srcRect);
		_lifeSpan = 12;

	}
	_curState = _mapState["Idle1"];
}


void StateManager::setState(string stateCode)
{
	if (_dictState[stateCode] != "")
	{	
		string targetState = _dictState[stateCode];
		_lifeSpan = _mapState[targetState].getListRect().size();
		_curState = _mapState[targetState];
	}

}
