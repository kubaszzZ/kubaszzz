#include <stdio.h>
#include "leader_tools.h"
#include "tools.h"
int leader_s_menu();

int cnt=0;
int flag=0;
char leader_menu()
{
	if(1==flag)
	{
		return leader_s_menu();
	}	
	char acc[256];//输入的账号
	char acc_1[255]={"admin"};
	char psw[256];//输入的密码
	int pswk1=0;
	do{
		system("clear");
		printf("请输入用户名:\n");
		scanf("%s",acc);
		if(0==strcmp(acc, acc_1))
		{
			flag=1;
			if(0==cnt)
			{
				do{
					printf("请输入初始密码:");
					scanf("%s",psw);
					if(0==strcmp(psw,"123"))
					{
						do{
							printf("初次登入重置密码:");
							char fpsw1[256];
							char fpsw2[256];
							scanf("%s", fpsw1);
							printf("再次输入:");
							scanf("%s", fpsw2);
							if(0==strcmp(fpsw1,fpsw2))
							{
								strcpy(leader_password,fpsw1);
									cnt=1;
							}
							else
							{
								printf("两次密码输入不一致!\n");	
							}
						}while(cnt==0);
					}
					else
					{
						printf("密码错误！\n");
					}
				}while(cnt==0);
			}//设置初始密码
			int pswk=0;
			do{
				printf("请输入密码:\n");//校长密码保存到文件(未实现)
				scanf("%s",psw);
				if(0==strcmp(psw, leader_password))
				{
					pswk=1;
					for(;;)
					{				
						return leader_s_menu();						
					}
				}
				else
				{
					printf("密码错误!\n");
					usleep(0.5*1000000);
					//校长多次密码错误任然可以输入
				}
			}while(pswk==0);
		}
		else
		{
			printf("用户名不存在!\n");
			usleep(1.0*1000000);
		}	
	}while(pswk1==0);
	return 0;
}

//重置教师密码
void reset_teapassword()
{
	strong_tea_change();//调用tools.c的函数
}

