#include<stdio.h>
#include"tools.h"


struct Student
{
    char stu_name[20];
    int stu_sex;
    char stu_id[8];
    char stu_password[10];
    short chinese_score;
    short math_score;
    short english_score;
};


struct Teacher
{
	char tea_name[20];
	int sex_tea;
	char stu_id[8];
	char stu_password;
};

//强制修改密码
void strong_change()
{
	
}

//修改自己的密码
void change_personpass()
{
	
}

//产生随机学号（1000-9999）
void srand_num()
{
	
}

//显示输入帐号密码的界面
char menu()
{
	//同时要在里面判断是否是第一次
	return 0;
}
