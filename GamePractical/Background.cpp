#include "Background.h"
#include <stdio.h>

Background::Background() {
	sprite = NULL;
	spriteHoop = NULL;
	texture = NULL;
	textureHoop = NULL;
	line = NULL;
	position = D3DXVECTOR2(1100,200);
	scaling = D3DXVECTOR2(1.5f, 1.5f);
	speed = (1.0f) * 30;
	isMoving = true;
	lockMove = false;

}

Background::~Background() {

}


void Background::Init() {
	//Create Sprite Device
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &spriteHoop);

	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "background.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "hoopRight.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &textureHoop);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	D3DXCreateLine(GameGraphic::getInstance()->getDevice(), &line);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;

	spriteHoopRect.left = 0;
	spriteHoopRect.top = 0;
	spriteHoopRect.right = 60;
	spriteHoopRect.bottom = 106;

	spriteBoardRect.left = 47;
	spriteBoardRect.top = 3;
	spriteBoardRect.right = 51;
	spriteBoardRect.bottom = 65;

	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;

}

void Background::Update() {

	if (checkCollision(Basketball::getInstance()->getPosition(), Basketball::getInstance()->spriteRectBasketball, position, spriteBoardRect))
	{
		D3DXVECTOR2 tempVelocity = D3DXVECTOR2(-40.0f, 1.0f);
		Basketball::getInstance()->setVelocity(tempVelocity);
		printf("run");
	}

	/*D3DXVECTOR2 velocity;
	if (isMoving)
	{
		if (position.x <= 1078 && lockMove==false) {
			direction.x = -1;
			direction.y = 0;
			velocity = direction * (speed / 60.0f);
			position += velocity;
			if (position.x <= 885) {
				lockMove = true;
				velocity.x = 0;
				velocity.y = 0;
			}
		}
		else if (position.x >= 883 && lockMove==true) {
			direction.x = 1;
			direction.y = 0;
			velocity = direction * (speed / 60.0f);
			position += velocity;
			if (position.x >= 1078) {
				lockMove = false;
			}
		}
	}*/
	
}
//885
//1078
void Background::Draw() {
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	spriteHoop->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
	spriteHoop->SetTransform(&mat);
	spriteHoop->Draw(textureHoop, &spriteHoopRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	spriteHoop->End();

	line->Begin();
	line->Draw(basketballVertices, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->Draw(hoopVertices, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->End();

	/*string hpStr = to_string(GameWin::getInstance()->hp);
font->DrawText(sprite, hpStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));*/
}

void Background::Release() {

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

}

bool Background::checkCollision(D3DXVECTOR2 positionBasketball, RECT rectBasketball, D3DXVECTOR2 positionHoop, RECT rectHoop) {
	rectBasketball.right = positionBasketball.x + rectBasketball.right - rectBasketball.left;
	rectBasketball.left = positionBasketball.x;
	rectBasketball.bottom = positionBasketball.y + rectBasketball.bottom - rectBasketball.top;
	rectBasketball.top = positionBasketball.y;

	//1100 + 0 + 47 = 1147
	rectHoop.right = positionHoop.x + 70 + rectHoop.right - rectHoop.left;
	rectHoop.left = positionHoop.x + 70;
	rectHoop.bottom = positionHoop.y +35 + rectHoop.bottom - rectHoop.top;
	rectHoop.top = positionHoop.y + 5;

	basketballVertices[0] = D3DXVECTOR2(rectBasketball.left, rectBasketball.top);
	basketballVertices[1] = D3DXVECTOR2(rectBasketball.right, rectBasketball.top);
	basketballVertices[2] = D3DXVECTOR2(rectBasketball.right, rectBasketball.bottom);
	basketballVertices[3] = D3DXVECTOR2(rectBasketball.left, rectBasketball.bottom);
	basketballVertices[4] = D3DXVECTOR2(rectBasketball.left, rectBasketball.top);

	hoopVertices[0] = D3DXVECTOR2(rectHoop.left, rectHoop.top);
	hoopVertices[1] = D3DXVECTOR2(rectHoop.right, rectHoop.top);
	hoopVertices[2] = D3DXVECTOR2(rectHoop.right, rectHoop.bottom);
	hoopVertices[3] = D3DXVECTOR2(rectHoop.left, rectHoop.bottom);
	hoopVertices[4] = D3DXVECTOR2(rectHoop.left, rectHoop.top);

	if (rectBasketball.bottom < rectHoop.top) { return false; }
	if (rectBasketball.top > rectHoop.bottom) { return false; }
	if (rectBasketball.right < rectHoop.left) { return false; }
	if (rectBasketball.left > rectHoop.right) { return false; }

	return true;
}


