#ifndef QUANTVERSO_SHAPE_H
#define QUANTVERSO_SHAPE_H

//--------------------------------------------------------------------------------------------------

#include "Transformable.h"

class Window;

//--------------------------------------------------------------------------------------------------

class Shape : public Transformable
{
public:
	const Vector2f& position; ///< Posi��o da forma geom�trica

	Shape();
	virtual ~Shape() {};
};

//--------------------------------------------------------------------------------------------------

#endif
