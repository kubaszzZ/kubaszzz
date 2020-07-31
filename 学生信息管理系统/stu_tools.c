#include<stdio.h>
#include "stu_tools.h"
#include"tools.h"

int wrong=0;
char student_name[20];//学生姓名
int flag_1=0;//０为未登录，１为登录

void read_student()//读取学生信息
{
	FILE* fp=fopen("student.txt","r+");	
	for(int i=0;i<2;i++)
	{
  		fscanf(fp,"%s %d %d %s %hd %hd %hd",stu[i].stu_name,&stu[i].stu_sex,&stu[i].stu_id,stu[i].stu_password,&stu[i].chinese_score,&stu[i].math_score,&stu[i].english_score);
  		printf("%s %d %d %s %hd %hd %hd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].stu_password,stu[i].chinese_score,stu[i].math_score,stu[i].english_score);
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
	puts("｜   	  1、登录　  　　　　 ｜");
	puts("｜   	 ２、查询成绩　 　　　｜");
	puts("｜       ３、修改密码　　　　 ｜");
	puts("｜       ４、查看个人信息　　 ｜");
	puts("｜       ５、退出　　　　　　 ｜");
	puts("———————————————————————————————");
	puts("请输入选项：");
	scanf("%d",&option);
	if(5==option) return option;
	if(1==option&&0==flag_1) return option;
	else if(1==option&&1==flag_1) printf("已登录");
	while(1!=option&&0==flag_1)
	{
		if(5==option) return option;
		printf("请先登录：");
		scanf("%d",&option);
	}
	return option;
	/*if(2<=option&&4>=option&&1==flag_1)
	{
		return option;
	}
	else if(2<=option&&4>=option&&0==flag_1)
	{
		printf("请先登录：");
		scanf("%d",&option);
	}
	if(5==option) return option;
	if(1==option) return option;
	if(2<=option&&4>=option&&1==flag_1)
	{
		return option;
	}
	else
	{
		printf("请先登录：");
		scanf("%d",&option);
	}*/
}
	/*while(1!=option||flag_1)
	{
		if(0==flag_1)
		{
			printf("请先登录：");
		}
		if(5==option) return option;
		else return option;
		scanf("%d",&option);
	}*/

void stu_online()//登录
{
	int cmp=0,record=0,num=0;
	char student_password[10]={};
	printf("请输入姓名、密码:");
	scanf("%s %s",student_name,student_password);
	for(int i=0;i<2;i++)
	{
		if(0==strcmp(stu[i].stu_name,student_name))
		{
			record=i;
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
			cmp=strcmp("12345",student_password);
			if(0==cmp)
			{
				printf("强制修改密码：\n");
				strong_change();
			}
			wrong=0;
			flag_1=1;
			return;
		}
		else
		{
			printf("密码错误，重新输入：");
			wrong++;
			scanf("%s ",student_password);
		}
		if(3==wrong) 
		{
			printf("密码输入错误已达３次，账号已锁定");  
			return;
		}
		/*printf("密码错误，重新输入：");
		wrong++;
		scanf("%s %s",student_name,student_password);*/
	}
	return;
}
	/*while(3>wrong)
	{
		for(int i=0;i<2;i++)
		{
			if(0==strcmp(stu[i].stu_name,student_name)&&0==strcmp(stu[i].stu_password,student_password))
			{
				printf("登录成功");
				cmp=strcmp("12345",student_password);
				if(0==cmp)
				{
					printf("强制修改密码：\n");
					strong_change();
				}
			}
			
		}*/
		
		/*if(3==wrong)
		{
			printf("账号已锁定");
			return;
		}*/
		/*while(wrong<3)
		{
			if(0==strcmp(stu[i].stu_name,student_name)&&0==strcmp(stu[i].stu_password,student_password))
			{
				printf("登录成功!");
				cmp=strcmp("12345",student_password);
				if(0==cmp)
				{
					printf("强制修改密码：\n");
					strong_change();
				}
				flag_1=1;
				wrong=0;
				break;
			}
			else if(0!=strcmp(stu[i].stu_name,student_name))
			{
				for(int j=i+1;j<2;j++)
				{
					wrong++;
					printf("密码错误，请重新输入：");
					printf("%s %s\n",stu[i].stu_name,stu[i].stu_password);
					scanf("%s %s",student_name,student_password);
				}
			}
		
		}
		if(3==wrong)
		{
			printf("密码输入错误已达３次，账号已锁定\n");
			return;
		}
	}*/
void find_score() //查看成绩
{
  	int max_chinese=0,min_chinese=100,max_eng=0,min_eng=100,max_math=0,min_math=100;
  	int sum_chinese=0,sum_eng=0,sum_math=0;
	for(int i=0;i<2;i++)
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
	printf("语文最高分：%hd 最低分：%hd 平均分：%f\n",max_chinese,min_chinese,(float)(sum_chinese/100));
	for(int i=0;i<2;i++)
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
	printf("数学最高分：%hd 最低分：%hd　平均分： %f \n",max_math,min_math,(float)(sum_math/100));
	for(int i=0;i<2;i++)
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
	printf("英语最高分：%hd 最低分：%hd　平均分： %f\n",max_eng,min_eng,(float)(sum_eng/100));
	return;
}

void watch_person()//查看个人信息
{
	for(int i=0;i<2;i++)
	{
		if(student_name==stu[i].stu_name)
		{
			printf("名字:%s\n性别:%d\n学号:%d\n密码:******\n语文成绩:%hd\n数学成绩:%hd\n英语成绩：%hd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].chinese_score,stu[i].math_score,stu[i].english_score);
		}
	}
	return;
}
