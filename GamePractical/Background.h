#pragma once
#include "GameGraphic.h"

class Background
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	RECT spriteRect;
	LPD3DXFONT font;
	RECT textRect;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 trans;
	D3DXVECTOR2 scaling;
	float rotation;

public:
	Background();
	~Background();

	void Init();
	void Update();
	void Draw();
	void Release();
};


