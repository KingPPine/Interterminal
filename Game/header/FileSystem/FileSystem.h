#pragma once
#include<FileSystem/Directory.h>

class FileSystem 
{
public:
	FileSystem();
	~FileSystem();

	void initialize(); //initializing without any save data

	Directory* getRootDirectory();
	void setCurrentDirectory(Directory* directory);
	Directory* getCurrentDirectory();

private:
	Directory* rootDirectory;
	Directory* currentDirectory;
	Directory* previousDirectory;
};