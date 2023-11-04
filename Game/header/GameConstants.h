#pragma once
#include <InputManager.h>
#include <Camera.h>
#include <glm.hpp>

class InputManager;
namespace GameConstants
{
	extern InputManager* inputManager;
	extern Camera* camera;

	extern bool isGamePaused;
	extern int screenCenterX; //center of the screen in terms of the whole monitor
	extern int screenCenterY; //center of the screen in terms of the whole monitor
	extern int relativeScreenCenterX; //center of the screen rectangle
	extern int relativeScreenCenterY; //center of the screen rectangle

	extern glm::vec3 lightPos;
	extern glm::vec3 lightPos2;
	extern glm::vec3 lightPos3;
	extern glm::vec3 lightPos4;
}