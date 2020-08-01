#ifndef TOOLS_H
#define TOOLS_H

#define MAX 100
#define Max 100

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include<time.h>

extern int student_count;
extern int out;

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

struct Teacher
{
	char tea_name[20];
	int tea_sex;
	int tea_id;
	char tea_password[20];
	char tea_error;
};

extern struct Student stu[Max];
extern struct Teacher tea[Max];

char leader_password[10];

//强制修改密码
void strong_change();

//修改自己的密码
void change_personpass();

//产生随机学号（1000-9999）
int srand_num();

//显示输入帐号密码的界面

#endif// TOOLS_H
