#pragma once
#include <OGL3D/OPrerequisites.h>

class OEntitySystem; //forward declaration of the entity system
class OEntity
{
public:
	OEntity(); //constructor
	virtual ~OEntity(); //destructor

	void release(); //release (delete) this entity

	OEntitySystem* getEntitySystem(); //returns the entity system

protected:
	virtual void onCreate() {} //create the entity
	virtual void onUpdate(f32 deltaTime) {} //update the entity

protected:
	size_t m_id = 0; //entity id. used by the entity system
	OEntitySystem* m_entitySystem = nullptr; //pointer to the entity system.

	//allows protected / private values to be accessed by OEntitySystem
	friend class OEntitySystem;
};

