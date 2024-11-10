#include "Color.h"

//--------------------------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

const Color Color::Black{ 0, 0, 0 };
const Color Color::White{ 255, 255, 255 };
const Color Color::Red{ 255, 0, 0 };
const Color Color::Green{ 0, 255, 0 };
const Color Color::Blue{ 0, 0, 255 };
const Color Color::Yellow{ 255, 255, 0 };
const Color Color::Magenta{ 255, 0, 255 };
const Color Color::Cyan{ 0, 255, 255 };

//--------------------------------------------------------------------------------------------------

Color::Color() :
	SDL_Color{ Black }
{
};

//--------------------------------------------------------------------------------------------------

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) :
	SDL_Color{ r, g, b, a }
{
}

//--------------------------------------------------------------------------------------------------

Color::Color(const Color& other) :
	SDL_Color(other)
{
}

//--------------------------------------------------------------------------------------------------

Color& Color::operator=(const Color& other)
{
	if (this != &other)
		SDL_Color::operator=(other);
	return *this;
}

//--------------------------------------------------------------------------------------------------
