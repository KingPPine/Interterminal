#pragma once
#include<FileSystem/Directory.h>

class FileSystem 
{
public:
	FileSystem();
	~FileSystem();

private:
	Directory* rootDirectory;
	Directory* currentDirectory;
};