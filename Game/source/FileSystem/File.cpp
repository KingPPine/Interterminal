#include <FileSystem/File.h>

File::File()
{
}

File::~File()
{
}

void File::setName(std::string name)
{
	this->name = name;
}

std::string File::getName()
{
	return name;
}
