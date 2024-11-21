#include "BestFirst.h"
#include <vector>

// ---------------------------------------------------------------------------------------------------------------------

BestFirst::BestFirst(Map* map, bool cost) : Pathfinder(map)
{
	// Atribui a função heurística escolhida ao ponteiro
	h = cost ? &Heuristic1 : &Heuristic2;

	// Coloca o nó raiz na fila
	queue.push(map->root);
}

// ---------------------------------------------------------------------------------------------------------------------

const Node* BestFirst::Search()
{
	if (!queue.empty())
	{
		auto current = queue.top();

		// Retorna o nó objetivo se a busca for bem sucedida
		if (current == map->target)
		{
			// Percorre o caminho de volta até o nó raiz
			GetPath(current);

			return current;
		}

		queue.pop();

		// Acessa os nós adjacentes
		map->GetAdjacent(adjacent, current);

		// Visita cada nó adjacente, atualiza e coloca na fila
		for (const auto& adj : adjacent)
		{
			if (adj->Status() == Status::Empty || adj->Status() == Status::Target)
			{
				adj->Status(Status::Visited);
				adj->Distance(current->Distance() + 1);
				adj->Parent(current);

				queue.push(adj);

				visited++;
			}
		}

		// Marca o nó atual como explorado
		if (current->Status() != Status::Root)
			current->Status(Status::Explored);

		return nullptr;
	}

	// Retorna o nó raiz caso a busca falhe
	return map->root;
}

// ---------------------------------------------------------------------------------------------------------------------
