#pragma once
#include <OGL3D/OPrerequisites.h>
#include <GameConstants.h>
#include <glm.hpp>
#include <string>
#include <any>

class OEntitySystem; //forward declaration of the entity system
class OGraphicsEngine;
class OWindow;
class OShaderAttribute;
class Model;
class OEntity
{
public:
	OEntity(); //constructor
	virtual ~OEntity(); //destructor

	void release(OEntity* p_entity); //release (delete) this entity

	OEntitySystem* getEntitySystem(); //returns the entity system
	
	virtual void setPosition(glm::vec3 newPosition);
	virtual void setRotation(glm::vec3 newRotation);
	virtual void setScale(glm::vec3 newScale);
	virtual void passLightShaderAtrributes(); //called by the entity manager to pass light shader attributes to the entity

protected:
	virtual void onCreate(); //create the entity
	virtual void onUpdate(f32 deltaTime); //update the entity
	virtual void onDraw(); //draw the entity (OpenGL calls)

	void addShaderAttribute(std::string attribName, std::any data);
	short addDirectionalLight();
	short addPointLight();
	short addSpotLight();
	void addLightShaderAttribute(std::string attribName, std::any data);
	void updateLightShaderAttribute(std::string attribName, std::any data);
	void processShaderAttributes();
	void updateShaderAttribute(std::string attribName, std::any data);

	OGraphicsEngine* graphicsEngine(); //helps shorten calls to the graphics engine
	OWindow* display(); //helps shorten calls to the display

protected:
	//shader stuff
	int vertexRowSize = 0;
	int normalsRowSize = 0;
	int texCoordRowSize = 0;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int baseTexture = 0;
	unsigned int overlayTexture = 0;
	unsigned int specularMap = 0;
	const wchar_t* vertexShaderPath = nullptr;
	const wchar_t* fragmentShaderPath = nullptr;
	const char* baseTexturePath = nullptr;
	const char* overlayTexturePath = nullptr;
	const char* specularMapPath = nullptr;
	std::list<OShaderAttribute*> shaderAttribList;

	Model* model = nullptr;
	size_t m_id = 0; //entity id. used by the entity system
	OEntitySystem* m_entitySystem = nullptr; //pointer to the entity system.
	OEntity* m_entity = nullptr; //pointer to the entity in the entity manager
	Camera* camera = nullptr; //set in the constructor to point to the global camera. This is tied to every entity to be able to properly draw perspective

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); //the position of the entity
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f); //the rotation of the entity
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f); //the scale of the entity

	OVertexArrayObjectPtr m_polygonVAO; //The Pointer to the vertex array object. This stuff should probably be in an entity class
	OUniformBufferPtr m_uniform; //The Pointer to the uniform buffer.
	OShaderProgramPtr m_shader; //The pointer to the Shader Program, which calls both basic shaders

	//allows protected / private values to be accessed by OEntitySystem
	friend class OEntitySystem;
};

