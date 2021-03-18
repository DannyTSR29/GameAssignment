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
	D3DXVECTOR2 direction;
	D3DXVECTOR2 position;
	D3DXVECTOR2 directionmove;
	bool lockMove;
	float rotation;
	bool isMoving;
	float speed;
	float animationTimer;

public:
	Background();
	~Background();

	void Init();
	void Update();
	void Draw();
	void Release();
};


