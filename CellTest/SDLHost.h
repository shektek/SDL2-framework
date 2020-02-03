#ifndef SDLHOST_H
#define SDLHOST_H

#include "AppHost.h"
#include "RenderSDL.h"

class SDLHost : public AppHost
{
	private:
		bool _running;
		RenderSDL* _renderSdl;
		SDL_Window* _window;
		int _mapWidth;
		int _mapHeight;

		bool HandleEvents();
		void Test();
	public:
		SDLHost();
		virtual ~SDLHost();

		bool Init(int argc, char** argv);
		void Exec();
		void Quit();
};

#endif