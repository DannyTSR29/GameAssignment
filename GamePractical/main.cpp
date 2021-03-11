//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include "GameWin.h"
#include "GameGraphic.h"
#include "GameInput.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "lvl1.h"
#include "lvl2.h"
//--------------------------------------------------------------------

int main()
{
	GameWin* dWin = dWin->getInstance();

	//	IMPORTANT // To Do: Ensure window is created successfully then only create D3D9 device. 
	dWin->createWindow();
	 
	GameGraphic* dGraphic = dGraphic->getInstance();
	GameInput* dInput = dInput->getInstance();
	GameStateManager* dManager = dManager->getInstance();


	//bool isRunning = dWin->getIsFullScreen();

	while (dWin->gameloop())
	{
		//Input always first 
		dInput->playerControl();
		
		dManager->update();

		//	Begin the scene
		dGraphic->begin();

		dManager->draw();

		//	End the scene
		dGraphic->end();
	}

	dManager->releaseInstance();

	dWin->clearWindow();

	dGraphic->releaseInstance();
	dInput->releaseInstance();
	dWin->releaseInstance();

	return 0;
}
//--------------------------------------------------------------------

