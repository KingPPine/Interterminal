#include <Entities/Terminal.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Terminal::Terminal()
{
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
	timeValue += deltaTime;
	
	float speed = 1.5f;
	float heightMult = 0.1f;
	position.y += glm::sin(timeValue * speed) * heightMult * deltaTime;

	resetRotation();
	rotate(-timeValue * 0.5f, glm::vec3(0, 1, 0)); //y rotation
	//rotate(-timeValue * 0.2f, glm::vec3(1, 0, 0)); //x rotation

	//graphicsEngine()->PushText(new Text2D("This is sample text.\nThis is a second line.", position, 1.0f, glm::vec3(0.5, 0.8f, 0.2f))); //the graphics manager needs to transform it to 3d space
}

void Terminal::onDraw()
{
	OEntity::onDraw();
}
