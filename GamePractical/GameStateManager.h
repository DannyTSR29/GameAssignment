#pragma once
#include "GameState.h"
#include "GameWin.h"
#include <vector>
class GameStateManager
{
private:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* instance;

public:
	GameState* currentGameState;

	void update();
	void draw();
	void changeGameState(int index);
	static GameStateManager* getInstance();
	static void releaseInstance();

	vector<GameState*> gameStateList;
};

