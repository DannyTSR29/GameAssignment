#include "Background.h"

Background::Background() {
	sprite = NULL;
	texture = NULL;
	texture1 = NULL;
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

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "basketballco.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture1);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;

	spriteRect1.left = 0;
	spriteRect1.top = 0;
	spriteRect1.right = 1252;
	spriteRect1.bottom = 624;


	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;

	positionA.x = 100;
	positionA.y = 100;

}

void Background::Update() {
	
	if (isMoving)
	{
		animationTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = direction * (speed / 60.0f);
		position += velocity;
	}
	
}
//885
//1078
void Background::Draw() {
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);

	//BACKGROUND
	//	Sprite rendering. Study the documentation.
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &positionA);
	sprite->SetTransform(&mat);
	sprite->Draw(texture1, &spriteRect1, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	

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
