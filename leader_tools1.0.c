#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>//usleep
#include "leader_tools.h"
#include "tools.h"

struct Teacher tea[100];
int cnt=0;
int flag=0;
char leader_menu()
{
	//不用goto(未实现(不一定实现))
	if(1==flag)
	{
		goto l_loop;
	}	
	char acc[256];//输入的账号
	char acc_1[255]={"admin"};
	char psw[256];//输入的密码
	system("clear");
	printf("请输入用户名:\n");
	scanf("%s",acc);
	flag=1;
	if(0==strcmp(acc, acc_1))
	{
	reinput:
		printf("请输入密码:\n");//校长密码保存到文件(未实现)
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
				printf("2、重置教师的密码\n");//√调用tools.c函数
				printf("3、添加教师\n");//√ 读写文件
				printf("4、删除教师\n");//√ 写入文件
				printf("5、显示所有在职教师\n");//√ 从文件中读取
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
			printf("密码错误!\n");
			usleep(0.5*1000000);
			goto reinput;//校长多次密码错误任然可以输入
		}
	}
	else
	{
		printf("用户名不存在!\n");
		usleep(1.0*1000000);
		return 0;
	}	
	return 0;
}

//重置教师密码
void reset_teapassword()
{
	strong_change();//调用tools.c的函数
}

//添加教师
void add_tea()
{
	printf("输入添加教师信息：\n");
	int i=0;
	FILE *frotea=fopen("OLteacher.txt","r+");
	if(NULL==frotea)//↑从文件中获取在职老师信息
	{
		printf("文件不存在");
		return ;
	}
	for(;;)
	{
		fscanf(frotea,"%s %d %d %s\n", tea[i].tea_name, &tea[i].sex_tea, &tea[i].tea_id, tea[i].tea_password);
		//↑从文件中获取信息
		if(0==tea[i].tea_id)
		{//判断结构体中的空位从文件中读取
			scanf("%s %d %d %s", tea[i].tea_name, &tea[i].sex_tea, &tea[i].tea_id, tea[i].tea_password);//输入添加的教师
			int str_l=0;
			str_l+=strlen(tea[i].tea_name);
			str_l+=sizeof(tea[i].sex_tea);
			str_l+=sizeof(tea[i].tea_id);//文件指针指会此行开头
			str_l+=strlen(tea[i].tea_password);
			fseek(frotea,-str_l,1);
			fprintf(frotea,"%s %d %d %s\n", tea[i].tea_name, tea[i].sex_tea,tea[i].tea_id, tea[i].tea_password);
			break;
		}
		i++;
		if(i==MAX)
		{
			printf("系统升级中,录入失败\n");
			break;
		}
	}
	fclose(frotea);
	printf("添加成功\n");
	usleep(1.0*1000000);	
}

//删除教师
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
		int i=0,j=0;
		FILE *frotea=fopen("OLteacher.txt","r");
		if(NULL==frotea)//↑从文件中获取在职老师信息
		{
			printf("文件不存在");
			return ;
		}
		for(;i<MAX;)
		{
			fscanf(frotea,"%s %d %d %s\n", tea[i].tea_name, &tea[i].sex_tea, &tea[i].tea_id, tea[i].tea_password);
			i++;
		}
		fclose(frotea);
		for(i=0;;)
		{
			if(tea[i].tea_id==tea_id2)
			{
				FILE* ftea=fopen("dieteacher.txt","a");
				if(NULL==ftea)
				{
					printf("文件不存在");
					return ;
				}
				fprintf(ftea,"%s %d %d %s\n", tea[i].tea_name, tea[i].sex_tea, tea[i].tea_id, tea[i].tea_password);
				fclose(ftea);								
				tea[i].tea_id=0;
				//修改存在文件内容 已实现(被删除的教师会存在但是ID为0)
				FILE *frotea=fopen("OLteacher.txt","r+");
				if(NULL==frotea)//↑打开在线老师信息文件
				{
					printf("文件不存在");
					return ;
				}
				for(;j<MAX;)
				{
					fscanf(frotea,"%s %d %d %s\n", tea[j].tea_name, &tea[j].sex_tea, &tea[j].tea_id, tea[j].tea_password);//获取文件信息
					if(tea_id2==tea[j].tea_id)
					{
						int str_l=0;
						str_l+=strlen(tea[j].tea_name);
						str_l+=sizeof(tea[j].sex_tea);
						str_l+=sizeof(tea[j].tea_id);
						str_l+=strlen(tea[j].tea_password);
						//获取前几个参数的位数把文件指针指回要修改一行的开头
						tea[j].tea_id=0;
						printf("--%d--\n", str_l);
						fseek(frotea,-str_l,1);
						fprintf(frotea,"%s %d %3d %s", tea[j].tea_name, tea[j].sex_tea, tea[j].tea_id, tea[j].tea_password);//只改变id为0,%3d可以为ID的最大位数
						//完全删除(未实现)					
						break;
					}
					j++;
				}
				fclose(frotea);
				printf("删除成功\n");
				break;
			}
			i++;
			if(i==MAX)
			{
				printf("没有寻找到此教师信息\n");
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

//显示在职教师
void show_onlineteacher()
{	
	int i=0;
	FILE *frotea=fopen("OLteacher.txt","r");
	if(NULL==frotea)//↑从文件中获取在职老师信息
	{
		printf("文件不存在");
		return ;
	}
	for(;i<MAX;)
	{
		fscanf(frotea,"%s %d %d %s\n", tea[i].tea_name, &tea[i].sex_tea, &tea[i].tea_id, tea[i].tea_password);
		if(0!=tea[i].tea_id)//用ID是否存在(为0)来判断
		{
			printf("%s--%d--%d--%s\n", tea[i].tea_name, tea[i].sex_tea, tea[i].tea_id, tea[i].tea_password);
		}
		i++;
	}
	fclose(frotea);
	usleep(1.5*1000000);
}

//显示离职教师
void show_dieteacher()
{
	//从文件中读取离职教师(
	int i=0;
	struct Teacher tea[MAX]={};
	FILE* ftea=fopen("dieteacher.txt","r");
	if(NULL==ftea)
	{
		printf("文件不存在");
		return ;
	}
	for(i=0;i<MAX;)
	{
		fscanf(ftea,"%s %d %d %s\n", tea[i].tea_name, &tea[i].sex_tea, &tea[i].tea_id, tea[i].tea_password);
		//从文件获取离职教师名字
		if(0==tea[i].tea_id)
		{
			break;
		}
		printf("%s\n", tea[i].tea_name);	
		i++;
		//无离职老师的显示(未实现(不一定要实现))	
	}
	fclose(ftea);
	usleep(1.0*1000000);
}

void save_data()
{
	//如果同一个老师重复删除也会重复记录，(未实现(不一定要实现))
	int i=0;
	FILE* otea=fopen("OLteacher.txt","a");
	if(NULL==otea)
	{
		printf("文件不存在");
		return ;
	}
	for(;i<MAX;)
	{
		if(0!=tea[i].tea_id)
		{
		fprintf(otea,"%s %d %d %s\n",tea[i].tea_name,tea[i].sex_tea,tea[i].tea_id,tea[i].tea_password);	
		}
		i++;		
	}		
	fclose(otea);	
	flag=0;//记录是否退出'校长系统用'
}
