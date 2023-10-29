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
	//m_cube1 = getEntitySystem()->createEntity<Cube1>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
	//m_cube1->setPosition(OVec3(0, 0,0));

	//m_cube2 = getEntitySystem()->createEntity<Cube2>(); //generates a new entity from the entity system. getEntitySystem() comes from OGame
	//m_cube2->setPosition(OVec3(1, -1, 10));

	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	srand(time(0));

	for (int i = 0; i < 10; i++)
	{
		m_testEntity = getEntitySystem()->createEntity<TestEntity>();
		float randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) - 5.0f;
		float randZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) - 5.0f;
		m_testEntity->setPosition(glm::vec3(randX, 0.0f, randZ));
	}
	
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
