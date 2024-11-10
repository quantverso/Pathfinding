#ifndef QUANTVERSO_RECTANGLE_H
#define QUANTVERSO_RECTANGLE_H

//--------------------------------------------------------------------------------------------------

#include "Shape.h"
#include "Window.h"

//--------------------------------------------------------------------------------------------------

class Rectangle : public Shape
{
public:
	struct Bounds {
		const int& left;
		const int& top;
		int		   right;
		int		   bottom;
	};

	const float&  width{ width_ };
	const float&  height{ height_ };
	const Bounds& bounds{ bounds_ };

	Rectangle(bool filled = false);

	void Position(float x, float y);
	void Size(float width, float height);
	void Scale(float scale);
	void Move(float x, float y);
	void Origin(float x, float y);
	Vector2f Center() const;

private:
	friend class Entity;

	const bool filled{};
	float	   width_{ 100 };
	float	   height_{ 100 };
	Rect	   rect{ 0, 0, int(width), int(height) };
	Bounds	   bounds_{ rect.x, rect.y };
	Offset	   offset{};

	void Update();
};

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Position(float x, float y)
{
	Transformable::Position(x, y);
	Update();
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Size(float width, float height)
{
	rect.w = int(this->width_ = width);
	rect.h = int(this->height_ = height);
	offset.Update(width, height);
	Update();
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Scale(float scale)
{
	Transformable::Scale(scale);
	Size(width * scale, height * scale);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Move(float x, float y)
{
	Position(position.x + x, position.y + y);
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Origin(float x, float y)
{
	offset.Position(x, y, width, height);
	Update();
}

//--------------------------------------------------------------------------------------------------

inline Transformable::Vector2f Rectangle::Center() const
{
	return { rect.x + width / 2, rect.y + height / 2 };
}

//--------------------------------------------------------------------------------------------------

inline void Rectangle::Update()
{
	bounds_.right = rect.w + (rect.x = int(position.x) - offset.X());
	bounds_.bottom = rect.h + (rect.y = int(position.y) - offset.Y());
}

//--------------------------------------------------------------------------------------------------

#endif
