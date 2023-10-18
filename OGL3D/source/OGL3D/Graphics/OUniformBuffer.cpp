#include <OGL3D/Graphics/OUniformBuffer.h>
#include <glad/glad.h>

OUniformBuffer::OUniformBuffer(const OUniformBufferDesc& desc) //constructor
{
	glGenBuffers(1, &m_id); //returns n buffer object names (1 in this case) into m_id
	glBindBuffer(GL_UNIFORM_BUFFER, m_id); //binds the buffer of m_id into GL_UNIFORM_BUFFER
	
	//creates a new data store for a buffer object. 
	// the data attribute is null because no data is being copied into the data store. GL_STATIC_DRAW specifies the expected usage
	glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0); //I think this is a precaution to unbind the buffer from GL_UNIFORM_BUFFER, since the call to setData happens separately.
	m_size = desc.size; //keep the size of the buffer description for use in setData
}

OUniformBuffer::~OUniformBuffer() //destructor
{
	glDeleteBuffers(1, &m_id); //deletes 1 buffer at the index of m_id
}

void OUniformBuffer::setData(void* data) //updates the buffer subdata
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id); //binds the buffer of m_id back into GL_UNIFORM_BUFFER
	glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data); //updates a subset of a buffer object's data store
	glBindBuffer(GL_UNIFORM_BUFFER, 0); //I think this is a precaution to unbind the buffer from GL_UNIFORM_BUFFER, since this buffer gets called separately from other places.
}

ui32 OUniformBuffer::getId() //returns m_id
{
	return m_id;
}
