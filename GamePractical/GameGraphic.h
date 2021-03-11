#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class GameGraphic
{
private:
	IDirect3D9* direct3D9;
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3DDevice9* d3dDevice;
	GameGraphic();
	~GameGraphic();
	static GameGraphic* instance;

public:
	void begin();
	void end();

	static GameGraphic* getInstance();
	static void releaseInstance();

	IDirect3DDevice9* getDevice();
};


