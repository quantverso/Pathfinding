#include "Text.h"
#include "Engine.h"

//--------------------------------------------------------------------------------------------------

Text::Text() :
	size{},
	font{},
	texture{},
	surface{},
	rect{},
	color{}
{
	if (instances++ == 0 && TTF_Init() == -1)
		std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

Text::~Text()
{
	if (texture)
		SDL_DestroyTexture(texture);
	if (font)
		TTF_CloseFont(font);

	if (--instances == 0)
	{
		TTF_Quit();
		Engine::window.Close();
	}
}

//--------------------------------------------------------------------------------------------------

void Text::Load(const char* file, Uint32 size)
{
	this->size = size;
	if (font = TTF_OpenFont(file, size))
	{
		rect.h = size;
		rect.w = size;
	}
	else
		std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

void Text::String(const std::string& string)
{
	text = string;
	rect.w = Uint32(string.size()) * size;
	if (surface = TTF_RenderText_Solid(font, string.c_str(), color))
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}

		if (!(texture = SDL_CreateTextureFromSurface(Engine::window.renderer, surface)))
			std::cerr << "Erro ao criar textura de texto: " << SDL_GetError() << std::endl;

		SDL_FreeSurface(surface);
		surface = nullptr;
	}
	else
		std::cerr << "Erro ao criar superficie de texto: " << TTF_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------
