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

	position += tempVelocityBasketball;
	tempVelocityBasketball *= 0.9;
	printf("2.basketball X: %.2f\n", tempVelocityBasketball.x);
	printf("2.basketball Y: %.2f\n", tempVelocityBasketball.y);

	if (tempVelocityBasketball.x <= 1)
	{
		tempVelocityBasketball.x *= 2;
		tempVelocityBasketball.y += 5;
	}

}

void Basketball::draw(LPD3DXSPRITE sprite) {
	if (isUsing == false) {
		return;
	}

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}
