#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <list>
#include <vector>

struct Text2D
{
	std::string text;
	glm::vec3 position;
	float scale;
	glm::vec3 color;

	Text2D(std::string text, glm::vec3 position, float scale, glm::vec3 color) : text(text), position(position), scale(scale), color(color)
	{

	}
};

struct Text3D
{
	std::string text;
	glm::vec3 position;
	glm::mat4 rotationMatrix;
	float scale;
	glm::vec3 color;

	Text3D(std::string text, glm::vec3 position, glm::mat4 rotationMatrix, float scale, glm::vec3 color) : text(text), position(position), rotationMatrix(rotationMatrix), scale(scale), color(color)
	{

	}
};

class Camera;
class OGraphicsEngine
{
public:
	OGraphicsEngine(); //constructor. Points to the CWin32GraphicsEngine.cpp implementation
	~OGraphicsEngine(); //destructor

public:
	OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc); //creates a shared pointer for the shader program, based on the shader program description

public:
	void clear(const OVec4& color); //clears the screen with whatever colour is passed

	void setTextureVerticallyFlip(bool flip);
	void loadTexture(const char* filePath, GLuint* p_texture);
	void setTextureUniform(GLuint program, const GLchar* name, int index);
	void activate2DTexture(int uniformIndex, GLuint texture);
	void reset2DTexture();

	void EnableDepthTest();
	void DisableDepthTest();
	void setFaceCulling(const OCullType& type); //sets the culling type to whatever we pass (FrontFace, BackFace, or Both)
	void setWindingOrder(const OWindingOrder& order); //sets the order in which the triangles get drawn, which influences what is facing front / back
	void setViewport(const ORect& size); //sets the viewport for where things draw within the screen. 0,0 is the bottom left, and width/height is as expected (up and to the right)
	void createArrayBuffer(GLuint* p_buffer, GLsizeiptr size, const void* data); //generates and sets up an array buffer
	void createElementArrayBuffer(GLuint* p_buffer, GLsizeiptr size, const void* data);
	void setVertexAttributeArray(GLuint index, GLint size, GLsizei stride, const void* offset);
	void setVertexAttributeArrayInt(GLuint index, GLint size, GLsizei stride, const void* offset);
	void generateVertexArrayObject(GLuint* p_VAO); //creates the vertex array in OpenGL with glBindVertexArray
	void bindVertexArrayObject(GLuint p_VAO); //binds the vertex array in OpenGL with glBindVertexArray
	void setShaderProgram(const OShaderProgramPtr& program); //sets the shader program in OpenGL with glUseProgram()
	void drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset); //draws the list of triangles based on the type being passed, using glDrawArrays
	void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount); //draws the list of triangles based on the type being passed and their indices, using glDrawElements


	void setUniformMat4(int shaderID, const char* attributeName, glm::mat4* value);
	void setUniformVec3(int shaderID, const char* attributeName, glm::vec3* value);
	void setUniformFloat(int shaderID, const char* attributeName, float value);
	void setUniformInt(int shaderID, const char* attributeName, int value);

	void initializeFreeType2D();
	void RenderText2D(Text2D* text);
	void CallRenderText2D(int length);
	void PushText2D(Text2D* text);
	void RenderAllText2D();

	void initializeFreeType3D();
	void RenderText3D(Text3D* text);
	void CallRenderText3D(int length);
	void PushText3D(Text3D* text);
	void RenderAllText3D();

private:
	std::vector<glm::mat4> text2DTransforms;
	std::vector<int> text2DLetterMap;
	GLuint text2DTextureArray;
	unsigned int text2D_VAO, text2D_VBO;
	OShaderProgramPtr text2D_shader; //The pointer to the Shader Program, which calls both basic shaders
	std::list<Text2D*> tex2DList;

	std::vector<glm::mat4> text3DTransforms;
	std::vector<int> text3DLetterMap;
	GLuint text3DTextureArray;
	unsigned int text3D_VAO, text3D_VBO;
	OShaderProgramPtr text3D_shader; //The pointer to the Shader Program, which calls both basic shaders
	std::list<Text3D*> tex3DList;
};