//添加教师
void add_tea()
{
	printf("输入添加教师的姓名性别工号：\n");
	int i=0;
	FILE *frotea=fopen("OLteacher.txt","a+");
	if(NULL==frotea)//↑从文件中获取在职老师信息
	{
		printf("文件不存在");
		return ;
	}
	for(;;i++)
	{
		if(i==MAX)
		{
			printf("系统升级中,录入失败\n");
			break;
		}
		fscanf(frotea,"%s %d %d %s %hhd\n", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id, tea[i].tea_password,&tea[i].tea_error);
		//↑从文件中获取信息--错误次数
		if(0==tea[i].tea_id)
		{//判断结构体中的空位从文件中读取
			scanf("%s %d %d", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id);//输入添加的教师--错误次数
			int str_l=0;
			strcpy(tea[i].tea_password,"123");
			tea[i].tea_error=0;
			str_l+=strlen(tea[i].tea_name);
			str_l+=sizeof(tea[i].tea_sex);
			str_l+=sizeof(tea[i].tea_id);//文件指针指回此行开头
			str_l+=strlen(tea[i].tea_password);
			str_l+=sizeof(tea[i].tea_error);
			fseek(frotea,-str_l,1);
			fprintf(frotea,"%s %d %d %s %2hhd\n", tea[i].tea_name, tea[i].tea_sex,tea[i].tea_id, tea[i].tea_password,tea[i].tea_error);
			//--错误次数
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
		for(;i<MAX;i++)
		{
			fscanf(frotea,"%s %d %d %s %hhd\n", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id, tea[i].tea_password,&tea[i].tea_error);
		}		//--错误次数
		fclose(frotea);
		for(i=0;;i++)
		{
			if(i==MAX)
			{
				printf("没有寻找到此教师信息\n");
				break;	
			}
			if(tea[i].tea_id==tea_id2)
			{
				FILE* ftea=fopen("dieteacher.txt","a");
				if(NULL==ftea)
				{
					printf("文件不存在");
					return ;
				}
				fprintf(ftea,"%s %d %d %s\n", tea[i].tea_name, tea[i].tea_sex, tea[i].tea_id, tea[i].tea_password);
				fclose(ftea);								
				tea[i].tea_id=0;
				//修改存在文件内容 			
				
				FILE *frotea=fopen("OLteacher.txt","r+");
				if(NULL==frotea)//↑打开在线老师信息文件
				{
					printf("文件不存在");
					return ;
				}
				for(;j<MAX;j++)
				{
					fscanf(frotea,"%s %d %d %s %hhd\n", tea[j].tea_name, &tea[j].tea_sex, &tea[j].tea_id, tea[j].tea_password,&tea[i].tea_error);//获取文件信息----错误信息
							
					if(tea_id2==tea[j].tea_id)
					{
						int str_l=0;
						str_l+=strlen(tea[j].tea_name);
						str_l+=sizeof(tea[j].tea_sex);
						str_l+=sizeof(tea[j].tea_id);
						str_l+=strlen(tea[j].tea_password);
						str_l+=sizeof(tea[j].tea_error);
						//获取前几个参数的位数把文件指针指回要修改一行的开头
						tea[j].tea_sex=0;
						tea[j].tea_id=0;
						fseek(frotea,-str_l,1);
						fprintf(frotea,"%s %d %d %s %hhd\n", tea[j].tea_name, tea[j].tea_sex, tea[j].tea_id, tea[j].tea_password,tea[j].tea_error);//只改变id为0,%3d可以为ID的最大位数---错误次数(从fseek中减去位数)
											
						break;
					}
				}
				fclose(frotea);
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

//显示在职教师
void show_onlineteacher()
{	
	FILE *frotea=fopen("OLteacher.txt","r");
	if(NULL==frotea)//↑从文件中获取在职老师信息
	{
		printf("文件不存在");
		return ;
	}
	for(int i=0;i<MAX;i++)
	{
		fscanf(frotea,"%s %d %d %s %hhd\n", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id, tea[i].tea_password,&tea[i].tea_error);
		if(0!=tea[i].tea_id)//用ID是否存在(为0)来判断---错误次数
		{
			printf("%s--%d--%d--%s--%hhd\n", tea[i].tea_name, tea[i].tea_sex, tea[i].tea_id, tea[i].tea_password,tea[i].tea_error);
		}		//错误次数
	}
	fclose(frotea);
	usleep(1.5*1000000);
}

//显示离职教师
void show_dieteacher()
{
	//从文件中读取离职教师(
	struct Teacher tea[MAX]={};
	FILE* ftea=fopen("dieteacher.txt","r");
	if(NULL==ftea)
	{
		printf("文件不存在");
		return ;
	}
	for(int i=0;i<MAX;i++)
	{
		fscanf(ftea,"%s %d %d %s\n", tea[i].tea_name, &tea[i].tea_sex, &tea[i].tea_id, tea[i].tea_password);
		//从文件获取离职教师名字
		if(0==tea[i].tea_id)
		{
			break;
		}
		printf("%s\n", tea[i].tea_name);	
		//无离职老师的显示(未实现(不一定要实现))	
	}
	fclose(ftea);
	usleep(1.0*1000000);
}

void save_data()
{
	flag=0;//记录是否退出'校长系统用'
}

int leader_s_menu()
{
	system("clear");
	printf("┏━━━━━━━━━━━━━━━━━━━┓\n");			
	printf("┃    校长管理系统   ┃\n");
	printf("┣━━━━━━━━━━━━━━━━━━━┫\n");				
	printf("┃1、重置自己的密码  ┃\n");//√
	printf("┃2、重置教师的密码  ┃\n");//√调用tools.c函数
	printf("┃3、添加教师	    ┃\n");//√ 读写文件
	printf("┃4、删除教师	    ┃\n");//√ 写入文件
	printf("┃5、显示所有在职教师┃\n");//√ 从文件中读取
	printf("┃6、显示所有离职教师┃\n");//√ 	
	printf("┃7、退出	    ┃\n");//√ 退出后记录在文件
	printf("┗━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请输入操作:");
	int n=0;
	scanf("%d", &n);				
	return n;
}
