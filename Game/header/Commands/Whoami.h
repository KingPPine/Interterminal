#pragma once
#include <Commands/Command.h>

class Whoami : public Command
{
public:
	Whoami();
	~Whoami();

	virtual std::string processCommand(CommandDetails commandDetails = { .options = {}, .arguments = {} });

private:
	//possible flags?
};