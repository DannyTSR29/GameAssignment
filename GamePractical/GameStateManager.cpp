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
	dlvl1->inti();

	lvl2* dlvl2 = new lvl2;
	dlvl2->inti();

	gameStateList.push_back(dlvl1);
	gameStateList.push_back(dlvl2);

	currentGameState = dlvl1;

}

GameStateManager::~GameStateManager() {
	for (int i = 0; i < gameStateList.size(); i++)
	{
		delete gameStateList[i];
		gameStateList[i] = NULL;
	}
}

void GameStateManager::update() {
	currentGameState->update();
}

void GameStateManager::draw() {
	currentGameState->draw();
}

void GameStateManager::changeGameState(int index) {
	currentGameState = gameStateList[index];
}