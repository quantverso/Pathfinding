#ifndef QUANTVERSO_WINDOW_H
#define QUANTVERSO_WINDOW_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include "Texture.h"
#include "Text.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Transformable.h"
#include <unordered_set>
#include <iostream>

using Rect	   = SDL_Rect;
using Vector2i = SDL_Point;
using uint     = unsigned int;

//--------------------------------------------------------------------------------------------------

class Window
{
public:
	enum Event : uint {
		Quit = SDL_QUIT
	};

	static const uint& width;  ///< Largura da janela
	static const uint& height; ///< Altura da janela

	Window();
	~Window();
	void Create();
	void Create(const char* title, uint width, uint height);
	void Size(uint width, uint height);
	void Title(const char* title);
	bool IsOpen() const;
	void Close();
	void WatchEvents();
	bool CheckEvent(Event event);	
	void Clear(uint r = 0, uint g = 0, uint b = 0, uint a = 255);
	void Display();
	void Draw(const Text* text);
	void Draw(
		const Texture*   texture,
		const Rect*		 srcRect = nullptr,
		const Rect*		 dstRect = nullptr,
		float			 angle   = 0,
		const SDL_Point* offset  = nullptr
	);

	static Transformable::Size Center();

private:
	friend class Image;
	friend class Texture;
	friend class Text;

	SDL_Window*				 window;   ///< Janela gráfica
	SDL_Renderer*			 renderer; ///< Rederizador
	SDL_Event				 event;	   ///< Eventos
	std::unordered_set<uint> events;   ///< Hash de eventos

	const char*	title;	 ///< Título da janela
	static uint	width_;	 ///< Largura
	static uint	height_; ///< Altura
};

//--------------------------------------------------------------------------------------------------

inline bool Window::IsOpen() const
{
	return window;
}

//--------------------------------------------------------------------------------------------------

inline void Window::WatchEvents()
{
	events.clear();
	while (SDL_PollEvent(&event))
		events.insert(event.type);
}

//--------------------------------------------------------------------------------------------------

inline bool Window::CheckEvent(Event event)
{
	return events.find(event) != events.end() ? true : false;
}

//--------------------------------------------------------------------------------------------------

inline void Window::Clear(uint r, uint g, uint b, uint a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Display()
{
	SDL_RenderPresent(renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(
	const Texture* texture,
	const Rect* srcRect,
	const Rect* dstRect,
	float angle,
	const SDL_Point* offset)
{
	if (angle)
		SDL_RenderCopyEx(renderer, texture->texture, srcRect, dstRect, angle, offset, SDL_FLIP_NONE);
	else
		SDL_RenderCopy(renderer, texture->texture, srcRect, dstRect);
}

//--------------------------------------------------------------------------------------------------


inline void Window::Draw(const Text* text)
{
	SDL_RenderCopy(renderer, text->texture, nullptr, &text->rect);
}

//--------------------------------------------------------------------------------------------------

inline Transformable::Size Window::Center()
{
	return { width / 2.f, height / 2.f };
}

//--------------------------------------------------------------------------------------------------

#endif
