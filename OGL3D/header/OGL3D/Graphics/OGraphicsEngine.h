#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <list>

struct Text
{
	std::string text;
	float x;
	float y;
	float scale;
	glm::vec3 color;

	Text(std::string text, float x, float y, float scale, glm::vec3 color) : text(text), x(x), y(y), scale(scale), color(color)
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

	Camera* getCamera();

	void EnableDepthTest();
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

	void initializeFreeType();
	void RenderText(Text* text);
	void PushText(Text* text);
	void RenderAllText();

private:
	Camera* camera;

	glm::mat4 transform;
	unsigned int text_VAO, text_VBO;
	OShaderProgramPtr text_shader; //The pointer to the Shader Program, which calls both basic shaders

	std::list<Text*> textList;
};

