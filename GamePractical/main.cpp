//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include "GameWin.h"
#include "GameGraphic.h"
#include "GameInput.h"
#include "GameState.h"
#include "GameStateManager.h"
//--------------------------------------------------------------------

//b2Vec2 getTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n)
//{
//	//velocity and gravity are given per second but we want time step values here
//	float t = 1 / 60.0f; // seconds per time step (at 60fps)
//	b2Vec2 stepVelocity = t * startingVelocity; // m/s
//	b2Vec2 stepGravity = t * t * m_world->GetGravity(); // m/s/s
//
//	return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
//}

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
		dInput->ReadKeyboard();
		//	Begin the scene
		dGraphic->begin();

		dManager->update();

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

