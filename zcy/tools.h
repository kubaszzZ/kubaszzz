#ifndef TOOLS_H
#define TOOLS_H
#define MAX 100
struct Student
{
    char stu_name[20];
    int stu_sex;
    int stu_id[8];
    char stu_password[10];
    short chinese_score;
    short math_score;
    short english_score;
};


struct Teacher
{
	char t_name[20];
	int t_sex;
	int t_id;
	char t_password[20];
	char t_error;
};

char leader_password[10];

//强制修改密码
void strong_change();

//修改自己的密码
void change_personpass();

//产生随机学号（1000-9999）
int srand_num();

//显示输入帐号密码的界面

#endif// TOOLS_H
