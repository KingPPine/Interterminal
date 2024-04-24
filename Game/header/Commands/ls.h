#pragma once
#include <Commands/Command.h>

class Ls : public Command
{
public:
	Ls();
	~Ls();

	virtual std::string processCommand(CommandDetails commandDetails = { .options = {}, .arguments = {} });

private:
	//possible flags?
};