#include<stdio.h>
#include "stu_tools.h"
#include"tools.h"

int wrong=0;
char student_name[20];//学生姓名
int flag_1=0;//０为未登录，１为登录
int record=0;
void read_student()//读取学生信息
{
	FILE* fp=fopen("student.txt","r+");	
	for(int i=0;i<student_count;i++)
	{
  		fscanf(fp,"%s %d %d %s %hd %hd %hd",stu[i].stu_name,&stu[i].stu_sex,&stu[i].stu_id,stu[i].stu_password,&stu[i].chinese_score,&stu[i].math_score,&stu[i].english_score);
  		//printf("%s %d %d %s %hd %hd %hd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].stu_password,stu[i].chinese_score,stu[i].math_score,stu[i].english_score);
	}
	fclose(fp);
	return;
}
char stu_menu()//学生菜单
{
	int option=0;
	system("clear");
	puts("————————————————————————————————");
	puts("｜   　　学生学籍管理　　　　 ｜");
	puts("｜   	 1、登录　  　　　　 ｜");
	puts("｜   	 ２、查询成绩　 　　　｜");
	puts("｜       ３、修改密码　　　　 ｜");
	puts("｜       ４、查看个人信息　　 ｜");
	puts("｜       ５、退出　　　　　　 ｜");
	puts("———————————————————————————————");
	puts("请输入选项：");
	scanf("%d",&option);
	if(3<wrong) {printf("密码错误已达3次，联系教师");return 0;}
	if(5==option) return option;
	if(1==option&&0==flag_1) return option;
	else if(1==option&&1==flag_1) {printf("已登录请勿重复登录\n"); return 0;}
	if(1<option&&5>option&&1==flag_1) {return option;}
	while(1!=option&&0==flag_1)
	{
		if(5==option) return option;
		printf("请先登录：\n");
		scanf("%d",&option);
	}
	return option;
}

void stu_online()//登录
{
	int cmp=0,num=0;
	char student_password[10]={};
	printf("请输入姓名、密码:");
	scanf("%s %s",student_name,student_password);
	for(int i=0;i<student_count;i++)
	{
		if(0==strcmp(stu[i].stu_name,student_name))
		{
			record=i;
			//printf("%d",record);
			num=1;
			break;
		}
		
	}
	if(0==num) 
	{
		printf("学生不存在!\n");
		return;
	} 
	while(3>wrong)
	{
		if(0==strcmp(stu[record].stu_password,student_password))
		{
			printf("登录成功\n");
			cmp=strcmp("123",student_password);
			if(0==cmp)
			{
				printf("强制修改密码：\n");
				change_personpass();
				FILE* fp=fopen("student.txt","w");
				for(int k=0;k<2;k++)
				{
					fprintf(fp,"%s %d %d %s %hd %hd %hd",stu[k].stu_name,stu[k].stu_sex,stu[k].stu_id,stu[k].stu_password,stu[k].chinese_score,stu[k].math_score,stu[k].english_score);
				}
				fclose(fp);
			}
			wrong=0;
			flag_1=1;
			return;
		}
		else
		{
			printf("密码错误，重新输入：");
			wrong++;
			scanf("%s",student_password);
			fflush(stdin);
		}
		if(3==wrong) 
		{
			printf("密码输入错误已达３次，账号已锁定\n");  
			return;
		}
	}
	return;
}
void find_score() //查看成绩
{
  	int max_chinese=0,min_chinese=100,max_eng=0,min_eng=100,max_math=0,min_math=100;
  	int sum_chinese=0,sum_eng=0,sum_math=0;
	for(int i=0;i<student_count;i++)
	{
		sum_chinese+=stu[i].chinese_score;
		if(max_chinese<stu[i].chinese_score)
		{
			max_chinese=stu[i].chinese_score;
		}
		if(min_chinese>stu[i].chinese_score)
		{
			min_chinese	=stu[i].chinese_score;
		}
	}
	printf("语文最高分：%hd 最低分：%hd 平均分：%f\n",max_chinese,min_chinese,(float)(sum_chinese/student_count));
	for(int i=0;i<student_count;i++)
	{
		sum_math+=stu[i].math_score;
		if(max_math<stu[i].math_score)
		{
			max_math=stu[i].math_score;
		}
		if(min_math>stu[i].math_score)
		{
			min_math=stu[i].math_score;
		}
	}
	printf("数学最高分：%hd 最低分：%hd　平均分： %f \n",max_math,min_math,(float)(sum_math/student_count));
	for(int i=0;i<student_count;i++)
	{
		sum_eng+=stu[i].english_score;
		if(max_eng<stu[i].english_score)
		{
			max_eng=stu[i].english_score;
		}
		if(min_eng>stu[i].english_score)
		{
			min_eng=stu[i].english_score;
		}
	}
	printf("英语最高分：%hd 最低分：%hd　平均分： %f\n",max_eng,min_eng,(float)(sum_eng/student_count));
	
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	return;
}

void watch_person()//查看个人信息
{
	for(int i=0;i<student_count;i++)
	{
		if(0==strcmp(stu[record].stu_name,stu[i].stu_name))
		{
			printf("名字:%s\n性别:%d\n学号:%d\n密码:******\n语文成绩:%hd\n数学成绩:%hd\n英语成绩：%hd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].chinese_score,stu[i].math_score,stu[i].english_score);
		}
	}
		
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	return ;}
