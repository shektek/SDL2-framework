#include "SDLHost.h"

SDLHost::SDLHost()
{
	_running = false;
	_mapWidth = 14;
	_mapHeight = 8;
}

SDLHost::~SDLHost()
{
}

bool SDLHost::Init(int argc, char** argv)
{
	_running = (SDL_Init(SDL_INIT_EVERYTHING) == 0);
	int width = 800;
	int height = 600;
	_window = SDL_CreateWindow(argv[0], 100, 100, width, height, 0);
	_renderSdl = new RenderSDL(_window, width, height);

	return _running;
}

bool SDLHost::HandleEvents()
{
	bool result = true;
	SDL_Event e;

	//basic stuff you might want to do
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			result = false;
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_SPACE)
			{
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				//quick quit via esc key
				result = false;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
		}
	}

	return result;
}

void SDLHost::Exec()
{
	double frameStart = 0, frameEnd = SDL_GetTicks(), frameDelta = 0;

	while (_running)
	{
		frameStart = SDL_GetTicks();
		frameDelta = frameEnd - frameStart;

		_running = HandleEvents();

		if (_running)
		{
			int mousex = 0, mousey = 0;
			SDL_GetMouseState(&mousex, &mousey);

			_renderSdl->StartRender(frameDelta);

			//render all your stuff
			_renderSdl->RenderBorders();

			_renderSdl->FinishRender();

			frameEnd = SDL_GetTicks();
		}
	}
}

void SDLHost::Quit()
{
	SDL_DestroyWindow(_window);
}