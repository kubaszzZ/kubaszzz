#include "teacher_tools.h"
#include "tools.h"

//显示教师菜单
char tea_menu(void)
{
	
	FILE* fpx = fopen("OLteacher.txt","r+");
	for(int t=0;t<100;t++)
	{
		fscanf(fpx,"%s %d %d %s", tea[t].tea_name, &tea[t].tea_sex, &tea[t].tea_id,tea	[t].tea_password);
	}

	
	int i=0;
	char names[20];
	char key[13];
	printf("请输入用户名：");
	scanf("%s",names);
	while(i+1)
	{	
		if(99==i&&0!=strcmp(names,tea[i].tea_name))
		{
			printf("用户名不存在,请重新输入:");
			memset(names,0,sizeof(names));
			gets(names);
			i=-1;
		}
		else if(0==strcmp(names,tea[i].tea_name))
		{
			break;
		}
		i++;
	}
	if(tea[i].tea_error==4)
	{
		return 9;
	}

	printf("请输入密码：");
	scanf("%s",key);

	while(0!=strcmp(key,tea[i].tea_password))
	{
	
		tea[i].tea_error ++;
		printf("\n密码错误,请重试:");
		memset(key,0,sizeof(key));
		scanf("%s",key);	
		if(tea[i].tea_error==4) return 9;
	}
	
	if(tea[i].tea_error==0)
	{
		printf("初次登录请重置密码:");
		scanf("%s",tea[i].tea_password);
		tea[i].tea_error ++;
	}
	rewind(fpx);
	for(int t=0;t<100;t++)
	{
		if(tea[i].tea_sex)fprintf(fpx,"%s %d %d %s %hhd\n",tea[t].tea_name,tea[t].tea_sex,tea[t].tea_id,tea[t].tea_password,tea[i].tea_error);
	}
	fclose(fpx);
	system("clear");
	puts("┏━━━━━━━━━━━━━━━━━━━━━━━━┓");
	puts("┃欢迎使用学生信息管理系统┃");
	puts("┣━━━━━━━━━━━━━━━━━━━━━━━━┫");
	puts("┃ _1_ 添加学生信息       ┃");
	puts("┃ _2_ 删除学生信息       ┃"); 
	puts("┃ _3_ 查找学生信息       ┃"); 
	puts("┃ _4_ 修改学生信息       ┃"); 
	puts("┃ _5_ 录入学生成绩       ┃"); 
	puts("┃ _6_ 重置学生密码       ┃");
	puts("┃ _7_ 显示所有学生信息　 ┃");
	puts("┃ _8_ 保存信息并退出　   ┃");
	puts("┗━━━━━━━━━━━━━━━━━━━━━━━━┛");              
	printf("请输入指令：");
	char cmd;
	scanf("%hhd",&cmd);

	return cmd;
}
//添加学生
void add_stu()
{
	FILE* fp = fopen("student.txt","a+");
	fscanf(fp,"%d",&student_count);
	for(int i=0;i<=100;i++)
	{
		fscanf(fp,"%s %d %d %s|%hd %hd %hd %hhd",stu[i].stu_name,&stu[i].stu_sex,&stu[i].stu_id,stu[i].stu_password,&stu[i].chinese_score,&stu[i].math_score,&stu[i].english_score,&stu[i].stu_error);
	}
	


	if(student_count>=100)
	{
		printf("we need more space！");
		fflush(stdout);
		usleep(3333333);
		return ;
	}
	char fla=0;
	int i=0,j=0,num;
	printf("是否批量操作?(y/n)");
	fflush(stdin);
	scanf(" %c",&fla);
	
	if('y'==fla) 
	{
		printf("请输入人数：");
		scanf("%d",&num);
	}
	else num=1;
	while(num--)
	{
		i=0;
		while(stu[i].stu_sex) i++;
		printf("\n请输入新增学生的姓名和性别");
		scanf("%s %d",stu[i].stu_name,&stu[i].stu_sex);
		stu[i].stu_id=srand_num();
		stu[i].stu_error=0;
		sprintf(stu[i].stu_password,"123456");
		for(j=0;j<=student_count;j++)
		{
			if(j!=i && stu[i].stu_id==stu[j].stu_id)
			{
				stu[i].stu_id =srand_num();
				j=-1;
			}
		}
		student_count++;
	}
	return ;
}
//删除学生
void del_stu()
{
	
    int i;
	char names[20];
	printf("请输入学生姓名或学号：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(stu[i].stu_sex>0&&(0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names)))
		{
			stu[i].stu_sex=0;
			printf("%s已删除",stu[i].stu_name);
			student_count--;
		}
		if(i==student_count-1&&(0!=strcmp(names,stu[i].stu_name)||stu[i].stu_id!=atoi(names)))
		{
			printf("未能找到相关学生信息\n");
		}
	}
	
	return ;
}
//查找学生信息
void find_stu()
{
	int i,flag=1;
	char names[20];
	printf("请输入要查找的学生姓名或学号：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(stu[i].stu_sex>0&&(0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names)))
		{
			flag=0;
			printf("姓名：%s ",stu[i].stu_name);
			if(1==stu[i].stu_sex) printf("性别：男\n");
			else if(2==stu[i].stu_sex) printf("性别：女\n");
			printf("学号：%08d\n",stu[i].stu_id);
		}
	}
	if(flag) printf("未能找到相关学生信息\n");
}
//修改学生信息
void change_inf()
{
	int i;
	char j=0,names[20];
	printf("请输入需要修改信息的学生姓名：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0<stu[i].stu_sex&&0==strcmp(names,stu[i].stu_name))
		{
			printf("请重新输入学生的姓名和性别:");
			scanf("%s %d",stu[i].stu_name,&stu[i].stu_sex);
			printf("是否需要修改成绩?(y/n)");
			fflush(stdin);
			scanf("%c",&j);
			if('y'==j)
			{
				puts("1.语文");
				puts("2.数学");
				puts("3.英语");
				printf("修改哪项？");
				char ch=0;
				scanf("%c",&ch);
				switch(ch)
				{
					case '1':
						scanf("%hd",&stu[i].chinese_score);
						break;
					case '2':
						scanf("%hd",&stu[i].math_score);
						break;
					case '3':
						scanf("%hd",&stu[i].english_score);
						break;
				}	
			}
			else return;
		}
	}
	printf("未能找到相关学生信息\n");
	return ;
}
//录入学生成绩
void import_score()
{
	int i;
	char names[20];
	printf("请输入需要登记成绩的学生姓名或学号：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(stu[i].stu_sex>0&&(0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names)))
		{
			printf("语文：");
			scanf("%hd",&stu[i].chinese_score);
			printf("数学：");
			scanf("%hd",&stu[i].math_score);
			printf("英语：");
			scanf("%hd",&stu[i].english_score);
		}
	}
}
//显示所有学生信息
void show_allstu()
{
// FILE* fp = fopen("student.txt","r")
	//puts("1.在校");
	//puts("2.辍学");
	
	for(int i=0;i<student_count;i++)
	{
		printf("姓名：%s",stu[i].stu_name);
		if(1==stu[i].stu_sex) printf("性别：男\n");
		else if(2==stu[i].stu_sex) printf("性别：女\n");
		printf("学号：%08d\n",stu[i].stu_id);
		if(stu[i].chinese_score && stu[i].math_score && stu[i].english_score)
		{
			printf("语文%hd数学%hd英语%hd\n",stu[i].chinese_score,stu[i].math_score,stu[i].english_score);	
		}
		else printf("成绩信息未更新\n");
	}
		return ;
}
//重置学生密码
void reset_stupassword()
{	
	int i;
	char names[20];
	printf("请输入重置的学生姓名：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0<stu[i].stu_sex&&0==strcmp(names,stu[i].stu_name))
		{
			strcpy(stu[i].stu_password,"123456");
			stu[i].stu_error=0;
			return;
		}
	}
	printf("未能找到相关学生信息\n");
	return ;
}
void save_studata(void)
{
	FILE* save_stu = fopen("student.txt","w+");
	int i;
	fprintf(save_stu,"%d\n",student_count);
	
	for(i=0;i<student_count;i++)
	{
		fprintf(save_stu,"%s %d %d %s|%hd %hd %hd|%hhd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].stu_password,stu[i].chinese_score,stu[i].math_score,stu[i].english_score,stu[i].stu_error);
	}
	printf("保存完毕.");
	fflush(stdout);
	usleep(500000);
	printf(".");
	fflush(stdout);
	usleep(500000);
	printf(".");
	fflush(stdout);
	usleep(500000);
	printf(".");
	fflush(stdout);
	usleep(500000);
	printf(".");
	fflush(stdout);
	usleep(500000);
	printf(".");
	fflush(stdout);
	usleep(500000);
	printf("\n");
	fclose(save_stu);
	return ;
}
