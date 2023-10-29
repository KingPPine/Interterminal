#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Game/OGame.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <assert.h>
#include <GameConstants.h>

//LRESULT is just a typedef for LONG_PTR
//A callback function is a function that is passed as an argument to another function and is then called within that function.
//I believe this processes the "messages" that happen in the window. Lets us close the window when needed
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}

	//keyboard input
	case WM_KEYDOWN:
	{
		if (wParam == VK_OEM_3) //detecting a tilde
		{
			PostQuitMessage(0);
			break;
		}
		else 
		{
			bool held = lParam & 0x40000000; //this logic gets the 30th bit of lParam. If non-zero, that means the input was held.
			GameConstants::inputManager->sendInput(wParam, held);
			break;
		}
	}
	case WM_KEYUP:
	{
		GameConstants::inputManager->removeInput(wParam);
		break;
	}

	//mouse input
	case WM_LBUTTONDOWN:
	{
		GameConstants::inputManager->sendInput(wParam, false); //key commands can't be held, so just pass false
		break;
	}
	case WM_RBUTTONDOWN:
	{
		GameConstants::inputManager->sendInput(wParam, false); //key commands can't be held, so just pass false
		break;
	}
	case WM_LBUTTONUP:
	{
		GameConstants::inputManager->removeInput(wParam);
		break;
	}
	case WM_RBUTTONUP:
	{
		GameConstants::inputManager->removeInput(wParam);
		break;
	}
	case WM_MOUSEMOVE:
	{
		int xPos = LOWORD(lParam); //this gets the x position of the mouse
		int yPos = HIWORD(lParam); //this gets the y position of the mouse

		GameConstants::inputManager->sendMousePos(xPos, yPos); //for when the game is paused or a menu is up
		GameConstants::inputManager->sendMouseVelocity(xPos - GameConstants::relativeScreenCenterX, yPos - GameConstants::relativeScreenCenterY);
		
		break;
	}

	//default
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}

