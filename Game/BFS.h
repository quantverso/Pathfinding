#ifndef QUANTVERSO_BFS_H
#define QUANTVERSO_BFS_H

//--------------------------------------------------------------------------------------------------

#include "Pathfinder.h"
#include <queue>

//--------------------------------------------------------------------------------------------------

class BFS : public Pathfinder
{
public:
	BFS(Map* map);
	const Node* Search();

private:
	std::queue<Node*> queue; ///< FIFO
};

//--------------------------------------------------------------------------------------------------

#endif
