#ifndef QUANTVERSO_TEXTURE_H
#define QUANTVERSO_TEXTURE_H

//--------------------------------------------------------------------------------------------------

#include "Image.h"

class Color;

//--------------------------------------------------------------------------------------------------

class Texture : Image
{
public:
	Texture();
	~Texture();
	void Load(const char* file);
	void Color(::Color color);

	::Size Size() const;

private:
	friend class Window;

	SDL_Texture* texture;
};

//--------------------------------------------------------------------------------------------------

inline ::Size Texture::Size() const
{
	return Image::Size();
}

//--------------------------------------------------------------------------------------------------

#endif
