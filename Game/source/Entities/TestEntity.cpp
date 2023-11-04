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
	normalsRowSize = 3;
	texCoordRowSize = 2;

	float vertices[] = {
		// positions				// normals				// texture coords
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f, 1.0f,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f
	};

	graphicsEngine()->createArrayBuffer(&VBO, sizeof(vertices), vertices);

	vertexShaderPath = L"Assets/Shaders/TestShader.vert";
	fragmentShaderPath = L"Assets/Shaders/TestShader.frag";
	//vertexShaderPath = L"Assets/Shaders/BasicShader.vert";
	//fragmentShaderPath = L"Assets/Shaders/BasicShader.frag";
	baseTexturePath = "Assets/Textures/container2.png";
	specularMapPath = "Assets/Textures/container2_specular.png";

#pragma region setting up lights
	//global shader values
	shaderAttribList.push_back(new OShaderAttribute("viewPos", GameConstants::camera->cameraPosition));

	//material
	shaderAttribList.push_back(new OShaderAttribute("material.diffuse", 0));
	shaderAttribList.push_back(new OShaderAttribute("material.specular", 1));
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 32.0f));

	//directional light
	shaderAttribList.push_back(new OShaderAttribute("dirLight.direction", glm::vec3(- 0.2f, -1.0f, -0.3f)));
	shaderAttribList.push_back(new OShaderAttribute("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f)));
	shaderAttribList.push_back(new OShaderAttribute("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f)));
	shaderAttribList.push_back(new OShaderAttribute("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f)));

	//point light 1
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].position", GameConstants::lightPos));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].constant", 1.0f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].linear", 0.09f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[0].quadratic", 0.032f));

	//point light 2
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].position", GameConstants::lightPos2));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].constant", 1.0f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].linear", 0.09f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[1].quadratic", 0.032f));

	//point light 3
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].position", GameConstants::lightPos3));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].constant", 1.0f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].linear", 0.09f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[2].quadratic", 0.032f));

	//point light 4
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].position", GameConstants::lightPos4));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].constant", 1.0f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].linear", 0.09f));
	shaderAttribList.push_back(new OShaderAttribute("pointLights[3].quadratic", 0.032f));

	//spotlight
	shaderAttribList.push_back(new OShaderAttribute("spotLight.position", GameConstants::camera->cameraPosition));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.direction", GameConstants::camera->cameraFront));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f)));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f)));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.constant", 1.0f));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.linear", 0.09f));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.quadratic", 0.032f));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.cutOff", glm::cos(glm::radians(12.5f))));
	shaderAttribList.push_back(new OShaderAttribute("spotLight.outerCutOff", glm::cos(glm::radians(15.0f))));

#pragma endregion

	OEntity::onCreate();
}

void TestEntity::onUpdate(f32 deltaTime)
{
	timeValue += deltaTime;

	rotation.x = 0.3f * timeValue;
	rotation.y = 1.0f * timeValue;
	rotation.z = 0.7f * timeValue;

	updateShaderAttribute("spotLight.position", GameConstants::camera->cameraPosition);
	updateShaderAttribute("spotLight.direction", GameConstants::camera->cameraFront);
	updateShaderAttribute("viewPos", GameConstants::camera->cameraPosition);
}

void TestEntity::onDraw()
{
	OEntity::onDraw();
}
