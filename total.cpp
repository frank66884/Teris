#include "total.h"
#include "Tetris.h"
#include <map>
void singlemodeoperate(bool flag)
{
	initializegrid();    //完成
	if (flag == TRUE)//开始新的游戏为TRUE
	{
		srand((unsigned)time(NULL));    //配置随机数种子
		int z = rand() % 7;
		nowcolor = z;
		nextcolor = z;
		nextblock();
		Sleep(100);
		memset(gridnum, 0, sizeof(gridnum));
	}
	else {
		loadfile();//继续游戏的话先进行存档的读取
		clearnextblock(690, 276, 840, 426);
		drawblock(725, 260, nextindex, nextcolor);
		drawblock(beginx+(continuex-EXTRA)*BLOCKSIZE, beginy+continuey*BLOCKSIZE, nowindex, nowcolor);
		Sleep(100);
		move(continuex-EXTRA- (GRIDNUMX - EXTRA) / 2,continuey);
	}
	BeginBatchDraw();//开始批量绘图
	while (true)
	{
		FlushBatchDraw();//绘图批处理防止闪烁
		if (nowblock() == TRUE)
		{
			break;
		}
	}
	EndBatchDraw();//结束批量绘图
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
	MessageBox(hwnd, "游戏开始!!!\n", "提示", MB_OK) == IDOK;
	int flag=2;
	while (true)//双人模式一直在循环
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
void maininterface()//创建窗口图形
{
	
	initgraph(938, 896, SHOWCONSOLE);	    // 创建绘图窗口，大小为 938*896 像素
	setbkmode(TRANSPARENT);//透明化
	
	Bgm();

	Backgound();
	button(290, 200, 280, 102, "单人独享");//修改方格位置and长宽,第一个是x负责左右，y负责上下是第二个
	button(290, 380, 280, 102, "双人成行");
	button(290, 560, 280, 102, "大神排名");
}
void buttonhit()//按钮点击设计
{
	int flag = 1;//flag为0时为mute，为1时为sound
	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE))//第一个页面三个按钮坐标控制
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 200 && msg.x < 570 && msg.y < 302)//单人模式设计
			{
				BOOL flag1 = newcontinue();//判断是否开始新的游戏，开始新的游戏则为TRUE，继续游戏为FALSE
				if (flag1 == true) {
					Tetris game(20, 10, 263, 133, 36);//根据背景的像素参数来制定
					game.play();
				}
				else {
					Tetris game(20, 10, 263, 133, 36);//根据背景的像素参数来制定
					game.init();
					game.huanyuan();
					game.playcon();
				}
			}        
             //双人模式设计
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 380 && msg.x < 570 && msg.y < 482)
			{
				//进入双人模式，关闭之前那的背景音乐
				mciSendString("close kn.mp3", NULL, 0, NULL);
				//背景
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
					if (MessageBox(hwnd, "游戏结束!!!\n", "提示", MB_OK) == IDOK)
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
					if (MessageBox(hwnd, "游戏结束!!!\n", "提示", MB_OK) == IDOK)
					{
						mciSendString("close end.mp3", NULL, 0, NULL);
						return;
					}
				}
				return;
			}
			//排行榜设计
			else if (msg.message == WM_LBUTTONDOWN && msg.x > 290 && msg.y > 560 && msg.x < 570 && msg.y < 662)
			{
				//进入排行榜进行音乐的关闭
				
				mciSendString("close kn.mp3", NULL, 0, NULL);
				mciSendString("open rank.mp3", NULL, 0, NULL);
				mciSendString("play rank.mp3", NULL, 0, NULL);
				initgraph(938, 896, SHOWCONSOLE);
				setbkmode(TRANSPARENT);
				setbkcolor(WHITE);
				clearcliprgn();
				list();                           //排行榜的页面设计
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
			//声音关闭状态
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