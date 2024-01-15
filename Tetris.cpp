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
const int SPEED_NORMAL[MAX_LEVEL] = { 550,400,300,200,100 }; //通过改变普通模式的关卡的下落速度改变难度
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

void Tetris::init()//初始化
{
	mciSendString("close BGM.mp3 repeat", NULL, 0, NULL);
	mciSendString("open BGM.mp3 repeat", NULL, 0, NULL);
	mciSendString("play BGM.mp3 repeat", NULL, 0, NULL);
	delay = SPEED_NORMAL[0];//设置方块掉落的时间间隔
	//配置随机种子
	srand(time(NULL));

	//加载背景图片
	loadimage(&imgBg, "bg2.png");//加载背景图

	loadimage(&sound, "sound.png", 40, 40);
	loadimage(&mute, "mute.png", 40, 40);

	loadimage(&imgWin, "win.png");
	loadimage(&imgOver, "over.png");

	//初始化游戏区中的数据
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

	//初始化最高分
	ifstream file(RECORDER_FILE);
	if (!file.is_open())
	{
		cout << RECORDER_FILE << "打开失败" << endl;
		highestScore = 0;
	}
	else
	{
		file >> highestScore;        //从文件中输入
	}
	file.close();           //关闭文件
	gameOver = false;
}

void Tetris::play()
{
	init();                   //界面设计
	nextBlock = new Block;    //生成预告方块
	curBlock = nextBlock;     //更新当前方块
	nextBlock = new Block;    //

	int timer = 0;
	while (1)
	{
		preBlock = curBlock;
		//接受用户输入
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			//渲染游戏画面
			update = true;
		}
		if (update)
		{
			update = false;
			//更新画面
			upadteWindow();
			//更新数据
			clearLine();
		}
		if (gameOver)//保存分数
		{
			saveScore();
			//更新游戏结束界面
			displayOver();
			system("pause");
			init();//重新开局
		}
	}
}

void Tetris::keyEvent()
{
	unsigned char ch;   //0..255
	bool rotateFlag = false;
	int dx = 0;            //定义偏移量，用于左右移动
	if (_kbhit())           //_kbhit有按键输入，返回值为真
	{
		ch = _getch();
		//如果按下方向键，会自动返回两个字符
		//如果按向上方向键，会先后返回：224 72
		//如果按向下方向键，会先后返回：224 80
		//如果按向左方向键，会先后返回：224 75 
		//如果按向右方向键，会先后返回：224 77
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case 72:    //上
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				rotateFlag = true;
				break;
			case 80:    //下
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				delay = 0;
				break;
			case 75:    //左
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				dx = -1;
				break;
			case 77:   //右
				mciSendString("close 116.mp3", NULL, 0, NULL);
				mciSendString("open 116.mp3", NULL, 0, NULL);
				mciSendString("play 116.mp3", NULL, 0, NULL);
				dx = 1;
				break;

			default:
				break;
			}
		}
		else if (ch == 32) // 空格键-暂停/继续
		{
			isPaused = !isPaused; // 切换暂停状态

			if (isPaused)
			{
				HWND hwnd = GetHWnd();
				mciSendString("stop BGM.mp3", NULL, 0, NULL);         
				MessageBox(hwnd, "游戏已经暂停\n继续点击确定", "提示", MB_OK);      

			}
			mciSendString("play BGM.mp3", NULL, 0, NULL);
		}
		else if (ch == 27)       //Esc键
		{
			isPaused = !isPaused; //  切换暂停状态

			if (isPaused)
			{
				HWND hwnd = GetHWnd();
				mciSendString("stop BGM.mp3", NULL, 0, NULL);
				if (MessageBox(hwnd, "是否保存当前游戏\n", "提示", MB_OKCANCEL) != IDOK)
					//如果用户选择了“确定”按钮（点击了 OK），则整个条件表达式的结果为 true，否则为 false
				{
					main();
				}
				else {
					FILE* p;
					if (!fopen_s(&p, "gamefile.txt", "r")) {
						fclose(p);
						if (MessageBox(hwnd, "已经存在游戏进度，是否删除", "提示", MB_OKCANCEL) == IDCANCEL) {
							return;
						}
					}
					int flag = fopen_s(&p, "gamefile.txt", "w");
					if (flag != 0) {
						printf("无法存储游戏进度\n");
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
	if (rotateFlag)//旋转处理
	{
		//rotateFlag = false;
		rotate();
		update = true;
	}
	if (dx != 0)//实现左右移动
	{
		moveLeftRight(dx);
		update = true;
	}
}

void Tetris::upadteWindow()    //更新游戏画面
{
    BeginBatchDraw();//启动批量绘制模式
	putimage(0, 0, &imgBg); //绘制背景图
	
	for (int i = 0; i < GRIDNUMX; i++)
	{
		for (int j = 0; j < GRIDNUMY; j++)
		{
			//画透明的网格
			setcolor(WHITE);
			setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);
			drawRectangle((i - 0) * BLOCKSIZE + 263, (j - 0) * BLOCKSIZE + 133, (i - 0) * BLOCKSIZE + 263 + BLOCKSIZE, (j - 0) * BLOCKSIZE + 133 + BLOCKSIZE);
		}
	}

	IMAGE** imgs = Block::getImages();//已经降落到底部固定方块的渲染                      
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
	nextBlock->draw(689, 150);//预告下一个方块

	drawScore();//绘制分数

	EndBatchDraw();
}

//第一次调用，返回0
//返回距离上一次调用，间隔了多少ms
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
	//备用位置，记录上一次的位置
	bakBlock = *curBlock;  //重载了等号的意义
	curBlock->drop();

	if (!curBlock->blockInMap(map))//下降过程中，判断位置如果不合法
	{
		//固化方块
		bakBlock.solidify(map);
		delete curBlock;        //删除不合法方块
		curBlock = nextBlock;  //将当前方块设置为下一个方块
		nextBlock = new Block; //下一个方块设置为新方块

		//检查游戏是否结束
		checkOver();
	}
	delay = SPEED_NORMAL[level - 1];
}

void Tetris::clearLine()    //消除原理
{
	int lines = 0;

	int k = rows - 1;    //存储数据的行数
	for (int i = rows - 1; i >= 0; i--)
	{
		//检查第i行是否满行
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];    //边扫描边存储
		}
		if (count < cols)    //不是满行，就退到上一行，是满行，就停在那一行，等下一次的覆盖
		{
			k--;
		}
		else   //满行
		{
			                                                      
			lines++;    //知道一次消除了几行
			applyCarton(i); 
		}
	}
	if (lines > 0)
	{
		//计算得分
		int addScore[5] = { 10,30,60,80 ,100};
		score += addScore[lines - 1];

		mciSendString("play xiaochu1.mp3", 0, 0, 0); //播放消除行的音效,待修改xiaochu1
		update = true;

		level = (score + 99) / 100;//设置关卡 每100分一关
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
	loadimage(&xh1, "0.png", 360, 36);     //长，宽
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
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh2);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36 ,&xh3);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh4);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh5);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh6);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh7);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh8);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh9);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh10);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh11);
	Sleep(10);
	//cleardevice(); // 清空屏幕释放内存
	drawAlpha(263, 820 - (20 - 1 - o) * 36, &xh12);
	//cleardevice(); // 清空屏幕释放内存
}

