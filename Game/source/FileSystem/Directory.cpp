#include <FileSystem/Directory.h>

Directory::Directory()
{
	parentDirectory = nullptr;
}

Directory::~Directory()
{
}

std::list<Directory*> Directory::getSubDirectories()
{
	return directories;
}

std::list<File*> Directory::getFiles()
{
	return files;
}

void Directory::setName(std::string name)
{
	this->name = name;
}

std::string Directory::getName()
{
	return name;
}

void Directory::setParentDirectory(Directory* directory)
{
	parentDirectory = directory;
}

Directory* Directory::getParentDirectory()
{
	return parentDirectory;
}

bool Directory::addDirectory(Directory* directory)
{
	directories.push_back(directory);
	return true;
}

bool Directory::removeDirectory(Directory* directory)
{
	directories.remove(directory);
	delete(directory);
	return true;
}

bool Directory::addFile(File* file)
{
	files.push_back(file);
	return true;
}

bool Directory::removeFile(File* file)
{
	files.remove(file);
	delete(file);
	return true;
}
