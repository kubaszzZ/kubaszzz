#include<stdio.h>
#include"tools.h"

struct Student stu[MAX];
struct Teacher tea[MAX];

int student_count=0;
int n=0;

void strong_tea_change()
{
		char names[20];
		printf("请输入要修改密码的姓名:");
		scanf("%s",names);
		
		//打开		
		FILE *frotea=fopen("OLteacher.txt","r+");
		if(NULL==frotea)//↑打开在线老师信息文件
		{
			printf("文件不存在");
			return ;
		}
		for(int j=0;j<MAX;j++)
		{
			fscanf(frotea,"%s %d %d %s %hhd\n", tea[j].tea_name, &tea[j].tea_sex, &tea[j].tea_id, tea[j].tea_password,&tea[j].tea_error);//获取文件信息----错误信息							
			if(strcmp(tea[j].tea_name,names)==0 && tea[j].tea_id!=0)
			{
				int str_l=0;
				str_l+=strlen(tea[j].tea_name);
				str_l+=sizeof(tea[j].tea_sex);
				str_l+=sizeof(tea[j].tea_id);
				str_l+=strlen(tea[j].tea_password);
				str_l+=sizeof(tea[j].tea_error);
				//获取前几个参数的位数把文件指针指回要修改一行的开头
				//tea[j].tea_error=0;
				strcpy(tea[j].tea_password,"123");
				tea[j].tea_error=0;
				printf("--%hhd--\n", tea[j].tea_error);
				fseek(frotea,-str_l-1,1);
				fprintf(frotea,"%s %d %3d %s %hhd\n", tea[j].tea_name, tea[j].tea_sex, tea[j].tea_id, tea[j].tea_password,tea[j].tea_error);//只改变error为0,%3d可以为ID的最大位数---错误次数(从fseek中减去位数)
						
				break;
			}
		}
		fclose(frotea);	
		printf("重置成功\n");
		usleep(1.0*1000000);	
}

//修改自己的密码
void change_stu_personpass(void)
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
		FILE* fp=fopen("student.txt","w");
		for(int k=0;k<student_count;k++)
		{
			fprintf(fp,"%s %d %d %s %hd %hd %hd %hhd\n",stu[k].stu_name,stu[k].stu_sex,stu[k].stu_id,stu[k].stu_password,stu[k].chinese_score,stu[k].math_score,stu[k].english_score,stu[k].stu_error);
		}
		fclose(fp);		
}

void change_tea_personpass(void)
{
	char names[20];
	printf("请输入要修改密码的姓名:");
	scanf("%s",names);
	for(int i=0;;i++)
	{
		if(strcmp(tea[i].tea_name,names)==0 && tea[i].tea_sex!=0)
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
void change_admin_personpass(void)
{
		char new_pass[10]={};
		printf("请校长输入你要修改的新密码:");
		scanf("%s",new_pass);
		strcpy(leader_password,new_pass);
		puts("密码修改成功");
}

void origin_menu(void)
{
	system("clear");
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	puts("┃欢迎使用中国计量大学教务在线┃");
	puts("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
	puts("┃       请选择您的身份       ┃");
	puts("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
	puts("┃1.学生                      ┃");
	puts("┃2.教职工                    ┃");
	puts("┃3.管理员                    ┃");
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	printf("请输入：");
	scanf("%d",&n);
}

//产生随机学号（1000-9999）
int srand_num()
{
	srand(time(NULL));
	return rand()%9000+1000;
}
void contiiinue(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	return ;
}
