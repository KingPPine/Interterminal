#pragma once
#include <OGL3D/Entity/OEntity.h>
class Cube1 : public OEntity
{
public:
	Cube1(); //constructor. Does nothing at the moment
	~Cube1(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

private:
	float timeValue = 0;
};