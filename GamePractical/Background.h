#pragma once
#include "GameWin.h"
#include "GameGraphic.h"
#include "Basketball.h"
#include "Player.h"
#include<fmod.hpp>

class Background
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 textureHoop;
	LPD3DXSPRITE sprite;
	LPD3DXSPRITE spriteHoop;
	LPD3DXLINE line;

	RECT spriteRect;
	LPD3DXFONT font;
	RECT textRect;
	FMOD::System* system;               //Fmod system object
	FMOD::Sound* bgmusic;
	FMOD::Channel* bgChannel;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 trans;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 directionmove;
	bool lockMove;
	float rotation;
	bool isMoving;
	float speed;
	float animationTimer;

	D3DXVECTOR2 basketballVertices[5];
	D3DXVECTOR2 hoopVertices[5];

public:
	Background();
	~Background();

	void Init();
	void Update();
	void Draw();
	void Release();

	RECT spriteHoopRect;
	RECT spriteBoardRect;
	D3DXVECTOR2 position;
	bool checkCollision(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionHoop, RECT rectHoop);

};


