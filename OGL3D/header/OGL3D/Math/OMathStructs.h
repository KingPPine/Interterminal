#pragma once
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OMat4.h>

struct Vertex //data struct for a vertex, includes a position and a color
{
	OVec3 position;
	OVec3 texcoord;
};

struct UniformData //data struct to pass to the uniform buffer
{
	OMat4 world; //the matrix of world coordinates (scale, rotation, translation)
	OMat4 projection; //the projection matrix
};
