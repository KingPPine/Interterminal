#pragma once
#include <string>
#include <unordered_map>

class Command;
class CommandProcessor
{
public:
	CommandProcessor();
	~CommandProcessor();

	std::string ProcessCommand(std::string commandLine); //processes a command from TextManager and returns what needs to print to the terminal

private:
	std::unordered_map<std::string, Command*> commandMap;
};
