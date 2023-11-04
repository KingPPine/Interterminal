#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Math/OMathStructs.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <GameConstants.h>

OGame::OGame() //constructor
{
	//make_unique is good for safe memory allocation of new objects. I think...
	//explanation page here: https://pvs-studio.com/en/docs/warnings/v824/
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //initializes the graphics engine to a unique pointer
	m_display = std::make_unique<OWindow>(); //initializes the display window to a unique pointer, calling the constructor
	m_entitySystem = std::make_unique<OEntitySystem>(this); //initializes the entity system to a unique pointer

	m_display->makeCurrentContext(); //calls makeCurrentContext() in CWin32Window.cpp

	m_graphicsEngine->setViewport(m_display->getInnerSize()); //sets the viewport to the size defined in m_display within its constructor
	m_graphicsEngine->EnableDepthTest();
	m_graphicsEngine->setTextureVerticallyFlip(true);//makes sure that textures are loaded in with the correct vertical orientation.
}

OGame::~OGame() //destructor
{
}

void OGame::onCreate()
{
	
}

void OGame::onUpdateInternal()
{
	//computing delta time
	auto currentTime = std::chrono::system_clock::now(); //current point in time
	auto elapsedSeconds = std::chrono::duration<double>(); //initializing a duration at 0

	//m_previousTime is a "chrono::time_point". time_since_epoch() returns the the time point since the start of its clock. 
	//basically we're checking that we're passed the first frame.
	if (m_previousTime.time_since_epoch().count()) 
		elapsedSeconds = currentTime - m_previousTime; //difference in time between frames
	m_previousTime = currentTime; //setting the previous time for the next frame

	auto deltaTime = (f32)elapsedSeconds.count(); //I think this turns it from a time point to a float of seconds


	//m_graphicsEngine->clear(OVec4(0.26f, 0.75f, 0.58f, 1)); //clears the screen with a specified colour
	m_graphicsEngine->clear(OVec4(0.0f, 0.0f, 0.0f, 1)); //clears the screen with a specified colour

	//calling the General Update, and Entity System Update
	onUpdate(deltaTime); //in OGame and MyGame to help separate regular update instructions from the matrix stuff in here
	m_entitySystem->update(deltaTime); //in OEntitySystem, which calls the update method of every entity in the game
	m_entitySystem->draw(); //in OEntitySystem, which calls the draw method of every entity in the game

	m_display->update(); //in CWin32Window.cpp, perform any updates needed for the window
	m_display->present(false); //this puts everything on our display. false means no vsync.

	//Calling the input manager update at the end of the frame, as it prepares updates for the next frame
	GameConstants::inputManager->update();
}

void OGame::onQuit()
{
}

void OGame::quit()
{
	m_isRunning = false; //tells CWin32Game.cpp to quit the app
}

OEntitySystem* OGame::getEntitySystem()
{
	return m_entitySystem.get();
}

OGraphicsEngine* OGame::getGraphicsEngine()
{
	return m_graphicsEngine.get();
}

OWindow* OGame::getWindowDisplay()
{
	return m_display.get();
}
