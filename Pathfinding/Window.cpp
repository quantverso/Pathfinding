#include "Window.h"

//--------------------------------------------------------------------------------------------------

unsigned int		Window::width_{ 640 };
unsigned int		Window::height_{ 480 };
const unsigned int& Window::width{ width_ };
const unsigned int& Window::height{ height_ };

//--------------------------------------------------------------------------------------------------

Window::Window() :
	window(nullptr),
	renderer(nullptr),
	event(),
	title("Window")
{	
}

//--------------------------------------------------------------------------------------------------

Window::~Window()
{
	Close();
}

//--------------------------------------------------------------------------------------------------

void Window::Create()
{	
	if (!window)
	{
		// Inicializa a SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
			return;
		}

		// Cria a janela gráfica
		if (!(window = SDL_CreateWindow
		(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_SHOWN
		)))
		{
			std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}
		else if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
		{
			std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
			Close();
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Window::Create(const char* title, uint width, uint height)
{
	if (!window) {
		this->title = title;
		width_ = width;
		height_ = height;

		Create();
	}
}

//--------------------------------------------------------------------------------------------------

void Window::Size(uint width, uint height)
{
	width_ = width;
	height_ = height;

	if (window)
		SDL_SetWindowSize(window, width, height);
}

//--------------------------------------------------------------------------------------------------

void Window::Title(const char* title)
{
	this->title = title;

	if (window)
		SDL_SetWindowTitle(window, title);
}

//--------------------------------------------------------------------------------------------------

void Window::Close()
{
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;

		if (Image::instanceCount + Text::instanceCount == 0)
			SDL_Quit();
	}
}

//--------------------------------------------------------------------------------------------------
