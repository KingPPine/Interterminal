#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	Camera() 
	{
		setIdentity();
		cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 getViewMatrix()
	{
		return cameraViewMatrix;
	}

	void lookAt(float radius, float camX, float camZ)
	{
		cameraViewMatrix = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void setIdentity() //sets this matrix to the identity matrix (diagonal 1's from top left to bottom right, 0' otherwise)
	{
		memset(&cameraViewMatrix, 0, sizeof(cameraViewMatrix));
		cameraViewMatrix[0][0] = 1;
		cameraViewMatrix[1][1] = 1;
		cameraViewMatrix[2][2] = 1;
		cameraViewMatrix[3][3] = 1;
	}

public:
	glm::mat4 cameraViewMatrix;
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float yaw = 270.0f;
	float pitch = 0.0f;
};