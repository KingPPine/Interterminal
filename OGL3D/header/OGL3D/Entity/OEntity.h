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
	virtual void setScale(glm::vec3 newScale);
	void rotate(float angle, glm::vec3 axis);
	void lookAt(glm::vec3* eye, glm::vec3* center, glm::vec3* top);
	void resetRotation();
	virtual void passLightShaderAtrributes(); //called by the entity manager to pass light shader attributes to the entity

protected:
	virtual void onCreate(); //create the entity
	virtual void onUpdate(float deltaTime); //update the entity
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
	//OWindow* display(); //helps shorten calls to the display

protected:
	//shader stuff
	const wchar_t* vertexShaderPath = nullptr;
	const wchar_t* fragmentShaderPath = nullptr;
	std::list<OShaderAttribute*> shaderAttribList;

	Model* model = nullptr;
	size_t m_id = 0; //entity id. used by the entity system
	OEntitySystem* m_entitySystem = nullptr; //pointer to the entity system.
	OEntity* m_entity = nullptr; //pointer to the entity in the entity manager
	Camera* camera = nullptr; //set in the constructor to point to the global camera. This is tied to every entity to be able to properly draw perspective

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); //the position of the entity
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f); //the scale of the entity

	OShaderProgramPtr m_shader; //The pointer to the Shader Program, which calls both basic shaders

	//allows protected / private values to be accessed by OEntitySystem
	friend class OEntitySystem;
};

