#pragma once
#include "GameState.h"
#include "GameWin.h"
#include "GameTimer.h"
#include <vector>
class GameStateManager
{
private:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* instance;

public:
	GameState* currentGameState;
	GameTimer* gTimer;

	void update();
	void draw();
	void changeGameState(int index);
	void control();

	static GameStateManager* getInstance();
	static void releaseInstance();

	vector<GameState*> gameStateList;
};

