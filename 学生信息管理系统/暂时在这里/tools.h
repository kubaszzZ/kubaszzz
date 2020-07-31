#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getch.h>
#define Max 100//最大容量100
#define MAX 100

extern int student_count;//容量计数
extern int out;
struct Teacher
{
	char tea_name[20];
	int tea_sex;
	int tea_id;
	char tea_password[13];
	char tea_error;
};

struct Student
{
    char stu_name[20];
    int stu_sex;
    int stu_id;
    char stu_password[10];
    short chinese_score;
    short math_score;
    short english_score;
    char stu_error;
};

extern struct Student stu[Max];
extern struct Teacher tea[Max];

char leader_password[10];
//强制修改密码
void strong_change(void);

//修改自己的密码
void change_personpass(void);

//产生随机学号（1000-9999）
int srand_num(void);

//显示输入帐号密码的界面
#endif// TOOLS_H
