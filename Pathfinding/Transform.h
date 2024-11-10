#ifndef QUANTVERSO_TRANSFORM_H
#define QUANTVERSO_TRANSFORM_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include "Component.h"
#include "Rectangle.h"
using Vector2f = Rectangle::Vector2f;

//--------------------------------------------------------------------------------------------------

class Transform : public Component
{
public:
	Transform(Entity* entity);

	void Position(float x, float y);
	void Size(float width, float height);
	void Scale(float scale);
	void Move(float x, float y);
	void Origin(float x, float y);
	Vector2f Center() const;

private:
	friend class Entity;
	friend class Component;

	Rectangle rect;
};

//--------------------------------------------------------------------------------------------------

inline void Transform::Position(float x, float y)
{
	rect.Position(x, y);
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Size(float width, float height)
{
	rect.Size(width, height);
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Scale(float scale)
{
	rect.Scale(scale);
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Move(float x, float y)
{
	rect.Move(x, y);
}

//--------------------------------------------------------------------------------------------------

inline void Transform::Origin(float x, float y)
{
	rect.Origin(x, y);
}


//--------------------------------------------------------------------------------------------------

inline Vector2f Transform::Center() const
{
	return rect.Center();
}

//--------------------------------------------------------------------------------------------------

#endif
