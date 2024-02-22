
#include <iostream>
#include "App\App.h"

int main()
{
	try
	{
		App* game = new App();
		game->Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
