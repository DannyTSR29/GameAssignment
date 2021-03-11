#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class GameWin
{
private:
	//	Window handle
	static GameWin* instance;
	HWND g_hWnd;
	HINSTANCE hInstance;
	//	Window's structure
	WNDCLASS wndClass;
	bool isFullscreen;
	GameWin();

public:
	int r;
	int g;
	int	b;
	int x;
	int x_direction;
	float y;
	int	speed;
	int hp;

	static GameWin* getInstance();
	static void releaseInstance();
	void createWindow();
	bool gameloop();
	void clearWindow();
	HWND getHWND();
	void setIsFullScreen(bool isFullScreen);
	bool getIsFullScreen();
};
