#pragma once
#include"point.h"
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#define DOUBLEGRIDNUMX 20//双人模式网格数
#define DOUBLEGRIDNUMY 30
#define DOUBLEBEGINX1 20//双人模式网格
#define DOUBLEBEGINX2 860
#define DOUBLEBEGINY 0
#define DOUBLEBEGINY1 100 //网格与上界面的距离
#define DOUBLEBLOCKSIZE 20
#define EXTRA 5
//using namespace std;

extern int doublenowscore1;
extern int doublenowscore2;//当前分数1和2
extern int doublenextindex1;//下一个方块
extern int doublenowcolor1;
extern int doublenextcolor1;
extern int doublenowindex1;//当前方块
extern int doublenextindex2;//下一个方块
extern int doublenowcolor2;
extern int doublenextcolor2;
extern int doublenowindex2;//当前方块
extern int doublespeed;//速度
extern int doublegridnum1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//格子数
extern int doublegridcolor1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//格子方块颜色
extern int doublegridnum2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//格子数
extern int doublegridcolor2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//格子方块颜色
extern int x11;
extern int y11;
extern int nowspeed1;
extern int k1;
extern block_direct nowdirect1 ;
extern block_direct nextdirect1 ;
extern int x22;
extern int y22 ;
extern int nowspeed2 ;
extern int k2 ;
extern block_direct nowdirect2 ;
extern block_direct nextdirect2 ;
extern int winflag;
//画双人模式网格和已经纪录的方块
void doubledrawgrid();
//双人模式数据网格初始化
void doubleinitialize();
//双人模式判断是否可以移动
BOOL doubleremovable(int x0, int y0, block_direct removedirect,int index,const int flag0);
//判断双人模式是否可以转向
BOOL doubleturnto(int x0, int y0,int index,const int flag0);
//双人模式标记位置
void doublemark(int x0, int y0, const int flag0);
//双人模式判断结束
int doubleend();
//双人模式下一个方块
void doublenextblock(const int flag0);
//双人模式界面
void doublemode();
//双人模式判断下落和消除行
void doubledown(const int flag0);
//双人模式画方块
void doubledrawblock(int x, int y, int index, int color, const int flag0);
//控制方块移动，返回3游戏结束，返回2左右方块不能移动，返回0左方块不能移动，返回1右方块不能移动
int doublemove();
//双人模式当前方块
int doublenowblock(const int flag0);