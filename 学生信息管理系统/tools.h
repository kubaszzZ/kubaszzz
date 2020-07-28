#ifndef TOOLS_H
#define TOOLS_H
#define M 100



struct Student
{
    char stu_name[20];
    int stu_sex;
    int stu_id;
    char stu_password[10];
    short chinese_score;
    short math_score;
    short english_score;
};


struct Teacher
{
	char tea_name[20];
	int sex_tea;
	int tea_id;
	char tea_password[10];
};

char leader_password[10];

//强制修改密码
void strong_change();

//修改自己的密码
void change_personpass();

//产生随机学号（1000-9999）
int srand_num();


#endif// TOOLS_H
