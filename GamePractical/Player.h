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
	LPDIRECT3DTEXTURE9 textureTrajectory;

	LPD3DXSPRITE sprite;
	LPD3DXSPRITE spriteBasketball;
	LPD3DXSPRITE spriteTrajectory;

	LPD3DXFONT font;
	LPD3DXLINE line;

	RECT spriteRect;
	RECT spriteRectForce;
	RECT textRect;
	RECT trajectory;


	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 position;
	D3DXVECTOR2 direction;
	D3DXVECTOR2 characterSize;
	D3DXVECTOR2 positionBasketball;
	D3DXVECTOR2 velocityBasketball;
	D3DXVECTOR2 directionBasketball;
	D3DXVECTOR2 nextPosition[15];
	D3DXVECTOR2 tempPos;
	D3DXVECTOR2 gravity;
	D3DXVECTOR2 positionForceBar;
	D3DXVECTOR2 scaling;

	float rotation;


	int characterCurrentFrame;
	int animationRow;
	float animationDuration;
	float animationTimer;
	float speed;
	float speedBasketball;
	bool isMoving;

	int basketballQty;
	int force;
	int forceTimer;
	int maxTimer;
	int maxAnimationTimer;
	int animationDefault[3];
	bool lockForce;
	int tempForce;

	vector <Basketball*> basketballList;

	static Player* instance;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void FixedUpdate();
	void AnimationDefault();
	void Draw();
	void Release();

	static Player* getInstance();
	static void releaseInstance();

	void setBasketballQty(int qty);
	int getBasketballQty();
};


