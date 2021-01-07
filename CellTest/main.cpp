#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifdef CONSOLE_APP
#include "ConsoleHost.h"
#define HOST_TYPE ConsoleHost
#else
#include "SDLHost.h"
#define HOST_TYPE SDLHost
#endif

int main(int argc, char **argv)
{
	srand((unsigned)time(0));

	std::shared_ptr<SDLHost> app = std::make_shared<HOST_TYPE>();

	if (app->Init(argc, argv))
	{
		app->Exec();
	}

	app->Quit();

	return 0;
}
