#include "Tetris.h"
#include<time.h>
#include<stdlib.h>
#include "Block.h"
#include<conio.h>
#include<mmsystem.h>
#include<fstream>
#include<iostream>
#include "single.h"
#include "total.h"
#include <map>
#pragma comment(lib,"winmm.lib")

#define MAX_LEVEL 5
#define RECORDER_FILE "recorder.txt"
const int SPEED_NORMAL[MAX_LEVEL] = { 550,400,300,200,100 }; //ͨ���ı���ͨģʽ�Ĺؿ��������ٶȸı��Ѷ�
const int SPEED_QUICK = 5;  //ms
const int SPEED_LIGHT = 0;

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++)
	{
		vector<int> mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}

}

void Tetris::init()//��ʼ��
{
	mciSendString("close BGM.mp3 repeat", NULL, 0, NULL);
	mciSendString("open BGM.mp3 repeat", NULL, 0, NULL);
	mciSendString("play BGM.mp3 repeat", NULL, 0, NULL);
	delay = SPEED_NORMAL[0];//���÷�������ʱ����
	//�����������
	srand(time(NULL));

	//���ر���ͼƬ
	loadimage(&imgBg, "bg2.png");//���ر���ͼ

	loadimage(&sound, "sound.png", 40, 40);
	loadimage(&mute, "mute.png", 40, 40);

	loadimage(&imgWin, "win.png");
	loadimage(&imgOver, "over.png");

	//��ʼ����Ϸ���е�����
	char data[20][10];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	level = 1;
	lineCount = 0;

	//��ʼ����߷�
	ifstream file(RECORDER_FILE);
	if (!file.is_open())
	{
		cout << RECORDER_FILE << "��ʧ��" << endl;
		highestScore = 0;
	}
	else
	{
		file >> highestScore;        //���ļ�������
	}
	file.close();           //�ر��ļ�
	gameOver = false;
}

void Tetris::play()
{
	init();                   //�������
	nextBlock = new Block;    //����Ԥ�淽��
	curBlock = nextBlock;     //���µ�ǰ����
	nextBlock = new Block;    //

	int timer = 0;
	while (1)
	{
		preBlock = curBlock;
		//�����û�����
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			//��Ⱦ��Ϸ����
			update = true;
		}
		if (update)
		{
			update = false;
			//���»���
			upadteWindow();
			//��������
			clearLine();
		}
		if (gameOver)//�������
		{
			saveScore();
			//������Ϸ��������
			displayOver();
			system("pause");
			init();//���¿���
		}
	}
}

