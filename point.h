#pragma once
#include <graphics.h>
#include<mmsystem.h>//包含多媒体设备接口头文件
#include<stdio.h>
#include <graphics.h>	// 引用图形库头文件
#include <conio.h>
#include <easyx.h>
#include<mmsystem.h>//包含多媒体设备接口头文件
#include<time.h>
#include<iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <queue>
//#include <pthread.h>
#pragma comment(lib,"Winmm.lib")//加载静态库
//#pragma comment(lib,"pthreadVC2.lib")

//#define FONT "锐字工房云字库粗圆GBK"
#define FONT "黑体"
#define MYWHITE RGB(240, 248, 255);
#define COLORNUM 13
#define PINK RGB(255,192,203)
#define PURPLE RGB(128,0,128)
#define ORANGE RGB(255,165,0)
//#define EXTRA 5//未显示区的格子，额外的

#define KEYUP 72
#define KEYLEFT 75
#define KEYRIGHT 77
#define KEYDOWN 80
#define KEYSPACE 32
#define KEYEsc 27
#define KEYA 65
#define KEYW 87
#define KEYS 83
#define KEYD 68
#define KEYa 97
#define KEYw 119
#define KEYs 115
#define KEYd 100

//7种不同方块及其变形
extern int block[28][5][5];
extern int blockcolor[COLORNUM];//方块颜色
typedef enum//枚举方块方向
{
	BLOCK_LEFT,
	BLOCK_RIGHT,
	BLOCK_DOWN,
	BLOCK_UP
}block_direct;
typedef struct inf
{
	char name[30];
	int score;
}info;
//播放音乐
void Bgm();
//背景
void Backgound();
//主界面按钮
void button(int x, int y, int w, int h, const char* text);
//读取排行榜
int readrank();
//排行榜界面
void list();
void wait(int interval);