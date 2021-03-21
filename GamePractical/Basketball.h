#pragma once
#include "GameWin.h"
#include "GameGraphic.h"
#include <vector>

class Basketball
{
private:

	void create(LPDIRECT3DTEXTURE9 texture);
	void release();

	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIX mat;
	D3DXVECTOR2 gravity;
	D3DXVECTOR2 position;

	bool isUsing;

	static vector<Basketball*> poolList;
	static Basketball* instance;

public:
	Basketball();
	~Basketball();

	static Basketball* getBasketball(LPDIRECT3DTEXTURE9 texture);
	static void releaseAllBasketball();

	void init(D3DXVECTOR2 position, D3DXVECTOR2 velocityBasketball);
	void hide();

	void update();
	void draw(LPD3DXSPRITE sprite);

	RECT spriteRectBasketball;

	void setPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 getPosition();

	D3DXVECTOR2 tempVelocityBasketball;
	void setVelocity(D3DXVECTOR2 tempVelocityBasketball);
	D3DXVECTOR2 getVelocity();

	static Basketball* getInstance();
	static void releaseInstance();

};