void Tetris::keyEvent()
{
	unsigned char ch;   //0..255
	bool rotateFlag = false;
	int dx = 0;            //����ƫ���������������ƶ�
	if (_kbhit())           //_kbhit�а������룬����ֵΪ��
	{
		ch = _getch();
		//������·���������Զ����������ַ�
		//��������Ϸ���������Ⱥ󷵻أ�224 72
		//��������·���������Ⱥ󷵻أ�224 80
		//�����������������Ⱥ󷵻أ�224 75 
		//��������ҷ���������Ⱥ󷵻أ�224 77
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case 72:    //��
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				rotateFlag = true;
				break;
			case 80:    //��
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				delay = 0;
				break;
			case 75:    //��
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				dx = -1;
				break;
			case 77:   //��
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				dx = 1;
				break;

			default:
				break;
			}
		}
		else if (ch == 32) // �ո��-��ͣ/����
		{
			isPaused = !isPaused; // �л���ͣ״̬

			if (isPaused)
			{
				HWND hwnd = GetHWnd();
				mciSendString("stop BGM.mp3", NULL, 0, NULL);         
				MessageBox(hwnd, "��Ϸ�Ѿ���ͣ\n�������ȷ��", "��ʾ", MB_OK);      

			}
			mciSendString("play BGM.mp3", NULL, 0, NULL);
		}
		else if (ch == 27)       //Esc��
		{
			isPaused = !isPaused; //  �л���ͣ״̬

			if (isPaused)
			{
				HWND hwnd = GetHWnd();
				mciSendString("stop BGM.mp3", NULL, 0, NULL);
				if (MessageBox(hwnd, "�Ƿ񱣴浱ǰ��Ϸ\n", "��ʾ", MB_OKCANCEL) != IDOK)
					//����û�ѡ���ˡ�ȷ������ť������� OK�����������������ʽ�Ľ��Ϊ true������Ϊ false
				{
					main();
				}
				else {
					FILE* p;
					if (!fopen_s(&p, "gamefile.txt", "r")) {
						fclose(p);
						if (MessageBox(hwnd, "�Ѿ�������Ϸ���ȣ��Ƿ�ɾ��", "��ʾ", MB_OKCANCEL) == IDCANCEL) {
							return;
						}
					}
					int flag = fopen_s(&p, "gamefile.txt", "w");
					if (flag != 0) {
						printf("�޷��洢��Ϸ����\n");
						system("pause");
					}
					else {
						fprintf(p, "%d %d\n", nextBlock->getBlockType(), nextBlock->getBlockcolor());
						fprintf(p, "%d %d %d %d %d %d %d %d %d %d\n", curBlock->getlocation(0).col, curBlock->getlocation(0).row, curBlock->getlocation(1).col, curBlock->getlocation(1).row, curBlock->getlocation(2).col, curBlock->getlocation(2).row, curBlock->getlocation(3).col, curBlock->getlocation(3).row, curBlock->getBlockType(), curBlock->getBlockcolor());
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < cols; j++) {                                                                                                                  
								fprintf(p, "%d\n", map[i][j]);
							}
						}
						fprintf(p, "%d %d %d %d\n", score, level, lineCount);
						fclose(p);
						main();
					}
				}
			}
		}
	}
	if (rotateFlag)//��ת����
	{
		//rotateFlag = false;
		rotate();
		update = true;
	}
	if (dx != 0)//ʵ�������ƶ�
	{
		moveLeftRight(dx);
		update = true;
	}
}

void Tetris::upadteWindow()    //������Ϸ����
{
    BeginBatchDraw();//������������ģʽ
	putimage(0, 0, &imgBg); //���Ʊ���ͼ
	
	for (int i = 0; i < GRIDNUMX; i++)
	{
		for (int j = 0; j < GRIDNUMY; j++)
		{
			//��͸��������
			setcolor(WHITE);
			setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);
			drawRectangle((i - 0) * BLOCKSIZE + 263, (j - 0) * BLOCKSIZE + 133, (i - 0) * BLOCKSIZE + 263 + BLOCKSIZE, (j - 0) * BLOCKSIZE + 133 + BLOCKSIZE);
		}
	}

	IMAGE** imgs = Block::getImages();//�Ѿ����䵽�ײ��̶��������Ⱦ                      
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}
	curBlock->draw(leftMargin, topMargin);                          
	nextBlock->draw(689, 150);//Ԥ����һ������

	drawScore();//���Ʒ���

	EndBatchDraw();
}

//��һ�ε��ã�����0
//���ؾ�����һ�ε��ã�����˶���ms
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;

	unsigned long long currentTime = GetTickCount();

	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
	return 0;
}

void Tetris::drop()
{
	//����λ�ã���¼��һ�ε�λ��
	bakBlock = *curBlock;  //�����˵Ⱥŵ�����
	curBlock->drop();

	if (!curBlock->blockInMap(map))//�½������У��ж�λ��������Ϸ�
	{
		//�̻�����
		bakBlock.solidify(map);
		delete curBlock;        //ɾ�����Ϸ�����
		curBlock = nextBlock;  //����ǰ��������Ϊ��һ������
		nextBlock = new Block; //��һ����������Ϊ�·���

		//�����Ϸ�Ƿ����
		checkOver();
	}
	delay = SPEED_NORMAL[level - 1];
}

