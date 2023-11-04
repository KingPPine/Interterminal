#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Camera.h>


OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
	return std::make_shared<OVertexArrayObject>(vbDesc); //creates a shared pointer for the vertex array object, based on the vertex buffer description
}

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc)
{
	return std::make_shared<OVertexArrayObject>(vbDesc, ibDesc); //creates a shared pointer for the vertex array object, based on the vertex buffer description and a list of indices
}

OUniformBufferPtr OGraphicsEngine::createUniformBuffer(const OUniformBufferDesc& desc)
{
	return std::make_shared<OUniformBuffer>(desc); //creates a shared pointer for the uniform buffer object, based on the uniform buffer description
}

OShaderProgramPtr OGraphicsEngine::createShaderProgram(const OShaderProgramDesc& desc)
{
	return std::make_shared<OShaderProgram>(desc); //creates a shared pointer for the shader program, based on the shader program description
}

void OGraphicsEngine::clear(const OVec4& color) //clears the screen with whatever colour is passed
{
	glClearColor(color.x, color.y, color.z, color.w); //specify clear values for the color buffers
	glClear(GL_COLOR_BUFFER_BIT); //clear buffers. GL_COLOR_BUFFER_BIT = Indicates the buffers currently enabled for color writing.
}

void OGraphicsEngine::clearDepthBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGraphicsEngine::setTextureVerticallyFlip(bool flip)
{
	stbi_set_flip_vertically_on_load(flip); // tell stb_image.h to flip loaded texture's on the y-axis.
}

void OGraphicsEngine::loadTexture(const char* filePath, GLuint* p_texture)
{
	//create the texture
	glGenTextures(1, p_texture);

	//load in the data for the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum type;
		if (nrChannels == 1)
			type = GL_RED;
		else if (nrChannels == 3)
			type = GL_RGB;
		else if (nrChannels == 4)
			type = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, *p_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		OGL3D_ERROR("Failed to load texture");
	}
	stbi_image_free(data);
}

void OGraphicsEngine::setTextureUniform(GLuint program, const GLchar* name, int index)
{
	glUniform1i(glGetUniformLocation(program, name), index); //setting the uniform textures for the shaders
}

void OGraphicsEngine::activate2DTexture(int uniformIndex, GLuint texture)
{
	GLenum gl_texture_index = 33984 + uniformIndex; //This is a hacky way to get "GL_TEXTURE0" from '0', and so on

	glActiveTexture(gl_texture_index); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, texture);
}

Camera* OGraphicsEngine::getCamera()
{
	return camera;
}

void OGraphicsEngine::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void OGraphicsEngine::setFaceCulling(const OCullType& type) //sets the culling type to whatever we pass (FrontFace, BackFace, or Both)
{
	auto cullType = GL_BACK; //GL_BACK is an int. we're just using this as a default value for instantiation.

	if (type == OCullType::FrontFace) cullType = GL_FRONT; //culls the front faces
	if (type == OCullType::BackFace) cullType = GL_BACK; //culls the back faces (honestly the only one that makes sense)
	if (type == OCullType::Both) cullType = GL_FRONT_AND_BACK; //culls the back and front faces

	glEnable(GL_CULL_FACE); //enable or disable server-side GL capabilities. We're enabling culling with this
	glCullFace(cullType); //sets the culling type
}

void OGraphicsEngine::setWindingOrder(const OWindingOrder& order) //sets the order in which the triangles get drawn, which influences what is facing front / back
{
	auto orderType = GL_CW; //GL_CW is just an int. we're using this as a default value for instantiation.

	if (order == OWindingOrder::ClockWise) orderType = GL_CW; //clockwise winding order
	else if (order == OWindingOrder::CounterClockWise) orderType = GL_CCW; //counter-clockwise winding order

	glFrontFace(orderType); //define front and back-facing polygons
}

void OGraphicsEngine::setViewport(const ORect& size) //sets the viewport for where things draw within the screen. 0,0 is the bottom left, and width/height is as expected (up and to the right)
{
	glViewport(size.left, size.top, size.width, size.height); //dividing width and height by 2 will reduce the viewport to a quarter of the screen (everything within the viewport will shrink too)
}

void OGraphicsEngine::createArrayBuffer(GLuint* p_buffer, GLsizeiptr size, const void* data)
{
	glGenBuffers(1, p_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *p_buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void OGraphicsEngine::setVertexAttributeArray(GLuint index, GLint size, GLsizei stride, const void* offset)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

void OGraphicsEngine::generateVertexArrayObject(GLuint* p_VAO)
{
	glGenVertexArrays(1, p_VAO);
}

void OGraphicsEngine::bindVertexArrayObject(GLuint p_VAO) //binds the vertex array in OpenGL with glBindVertexArray
{
	glBindVertexArray(p_VAO); //bind a vertex array object.
	//array is the name of a vertex array object previously returned from a call to glGenVertexArrays, or zero to break the existing vertex array object binding.
}

void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot) //sets the uniform buffer and the slot in OpenGL with glBindBufferBase
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId()); //bind a buffer object to an indexed buffer target. GL_UNIFORM_BUFFER is the target
}

void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program) //sets the shader program in OpenGL with glUseProgram()
{
	glUseProgram(program->getId()); //Installs a program object as part of current rendering state. In this case, our shader program
	//One or more executables are created in a program object by successfully attaching shader objects to it with 
	// glAttachShader, successfully compiling the shader objects with glCompileShader, and successfully linking the program object with glLinkProgram.
}

void OGraphicsEngine::drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset) //draws the list of triangles based on the type being passed, using glDrawArrays
{
	auto glTriType = GL_TRIANGLES; //GL_TRIANGLES is just an int. we're using this as a default value for instatiation.

	switch (triangleType)
	{
	case OTriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; } //represents a list of triangles, 3 points at a time
	case OTriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; } //represents a triangle strip, meaning the next point will create a triangle with the previous 2
	}

	glDrawArrays(glTriType, offset, vertexCount); //render primitives from array data. "offset" specifies the starting index.
}

void OGraphicsEngine::drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount) //draws the list of triangles based on the type being passed and their indices, using glDrawElements
{
	auto glTriType = GL_TRIANGLES; //GL_TRIANGLES is just an int. we're using this as a default value for instatiation.

	switch (triangleType)
	{
	case OTriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; } //represents a list of triangles, 3 points at a time
	case OTriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; } //represents a triangle strip, meaning the next point will create a triangle with the previous 2
	}

	glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr); //render primitives from array data using a mode, count, type (of the values in indices), and a pointer to where the indices are stored
	//I'm not actually sure why a null pointer works here. I THINK because glBindVertexArray binds the vertex array earlier in the code (which contains the indices), it doesn't need a further pointer to it (??)
}
