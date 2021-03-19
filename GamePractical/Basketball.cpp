#include "Basketball.h"

vector<Basketball*>Basketball::poolList;
Basketball* Basketball::getBasketball(LPDIRECT3DTEXTURE9 texture) {
	Basketball* basketball = NULL;
	for (int i = 0; i < poolList.size(); i++)
	{
		if (poolList[i]->isUsing == false) {
			basketball = poolList[i];
			break;
		}
	}

	if (basketball == NULL)
	{
		basketball = new Basketball();
		basketball->create(texture);
		poolList.push_back(basketball);
	}
	return basketball;
}

void Basketball::releaseAllBasketball() {
	for (int i = 0; i < poolList.size(); i++)
	{
		poolList[i]->release();
		delete poolList[i];
		poolList[i] = NULL;
	}
	poolList.clear();
}

Basketball::Basketball() {
	gravity = D3DXVECTOR2(0,3);

}

Basketball::~Basketball() {

}

void Basketball::create(LPDIRECT3DTEXTURE9 texture) {
	this->texture = texture;
}
void Basketball::release() {

}

void Basketball::init(D3DXVECTOR2 position, D3DXVECTOR2 velocityBasketball) {
	this->position = position; 
	isUsing = true;
	tempVelocityBasketball = velocityBasketball;
}

void Basketball::hide() {
	isUsing = false;
}

void Basketball::update() {
	if (isUsing == false) {
		return;
	}

	printf("2.basketball X: %.2f\n", tempVelocityBasketball.x);
	printf("2.basketball Y: %.2f\n", tempVelocityBasketball.y);

	//WHY THE BALL WILL MOVE SO FAST
	if ((tempVelocityBasketball.y * 30) / 2)
	{
		tempVelocityBasketball += gravity;
	}
	position += tempVelocityBasketball;
}

void Basketball::draw(LPD3DXSPRITE sprite) {
	if (isUsing == false) {
		return;
	}

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}
