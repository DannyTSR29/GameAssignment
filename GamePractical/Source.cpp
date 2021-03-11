//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include "GameWin.h"
#include "GameGraphic.h"
#include <d3dx9.h>
#include <dinput.h>
//--------------------------------------------------------------------

int main()
{
	GameWin* dWin = dWin->getInstance();

	//	IMPORTANT // To Do: Ensure window is created successfully then only create D3D9 device. 
	dWin->createWindow();

	GameGraphic* dGraphic = new GameGraphic();

	//START SPRITE
	//Object Sprite and texture
	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite = NULL;


	//Create Sprite Device
	D3DXCreateSprite(dGraphic->d3dDevice, &sprite);


	//	Create texture. Study the documentation.
	//D3DXCreateTextureFromFile(dGraphic->d3dDevice, "bg1.png", &texture);
	D3DXCreateTextureFromFileEx(dGraphic->d3dDevice, "bc.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
	D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
	D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
	NULL, NULL, &texture);

	//Rect for sprite
	RECT spriteRect;
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 626;
	spriteRect.bottom = 313;

	RECT spriteRect1;
	spriteRect1.left = 29;
	spriteRect1.top = 350;
	spriteRect1.right = 103;
	spriteRect1.bottom = 417;

	//END SPRITE


	//START FONT
	//Object Font
	LPD3DXFONT font = NULL;

	//	Create font. Study the documentation.
	D3DXCreateFont(dGraphic->d3dDevice, 25, 0, 0, 1, false,
	DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	//Rect for font text
	RECT textRect;
	textRect.left = 0;
	textRect.top = -100;
	textRect.right = 0;
	textRect.bottom = 0;
	//END FONT


	//START MATRIX
	//Object Matrix
	D3DXMATRIX mat;
	float rotation = 0;
	//END MATRIX


	//START INPUT
	//Direct input object
	LPDIRECTINPUT8 dInput;
	//Direct input keyboard device
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;

	//Create the Direct Input object.
	DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	dInputKeyboardDevice->SetCooperativeLevel(dWin->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//	Key input buffer
	BYTE  diKeys[256] = {0};
	//END INPUT


	bool isRunning = dWin->getIsFullScreen();
	
	HRESULT result;
	while (dWin->gameloop())
	{
		//Input always first 
		result = dInputKeyboardDevice->GetDeviceState(256, diKeys);
		if (FAILED(result)) {
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				//	Acquire the device.
				dInputKeyboardDevice->Acquire();
			}
		}
		if (diKeys[DIK_UP] & 0x80)
		{
			dWin->y--;
			printf("UP\n");
		}

		else if (diKeys[DIK_DOWN] & 0x80)
		{
			dWin->y++;
			printf("Down\n");
		}

		if (diKeys[DIK_LEFT] & 0x80)
		{
			dWin->x--;
			dWin->x_direction = 1;
			dWin->hp--;
			printf("LEFT\n");
		}

		else if (diKeys[DIK_RIGHT] & 0x80)
		{
			dWin->x++;
			dWin->x_direction = -1;
			dWin->hp++;
			printf("RIGHT\n");
		}

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

		// Texture being used is 64 by 64:
		D3DXVECTOR2 spriteCentre = D3DXVECTOR2(0, 0);
		// Screen position of the sprite
		D3DXVECTOR2 trans = D3DXVECTOR2(dWin->x, dWin->y);
		// Rotate based on the time passed
		rotation += 0;
		// Build our matrix to rotate, scale and position our sprite
		D3DXVECTOR2 scaling(dWin->x_direction, 1.0f);
		// out, scaling centre, scaling rotation, scaling, rotation centre, rotation,translation
		//		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);

		D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
		int i = 0;

		//	Begin the scene
		dGraphic->begin();
		//	Clear and begin scene

		//	Specify alpha blend will ensure that the sprite will render the background with alpha.
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//mat = 0;
		sprite->SetTransform(&mat);

		D3DXVECTOR3 position(65 - 29, 382 - 350, 0);

		//	Sprite rendering. Study the documentation.
		//background
		sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

		//player
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
		sprite->SetTransform(&mat);

		sprite->Draw(texture, &spriteRect1, &position, NULL, D3DCOLOR_XRGB(255, 255, 255));

		//scaling.x = 1.0f;
		//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
		////sprite->SetTransform(&mat);

		//string hpStr = to_string(dWin->hp);
		//font->DrawText(sprite, hpStr.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

		//	End sprite drawing
		sprite->End();

		//	End the scene
		dGraphic->end();

	}

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;


	dWin->clearWindow();

	delete dGraphic;

	delete dWin;
	//dWin->releaseInstance();

	return 0;
}
//--------------------------------------------------------------------

