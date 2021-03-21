#include "Basketball.h"

Basketball* Basketball::instance = NULL;

Basketball* Basketball::getInstance()
{
	if (instance == NULL) {
		instance = new Basketball();
	}
	return instance;
}
//comi
void Basketball::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

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
	spriteRectBasketball.left = 0;
	spriteRectBasketball.top = 0;
	spriteRectBasketball.right = 32;
	spriteRectBasketball.bottom = 32;
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
	//tempVelocityBasketball = velocityBasketball;
	Basketball::getInstance()->setVelocity(velocityBasketball);
}

void Basketball::hide() {
	isUsing = false;
}

void Basketball::update() {
	if (isUsing == false) {
		return;
	}
	printf("%f\n", Basketball::getInstance()->getVelocity().x);
	printf("%f\n", Basketball::getInstance()->getVelocity().y);

	//if ((tempVelocityBasketball.y * 30) / 2)
	//{
	//	tempVelocityBasketball += gravity / 5.0f;
	//}
	//position += tempVelocityBasketball / 5.0f;

	if ((Basketball::getInstance()->getVelocity().y * 30) / 2)
	{
		Basketball::getInstance()->setVelocity(Basketball::getInstance()->getVelocity() += gravity / 5.0f);
	}
	position += Basketball::getInstance()->getVelocity() / 5.0f;

	Basketball::getInstance()->setPosition(position);

	if (position.y >= 580)
	{
		isUsing = false;
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

void Basketball::setPosition(D3DXVECTOR2 position) {
	this->position = position;
}

D3DXVECTOR2 Basketball::getPosition() {
	return position;
}

void Basketball::setVelocity(D3DXVECTOR2 tempVelocityBasketball) {
	this->tempVelocityBasketball = tempVelocityBasketball;
}

D3DXVECTOR2 Basketball::getVelocity() {
	return tempVelocityBasketball;
}