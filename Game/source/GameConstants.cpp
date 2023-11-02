#include <GameConstants.h>

namespace GameConstants
{
	InputManager* inputManager = new InputManager();
	Camera* camera = new Camera();
	bool isGamePaused = false;
	int screenCenterX = 0;
	int screenCenterY = 0;
	int relativeScreenCenterX = 0;
	int relativeScreenCenterY = 0;
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
}