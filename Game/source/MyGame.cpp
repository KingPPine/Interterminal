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

	//the light cube, drawing 4 of them now
	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(glm::vec3(0.0f, 0.2f, 2.0f));
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(glm::vec3(2.3f, -3.3f, -4.0f));
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(glm::vec3(-4.0f, 2.0f, -12.0f));
	m_cube2->setScale(glm::vec3(0.2f));

	m_cube2 = getEntitySystem()->createEntity<Cube2>();
	m_cube2->setPosition(glm::vec3(0.0f, 0.0f, -3.0f));
	m_cube2->setScale(glm::vec3(0.2f));

	//m_testEntity = getEntitySystem()->createEntity<TestEntity>();
	//m_testEntity->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	//m_testEntity->setPosition(glm::vec3(- 1.0f, 0.0f, 0.0f));

	srand(time(0));	
	for (int i = 0; i < 10; i++)
	{
		m_testEntity = getEntitySystem()->createEntity<TestEntity>();
		float range = 15.0f;
		
		float randX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range/2.0f);
		float randY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range / 2.0f);
		float randZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range)) - (range / 2.0f);
		m_testEntity->setPosition(glm::vec3(randX, randY, randZ));
	}
	
}

void MyGame::onUpdate(f32 deltaTime)
{
	
}
