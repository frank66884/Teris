#pragma once
#include "point.h"
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#define GRIDNUMX 10               //���������      
#define GRIDNUMY 20               //���������
#define BLOCKSIZE 36

extern int beginx;
extern int beginy;
extern int beginy1;//�������Ͻ���ľ���
extern int nowscore;//��ǰ����
extern int grade;//�ȼ�
extern int nextindex;//��һ������
extern int nowcolor;
extern int nextcolor;
extern int nowindex;//��ǰ����
extern int speed;//�ٶ�
extern int gridnum[GRIDNUMX ][GRIDNUMY ];//������
extern int gridcolor[GRIDNUMX ][GRIDNUMY ];//���ӷ�����ɫ
extern int continuex;//������Ϸ����x��y
extern int continuey;

//��ʼ��
void initializegrid();
//���а�����
int rank1(int score);
//���ѱ���ķ���
void savedblock();
//��������,���������Լ���ʾ
void scoregrade(int x, int y, int w, int h, int flag);
//�����һ������
void clearnextblock(int left, int top, int right, int bottom);
//�жϵ�ǰ�����Ƿ�����ƶ�
int removable(int x0, int y0, block_direct removedirect);
//�жϵ�ǰ�����Ƿ����ת��
int turnto(int x0, int y0);
//��block�б�Ƿ������λ��
void mark(int x0, int y0);
//�ж���Ϸ����,��������true������������false
BOOL end(int x, int y);
//�ж��Ƿ������Լ�����������
void down();
//����ʾ������
void drawblock(int x, int y, int index, int color);
//�浵����
void archive(int x0, int y0);
//��������
void loadfile();
//�ƶ�����,���ػ��߽�������true,x0��y0���������߸���
BOOL move(int x0, int y0);
//��һ������
void nextblock();
//�����·��飬���ػ��߽�������true
BOOL nowblock();
//����Ϸ������Ϸ,trueΪ����Ϸ
BOOL newcontinue();

void drawRectangle(int x1, int y1, int x2, int y2);