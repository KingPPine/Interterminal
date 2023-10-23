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

	void setPosition(float x, float y, float z)
	{
		cameraPosition.x = x;
		cameraPosition.y = y;
		cameraPosition.z = z;
	}
	glm::vec3 getPosition() { return cameraPosition; }

	void setTarget(float x, float y, float z)
	{
		cameraTarget.x = x;
		cameraTarget.y = y;
		cameraTarget.z = z;
	}
	glm::vec3 getTarget() { return cameraTarget; }

private:
	glm::mat4 cameraViewMatrix;
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
};