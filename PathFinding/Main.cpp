#include "Engine.h"
#include "Entity.h"
#include "PathFinder.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirst.h"

// ---------------------------------------------------------------------------------------------------------------------

class PathFinding : public Entity
{
private:
	Map* map;
	PathFinder* pathfinder;

	void Update();
	
public:
	PathFinding();
	~PathFinding();
};

// ---------------------------------------------------------------------------------------------------------------------

PathFinding::PathFinding()
{
	map = new Map{ 10 };
	pathfinder = nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

PathFinding::~PathFinding()
{
	delete map;
}

// ---------------------------------------------------------------------------------------------------------------------

void PathFinding::Update()
{
	// Cria o objeto do algoritmo de busca selecionado
	if (!pathfinder)
	{
		if (pathfinder->getTarget())
		{
			// BFS
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				pathfinder = new BFS{ map };

			// A*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				pathfinder = new BestFirst{ map, true };

			// Busca gulosa
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				pathfinder = new BestFirst{ map, false };

			// DFS
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
				pathfinder = new DFS{ map };
		}
	}
	// Processa a busca do algoritmo selecionado
	else if (pathfinder->Search() || sf::Keyboard::isKeyPressed(sf::Keyboard::End))
	{
		// Destrói o objeto ao fim da busca
		delete pathfinder;
		pathfinder = nullptr;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

int main()
{	
	Engine* engine{ new Engine };
	int status{ engine->Run(new PathFinding) };
	delete engine;
	return status;
}

// ---------------------------------------------------------------------------------------------------------------------
