#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h "         
using namespace std;
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);//行，列，左侧边界，顶部边界，每个方块大小    //右边界，和顶部可以用方块大小计算

	void init();//初始化
	void play();//开始游戏
	void drawAlpha(int picture_x, int picture_y, IMAGE* picture);
	void Tetris::huanyuan();
	void playcon();
private:
	void keyEvent();
	void upadteWindow();
	//返回距离上一次调用该函数，间隔了多少时间（ms）
	//第一次调用该函数，返回0
	int getDelay();
	void drop();
	void clearLine();
	void applyCarton(int o);
	void moveLeftRight(int offset);
	void rotate(); //旋转
	void drawScore();    //绘制当前分数
	void checkOver();
	void saveScore();    //保存最高分
	void displayOver();    //更新游戏结束

	bool isPaused = false;
private:
	int delay;
	int update;//是否更新

	//0：空白，没有俄罗斯方块
	//5：是第5种俄罗斯方块
	vector<vector<int> > map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;
	IMAGE sound;
	IMAGE mute;
	IMAGE imgOver;
	IMAGE imgWin;


	Block* curBlock;
	Block* nextBlock; //预告方块
	Block* preBlock;  //预测下落方块

	Block bakBlock;   //当前方块降落过程中，用来备份上一个合法位置的
	Block BAKBLOCK;
	int score;    //当前分数
	int highestScore;
	int level;    //当前关卡
	int lineCount; //消除行数
	bool gameOver;   //游戏是否结束

};