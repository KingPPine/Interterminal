#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <GameConstants.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Camera.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

struct Character { //character struct for text rendering
	int CharacterIndex;		// index of which character in the text is being drawn
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters; //map of characters

OShaderProgramPtr OGraphicsEngine::createShaderProgram(const OShaderProgramDesc& desc)
{
	return std::make_shared<OShaderProgram>(desc); //creates a shared pointer for the shader program, based on the shader program description
}

void OGraphicsEngine::clear(const OVec4& color) //clears the screen with whatever colour is passed
{
	glClearColor(color.x, color.y, color.z, color.w); //specify clear values for the color buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffers. GL_COLOR_BUFFER_BIT = Indicates the buffers currently enabled for color writing. GL_DEPTH_BUFFER_BIT = depth buffers
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
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum type = GL_RGBA;
		if (nrComponents == 1)
			type = GL_RED;
		else if (nrComponents == 3)
			type = GL_RGB;
		else if (nrComponents == 4)
			type = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, *p_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //the original filter is GL_LINEAR_MIPMAP_LINEAR, but I wanted the ps1 look
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //the original filter is GL_LINEAR, but I wanted the ps1 look
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

void OGraphicsEngine::reset2DTexture()
{
	glActiveTexture(GL_TEXTURE0);
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

void OGraphicsEngine::createElementArrayBuffer(GLuint* p_buffer, GLsizeiptr size, const void* data)
{
	glGenBuffers(1, p_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *p_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void OGraphicsEngine::setVertexAttributeArray(GLuint index, GLint size, GLsizei stride, const void* offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
}

void OGraphicsEngine::setVertexAttributeArrayInt(GLuint index, GLint size, GLsizei stride, const void* offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, GL_INT, stride, (void*)offset);
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

void OGraphicsEngine::setUniformMat4(int shaderID, const char* attributeName, glm::mat4* value)
{
	int location = glGetUniformLocation(shaderID, attributeName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*value));
}

void OGraphicsEngine::setUniformVec3(int shaderID, const char* attributeName, glm::vec3* value)
{
	int location = glGetUniformLocation(shaderID, attributeName);
	glUniform3f(location, value->x, value->y, value->z);
}

void OGraphicsEngine::setUniformFloat(int shaderID, const char* attributeName, float value)
{
	int location = glGetUniformLocation(shaderID, attributeName);
	glUniform1f(location, value);
}

void OGraphicsEngine::setUniformInt(int shaderID, const char* attributeName, int value)
{
	int location = glGetUniformLocation(shaderID, attributeName);
	glUniform1i(location, value);
}

void OGraphicsEngine::initializeFreeType()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//create the shader program
	text_shader = createShaderProgram(
		{
			L"Assets/Shaders/TextShader.vert", //basic vertex shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
			L"Assets/Shaders/TextShader.frag" //basic fragmentation shader. the 'L' is a wchar_t literal - this requires 16 bits of storage as opposed to 8
		});
	text_shader->setUniformBufferSlot("UniformData", 0); //idk I'm lost and afraid
	text_shader->use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(GameConstants::screenWidth), 0.0f, static_cast<float>(GameConstants::screenHeight));
	glUniformMatrix4fv(glGetUniformLocation(text_shader->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	// find path to font
	std::string font_name = "Assets/Fonts/arial.ttf";
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 256, 256);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &text2DTextureArray);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, text2DTextureArray);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_R8, 256, 256, 128, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			glTexSubImage3D(
				GL_TEXTURE_2D_ARRAY,
				0, 0, 0, int(c),
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows, 1,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// set texture options
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				int(c),
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	for (int i = 0; i < GameConstants::TEXT_ARRAY_LIMIT; i++)
	{
		letterMap.push_back(0);
		text2DTransforms.push_back(glm::mat4(1.0f));
	}

	GLfloat vertex_data[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &text_VAO);
	glGenBuffers(1, &text_VBO);
	glBindVertexArray(text_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //if the stride is set to 0, it assumes it fills our whole length
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OGraphicsEngine::RenderText(Text2D* text)
{
	// activate corresponding render state
	text->scale = text->scale * 48.0f / 256.0f;
	float copyX = text->position.x; //copies the starting x position for when we need to star a new line
	text_shader->use();
	glUniform3f(glGetUniformLocation(text_shader->getId(), "textColor"), text->color.x, text->color.y, text->color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, text2DTextureArray);
	glBindVertexArray(text_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, text_VBO);

	int workingIndex = 0;
	// iterate through all characters
	std::string::const_iterator c;
	for (c = text->text.begin(); c != text->text.end(); c++)
	{
		if (workingIndex == GameConstants::TEXT_ARRAY_LIMIT - 1)
		{
			break;
		}

		Character ch = Characters[*c];

		if (*c == '\n') //if the character is a new line, shift the y position down and reset the x position.
		{
			text->position.y -= (ch.Size.y) * 1.3 * text->scale;
			text->position.x = copyX;
		}
		else if (*c == ' ') //if the character is a space, don't render. Just move the cursor forward.
		{
			text->position.x += (ch.Advance >> 6) * text->scale;
		}
		else
		{
			float xpos = text->position.x + ch.Bearing.x * text->scale;
			float ypos = text->position.y - (ch.Size.y - ch.Bearing.y) * text->scale;

			text2DTransforms[workingIndex] = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0)) //move the text
				* glm::scale(glm::mat4(1.0f), glm::vec3(256 * text->scale, 256 * text->scale, 0));  //scale the text
				//* glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1)); //rotate the text
			letterMap[workingIndex] = ch.CharacterIndex;
			
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			text->position.x += (ch.Advance >> 6) * text->scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
			workingIndex++;
		}
	}

	glUniformMatrix4fv(glGetUniformLocation(text_shader->getId(), "transforms"), workingIndex, GL_FALSE, &text2DTransforms[0][0][0]);
	glUniform1iv(glGetUniformLocation(text_shader->getId(), "letterMap"), workingIndex, &letterMap[0]);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, workingIndex);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void OGraphicsEngine::PushText(Text2D* text)
{
	textList.push_back(text);
}

void OGraphicsEngine::RenderAllText()
{
	for (Text2D* text : textList)
	{
		RenderText(text);
		delete(text);//free the memory of the text
	}
	textList.clear();
}
