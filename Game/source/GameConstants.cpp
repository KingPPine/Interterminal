#include <GameConstants.h>

namespace GameConstants
{
	InputManager* inputManager = new InputManager();
	Camera* camera = new Camera();
	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();

	bool isGamePaused = false;
	bool isGameInMonitorView = false;
	int screenWidth = 1920;
	int screenHeight = 1080;
	int screenCenterX = 0;
	int screenCenterY = 0;
	int relativeScreenCenterX = 0;
	int relativeScreenCenterY = 0;
	unsigned int TEXT_ARRAY_LIMIT = 200;
}