#version 410 core

//the colour data being passed from the vertex shader
layout(location = 0) in vec3 vertOutColor;

//the color being output from the shader
layout(location = 0) out vec4 outColor;

void main()
{
	//outputting the same colours being given by the vertex shader
	outColor.rgb = vertOutColor;
}