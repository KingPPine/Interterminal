#include <MyGame.h> //Can be called out in the angular brackets because of the VC++ additional directories in the project settings
#include <iostream> //input output

int main()
{
	//OpenGL Documentation: https://registry.khronos.org/OpenGL-Refpages/gl4/
	try
	{
		MyGame game; //creates instance of MyGame, which inherits OGame 
		game.run(); //calls the run method housed in OGame.cpp
	}
	catch (const std::exception e) //used to be "exception&" but I removed that because it makes no sense to treat this an address(??). Made no difference.
	{
		std::wclog << e.what() << std::endl; //wclog, w = wide, c = character, log = it uses the logging stream (I think? Documentation is so bad for c++ wow)
		return -1;
	}

	
	return 0;
}