#version 410 core

//representing the uniform data in this shader
layout (row_major) uniform UniformData
{
	mat4 world;
	mat4 projection;
};

//position and texcoord being sent into this shader
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texcoord;

//the vertex colour being passed into this shader
layout(location = 0) out vec3 vertOutColor;

void main()
{
	//regular translation
	vec4 pos = vec4(position,1) * world;
	//projection
	pos = pos * projection;

	//setting the vertex position based on the above calculations
	gl_Position = pos;

	//passing the colour to the fragment shader without any modification
	vertOutColor = texcoord; // if needed, can be separated as  vec3(texcoord.x, texcoord.y, texcoord.z)
}