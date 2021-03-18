#include "GameGraphic.h"
#include "GameWin.h"

GameGraphic* GameGraphic::instance = NULL;

GameGraphic* GameGraphic::getInstance()
{
	if (instance == NULL) {
		instance = new GameGraphic();
	}
	return instance;
}

void GameGraphic::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

IDirect3DDevice9* GameGraphic::getDevice()
{
	return this->d3dDevice;
}

GameGraphic::GameGraphic() {
	//	Define Direct3D 9.
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 1252; //1269 17
	d3dPP.BackBufferHeight = 624; //662 38
	d3dPP.hDeviceWindow = GameWin::getInstance()->getHWND();

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GameWin::getInstance()->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

}

GameGraphic::~GameGraphic() {
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}

void GameGraphic::begin() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(GameWin::getInstance()->r, GameWin::getInstance()->g, 255), 1.0f, 0);
	d3dDevice->BeginScene();
}

void GameGraphic::end() {
	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}