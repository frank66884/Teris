#include"single.h"
#include "total.h"
#include "Block.h"
#include"Tetris.h"
#include <Windows.h>
#include <wingdi.h>
void color(int a)//�趨��ɫ�ĺ���
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);//������ɫ���ƺ���
}//�� ���� ���� ǳ��  ��  ����  ���� ǳ�� ��� ���� ����  ����� �Һ� ǳ��  �׻�  ��
int beginx;
int beginy;
int beginy1;
int nowscore;
int grade;
int nextindex;
int nowcolor;
int nextcolor;
int nowindex;
int speed;
int continuex;
int continuey;
int inferx;
int infery;
int bj;
int aj;
int gridnum[GRIDNUMX] [GRIDNUMY]; //������
int gridcolor[GRIDNUMX ][GRIDNUMY ];//������ɫ

//�����ʼ��
void initializegrid()
{
	nowscore = 0;
	grade = 1;
	nextindex = -1;
	nowcolor = -1;
	nextcolor = -1;
	nowindex = -1;
	speed = 500;
	beginx = 263;  
	beginy = -50;  //
	beginy1 = 133;
	for (int i = 0; i < GRIDNUMX ; i++)
	{
		for (int j = 0; j < GRIDNUMY ; j++)
		{
			gridcolor[i][j] = WHITE;
			gridnum[i][j] = 0;
			setfillcolor(gridcolor[i][j]);
			//��͸��������
			setcolor(WHITE);
			drawRectangle((i - 0) * BLOCKSIZE + beginx, (j - 0) * BLOCKSIZE + beginy1, (i - 0) * BLOCKSIZE + beginx + BLOCKSIZE, (j - 0) * BLOCKSIZE + beginy1 + BLOCKSIZE);
		}
	}
	for (int i = 0;i < GRIDNUMX + 0;i++)   //���Ǻ�����������һ�к�ʹ��
	{
		for (int j = 0;j < GRIDNUMY + 0;j++)
		{
			gridcolor[i][j] = WHITE;
			gridnum[i][j] = 0;
		}
	}
}
//��������
int rank1(int score)
{
	info tmp;
	FILE* fp;
	int flag = 0;
	color(10);
	printf("�������������Ĵ�����");
	fgets(tmp.name, 30, stdin);
	tmp.score = score;
	flag = fopen_s(&fp, "rank.txt", "a");
	if (flag != 0)
	{
		printf("cannot open rank.txt\n");
		system("pause");
		return -1;
	}
	fprintf(fp, "%s%d\n", tmp.name, tmp.score);
	fclose(fp);
	return 0;
}
void savedblock()
{
	for (int i = 0;i < 0 + GRIDNUMX; i++)
	{
		for (int j = 0;j < 0 + GRIDNUMY;j++)
		{
			if (gridnum[i][j])
			{
				setfillcolor(gridcolor[i][j]);
				fillrectangle((i - 0) * BLOCKSIZE + beginx, (j - 0) * BLOCKSIZE + beginy1, (i - 0 + 1) * BLOCKSIZE + beginx, (j - 0 + 1) * BLOCKSIZE + beginy1);
			}
		}
	}
}
void scoregrade(int x, int y, int w, int h, int flag)//�ӷ��������,��������������ʾ
{
	//���������Ч
	int add = 0;
	if (flag == 0)
	{
		add = nowscore;
	}
	else if (flag == 1)
	{
		mciSendString("close 118.mp3", NULL, 0, NULL);
		mciSendString("open 118.mp3", NULL, 0, NULL);
		mciSendString("setaudio 118.mp3 volume to 1000", NULL, 0, NULL);
		mciSendString("play 118.mp3", NULL, 0, NULL);
		add = grade;
	}
	setfillcolor(WHITE);               //��ָ���������Ϊָ����ɫ
	fillrectangle(x, y, x + w, y + h);
	char str[50];
	sprintf_s(str, "%d", add);//�����ָ�ʽ�����Ϊ�ַ���
	settextstyle(80, 0, FONT);
	int tx = x + w / 2 - textwidth(str) / 2;
	int ty = y + h / 2 - textheight(str) / 2;
	outtextxy(tx, ty, str);
}
void clearnextblock(int left, int top, int right, int bottom)//�������������һ��
{
	setfillcolor(WHITE);
	fillrectangle(left, top, right, bottom);//�������������Σ�������������
}
int removable(int x0, int y0, block_direct removedirect)       //���ƶ����ƶ���ʽ���жϵ�ǰ�����Ƿ�����ƶ�
{
	int x = (x0 - 30) / 36;
	int y = (y0 - 100) / 36;
	int flag = 1;
	if (removedirect == BLOCK_LEFT)//���ܹ������ƶ����ж�
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (block[nowindex][i][j] == 1 && (x + i == 0 || gridnum[x + i - 1 + 0][y + j + 0] == 1))
				{
					flag = 0;
				}
			}
		}
	}
	else if (removedirect == BLOCK_RIGHT)//���ܹ������ƶ����ж�
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (block[nowindex][i][j] == 1 && (x + i >= 10 || gridnum[x + i + 1 + 0][y + j + 0] == 1))
				{
					flag = 0;
				}
			}
		}
	}
	else if (removedirect == BLOCK_DOWN)//���ܹ������ƶ���ֱ�Ӿ͵��˽���
	{
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (block[nowindex][i][j] == 1 && (y + j + 1 >= 19 || gridnum[x + i + 0][y + j + 1 + 0] == 1))
				{
					return 0;
				}
			}
		}
	}
	return flag;
}
int turnto(int x0, int y0)//��״ת������
{
	int x = (x0 - 30) / 30;
	int y = (y0 - 100) / 30;
	int flag = 1;
	if (!removable(x0, y0, BLOCK_DOWN))
	{
		return 0;
	}
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (block[(nowindex + 1) % 4 + nowindex / 4 * 4][i][j] == 1 && (x + i < 0 || x + i >= 11 || y + j < 0 || y + j >= 19 || gridnum[x + i + 0][y + j + 0] == 1))
			{
				flag = 0;
			}
		}
	}
	return flag;
}
void mark(int x0, int y0)//���������λ�������
{
	int x = (x0 - 30) / 30;
	int y = (y0 - 100) / 30;
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (block[nowindex][i][j] == 1)
			{
				gridnum[x + i + 0][y + j + 0] = 1;
				gridcolor[x + i + 0][y + j + 0] = blockcolor[nowcolor];
			}
		}
	}
}
BOOL end(int x, int y)//�ж��Ƿ����
{
	HWND hwnd = GetHWnd();
	if (!removable(x, y, BLOCK_DOWN))//��������ֵΪ0�ͽ����������
	{
		mciSendString("open end1.mp3", NULL, 0, NULL);
		mciSendString("play end1.mp3 ", NULL, 0, NULL);
		int isok = MessageBox(hwnd, "�����Ƿ��¼�ɼ�\n���ȷ��������������\n���ȡ����������������¼\n��Ϸ�����¿�ʼ", "��Ϸ������", MB_OKCANCEL);
		if (isok == IDOK)
		{
			//rank1();//���е÷ֵ�����
			mciSendString("close end1.mp3", NULL, 0, NULL);
		}
		return TRUE;
	}
	return FALSE;
}

