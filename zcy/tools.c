#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include"tools.h"

struct Student stu[100];
struct Teacher tea[100];

//强制修改密码
void strong_change()
{
	int n=0;
	puts("1.学生");
	puts("2.老师");
	printf("请选择你要修改的身份:");
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
		
		//打开		
		FILE *frotea=fopen("OLT","r+");
		if(NULL==frotea)//↑打开在线老师信息文件
		{
			printf("文件不存在");
			return ;
		}
		for(int j=0;j<MAX;j++)
		{
			fscanf(frotea,"%s %d %d %s %hhd\n", tea[j].t_name, &tea[j].t_sex, &tea[j].t_id, tea[j].t_password,&tea[j].t_error);//获取文件信息----错误信息							
			if(strcmp(tea[j].t_name,names)==0 && tea[j].t_id!=0)
			{
				int str_l=0;
				str_l+=strlen(tea[j].t_name);
				str_l+=sizeof(tea[j].t_sex);
				str_l+=sizeof(tea[j].t_id);
				str_l+=strlen(tea[j].t_password);
				str_l+=sizeof(tea[j].t_error);
				//获取前几个参数的位数把文件指针指回要修改一行的开头
				//tea[j].tea_error=0;
				strcpy(tea[j].t_password,"123");
				tea[j].t_error=0;
				printf("--%d--\n", str_l);
				printf("--%hhd--\n", tea[j].t_error);
				fseek(frotea,-str_l-1,1);
				fprintf(frotea,"%s %d %3d %s %hhd\n", tea[j].t_name, tea[j].t_sex, tea[j].t_id, tea[j].t_password,tea[j].t_error);//只改变error为0,%3d可以为ID的最大位数---错误次数(从fseek中减去位数)
				//完全删除(未实现)					
				break;
			}
		}
		fclose(frotea);	
		printf("重置成功\n");
		usleep(1.0*1000000);				
	}
}

//修改自己的密码
void change_personpass()
{
	int n=0;
	puts("1.学生");
	puts("2.老师");
	puts("3.校长");
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
			if(strcmp(tea[i].t_name,names)==0 && tea[i].t_sex!=0)
			{
				char mima[10]={};
				printf("请输入新密码:");
				scanf("%s",mima);
				strcpy(tea[i].t_password,mima);
				puts("密码修改成功!");
				break;
			}
		}
	}
	if(3==n)
	{
		char new_pass[10]={};
		printf("请校长输入你要修改的新密码:");
		scanf("%s",new_pass);
		strcpy(leader_password,new_pass);
		puts("密码修改成功");
	}
}

//产生随机学号（1000-9999）
int srand_num()
{
	srand(time(NULL));			//随机学号是否重复
	return rand()%9000+1000;
}
