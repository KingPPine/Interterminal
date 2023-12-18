#pragma once
#include <list>
#include <string>

class Command
{
public:
	Command();
	virtual ~Command();

protected:

protected:
	std::string command;
	std::list<std::string> options;
	std::list<std::string> arguments;
};