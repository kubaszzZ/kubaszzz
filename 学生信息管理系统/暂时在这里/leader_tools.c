#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getch.h>//usleep
#include "leader_tools.h"
#include "tools.h"
//文件名加了"0.1"后缀 编译记得修改
//男1女2
/*
struct Teacher
{
	char tea_name[20];
	int tea_sex;
	char stu_id[8];
	char stu_password;
};
*/


// 显示校长菜单
/*校长：
	admin 
    1、第一次登录强制修改密码。
    2、能重置自己的密码
    3、能重置教师密码
    4、添加教师//.a的方式
	5、删除教师
    6、显示所有在职教师
    7、显示所有离职教师
    */

int cnt=0;
int flag=0;
char leader_menu()
{
	if(1==flag)
	{
		goto l_loop;
	}
	
	char acc[256];
	char acc_1[255]={"admin"};
	char psw[256];
	
	system("clear");
	printf("请输入用户名:\n");
	scanf("%s",acc);
	flag=1;
	

	if(0==strcmp(acc, acc_1))
	{
		printf("请输入密码:\n");
		scanf("%s",psw);
		if(0==cnt)
		{
			cnt++;
			strcpy(leader_password,psw);
		}
		if(0==strcmp(psw, leader_password))
		{
			for(;;)
			{
			l_loop:
				system("clear");
				printf("1、重置自己的密码\n");//√
				printf("2、重置教师的密码\n");
				printf("3、添加教师\n");//√
				printf("4、删除教师\n");//√ 写入文件
				printf("5、显示所有在职教师\n");//√
				printf("6、显示所有离职教师\n");//√
				printf("7、退出\n");//√ 退出后记录在文件
				printf("请输入操作:");
				int n=0;
				scanf("%d", &n);
				
				return n;	
			}
		}
		else
		{
			printf("密码错误!\n");//直接返回密码输入位置 未实现
		}
	}
	else
	{
		printf("用户名不存在!\n");
		return 0;
	}	
	return 0;
}

//重置教师密码
void reset_teapassword()
{
	strong_change();
	/*
	printf("输入要重置的老师的
	printf("重置成功\n");
	usleep(1.5*1000000);
	*/
}

//添加教师
void add_tea()
{
	printf("输入添加教师信息：\n");
	int i=0;
	for(;;)
	{
		if(0==tea[i].tea_id)
		{
			scanf("%s %d %d %s", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id, tea	[i].tea_password);
			break;
		}
		i++;//达到上限没实现
	}
		printf("添加成功\n");
	    usleep(1000000);		
}
//删除教师
void del_tea()//用工号学号删除
{

	printf("输入删除教师的工号:");
	int tea_id2=0;
	scanf("%d", &tea_id2);
	printf("请再次输入教师工号:");
	int tea_id1=0;
	scanf("%d", &tea_id1);
	if(tea_id2==tea_id1)
	{
		int i=0;
		for(;;)
		{
			if(tea[i].tea_id==tea_id2)
			{
				
				FILE* ftea=fopen("dieteacher.txt","a");
				if(NULL==ftea)
				{
					printf("文件不存在");
					return ;
				}
				fprintf(ftea,"%s %d %d %s\n", tea[i].tea_name, tea[i].tea_sex, tea[i].tea_id, tea	[i].tea_password);
				fclose(ftea);				
				
								
				tea[i].tea_id=0;

				printf("删除成功\n");
				break;
			}
			i++;//达到上限没实现
		}
	}
	else
	{
		printf("两次输入的工号不一样!\n");
	}
	usleep(1.0*1000000);

}

//显示在职教师
void show_onlineteacher()
{	
	int i=0;
	for(;;)
	{
		if(0!=tea[i].tea_id)
		{
			printf("%s--%d--%d--%s\n", tea[i].tea_name, tea[i].tea_sex, tea[i].tea_id, tea	[i].tea_password);
			
		}
		i++;
		if(100==i)
		{
			break;
		}
	}
	printf("显示在职\n");
	usleep(1.0*1000000);
}

//显示离职教师
void show_dieteacher()
{
	for(int i=0;;i++)
	{
		if(0==tea[i].tea_id && 0!=tea[i].tea_name)
		{		
			printf("%s \n", tea[i].tea_name);
		}
		
		if(i==MAX)
		{
			break;
		}		
	}
	usleep(1.0*1000000);
}
void save_data()
{
	int i=0;
	FILE* otea=fopen("OLteacher.txt","a");
	if(NULL==otea)
	{
		printf("文件不存在");
		return ;
	}
	for(;i<MAX;i++)
	{
		if(0!=tea[i].tea_id)
		{
		fprintf(otea,"%s %d %d %s\n", tea[i].tea_name, tea[i].tea_sex, tea[i].tea_id, tea	[i].tea_password);	
		}
	}		
	fclose(otea);			
}
