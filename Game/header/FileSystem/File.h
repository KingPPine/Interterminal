#pragma once
#include <string>

class File
{
public:
	File();
	~File();

	void setName(std::string name);
	std::string getName();

private:
	std::string name;
	bool userPermissions[3] = { false }; //boolean that translates to octal values, in rwx order. 4 = 1 0 0 = r--. 3 = 0 1 1 = -wx.
	bool groupPermissions[3] = { false };
	bool organizationPermissions[3] = { false };
};