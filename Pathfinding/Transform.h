#ifndef QUANTVERSO_TRANSFORM_H
#define QUANTVERSO_TRANSFORM_H

//--------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

class Transform : public Component, public Rectangle
{
public:
	Transform(Entity* entity);

private:
	friend class Entity;

	void Refresh();
};

//--------------------------------------------------------------------------------------------------

inline void Transform::Refresh()
{
	Rectangle::Refresh();
}

//--------------------------------------------------------------------------------------------------

#endif
