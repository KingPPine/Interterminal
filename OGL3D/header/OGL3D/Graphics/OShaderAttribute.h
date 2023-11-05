#pragma once
#include <any>
#include <string>

class OShaderAttribute
{
public:
	OShaderAttribute(std::string _attribName, std::any _data)
	{
		attribName = _attribName;
		data = _data;
	}
	~OShaderAttribute()
	{

	}

public:
	std::string attribName;
	std::any data;
};