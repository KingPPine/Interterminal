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
	glm::vec3 lightPos = glm::vec3(0.7f, 0.2f, 2.0f);
	glm::vec3 lightPos2 = glm::vec3(2.3f, -3.3f, -4.0f);
	glm::vec3 lightPos3 = glm::vec3(-4.0f, 2.0f, -12.0f);
	glm::vec3 lightPos4 = glm::vec3(0.0f, 0.0f, -3.0f);
}