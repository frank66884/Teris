#include"total.h"

#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//不显示窗口
#pragma comment(linker,"/MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR")//减小编译体积
void main()
{
	while (true)
	{
		maininterface();         //初始化界面
		buttonhit();
	}
}
