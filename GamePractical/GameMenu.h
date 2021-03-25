#pragma once
#include "GameState.h"
#include "GameInput.h"
#include "GameGraphic.h"
#include "GameWin.h"
#include "Sound.h"
class GameMenu : public GameState
{
private:
	//START SPRITE
	//Object Sprite and texture
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	LPD3DXFONT font;

	RECT spriteRect;
	RECT textRect;
	Sound* sound;

	bool soundPlay;


public:
	GameMenu();
	~GameMenu();

	void Init();
	void Update();
	void FixedUpdate();
	void Draw();
	void Release();


};

