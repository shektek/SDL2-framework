#include "ImageCache.h"

ImageCache::~ImageCache()
{
	Clear();
}

std::shared_ptr<SDL_Surface> ImageCache::GetImage(std::string filename)
{
	std::map<std::string, std::shared_ptr<SDL_Surface>>::iterator it = _cache.find(filename);
	if (it == _cache.end())
	{
		std::shared_ptr<SDL_Surface> s = std::shared_ptr<SDL_Surface>(IMG_Load(filename.c_str()), SDL_FreeSurface);
		it = _cache.insert(it, std::make_pair(filename, s));
	}
	return it->second;
}

void ImageCache::Clear()
{
	_cache.clear();
}
