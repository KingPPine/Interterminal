#pragma once
#include <Commands/Command.h>

class Cd : public Command
{
public:
	Cd();
	~Cd();

	virtual std::string processCommand(CommandDetails commandDetails = { .options = {}, .arguments = {} });

private:
	//possible flags?
};