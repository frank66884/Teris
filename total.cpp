#include "total.h"
#include "Tetris.h"
#include <map>
void singlemodeoperate(bool flag)
{
	initializegrid();    //���
	if (flag == TRUE)//��ʼ�µ���ϷΪTRUE
	{
		srand((unsigned)time(NULL));    //�������������
		int z = rand() % 7;
		nowcolor = z;
		nextcolor = z;
		nextblock();
		Sleep(100);
		memset(gridnum, 0, sizeof(gridnum));
	}
	else {
		loadfile();//������Ϸ�Ļ��Ƚ��д浵�Ķ�ȡ
		clearnextblock(690, 276, 840, 426);
		drawblock(725, 260, nextindex, nextcolor);
		drawblock(beginx+(continuex-EXTRA)*BLOCKSIZE, beginy+continuey*BLOCKSIZE, nowindex, nowcolor);
		Sleep(100);
		move(continuex-EXTRA- (GRIDNUMX - EXTRA) / 2,continuey);
	}
	BeginBatchDraw();//��ʼ������ͼ
	while (true)
	{
		FlushBatchDraw();//��ͼ�������ֹ��˸
		if (nowblock() == TRUE)
		{
			break;
		}
	}
	EndBatchDraw();//����������ͼ
}
void doublemodeoperate()
{
	doubleinitialize();
	srand((unsigned)time(NULL));
	int z = rand() % 7;
	doublenowcolor1 = z;
	doublenextcolor1 = z;
	srand((unsigned)time(NULL));
	z = rand() % 7;
	doublenowcolor2 = z;
	doublenextcolor2 = z;
	doublenextblock(2);
	Sleep(100);
	memset(doublegridnum1, 0, sizeof(doublegridnum1));
	memset(doublegridnum2, 0, sizeof(doublegridnum2));
	BeginBatchDraw();
	HWND hwnd = GetHWnd();
	MessageBox(hwnd, "��Ϸ��ʼ!!!\n", "��ʾ", MB_OK) == IDOK;
	int flag=2;
	while (true)//˫��ģʽһֱ��ѭ��
	{
		FlushBatchDraw();
		int flag1 = doublenowblock(flag);
		if (flag1 == 1)
		{
			flag = 1;
		}
		else if(flag1==0) {
			flag = 0;
		}
		else if (flag1 == 2)
		{
			flag = 2;
		}
		else if (flag1 == 3)
		{
			break;
		}
	}
	EndBatchDraw();
}
void listoperate() 
{
	readrank();
	ExMessage msg;
	while (true)
	{
		if(peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN && msg.x > 0 && msg.y > 0 && msg.x < 55 && msg.y < 55)
		{
			mciSendString("close rank.mp3", NULL, 0, NULL);
			return;
		}
	}
}
void maininterface()//��������ͼ��
{
	
	initgraph(938, 896, SHOWCONSOLE);	    // ������ͼ���ڣ���СΪ 938*896 ����
	setbkmode(TRANSPARENT);//͸����
	
	Bgm();

	Backgound();
	button(290, 200, 280, 102, "���˶���");//�޸ķ���λ��and����,��һ����x�������ң�y���������ǵڶ���
	button(290, 380, 280, 102, "˫�˳���");
	button(290, 560, 280, 102, "��������");
}
void buttonhit()//��ť������
{
	int flag = 1;//flagΪ0ʱΪmute��Ϊ1ʱΪsound
	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE))//��һ��ҳ��������ť�������
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 200 && msg.x < 570 && msg.y < 302)//����ģʽ���
			{
				BOOL flag1 = newcontinue();//�ж��Ƿ�ʼ�µ���Ϸ����ʼ�µ���Ϸ��ΪTRUE��������ϷΪFALSE
				if (flag1 == true) {
					Tetris game(20, 10, 263, 133, 36);//���ݱ��������ز������ƶ�
					game.play();
				}
				else {
					Tetris game(20, 10, 263, 133, 36);//���ݱ��������ز������ƶ�
					game.init();
					game.huanyuan();
					game.playcon();
				}
			}        
             //˫��ģʽ���
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 380 && msg.x < 570 && msg.y < 482)
			{
				//����˫��ģʽ���ر�֮ǰ�ǵı�������
				mciSendString("close kn.mp3", NULL, 0, NULL);
				//����
				mciSendString("open double.mp3", NULL, 0, NULL);
				mciSendString("play double.mp3 repeat", NULL, 0, NULL);
				initgraph(1280, 720, SHOWCONSOLE);
				setbkmode(TRANSPARENT);
				setbkcolor(WHITE);
				clearcliprgn();
				doublemode();
				doublemodeoperate();
				mciSendString("close double.mp3", NULL, 0, NULL);
				mciSendString("open end.mp3", NULL, 0, NULL);
				mciSendString("play end.mp3", NULL, 0, NULL);
				IMAGE victory, failure;
				loadimage(&victory, "V1.png", 350, 200);
				loadimage(&failure, "F1.png", 350, 200);
				if (winflag == 1)
				{
					doublemode();
					doubledrawgrid();
					putimage(40, 260, &victory);
					putimage(890, 260, &failure);
					HWND hwnd = GetHWnd();
					if (MessageBox(hwnd, "��Ϸ����!!!\n", "��ʾ", MB_OK) == IDOK)
					{
						mciSendString("close end.mp3", NULL, 0, NULL);
						return;
					}
				}
				else if (winflag == 2)
				{
					doublemode();
					doubledrawgrid();
					putimage(40, 260, &failure);
					putimage(890, 260, &victory);
					HWND hwnd = GetHWnd();
					if (MessageBox(hwnd, "��Ϸ����!!!\n", "��ʾ", MB_OK) == IDOK)
					{
						mciSendString("close end.mp3", NULL, 0, NULL);
						return;
					}
				}
				return;
			}
			//���а����
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 560 && msg.x < 570 && msg.y < 662)
			{
				//�������а�������ֵĹر�
				
				mciSendString("close kn.mp3", NULL, 0, NULL);
				mciSendString("open rank.mp3", NULL, 0, NULL);
				mciSendString("play rank.mp3", NULL, 0, NULL);
				initgraph(938, 896, SHOWCONSOLE);
				setbkmode(TRANSPARENT);
				setbkcolor(WHITE);
				clearcliprgn();
				list();                           //���а��ҳ�����
				listoperate();
				return;
			}
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 740 && msg.x < 570 && msg.y < 842) {

			}
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 0 && msg.y > 0 && msg.x < 40 && msg.y < 40 && flag == 1)
			{
				mciSendString("stop kn.mp3", NULL, 0, NULL);
				IMAGE mute;
				loadimage(&mute, "csoundn.png", 40, 40);
				putimage(0, 0, &mute);
				flag = 0;
			}
			//�����ر�״̬
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 0 && msg.y > 0 && msg.x < 40 && msg.y < 40 && flag == 0)
			{
				mciSendString("play kn.mp3 repeat", NULL, 0, NULL);
				IMAGE sound;
				loadimage(&sound, "soundn.png", 40, 40);
				putimage(0, 0, &sound);
				flag = 1;
			}
		}
	}
}