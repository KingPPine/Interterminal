#include <Entities/Terminal.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>
#include <TextManager.h>

Terminal::Terminal()
{
	textManager = new TextManager();
}

Terminal::~Terminal()
{
}

void Terminal::onCreate()
{
	model = new Model(std::string("Assets/Models/Terminal/terminal.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	OEntity::onCreate();
}

void Terminal::onUpdate(float deltaTime)
{
	textManager->onUpdate();

	timeValue += deltaTime * 0.25f;
	
	float speed = 5.0f;
	float heightMult = 0.02f;
	position.y += glm::sin(timeValue * speed) * heightMult * deltaTime;

	resetRotation();
	lookAtFlat(&GameConstants::camera->cameraPosition);

	glm::vec3 forward = glm::vec3(rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2]);
	forward.z *= -1.0f;
	glm::vec3 right = glm::vec3(rotationMatrix[0][0], rotationMatrix[1][0], rotationMatrix[2][0]);
	right.z *= -1.0f;
	glm::vec3 up = glm::vec3(0, 1, 0);

	graphicsEngine()->PushText3D(new Text3D(textManager->getDisplayText(),
		position + (-forward * 0.5891f) + (-right * 0.5f) + (up * 0.54f), rotationMatrix, 0.0005f, glm::vec3(0.5, 0.8f, 0.2f)));

	graphicsEngine()->PushText3D(new Text3D(textManager->getCommandLineText(),
		position + (-forward * 0.5891f) + (-right * 0.5f) + (-up * 0.38f), rotationMatrix, 0.0005f, glm::vec3(0.5, 0.8f, 0.2f)));
}

void Terminal::onDraw()
{
	OEntity::onDraw();
}
