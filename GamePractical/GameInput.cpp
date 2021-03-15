#include "GameInput.h"
#include "GameWin.h"
#include "lvl1.h"

int tempPosX = 0;
float tempXDir = 0;

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
	previousKeyStateSpace[DIK_SPACE] = 0;
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

void GameInput::ReadKeyboard() {
	result = dInputKeyboardDevice->GetDeviceState(256, diKeys);
	if (FAILED(result)) {
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			//	Acquire the device.
			dInputKeyboardDevice->Acquire();
		}

	}
}

bool GameInput::KeyboardKeyHold(int code)
{
	if (diKeys[code] & 0x80)
	{
		previousKeyStateSpace[code] = 1;
		printf("1. %d\n", previousKeyStateSpace[code]);
		return true;
	}

	else if (previousKeyStateSpace[code] == 1)
	{
		previousKeyStateSpace[code] = 2;
		printf("2. %d\n", previousKeyStateSpace[code]);
	}

	return false;
}

bool GameInput::KeyboardKeyPressed(int code)
{
	if (diKeys[code] & 0x80)
	{
		previousKeyState[code] = 1;

	}
	else if (previousKeyState[code] == 1)
	{
		previousKeyState[code] = 0;
		return true;
	}
	return false;
}

