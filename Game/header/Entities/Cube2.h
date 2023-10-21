#pragma once
#include <OGL3D/Entity/OEntity.h>
class Cube2 : public OEntity
{
public:
	Cube2(); //constructor. Does nothing at the moment
	~Cube2(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

private:

private:
	f32 m_elapsedSeconds = 0.0f; //elapsed seconds since creation

protected:

};