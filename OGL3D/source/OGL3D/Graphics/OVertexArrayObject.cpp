#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc) //constructor
{
	if (!vbDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL"); //throw an error if no vertices are being passed
	if (!vbDesc.vertexSize) OGL3D_ERROR("OVertexArrayObject | vertexSize is NULL"); //throw an error if the vertex has a size of 0
	if (!vbDesc.verticesList) OGL3D_ERROR("OVertexArrayObject | verticesList is NULL"); //throw an error if the pointer to the vertices is the null pointer

	glGenVertexArrays(1, &m_vertexArrayObjectId); //generates 1 vertex array and stores the index in m_vertexArrayObjectId
	glBindVertexArray(m_vertexArrayObjectId); //binds the vertex array to OpenGL

	glGenBuffers(1, &m_vertexBufferId); //generates one buffer and stores the index in m_vertexBufferId
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId); //binds the buffer of m_vertexBufferId into GL_ARRAY_BUFFER

	//creates a new data store for a buffer object. 
	//Vertex attributes go into GL_ARRAY_BUFFER, the size is the vertex size multiplied by the amount of elements,
	//the data is the list of vertices, and the usage is GL_STATIC_DRAW
	glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW); 

	for (ui32 i = 0; i < vbDesc.attributesListSize; i++) //for each attribute
	{
		glVertexAttribPointer(
			i, //the index of the generic vertex attribute to be modified
			vbDesc.attributesList[i].numElements, //the size of the array
			GL_FLOAT, //type of each component in the array. In this case, a float
			GL_FALSE, //whether the fixed-point data values should be normalized
			vbDesc.vertexSize, //the stride, meaning the bite offset between consecutive vertex attributes
			(void*)((i==0)?0:vbDesc.attributesList[i-1].numElements*sizeof(f32)) //an offset of the first attribute. important to iterate through each set of elements/attributes
		);
		glEnableVertexAttribArray(i); //enable this vertex array attribute
	}

	glBindVertexArray(0); //safety precaution - unbinds this array to prevent crossed wires

	m_vertexBufferData = vbDesc; //store the description locally
}

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc):OVertexArrayObject(vbDesc) //here, this calls the base constructor
{
	if (!ibDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL"); //throw an error if there are no indices
	if (!ibDesc.indicesList) OGL3D_ERROR("OVertexArrayObject | indicesList is NULL"); //throw an error if the pointer to the indices is the null pointer

	glBindVertexArray(m_vertexArrayObjectId); //since we know glGenVertexArrays was called in the base constructor, we can bind the vertex array again

	glGenBuffers(1, &m_elementBufferId); //generates one buffer and stores the index in m_elementBufferId
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId); //binds the buffer of m_elementBufferId into GL_ELEMENT_ARRAY_BUFFER

	//creates a new data store for a buffer object. 
	//Indices go into GL_ELEMENT_ARRAY_BUFFER, the size is the the amount of elements,
	//the data is the list of indices, and the usage is GL_STATIC_DRAW
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

	glBindVertexArray(0); //safety precaution - unbinds this array to prevent crossed wires
}

OVertexArrayObject::~OVertexArrayObject() //destructor
{
	glDeleteBuffers(1, &m_elementBufferId); //deletes one buffer, updating the memory address for m_elementBufferId
	glDeleteBuffers(1, &m_vertexBufferId); //deletes one buffer, updating the memory address for m_vertexBufferId
	glDeleteVertexArrays(1, &m_vertexArrayObjectId); //deletes one vertex array, updating the memory address for m_vertexArrayObjectId
}

ui32 OVertexArrayObject::getId() //returns m_vertexArrayObjectId
{
	return m_vertexArrayObjectId;
}

ui32 OVertexArrayObject::getVertexBufferSize() //returns the amount of elements in the vertex buffer data
{
	return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize() //returns the size of one vertex in the vertex buffer data
{
	return m_vertexBufferData.vertexSize;
}
