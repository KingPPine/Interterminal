#version 410 core
layout (location = 0) in vec2 vertex; // <vec2 pos>

out VS_OUT{
    vec2 TexCoords;
    flat int index;
}vs_out;

uniform mat4 transforms[200];
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transforms[gl_InstanceID] * vec4(vertex.xy, 1.0, 1.0); //gl_InstanceID points to which instance of this shader call we're on
    vs_out.index = gl_InstanceID; //passing the instanceID to the fragment shader
    vs_out.TexCoords = vertex.xy;
    vs_out.TexCoords.y = 1.0f - vs_out.TexCoords.y;
}