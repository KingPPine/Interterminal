#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	//TODO: CHECK WHY THIS CODE MATTERS. It seems like CWin32Window.cpp makes this code irrelevant, because it overwrites values like the viewport rectangle

	//this is the process to register a local window and use it to create a main window
	WNDCLASSEX wc = {}; //WNDCLASSEX is similar to WNDCLASS, except it includes cbSize (which specifies the size of the structure)
	//fill in the window class structure with parameters that describe the main window.
	wc.style = CS_OWNDC; //this creates a unique "DC" (device context) for the window. more details: https://devblogs.microsoft.com/oldnewthing/20060601-06/?p=31003
	wc.lpfnWndProc = DefWindowProcA; //lpfnWndProc points to the window procedure. "DefWindowProcA" calls the default window procedure to provide default processing
	wc.lpszClassName = L"OGL3DDummyWindow"; //specifies the window class name
	wc.cbSize = sizeof(WNDCLASSEX); //specifies the size of the structure

	auto classId = RegisterClassEx(&wc); //registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function
	assert(classId); //asserts the window class was created successfully

	RECT rc = { 0,0,1024,768 }; //rectangle of the window. This should be pulled from a static preferences file or something (same as the window's viewport)

	auto dummyWindow = CreateWindowEx( //this function creates the window with an extended style (otherwise it's idetical to CreateWindow)
		WS_EX_LEFT, //the extended style. Technically this is just an unsigned integer. WS_EX_LEFT = 0, creates a window that has generic left-aligned properties. This is the default
		MAKEINTATOM(classId), //Long pointer to a null-terminated string or an integer atom. If this parameter is an atom, it must be a global atom created by a previous call to the RegisterClass function.
		L"OGL3DDummyWindow", //Long pointer to a null-terminated string that specifies the window name.
		WS_OVERLAPPED, //the style of window. Technically this is just an unsigned integer. WS_OVERLAPPED = 0, Creates an overlapped window. An overlapped window has a title bar and a border
		CW_USEDEFAULT, //initial horizontal position of the window (upper left in screen coordinates). CW_USEDEFAULT the system selects the default position.
		CW_USEDEFAULT, //initial vertical position of the window (upper left in screen coordinates). CW_USEDEFAULT the system selects the default position.
		CW_USEDEFAULT, //specifies the width of the window. CW_USEDEFAULT selects a default width and height for the window
		CW_USEDEFAULT, //specifies the width of the window. CW_USEDEFAULT selects a default width and height for the window
		0, //handle to the parent of orner window. Only matters for child or owned windows
		0, //handle to the menu, or a child-window identifier. Doesn't matter here either
		wc.hInstance, //handle to the instance of the module to be associated with the window
		0); //Long pointer to a value to be passed to the window through the CREATESTRUCT structure passed in the lParam parameter the WM_CREATE message.

	assert(dummyWindow); //check that the windows was created successfully

	//Initializing OpenGL
	auto dummyDC = GetDC(dummyWindow); //DC = Device Context. GetDC() retrieves a handle to a DC for the client area of a specified window.
	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize = sizeof(pixelFormatDesc);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;
	pixelFormatDesc.cStencilBits = 8;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	bool res = wglMakeCurrent(dummyDC, dummyContext);
	assert(res);

	if (!gladLoadWGL(dummyDC))
		OGL3D_ERROR("OGraphicsEngine - Error - gladLoadWGL failed");

	if (!gladLoadGL())
		OGL3D_ERROR("OGraphicsEngine - Error - gladLoadGL failed");

	//If everything worked fine, OpenGL is loaded
	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{

}
