#pragma once
#include <OGL3D/OPrerequisites.h>

class OVertexArrayObject
{
public:
	OVertexArrayObject(const OVertexBufferDesc& vbDesc); //constructor with the Vertex Buffer Description.
	OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc); //constructor with the vertex buffer description as well as the index buffer description.
	~OVertexArrayObject(); //destructor. deletes the elemtn and vertex buffers

	ui32 getId(); //returns m_vertexArrayObjectId

	ui32 getVertexBufferSize(); //returns how many elements are in the vertext buffer data
	ui32 getVertexSize(); //returns the size of one vertex in the vertext buffer data

private:
	ui32 m_vertexBufferId = 0; //buffer id for the vertex buffer. used when binding and populating data in the buffers
	ui32 m_elementBufferId = 0; //buffer id for the element buffer. used when binding and populating data in the buffers
	ui32 m_vertexArrayObjectId = 0; //id for this vertex array object. used to bind and delete the vertices with OpenGL
	OVertexBufferDesc m_vertexBufferData; //local variable of the vertex buffer description.
};

