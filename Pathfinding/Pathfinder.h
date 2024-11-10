#ifndef QUANTVERSO_PATHFINDER_H
#define QUANTVERSO_PATHFINDER_H

//--------------------------------------------------------------------------------------------------

#include "Clock.h"
#include "Map.h"

//--------------------------------------------------------------------------------------------------

class Pathfinder
{
public:
	static int visited;		  ///< Quantidade de nós visitados
	static Clock clock;		  ///< Usado para cronometrar tempo da busca
	static float timeElapsed; ///< Tempo decorrido da busca

	Pathfinder(Map*& map);
	virtual ~Pathfinder();
	virtual Node* Search() = 0;

protected:
	Map* const map; ///< Ponteiro para o mapa de busca

	void GetPath(Node*& current) const;
};

//--------------------------------------------------------------------------------------------------

#endif
