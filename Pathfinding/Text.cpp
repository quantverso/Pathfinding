#include "Text.h"
#include "Engine.h"

//--------------------------------------------------------------------------------------------------

int Text::instanceCount {};

//--------------------------------------------------------------------------------------------------

Text::Text() :
	size(0),
	font(nullptr),
	texture(nullptr),
	surface(nullptr),
	rect({}),
	color({})
{
	if (instanceCount++ == 0)
		if (TTF_Init() == -1)
			std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
}

//--------------------------------------------------------------------------------------------------

Text::~Text()
{
	if (texture)
		SDL_DestroyTexture(texture);
	if (font)
		TTF_CloseFont(font);

	if (--instanceCount == 0)
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

void Text::Position(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

//--------------------------------------------------------------------------------------------------

void Text::Size(int w, int h)
{
	size = w;
	rect.w = w;
	rect.h = h;
}

//--------------------------------------------------------------------------------------------------

void Text::Color(::Color color)
{
	this->color = color;
	if (!text.empty())
		String(text);
}

//--------------------------------------------------------------------------------------------------
