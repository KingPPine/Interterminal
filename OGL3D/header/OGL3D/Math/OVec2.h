#pragma once
#include <OGL3D/OPrerequisites.h>

class OVec2 //vector2 class
{
public:
	OVec2() //empty constructor. leaves all the values as 0
	{
	}
	OVec2(f32 x, f32 y) : x(x), y(y) //regular constructor, assigns each value
	{
	}


public:
	f32 x = 0, y = 0;
};