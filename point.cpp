#include "point.h"
int block[28][5][5]{
	//l�η���
		{0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0
	},
		{0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
	//���η���
		{0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
	//S�η���
		{0,0,0,0,0,
		0,0,1,1,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,1,0,
		0,0,0,1,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,1,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,1,0,
		0,0,0,1,0,
		0,0,0,0,0
	},
	//Z�η���
		{0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,0,1,0,
		0,0,1,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{0,0,0,0,0,
		0,0,0,1,0,
		0,0,1,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	},
	//L�η���
		{0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,0,0,0,
		0,1,1,1,0,
		0,1,0,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,1,1,0,
		0,0,0,1,0,
		0,0,0,1,0,
		0,0,0,0,0
		},
		{ 0,0,0,0,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
		},
	//J�η���
		{ 0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,1,1,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,0,0,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,0,0,0,0
	},
	//T�η���
		{ 0,0,0,0,0,
		0,1,1,1,0,
		0,0,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,1,0,0,
		0,1,1,0,0,
		0,0,1,0,0,
		0,0,0,0,0
	},
		{ 0,0,0,0,0,
		0,0,1,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	},
	{ 
		0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	}
};
int blockcolor[COLORNUM]{ RED,GREEN,CYAN,ORANGE,PINK,PURPLE,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW };

void Bgm()
{
	//�����֣���������
	mciSendString("open kn.mp3", NULL, 0, NULL);

	mciSendString("play kn.mp3 repeat", NULL, 0, NULL);

	IMAGE ct2, ct3, ct4, ct5, ct6, ct7, ct8, ct9, ct10, ct11, ct12, ct13, ct14, ct15, ct16, ct17, ct18, ct19, ct20, ct21, ct22, ct23, ct24, ct25, ct26,ct27;          //��������
	
	//ct(1).png
	loadimage(&ct2, "ct(2).png", 938, 896);
	loadimage(&ct3, "ct(3).png", 938, 896);
	loadimage(&ct4, "ct(4).png", 938, 896);
	loadimage(&ct5, "ct(5).png", 938, 896);
	loadimage(&ct6, "ct(6).png", 938, 896);
	loadimage(&ct7, "ct(7).png", 938, 896);
	loadimage(&ct8, "ct(8).png", 938, 896);
	loadimage(&ct9, "ct(9).png", 938, 896);
	loadimage(&ct10, "ct(10).png", 938, 896);
	loadimage(&ct11, "ct(11).png", 938, 896);
	loadimage(&ct12, "ct(12).png", 938, 896);
	loadimage(&ct13, "ct(13).png", 938, 896);
	loadimage(&ct14, "ct(14).png", 938, 896);
	loadimage(&ct15, "ct(15).png", 938, 896);
	loadimage(&ct16, "ct(16).png", 938, 896);
	loadimage(&ct17, "ct(17).png", 938, 896);
	loadimage(&ct18, "ct(18).png", 938, 896);
	loadimage(&ct19, "ct(19).png", 938, 896);
	loadimage(&ct20, "ct(20).png", 938, 896);
	loadimage(&ct21, "ct(21).png", 938, 896);
	loadimage(&ct22, "ct(22).png", 938, 896);
	loadimage(&ct23, "ct(23).png", 938, 896);
	loadimage(&ct24, "ct(24).png", 938, 896);
	loadimage(&ct25, "ct(25).png", 938, 896);
	loadimage(&ct26, "ct(26).png", 938, 896);
	loadimage(&ct26, "ct(27).png", 938, 896);

	putimage(0, 0, &ct2);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct3);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct4);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct5);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct6);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct7);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct8);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct9);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct10);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct11);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct12);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct13);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct14);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct15);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct16);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct17);
	Sleep(100);
	cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct18);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct19);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct20);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct21);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct22);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct23);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct24);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct25);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct26);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�
	putimage(0, 0, &ct27);
	Sleep(100); cleardevice(); // �����Ļ�ͷ��ڴ�

}

	void Backgound()
{
	//����ͼƬ1
	IMAGE background1;
	loadimage(&background1, "bg1.png", 938, 896);
	putimage(0, 0, &background1);
	//����ͼƬ
	IMAGE sound;
	loadimage(&sound, "soundn.png", 40, 40);
	putimage(0, 0, &sound);
}
void button(int x, int y, int w, int h, const char* text)//��ť���
{
	setbkmode(TRANSPARENT);//��ť�ײ����		
	setfillcolor(RGB(14, 99, 254));
	fillroundrect(x, y, x + w, y + h, 10, 10);

	settextstyle(50, 0, "����");//�����С
	settextcolor(RGB(255, 255, 255));
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}
void rankbutton(int x, int y, int w, int h, const char* text)//���а�ť���
{
	setbkmode(TRANSPARENT);//��ť�ײ����		
	setfillcolor(RGB(238, 255, 229));
	fillroundrect(x, y, x + w, y + h, 10, 10);

	settextstyle(70, 0, "���ֹ������ֿ��ԲGBK");//�����С
	settextcolor(RGB(255, 0, 0));
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);
}
int readrank()
{
	info temp;
	int n = 0;
	FILE* fp;
	int flag = 0;
	//��������
	char buf[100];
	FILE* p;
	flag = fopen_s(&p, "rank.txt", "rb");
	if (flag != 0)
	{
		printf("cannot open the files\n");
		system("pause");
		return -1;
	}
	else {
		while (!feof(p))
		{
			memset(buf, 0, sizeof(buf));//ÿ�ζ�ȡһ��֮ǰ�������buf���
			fgets(buf, sizeof(buf), p);//���ļ��ж�ȡһ��
			n++;
		}
		fclose(p);
	}
	n /= 2;
	info* array = (info*)malloc(n * sizeof(temp));//����һ����̬���飬��̬����ĳ�Ա������.txt�ļ�����һ����
	flag = fopen_s(&fp, "rank.txt", "rb");
	if (flag != 0)
	{
		printf("cannot open rank.txt\n");
		system("pause");
		return -1;
	}
	for (int i = 0;i < n;i++)//��ȡ���ֺ����ݣ�����һ������
	{
		fgets(array[i].name, 30, fp);
		char* tmp = NULL;
		if ((tmp = strstr(array[i].name, "\n")))
		{
			*tmp = '\0';
		}
        
		fscanf_s(fp, "%d", &array[i].score);
        fgets(buf, sizeof(buf), fp);//��ȡ�������һ��
		
	}
	for (int i = 0;i < n - 1;i++)//��������ð������
	{
		int k = i;
		for (int j = i + 1;j < n;j++)
		{
			if (array[j].score > array[i].score)
			{
				k = j;
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	fclose(fp);
	for (int i = 0;i < n;i++)//���µ���������Ķ���չʾ����
	{
		settextcolor(RGB(117, 22, 63));
		settextstyle(31, 0, "����");
		char str1[30];
		sprintf_s(str1, "%d", i + 1);//�����ָ�ʽ�����Ϊ�ַ���
		outtextxy(300 + textwidth("����") / 2 - textwidth(str1) / 2, 170 + i * textheight(str1), str1);
		outtextxy(450 + textwidth("����") / 2 - textwidth(array[i].name) / 2, 170 + i * textheight(array[i].name), array[i].name);
		char str2[30];
		sprintf_s(str2, "%d", array[i].score);//�����ָ�ʽ�����Ϊ�ַ���
		outtextxy(600 + textwidth("�÷�") / 2 - textwidth(str2) / 2, 170 + i * textheight(str2), str2);
	}
	free(array);
	return 0;
}
void list()
{
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "���а�");
	IMAGE background;
	loadimage(&background, "rankn.png", 938, 896);
	putimage(0, 0, &background);
	//rankbutton(150, 20, 350, 100, "���а�");
	settextcolor(RGB(255, 13, 7));
	settextstyle(35, 0, "����");
	outtextxy(300, 130, "����");
	outtextxy(450, 130, "����");
	outtextxy(600, 130, "����");
	//���ذ���ͼ��
	IMAGE backimage1, backimage2;
	loadimage(&backimage1, "back1.png", 50, 50);
	loadimage(&backimage2, "back2.png", 50, 50);
	putimage(0, 0, &backimage2, SRCAND);
	putimage(0, 0, &backimage1, SRCPAINT);
}
void wait(int interval)
{
	int count = interval / 10;
	for (int i = 0; i < count; i++) {
		Sleep(10);
		if (_kbhit()) {
			return;
		}
	}
}