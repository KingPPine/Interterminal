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

	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	//m_testEntity = getEntitySystem()->createEntity<TestEntity>();

	//the light cube, drawing 4 of them now
	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(GameConstants::lightPos);
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(GameConstants::lightPos2);
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(GameConstants::lightPos3);
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(GameConstants::lightPos4);
	m_cube2->setScale(glm::vec3(0.2f));
	
	srand(time(0));	
	for (int i = 0; i < 10; i++)
	{
	//	m_cube1 = getEntitySystem()->createEntity<Cube1>();
	//	float randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) - 5.0f;
	//	float randZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) - 5.0f;
	//	m_cube1->setPosition(glm::vec3(randX, 0.0f, randZ));

		float range = 15.0f;
		m_testEntity = getEntitySystem()->createEntity<TestEntity>();
		float randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range/2.0f);
		float randY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range / 2.0f);
		float randZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range / 2.0f);
		m_testEntity->setPosition(glm::vec3(randX, randY, randZ));
	}
	
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
