#pragma once
#include <string>
#include <list>

class Directory
{
public:
	Directory();
	~Directory();

private:
	std::string name;
	std::list<Directory*> directories;
};