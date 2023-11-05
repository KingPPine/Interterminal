#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMathStructs.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OShaderAttribute.h>
#include <glm.hpp>
#include <string>
#include <any>

OEntity::OEntity() //constructor
{
	camera = GameConstants::camera;
	shaderAttribList = {};
}

OEntity::~OEntity() //destructor
{
}

void OEntity::onCreate()
{
	//unsigned int EBO;
	graphicsEngine()->generateVertexArrayObject(&VAO);
	graphicsEngine()->bindVertexArrayObject(VAO);
	//graphicsEngine()->createArrayBuffer(&EBO, ...);

	//create the shader program
	m_shader = graphicsEngine()->createShaderProgram(
		{
			vertexShaderPath, //basic vertex shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
			fragmentShaderPath //basic fragmentation shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
		});
	m_shader->setUniformBufferSlot("UniformData", 0); //idk I'm lost and afraid

	short index = 0;
	// position attribute
	if (vertexRowSize > 0)
	{
		graphicsEngine()->setVertexAttributeArray(index, vertexRowSize, (vertexRowSize + texCoordRowSize + normalsRowSize) * sizeof(float), (void*)0);
		index++;
	}
	// normal attribute
	if (normalsRowSize > 0)
	{
		graphicsEngine()->setVertexAttributeArray(index, normalsRowSize, (vertexRowSize + texCoordRowSize + normalsRowSize) * sizeof(float), (void*)(vertexRowSize * sizeof(float)));
		index++;
	}
	// texcoord attribute
	if (texCoordRowSize > 0)
	{
		graphicsEngine()->setVertexAttributeArray(index, texCoordRowSize, (vertexRowSize + texCoordRowSize + normalsRowSize) * sizeof(float), (void*)((vertexRowSize + normalsRowSize)* sizeof(float)));
		index++;
	}
	
	if (baseTexturePath != nullptr)
		graphicsEngine()->loadTexture(baseTexturePath, &baseTexture);
	if (overlayTexturePath != nullptr)
		graphicsEngine()->loadTexture(overlayTexturePath, &overlayTexture);
	if (specularMapPath != nullptr)
		graphicsEngine()->loadTexture(specularMapPath, &specularMap);

	graphicsEngine()->setShaderProgram(m_shader);

	//if (baseTexturePath != nullptr)
	//	graphicsEngine()->setTextureUniform(m_shader->getId(), "texture1", 0); //setting the uniform textures for the shaders
	//if (overlayTexturePath != nullptr)
	//	graphicsEngine()->setTextureUniform(m_shader->getId(), "texture2", 1); //setting the uniform textures for the shaders
}

void OEntity::onUpdate(f32 deltaTime)
{

}

void OEntity::onDraw()
{
	m_shader->use();

	int index = 0;
	if (baseTexture != 0)
	{
		graphicsEngine()->activate2DTexture(index, baseTexture);
		index++;
	}
	if (overlayTexture != 0)
	{
		graphicsEngine()->activate2DTexture(index, overlayTexture);
		index++;
	}
	if (specularMap != 0)
	{
		graphicsEngine()->activate2DTexture(index, specularMap);
		index++;
	}

	//process any shader attributes that were set up on the entity
	processShaderAttributes();

	//MATRIX OPERATIONS
	//model operations
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::length(rotation) * glm::radians(50.0f), rotation);


	//camera view
	glm::mat4 view = glm::lookAt(camera->cameraPosition, camera->cameraPosition + camera->cameraFront, camera->cameraUp);

	//projection
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(m_shader->getId(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(m_shader->getId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projectionLoc = glGetUniformLocation(m_shader->getId(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void OEntity::addShaderAttribute(std::string attribName, std::any data)
{
	shaderAttribList.push_back(new OShaderAttribute(attribName, data));
}

short OEntity::addDirectionalLight()
{
	return m_entitySystem->addDirectionalLight();
}

short OEntity::addPointLight()
{
	return m_entitySystem->addPointLight();
}

short OEntity::addSpotLight()
{
	return m_entitySystem->addSpotLight();
}

void OEntity::addLightShaderAttribute(std::string attribName, std::any data)
{
	m_entitySystem->addLightShaderAttribute(attribName, data);
}

void OEntity::updateLightShaderAttribute(std::string attribName, std::any data)
{
	m_entitySystem->updateLightShaderAttribute(attribName, data);
}

void OEntity::passLightShaderAtrributes()
{
	m_entitySystem->passLightShaderAtrributes(&shaderAttribList);
}

void OEntity::processShaderAttributes()
{
	for (auto const& attrib : shaderAttribList) {
		if (attrib != nullptr && !attrib->attribName.empty())
		{
			std::string type = attrib->data.type().name();
			int location = glGetUniformLocation(m_shader->getId(), attrib->attribName.c_str());

			if (type == std::string("struct glm::vec<3,float,0>")) //if the shader attribute data we stored is a Vector3, pass it to the shader this way
			{
				glm::vec3 vector = std::any_cast<glm::vec3>(attrib->data);
				//pass the uniform data to the fragment shader
				glUniform3f(location, vector.x, vector.y, vector.z);
			}

			else if (type == std::string("float"))
			{
				float value = std::any_cast<float>(attrib->data);
				//pass the uniform data to the fragment shader
				glUniform1f(location, value);
			}

			else if (type == std::string("int"))
			{
				int value = std::any_cast<int>(attrib->data);
				//pass the uniform data to the fragment shader
				glUniform1i(location, value);
			}
		}
	}
}

void OEntity::updateShaderAttribute(std::string attribName, std::any data)
{
	for (OShaderAttribute* shaderAttribute : shaderAttribList)
	{
		if (shaderAttribute->attribName == attribName) //compares the strings of the char pointers
		{
			shaderAttribute->data = data;
			return; //break out of the function since there should only be one attribute of each name
		}
	}
}

void OEntity::release(OEntity* p_entity) //releases the entity from the entity system
{
	m_entitySystem->removeEntity(p_entity);
}

OEntitySystem* OEntity::getEntitySystem() //returns the entity system
{
	return m_entitySystem;
}

void OEntity::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void OEntity::setRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void OEntity::setScale(glm::vec3 newScale)
{
	scale = newScale;
}

OGraphicsEngine* OEntity::graphicsEngine()
{
	return m_entitySystem->getGraphicsEngine();
}

OWindow* OEntity::display()
{
	return m_entitySystem->getWindowDisplay();
}
