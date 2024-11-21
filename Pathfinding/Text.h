#ifndef QUANTVERSO_TEXT_H
#define QUANTVERSO_TEXT_H

//--------------------------------------------------------------------------------------------------

#include "SDL_ttf.h"
#include "Color.h"
#include <string>

class Window;

//--------------------------------------------------------------------------------------------------

class Text
{
public:
	Text();
	~Text();
	void Load(const char* file, Uint32 size);
	void String(const std::string& string);
	void Position(int x, int y);
	void Size(int w, int h);
	void Size(float w, float h);
	void Color(::Color color);

	SDL_Rect Bounds() const;

private:
	friend class Window;

	std::string		  text;		 ///< Texto a ser renderizado
	Uint32			  size;		 ///< Tamanho da fonte
	::Color			  color;	 ///< Cor do texto
	TTF_Font*		  font;		 ///< Fonte carregada do arquivo .ttf
	SDL_Texture*	  texture;	 ///< Textura renderizada
	SDL_Surface*      surface;	 ///< Superfície de renderização
	SDL_Rect		  rect;		 ///< Rect de renderização
	inline static int instances; ///< Contador de instâncias
};

//--------------------------------------------------------------------------------------------------

inline void Text::Position(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

//--------------------------------------------------------------------------------------------------

inline void Text::Size(int w, int h)
{
	size = w;
	rect.w = w;
	rect.h = h;
}

//--------------------------------------------------------------------------------------------------

inline void Text::Size(float w, float h)
{
	Size(int(w), int(h));
}

//--------------------------------------------------------------------------------------------------

inline void Text::Color(::Color color)
{
	this->color = color;
	if (!text.empty())
		String(text);
}

//--------------------------------------------------------------------------------------------------

inline SDL_Rect Text::Bounds() const
{
	return rect;
}

//--------------------------------------------------------------------------------------------------

#endif
