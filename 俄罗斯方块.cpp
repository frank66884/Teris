#include"total.h"

#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//����ʾ����
#pragma comment(linker,"/MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR")//��С�������
void main()
{
	while (true)
	{
		maininterface();         //��ʼ������
		buttonhit();
	}
}
