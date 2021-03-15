#pragma once
#include "GameGraphic.h"
#include "GameWin.h"

class Player
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	RECT spriteRect;
	LPD3DXFONT font;
	RECT textRect;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 position;
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


