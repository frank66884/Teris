#include"double.h"

int doublenowscore1;
int doublenowscore2;
int doublenextindex1;
int doublenowcolor1;
int doublenextcolor1;
int doublenowindex1;
int doublenextindex2;
int doublenowcolor2;
int doublenextcolor2;
int doublenowindex2;
int doublespeed;
int doublegridnum1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];
int doublegridcolor1[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];
int doublegridnum2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];
int doublegridcolor2[DOUBLEGRIDNUMX + EXTRA][DOUBLEGRIDNUMY + EXTRA];
int x11;
int y11;
int nowspeed1 ;
int k1;
block_direct nowdirect1;
block_direct nextdirect1 ;
int x22;
int y22 ;
int nowspeed2 ;
int k2;
int winflag;
block_direct nowdirect2;
block_direct nextdirect2 ;
//queue<int> B1;
//queue<int> B2;

void doubledrawgrid()//˫��ģʽ������Ѿ���¼�ķ���
{
	for (int i = EXTRA;i < DOUBLEGRIDNUMX + EXTRA;i++)
	{
		for (int j = EXTRA;j < DOUBLEGRIDNUMY + EXTRA;j++)
		{
			if (doublegridnum1[i][j])
			{
				setfillcolor(doublegridcolor1[i][j]);
				int x1 = (i - EXTRA) * 20 + DOUBLEBEGINX1;
				int y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
				int x2 = (i + 1 - EXTRA) * 20 + DOUBLEBEGINX1;
				int y2 = (j + 1 - EXTRA) * 20 + DOUBLEBEGINY1;
				fillrectangle(x1, y1, x2, y2);
			}
			if (doublegridnum2[i][j])
			{
				setfillcolor(doublegridcolor2[i][j]);
				int x1 = (i - EXTRA) * 20 + DOUBLEBEGINX2;
				int y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
				int x2 = (i + 1 - EXTRA) * 20 + DOUBLEBEGINX2;
				int y2 = (j + 1 - EXTRA) * 20 + DOUBLEBEGINY1;
				fillrectangle(x1, y1, x2, y2);
			}
			setlinecolor(6);
			int x1 = (i - EXTRA) * 20 + DOUBLEBEGINX1;
			int y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
			int x2 = (i + 1 - EXTRA) * 20 + DOUBLEBEGINX1;
			int y2 = (j + 1 - EXTRA) * 20 + DOUBLEBEGINY1;
			rectangle(x1, y1, x2, y2);
			x1 = (i - EXTRA) * 20 + DOUBLEBEGINX2;
			y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
			x2 = (i + 1 - EXTRA) * 20 + DOUBLEBEGINX2;
			y2 = (j + 1 - EXTRA) * 20 + DOUBLEBEGINY1;
			rectangle(x1, y1, x2, y2);
		}
	}
}
void doubleinitialize()//˫��ģʽ���������ʼ��
{
	doublenowscore1 = 0;
	doublenowscore2 = 0;
	doublenextindex1=-1;
	doublenowcolor1=-1;
	doublenextcolor1=-1;
	doublenowindex1=-1;
	doublenextindex2=-1;
	doublenowcolor2=-1;
	doublenextcolor2=-1;
	doublenowindex2=-1;
	doublespeed = 100;//˫��ģʽ�½��ٶȣ�����ԽС�ٶ�Խ�죬��ʼֵ��100��������ڵ�60
	x11 = DOUBLEBEGINX1 + DOUBLEBLOCKSIZE*9;
	y11 = DOUBLEBEGINY;
	nowspeed1 = doublespeed;
	k1 = 0;
	nowdirect1 = BLOCK_UP;
	nextdirect1 = BLOCK_RIGHT;
	x22 = DOUBLEBEGINX2 + DOUBLEBLOCKSIZE*9;
	y22= DOUBLEBEGINY;
	nowspeed2 = doublespeed;
	k2 = 0;
	nowdirect2 = BLOCK_UP;
	nextdirect2 = BLOCK_RIGHT;
	//��ʼ��ͼƬ
	for (int i = EXTRA;i < DOUBLEGRIDNUMX + EXTRA;i++)
	{
		for (int j = EXTRA;j < DOUBLEGRIDNUMY + EXTRA;j++)
		{
			doublegridcolor1[i][j] = MYWHITE;
			doublegridnum1[i][j] = 0;
			doublegridcolor2[i][j] = MYWHITE;
			doublegridnum2[i][j] = 0;
			setlinecolor(doublegridcolor1[i][j]);
			int x1 = (i - EXTRA) * 20 + DOUBLEBEGINX1;
			int y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
			int x2 = (i+1 - EXTRA) * 20 + DOUBLEBEGINX1;
			int y2 = (j+1 - EXTRA) * 20 + DOUBLEBEGINY1;
			//ʹ�øú�����һ�����Σ������õ�ǰ�Ļ��ʻ������������õ�ǰ��ˢ������䡣
			rectangle(x1,y1,x2,y2);
			x1 = (i - EXTRA) * 20 + DOUBLEBEGINX2;
			y1 = (j - EXTRA) * 20 + DOUBLEBEGINY1;
			x2 = (i + 1 - EXTRA) * 20 + DOUBLEBEGINX2;
			y2 = (j + 1 - EXTRA) * 20 + DOUBLEBEGINY1;
			rectangle(x1, y1, x2, y2);
		}
	}
	for (int i = 0;i < DOUBLEGRIDNUMX + EXTRA;i++)//��ʼ��Ϊ����ɫ
	{
		for (int j = 0;j < DOUBLEGRIDNUMY + EXTRA;j++)
		{
			doublegridcolor1[i][j] = MYWHITE;
			doublegridnum1[i][j] = 0;
			doublegridcolor2[i][j] = MYWHITE;
			doublegridnum2[i][j] = 0;
		}
	}
}
BOOL doubleremovable(int x0, int y0, block_direct removedirect,int index,const int flag0)//˫��ģʽ�ж��Ƿ�����ƶ�
{
	int x;
	if (flag0 == 0)
	{
		x = (x0 - DOUBLEBEGINX1) / DOUBLEBLOCKSIZE;
	}
	else {
		x = (x0 - DOUBLEBEGINX2) / DOUBLEBLOCKSIZE;
	}
	int y = (y0 - DOUBLEBEGINY1) / DOUBLEBLOCKSIZE;
	int flag = 1;
	if (removedirect == BLOCK_LEFT)
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (flag0 == 0)
				{
					if (block[index][i][j] == 1 && (x + i == 0 || doublegridnum1[x + i - 1 + EXTRA][y + j + EXTRA] == 1))
					{
						flag = 0;
					}
				}
				else if(flag0==1)
				{
					if (block[index][i][j] == 1 && (x + i == 0 || doublegridnum2[x + i - 1 + EXTRA][y + j + EXTRA] == 1))
					{
						flag = 0;
					}
				}
				
			}
		}
	}
	else if (removedirect == BLOCK_RIGHT)
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (flag0 == 0) 
				{
					if (block[index][i][j] == 1 && (x + i >= DOUBLEGRIDNUMX-1 || doublegridnum1[x + i + 1 + EXTRA][y + j + EXTRA] == 1))
					{
						flag = 0;
					}
				}
				else if (flag0 == 1)
				{
					if (block[index][i][j] == 1 && (x + i >= DOUBLEGRIDNUMX - 1 || doublegridnum2[x + i + 1 + EXTRA][y + j + EXTRA] == 1))
					{
						flag = 0;
					}
				}
				
			}
		}
	}
	else if (removedirect == BLOCK_DOWN)
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (flag0 == 0)
				{
					if (block[index][i][j] == 1 && (y + j + 1 >= DOUBLEGRIDNUMY || doublegridnum1[x + i + EXTRA][y + j + 1 + EXTRA] == 1))
					{
						return 0;
					}
				}
				else if (flag0 == 1)
				{
					if (block[index][i][j] == 1 && (y + j + 1 >= DOUBLEGRIDNUMY || doublegridnum2[x + i + EXTRA][y + j + 1 + EXTRA] == 1))
					{
						return 0;
					}
				}
				
			}
		}
	}
	return flag;
}
BOOL doubleturnto(int x0, int y0,int index,const int flag0)//˫��ģʽ�ж��Ƿ����ת��
{
	int x ;
	if (flag0 == 0)
	{
		x = (x0 - DOUBLEBEGINX1) / DOUBLEBLOCKSIZE;
	}
	else {
		x = (x0 - DOUBLEBEGINX2) / DOUBLEBLOCKSIZE;
	}
	int y = (y0 - DOUBLEBEGINY1) / DOUBLEBLOCKSIZE;
	int flag = 1;
	if (!doubleremovable(x0, y0, BLOCK_DOWN,index,flag0))
	{
		return 0;
	}
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (flag0 == 0)
			{
				if (block[(index + 1) % 4 + index / 4 * 4][i][j] == 1 && (x + i < 0 || x + i >= DOUBLEGRIDNUMX || y + j < 0 || y + j >= DOUBLEGRIDNUMY || doublegridnum1[x + i + EXTRA][y + j + EXTRA] == 1))
				{
					flag = 0;
				}
			}
			else if (flag0 == 1)
			{
				if (block[(index + 1) % 4 + index / 4 * 4][i][j] == 1 && (x + i < 0 || x + i >= DOUBLEGRIDNUMX || y + j < 0 || y + j >= DOUBLEGRIDNUMY || doublegridnum2[x + i + EXTRA][y + j + EXTRA] == 1))
				{
					flag = 0;
				}
			}
			
		}
	}
	return flag;
}
void doublemark(int x0, int y0,const int flag0)//˫��ģʽ���λ��
{
	int x;
	if (flag0 == 0)
	{
		x = (x0 - DOUBLEBEGINX1) / DOUBLEBLOCKSIZE;
	}
	else {
		x = (x0 - DOUBLEBEGINX2) / DOUBLEBLOCKSIZE;
	}
	int y = (y0 - DOUBLEBEGINY1) / DOUBLEBLOCKSIZE;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (flag0==0&&block[doublenowindex1][i][j] == 1)
			{
				doublegridnum1[x + i + EXTRA][y + j + EXTRA] = 1;
				doublegridcolor1[x + i + EXTRA][y + j + EXTRA] = blockcolor[doublenowcolor1];
			}
			else if (flag0 == 1 && block[doublenowindex2][i][j] == 1)
			{
				doublegridnum2[x + i + EXTRA][y + j + EXTRA] = 1;
				doublegridcolor2[x + i + EXTRA][y + j + EXTRA] = blockcolor[doublenowcolor2];
			}
		}
	}
}
BOOL doubleend()//˫��ģʽ����ʱ���ж�
{
	int flag1 = doubleremovable(x11, y11, BLOCK_DOWN, doublenowindex1, 0);
	int flag2 = doubleremovable(x22, y22, BLOCK_DOWN, doublenowindex2, 1);
	//IMAGE victory, failure;
	//loadimage(&victory, "VICTORY.jpg", 350, 200);
	//loadimage(&failure, "FAILURE.jpg", 350, 200);
	if (flag1==0)
	{
		//putimage(40, 260, &failure);
		//putimage(890, 260, &victory);
		winflag = 2;
		return TRUE;
	}
	else if (flag2 == 0)
	{
		//putimage(40, 260, &victory);
		//putimage(890, 260, &failure);
		winflag = 1;
		return TRUE;
	}
	return FALSE;
}
void doublenextblock(const int flag0)//˫��ģʽ��һ������
{
	if (flag0 == 0)
	{
		srand((unsigned)time(NULL));
		doublenextindex1 = rand() % 28;
		setfillcolor(blockcolor[doublenextcolor1]);
		for (int i = 0;i <= 4;i++)
		{
			for (int j = 0;j <= 4;j++)
			{
				if (block[doublenextindex1][i][j] == 1 && (360 + j * 30) >= 100)
				{
					int x1 = 465 + i * DOUBLEBLOCKSIZE;
					int y1 = 160 + j * DOUBLEBLOCKSIZE;
					int x2 = 465 + (i + 1) * DOUBLEBLOCKSIZE;
					int y2 = 160 + (j + 1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
		}
	}
	else if (flag0 == 1)
	{
		srand((unsigned)time(NULL));
		doublenextindex2 = rand() % 28;
		setfillcolor(blockcolor[doublenextcolor2]);
		for (int i = 0;i <= 4;i++)
		{
			for (int j = 0;j <= 4;j++)
			{
				if (block[doublenextindex2][i][j] == 1 && (360 + j * 30) >= 100)
				{
					int x1 = 735 + i * DOUBLEBLOCKSIZE;
					int y1 = 160 + j * DOUBLEBLOCKSIZE;
					int x2 = 735 + (i + 1) * DOUBLEBLOCKSIZE;
					int y2 = 160 + (j + 1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
		}
	}
	else if (flag0 == 2)
	{
		srand((unsigned)time(NULL));
		doublenextindex1 = rand() % 28;
		setfillcolor(blockcolor[doublenextcolor1]);
		for (int i = 0;i <= 4;i++)
		{
			for (int j = 0;j <= 4;j++)
			{
				if (block[doublenextindex1][i][j] == 1 && (360 + j * 30) >= 100)
				{
					int x1 = 465 + i * DOUBLEBLOCKSIZE;
					int y1 = 160 + j * DOUBLEBLOCKSIZE;
					int x2 = 465 + (i + 1) * DOUBLEBLOCKSIZE;
					int y2 = 160 + (j + 1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
		}
		srand((unsigned)time(NULL));
		doublenextindex2 = rand() % 28;
		setfillcolor(blockcolor[doublenextcolor2]);
		for (int i = 0;i <= 4;i++)
		{
			for (int j = 0;j <= 4;j++)
			{
				if (block[doublenextindex2][i][j] == 1 && (360 + j * 30) >= 100)
				{
					int x1 = 735 + i * DOUBLEBLOCKSIZE;
					int y1 = 160 + j * DOUBLEBLOCKSIZE;
					int x2 = 735 + (i + 1) * DOUBLEBLOCKSIZE;
					int y2 = 160 + (j + 1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
		}
	}
}
void doublemode()//˫��ģʽҳ�����
{
	//����
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "˫��ģʽ");
	IMAGE background2;
	loadimage(&background2, "dbg2.png", 1280, 720);
	putimage(0, 0, &background2);
	//��
	settextstyle(20, 0, FONT);
	settextcolor(RGB(0, 0, 0));
	outtextxy(20, 20, "��ǰ����");
	outtextxy(1280 - 20 - textwidth("��ǰ����"), 20, "��ǰ����");
	settextcolor(RGB(0, 0, 0));
	settextstyle(55, 0,"����" );
	outtextxy(440, 120, "��һ��");
	outtextxy(1280 - 440 - textwidth("��һ��"), 120, "��һ��");
	//����ͼ�꣬ʹ�õ�ͼλ����
	IMAGE integral11, integral12, integral21, integral22;
	loadimage(&integral21, "integral21.png", 50, 40);
	loadimage(&integral22, "integral22.png", 50, 40);
	putimage(30, 45, &integral22, SRCAND);
	putimage(30, 45, &integral21, SRCPAINT);
	putimage(1280 - 30 - 30 - 20, 45, &integral22, SRCAND);//��������
	putimage(1280 - 30 - 30 - 20, 45, &integral21, SRCPAINT);//��������
	//˫��ģʽ�Ʒ�
	settextstyle(80, 0, FONT);
	settextcolor(RGB(0, 0, 0));
	char str1[30];
	//A���
	sprintf_s(str1, "%d", doublenowscore2);//�����ָ�ʽ�����Ϊ�ַ���
	int tx = 1280 - 180 + (1280 - 100 - (1280 - 180)) / 2 - textwidth(str1) / 2;
	int ty = 50 - textheight(str1) / 2;
	outtextxy(tx + 10, ty + 10, str1);
	//B���
	sprintf_s(str1, "%d", doublenowscore1);//�����ָ�ʽ�����Ϊ�ַ���
	tx = 140 - textwidth(str1) / 2;
	ty = 50 - textheight(str1) / 2;
	outtextxy(tx - 10, ty + 10, str1);
	settextcolor(RGB(0, 0, 0));
	settextstyle(40, 0,"����");
	outtextxy(195, 15, "����:A");
	outtextxy(195, 50, "����:D");
	outtextxy(350, 15, "����:S");
	outtextxy(350, 50, "��ת:W");
	outtextxy(1280 - 195 - textwidth("����:��"), 15, "����:��");
	outtextxy(1280 - 195 - textwidth("����:��"), 50, "����:��");
	outtextxy(1280 - 350 - textwidth("����:��"), 15, "����:��");
	outtextxy(1280 - 350 - textwidth("��ת:��"), 50, "��ת:��");
	outtextxy(640 - textwidth("��ͣ:�ո�") / 2, 15, "��ͣ:�ո�");
	outtextxy(640 - textwidth("����:Esc") / 2, 50, "����:Esc");
}
void doubledown(const int flag0)//ʵ���Ƿ��������е��ж�
{
	for (int i = DOUBLEGRIDNUMY + EXTRA - 1;i >= EXTRA;i--)
	{
		int flag = 1;
		for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
		{
			if (flag0==0&&doublegridnum1[j][i] != 1)
			{
				flag = 0;
			}
			if (flag0 == 1 && doublegridnum2[j][i] != 1)//��λ���п�ȱ����� 
			{
				flag = 0;
			}
		}
		if (flag0==0&&flag == 1)//���A�����һ��ȫ����Ϊ���飬����мӷֺ�������һ��
		{
			doublenowscore1 += 10;
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				doublegridnum1[j][i] = 0;//���Ϊ0��ʾ���λ��û�з��飬1��ʾ���λ���з���
				doublegridcolor1[j][i] = MYWHITE;
				FlushBatchDraw();//ִ��û����ɵĻ�������
				doublemode();//˫��ģʽA��ҳɼ�����
				doubledrawgrid();//˫��ģʽ�����¼
			}
			for (int y = i;y >= EXTRA;y--)
			{
				for (int x = EXTRA;x < DOUBLEGRIDNUMX + EXTRA;x++)
				{
					doublegridnum1[x][y] = doublegridnum1[x][y - 1];//�ݹ�ʵ����ɫ��䣿
					doublegridnum1[x][y - 1] = 0;
					doublegridcolor1[x][y] = doublegridcolor1[x][y - 1];
					doublegridcolor1[x][y - 1] = RED;
					if (doublegridnum1)
					{
						setfillcolor(doublegridcolor1[x][y]);
						fillrectangle((x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX1, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX1 + DOUBLEBLOCKSIZE, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
					}
				}
			}
			for (int y = EXTRA;y <DOUBLEGRIDNUMY+EXTRA-1;y++)
			{
				for (int x = EXTRA;x < DOUBLEGRIDNUMX + EXTRA;x++)
				{
					doublegridnum2[x][y] = doublegridnum2[x][y + 1];
					doublegridcolor2[x][y] = doublegridcolor2[x][y + 1];
					if (doublegridnum2[x][y])
					{
						setfillcolor(doublegridcolor2[x][y]);
						fillrectangle((x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2 + DOUBLEBLOCKSIZE, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
					}
				}
			}
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				srand((unsigned)time(NULL));
				doublegridnum2[j][DOUBLEGRIDNUMY+EXTRA-1] = rand()%2;
				doublegridcolor2[j][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			int flag1 = 1;
			int flag2 = 1;
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				if (doublegridnum2[j][DOUBLEGRIDNUMY + EXTRA - 1]==0)
				{
					flag1=0;
				}
				if (doublegridnum2[j][DOUBLEGRIDNUMY + EXTRA - 1] == 1)
				{
					flag2 = 0;
				}
			}
			srand((unsigned)time(NULL));
			if (flag1 == 1)
			{
				int p = rand() % (DOUBLEGRIDNUMX + EXTRA);
				doublegridnum2[p][DOUBLEGRIDNUMY + EXTRA - 1] = 0;
				doublegridcolor2[p][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			if (flag2 == 1)
			{
				int p = rand() % (DOUBLEGRIDNUMX + EXTRA);
				doublegridnum2[p][DOUBLEGRIDNUMY + EXTRA - 1] = 1;
				doublegridcolor2[p][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				if (doublegridnum2[j][DOUBLEGRIDNUMY + EXTRA - 1] == 1)
				{
					doublegridcolor2[j][0] = RGB(112, 128, 114);
					setfillcolor(doublegridcolor2[j][0]);
					fillrectangle((j - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2, (DOUBLEGRIDNUMY + EXTRA - 1 - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (j - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2 + DOUBLEBLOCKSIZE, (DOUBLEGRIDNUMY + EXTRA - 1 - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
				}
				else {
					doublegridcolor2[j][DOUBLEGRIDNUMY + EXTRA - 1] = MYWHITE;
				}
			}
			i++;
		}
		if (flag0 == 1 && flag == 1)//�����к�������»���
		{
			doublenowscore2 += 10;
			FlushBatchDraw();
			doublemode();
			doubledrawgrid();
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				doublegridnum2[j][i] = 0;
				doublegridcolor2[j][i] = MYWHITE;
				FlushBatchDraw();
				doublemode();
				doubledrawgrid();
			}
			for (int y = i;y >= EXTRA;y--)
			{
				for (int x = EXTRA;x < DOUBLEGRIDNUMX + EXTRA;x++)
				{
					doublegridnum2[x][y] = doublegridnum2[x][y - 1];
					doublegridnum2[x][y - 1] = 0;
					doublegridcolor2[x][y] = doublegridcolor2[x][y - 1];//����������滻��Ȼ�����ݵ��滻
					doublegridcolor2[x][y - 1] = MYWHITE;
					if (doublegridnum2[x][y])
					{
						setfillcolor(doublegridcolor2[x][y]);
						fillrectangle((x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2 + DOUBLEBLOCKSIZE, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
					}
				}
			}
			for (int y = EXTRA;y < DOUBLEGRIDNUMY + EXTRA - 1;y++)
			{
				for (int x = EXTRA;x < DOUBLEGRIDNUMX + EXTRA;x++)
				{
					doublegridnum1[x][y] = doublegridnum1[x][y + 1];
					doublegridcolor1[x][y] = doublegridcolor1[x][y + 1];
					if (doublegridnum1[x][y])
					{
						setfillcolor(doublegridcolor1[x][y]);
						fillrectangle((x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX1, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (x - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX1 + DOUBLEBLOCKSIZE, (y - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
					}
				}
			}
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				srand((unsigned)time(NULL));
				doublegridnum1[j][DOUBLEGRIDNUMY + EXTRA - 1] = rand() % 2;
				doublegridcolor2[j][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			int flag1 = 1;
			int flag2 = 1;
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				if (doublegridnum1[j][DOUBLEGRIDNUMY + EXTRA - 1] == 0)
				{
					flag1 = 0;
				}
				if (doublegridnum1[j][DOUBLEGRIDNUMY + EXTRA - 1] == 1)
				{
					flag2 = 0;
				}
			}
			srand((unsigned)time(NULL));
			if (flag1 == 1)
			{
				int p = rand() % (DOUBLEGRIDNUMX + EXTRA);
				doublegridnum1[p][DOUBLEGRIDNUMY + EXTRA - 1] = 0;
				doublegridcolor1[p][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			if (flag2 == 1)
			{
				int p = rand() % (DOUBLEGRIDNUMX + EXTRA);
				doublegridnum1[p][DOUBLEGRIDNUMY + EXTRA - 1] = 1;
				doublegridcolor1[p][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
			}
			for (int j = EXTRA;j < DOUBLEGRIDNUMX + EXTRA;j++)
			{
				if (doublegridnum1[j][DOUBLEGRIDNUMY + EXTRA - 1] == 1)
				{
					doublegridcolor1[j][DOUBLEGRIDNUMY + EXTRA - 1] = RGB(112, 128, 114);
					setfillcolor(doublegridcolor1[j][0]);
					fillrectangle((j - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2, (DOUBLEGRIDNUMY + EXTRA - 1 - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1, (j - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINX2 + DOUBLEBLOCKSIZE, (DOUBLEGRIDNUMY + EXTRA - 1 - EXTRA) * DOUBLEBLOCKSIZE + DOUBLEBEGINY1 + DOUBLEBLOCKSIZE);
				}
				else {
					doublegridcolor1[j][DOUBLEGRIDNUMY + EXTRA - 1] = MYWHITE;
				}
			}
			i++;
		}
	}
}
void doubledrawblock(int x, int y, int index, int color,const int flag0)//˫��ģʽ�½������з�������
{
	setfillcolor(blockcolor[color]);
	for (int i = 0;i <= 4;i++)
	{
		for (int j = 0;j <= 4;j++)
		{
			if (flag0 == 0)
			{
				if (block[index][i][j] == 1 && (y + j * 20) >= 100)
				{
					int x1 = x + i * DOUBLEBLOCKSIZE;
					int y1 = y + j * DOUBLEBLOCKSIZE;
					int x2= x + (i+1) * DOUBLEBLOCKSIZE;
					int y2 = y + (j+1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
			else if (flag0 == 1)
			{
				if (block[index][i][j] == 1 && (y + j * 20) >= 100)
				{
					int x1 = x + i * DOUBLEBLOCKSIZE;
					int y1 = y + j * DOUBLEBLOCKSIZE;
					int x2 = x + (i + 1) * DOUBLEBLOCKSIZE;
					int y2 = y + (j + 1) * DOUBLEBLOCKSIZE;
					fillrectangle(x1, y1, x2, y2);
				}
			}
			
		}
	}
}
int doublemove()//˫��ģʽ�ƶ��ķ�ʽ�任
{
	int flag = 0;
	while (true)
	{
		if (doubleend() == TRUE)
		{
			return 3;
		};
		if (flag != 0)
		{
			FlushBatchDraw();
			doublemode();
			doubledrawgrid();
		}
		flag = 1;
		doubledrawblock(465, 160 , doublenextindex1, doublenextcolor1, 0);
		doubledrawblock(735, 160 , doublenextindex2, doublenextcolor2, 1);
		if (GetAsyncKeyState(VK_UP))
		{
			nextdirect2 = BLOCK_UP;
			if (doubleturnto(x22, y22 + k2,doublenowindex2,1) == 1)
			{
				nowdirect2 = nextdirect2;
				doublenowindex2 = (doublenowindex2 + 1) % 4 + doublenowindex2 / 4 * 4;
				k2 -= DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			nextdirect2 = BLOCK_LEFT;
			if (doubleremovable(x22, y22 + k2, nextdirect2,doublenowindex2,1))
			{
				nowdirect2 = nextdirect2;
				x22 = x22 - DOUBLEBLOCKSIZE;
				k2 -= DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			nextdirect2 = BLOCK_RIGHT;
			if (doubleremovable(x22, y22 + k2, nextdirect2, doublenowindex2, 1))
			{
				nowdirect2 = nextdirect2;
				x22 = x22 + DOUBLEBLOCKSIZE;
				k2 -= DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			nextdirect2 = BLOCK_DOWN;
			if (doubleremovable(x22, y22 + k2 + 20, nextdirect2, doublenowindex2, 1))
			{
				nowdirect2 = nextdirect2;
				k2+=DOUBLEBLOCKSIZE;
			}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			HWND hwnd = GetHWnd();
			if (!MessageBox(hwnd, "��Ϸ�Ѿ���ͣ\n�������ȷ��", "��ʾ", MB_OK))
			{
				printf("pause error");
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			return  3;
		}
		if (GetAsyncKeyState('A') || GetAsyncKeyState('a') )
		{
			nextdirect1 = BLOCK_LEFT;
			if (doubleremovable(x11, y11 + k1, nextdirect1, doublenowindex1, 0))
			{
				nowdirect1 = nextdirect1;
				x11 = x11 - DOUBLEBLOCKSIZE;
				k1 -= DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState('W') || GetAsyncKeyState('w') )
		{
			nextdirect1 = BLOCK_UP;
			if (doubleturnto(x11, y11 + k1, doublenowindex1, 0) == 1)
			{
				nowdirect1 = nextdirect1;
				doublenowindex1 = (doublenowindex1 + 1) % 4 + doublenowindex1 / 4 * 4;
				k1 -= DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState('S') || GetAsyncKeyState('s'))
		{
			nextdirect1 = BLOCK_DOWN;
			if (doubleremovable(x11, y11 + k1 + 30, nextdirect1, doublenowindex1, 0))
			{
				nowdirect1 = nextdirect1;
				k1+=DOUBLEBLOCKSIZE;
			}
		}
		else if (GetAsyncKeyState('D') || GetAsyncKeyState('d') )
		{
			nextdirect1 = BLOCK_RIGHT;
			if (doubleremovable(x11, y11 + k1, nextdirect1, doublenowindex1, 0))
			{
				nowdirect1 = nextdirect1;
				x11 = x11 + DOUBLEBLOCKSIZE;
				k1 -= DOUBLEBLOCKSIZE;
			}
		}
		k1 += DOUBLEBLOCKSIZE;
		doubledrawblock(x11, y11 + k1, doublenowindex1, doublenowcolor1, 0);
		k2 += DOUBLEBLOCKSIZE;
		doubledrawblock(x22, y22 + k2, doublenowindex2, doublenowcolor2, 1);
		Sleep(nowspeed1);
		nowspeed1 = doublespeed;
		nowspeed2 = doublespeed;
		if (!doubleremovable(x11, y11 + k1, BLOCK_DOWN, doublenowindex1, 0) && !doubleremovable(x22, y22 + k2, BLOCK_DOWN, doublenowindex2, 1))
		{
			doublemark(x11, y11 + k1, 0);
			x11 = DOUBLEBEGINX1+DOUBLEBLOCKSIZE*9;
			y11 = DOUBLEBEGINY;
			nowspeed1 = doublespeed;
			k1 = 0;
			nowdirect1 = BLOCK_UP;
			nextdirect1 = BLOCK_RIGHT;
			doublemark(x22, y22 + k2, 1);
			x22 = DOUBLEBEGINX2 + DOUBLEBLOCKSIZE *9;
			y22 = DOUBLEBEGINY;
			nowspeed2 = doublespeed;
			k2 = 0;
			nowdirect2 = BLOCK_UP;
			nextdirect2 = BLOCK_RIGHT;
			doubledown(0);
			doubledown(1);
			return 2;
		}
		if (!doubleremovable(x11, y11 + k1, BLOCK_DOWN,doublenowindex1,0))
		{
			doublemark(x11, y11 + k1,0);
			x11 = DOUBLEBEGINX1 + DOUBLEBLOCKSIZE *9;
			y11 = DOUBLEBEGINY;
			nowspeed1 = doublespeed;
			k1 = 0;
			nowdirect1 = BLOCK_UP;
			nextdirect1 = BLOCK_RIGHT;
			doubledown(0);
			return 0;
		}
		if (!doubleremovable(x22, y22 + k2, BLOCK_DOWN, doublenowindex2, 1))
		{
			doublemark(x22, y22 + k2, 1);
			x22 = DOUBLEBEGINX2 + DOUBLEBLOCKSIZE *9;
			y22= DOUBLEBEGINY;
			nowspeed2 = doublespeed;
			k2 = 0;
			nowdirect2 = BLOCK_UP;
			nextdirect2 = BLOCK_RIGHT;
			doubledown(1);
			return 1;
		}
	}
}
int doublenowblock(const int flag0)//˫��ģʽ��ǰ����
{
	FlushBatchDraw();
	if (flag0 == 0)
	{
		doublenowindex1 = doublenextindex1;
		srand((unsigned)time(NULL));
		doublenowcolor1 = doublenextcolor1;
		doublenextcolor1 = rand() % COLORNUM;
		doublemode();
		doublenextblock(flag0);
		doubledrawgrid();
	}
	else if (flag0 == 1)
	{
		doublenowindex2 = doublenextindex2;
		srand((unsigned)time(NULL));
		doublenowcolor2 = doublenextcolor2;
		doublenextcolor2 = rand() % COLORNUM;
		doublemode();
		doublenextblock(flag0);
		doubledrawgrid();
	}
	else if (flag0 == 2)
	{
		doublenowindex1 = doublenextindex1;
		srand((unsigned)time(NULL));
		doublenowcolor1 = doublenextcolor1;
		doublenextcolor1 = rand() % COLORNUM;
		doublenowindex2 = doublenextindex2;
		srand((unsigned)time(NULL));
		doublenowcolor2 = doublenextcolor2;
		doublenextcolor2 = rand() % COLORNUM;
		doublemode();
		doublenextblock(flag0);
		doubledrawgrid();
	}
	int flag = doublemove();
	if (flag == 0)
	{
		return 0;
	}
	else if(flag==1) {
		return 1;
	}
	else if (flag == 2)
	{
		return 2;
	}
	else if (flag == 3)
	{
		return 3;
	}
}