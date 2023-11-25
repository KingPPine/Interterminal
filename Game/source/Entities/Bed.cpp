#include <Entities/Bed.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Bed::Bed()
{
}
Bed::~Bed()
{
}

void Bed::onCreate()
{
	model = new Model(std::string("Assets/Models/Bed/bed.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 10.0f));

	OEntity::onCreate();
}

void Bed::onUpdate(float deltaTime)
{

}

void Bed::onDraw()
{
	OEntity::onDraw();
}
