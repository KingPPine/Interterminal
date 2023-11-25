#pragma once
#include <OGL3D/Entity/OEntity.h>
class MyPlayer : public OEntity
{
public:
	MyPlayer(); //constructor. Does nothing at the moment
	~MyPlayer(); //destructor. Does nothing at the moment

	void setPosition(glm::vec3 newPosition);
	
	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(float deltaTime); //after 3 seconds, deletes the entity
	virtual void onDraw();

	virtual void passLightShaderAtrributes(); //called by the entity manager to pass light shader attributes to the entity

private:

private:
	float m_elapsedSeconds = 0.0f; //elapsed seconds since creation
	float mouseSensitivity;
	float movementSpeed;
	bool firstFrame = true; //used to skip the camera input on first frame

	int directionalLightIndex = 0;
	int spotLightIndex = 0;
};

