#include <Commands/Whoami.h>

Whoami::Whoami()
{

}
Whoami::~Whoami()
{
}

std::string Whoami::processCommand(CommandDetails commandDetails)
{
	std::string name = "Zachary";
	if (!commandDetails.arguments.empty())
	{
		if (commandDetails.arguments.size() > 1)
			return "whoami takes a maximum of one argument";

		name = commandDetails.arguments.front();
	}

	std::string returnData = "I am " + name;
	for (std::string s : commandDetails.options)
	{
		if (s == "c")
			returnData.append("\nfound the c flag");
		if (s == "f")
			returnData.append("\nfound the f flag");
		if (s == "full")
			returnData.append("\nfound the \'full\' option");
	}

	return returnData;
}
