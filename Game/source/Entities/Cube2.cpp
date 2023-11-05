#include <Entities/Cube2.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
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
	vertexRowSize = 3;
	texCoordRowSize = 2;
	float vertices[] = {
		// positions				// texture coords
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
	};

	graphicsEngine()->createArrayBuffer(&VBO, sizeof(vertices), vertices);

	vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	fragmentShaderPath = L"Assets/Shaders/LightSourceShader.frag";
	//texturePath1 = "Assets/Textures/container.jpg";
	//texturePath2 = "Assets/Textures/awesomeface.png";

	//light shader attributes
	lightIndex = addPointLight(); //adds a new light to the entity system, and retrieves the index that should be used for all the shader attributes
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].position")), position);
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].ambient")), glm::vec3(0.05f, 0.05f, 0.05f));
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].diffuse")), glm::vec3(0.8f, 0.8f, 0.8f));
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].specular")), glm::vec3(1.0f, 1.0f, 1.0f));
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].constant")), 1.0f);
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].linear")), 0.09f);
	addLightShaderAttribute((std::string("pointLights[") + std::to_string(lightIndex) + std::string("].quadratic")), 0.032f);

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
