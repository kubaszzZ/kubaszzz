#include "tools.h"


int student_count=0;

//强制修改密码
void strong_change(void)
{
	
}

//修改自己的密码
void change_personpass(void)
{
	
}

//产生随机学号（1000-9999）
int srand_num(void)
{
	srand(time(NULL));
	int num=rand()%9000+1000;
	return num;
}

//显示输入帐号密码的界面
char menu(void)
{
	//同时要在里面判断是否是第一次
	return 0;
}
