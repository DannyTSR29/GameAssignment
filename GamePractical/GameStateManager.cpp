#include "GameStateManager.h"
#include "lvl1.h"
#include "lvl2.h"

GameStateManager* GameStateManager::instance = NULL;

GameStateManager* GameStateManager::getInstance()
{
	if (instance == NULL) {
		instance = new GameStateManager();
	}
	return instance;
}

void GameStateManager::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}
GameStateManager::GameStateManager() {
	lvl1* dlvl1 = new lvl1;
	dlvl1->Init();

	lvl2* dlvl2 = new lvl2;
	dlvl2->Init();

	gameStateList.push_back(dlvl1);
	gameStateList.push_back(dlvl2);

	currentGameState = dlvl1;

	gTimer = new GameTimer();
	gTimer->Init(60);
}

GameStateManager::~GameStateManager() {
	delete gTimer;
	gTimer = NULL;

	for (int i = 0; i < gameStateList.size(); i++)
	{
		delete gameStateList[i];
		gameStateList[i] = NULL;
	}

}

void GameStateManager::update() {
	currentGameState->Update();
	int frameToUpdate = gTimer->framesToUpdate();
	for (int i = 0; i < frameToUpdate; i++)
	{
		currentGameState->FixedUpdate();
	}
}

void GameStateManager::draw() {
	currentGameState->Draw();
}

void GameStateManager::changeGameState(int index) {
	currentGameState = gameStateList[index];
}