void Tetris::clearLine()    //����ԭ��
{
	int lines = 0;

	int k = rows - 1;    //�洢���ݵ�����
	for (int i = rows - 1; i >= 0; i--)
	{
		//����i���Ƿ�����
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];    //��ɨ��ߴ洢
		}
		if (count < cols)    //�������У����˵���һ�У������У���ͣ����һ�У�����һ�εĸ���
		{
			k--;
		}
		else   //����
		{
			                                                      
			lines++;    //֪��һ�������˼���
			applyCarton(i); 
		}
	}
	if (lines > 0)
	{
		//����÷�
		int addScore[5] = { 10,30,60,80 ,100};
		score += addScore[lines - 1];

		mciSendString("play xiaochu1.mp3", 0, 0, 0); //���������е���Ч,���޸�xiaochu1
		update = true;

		level = (score + 99) / 100;//���ùؿ� ÿ100��һ��
		if (level > MAX_LEVEL)
		{
			gameOver = true;
		}
		lineCount += lines;
	}
}

void Tetris::applyCarton(int o)
{
	IMAGE xh1, xh2, xh3, xh4, xh5, xh6, xh7, xh8, xh9, xh10, xh11,xh12;
	loadimage(&xh1, "0.png", 360, 36);     //������
	loadimage(&xh2, "1.png", 360, 36);
	loadimage(&xh3, "2.png", 360, 36);
	loadimage(&xh4, "3.png", 360, 36);
	loadimage(&xh5, "4.png", 360, 36);
	loadimage(&xh6, "5.png", 360, 36);
	loadimage(&xh7, "6.png", 360, 36);
	loadimage(&xh8, "7.png", 360, 36);
	loadimage(&xh9, "8.png", 360, 36);
	loadimage(&xh10, "9.png", 360, 36);
	loadimage(&xh11, "10.png", 360, 36);
	loadimage(&xh12, "11.png", 360, 36);
	

	drawAlpha(263, 820 - (20 -1 - o) * 36, &xh1);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh2);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36 ,&xh3);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh4);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh5);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh6);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh7);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh8);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh9);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh10);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh11);
	Sleep(10);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh12);
	//cleardevice(); // �����Ļ�ͷ��ڴ�
}

void Tetris::moveLeftRight(int offset)//�����ƶ�
{
	bakBlock = *curBlock;//����
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map))//�ж��Ƿ�Խ��
	{
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;
	bakBlock = *curBlock;  //����
	curBlock->rotate();
	if (!curBlock->blockInMap(map))//��Խ��
	{
		*curBlock = bakBlock;
	}
}

void Tetris::drawScore()
{
	HWND hwnd = GetHWnd(); // ��ȡ���ھ��
	RECT rect;
	SetWindowText(hwnd, "����ģʽ");//�������Ͻ���ʾ
	GetClientRect(hwnd, &rect); // ��ȡ�ͻ�������

	int width = 938; // �����´��ڵĿ��
	int height = 896; // �����´��ڵĸ߶�
	UINT flags = SWP_NOZORDER | SWP_SHOWWINDOW; // ����ѡ��

	SetWindowPos(hwnd, NULL, 100, 100, width, height, flags); // ���ô���λ�úʹ�С

	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);//��ӡ����
	setcolor(RGB(43, 121, 214)); //������ɫ
	LOGFONT f;//�޸�����ʹ�С
	gettextstyle(&f);
	f.lfHeight = 60;//�߶��趨
	f.lfWidth = 30; //����趨
	f.lfQuality = ANTIALIASED_QUALITY; //�����Ч��


	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("����"));//��������
	settextstyle(&f);//Ӧ������
	setbkmode(TRANSPARENT);//���屳��͸��
	outtextxy(793, 526, scoreText); //ѡ�����λ��,���޸�

	//���������˶�����                                                 
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);  //��ӡ����
	gettextstyle(&f);   //��ȡ���������޸�                                                              
	int xPos = 244 - f.lfWidth * strlen(scoreText);                                      //��̬���õ÷�����λ��
	outtextxy(xPos, 763, scoreText);

	//���Ƶ�ǰ�ǵڼ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);  //��ӡ����
	outtextxy(140, 644, scoreText);

	//������߷�
	sprintf_s(scoreText, sizeof(scoreText), "%d", highestScore);
	outtextxy(687, 708, scoreText);

	//��һ������ע��
	settextstyle(40, 0, "����");
	settextcolor(RGB(0, 0, 0));
	outtextxy(679, 115, "��һ��");

}

