#pragma once
#include <OGL3D/OPrerequisites.h>

class OShaderProgram 
{
public:
	OShaderProgram(const OShaderProgramDesc& desc); //constructor. Takes in a shader program description, and attaches / links the shaders to OpenGL
	~OShaderProgram(); //descructor. detaches and deletes each shader, then deletes the program - all in OpenGL
	ui32 getId(); //returns m_programId
	void setUniformBufferSlot(const char* name, ui32 slot); //binds our program to a uniform block
	void use();

private:
	void attach(const wchar_t* shaderFilePath, const OShaderType& type); //takes a shader file path and shader type, and attaches the shader to OpenGL
	void link(); //links previously attached shaders to OpenGL

private:
	ui32 m_programId = 0; //the program ID, used in setUniformBufferSlot
	ui32 m_attachedShaders[2] = {}; //store the shader id for each shader being attached
};