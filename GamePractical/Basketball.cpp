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
	spriteRectBasketball.right = 25;
	spriteRectBasketball.bottom = 25;
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
	isUsing = true;
	Basketball::getInstance()->setPosition(position);
	Basketball::getInstance()->setVelocity(velocityBasketball);
}

void Basketball::hide() {
	isUsing = false;
}

void Basketball::update() {
	if (isUsing == false) {
		return;
	}
	tempPosition = Basketball::getInstance()->getPosition();

	//printf("%f\n", Basketball::getInstance()->getVelocity().x);
	//printf("%f\n", Basketball::getInstance()->getVelocity().y);
	if ((Basketball::getInstance()->getVelocity().y * 30) / 2)
	{
		Basketball::getInstance()->setVelocity(Basketball::getInstance()->getVelocity() += gravity / 3.5f);
	}
	Basketball::getInstance()->setPosition(Basketball::getInstance()->getPosition() += Basketball::getInstance()->getVelocity() / 3.5f);

	if (Basketball::getInstance()->getPosition().y >= 450)
	{
		isUsing = false;
	}
}

void Basketball::draw(LPD3DXSPRITE spriteBasketball) {
	if (isUsing == false) {
		return;
	}

	spriteBasketball->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &tempPosition);
	spriteBasketball->SetTransform(&mat);
	spriteBasketball->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	spriteBasketball->End();

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