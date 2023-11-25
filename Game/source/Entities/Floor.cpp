#include <Entities/Floor.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::onCreate()
{
	model = new Model(std::string("Assets/Models/Floor/floor.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 10.0f));

	OEntity::onCreate();
}

void Floor::onUpdate(float deltaTime)
{

}

void Floor::onDraw()
{
	OEntity::onDraw();
}
