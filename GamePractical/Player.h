#pragma once
#include "GameGraphic.h"
#include "GameWin.h"
#include "Basketball.h"
#include <vector>


class Player
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 textureForce;
	LPDIRECT3DTEXTURE9 textureBasketball;

	LPD3DXSPRITE sprite;
	RECT spriteRect;
	RECT spriteRectForce;
	RECT spriteRectBasketball;
	LPD3DXFONT font;
	RECT textRect;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 position;
	D3DXVECTOR2 positionForceBar;
	D3DXVECTOR2 scaling;
	float rotation;


	int characterCurrentFrame;
	float animationDuration;
	float animationTimer;
	int animationRow;
	bool isMoving;
	float speed;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 characterSize;

	int force;
	int forceTimer;
	int maxTimer;
	int maxAnimationTimer;
	int animationDefault[3];
	bool lockForce;

	vector <Basketball*> basketballList;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void FixedUpdate();
	void AnimationDefault();
	void Draw();
	void Release();


};


