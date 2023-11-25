#include <Entities/TestEntity.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/Model.h>





TestEntity::TestEntity()
{
}

TestEntity::~TestEntity()
{
}

void TestEntity::onCreate()
{
	model = new Model(std::string("Assets/Models/Terminal/terminal.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/model_loading.vert";
	fragmentShaderPath = L"Assets/Shaders/model_loading.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	OEntity::onCreate();
}

void TestEntity::onUpdate(float deltaTime)
{
	//timeValue += deltaTime;

	//rotation.x = 0.3f * timeValue;
	//rotation.y = 1.0f * timeValue;
	//rotation.z = 0.7f * timeValue;
}

void TestEntity::onDraw()
{
    OEntity::onDraw();
}
