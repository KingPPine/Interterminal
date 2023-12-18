#pragma once
#include <string>

class CommandProcessor
{
public:
	CommandProcessor();
	~CommandProcessor();

	std::string ProcessCommand(std::string commandLine); //processes a command from TextManager and returns what needs to print to the terminal

private:

};
