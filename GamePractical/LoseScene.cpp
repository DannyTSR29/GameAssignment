#include "LoseScene.h"
#include "GameStateManager.h"

LoseScene::LoseScene() {
	sprite = NULL;
	texture = NULL;

	sound->Init();
	sound = new Sound("lose.wav", true);
}

LoseScene::~LoseScene() {

}

void LoseScene::Init() {
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);

	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "gameOver.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 841;
	spriteRect.bottom = 604;

	textRect.left = 1250;
	textRect.top = 250;
	spriteRect.right = 1252;
	spriteRect.bottom = 624;

	sound->play();
}

void LoseScene::Update() {
	if (soundPlay == true)
	{
		sound->volumeDown();
		sound->Update();
	}

	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		sound->stop();
		soundPlay = false;
		GameStateManager::getInstance()->changeGameState(1);
	}

}

void LoseScene::FixedUpdate() {

}

void LoseScene::Draw() {
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}

void LoseScene::Release() {
	sound->Release();
	sound = NULL;

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

}

