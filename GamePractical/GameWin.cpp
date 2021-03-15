#include "GameWin.h"
#include "Player.h"

GameWin* GameWin::instance = NULL;

GameWin* GameWin::getInstance()
{
	if (instance == NULL) {
		instance = new GameWin();
	}
	return instance;
}
//comi
void GameWin::releaseInstance() {
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

GameWin::GameWin()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->speed = 1;
	this->hp = 100;
	this->isFullscreen = false;
	this->g_hWnd = NULL;
	this->hInstance = GetModuleHandle(NULL);
}


HWND GameWin::getHWND()
{
	return this->g_hWnd;
}

void GameWin::setIsFullScreen(bool value)
{
	isFullscreen = value;
}

bool GameWin::getIsFullScreen()
{
	return this->isFullscreen;
}


//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GameWin* dWin = dWin->getInstance();

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	

	case WM_KEYDOWN:
		//printf("%d", wParam);
		if (wParam == 27) {
			PostQuitMessage(0);
			break;
		}
		//else if (wParam == 70)
		//{
		//	if (!dWin->getIsFullScreen())
		//	{
		//		dWin->setIsFullScreen(true);
		//	}
		//	else if (dWin->getIsFullScreen())
		//	{
		//		dWin->setIsFullScreen(false);
		//	}

		//}
		else if (wParam == 82 || wParam == 71 || wParam == 66 || wParam == 187 || wParam == 189)
		{
			if (wParam == 82)
			{
				dWin->r += dWin->speed;
				if (dWin->r > 255)
				{
					dWin->r = 0;
				}
			}
			else if (wParam == 71)
			{
				dWin->g += dWin->speed;
				if (dWin->g > 255)
				{
					dWin->g = 0;
				}
			}
			else if (wParam == 66)
			{
				dWin->b += dWin->speed;
				if (dWin->b > 255)
				{
					dWin->b = 0;
				}
			}
			else if (wParam == 187)
			{
				if (!(dWin->speed >= 10))
				{
					dWin->speed += 1;
				}
			}
			else if (wParam == 189)
			{
				if (!(dWin->speed <= 1))
				{
					dWin->speed -= 1;
				}
			}

			printf("SP  :  %d  RGB  :  (%d,  %d,  %d)\n", dWin->speed, dWin->r, dWin->g, dWin->b);

		}
		


		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void GameWin::createWindow()
{

	/*
		Step 1
		Define and Register a Window.
	*/

	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));


	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	/*wndClass.hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1));
	wndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));*/
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Danny's Window", WS_OVERLAPPEDWINDOW, 0, 100, 1269, 662, g_hWnd, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//	ShowCursor(false);


}

bool GameWin::gameloop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/


	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.

		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) break;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}



	/*
		Write your code here...
	*/

	return msg.message != WM_QUIT;
}

void GameWin::clearWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

