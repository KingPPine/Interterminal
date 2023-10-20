#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Entity/OEntitySystem.h>

OEntity::OEntity() //constructor
{
}

OEntity::~OEntity() //destructor
{
}

void OEntity::release(OEntity* p_entity) //releases the entity from the entity system
{
	m_entitySystem->removeEntity(p_entity);
}

OEntitySystem* OEntity::getEntitySystem() //returns the entity system
{
	return m_entitySystem;
}
