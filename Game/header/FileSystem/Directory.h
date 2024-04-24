#pragma once
#include <FileSystem/File.h>
#include <string>
#include <list>

class Directory
{
public:
	Directory();
	~Directory();

	std::list<Directory*> getSubDirectories();
	std::list<File*> getFiles();

	void setName(std::string name);
	std::string getName();
	void setParentDirectory(Directory* directory);
	Directory* getParentDirectory();
	bool addDirectory(Directory* directory); //might need string return type instead of bool to allow error messages to be passed back to commands
	bool removeDirectory(Directory* directory);
	bool addFile(File* file);
	bool removeFile(File* file);

private:
	std::string name;
	Directory* parentDirectory;
	std::list<Directory*> directories;
	std::list<File*> files;
};