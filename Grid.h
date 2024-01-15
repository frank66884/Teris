#pragma once
#ifndef GRIS_CLASS
#define GRID_CLASS

#include"Tetris111.h"
#include<vector>
#include <Windows.h>
using std::vector;
class Tetris111;

typedef vector<BYTE> ROWSPAN;
typedef vector<ROWSPAN> GRID;
class Grid
{
public:
	GRID grid;

	Grid();
	Grid(int row, int col);
	~Grid();
	ROWSPAN& operator [](int index);
	Grid& operator=(const Grid&);
	BOOL isExist(Tetris111 tetris);
	void addCurTetrisToGrid(Tetris111 tetris);
	int clearLine();
	int lineStatus(int);
	void init(int, int);
};
#endif // !GRIS_CLASS
