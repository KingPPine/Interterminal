#pragma once
#include <string>
#include <vector>

class InputManager;
class CommandProcessor;
class TextManager
{
public:
	TextManager();
	~TextManager();

	void onUpdate();
	std::string* getDisplayText();
	std::string* getCommandLineText();

private:
	void addCommandHistory(std::string command);
	void navigateHistoryUp();
	void navigateHistoryDown();

private:
	CommandProcessor* commandProcessor;
	InputManager* inputManager;
	std::string displayText;
	std::string commandLineText;

	std::vector<std::string> commandHistory;
	int historyIndex = 0;
	int maxHistorySize = 100;
};
