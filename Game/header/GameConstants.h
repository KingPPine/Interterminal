#pragma once
#include <InputManager.h>
#include <Camera.h>
#include <glm.hpp>
#include <irrKlang.h>

class InputManager;
namespace GameConstants
{
	extern InputManager* inputManager;
	extern Camera* camera;
	extern irrklang::ISoundEngine* soundEngine;

	extern bool isGamePaused;
	extern int screenWidth; //width of the screen, used to draw the window and for the perspective matrix
	extern int screenHeight; //height of the screen, used to draw the window and for the perspective matrix
	extern int screenCenterX; //center of the screen in terms of the whole monitor
	extern int screenCenterY; //center of the screen in terms of the whole monitor
	extern int relativeScreenCenterX; //center of the screen rectangle
	extern int relativeScreenCenterY; //center of the screen rectangle
	extern unsigned int TEXT_ARRAY_LIMIT; //the limit of characters that can be drawn in one call
}