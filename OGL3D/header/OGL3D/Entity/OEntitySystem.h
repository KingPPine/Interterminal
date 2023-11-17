#pragma once
#include <OGL3D/OPrerequisites.h>
#include <list>
#include <map>
#include <set>
#include <any>
#include <string>

class OEntity; //forward declaration for Entity
class OGame;
class OGraphicsEngine;
class OWindow;
class OShaderAttribute;
class OEntitySystem
{
public:
	OEntitySystem(); //constructor. Does nothing at this time
	OEntitySystem(OGame* game); //constructor. sets the game pointer
	~OEntitySystem(); //destructor. Does nothing at this time
	
public:
	//all code based on template parameters must be placed in header files.
	//templates are essentially the compiler writing code based on the rules I've set up.
	//the main use here is to have a function that derives any object type, and the function can then handle that type as needed
	template <typename T> 
	T* createEntity()
	{
		//static_assert does the assertion at compile time
		static_assert(std::is_base_of<OEntity, T>::value, "T must derive from OEntity class"); //checks that the object derives from OEntity
		auto id = typeid(T).hash_code(); //get the hash id of the object type we've called this from 
		auto e = new T(); //creates the entity of this type

		//if entity creation was successful, return it. Otherwise, return a null pointer
		if (createEntityInternal(e, id)) //try to create the entity of the type captured, adding it to our entity system
			return e;
		return nullptr;
	}

public:
	OGraphicsEngine* getGraphicsEngine();
	OWindow* getWindowDisplay();

	short addDirectionalLight();
	short addPointLight();
	short addSpotLight();
	short getDirectionalLightCount();
	short getPointLightCount();
	short getSpotLightCount();

	void addLightShaderAttribute(std::string attribName, std::any data);
	void updateLightShaderAttribute(std::string attribName, std::any data);
	void passLightShaderAtrributes(std::list<OShaderAttribute*>* p_entityAttribList);

private:
	bool createEntityInternal(OEntity* entity, size_t id); //place this entity inside our map of entities
	void removeEntity(OEntity* entity); //remove the entity from our map of entities

	void update(float deltaTime); //update method which deletes unwanted entities and calls the onUpdate of the remaining entities
	void draw();

private:
	std::map < size_t, std::map< OEntity*, std::unique_ptr<OEntity>>> m_entities; //map of entities. I barely understand how this works
	std::set<OEntity*> m_entitiesToDestroy; //set of entities to destroy in the next frame
	std::list<OShaderAttribute*> lightShaderAttribList;

	short directionalLightCount = 0;
	short pointLightCount = 0;
	short spotLightCount = 0;

	bool firstFrame = true;

private:
	OGame* m_game = nullptr;

	//allows protected / private values to be accessed by OEntity and OGame
	friend class OEntity;
	friend class OGame;
};

