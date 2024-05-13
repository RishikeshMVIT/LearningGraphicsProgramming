#include "Application.h"

int main()
{

	Application* app = new Application();
	app->Initialize();
	app->Run();
	app->Shutdown();
	return 0;
}
