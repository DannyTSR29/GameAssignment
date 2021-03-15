#include "GameMenu.h"
#include "GameStateManager.h"

GameMenu::GameMenu() {
	sprite = NULL;
	texture = NULL;

	//Create Sprite Device
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);

	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "menu.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;


	textRect.left = 1250;
	textRect.top = 250;
	textRect.right = 0;
	textRect.bottom = 0;
}

GameMenu::~GameMenu() {
}

void GameMenu::Init() {
}

void GameMenu::Update() {
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_SPACE))
	{
		GameStateManager::getInstance()->changeGameState(1);
	}
}

void GameMenu::FixedUpdate() {

}

void GameMenu::Draw() {
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//BACKGROUND
	//	Sprite rendering. Study the documentation.
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//string gameName = "Spaceman Shooter";
	//font->DrawText(sprite, gameName.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	//	End sprite drawing
	sprite->End();
}

void GameMenu::Release() {

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

}
