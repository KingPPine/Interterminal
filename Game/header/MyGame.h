#pragma once
#include <OGL3D/Game/OGame.h>
#include <Entities/TestEntity.h>

class MyPlayer;
class Terminal;
class MyGame : public OGame
{
public:
	MyGame(); //constructor. Does nothing at the moment.
	~MyGame(); //destructor. Does nothing at the moment.

	virtual void onCreate(); //calls OGame's onCreate and sets m_player to a new entity, created by the entity system
	virtual void onUpdate(float deltaTime); //does nothing at the moment.

private:
	float m_elapsedSeconds = 0.0f; //never referenced.
	MyPlayer* player = nullptr; //pointer to player entity
	Terminal* terminal = nullptr;
};