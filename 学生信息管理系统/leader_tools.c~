#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>			//	usleep
#include "leader_tools.h"
#include "tools.h"

void ccdl_mm();
//-------------
struct Teacher tea[100];
int cnt=0;
int flag=0;
char acc[256];							//	输入的账号
char acc_1[255]={"admin"};				//	初始的账号
char psw[256];							//	输入的密码

void ccdl_zh()							//	初次登录的账号输入
{
	system("clear");
	printf("请输入账号:");
	scanf("%s",acc);
	if(0!=strcmp(acc, acc_1))
	{
		printf("输入账号有误!\n");
		usleep(0.75*1000000);
		ccdl_zh();
		return ;
	}
	else if(0==strcmp(acc, acc_1) && 0==cnt)
	{
		printf("请输入初始密码:");
		ccdl_mm();
	}
	else if(0==strcmp(acc, acc_1) && 1==cnt)
	{
		printf("请输入密码:");
		ccdl_mm();
	}
}
void ccdl_mm()							//	初次登录的密码输入
{
	scanf("%s",psw);
	if(0!=strcmp(psw,"123") && 0==cnt)
	{
		printf("输入初始密码有误！，请重新输入:");
		ccdl_mm();
	}
	else if(0!=strcmp(psw,leader_password) && 1==cnt)
	{
		printf("输入密码有误！，请重新输入：");
		ccdl_mm();
	}
	else if(0==strcmp(psw,"123"))		//	初始密码设置为"123"
	{
		do{
			printf("初次登入重置密码:");
			char fpsw1[256];			//	第一次输入的重置的密码
			char fpsw2[256];			//	第二次输入的重置的密码
			scanf("%s", fpsw1);
			printf("再次输入重置密码:");
			scanf("%s", fpsw2);
			if(0==strcmp(fpsw1,fpsw2))
			{
				strcpy(leader_password,fpsw1);
				cnt=1;
				flag=1;
			}
			else if(0==strcmp(fpsw1,fpsw2) && 10==strlen(fpsw1))
			{
				printf("密码过长!\n");
			}
			else
			{
				printf("两次密码输入不一致!\n");	
			}
		}while(cnt==0);
	}
	flag=1;								//	剩余情况密码正确自动进入系统
}

void scan_file()						//	文件夹读取函数(进入lesadr_menu读一次, 退出后存储
{
	FILE *frotea=fopen(OLT,"r");
	for(int i=0;i<MAX;i++)
	{
		fscanf(frotea,"%s %d %d %s %hhd\n", tea[i].t_name, &tea[i].t_sex, &tea[i].t_id, tea[i].t_password,&tea[i].t_error);
	}
	fclose(frotea);
}

//memset(tea,0,sizeof(tea));//释放结构体

char leader_menu()						//	进入菜单选择功能
{				
	if(0==flag)
	{
		scan_file();
		ccdl_zh();
	}	
	system("clear");
	printf("┏━━━━━━━━━━━━━━━━━━━┓\n");			
	printf("┃    校长管理系统   ┃\n");
	printf("┣━━━━━━━━━━━━━━━━━━━┫\n");				
	printf("┃1、重置自己的密码  ┃\n");		//	1 √
	printf("┃2、重置教师的密码  ┃\n");		//	2 √调用tools.c函数
	printf("┃3、添加教师	    ┃\n");		//	3 √ 读写文件
	printf("┃4、删除教师	    ┃\n");		//	4 √ 写入文件
	printf("┃5、显示所有在职教师┃\n");		//	5 √ 从文件中读取
	printf("┃6、显示所有离职教师┃\n");		//	6 √ 	
	printf("┃7、退出	    ┃\n");			//	7 √ 退出后记录在文件
	printf("┗━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请输入操作:");
	int n=0;
	scanf("%d", &n);				
	return n;
}

//	添加教师	功能3
void add_tea()
{
	//printf("输入添加教师的姓名性别工号：\n");
	for(int i=0;;i++)
	{
		if(i==MAX)
		{
			printf("系统升级中,录入失败\n");
			break;
		}
		if(0==tea[i].t_id)
		{
			strcpy(tea[i].t_password,"123");
			tea[i].t_error=0;
			printf("-%d-输入添加教师姓名:",i);							//	获取教师姓名
			do{
				scanf("%s",tea[i].t_name);
				if(20 < strlen(tea[i].t_name))
				{
					printf("输入的姓名不合法!请重新输入:");
				}
			}while(20 < strlen(tea[i].t_name));			//	最大姓名长度
			printf("输入添加教师性别:");							//	获取教师性别
			do{
				scanf("%d",&tea[i].t_sex);
				if(1!=tea[i].t_sex && 2!=tea[i].t_sex)
				{
					printf("输入的性别不合法!请重新输入:");
				}
			}while(1 != tea[i].t_sex && 2 != tea[i].t_sex);
			printf("输入添加教师工号:");							
			scanf("%d",&tea[i].t_id);
			break;
		}
	}
	printf("添加成功\n");
	usleep(1.0*1000000);	
}

//删除教师	功能4
void del_tea()//用工号学号删除
{
	//先从文件获取信息
	printf("输入删除教师的工号:");
	int tea_id2=0;
	scanf("%d", &tea_id2);
	printf("请再次输入教师工号:");
	int tea_id1=0;
	scanf("%d", &tea_id1);
	if(tea_id2==tea_id1)
	{
		int i=0;
		for(i=0;;i++)
		{
			if(i==MAX)
			{
				printf("没有寻找到此教师信息\n");
				break;	
			}
			if(tea[i].t_id == tea_id2)
			{								
				tea[i].t_id=0;
				printf("删除成功\n");
				break;
			}
		}
	}
	else
	{
		printf("两次输入的工号不一样!\n");
	}
	usleep(1.0*1000000);//延迟显示
}

//	显示在职教师	功能5
void show_onlineteacher()
{	
	for(int i=0;i<MAX;i++)
	{
		if(0 != tea[i].t_id)						//	用ID是否存在(为0)来判断
		{
			printf("-%d-%5s--%d--%4d--%4s--%hhd\n",i, tea[i].t_name, tea[i].t_sex, tea[i].t_id, tea[i].t_password,tea[i].t_error);
		}		
	}
	usleep(1.5*1000000);
}

//	显示离职教师	功能6
void show_dieteacher()
{
	for(int i=0;i<MAX;i++)
	{
		if(0 != tea[i].t_sex && 0 == tea[i].t_id)	//	用ID和性别来判定离职教师
		{
			printf("%s\n", tea[i].t_name);	
		}
	}
	usleep(1.0*1000000);
}

//	退出系统
void save_data()
{
	//	如果同一个老师重复删除也会重复记录，(未实现(不一定要实现))
	//	保存在职教师
	FILE *frotea=fopen(OLT,"w+");
	for(int i=0;i<MAX;i++)
	{
		if(0 != tea[i].t_sex)
		{
			fprintf(frotea,"%s %d %d %s %hhd\n", tea[i].t_name, tea[i].t_sex, tea[i].t_id, tea[i].t_password,tea[i].t_error);
		}
	}
	fclose(frotea);
	flag=0;											//	记录是否退出'校长系统用'
}

