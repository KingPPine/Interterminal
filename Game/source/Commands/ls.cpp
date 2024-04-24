#include <Commands/ls.h>
#include <GameConstants.h>
#include <FileSystem/FileSystem.h>
#include <FileSystem/Directory.h>
#include <FileSystem/File.h>

Ls::Ls()
{

}
Ls::~Ls()
{
}

std::string Ls::processCommand(CommandDetails commandDetails)
{
	std::string result = "";
	for (Directory* directory : GameConstants::fileSystem->getCurrentDirectory()->getSubDirectories())
	{
		result += directory->getName() + "\n";
	}

	for (File* file : GameConstants::fileSystem->getCurrentDirectory()->getFiles())
	{
		result += file->getName() + "\n";
	}

	return result;
}
