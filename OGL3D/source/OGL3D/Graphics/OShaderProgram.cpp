#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc) //constructor
{
	m_programId = glCreateProgram(); //creates an empty program object and returns a non-zero value by which it can be referenced.
	attach(desc.vertexShaderFilePath, OShaderType::VertexShader); //attaches the vertex shader to the shader program
	attach(desc.fragmentShaderFilePath, OShaderType::FragmentShader); //attaches the fragment shader to the shader program
	link(); //links the shader program to OpenGL
}

OShaderProgram::~OShaderProgram() //destructor
{
	for (ui32 i = 0; i < 2; i++) //for each shader, detach and delete it from the program
	{
		glDetachShader(m_programId, m_attachedShaders[i]); //detaches shader from the program
		glDeleteShader(m_attachedShaders[i]); //frees the memory and invalidates the name associated with the shader object. Effectively undoes glCreateShader()
	}
	glDeleteProgram(m_programId); //frees the memory and invalidates the name associated with the program object. Effectively undoes glCreateProgram()
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type) //attaches the shader to the program
{
	std::string shaderCode; //string that will represent the shader file's code 
	std::ifstream shaderStream(shaderFilePath); //ifstream = Input File Stream. Meant to operate on files.
	if (shaderStream.is_open()) //checks if the file is open
	{
		std::stringstream sstr; //stringstream = stream class to operate on strings
		sstr << shaderStream.rdbuf(); //inserts the pointer to the shaderstream into the stringstream
		shaderCode = sstr.str(); //.str() accesses the string of characters, which we pass into shader code
		shaderStream.close(); //close the stream now that we've put the contents into "ShaderCode"
	}
	else //if the file wasn't opened
	{
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " not found"); //log a warning that the file wasn't found
		return; //stop the function
	}

	ui32 shaderId = 0; //int shader ID, will represent the shader type
	if (type == OShaderType::VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader through OpenGL, and assign the ID back to shaderId
	else if (type == OShaderType::FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER); //create a fragment shader through OpenGL, and assign the ID back to shaderId

	auto sourcePointer = shaderCode.c_str(); //c_str() returns a pointer to the string
	glShaderSource(shaderId, 1, &sourcePointer, NULL); //glShaderSource() replaces the source code in a shader object.
	glCompileShader(shaderId); //compiles the source code placed at the shaderID location

	//get compile errors
	int logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength); //queries the shader for a certain parameter, and puts it into the third argument. GL_INFO_LOG_LENGTH is the number of characters in the information log.
	if (logLength > 0) //if there are characters in the info log (GL_INFO_LOG_LENGTH), then an issue happened
	{
		std::vector<char> errorMessage(logLength + 1); //creating a vector of characters (basically a string) of the info log size + 1 
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]); //puts the info log into the errorMessage string
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " compiled with errors: " << std::endl << &errorMessage[0]); //display a warning with the error message
		return; //stop the function
	}

	glAttachShader(m_programId, shaderId); //attaches the shader object to the program
	m_attachedShaders[(ui32)type] = shaderId; //store the shader in the index representing the type enum (VertexShader = 0, FragmentShader = 1)

	OGL3D_INFO("OShaderProgram | " << shaderFilePath << " compiled successfully"); //confirm when shaders are compiled successfully
}

void OShaderProgram::link() //link the program to OpenGL
{
	glLinkProgram(m_programId); //links the shader program

	//get compile errors
	int logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength); //queries the program for a certain parameter, and puts it into the third argument. GL_INFO_LOG_LENGTH is the number of characters in the information log. 
	if (logLength > 0) //if there are characters in the info log (GL_INFO_LOG_LENGTH), then an issue happened
	{
		std::vector<char> errorMessage(logLength + 1); //creating a vector of characters (basically a string) of the info log size + 1 
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]); //puts the info log into the errorMessage string
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]); //display a warning with the error message
		return;
	}
}

ui32 OShaderProgram::getId() //returns m_programId
{
	return m_programId;
}

void OShaderProgram::setUniformBufferSlot(const char* name, ui32 slot) //binds our program to a uniform block
{
	ui32 index = glGetUniformBlockIndex(m_programId, name); //retrieves the index of a named uniform block. The program contains the block, and the name specifies the array of characters to retrieve
	glUniformBlockBinding(m_programId, index, slot); //honestly I don't understand this piece. https://docs.gl/gl4/glUniformBlockBinding
}

void OShaderProgram::use()
{
	glUseProgram(m_programId);
}
