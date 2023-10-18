#pragma once
#include <OGL3D/OPrerequisites.h>

class OUniformBuffer
{
public:
	OUniformBuffer(const OUniformBufferDesc& desc); //constructor. initializes a buffer object based on the description
	~OUniformBuffer(); //destructor. deletes the buffer

	void setData(void* data); //updates the buffer subdata. basically we're storing vertex data for later

	ui32 getId(); //returns m_id

private:
	ui32 m_id = 0; //the id of this buffer object
	ui32 m_size = 0; //the size of this buffer object
};

