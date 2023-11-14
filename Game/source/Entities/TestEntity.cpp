#include <Entities/TestEntity.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <OGL3D/Graphics/OShaderProgram.h>

TestEntity::TestEntity()
{
	
}

TestEntity::~TestEntity()
{
}

void TestEntity::onCreate()
{
	vertexShaderPath = L"Assets/Shaders/model_loading.vert";
	fragmentShaderPath = L"Assets/Shaders/model_loading.frag";

	//create the shader program
	m_shader = graphicsEngine()->createShaderProgram(
		{
			vertexShaderPath, //basic vertex shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
			fragmentShaderPath //basic fragmentation shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
		});
	m_shader->setUniformBufferSlot("UniformData", 0); //idk I'm lost and afraid
	graphicsEngine()->setShaderProgram(m_shader);

	//material shader attributes
	//shaderAttribList.push_back(new OShaderAttribute("material.diffuse", 0));
	//shaderAttribList.push_back(new OShaderAttribute("material.specular", 1));
	shaderAttribList.push_back(new OShaderAttribute("material.shininess", 31.0f));

	//OEntity::onCreate();
}

void TestEntity::onUpdate(f32 deltaTime)
{
	//timeValue += deltaTime;

	//rotation.x = 0.3f * timeValue;
	//rotation.y = 1.0f * timeValue;
	//rotation.z = 0.7f * timeValue;
}

void TestEntity::onDraw()
{
	m_shader->use();

	//process any shader attributes that were set up on the entity
	processShaderAttributes();

	//projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); //45.0f can be replaced with a camera zoom, 800f with the screen width, 600f with the screen height
	//camera view
	glm::mat4 view = glm::lookAt(camera->cameraPosition, camera->cameraPosition + camera->cameraFront, camera->cameraUp);
	
	int viewLoc = glGetUniformLocation(m_shader->getId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(m_shader->getId(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//render the loaded model
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, scale);
	//modelMat = glm::rotate(modelMat, glm::length(rotation) * glm::radians(50.0f), rotation);
	int modelLoc = glGetUniformLocation(m_shader->getId(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

	model.Draw(m_shader->getId());
}