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
	m_cube1 = getEntitySystem()->createEntity<Cube1>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
	m_cube1->setPosition(OVec3(0, 0,0));
	//m_cube1->setScale(OVec3(0.5f, 0.5f, 0.5f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
	m_cube2->setPosition(OVec3(1, -1, 10));
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
