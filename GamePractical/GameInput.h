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

	GameInput();
	~GameInput();
public:
	static GameInput* getInstance();
	static void releaseInstance();

	void playerControl();
	bool isKeyDown(int index);
};

