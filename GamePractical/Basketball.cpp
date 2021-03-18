#include "Basketball.h"
int forceTimer = 0;

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

void Basketball::init(D3DXVECTOR2 position) {
	this->position = position; 
	isUsing = true;
}
void Basketball::hide() {
	isUsing = false;
}

void Basketball::update(int force) {
	if (isUsing == false) {
		return;
	}

	float speed = (force) * 30;
	D3DXVECTOR2 direction;
	direction.x = 1;
	direction.y = 0;
	D3DXVECTOR2 velocity = direction * (speed / 60.0f);
	int maxAnimationTimer = 30;

	if (forceTimer < maxAnimationTimer) {
		forceTimer++;
	}

	if (forceTimer >= 30)
	{
		printf("poS: %.2f\n", velocity.x);
		velocity.x *= 0.9;
		printf("poS: %.2f\n", velocity.x);
		forceTimer = 0;
	}
	position += velocity;


	if (position.x > 1195)
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
