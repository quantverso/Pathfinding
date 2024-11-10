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
	void Color(::Color color);

	SDL_Rect Bounds();

private:
	friend class Window;
	
	std::string	  text;			 ///< Texto a ser renderizado
	Uint32		  size;			 ///< Tamanho do texto
	::Color		  color;		 ///< Cor do texto
	TTF_Font*	  font;			 ///< Fonte carregada do ttf
	SDL_Texture*  texture;		 ///< Textura rederizada
	SDL_Surface*  surface;		 ///< Superfície de renderização
	SDL_Rect	  rect;			 ///< Limites de renderização
	static int	  instanceCount; ///< Contador de instâncias
};

//--------------------------------------------------------------------------------------------------

inline SDL_Rect Text::Bounds()
{
	return rect;
}

//--------------------------------------------------------------------------------------------------

#endif
