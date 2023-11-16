#include <Entities/Cube2.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/Model.h>
#include <string>
#include <sstream>

Cube2::Cube2()
{

}

Cube2::~Cube2()
{
}

void Cube2::onCreate()
{
	model = new Model(std::string("Assets/Models/TestCube/testCube.obj"));

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/LightSourceShader.frag";

	//material shader attributes
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	OEntity::onCreate();
}

void Cube2::onUpdate(f32 deltaTime)
{
	timeValue += deltaTime;

	rotation.x = 0.0f;
	rotation.y = 1.0f * timeValue;
	rotation.z = 0.0f;

	updateLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].position")), position);
}

void Cube2::onDraw()
{
	OEntity::onDraw();
}

void Cube2::passLightShaderAtrributes()
{
	//do nothing here, since I don't need to inherit the light shader attributes
}
