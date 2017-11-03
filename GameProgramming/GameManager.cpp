#include "GameManager.h"


GameManager* GameManager::mInstance = NULL;
GameManager::GameManager()
{
	mCurrentScene = nullptr;
}


GameManager* GameManager::GetInstance()
{
	if (!mInstance)
		mInstance = new GameManager();

	return mInstance;
}

GameManager::~GameManager()
{
}

Game* GameManager::GetCurrentScene()
{
	return mCurrentScene;
}

void GameManager::Update(HWND hWnd)
{
	mCurrentScene->Game_Run(hWnd);
}

void GameManager::ReplaceScene(Game* scene)
{
	delete mCurrentScene;
	mCurrentScene = scene;
}
