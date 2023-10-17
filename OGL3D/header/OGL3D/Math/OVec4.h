#pragma once
#include <OGL3D/OPrerequisites.h>

class OVec4 //vector4 class
{
public:
	OVec4() //empty constructor. leaves all the values as 0
	{
	}
	OVec4(f32 x, f32 y, f32 z, f32 w): x(x),y(y),z(z),w(w) //regular constructor, assigns each value
	{
	}


public:
	f32 x = 0, y = 0, z = 0, w = 0;
};