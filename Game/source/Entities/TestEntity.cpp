#include <Entities/TestEntity.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>


TestEntity::TestEntity()
{
	
}

TestEntity::~TestEntity()
{
}

void TestEntity::onCreate()
{
	vertexRowSize = 3;
	texCoordRowSize = 0;
	normalsRowSize = 3;
	//float vertices[] = {
	//	// positions			// texture coords	//normal vectors
	//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,
	//	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,			0.0f,  0.0f, -1.0f,
	//	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	//	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  0.0f, -1.0f,
	//	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,

	//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  0.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,			0.0f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,

	//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,

	//	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	//	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,
	//	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			1.0f,  0.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,

	//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,
	//	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,			0.0f, -1.0f,  0.0f,
	//	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	//	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,

	//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,
	//	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f
	//};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	graphicsEngine()->createArrayBuffer(&VBO, sizeof(vertices), vertices);

	vertexShaderPath = L"Assets/Shaders/TestShader.vert";
	fragmentShaderPath = L"Assets/Shaders/TestShader.frag";
	//vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	//fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";
	texturePath1 = "Assets/Textures/container.jpg";
	texturePath2 = "Assets/Textures/awesomeface.png";

	shaderAttribList.push_back(new OShaderAttribute("objectColor", glm::vec3(1.0f, 0.5f, 0.31f)));
	shaderAttribList.push_back(new OShaderAttribute("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("lightPos", GameConstants::lightPos));
	
	OEntity::onCreate();
}

void TestEntity::onUpdate(f32 deltaTime)
{
	timeValue += deltaTime;

	rotation.x = 0.0f;
	rotation.y = 1.0f * timeValue;
	rotation.z = 0.0f;
}

void TestEntity::onDraw()
{
	OEntity::onDraw();
}
