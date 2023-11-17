#pragma once
#include <OGL3D/OPrerequisites.h>

class OVec3 //vector3 class
{
public:
	OVec3() //empty constructor. leaves all the values as 0
	{
	}
	OVec3(float x, float y, float z) : x(x), y(y), z(z) //regular constructor, assigns each value
	{
	}


public:
	float x = 0, y = 0, z = 0;
};