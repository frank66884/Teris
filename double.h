#pragma once
#include"point.h"
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#define DOUBLEGRIDNUMX 20//˫��ģʽ������
#define DOUBLEGRIDNUMY 30
#define DOUBLEBEGINX1 20//˫��ģʽ����
#define DOUBLEBEGINX2 860
#define DOUBLEBEGINY 0
#define DOUBLEBEGINY1 100 //�������Ͻ���ľ���
#define DOUBLEBLOCKSIZE 20
#define EXTRA 5
//using namespace std;

extern int doublenowscore1;
extern int doublenowscore2;//��ǰ����1��2
extern int doublenextindex1;//��һ������
extern int doublenowcolor1;
extern int doublenextcolor1;
extern int doublenowindex1;//��ǰ����
extern int doublenextindex2;//��һ������
extern int doublenowcolor2;
extern int doublenextcolor2;
extern int doublenowindex2;//��ǰ����
extern int doublespeed;//�ٶ�
extern int doublegridnum1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//������
extern int doublegridcolor1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//���ӷ�����ɫ
extern int doublegridnum2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//������
extern int doublegridcolor2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];//���ӷ�����ɫ
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
//��˫��ģʽ������Ѿ���¼�ķ���
void doubledrawgrid();
//˫��ģʽ���������ʼ��
void doubleinitialize();
//˫��ģʽ�ж��Ƿ�����ƶ�
BOOL doubleremovable(int x0, int y0, block_direct removedirect,int index,const int flag0);
//�ж�˫��ģʽ�Ƿ����ת��
BOOL doubleturnto(int x0, int y0,int index,const int flag0);
//˫��ģʽ���λ��
void doublemark(int x0, int y0, const int flag0);
//˫��ģʽ�жϽ���
int doubleend();
//˫��ģʽ��һ������
void doublenextblock(const int flag0);
//˫��ģʽ����
void doublemode();
//˫��ģʽ�ж������������
void doubledown(const int flag0);
//˫��ģʽ������
void doubledrawblock(int x, int y, int index, int color, const int flag0);
//���Ʒ����ƶ�������3��Ϸ����������2���ҷ��鲻���ƶ�������0�󷽿鲻���ƶ�������1�ҷ��鲻���ƶ�
int doublemove();
//˫��ģʽ��ǰ����
int doublenowblock(const int flag0);