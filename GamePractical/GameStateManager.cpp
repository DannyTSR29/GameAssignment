#include "GameStateManager.h"
#include "GameMenu.h"
#include "MenuUI.h"
#include "lvl1.h"
#include "WinScene.h"
#include "LoseScene.h"

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
	GameMenu* dMenu = new GameMenu;
	dMenu->Init();

	MenuUI* dUI = new MenuUI;

	lvl1* dlvl1 = new lvl1;

	WinScene* dWin = new WinScene;

	LoseScene* dLose = new LoseScene;

	gameStateList.push_back(dMenu);
	gameStateList.push_back(dUI);
	gameStateList.push_back(dlvl1);
	gameStateList.push_back(dWin);
	gameStateList.push_back(dLose);

	currentGameState = dMenu;

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
	currentGameState->Init();
}
