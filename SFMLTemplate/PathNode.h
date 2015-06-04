#ifndef _PATHNODE_H
#define _PATHNODE_H
#include "Vec2.h"
#include <math.h>

class PathNode
{
public:
	PathNode(float, float);
	bool operator==(const PathNode& other) const;
	bool operator!=(const PathNode& other) const;

	float calculateF(PathNode* end);
	float calculateG(PathNode* parent);
	float calculateH(PathNode* end);

	PathNode* parent;
	float x;
	float y;

	float f;
	float g;
	float h;

	bool isWalkable;

	bool inOpenList;
	bool inClosedList;

	bool isLowestPath;

};

#endif