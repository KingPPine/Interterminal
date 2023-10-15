#pragma once
#include <OGL3D/OPrerequisites.h> //a header file full of type declarations, structs, enums, and logging formats
#include <memory> //this header defines general utilities to manage dynamic memory
#include <chrono> //the elements in this header deal with time

//these are called a "forward declaration"
//As a hangover from C, the C++ compiler works in a top-to-bottom fashion (more or less). 
//If you want your class C to refer to class A or class B in some way (via a pointer or a reference), 
//then the compiler must know about their existence beforehand.
class OGraphicsEngine; 
class OEntitySystem;
class OWindow;

class OGame
{
public:
	OGame(); //constructor. initializes the graphics engine, display, and entity system.
	virtual ~OGame(); //destructor. Does nothing right now.

	void run(); //calls run() inside CWin32Game.cpp, which calls onCreate from OGame, captures all window messages, calls onUpdateInternal() from OGame, then once the game is done running it calls onQuit() from OGame
	void quit(); //sets m_isRunning to false, triggering the end of the app in CWin32Game.cpp

	OEntitySystem* getEntitySystem(); //returns m_entitySystem.get(). "get()" extracts characters from the stream, as unformatted input

protected:
	virtual void onCreate(); //currently initializing everything for the spinning cube (vertices, texcoords, shaders, uniform data being put into the buffer)
	virtual void onUpdate(f32 deltaTime) {} //does nothing right now
	virtual void onQuit(); //does nothing right now

private:
	void onUpdateInternal(); //computing time, calling the Entity System Update, doing all the matrix operations + graphics engine calls to display the cube

protected:
	bool m_isRunning = true; //variable that determines if the game should keep running or not. Gets set to false through a call to "quit()"

	std::unique_ptr<OGraphicsEngine> m_graphicsEngine; //this declares m_graphicsEngine as a unique pointer. Gets assigned in the constructor with std::make_unique
	std::unique_ptr<OWindow> m_display; //this declares m_display as a unique pointer. Gets assigned in the constructor with std::make_unique
	std::unique_ptr<OEntitySystem> m_entitySystem; //this declares m_entitySystem as a unique pointer. Gets assigned in the constructor with std::make_unique


	OVertexArrayObjectPtr m_polygonVAO; //The Pointer to the vertex array object. This stuff should probably be in an entity class
	OUniformBufferPtr m_uniform; //The Pointer to the uniform buffer.
	OShaderProgramPtr m_shader; //The pointer tot he Shader Program, which calls both basic shaders

	std::chrono::system_clock::time_point m_previousTime; //declaration of the previous time. Gets updated in "onUpdateInternal()"
	f32 m_scale = 0; //a default value, not really used for scale anymore. used in onUpdateInternal() for messing with the matrix
};

