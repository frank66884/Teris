#pragma once
#include <graphics.h>
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#include<stdio.h>
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <easyx.h>
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#include<time.h>
#include<iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <queue>
//#include <pthread.h>
#pragma comment(lib,"Winmm.lib")//���ؾ�̬��
//#pragma comment(lib,"pthreadVC2.lib")

//#define FONT "���ֹ������ֿ��ԲGBK"
#define FONT "����"
#define MYWHITE RGB(240, 248, 255);
#define COLORNUM 13
#define PINK RGB(255,192,203)
#define PURPLE RGB(128,0,128)
#define ORANGE RGB(255,165,0)
//#define EXTRA 5//δ��ʾ���ĸ��ӣ������

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

//7�ֲ�ͬ���鼰�����
extern int block[28][5][5];
extern int blockcolor[COLORNUM];//������ɫ
typedef enum//ö�ٷ��鷽��
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
//��������
void Bgm();
//����
void Backgound();
//�����水ť
void button(int x, int y, int w, int h, const char* text);
//��ȡ���а�
int readrank();
//���а����
void list();
void wait(int interval);