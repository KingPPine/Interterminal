#include "CommandProcessor.h"
#include <Commands/Command.h>
#include <Commands/Whoami.h>

CommandProcessor::CommandProcessor()
{
	//TODO: I hate that I'm creating individual objects for each command. Surely there's a better way
	commandMap.insert({ "whoami", new Whoami()});
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
	std::list<std::string> options;
	std::list<std::string> arguments;

	commandLine.erase(0, space + 1); //+1 for the size of the space character
	while (space != commandLine.npos) // a space was found, continue to iterate through the elements
	{
		//set options and arguments based on if '-' or '--' exists at the front of the next token
		auto space = commandLine.find(" "); //search for the next space. Searching here should capture the end of the string on the final loop

		std::string token = commandLine.substr(0, space);
		if (token.length() > 1 && token[0] == '-')
		{
			if (token.length() > 2 && token[1] == '-') //'--' style option
			{
				options.push_back(token.substr(2, token.npos));
			}
			else //'-' style option
			{
				for (char c : token.substr(1, token.npos))
				{
					options.push_back(std::string{ c });
				}
			}
		}
		else if (!token.empty())//no preceding dashes, so it's an argument
		{
			arguments.push_back(token);
		}

		if (space == commandLine.npos)
			break;

		commandLine.erase(0, space + 1); //+1 for the size of the space character
	}

	//see if the command exists in the commandMap, and call it
	std::unordered_map<std::string, Command*>::iterator it = commandMap.find(command);
	if (it != commandMap.end()) //found the right command
	{
		commandResults = it->second->processCommand(CommandDetails{options, arguments});
	}

	return commandResults;
}
