#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec3.h>

class OEntitySystem; //forward declaration of the entity system
class OGraphicsEngine;
class OWindow;
class OEntity
{
public:
	OEntity(); //constructor
	virtual ~OEntity(); //destructor

	void release(OEntity* p_entity); //release (delete) this entity

	OEntitySystem* getEntitySystem(); //returns the entity system
	
	void setPosition(OVec3 newPosition);
	void setRotation(OVec3 newRotation);
	void setScale(OVec3 newScale);

protected:
	virtual void onCreate() {} //create the entity
	virtual void onUpdate(f32 deltaTime); //update the entity
	virtual void onDraw(); //draw the entity (OpenGL calls)

	OGraphicsEngine* graphicsEngine(); //helps shorten calls to the graphics engine
	OWindow* display(); //helps shorten calls to the display

protected:
	size_t m_id = 0; //entity id. used by the entity system
	OEntitySystem* m_entitySystem = nullptr; //pointer to the entity system.
	OEntity* m_entity = nullptr; //pointer to the entity in the entity manager

	OVec3 position; //the position of the entity
	OVec3 rotation;
	OVec3 scale = OVec3(1.0f,1.0f,1.0f); //the scale of the entity

	OVertexArrayObjectPtr m_polygonVAO; //The Pointer to the vertex array object. This stuff should probably be in an entity class
	OUniformBufferPtr m_uniform; //The Pointer to the uniform buffer.
	OShaderProgramPtr m_shader; //The pointer to the Shader Program, which calls both basic shaders

	//allows protected / private values to be accessed by OEntitySystem
	friend class OEntitySystem;
};

