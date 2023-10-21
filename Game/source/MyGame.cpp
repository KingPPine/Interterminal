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
	m_player->setPosition(OVec3(-1, 0, 0));

	m_player2 = getEntitySystem()->createEntity<MyPlayer>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
	m_player2->setPosition(OVec3(1, 0, 0));
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
