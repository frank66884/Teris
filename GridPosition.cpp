#include "stdafx.h"
#include "GridPosition.h"

GridPosition::GridPosition()
{
}

GridPosition::GridPosition(int x, int y):x(x),y(y)
{
}

GridPosition::~GridPosition()
{
}

GridPosition& GridPosition::operator=(const GridPosition& ps)
{
	// TODO: 在此处插入 return 语句
	x = ps.x;
	y = ps.y;
	return *this;
}
