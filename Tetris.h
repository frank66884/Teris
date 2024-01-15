#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h "         
using namespace std;
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);//�У��У����߽磬�����߽磬ÿ�������С    //�ұ߽磬�Ͷ��������÷����С����

	void init();//��ʼ��
	void play();//��ʼ��Ϸ
	void drawAlpha(int picture_x, int picture_y, IMAGE* picture);
	void Tetris::huanyuan();
	void playcon();
private:
	void keyEvent();
	void upadteWindow();
	//���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms��
	//��һ�ε��øú���������0
	int getDelay();
	void drop();
	void clearLine();
	void applyCarton(int o);
	void moveLeftRight(int offset);
	void rotate(); //��ת
	void drawScore();    //���Ƶ�ǰ����
	void checkOver();
	void saveScore();    //������߷�
	void displayOver();    //������Ϸ����

	bool isPaused = false;
private:
	int delay;
	int update;//�Ƿ����

	//0���հף�û�ж���˹����
	//5���ǵ�5�ֶ���˹����
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
	Block* nextBlock; //Ԥ�淽��
	Block* preBlock;  //Ԥ�����䷽��

	Block bakBlock;   //��ǰ���齵������У�����������һ���Ϸ�λ�õ�
	Block BAKBLOCK;
	int score;    //��ǰ����
	int highestScore;
	int level;    //��ǰ�ؿ�
	int lineCount; //��������
	bool gameOver;   //��Ϸ�Ƿ����

};