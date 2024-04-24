#include <Commands/cd.h>
#include <GameConstants.h>
#include <FileSystem/FileSystem.h>
#include <FileSystem/Directory.h>
#include <FileSystem/File.h>

Cd::Cd()
{

}
Cd::~Cd()
{
}

std::string Cd::processCommand(CommandDetails commandDetails)
{
	bool found = false;
	std::string result = "";
	
	//TODO: add parent directory (..), root directory (starting with '/'), and multiple directories.
	//TODO: also add a function that allows the tab key to auto-complete the directory name
	//TODO: Add '-' to go back to the previous directory
	if (commandDetails.arguments.size() == 1)
	{
		std::string desiredDirectory = commandDetails.arguments.front();

		if (desiredDirectory == "..")
		{
			if (GameConstants::fileSystem->getCurrentDirectory() == GameConstants::fileSystem->getRootDirectory())
			{
				return "cannot access parent directory of root.";
			}

			GameConstants::fileSystem->setCurrentDirectory(GameConstants::fileSystem->getCurrentDirectory()->getParentDirectory());
			found = true;
		}
		
		for (Directory* directory : GameConstants::fileSystem->getCurrentDirectory()->getSubDirectories())
		{
			if (directory->getName() == desiredDirectory)
			{
				GameConstants::fileSystem->setCurrentDirectory(directory);
				found = true;
			}
		}
	}

	if (!found)
		result += "directory not found";

	return result;
}
