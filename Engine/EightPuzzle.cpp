#include "EightPuzzle.h"
#include "Tile.h"
#include "BFS.h"
#include "Clock.h"
#include <random>

//--------------------------------------------------------------------------------------------------

EightPuzzle::EightPuzzle() :
	borderSize{ window.GetSize().width / 37 },
	tiles{ 9 },
	pathfinder{}
{
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Start()
{
	SetBackground("Resources/base.png");

	for (unsigned i{}; i < tiles.Size(); ++i)
	{
		tiles[i] = i;
		CreateObject<Tile>();
	}

	Shuffle();
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Update()
{
	// Embaralha o quebra-cabe�a
	if (Keyboard::KeyPressed(Keyboard::Num0))
		Shuffle();

	// Move com o mouse
	if (window.IsEventTriggered(Window::MouseButtonDown))
		tiles.Move(Tile::Clicked());

	// BFS
	if (!pathfinder)
	{
		if (Keyboard::KeyDown(Keyboard::Return))
			pathfinder = new BFS{ tiles };
	}
	else
	{
		pathfinder->Search(solution);
		delete pathfinder;
		pathfinder = nullptr;
	}

	// Monta o quebra-cabe�a
	if (!solution.empty())
	{
		static Clock clock;

		if (clock.Count() > 0.5f)
		{
			tiles = *solution.top();

			solution.pop();

			clock.Reset();
		}		
	}

	Scene::Update();
}

//--------------------------------------------------------------------------------------------------

void EightPuzzle::Shuffle()
{
	// Embaralha at� surgir uma configura��o sol�vel
	while (true)
	{
		// Gerador de n�meros aleat�rios
		static std::mt19937 mt{ std::random_device{}() };
		static std::uniform_int_distribution<> dist{ 0, 8 };

		for (size_t i{}; i < tiles.Size(); ++i)
		{
			int randomIndex{ dist(mt) };
			int temp{ tiles[i] };
			tiles[i] = int(tiles[randomIndex]);
			tiles[randomIndex] = temp;
		}

		// Contagem de invers�es
		unsigned inversions{};
		for (size_t i{}; i < tiles.Size() - 1; ++i)
		{
			for (size_t j{ i + 1 }; j < tiles.Size(); ++j)
			{
				if (tiles[i] != 0 && tiles[j] != 0 && tiles[i] > tiles[j]) // Conta as invers�es (ignorando o 0)
					++inversions;
			}
		}

		// Se as invers�es forem par, a configura��o � sol�vel
		if (inversions % 2 == 0)
			break;
	}
}

//--------------------------------------------------------------------------------------------------
