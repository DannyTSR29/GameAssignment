#include "lvl1.h"
#include "GameStateManager.h"

lvl1::lvl1() {

}

lvl1::~lvl1() {

}

void lvl1::inti() {
	//Create Sprite Device
	D3DXCreateSprite(GameGraphic::getInstance()->getDevice(), &sprite);

	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->getDevice(), "bc.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	//	Create font. Study the documentation.
	D3DXCreateFont(GameGraphic::getInstance()->getDevice(), 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 626;
	spriteRect.bottom = 313;

	spriteRect1.left = 25;
	spriteRect1.top = 348;
	spriteRect1.right = 104;
	spriteRect1.bottom = 418;

	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;
}

void lvl1::update() {
	if (GameInput::getInstance()->isKeyDown(DIK_0))
	{
		GameStateManager::getInstance()->changeGameState(1);
	}

	// Texture being used is 64 by 64:
	spriteCentre = D3DXVECTOR2(0, 0);
	// Screen position of the sprite
	trans = D3DXVECTOR2(GameWin::getInstance()->x, GameWin::getInstance()->y);
	// Rotate based on the time passed
	rotation += 0;
	// Build our matrix to rotate, scale and position our sprite
	scaling = D3DXVECTOR2(GameWin::getInstance()->x_direction, 1.0f);
	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation,translation

	/*if (isRunning != dWin->getIsFullScreen())
		{
			if (dWin->getIsFullScreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
				d3dPP.Windowed = false;
				d3dDevice->Reset(&d3dPP);
			}
			else if (!dWin->getIsFullScreen())
			{
				d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
				d3dPP.Windowed = true;
				d3dDevice->Reset(&d3dPP);
			}

			isRunning = dWin->getIsFullScreen();
		}*/
}

void lvl1::draw() {
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);

	//BACKGROUND
	//	Sprite rendering. Study the documentation.
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//CHARACTER
	D3DXVECTOR3 position(62 - 25, 386 - 348, 0);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect1, &position, NULL, D3DCOLOR_XRGB(255, 255, 255));


	/*string hpStr = to_string(GameWin::getInstance()->hp);
	font->DrawText(sprite, hpStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));*/

	//	End sprite drawing
	sprite->End();
}

void lvl1::release() {

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}
