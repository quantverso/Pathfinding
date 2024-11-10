#ifndef QUANTVERSO_SHAPE_H
#define QUANTVERSO_SHAPE_H

//--------------------------------------------------------------------------------------------------

#include "Transformable.h"

class Window;

//--------------------------------------------------------------------------------------------------

class Shape : public Transformable
{
public:
	const Vector2f& position; ///< Posição da forma geométrica

	Shape();
	virtual ~Shape() {};
};

//--------------------------------------------------------------------------------------------------

#endif
