#include <MyGame.h>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	OGame::onCreate(); //calls OGame's onCreate
	m_player = getEntitySystem()->createEntity<MyPlayer>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
