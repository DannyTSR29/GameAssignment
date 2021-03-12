#pragma once
#include <dinput.h>
class GameInput
{
private:
	//START INPUT
	//Direct input object
	LPDIRECTINPUT8 dInput;
	//Direct input keyboard device
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	//	Key input buffer
	BYTE  diKeys[256] = { 0 };
	HRESULT result;
	static GameInput* instance;
	int previousKeyState[256];

	GameInput();
	~GameInput();
public:
	static GameInput* getInstance();
	static void releaseInstance();

	void ReadKeyboard();
	bool KeyboardKeyPressed(int code);
	bool KeyboardKeyHold(int code);
	bool KeyboardKeyHoldRelease(int code);
};

