#pragma once
#include "GameState.h"
#include "GameInput.h"
#include "GameGraphic.h"
#include "GameWin.h"
class lvl2 : public GameState
{
private:
	//START SPRITE
	//Object Sprite and texture
	//LPDIRECT3DTEXTURE9 texture;
	//LPD3DXSPRITE sprite;
	//LPD3DXFONT font;

	//RECT spriteRect;
	//RECT textRect;

	//D3DXMATRIX mat;
	//D3DXVECTOR2 spriteCentre;
	//D3DXVECTOR2 trans;
	//D3DXVECTOR2 scaling;
	//float rotation = 0;




public:
	lvl2();
	~lvl2();

	void inti();
	void update();
	void draw();
	void release();
};

