#pragma once
#include <any>

class OShaderAttribute
{
public:
	OShaderAttribute(const char* _attribName, std::any _data)
	{
		attribName = _attribName;
		data = _data;
	}
	~OShaderAttribute()
	{

	}

public:
	const char* attribName;
	std::any data;
};