#pragma once
#include "GameState.h"
#include "GameInput.h"
#include "GameGraphic.h"
#include "GameWin.h"
#include "Sound.h"

class LoseScene : public GameState
{
private:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXFONT font;

	RECT spriteRect;
	RECT textRect;

	Sound* sound;
	bool soundPlay;


public:
	LoseScene();
	~LoseScene();

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();
};