void Tetris::checkOver()
{
	gameOver = (curBlock->blockInMap(map) == false);
}


void Tetris::saveScore()
{
	if (score > highestScore)
	{
		highestScore = score;
		ofstream file(RECORDER_FILE);
		file << highestScore;
		file.close();
	}
}

bool  nowflag = 0;
void Tetris::displayOver()
{
	mciSendString("stop BGM.mp3", 0, 0, 0);

	//ʤ������������ʧ�ܽ���
	if (level <= MAX_LEVEL)
	{
		putimage(262, 361, &imgOver);                                           //��ָ��λ�����ͼƬ������������
		mciSendString("play over.mp3", 0, 0, 0);
		
	}

	else
	{
		putimage(262, 361, &imgWin);
		mciSendString("play win.mp3", 0, 0, 0);
		
	}
	
		HWND hwnd = GetHWnd();
		int isok = MessageBox(hwnd, "�����Ƿ��¼�ɼ�\n���ȷ��������������\n���ȡ����������������¼\n��Ϸ�����¿�ʼ", "��Ϸ������", MB_OKCANCEL);
		if (isok == IDOK)
		{
			rank1(score);
		}
}



//ʵ��͸��ͼ�����ж���
void Tetris::drawAlpha( int picture_x, int picture_y, IMAGE* picture)//xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
void Tetris::huanyuan() {
	char buf[100];
	FILE* fp;
	int flag1 = fopen_s(&fp, "gamefile.txt", "rb");
	if (flag1 != 0) {
		printf("�ļ���ʧ��\n");
		system("pause");
	}
	else {
		int nextindex, nextcolor;
		int location[4][2];
		int nowindex, nowcolor;
		fscanf_s(fp, "%d %d ", &nextindex, &nextcolor);
		fgets(buf, sizeof(buf), fp);
		fscanf_s(fp, "%d %d %d %d %d %d %d %d %d %d", &location[0][0], &location[0][1], &location[1][0], &location[1][1], &location[2][0], &location[2][1], &location[3][0], &location[3][1], &nowindex, &nowcolor);
		fgets(buf, sizeof(buf), fp);
		for (int i = 0; i < rows-1; i++) {
			for (int j = 0; j < cols; j++) {
				fscanf_s(fp, "%d", &map[i+1][j]);
				fgets(buf, sizeof(buf), fp);
			}
		}
		fscanf_s(fp, "%d %d %d", &score, &level, &lineCount);
		fgets(buf, sizeof(buf), fp);
	}
}

void Tetris::playcon()
{
	nextBlock = new Block;    //����Ԥ�淽��
	curBlock = nextBlock;     //���µ�ǰ����
	nextBlock = new Block;   

	int timer = 0;
	while (1)
	{
		//�����û�����
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			//��Ⱦ��Ϸ����
			update = true;
		}
		if (update)
		{
			update = false;
			//���»���
			upadteWindow();
			//��������
			clearLine();
		}
		if (gameOver)//�������
		{
			saveScore();
			//������Ϸ��������
			displayOver();
			system("pause");
			init();//���¿���
		}
	}
}






