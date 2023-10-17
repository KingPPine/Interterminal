#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine(); //constructor. Points to the CWin32GraphicsEngine.cpp implementation
	~OGraphicsEngine(); //destructor

public:
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc); //creates a shared pointer for the vertex array object, based on the vertex buffer description
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc); //same as above, but this allows a list of indices
	OUniformBufferPtr createUniformBuffer(const OUniformBufferDesc& desc); //creates a shared pointer for the uniform buffer object, based on the uniform buffer description
	OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc); //creates a shared pointer for the shader program, based on the shader program description

public:
	void clear(const OVec4& color); //clears the screen with whatever colour is passed
	void setFaceCulling(const OCullType& type); //sets the culling type to whatever we pass (FrontFace, BackFace, or Both)
	void setWindingOrder(const OWindingOrder& order); //sets the order in which the triangles get drawn, which influences what is facing front / back
	void setViewport(const ORect& size); //sets the viewport for where things draw within the screen. 0,0 is the bottom left, and width/height is as expected (up and to the right)
	void setVertexArrayObject(const OVertexArrayObjectPtr& vao); //binds the vertex array in OpenGL with glBindVertexArray
	void setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot); //sets the uniform buffer and the slot in OpenGL with glBindBufferBase
	void setShaderProgram(const OShaderProgramPtr& program); //sets the shader program in OpenGL with glUseProgram()
	void drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset); //draws the list of triangles based on the type being passed, using glDrawArrays
	void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount); //draws the list of triangles based on the type being passed and their indices, using glDrawElements
};

