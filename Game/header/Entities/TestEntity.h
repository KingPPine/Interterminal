#pragma once
#include <OGL3D/Entity/OEntity.h>
class TestEntity : public OEntity
{
public:
	TestEntity(); //constructor. Does nothing at the moment
	~TestEntity(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

private:

private:
	f32 m_elapsedSeconds = 0.0f; //elapsed seconds since creation
	unsigned int VAO = 0;
	unsigned int texture1 = 0;
	unsigned int texture2 = 0;
	float timeValue = 0;

protected:

};