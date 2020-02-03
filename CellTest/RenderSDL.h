#ifndef RENDERSDL_H
#define RENDERSDL_H

#pragma comment(lib, "lib/x64/SDL2.lib")
#pragma comment(lib, "lib/x64/SDL2main.lib")
#pragma comment(lib, "lib/x64/SDL2_image.lib")

#include <map>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "ImageCache.h"

class RenderSDL
{
private:
	//the viewport is the non-2D-border/UI portion of the screen
	short _viewportWidth;
	short _viewportHeight;
	short _viewportOriginX;
	short _viewportOriginY;

	short _borderWidth;
	short _borderHeight;

	int _windowWidth;
	int _windowHeight;
	int _xGridSpacing;
	int _yGridSpacing;

	double _frameDelta;
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	SDL_Surface* _backgroundSurface;
	SDL_Texture* _backgroundTexture;
	ImageCache _images;
	std::map<SDL_Surface*, SDL_Texture*> _loadedTextures;

	short _borderColour[4];

	void ClearTextures();

public:
	RenderSDL(SDL_Window* win, int windowWidth, int windowHeight);
	virtual ~RenderSDL();

	void StartRender(double frameDelta);

	//put your render functions in here
	void RenderBorders();

	void FinishRender();

	SDL_Texture* GetTexture(SDL_Surface* surface);

	SDL_Renderer* GetRenderer() { return _renderer; } //temp
};

#endif