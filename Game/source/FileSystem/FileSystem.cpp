#include <FileSystem/FileSystem.h>

FileSystem::FileSystem()
{
	//doing this to satisfy the constructor. Needs to be deleted and recreated when initializing with save data
	rootDirectory = new Directory(); 
	currentDirectory = rootDirectory;
	previousDirectory = currentDirectory;
}

FileSystem::~FileSystem()
{
}

void FileSystem::initialize()
{
	if (rootDirectory != nullptr)
	{
		//name is 'root', even thought that's irrelevant
		//give it a test subdirectory and file
		//give the subdirectory its own file

		rootDirectory->setName("root");

		Directory* subdirectory = new Directory();
		subdirectory->setName("subdirectory");
		subdirectory->setParentDirectory(rootDirectory);
		rootDirectory->addDirectory(subdirectory);

		File* subfile = new File();
		subfile->setName("subfile");
		rootDirectory->addFile(subfile);

		Directory* subsubdirectory = new Directory();
		subsubdirectory->setName("subsub");
		subsubdirectory->setParentDirectory(subdirectory);
		subdirectory->addDirectory(subsubdirectory);
	}
}

Directory* FileSystem::getRootDirectory()
{
	return rootDirectory;
}

void FileSystem::setCurrentDirectory(Directory* directory)
{
	previousDirectory = currentDirectory;
	currentDirectory = directory;
}

Directory* FileSystem::getCurrentDirectory()
{
	return currentDirectory;
}
