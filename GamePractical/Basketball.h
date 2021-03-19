#pragma once
#include "GameWin.h"
#include "GameGraphic.h"
#include <vector>

class Basketball
{
private:
	Basketball();
	~Basketball();

	static vector<Basketball*> poolList;

	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIX mat;
	D3DXVECTOR2 position;

	D3DXVECTOR2 tempVelocityBasketball;
	D3DXVECTOR2 gravity;

	bool isUsing;

	void create(LPDIRECT3DTEXTURE9 texture);
	void release();
public:
	static Basketball* getBasketball(LPDIRECT3DTEXTURE9 texture);
	static void releaseAllBasketball();

	void init(D3DXVECTOR2 position, D3DXVECTOR2 velocityBasketball);
	void hide();

	void update();
	void draw(LPD3DXSPRITE sprite);


};

