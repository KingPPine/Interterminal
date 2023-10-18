#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Entity/OEntity.h>

OEntitySystem::OEntitySystem() //constructor
{
}

OEntitySystem::~OEntitySystem() //destructor
{
}

bool OEntitySystem::createEntityInternal(OEntity* entity, size_t id) //adds the entity to our map
{
	auto ptr = std::unique_ptr<OEntity>(entity); //generate a unique pointer for the entity
	m_entities[id].emplace(entity, std::move(ptr)); //std::move allows the transfor of resources. moves our pointer into the map, and ties it to the entity

	entity->m_id = id; //provides the entity its id, so that it can call back to this system
	entity->m_entitySystem = this; //sets a pointer to this system so that it can be easily referenced

	entity->onCreate(); //calls the onCreate of the entity.
	//TODO: review this. I don't like that the entity needs to "create itself" through the entity system before having its own OnCreate called.
	//TODO: (cont.) I feel like it's mor intuitive if the process starts in EntitySystem to create the entity object in the first place

	return true; //confirm this was successful
}

void OEntitySystem::removeEntity(OEntity* entity) //add to the set of entities to be destroyed so that it can happen at the beginning of the update() method
{
	m_entitiesToDestroy.emplace(entity);
}

void OEntitySystem::update(f32 deltaTime) //update method
{
	for (auto e : m_entitiesToDestroy) // for each entity to destroy
	{
		m_entities[e->m_id].erase(e); //erase it from the m_entities map
	}
	m_entitiesToDestroy.clear(); //clear out the set of entities to destroy

	for (auto&& [id, entities] : m_entities) //for the remaining valid entities
	{
		for (auto&& [ptr, entity] : entities) //this is some crazy syntax - I need to look into this
		{
			entity->onUpdate(deltaTime); //update the entity
		}
	}
}
