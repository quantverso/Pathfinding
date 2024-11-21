#ifndef QUANTVERSO_IMAGE_H
#define QUANTVERSO_IMAGE_H

//--------------------------------------------------------------------------------------------------

#include <SDL_image.h>
#include "Transformable.h"

class Color;

//--------------------------------------------------------------------------------------------------

class Image
{
public:
	Image();
	virtual ~Image();
	void Load(const char* file);

	Color GetPixelColor(int x, int y) const;
	bool ComparePixelColor(int x, int y, Color color, int tolerance = 100) const;
	const ::Size& Size() const;

protected:
	::Size size;

private:
	friend class Window;

	SDL_Surface*	  surface;
	inline static int instances;
};

//--------------------------------------------------------------------------------------------------

inline const ::Size& Image::Size() const
{
	return size;
}

//--------------------------------------------------------------------------------------------------

#endif
