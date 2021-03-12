#pragma once
#include "GameWin.h"
class GameTimer
{
private:
	LARGE_INTEGER time_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	int requested_FPS;
	float intervalsPerFrame;

public:
	GameTimer();
	~GameTimer();

	void Init(int fps);
	int framesToUpdate();

};

