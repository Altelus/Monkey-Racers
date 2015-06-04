#include "PathNode.h"

PathNode::PathNode( float xPos, float yPos)
{
	parent = nullptr;

	f = g = h = 0;

	x = xPos;
	y = yPos;

	isWalkable = true;

	inOpenList = false;
	inClosedList = false;

	isLowestPath = false;
}

bool PathNode::operator==( const PathNode& other ) const
{
	return (this->x == other.x && this->y == other.y);
}

bool PathNode::operator!=( const PathNode& other ) const
{
	return !operator==(other);
}

float PathNode::calculateF(PathNode* end)
{
	g = calculateG(parent);
	h = calculateH(end);

	return f = g + h;
}

float PathNode::calculateG(PathNode* parent)
{
	float result = parent->g;
	return result += (x == parent->x || y == parent->y) ? 10 : 14;
}

float PathNode::calculateH(PathNode* end)
{
	return (abs(end->x - x) + abs(end->y - y)) * 10;
}
