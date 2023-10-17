#include <Entities/MyPlayer.h>

MyPlayer::MyPlayer()
{
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
	m_entity = getEntitySystem()->createEntity<OEntity>(); //calls the entity system to create and assign an entity to the pointer
}

void MyPlayer::onUpdate(f32 deltaTime)
{
	m_elapsedSeconds += deltaTime;
	OGL3D_INFO("Player elapsed time: " << m_elapsedSeconds << std::endl);

	if (m_entity && m_elapsedSeconds >= 3.0f) //if 3 seconds have passed by, release the entity and set the entity to a null pointer
	{
		m_entity->release(); //in OEntity.cpp, calls the entity system's "removeEntity()" method
		m_entity = nullptr;
	}
}
