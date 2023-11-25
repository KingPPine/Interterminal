#pragma once
#include <OGL3D/Entity/OEntity.h>

class Floor : public OEntity
{
public:
	Floor(); //constructor. Does nothing at the moment
	~Floor(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(float deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

private:
	float timeValue = 0;
};