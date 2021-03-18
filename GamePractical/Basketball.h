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

	//sample
	D3DXVECTOR2 direction;
	D3DXVECTOR2 velocity;

	bool isUsing;

	void create(LPDIRECT3DTEXTURE9 texture);
	void release();
public:
	static Basketball* getBasketball(LPDIRECT3DTEXTURE9 texture);
	static void releaseAllBasketball();

	void init(D3DXVECTOR2 position);
	void hide();

	void update(int force);
	void draw(LPD3DXSPRITE sprite);


};

