#include "Tile.h"
#include "EightPuzzle.h"

//--------------------------------------------------------------------------------------------------

Tile::Tile() :
	index{ []()
		{
			static size_t index{};
			return index++;
		}()
	}
{
}

//--------------------------------------------------------------------------------------------------

void Tile::Awake()
{
	auto game{ GetScene<EightPuzzle>() };

	// Calcula o tamanho da pe�a
	size = (window.GetSize().width - game->borderSize * 2) / 3;

	// Carrega a textura da pe�a
	static Texture texture("Resources/tiles.png");
	sprite.SetTexture(&texture);
	
	// Define tamanho e posi��o da pe�a
	transform.SetSize(size, size);

	float x{ game->tiles[index] % 3 * size + game->borderSize };
	float y{ float(game->tiles[index] / 3) * size + game->borderSize };
	transform.Position(x, y);
}

//--------------------------------------------------------------------------------------------------

void Tile::Update()
{
	Node& tiles{ GetScene<EightPuzzle>()->tiles };
	if (tiles[index] != 0)
	{
		sprite.SetRect({ (tiles[index] - 1) * 334, 0, 334, 334 });

		if (window.IsEventTriggered(Window::MouseButtonDown))
		{
			Point point{ Mouse::Position() };
			if (transform.CheckCollision(&point))
				clicked = index;
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Tile::Draw()
{
	if (GetScene<EightPuzzle>()->tiles[index] != 0)
		Entity::Draw();
}

//--------------------------------------------------------------------------------------------------
