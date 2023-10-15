#version 410 core

layout (row_major) uniform UniformData
{
	mat4 world;
	mat4 projection;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texcoord;

layout(location = 0) out vec3 vertOutColor;

void main()
{
	//regular translation
	vec4 pos = vec4(position,1) * world;
	//projection
	pos = pos * projection;

	gl_Position = pos;

	vertOutColor = vec3(texcoord.x, texcoord.y, texcoord.z);
}