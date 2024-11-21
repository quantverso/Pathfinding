#ifndef QUANTVERSO_WINDOW_H
#define QUANTVERSO_WINDOW_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include "Transformable.h"
#include "Color.h"
#include "Texture.h"
#include "Text.h"
#include "Shape.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <bitset>
#include <iostream>

//--------------------------------------------------------------------------------------------------

class Window
{
public:
	enum Event
	{
		Quit = SDL_QUIT,
		MouseButtonDown = SDL_MOUSEBUTTONDOWN,
		MouseButtonUp = SDL_MOUSEBUTTONUP
	};

	Window();
	~Window();

	void Create();
	void Create(const char* title, Uint32 width, Uint32 height);
	void Size(Uint32 width, Uint32 height);
	void Title(const char* title);
	void Close();
	void WatchEvents();
	void Clear(Color color = Color::Black);
	void Display();
	void Draw(const Text* text);
	void Draw(
		const Texture* texture,
		const Rect* srcRect = nullptr,
		const Rect* dstRect = nullptr,
		float angle = 0,
		const Vector2i* offset = nullptr);

	bool IsOpen() const;
	bool CheckEvent(Event event);
	const char* Title();
	static const ::Size& Size();
	static Vector2f Center();

private:
	friend class Texture;
	friend class Text;

	SDL_Window*   window;
	SDL_Renderer* renderer;
	SDL_Event	  event;
	std::bitset<MouseButtonUp + 1> events;

	const char*   title;
	static ::Size size;
};

//--------------------------------------------------------------------------------------------------

inline bool Window::IsOpen() const
{
	return window;
}


//--------------------------------------------------------------------------------------------------

inline void Window::WatchEvents()
{
	events.reset();
	while (SDL_PollEvent(&event))
		events[event.type] = true;
}

//--------------------------------------------------------------------------------------------------

inline bool Window::CheckEvent(Event event)
{
	return events[event];
}

//--------------------------------------------------------------------------------------------------

inline void Window::Clear(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Display()
{
	SDL_RenderPresent(renderer);
}

//--------------------------------------------------------------------------------------------------


inline void Window::Draw(const Text* text)
{
	SDL_RenderCopy(renderer, text->texture, nullptr, &text->rect);
}

//--------------------------------------------------------------------------------------------------

inline void Window::Draw(
	const Texture* texture,
	const Rect* srcRect,
	const Rect* dstRect,
	float angle,
	const Vector2i* offset)
{
	if (angle)
		SDL_RenderCopyEx(renderer, texture->texture, srcRect, dstRect, angle, offset, SDL_FLIP_NONE);
	else
		SDL_RenderCopy(renderer, texture->texture, srcRect, dstRect);
}

//--------------------------------------------------------------------------------------------------

inline const char* Window::Title()
{
	return title;
}

//--------------------------------------------------------------------------------------------------

inline const ::Size& Window::Size()
{
	return size;
}

//--------------------------------------------------------------------------------------------------

inline Vector2f Window::Center()
{
	return { size.width / 2.f, size.height / 2.f };
}

//--------------------------------------------------------------------------------------------------

#endif
