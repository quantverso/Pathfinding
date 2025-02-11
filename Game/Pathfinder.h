#ifndef QUANTVERSO_PATHFINDER_H
#define QUANTVERSO_PATHFINDER_H

//--------------------------------------------------------------------------------------------------

#include "Clock.h"
#include "Map.h"
#include <vector>

//--------------------------------------------------------------------------------------------------

class Pathfinder
{
public:
	inline static int	visited;	 ///< Quantidade de nós visitados
	inline static Clock clock;		 ///< Usado para cronometrar tempo da busca
	inline static float timeElapsed; ///< Tempo decorrido da busca

	Pathfinder(Map*& map);
	virtual ~Pathfinder();
	virtual const Node* Search() = 0;

protected:
	Map* const		   map;		 ///< Ponteiro para o mapa de busca
	std::vector<Node*> adjacent; ///< Vetor para guardar nós adjacentes

	void GetPath(Node*& current) const;
};

//--------------------------------------------------------------------------------------------------

#endif
