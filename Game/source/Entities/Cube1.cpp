#include <Entities/Cube1.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Cube1::Cube1()
{

}

Cube1::~Cube1()
{
}

void Cube1::onCreate()
{
	model = new Model(std::string("Assets/Models/TestCube/testCube.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/model_loading.vert";
	fragmentShaderPath = L"Assets/Shaders/model_loading.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	OEntity::onCreate();
}

void Cube1::onUpdate(float deltaTime)
{
	timeValue += deltaTime;

	rotation.x = 0.3f * timeValue;
	rotation.y = 1.0f * timeValue;
	rotation.z = 0.7f * timeValue;
}

void Cube1::onDraw()
{
	OEntity::onDraw();
}
