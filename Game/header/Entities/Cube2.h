#pragma once
#include <OGL3D/Entity/OEntity.h>
class Cube2 : public OEntity
{
public:
	Cube2(); //constructor. Does nothing at the moment
	~Cube2(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(float deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

	virtual void passLightShaderAtrributes(); //called by the entity manager to pass light shader attributes to the entity

private:
	float timeValue = 0;
	short lightIndex = 0;
};