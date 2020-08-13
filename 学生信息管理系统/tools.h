#ifndef TOOLS_H
#define TOOLS_H

#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include<time.h>

#define MAX 100 

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#define STFP stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].stu_password,stu[i].chinese_score,stu[i].math_score,stu[i].english_score,stu[i].stu_error
#define STFS stu[i].stu_name,&stu[i].stu_sex,&stu[i].stu_id,stu[i].stu_password,&stu[i].chinese_score,&stu[i].math_score,&stu[i].english_score,&stu[i].stu_error
#define TFP tea[i].tea_name,tea[i].tea_sex,tea[i].tea_id,tea[i].tea_password,tea[i].tea_error
#define TFS tea[i].tea_name,&tea[i].tea_sex,&tea[i].tea_id,tea[i].tea_password,&tea[i].tea_error

extern int student_count;
extern int n;

typedef struct Student
{
    char stu_name[20];
    int stu_sex;
    int stu_id;
    char stu_password[10];
    short chinese_score;
    short math_score;
    short english_score;
    char stu_error;
}Student;

typedef struct Teacher
{
	char tea_name[20];
	int tea_sex;
	int tea_id;
	char tea_password[20];
	char tea_error;
}Teacher;
enum usualnum
{
	fu1=-1,ling,yi,er=2,san,si,wu,liu,qi,ba,jiu
};
extern Student stu[MAX];
extern Teacher tea[MAX];

char leader_password[10];

//强制修改密码
void strong_stu_change(void);
void strong_tea_change(void);
//修改自己的密码
void change_stu_personpass(void);

void change_tea_personpass(void);

void change_admin_personpass(void);

//产生随机学号（1000-9999）
int srand_num();

//显示输入帐号密码的界面
void origin_menu(void);
//保持
void contiiinue(void);
#endif// TOOLS_H
