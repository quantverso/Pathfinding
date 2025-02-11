#include "Pathfinder.h"

//--------------------------------------------------------------------------------------------------

Pathfinder::Pathfinder(Map*& map) :
	map{ map }
{
	clock.Reset();
	map->Reset();
	visited = 0;
}

//--------------------------------------------------------------------------------------------------

Pathfinder::~Pathfinder()
{
	timeElapsed = clock.Count();
}

//--------------------------------------------------------------------------------------------------

void Pathfinder::GetPath(Node*& current) const
{
	auto step{ current };
	while ((step = step->Parent()) != map->root)
		step->Status(Status::Path);
}

//--------------------------------------------------------------------------------------------------
