#include "GameInput.h"
#include "GameWin.h"


GameInput* GameInput::instance = NULL;

GameInput* GameInput::getInstance()
{
	if (instance == NULL) {
		instance = new GameInput();
	}
	return instance;
}

void GameInput::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}


GameInput::GameInput() {
	//Create the Direct Input object.
	DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	dInputKeyboardDevice->SetCooperativeLevel(GameWin::getInstance()->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

GameInput::~GameInput() {
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInput->Release();
	dInput = NULL;
}

void GameInput::playerControl() {
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
		GameWin::getInstance()->y--;
		printf("UP\n");
	}

	else if (diKeys[DIK_DOWN] & 0x80)
	{
		GameWin::getInstance()->y++;
		printf("Down\n");
	}

	if (diKeys[DIK_LEFT] & 0x80)
	{
		GameWin::getInstance()->x--;
		GameWin::getInstance()->x_direction = -1;
		GameWin::getInstance()->hp--;
		printf("LEFT\n");
	}

	else if (diKeys[DIK_RIGHT] & 0x80)
	{
		GameWin::getInstance()->x++;
		GameWin::getInstance()->x_direction = 1;
		GameWin::getInstance()->hp++;
		printf("RIGHT\n");
	}

}

bool GameInput::isKeyDown(int index) {
	return diKeys[index] & 0x80;
}