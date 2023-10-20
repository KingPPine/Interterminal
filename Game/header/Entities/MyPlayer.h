#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/All.h>

class MyPlayer : public OEntity
{
public:
	MyPlayer(); //constructor. Does nothing at the moment
	~MyPlayer(); //destructor. Does nothing at the moment
	
	virtual void onCreate(); //currently calls the entity system to create an entity and assigns it to m_entity. This resides in the OEntitySystem header file.
	virtual void onUpdate(f32 deltaTime); //after 3 seconds, deletes the entity

private:
	f32 m_elapsedSeconds = 0.0f; //elapsed seconds since creation

protected:
	OVertexArrayObjectPtr m_polygonVAO; //The Pointer to the vertex array object. This stuff should probably be in an entity class
	OUniformBufferPtr m_uniform; //The Pointer to the uniform buffer.
	OShaderProgramPtr m_shader; //The pointer to the Shader Program, which calls both basic shaders

	f32 m_scale = 0; //a default value, not really used for scale anymore. used in onUpdateInternal() for messing with the matrix
};

