#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Entity/OEntitySystem.h>

class OEntitySystem; //forward declaration of the entity system
class OShaderProgram;
class OWindow;
class OUniformBuffer;
class OEntity
{
public:
	OEntity(); //constructor
	virtual ~OEntity(); //destructor

	void release(OEntity* p_entity); //release (delete) this entity

	OEntitySystem* getEntitySystem(); //returns the entity system

protected:
	virtual void onCreate() {} //create the entity
	virtual void onUpdate(f32 deltaTime) {} //update the entity

protected:
	size_t m_id = 0; //entity id. used by the entity system
	OEntitySystem* m_entitySystem = nullptr; //pointer to the entity system.
	OEntity* m_entity = nullptr; //pointer to the entity in the entity manager

	//allows protected / private values to be accessed by OEntitySystem
	friend class OEntitySystem;
};

