#include <Entities/Chain.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::onCreate()
{
	model = new Model(std::string("Assets/Models/Chain/chain.obj"), graphicsEngine());

	vertexShaderPath = L"Assets/Shaders/TestShader2.vert";
	fragmentShaderPath = L"Assets/Shaders/TestShader2.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 10.0f));

	OEntity::onCreate();
}

void Chain::onUpdate(float deltaTime)
{

}

void Chain::onDraw()
{
	OEntity::onDraw();
}
