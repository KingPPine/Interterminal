#include <CommandProcessor.h>
#include <TextManager.h>
#include <GameConstants.h>

TextManager::TextManager()
{
	inputManager = GameConstants::inputManager;
	commandProcessor = new CommandProcessor();
}

TextManager::~TextManager()
{
}

void TextManager::onUpdate()
{
	commandLineText.append(inputManager->getCharacters());

	//backspace
	if (inputManager->keyDown(KeyCode::Backspace))
		commandLineText.pop_back();

	//up arrow - going up in history
	if (inputManager->keyDown(KeyCode::UpArrow))
		navigateHistoryUp();
	//down arrow - going down in history
	if (inputManager->keyDown(KeyCode::DownArrow))
		navigateHistoryDown();

	//enter command
	if (inputManager->keyDown(KeyCode::Enter))
	{
		addCommandHistory(commandLineText);
		std::string result = commandProcessor->ProcessCommand(commandLineText);
		displayText += commandLineText + "\n" + result + "\n";
		commandLineText = "";
	}

}

std::string* TextManager::getDisplayText()
{
	return &displayText;
}

std::string* TextManager::getCommandLineText()
{
	return &commandLineText;
}

void TextManager::addCommandHistory(std::string command)
{
	commandHistory.push_back(command);
	if (commandHistory.size() > maxHistorySize)
		commandHistory.erase(commandHistory.begin()); //get rid of the first element

	historyIndex = commandHistory.size();
}

void TextManager::navigateHistoryUp()
{
	if (!commandHistory.empty() && historyIndex > 0)
	{
		historyIndex--;
		commandLineText = commandHistory[historyIndex];
	}
}

void TextManager::navigateHistoryDown()
{
	if (!commandHistory.empty() && historyIndex < commandHistory.size() - 1)
	{
		historyIndex++;
		commandLineText = commandHistory[historyIndex];
	}
}
