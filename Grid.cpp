#include"stdafx.h"
#include "Grid.h"

Grid::Grid() {};

Grid::Grid(int row, int col)
{
	init(row, col);
};
VOID Grid::init(int row, int col) {
	grid.clear();
	for (int i = 0; i < row; i++) {
		ROWSPAN row(col);
		grid.push_back(row);
	}
}
Grid::~Grid(){};

ROWSPAN& Grid::operator[](int index)
{
	return grid[index];
	// TODO: �ڴ˴����� return ���
}

Grid& Grid::operator=(const Grid& row)
{
	// TODO: �ڴ˴����� return ���
	grid = row.grid;
	return *this;
}

BOOL Grid::isExist(Tetris111 tetris)
{
	for (int i = 0; i < 4; i++) {
		if (grid[tetris.positions[i].x][tetris.positions[i].y] > 0) {
			return true;
		}
	}
	return false;
}

void Grid::addCurTetrisToGrid(Tetris111 tetris)
{
	for (int i = 0; i < 4; i++) {
		grid[tetris.positions[i].x][tetris.positions[i].y];
	}
}

int Grid::clearLine()
{
	int  status, clearline = 0;
	ROWSPAN row(10);
	int size = grid.size();
	for (int i = size - 1; i >= 0; i--)
	{
		status = lineStatus(i);
		if (status == 0)
		{
			continue;
		}
		if (status == 1)
		{
			// ��
			grid.erase(grid.begin() + i); // ɾ����ǰ��
			grid.insert(grid.begin(), row);
			clearline++;
			i++; // ��Ȼ������
		}
		else
		{
			// ��
			break;
		}
	}
	return clearline;
}

int Grid::lineStatus(int i)
{
	ROWSPAN::iterator it = grid[i].begin();
	while (it < grid[i].end() - 1)
	{
		// ��������ֵһ��Ϊ0 һ�������㣬��һ���нڵ�һ���޽ڵ�
		if (!(*it * *(it + 1)) && *it != *(it + 1))
		{
			return 0;
		}
		// ����ֵ���
		if (it == grid[i].end() - 2)
		{
			// ���нڵ�
			if (*it > 0)
			{
				return 1;
			}
			// ���޽ڵ�
			return -1;
		}
		it++;
	}
}