OWindow::OWindow() //constructor
{
	//this is the process to register a local window and use it to create a main window
	WNDCLASSEX wc = {}; //WNDCLASSEX is similar to WNDCLASS, except it includes cbSize (which specifies the size of the structure)
	//fill in the window class structure with parameters that describe the main window.
	wc.style = CS_OWNDC; //this creates a unique "DC" (device context) for the window. more details: https://devblogs.microsoft.com/oldnewthing/20060601-06/?p=31003
	wc.lpfnWndProc = &WndProc; //lpfnWndProc points to the window procedure. "DefWindowProcA" calls the default window procedure to provide default processing
	wc.lpszClassName = L"OGL3DWindow"; //specifies the window class name
	wc.cbSize = sizeof(WNDCLASSEX); //specifies the size of the structure

	auto classId = RegisterClassEx(&wc); //registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function
	assert(classId); //asserts the window class was created successfully

	rc = { 0,0,1024,768 }; //rectangle of the window. This should be pulled from a static preferences file or something
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false); //Calculates the required size of the window rectangle, based on the desired client-rectangle size.

	m_handle = CreateWindowEx( //this function creates the window with an extended style (otherwise it's identical to CreateWindow)
		WS_EX_LEFT, //the extended style. Technically this is just an unsigned integer. WS_EX_LEFT = 0, creates a window that has generic left-aligned properties. This is the default
		MAKEINTATOM(classId), //Long pointer to a null-terminated string or an integer atom. If this parameter is an atom, it must be a global atom created by a previous call to the RegisterClass function.
		L"Inter-Terminal", //Long pointer to a null-terminated string that specifies the window name.
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, //the style of window. Technically this is just an unsigned integer. WS_OVERLAPPED = 0, Creates an overlapped window. An overlapped window has a title bar and a border
		CW_USEDEFAULT, //initial horizontal position of the window (upper left in screen coordinates). CW_USEDEFAULT the system selects the default position
		CW_USEDEFAULT, //initial vertical position of the window (upper left in screen coordinates). CW_USEDEFAULT the system selects the default position.
		rc.right - rc.left, //specifies the width of the window.
		rc.bottom - rc.top, //specifies the height of the window
		NULL, //handle to the parent of orner window. Only matters for child or owned windows
		NULL, //handle to the menu, or a child-window identifier. Doesn't matter here either
		NULL, //handle to the instance of the module to be associated with the window. Not sure why it doesn't matter here.
		0); //Long pointer to a value to be passed to the window through the CREATESTRUCT structure passed in the lParam parameter the WM_CREATE message.

	assert(m_handle); // checking that the window creation was successful since m_handle would be null if it failed

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA,(LONG_PTR)this); //sets the pointer to the window so that it can be used in the WndProc function

	ShowWindow((HWND)m_handle, SW_SHOW); //sets the window's specified show state
	ShowCursor(false);
	UpdateWindow((HWND)m_handle); //Sends a WM_PAINT to the window, updating the client area


	//Creating OpenGL Render Context
	auto hDC = GetDC(HWND(m_handle)); //DC = Device Context. GetDC() retrieves a handle to a DC for the client area of a specified window.
	int pixelFormatAttributes[] = { //List of the Pixel Format Attributes, OpenGL specific this time.
		//https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
		//these attributes are not cleanly explained in documentation, although it appears to be the same as what we implemented in CWin32GraphicsEngine.cpp 
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, // The buffer can draw to a window
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE, // The buffer supports OpenGL
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE, // The buffer is double-buffered
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB, //Indicates whether the pixel format is supported by the driver. WGL_FULL_ACCELERATION_ARB means it's supported by an ICD driver
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, //the type of pixel data. RGBA for us
		WGL_COLOR_BITS_ARB, 32, //the number of color bitplanes in each color buffer. For RGBA pixel types, it is the size of the color buffer, excluding the alpha bitplanes.
		WGL_DEPTH_BITS_ARB, 24, //the  ber of alpha bitplanes in each RGBA color buffer
		WGL_STENCIL_BITS_ARB, 8, //Specifies the depth of the stencil buffer.
		0 //possibly relates to the layer type, which is now ignored
	};

	int pixelFormat = 0; //gets assigned in the wglChoosePixelFormatARB call
	UINT numFormats = 0; //gets assigned in the wglChoosePixelFormatARB call
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats); //assigns values to numFormats and pixelFormat. Attempts to match the pixel format to the device context
	assert(numFormats); //does this maybe signify the end of the attributes??

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {}; //creating the pixel format descriptor
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc); //obtains information about the pixel format and puts it into the pixel format descriptor
	SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc); //sets the pixel format to the device context

	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4, //these assign version 4.6 of OpenGL
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, //Requests an OpenGL context. WGL_CONTEXT_CORE_PROFILE_BIT_ARB = a context implementing the <compatibility> profile is returned.
		0 //does this maybe signify the end of the attributes??
	};

	m_context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes); //creates the OpenGL context
	assert(m_context); //checks that the context was created correctly
}

OWindow::~OWindow() //destructor. deletes the OpenGL context and destroys the window.
{
	wglDeleteContext(HGLRC(m_context));
	DestroyWindow((HWND)m_handle);
}

ORect OWindow::getInnerSize() //returns the size of the window, excluding the handle
{
	RECT rect = {};
	GetClientRect((HWND)m_handle, &rect);
	return ORect(rect.right - rect.left, rect.bottom - rect.top);
}

void OWindow::update()
{
	//getting the relative position of the window so that we can center the cursor, regardless of window message
	if (!GameConstants::isGamePaused && GetActiveWindow() == (HWND)m_handle)
	{
		GetClientRect((HWND)m_handle, &rc);
		ClientToScreen((HWND)m_handle, (LPPOINT)&rc.left);
		ClientToScreen((HWND)m_handle, (LPPOINT)&rc.right);

		int relativeCenterX = (rc.right - rc.left) / 2;
		int relativeCenterY = (rc.bottom - rc.top) / 2;
		int centerX = rc.left + relativeCenterX;
		int centerY = rc.top + relativeCenterY;

		GameConstants::relativeScreenCenterX = relativeCenterX;
		GameConstants::relativeScreenCenterY = relativeCenterY;
		GameConstants::screenCenterX = centerX;
		GameConstants::screenCenterY = centerY;
		SetCursorPos(centerX, centerY);
	}
}

void OWindow::makeCurrentContext() //puts the openGL context we created into the window
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));
}

void OWindow::present(bool vsync) //presents the contents of our buffer to the window
{
	wglSwapIntervalEXT(vsync); //specifies the "swap" interval. Basically sets the vsync to on or off
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE); //Swaps the front and back buffers of the main plane.
}
