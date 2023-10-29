#pragma once
#include <OGL3D/Math/ORect.h>
#include <Windows.h>

class OWindow
{
public:
	OWindow(); //constructor. Initializes the window
	~OWindow(); //destructor. Destroys the window

	ORect getInnerSize(); //gets the size of the viewport (the indow excluding the handle at the top)
	void update(); //update functions for the window

	void makeCurrentContext(); //puts the openGL context we created into the window
	void present(bool vsync); //puts everything on our display with a choice of vsync

private:
	void* m_handle = nullptr; //pointer to the window handle
	void* m_context = nullptr; //pointer to the device context
	RECT rc;
};