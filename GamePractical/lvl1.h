#pragma once
#include "GameState.h"
#include "GameGraphic.h"
#include "GameWin.h"
#include "Background.h"
#include "Player.h"

class lvl1 : public GameState
{
private:
	Background* dBackGround;
	Player* dPlayer;


public:
	lvl1();
	~lvl1();

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();


};

