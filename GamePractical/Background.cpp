#include "Background.h"
#include <stdio.h>

Background::Background() {
	sprite = NULL;
	texture = NULL;
	position.x = 1078;
	position.y = 220;
	speed = (1.0f) * 30;
	isMoving = true;
	lockMove = false;
}

Background::~Background() {

}


void Background::Init() {
	//Create Sprite Device
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);

	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "bc.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	//D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "basketballco.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
	//	D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
	//	D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
	//	NULL, NULL, &texture1);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;

	//spriteRectForce.left = 0;
	//spriteRectForce.top = 0;
	//spriteRectForce.right = 237;
	//spriteRectForce.bottom = 79;

	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;

}

void Background::Update() {
	
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

void Background::Draw() {
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);

	//BACKGROUND
	//	Sprite rendering. Study the documentation.
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
	//sprite->SetTransform(&mat);
	//sprite->Draw(textureForce, &spriteRectForce, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	

	/*string hpStr = to_string(GameWin::getInstance()->hp);
	font->DrawText(sprite, hpStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));*/

	//	End sprite drawing
	sprite->End();
}

void Background::Release() {

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}