void Tetris::moveLeftRight(int offset)//左右移动
{
	bakBlock = *curBlock;//备份
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map))//判断是否越界
	{
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;
	bakBlock = *curBlock;  //备份
	curBlock->rotate();
	if (!curBlock->blockInMap(map))//当越界
	{
		*curBlock = bakBlock;
	}
}

void Tetris::drawScore()
{
	HWND hwnd = GetHWnd(); // 获取窗口句柄
	RECT rect;
	SetWindowText(hwnd, "单人模式");//程序左上角显示
	GetClientRect(hwnd, &rect); // 获取客户区矩形

	int width = 938; // 设置新窗口的宽度
	int height = 896; // 设置新窗口的高度
	UINT flags = SWP_NOZORDER | SWP_SHOWWINDOW; // 附加选项

	SetWindowPos(hwnd, NULL, 100, 100, width, height, flags); // 设置窗口位置和大小

	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);//打印函数
	setcolor(RGB(43, 121, 214)); //设置颜色
	LOGFONT f;//修改字体和大小
	gettextstyle(&f);
	f.lfHeight = 60;//高度设定
	f.lfWidth = 30; //宽度设定
	f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿效果


	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("宋体"));//设置字体
	settextstyle(&f);//应用字体
	setbkmode(TRANSPARENT);//字体背景透明
	outtextxy(793, 526, scoreText); //选定输出位置,待修改

	//绘制消除了多少行                                                 
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);  //打印函数
	gettextstyle(&f);   //获取字体后可以修改                                                              
	int xPos = 244 - f.lfWidth * strlen(scoreText);                                      //动态设置得分字体位置
	outtextxy(xPos, 763, scoreText);

	//绘制当前是第几关
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);  //打印函数
	outtextxy(140, 644, scoreText);

	//绘制最高分
	sprintf_s(scoreText, sizeof(scoreText), "%d", highestScore);
	outtextxy(687, 708, scoreText);

	//下一个方块注释
	settextstyle(40, 0, "宋体");
	settextcolor(RGB(0, 0, 0));
	outtextxy(679, 115, "下一个");

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

	//胜利结束，还是失败结束
	if (level <= MAX_LEVEL)
	{
		putimage(262, 361, &imgOver);                                           //在指定位置输出图片，并播放音乐
		mciSendString("play over.mp3", 0, 0, 0);
		
	}

	else
	{
		putimage(262, 361, &imgWin);
		mciSendString("play win.mp3", 0, 0, 0);
		
	}
	
		HWND hwnd = GetHWnd();
		int isok = MessageBox(hwnd, "分数是否记录成绩\n如果确定，请输入名字\n如果取消，分数将不被记录\n游戏将重新开始", "游戏结束了", MB_OKCANCEL);
		if (isok == IDOK)
		{
			rank1(score);
		}
}



//实现透明图的消行动画
void Tetris::drawAlpha( int picture_x, int picture_y, IMAGE* picture)//x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
void Tetris::huanyuan() {
	char buf[100];
	FILE* fp;
	int flag1 = fopen_s(&fp, "gamefile.txt", "rb");
	if (flag1 != 0) {
		printf("文件打开失败\n");
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
	nextBlock = new Block;    //生成预告方块
	curBlock = nextBlock;     //更新当前方块
	nextBlock = new Block;   

	int timer = 0;
	while (1)
	{
		//接受用户输入
		keyEvent();

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			//渲染游戏画面
			update = true;
		}
		if (update)
		{
			update = false;
			//更新画面
			upadteWindow();
			//更新数据
			clearLine();
		}
		if (gameOver)//保存分数
		{
			saveScore();
			//更新游戏结束界面
			displayOver();
			system("pause");
			init();//重新开局
		}
	}
}






