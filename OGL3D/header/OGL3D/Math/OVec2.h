#pragma once

class OVec2 //vector2 class
{
public:
	OVec2() //empty constructor. leaves all the values as 0
	{
	}
	OVec2(float x, float y) : x(x), y(y) //regular constructor, assigns each value
	{
	}

	OVec2 operator - (const OVec2& vec) //allows for matrix multiplication
	{
		OVec2 out;

		out.x = x - vec.x;
		out.y = y - vec.y;
		
		return out;
	}

	void operator -= (const OVec2& vec) //allows for matrix multiplication
	{
		OVec2 out;

		out.x = x - vec.x;
		out.y = y - vec.y;

		*this = out;
	}

public:
	float x = 0, y = 0;
};