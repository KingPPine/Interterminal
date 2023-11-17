#pragma once
#include <OGL3D/OPrerequisites.h>

class OVec4 //vector4 class
{
public:
	OVec4() //empty constructor. leaves all the values as 0
	{
	}
	OVec4(float x, float y, float z, float w): x(x),y(y),z(z),w(w) //regular constructor, assigns each value
	{
	}


public:
	float x = 0, y = 0, z = 0, w = 0;
};