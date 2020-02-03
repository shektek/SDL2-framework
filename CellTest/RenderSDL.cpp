#include "RenderSDL.h"
#include <cstring>

RenderSDL::RenderSDL(SDL_Window* win, int windowWidth, int windowHeight)
{
	_xGridSpacing = 0;
	_yGridSpacing = 0;
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	_window = win;

	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	short windowOriginX = 0;
	short windowOriginY = 0;

	_borderWidth = (windowWidth / 100) * 3;
	_borderHeight = (windowHeight / 100) * 3;

	_viewportWidth = windowWidth - _borderWidth;
	_viewportHeight = windowHeight - (_borderHeight);
	_viewportOriginX = windowOriginX + _borderWidth;
	_viewportOriginY = windowOriginY + _borderHeight;
	
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	_borderColour[0] = 128;
	_borderColour[1] = 128;
	_borderColour[2] = 128;
	_borderColour[3] = 255;

	//char str[256] = { 0 };
	//sprintf(str, "%s%s", imagesDir, battleBgImg);
	//_backgroundSurface = _images.GetImage(str);
	//_backgroundTexture = SDL_CreateTextureFromSurface(_renderer, _backgroundSurface);
}

RenderSDL::~RenderSDL()
{
	_images.Clear();
	ClearTextures();
	//SDL_DestroyTexture(_backgroundTexture);
	SDL_DestroyRenderer(_renderer);

	IMG_Quit();
}

SDL_Texture* RenderSDL::GetTexture(SDL_Surface* surface)
{
	std::map<SDL_Surface*, SDL_Texture*>::iterator it = _loadedTextures.find(surface);
	if (it == _loadedTextures.end())
	{
		SDL_Texture* t = SDL_CreateTextureFromSurface(_renderer, surface);
		it = _loadedTextures.insert(it, std::make_pair(surface, t));
	}
	return it->second;
}

void RenderSDL::ClearTextures()
{
	for (std::map<SDL_Surface*, SDL_Texture*>::iterator it = _loadedTextures.begin();
		it != _loadedTextures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}

	_loadedTextures.clear();
}

void RenderSDL::StartRender(double frameDelta)
{
	_frameDelta = frameDelta;
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

void RenderSDL::RenderBorders()
{
	//use this for really basic rect borders
	SDL_Rect toprect{ 0, 0, _windowWidth, _borderHeight };
	SDL_Rect bottomrect{ 0, _windowHeight - _borderHeight, _windowWidth, _borderHeight };
	SDL_Rect leftrect{ 0, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };
	SDL_Rect rightrect{ _windowWidth - _borderWidth, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };

	SDL_SetRenderDrawColor(_renderer, _borderColour[0], _borderColour[1], _borderColour[2], _borderColour[3]);

	SDL_RenderDrawRect(_renderer, &toprect);
	SDL_RenderDrawRect(_renderer, &bottomrect);
	SDL_RenderDrawRect(_renderer, &leftrect);
	SDL_RenderDrawRect(_renderer, &rightrect);

	//use this for textured borders
	//char buf[256] = { 0 };
	//sprintf(buf, "%s%s", imagesDir, borderHorImg);
	//SDL_Surface* sh = _images.GetImage(buf);
	//memset(buf, 0, 256);
	//sprintf(buf, "%s%s", imagesDir, borderVerImg);
	//SDL_Surface* sv = _images.GetImage(buf);
	//SDL_Texture* th = GetTexture(sh);
	//SDL_Texture* tv = GetTexture(sv);

	//SDL_Rect toprect{ 0, 0, _windowWidth, _borderHeight };
	//SDL_Rect bottomrect{ 0, _windowHeight - _borderHeight, _windowWidth, _borderHeight };
	//SDL_Rect leftrect{ 0, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };
	//SDL_Rect rightrect{ _windowWidth - _borderWidth, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };
	//SDL_RenderCopy(_renderer, th, NULL, &toprect);
	//SDL_RenderCopy(_renderer, th, NULL, &bottomrect);
	//SDL_RenderCopy(_renderer, tv, NULL, &leftrect);
	//SDL_RenderCopy(_renderer, tv, NULL, &rightrect);
}

void RenderSDL::FinishRender()
{
	SDL_RenderPresent(_renderer);
}
