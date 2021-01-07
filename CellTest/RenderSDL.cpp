#include "RenderSDL.h"
#include <cstring>
#include <iostream>

RenderSDL::RenderSDL(std::shared_ptr<SDL_Window> win, int windowWidth, int windowHeight)
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
	
	_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);

	_borderColour[0] = 128;
	_borderColour[1] = 128;
	_borderColour[2] = 128;
	_borderColour[3] = 255;
}

RenderSDL::~RenderSDL()
{
	_images.Clear();
	ClearTextures();
	IMG_Quit();
}

std::shared_ptr<SDL_Texture> RenderSDL::GetTexture(std::shared_ptr<SDL_Surface> surface)
{
	std::map<std::shared_ptr<SDL_Surface>, std::shared_ptr<SDL_Texture>>::iterator it = _loadedTextures.find(surface);
	if (it == _loadedTextures.end())
	{
		std::shared_ptr<SDL_Texture> t = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(_renderer.get(), surface.get()), SDL_DestroyTexture);
		it = _loadedTextures.insert(it, std::make_pair(surface, t));
	}
	return it->second;
}

void RenderSDL::ClearTextures()
{
	_loadedTextures.clear();
}

void RenderSDL::StartRender(double frameDelta)
{
	_frameDelta = frameDelta;
	SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer.get());
	SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_BLEND);
}

void RenderSDL::RenderBorders()
{
	//use this for really basic rect borders
	SDL_Rect toprect{ 0, 0, _windowWidth, _borderHeight };
	SDL_Rect bottomrect{ 0, _windowHeight - _borderHeight, _windowWidth, _borderHeight };
	SDL_Rect leftrect{ 0, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };
	SDL_Rect rightrect{ _windowWidth - _borderWidth, _borderHeight, _borderWidth, _windowHeight - _borderHeight * 2 };

	SDL_SetRenderDrawColor(_renderer.get(), _borderColour[0], _borderColour[1], _borderColour[2], _borderColour[3]);

	SDL_RenderDrawRect(_renderer.get(), &toprect);
	SDL_RenderDrawRect(_renderer.get(), &bottomrect);
	SDL_RenderDrawRect(_renderer.get(), &leftrect);
	SDL_RenderDrawRect(_renderer.get(), &rightrect);

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
	SDL_RenderPresent(_renderer.get());
}
