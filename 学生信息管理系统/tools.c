#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"tools.h"

struct Student stu[100];
struct Teacher tea[100];

//强制修改密码
void strong_change()
{
	int n=0;
	puts("1.学生");
	puts("2.老师");
	printf("请选择你的身份:");
	scanf("%d",&n);
	if(1==n)
	{	
		char names[20]={};
		printf("请输入要修改密码的姓名:");
		scanf("%s",names);
		for(int i=0;;i++)
		{
			if(	strcmp(stu[i].stu_name,names)==0 && stu[i].stu_sex!=0)
			{
				strcpy(stu[i].stu_password,"123");
				puts("密码重置成功!");
				break;
			}
		}
	}
	if(2==n)
	{
		char names[20]={};
		printf("请输入要修改密码的姓名:");
		scanf("%s",names);
		for(int i=0;;i++)
		{
			if(	strcmp(tea[i].tea_name,names)==0 && tea[i].sex_tea!=0)
			{

				strcpy(tea[i].tea_password,"123");
				puts("密码重置成功!");
				break;
			}
		}
	}
}

//修改自己的密码
void change_personpass()
{
	int n=0;
	puts("1.学生");
	puts("2.老师");
	printf("请选择你的身份:");
	scanf("%d",&n);
	if(1==n)
	{	
		char names[20]={};
		printf("请输入要修改密码的姓名:");
		scanf("%s",names);
		for(int i=0;;i++)
		{
			if(	strcmp(stu[i].stu_name,names)==0 && stu[i].stu_sex!=0)
			{
				char mima[10]={};
				printf("请输入新密码:");
				scanf("%s",mima);
				strcpy(stu[i].stu_password,mima);
				puts("密码修改成功!");
				break;
			}
		}
	}
	if(2==n)
	{
		char names[20]={};
		printf("请输入要修改密码的姓名:");
		scanf("%s",names);
		for(int i=0;;i++)
		{
			if(strcmp(tea[i].tea_name,names)==0 && tea[i].sex_tea!=0)
			{
				char mima[10]={};
				printf("请输入新密码:");
				scanf("%s",mima);
				strcpy(tea[i].tea_password,mima);
				puts("密码修改成功!");
				break;
			}
		}
	}
}

//产生随机学号（1000-9999）
int srand_num()
{
	srand(time(NULL));
	return rand()%9000+1000;
}
