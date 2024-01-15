#include "stdafx.h"
#include "Tetris111.h"
#include <time.h>

CONST HBRUSH TETRIS_COLOR[] = {

	(HBRUSH)GetStockObject(GRAY_BRUSH), // Ĭ����ɫ ��ɫ
	CreateSolidBrush(RGB(255,255,0)),// ��ɫ
	CreateSolidBrush(RGB(0,0,255)),	 // ��ɫ
	CreateSolidBrush(RGB(0,191,255)),	// ǳ��
	CreateSolidBrush(RGB(0,139,69)),  // ��ɫ
	CreateSolidBrush(RGB(0,205,102)),  // ǳ��
	CreateSolidBrush(RGB(255,0,0)),  // ��ɫ
	CreateSolidBrush(RGB(148,0,211))   // ��ɫ

};
HBRUSH getHbrush(int i)
{
	return TETRIS_COLOR[i];
}

Tetris111 tetrisLine(1, 0, 4, 1, 4, 2, 4, 3, 4); // ��ֱ��
Tetris111 tetrisRect(-1, 0, 4, 0, 5, 1, 4, 1, 5);// ������
Tetris111 tetrisL(1, 0, 4, 1, 4, 2, 4, 2, 5);// L��
Tetris111 tetrisRL(1, 0, 5, 1, 5, 2, 5, 2, 4);// ��L��
Tetris111 tetrisZ(2, 0, 3, 0, 4, 1, 4, 1, 5);// Z��
Tetris111 tetrisRZ(2, 0, 5, 0, 4, 1, 4, 1, 3);// ��Z��
Tetris111 tetrisT(2, 0, 4, 1, 3, 1, 4, 1, 5);// T����

CONST Tetris111 DEFAULT_TETRIS[] =
{
	tetrisLine,
	tetrisRect,
	tetrisL,
	tetrisRL,
	tetrisZ,
	tetrisRZ,
	tetrisT
};

static long iSrand = 0;

long getRandom(long limit)
{
	srand((long)time(NULL) + (iSrand++));     //ÿ��ִ�����Ӳ�ͬ�����ɲ�ͬ�������
	return rand() % (limit + 1);
}

Tetris111::~Tetris111()
{
}

Tetris111::Tetris111() :color(0){}

Tetris111::Tetris111(int key, ...):color(0)
{
	va_list arg_ptr;
	va_start(arg_ptr, key);
	for (int i = 0; i < 4; i++)
	{
		positions[i].x = va_arg(arg_ptr, BYTE);
		positions[i].y = va_arg(arg_ptr, BYTE);
	}
	this->key = key;
	va_end(arg_ptr);
}


Tetris111& Tetris111::operator=(const Tetris111& tetris)
{
	for (int i = 0; i < 4; i++)
	{
		positions[i] = tetris.positions[i];
	}
	color = tetris.color;
	key = tetris.key;
	return *this;
}

void Tetris111::changeX(int step)
{
	for (int i = 0; i < 4; i++)
	{
		positions[i].x += step;
	}
}

void Tetris111::changeY(int step)
{
	for (int i = 0; i < 4; i++)
	{
		positions[i].y += step;
	}
}

void Tetris111::getMaxMin(int& minX, int& maxX, int& minY, int& maxY)
{
	minX = maxX = positions[0].x;
	minY = maxY = positions[0].y;
	for (int i = 1; i < 4; i++)
	{
		if (minX > positions[i].x)
		{
			minX = positions[i].x;
		}
		if (maxX < positions[i].x)
		{
			maxX = positions[i].x;
		}
		if (minY > positions[i].y)
		{
			minY = positions[i].y;
		}
		if (maxY < positions[i].y)
		{
			maxY = positions[i].y;
		}
	}
}

void Tetris111::rotate(int min_x, int max_x, int min_y, int max_y)
{
	if (key < 0)
	{
		return;
	}
	int maxX = min_x, minX = max_x, maxY = min_y, minY = max_y;
	// TODO Խ�紦��
	for (int i = 0; i < 4; i++)
	{
		BYTE x = positions[i].x, y = positions[i].y;
		positions[i].x = y - positions[key].y + positions[key].x;
		positions[i].y = positions[key].x + positions[key].y - x;
	}
	getMaxMin(minX, maxX, minY, maxY);
	// Խ�����
	if (maxX > max_x)
	{
		changeX(max_x - maxX);
	}
	if (minX < min_x)
	{
		changeX(min_x - minX);
	}
	if (maxY > max_y)
	{
		changeY(max_y - maxY);
	}
	if (minY < min_y)
	{
		changeY(min_y - minY);
	}
}

void Tetris111::rotate()
{
	rotate(0, 19, 0, 9);
}
void Tetris111::down()
{
	changeX(1);

}

void Tetris111::left()
{
	changeY(-1);

}

void Tetris111::right()
{
	changeY(1);

}

void Tetris111::random()
{
	Tetris111 tetris = DEFAULT_TETRIS[getRandom(6)];
	for (int i = 0; i < 4; i++)
	{
		positions[i] = tetris.positions[i];
	}
	key = tetris.key;
	UINT times = getRandom(3);
	// �����ת0-3��
	for (int i = 0; i < times; i++)
	{
		rotate(0, 3, 3, 6); // ��ʼ������
	}
	color = getRandom(6) + 1;
}

int Tetris111::getLeftBottom()
{
	int index = 0;
	for (int i = 1; i < 4; i++)
	{
		if (positions[i].y < positions[index].y)
		{
			index = i;
		}
		else if (positions[i].y == positions[index].y && positions[i].x > positions[index].x)
		{
			index = i;
		}
	}
	return index;
}