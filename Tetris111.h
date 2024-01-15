#pragma once
#ifndef TETRIS_CLASS
#define TETRIS_CLASS

#include"GridPosition.h"
#include <wtypes.h>
class GridPosition;
class Tetris111 {
public:
	GridPosition positions[4];
	int color;
	int key;
	Tetris111();
	Tetris111(int key, ...);
	~Tetris111();
	Tetris111& operator=(const Tetris111& tetris);
	void changeX(int step);
	void changeY(int step);
	void getMaxMin(int& minX, int& maxX, int& minY, int& maxY);
	int getLeftBottom();
	void rotate(int min_x, int max_x, int min_y, int max_y);
	void rotate();
	void down();
	void left();
	void right();
	void random();
	friend HBRUSH getHbrush(int);
};
#endif // !TETRIS_CLASS
