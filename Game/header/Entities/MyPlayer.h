#pragma once
#include <OGL3D/All.h>

class MyPlayer : public OEntity
{
public:
	MyPlayer(); //constructor. Does nothing at the moment
	~MyPlayer(); //destructor. Does nothing at the moment
	
	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity

private:
	f32 m_elapsedSeconds = 0.0f; //elapsed seconds since creation

protected:
};

