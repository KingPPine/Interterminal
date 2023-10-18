#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <Windows.h>

void OGame::run() //runs an instance of the game on Windows
{
	onCreate(); //calls onCreate from OGame
	while (m_isRunning) //while the game is running
	{
		MSG msg = {};
		if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE)) //PeekMessage checks a special message queue. PM_REMOVE removes the message each time one is captured. The message is put into msg
		{
			if (msg.message == WM_QUIT) //if the message is the window quit action, then set the game to stop running
			{
				m_isRunning = false;
				continue; //continue to the next iteration of the loop, which will let the code reach the onQuit() method
			}
			else
			{
				//allows Windows process other messages as normal
				TranslateMessage(&msg); //Translates virtual-key messages into character messages
				DispatchMessage(&msg); //Dispatches a message to a window procedure.
			}
		}

		onUpdateInternal(); //calls this from OGame.cpp once a frame. Basically the origin of our engine loop
	}

	onQuit(); //calls onQuit from OGame.cpp. Does nothing right now
}