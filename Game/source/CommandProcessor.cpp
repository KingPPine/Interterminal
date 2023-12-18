#include "CommandProcessor.h"

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

std::string CommandProcessor::ProcessCommand(std::string commandLine)
{
	std::string commandResults = "command could not be processed";
	if (commandLine.empty())
		return commandResults;

	auto space = commandLine.find(" ");
	std::string command = commandLine.substr(0, space); //if no space was found, this will grab everything. Commands with no options / arguments are possible
	//options, instantiate
	//arguments, instantiate

	if (space != commandLine.npos) // a space was found
	{
		//options, set
		//arguments, set
	}

	commandResults = command + ": processed successfully";

	return commandResults;
}
