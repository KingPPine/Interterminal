#pragma once
#include <OGL3D/All.h> //a collection of other header files
#include <Entities/MyPlayer.h> //player header since it creates a player
#include <Entities/Cube1.h>
#include <Entities/Cube2.h>
#include <Entities/TestEntity.h>

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
	Cube1* m_cube1 = nullptr; //pointer to player entity
	Cube2* m_cube2 = nullptr; //pointer to player entity
	TestEntity* m_testEntity = nullptr; //pointer to player entity
	TestEntity* m_testEntity2 = nullptr; //pointer to player entity
};