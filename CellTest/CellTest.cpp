// CellTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

	SDLHost* app = new HOST_TYPE();

	if (app->Init(argc, argv))
	{
		app->Exec();
	}

	app->Quit();

	delete app;

	return 0;
}
