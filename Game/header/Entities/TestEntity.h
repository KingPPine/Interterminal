#pragma once
#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Graphics/Model.h>

class TestEntity : public OEntity
{
public:
	TestEntity(); //constructor. Does nothing at the moment
	~TestEntity(); //destructor. Does nothing at the moment

	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

private:
	float timeValue = 0;
	Model model = Model(std::string("Assets/Models/TestCube/testCube.obj"));
	//Model model = Model(std::string("Assets/Models/TestModel/dougie.obj"));
	//Model model = Model(std::string("Assets/Models/Backpack/backpack.obj"));
};