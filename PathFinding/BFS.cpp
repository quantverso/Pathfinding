#include "BFS.h"
#include <vector>

// ---------------------------------------------------------------------------------------------------------------------

BFS::BFS(Map* map) : PathFinder(map)
{
	// Insere n� raiz na fila
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

		// Retorna o n� objetivo se a busca for bem sucedida
		if (current == getTarget())
		{
			// Percorre o caminho de volta at� o n� raiz
			getPath(current);

			return current;
		}

		queue.pop();

		// Acessa os n�s adjacentes
		std::vector<Map::Node*> adjacent{ getAdjacent(current)};
		
		// Visita cada n� adjacente, atualiza e coloca na fila
		for (const auto& adj : adjacent)
		{
			adj->status = Map::Status::Visited;
			adj->distance = current->distance + 1;
			adj->parent = current;

			queue.push(adj);

			visitedNodes++;
		}

		// Desenha o progresso da busca (somente n�s visitados)
		map->Draw();

		// Marca o n� atual como explorado
		current->status = Map::Status::Explored;

		return nullptr;
	}

	// Retorna o n� raiz caso a busca falhe
	return getRoot();
}

// ---------------------------------------------------------------------------------------------------------------------
