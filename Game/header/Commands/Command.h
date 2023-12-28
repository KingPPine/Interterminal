#pragma once
#include <list>
#include <string>

struct CommandDetails
{
	std::list<std::string> options;
	std::list<std::string> arguments;
};

class Command
{
public:
	Command();
	virtual ~Command();

	virtual std::string processCommand(CommandDetails commandDetails = { .options = {}, .arguments = {} });

protected:

protected:
	std::string command;
};