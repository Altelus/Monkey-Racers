#ifndef _ASTAR_PATHFINDER
#define _ASTAR_PATHFINDER

#include "PathNode.h"
#include <list>
#include <vector>
#include <algorithm>

class AStarPathFinder
{
public:
	//AStarPathFinder();
	AStarPathFinder(std::vector<std::vector<PathNode*>>grid);

	bool findPath(float startX, float startY, float endX, float endY);
	void clearPath();
	void printPath();

	std::vector<std::vector<PathNode*>> pathGrid;

private:

	PathNode* start;
	PathNode* end;
	PathNode* current;

	std::list<PathNode*> openList;
	std::list<PathNode*> closedList;
};

#endif