void down()
{
	bj = 0;
	for (int i = 19 + 0 - 1; i >= 0; i--)
	{
		int flag = 1;
		for (int j = 0; j < 11 + 0; j++)
		{
			if (gridnum[j][i] != 1)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			aj = 0;
			nowscore += 10;
			grade = nowscore / 80 + 1;            //ÿ80����һ��
			scoregrade(100, 15, 80, 70, 0);
			scoregrade(410, 170, 150, 100, 1);
			for (int j = 0; j < 11 + 0; j++)
			{
				gridnum[j][i] = 0;
				gridcolor[j][i] = WHITE;
				clearnextblock((j - 0) * 30 + beginx, (i - 0) * 30 + beginy1, (j - 0) * 30 + beginx + 30, (i - 0) * 30 + 30 + beginy1);
			}
			for (int y = i; y >= 0; y--)
			{
				for (int x = 0; x < 11 + 0; x++)
				{
					{
						gridnum[x][y] = gridnum[x][y - 1];
						gridnum[x][y - 1] = 0;
						gridcolor[x][y] = gridcolor[x][y - 1];
						gridcolor[x][y - 1] = WHITE;
						setfillcolor(gridcolor[x][y]);
						fillrectangle((x - 0) * 30 + beginx, (y - 0) * 30 + beginy1, (x - 0) * 30 + beginx + 30, (y - 0) * 30 + beginy1 + 30);
					}
				}
				i++;
			}
		}
	}
}
void drawblock(int x, int y, int index, int color)//����ʾ������
{
	setfillcolor(blockcolor[color]);//������ʵ��һ��5x5�ķ���
	for (int i = 0;i <= 4;i++)
	{
		for (int j = 0;j <= 4;j++)
		{
			if (block[index][i][j] == 1 && (y + j * 36) >= 100)
			{
				int x1 = x + i * 36;
				int y1 = y + j * 36;
				fillrectangle(x1, y1, x1 + 36, y1 + 36);//�����䷽��
			}
		}
	}
}
void archive(int x0, int y0)                                  //��Ϸ�浵
{
	int x = (x0 - beginx) / 30;
	int y = (y0 - beginy1) / 30;
	HWND hwnd = GetHWnd();
	FILE* p;
	if (!fopen_s(&p, "gamefile.txt", "r"))
	{
		fclose(p);
		if (MessageBox(hwnd, "�Ѿ�������Ϸ���ȣ��Ƿ�ɾ��", "��ʾ", MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
	}
	int flag = fopen_s(&p, "gamefile.txt", "w");
	if (flag != 0)
	{
		printf("cannot creat rank.txt\n");
		system("pause");
	}
	else {
		fprintf(p, "%d %d\n", nextindex, nextcolor);
		fprintf(p, "%d %d %d %d\n", x + 0, y + 0, nowindex, nowcolor);
		for (int i = 0;i < GRIDNUMX + 0;i++)
		{
			for (int j = 0;j < GRIDNUMY + 0;j++)
			{
				fprintf(p, "%d %d\n", gridnum[i][j], gridcolor[i][j]);
			}
		}
		fclose(p);
	}
}
void loadfile()    //���ش浵
{
	char buf[100];
	FILE* fp;
	int flag1 = fopen_s(&fp, "gamefile.txt", "rb");
	if (flag1 != 0)
	{
		printf("cannot open gamefile.txt\n");
		system("pause");
	}
	else {
		fscanf_s(fp, "%d %d", &nextindex, &nextcolor);
		fgets(buf, sizeof(buf), fp);//��ȡ����һ��
		fscanf_s(fp, "%d %d %d %d", &continuex, &continuey, &nowindex, &nowcolor);
		fgets(buf, sizeof(buf), fp);//��ȡ����һ��
		for (int i = 0;i < GRIDNUMX + 0;i++)
		{
			for (int j = 0;j < GRIDNUMY + 0;j++)
			{
				fscanf_s(fp, "%d %d", &gridnum[i][j], &gridcolor[i][j]);
				fgets(buf, sizeof(buf), fp);//��ȡ����һ��
			}
		}
		fclose(fp);
	}
	savedblock();
}
BOOL move(int x0, int y0)//�ƶ���ʽ
{
	int x = beginx+ x0 * BLOCKSIZE+(GRIDNUMX-EXTRA)/2*36;
	int y = beginy+ y0 * BLOCKSIZE;
	int nowspeed = speed / grade;
	int k = 0;
	block_direct nowdirect = BLOCK_UP;
	block_direct nextdirect = BLOCK_RIGHT;
	while (true)
	{
		if (end(x, y + k) == TRUE)//������Ѿ������˵Ļ��ͷ���TRUE
		{
			return TRUE;
		};
		FlushBatchDraw();//��Ȼ��Ϸ����
		for (int i = 0;i < 5;i++)
		{
			for (int j = 0;j < 5;j++)
			{
				if (block[nowindex][i][j] == 1 && (y + k + j * 36) >= 100)
				{
					clearnextblock(x + i * 36, y + j * 36 + k, x + 36 + i * 36, y + j * 36 + k + 36);
				}
			}
		}
		//��ȡ���̽�����ת
		if (_kbhit())
		{
			if (bj == 1)drawblock(inferx, infery, nowindex, 13);
			bj = 1;
			char key = _getch();//��һ�λ�ȡֵΪ0
			if (key == 0 || key == -32)
			{
				key = _getch();//�ڶ��λ�ȡ��ʵֵ
					if (key == KEYUP)
					{
						mciSendString("close 116.mp3", NULL, 0, NULL);
						mciSendString("open 116.mp3", NULL, 0, NULL);
						mciSendString("play 116.mp3", NULL, 0, NULL);
						//Sleep(70);//��ֹʱ�䲥�Ų�����
						//Sleep(70);//��ֹʱ�䲥�Ų�����
						nextdirect = BLOCK_UP;
						if (turnto(x, y + k) == 1)
						{
							nowdirect = nextdirect;
							nowindex = (nowindex + 1) % 4 + nowindex / 4 * 4;
							k -= 36;//k������36������һ����
						}
						int o = 0;
						while (true)
						{
							o = o+30;
							if (!removable(x, y + k + o, BLOCK_DOWN))
							{
								inferx = x;
								infery = y + k + o;
								break;
							}
						}
						drawblock(inferx, infery, nowindex, nowcolor);
					}
					else if (key == KEYLEFT)
					{
						mciSendString("close 116.mp3", NULL, 0, NULL);
						mciSendString("open 116.mp3", NULL, 0, NULL);
						mciSendString("play 116.mp3", NULL, 0, NULL);
						//Sleep(70);
						nextdirect = BLOCK_LEFT;
						if (removable(x, y + k, nextdirect))
						{
							nowdirect = nextdirect;
							x = x - 30;
							k -= 30;
						}
						int o = 0;
						while (true)
						{
							o = o+30;
							if (!removable(x, y + k + o, BLOCK_DOWN))
							{
								inferx = x;
								infery = y + k + o;
								break;
							}
						}
						drawblock(inferx, infery, nowindex, nowcolor);
					}
					else if (key == KEYRIGHT)
					{
						mciSendString("close 116.mp3", NULL, 0, NULL);
						mciSendString("open 116.mp3", NULL, 0, NULL);
						mciSendString("play 116.mp3", NULL, 0, NULL);
						//Sleep(70);
						nextdirect = BLOCK_RIGHT;
						if (removable(x, y + k, nextdirect))
						{
							nowdirect = nextdirect;
							x = x + 30;
							k -= 30;
						}
						int o = 0;
						while (true)
						{
							o = o+30;
							if (!removable(x, y + k + o, BLOCK_DOWN))
							{
								inferx = x;
								infery = y + k + o;
								break;
							}
						}
						drawblock(inferx, infery, nowindex, nowcolor);
					}
					else if (key == KEYDOWN)
					{
						mciSendString("close 116.mp3", NULL, 0, NULL);
						mciSendString("open 116.mp3", NULL, 0, NULL);
						mciSendString("play 116.mp3", NULL, 0, NULL);
						//Sleep(70);
						nextdirect = BLOCK_DOWN;
						if (removable(x, y + k + 30, nextdirect))
						{
							nowdirect = nextdirect;
							nowspeed = 30;//��������������ٶȱ���
						}
						int o = 0;
						while (true)//ʵ��Ԥ�⹦��
						{
							o = o+30;
							if (!removable(x, y + k + o, BLOCK_DOWN))
							{
								inferx = x;
								infery = y + k + o;
								break;
							}
						}
						drawblock(inferx, infery, nowindex, nowcolor);
					}		
			}
			else if (key == KEYSPACE)
			{
				HWND hwnd = GetHWnd();
				if (!MessageBox(hwnd, "��Ϸ�Ѿ���ͣ\n�������ȷ��", "��ʾ", MB_OK))
				{
					printf("error");
				}
			}
			//else if (key == KEYSPACE)
			//{
			//	drawblock(inferx, infery, nowindex, nowcolor);
			//	mark(inferx, infery);//��Ƿ�������λ��
			//	down();//�ж��Ƿ����м�������
			//	break;
			//}
			else if (key == KEYEsc)
			{
				HWND hwnd = GetHWnd();
				if (MessageBox(hwnd, "�Ƿ񱣴浱ǰ��Ϸ\n", "��ʾ", MB_OKCANCEL) == IDOK)
				{
					archive(x, y + k);
					main();
				}
				return TRUE;
			}
		}
		k += 36;
		drawblock(x, y + k, nowindex, nowcolor);
		wait(nowspeed);//�����½��ĺ���
		nowspeed = speed / grade;
		if (!removable(x, y + k, BLOCK_DOWN))
		{
			mark(x, y + k);//��Ƿ�������λ��
			down();//�ж��Ƿ����м�������
			break;
		}
	}
	return FALSE;
}
void nextblock()                                        //��һ������
{
	clearnextblock(690, 276, 840, 426);      //ԭ���Ǹ���һ���ɫ�����ӣ���סԭ��������
	srand((unsigned)time(NULL));
	nextindex = rand() % 28;//�������һ�ַ�����״
	drawblock(692, 280, nextindex, nextcolor);//������һ���������Ա�
}
BOOL nowblock()                 //�����·���              
{
	if(aj==1)drawblock(inferx, infery, nowindex, nowcolor);
	aj = 1;
	bj = 0;
	nowindex = nextindex;
	srand((unsigned)time(NULL));
	nowcolor = nextcolor;                       //����������һ�������
	nextcolor = rand() % 13;                 
	nextblock();                                           //������һ������
	drawblock(beginx, beginy, nowindex, nowcolor);        //��������
	if (move(0, 0) == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL newcontinue()
{
	BOOL flag = false;
	
	//����
	HWND hwnd = GetHWnd(); // ��ȡ���ھ��
	SetWindowText(hwnd, "����ģʽ");//�������Ͻ���ʾ
	mciSendString("close kn.mp3", NULL, 0, NULL);     //���뵥��ģʽ��ѡ����������Ч�����µ���Ч��
	mciSendString("open BGM.mp3", NULL, 0, NULL);
	mciSendString("play BGM.mp3 repeat", NULL, 0, NULL);
	int flag3 = 1;
	FILE* p;
	
	//�����޸����ַ���
	if (!fopen_s(&p, "gamefile.txt", "r"))//������Ϸ����ȡ��Ϸ��ʷ��¼,�鿴�ܲ��ܴ�gamefile����ĵ����ɹ��򷵻�ֵΪ0�����ɹ�����ֵΪ1
	{
		fclose(p);
		flag = TRUE;
		//����ͼƬ
		IMAGE background;
		loadimage(&background, "bg1.png", 938,896);
		putimage(0, 0, &background);
		IMAGE sound;
		loadimage(&sound, "soundn.png", 40, 40);
		putimage(0, 80, &sound);
		IMAGE backimage1, backimage2;
		loadimage(&backimage1, "back1.png", 40, 40);
		loadimage(&backimage2, "back2.png", 40, 40);
		putimage(0, 0, &backimage2, SRCAND);
		putimage(0, 0, &backimage1, SRCPAINT);
        button(360, 265, 200, 62, "������Ϸ");
		button(360, 450, 200, 62, "����Ϸ");
		ExMessage msg;
		bool flag2 = 1;
	}
	else                                                                        //���ܵĻ�������µ���Ϸ
	{
		IMAGE background;
		loadimage(&background, "bg1.png", 938, 896);
		putimage(0, 0, &background);
		IMAGE sound;
		loadimage(&sound, "soundn.png", 40, 40);
		putimage(0, 0, &sound);
		button(360, 450, 200, 62, "����Ϸ");
	}
	
	
	ExMessage msg;
	
	while (true)                                                      //��Ƶ���ģʽ����
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (flag == TRUE && msg.x > 360 && msg.x < 560 && msg.y>265 && msg.y < 327)//������Ϸ�ı��
			{
				setlinecolor(RGB(250,0,0));
				rectangle(360, 265, 560, 327);
				if (msg.message == WM_LBUTTONDOWN)
				{
					//mciSendString("close BGM.mp3", NULL, 0, NULL);
					return FALSE;
				}
			}
			else if (flag == TRUE && msg.x > 360 && msg.x < 560 && msg.y>450 && msg.y < 512)//����Ϸ
			{
				setlinecolor(RGB(250, 0, 0));
				rectangle(360, 450, 560, 512);
				if (msg.message == WM_LBUTTONDOWN)
				{
					//mciSendString("close s.mp3", NULL, 0, NULL);
					return TRUE;
				}
			}
			//�����ر�
			else if (flag == TRUE && msg.x > 0 && msg.y > 80 && msg.x < 40 && msg.y < 120 && flag3 == 1)
			{
				if(msg.message == WM_LBUTTONDOWN)
				{
					mciSendString("pause BGM.mp3", NULL, 0, NULL);
					IMAGE mute;
					loadimage(&mute, "csoundn.png", 40, 40);
					putimage(0, 80, &mute);
					flag3 = 0;
				}
			}
			//������
			else if (flag == TRUE && msg.x > 0 && msg.y > 80 && msg.x < 40 && msg.y <120 && flag3 == 0)
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					mciSendString("play BGM.mp3 repeat", NULL, 0, NULL);
					IMAGE sound;
					loadimage(&sound, "soundn.png", 40, 40);
					putimage(0, 80, &sound);
					flag3 = 1;
				}
			}
			else if (flag == TRUE && msg.x > 0 && msg.y > 0 && msg.x < 40 && msg.y < 40 )
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					mciSendString("close BGM.mp3", NULL, 0, NULL);                             //ʵ�ַ��غ���
					main();                  

				}
			}
			else if (flag == FALSE && msg.x > 360 && msg.x < 560 && msg.y>450 && msg.y < 512)
			{
				//setlinecolor(RGB(250, 250, 250));
				//rectangle(490, 580, 690, 642);                               //С����Ч

				if (msg.message == WM_LBUTTONDOWN)
				{
					return TRUE;
				}
			}
			else if (flag == TRUE) {
				setlinecolor(RGB(240, 248, 255));
				setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 5);
				rectangle(360, 265, 560, 327);
				rectangle(360, 450, 560, 512);
			}
			else if (flag == FALSE)
			{
				setlinecolor(RGB(240, 248, 255));
				rectangle(360, 425, 560, 458);
			}
		}
	}

}

void drawRectangle(int x1, int y1, int x2, int y2)
{
	line(x1, y1, x2, y1);  // �ϱ߿�
	line(x2, y1, x2, y2);  // �ұ߿�
	line(x1, y2, x2, y2);  // �±߿�
	line(x1, y1, x1, y2);  // ��߿�
}
