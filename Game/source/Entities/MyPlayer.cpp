#include <Entities/MyPlayer.h>

MyPlayer::MyPlayer()
{
	mouseSensitivity = 15.0f;
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{

}

void MyPlayer::onUpdate(f32 deltaTime)
{
	//OEntity::onUpdate(deltaTime);
#pragma region process camera input

	//this check exists to prevent weird rotations when you boot up the game
	if (!firstFrame)
	{
		//key movement
		const float cameraSpeed = 2.0f * deltaTime;
		glm::vec2 moveDirection = glm::vec2();

		if (GameConstants::inputManager->keyDown(KeyCode::W) || GameConstants::inputManager->keyHeld(KeyCode::W))
			moveDirection.y += 1;
		if (GameConstants::inputManager->keyDown(KeyCode::S) || GameConstants::inputManager->keyHeld(KeyCode::S))
			moveDirection.y -= 1;
		if (GameConstants::inputManager->keyDown(KeyCode::D) || GameConstants::inputManager->keyHeld(KeyCode::D))
			moveDirection.x += 1;
		if (GameConstants::inputManager->keyDown(KeyCode::A) || GameConstants::inputManager->keyHeld(KeyCode::A))
			moveDirection.x -= 1;

		if (glm::length(moveDirection) != 0) moveDirection = glm::normalize(moveDirection); //normalize the vector as long as it's not a zero vector

		//mouse movement
		const float tiltSpeed = mouseSensitivity * deltaTime;
		camera->yaw += (float)GameConstants::inputManager->getMouseVelocity().x * tiltSpeed;
		camera->pitch += (float)-GameConstants::inputManager->getMouseVelocity().y * tiltSpeed;

		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;
		else if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;

		glm::vec3 lookDirection;
		lookDirection.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		lookDirection.y = sin(glm::radians(camera->pitch));
		lookDirection.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
		glm::vec3 goalFront = glm::normalize(lookDirection);
		camera->cameraFront = glm::normalize(camera->cameraFront + (goalFront * 0.015f));
		


		camera->cameraPosition += camera->cameraFront * moveDirection.y * cameraSpeed;
		camera->cameraPosition += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * moveDirection.x * cameraSpeed;
		camera->cameraPosition.y = 0.0f; //keeps the user on ground level
	}
	else 
		firstFrame = false;
	
#pragma endregion
}

void MyPlayer::onDraw()
{
	//OEntity::onDraw();
}

void MyPlayer::setPosition(glm::vec3 newPosition)
{
	OEntity::setPosition(newPosition);
	camera->cameraPosition = newPosition;
}
