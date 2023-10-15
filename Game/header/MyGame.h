#pragma once
#include <OGL3D/All.h> //a collection of other header files
#include <Entities/MyPlayer.h> //player header since it creates a player

class MyGame : public OGame
{
public:
	MyGame(); //constructor. Does nothing at the moment.
	~MyGame(); //destructor. Does nothing at the moment.

	virtual void onCreate(); //calls OGame's onCreate and sets m_player to a new entity, created by the entity system
	virtual void onUpdate(f32 deltaTime); //does nothing at the moment.

private:
	f32 m_elapsedSeconds = 0.0f; //never referenced.
	MyPlayer* m_player = nullptr; //pointer to player entity
};