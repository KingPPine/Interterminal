#pragma once
#include <OGL3D/OPrerequisites.h>

class ORect //rectangle class
{
public:
	ORect(){} //empty constructor. leaves all values as 0
	ORect(int width, int height) :width(width), height(height) {} //constructor with width and height, leaves position as 0
	ORect(int left, int top, int width, int height) :left(left), top(top), width(width), height(height) {} //constructor which assigns each value
	ORect(const ORect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height) {} //constructor which takes another rectangle and assigns the same values

public:
	int width = 0, height = 0, left = 0, top = 0;
};