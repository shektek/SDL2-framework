#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include <map>
#include <string>
#include <memory>

class ImageCache
{
	private:
		std::map<std::string, std::shared_ptr<SDL_Surface>> _cache;

	public:
		~ImageCache();

		std::shared_ptr<SDL_Surface> GetImage(std::string filename);
		void Clear();
};

#endif