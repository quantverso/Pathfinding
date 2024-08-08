#include "BFS.h"
#include <vector>

// ---------------------------------------------------------------------------------------------------------------------

BFS::BFS(Map* map) : PathFinder(map)
{
	// Insere nó raiz na fila
	queue.push(getRoot());
}

// ---------------------------------------------------------------------------------------------------------------------

BFS::~BFS()
{	
}

// ---------------------------------------------------------------------------------------------------------------------

Map::Node* BFS::Search()
{	
	if (!queue.empty())
	{
		auto current = queue.front();

		// Retorna o nó objetivo se a busca for bem sucedida
		if (current == getTarget())
		{
			// Percorre o caminho de volta até o nó raiz
			getPath(current);

			return current;
		}

		queue.pop();

		// Acessa os nós adjacentes
		std::vector<Map::Node*> adjacent{ getAdjacent(current)};
		
		// Visita cada nó adjacente, atualiza e coloca na fila
		for (const auto& adj : adjacent)
		{
			adj->status = Map::Status::Visited;
			adj->distance = current->distance + 1;
			adj->parent = current;

			queue.push(adj);

			visitedNodes++;
		}

		// Desenha o progresso da busca (somente nós visitados)
		map->Draw();

		// Marca o nó atual como explorado
		current->status = Map::Status::Explored;

		return nullptr;
	}

	// Retorna o nó raiz caso a busca falhe
	return getRoot();
}

// ---------------------------------------------------------------------------------------------------------------------
