#ifndef QUANTVERSO_TRANSFORMABLE_H
#define QUANTVERSO_TRANSFORMABLE_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>

//--------------------------------------------------------------------------------------------------

class Transformable
{
public:
	struct Vector2f {
		float x, y;
	};

	struct Size {
		float width, height;
	};

	class Offset : SDL_Point
	{
	public:
		void Position(float x, float y, float w, float h)
		{
			this->x = int(x);
			this->y = int(y);

			// Percentual de deslocamento relativo as dimensões.
			perX = x ? w / x : 0;
			perY = y ? h / y : 0;
		}

		void Update(float width, float height)
		{
			x = perX ? int(width / perX) : 0;
			y = perY ? int(height / perY) : 0;
		}

		int X() {
			return x;
		}

		int Y() {
			return y;
		}

	private:
		friend class Entity;

		float perX{};
		float perY{};
	};

	virtual ~Transformable() = 0;
	virtual void Update() {};

	void Position(float x, float y);
	void Move(float x, float y);
	void Scale(float scale);

protected:
	Vector2f position{};
	float	 scale{ 1 };
};

//--------------------------------------------------------------------------------------------------

inline Transformable::~Transformable()
{
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Position(float x, float y)
{
	position.x = x;
	position.y = y;
	Update();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Scale(float scale)
{
	this->scale = scale;
	Update();
}

//--------------------------------------------------------------------------------------------------

inline void Transformable::Move(float x, float y)
{
	Position(position.x + x, position.y + y);
}

//--------------------------------------------------------------------------------------------------

#endif
