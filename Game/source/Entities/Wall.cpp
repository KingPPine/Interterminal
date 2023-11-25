#include <Entities/Wall.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::onCreate()
{
	model = new Model(std::string("Assets/Models/Walls/wall.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 10.0f));

	OEntity::onCreate();
}

void Wall::onUpdate(float deltaTime)
{

}

void Wall::onDraw()
{
	OEntity::onDraw();
}
