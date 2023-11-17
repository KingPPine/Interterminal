#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

//these are called a "forward declaration"
//As a hangover from C, the C++ compiler works in a top-to-bottom fashion (more or less). 
//If you want your class C to refer to class A or class B in some way (via a pointer or a reference), 
//then the compiler must know about their existence beforehand.
class OVertexArrayObject;
class OUniformBuffer;
class OShaderProgram;

typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr; //type definition for a shared pointer to the Shader Program. Used in OGame.h

typedef unsigned int ui32; //type definition an unsigned int, written as ui32. This is nice shorthand.

struct OIndexBufferDesc //Description for the Index Buffer
{
	void* indicesList = nullptr; //pointer to the indices
	ui32 listSize = 0; //amount of indices
};

struct OShaderProgramDesc //Description for the Shader Program
{
	const wchar_t* vertexShaderFilePath; //path to the vertex shader
	const wchar_t* fragmentShaderFilePath; //path to the fragment shader
};

enum class OTriangleType //enum of triangle type for OpenGL
{
	TriangleList = 0, //list of triangles, separated into groups of 3 points
	TriangleStrip //strip of triangles, where the last point connects with the previous 2
};

enum class OCullType //enum of culling type for OpenGL
{
	BackFace = 0, //culls back faces. This is the choice we're going with
	FrontFace, //culls the front faces. Why would you ever wants this
	Both //culls both (dawg that just makes it invisible what's the point) 
};

enum class OWindingOrder //enum of the winding order for OpenGL. Helps determine the front face of a triangle
{
	ClockWise = 0, //clockwise
	CounterClockWise //counter-clockwise
};

enum class OShaderType //enum of the shader type for OpenGL
{
	VertexShader = 0, //vertex shader. modifies the position of vertices
	FragmentShader //fragment shader. sets the pixel colours
};

//Logging Error message format
#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

//Logging Warning message format
#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

//Logging Info message format
#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;
