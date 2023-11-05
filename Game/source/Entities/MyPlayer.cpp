#include <Entities/MyPlayer.h>
#include <OGL3D/Graphics/OShaderAttribute.h>

MyPlayer::MyPlayer()
{
	mouseSensitivity = 15.0f;
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
	//global shader values
	addLightShaderAttribute(std::string("viewPos"), GameConstants::camera->cameraPosition);

	//directional light
	directionalLightIndex = addDirectionalLight();
	addLightShaderAttribute(std::string("dirLights[" + std::to_string(directionalLightIndex) + std::string("].direction")), glm::vec3(-0.2f, -1.0f, -0.3f));
	addLightShaderAttribute(std::string("dirLights[" + std::to_string(directionalLightIndex) + std::string("].ambient")), glm::vec3(0.05f, 0.05f, 0.05f));
	addLightShaderAttribute(std::string("dirLights[" + std::to_string(directionalLightIndex) + std::string("].diffuse")), glm::vec3(0.4f, 0.4f, 0.4f));
	addLightShaderAttribute(std::string("dirLights[" + std::to_string(directionalLightIndex) + std::string("].specular")), glm::vec3(0.5f, 0.5f, 0.5f));

	//spotlight
	spotLightIndex = addSpotLight();
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].position"), GameConstants::camera->cameraPosition);
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].direction"), GameConstants::camera->cameraFront);
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].ambient"), glm::vec3(0.0f, 0.0f, 0.0f));
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].diffuse"), glm::vec3(1.0f, 1.0f, 1.0f));
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].specular"), glm::vec3(1.0f, 1.0f, 1.0f));
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].constant"), 1.0f);
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].linear"), 0.09f);
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].quadratic"), 0.032f);
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].cutOff"), glm::cos(glm::radians(12.5f)));
	addLightShaderAttribute("spotLights[" + std::to_string(spotLightIndex) + std::string("].outerCutOff"), glm::cos(glm::radians(15.0f)));
}

void MyPlayer::onUpdate(f32 deltaTime)
{
	//OEntity::onUpdate(deltaTime);
#pragma region process camera input

	//this check exists to prevent weird rotations when you boot up the game
	if (!firstFrame)
	{
		//key movement
		const float cameraSpeed = 4.0f * deltaTime;
		glm::vec3 moveDirection = glm::vec3();

		if (GameConstants::inputManager->keyDown(KeyCode::W) || GameConstants::inputManager->keyHeld(KeyCode::W))
			moveDirection.z += 1;
		if (GameConstants::inputManager->keyDown(KeyCode::S) || GameConstants::inputManager->keyHeld(KeyCode::S))
			moveDirection.z -= 1;
		if (GameConstants::inputManager->keyDown(KeyCode::D) || GameConstants::inputManager->keyHeld(KeyCode::D))
			moveDirection.x += 1;
		if (GameConstants::inputManager->keyDown(KeyCode::A) || GameConstants::inputManager->keyHeld(KeyCode::A))
			moveDirection.x -= 1;
		if (GameConstants::inputManager->keyDown(KeyCode::Space) || GameConstants::inputManager->keyHeld(KeyCode::Space))
			moveDirection.y += 1;
		if (GameConstants::inputManager->keyDown(KeyCode::Ctrl) || GameConstants::inputManager->keyHeld(KeyCode::Ctrl))
			moveDirection.y -= 1;

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
		

		float cameraY = camera->cameraPosition.y;
		camera->cameraPosition += camera->cameraFront * moveDirection.z * cameraSpeed;
		camera->cameraPosition += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * moveDirection.x * cameraSpeed;
		//camera->cameraPosition.y = 0.0f; //keeps the user on ground level
		camera->cameraPosition.y = cameraY + (moveDirection.y * cameraSpeed);
	}
	else 
		firstFrame = false;
	
#pragma endregion

	//update light related shader attributes
	updateLightShaderAttribute((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].position")), GameConstants::camera->cameraPosition);
	updateLightShaderAttribute((std::string("spotLights[") + std::to_string(spotLightIndex) + std::string("].direction")), GameConstants::camera->cameraFront);
	updateLightShaderAttribute(std::string("viewPos"), GameConstants::camera->cameraPosition);
}

void MyPlayer::onDraw()
{
	//OEntity::onDraw();
}

void MyPlayer::passLightShaderAtrributes()
{
	//do nothing here, since I don't need to inherit the light shader attributes
}

void MyPlayer::setPosition(glm::vec3 newPosition)
{
	OEntity::setPosition(newPosition);
	camera->cameraPosition = newPosition;
}
