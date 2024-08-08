#include "PathFinder.h"
#include <iostream>

// ---------------------------------------------------------------------------------------------------------------------

PathFinder::PathFinder(Map*& map) : map(map)
{
	// Reseta nós alterados por busca
	Reset();

	// Inicializa o cronômetro da busca
	start = std::chrono::high_resolution_clock::now();

	// Informa que há uma busca em andamento
	map->Searching(true);
}

// ---------------------------------------------------------------------------------------------------------------------

PathFinder::~PathFinder()
{
	// Informa que a busca foi concluída
	map->Searching(false);

	// Calcula a tempo de duração da busca
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = end - start;

	std::cout << "Tempo da busca: "
			  << time.count()
			  << " segundos.\nVertices visitados: "
			  << visitedNodes << "\n"
			  << "Vertices ate a raiz: "
			  << pathSteps << "\n\n";
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<Map::Node*> PathFinder::getAdjacent(const Map::Node* currentNode)
{
	std::vector<Map::Node*> adjacentNodes;

	for (const auto& adj : adjacent)
	{
		// Calcula os índices do nó adjacente
		int x{ currentNode->column + adj.x};
		int y{ currentNode->row + adj.y};
		
		// Verifica se x e y pertencem aos índices da matriz
		// e se o nó referenciado tem estado Vazio ou Objetivo
		if ((x >= 0 && x < map->COLUMNS) && (y >= 0 && y < map->ROWS) &&
			(map->nodes[y][x].status == Map::Status::Empty ||
				map->nodes[y][x].status == Map::Status::Target))
		{
			adjacentNodes.push_back(&map->nodes[y][x]);
		}
	}
	return adjacentNodes;
}

// ---------------------------------------------------------------------------------------------------------------------

void PathFinder::getPath(Map::Node*& current)
{
	auto step = current;
	while (step != getRoot())
	{		
		step = step->parent;
		step->status = Map::Status::Path;
		pathSteps++;
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void PathFinder::Reset()
{
	for (int i{}; i < map->ROWS; ++i)
		for (int j{}; j < map->COLUMNS; ++j)
			if (Map::Status::Visited == map->nodes[i][j].status ||
				Map::Status::Explored == map->nodes[i][j].status ||
				Map::Status::Path == map->nodes[i][j].status)
			{
				map->nodes[i][j].status = {};
				map->nodes[i][j].distance = {};
				map->nodes[i][j].parent = {};
			}

	// Desenha o mapa com a busca resetada
	// Necessário 2 vezes para os sprites não ficarem piscando, não me pergunte o porquê \0/
	for (int i{}; i < 2; i++)
	{
		map->window->clear();
		map->Draw();
	}
}

// ---------------------------------------------------------------------------------------------------------------------
