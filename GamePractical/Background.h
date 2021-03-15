#pragma once
#include "GameGraphic.h"

class Background
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture1;
	LPD3DXSPRITE sprite;
	RECT spriteRect;
	RECT spriteRect1;
	LPD3DXFONT font;
	RECT textRect;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 trans;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 position;
	D3DXVECTOR2 directionmove;
	D3DXVECTOR2 positionA;
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


