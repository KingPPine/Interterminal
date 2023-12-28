#include <Commands/Command.h>

Command::Command()
{
}

Command::~Command()
{
}

std::string Command::processCommand(CommandDetails commandDetails)
{
	return "command override not found";
}
