#include "teacher_tools.h"
#include "tools.h"

int tea_on=0;//在线检测标志

void open_data(void)//查看文本
{
	FILE* fp = fopen("student.txt","a");
	fclose(fp);
	fp = fopen("student.txt","r");
	rewind(fp);
	student_count=0;
	for(int i=0;;i++)
	{
		fscanf(fp,"%s %d %d %s %hd %hd %hd %hhd\n",stu[i].stu_name,&stu[i].stu_sex,&stu[i].stu_id,stu[i].stu_password,&stu[i].chinese_score,&stu[i].math_score,&stu[i].english_score,&stu[i].stu_error);
		if(stu[i].stu_sex==0) break;
		else student_count++;
	}
	fclose(fp);
}
//教师登录
void tea_link(void)
{	
	FILE* fp = fopen("OLteacher.txt","r");
	rewind(fp);
	int tcou=0;
	for(int i=0;;i++)
	{
		if(feof(fp)) break;
		fscanf(fp,"%s %d %d %s %hhd\n", tea[i].tea_name,&tea[i].tea_sex, &tea[i].tea_id,tea[i].tea_password,&tea[i].tea_error);
		tcou++;
	}
	fclose(fp);
	
	int j;
	char names[20];
	printf("请输入用户名:");
	scanf("%s",names);
	for(int i=0;i<tcou;i++)
	{
		if(0!=tea[i].tea_sex&&0==strcmp(names,tea[i].tea_name))
		{
			j=i;
			break;
		}
		if(0==tea[i].tea_sex||(tcou-1==i&&0!=strcmp(names,tea[i].tea_name)))
		{
			puts("无效用户名！");
			printf("请重试：");
			memset(names,0,sizeof(names));
			scanf("%s",names);
			i=-1;
		}	
	}

	if(tea[j].tea_error>3)
	{
		puts("用户名被锁定，请联系管理员");
		tea_on=2;
		return ;
	}
	char key[13];
	printf("请输入密码:");
	scanf("%s",key);
	if(0==tea[j].tea_error&&0==strcmp(key,tea[j].tea_password))
	{
		puts("初次登录请修改密码！");
		change_personpass();
		tea[j].tea_error++;
		tea_on=1;
		
		fp = fopen("OLteacher.txt","w");
		for(int i=0;i<tcou;i++)
		{
			fprintf(fp,"%s %d %d %s %hhd\n", tea[i].tea_name,tea[i].tea_sex, tea[i].tea_id,tea[i].tea_password,tea[i].tea_error);
		}
		fclose(fp);
	
		return ;
	}

	while(0!=strcmp(key,tea[j].tea_password))
	{
		tea[j].tea_error++;	
		if(tea[j].tea_error>3)
		{
			puts("用户名被锁定，请联系管理员");
			
			fp = fopen("OLteacher.txt","w");
			for(int i=0;i<tcou;i++)
			{
				fprintf(fp,"%s %d %d %s %hhd\n", tea[i].tea_name,tea[i].tea_sex, tea[i].tea_id,tea[i].tea_password,tea[i].tea_error);
			}
				
			fclose(fp);
			tea_on=2;
			return ;
		}
		printf("密码错误!请重试：");
		char new[13];
		scanf("%s",new);
		strcpy(key,new);
		memset(new,0,sizeof(new));

	}
	tea[j].tea_error=1;
	tea_on=1;
	
	fp = fopen("OLteacher.txt","w");
	for(int i=0;i<tcou;i++)
	{
		fprintf(fp,"%s %d %d %s %hhd\n", tea[i].tea_name,tea[i].tea_sex, tea[i].tea_id,tea[i].tea_password,tea[i].tea_error);
	}
	fclose(fp);
	
	
	return ;
}
//显示教师菜单
char tea_menu(void)
{
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
	open_data();
	if(student_count>=100)
	{
		printf("We need more space！");
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
		
		stu[i].stu_error=0;
		strcpy(stu[i].stu_password,"123456");
		
		stu[i].stu_id=srand_num();
		for(j=0;j<i;j++)
		{
			if(stu[i].stu_id==stu[j].stu_id)
			{
				stu[i].stu_id =srand_num();
				j=-1;
			}
		}
		student_count++;
	}
	
	
	save_studata();
	
	return ;
}
//删除学生
void del_stu(void)
{
	
	open_data();
	
	FILE* fdel = fopen("overlord.txt","a");
	
    int i;
	char names[20];
	printf("请输入学生姓名或学号：");
	scanf("%s",names);	
	for(i=0;i<student_count;i++)
	{
		if(0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names))
		{
			fprintf(fdel,"%s\n",stu[i].stu_name);
			stu[i].stu_sex=0;
			printf("%s已删除\n",stu[i].stu_name);
			memset(stu[i].stu_name,0,sizeof(stu[i].stu_name));

			fclose(fdel);
					
			break;
		}
		else if(student_count-1==i)
		{
			printf("未能找到相关学生信息\n");
				
			break;
		}
	}
		
	save_studata();
	
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	
	return ;

}
//查找在校学生信息
void find_stu(void)
{
	open_data();
	
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
			if(1==stu[i].stu_sex) printf("性别：男 \n");
			else if(2==stu[i].stu_sex) printf("性别：女 \n");
			printf("学号：%08d\n",stu[i].stu_id);
			
			
			if(stu[i].chinese_score || stu[i].math_score || stu[i].english_score)
				{
					printf("|语文%3hd|数学%3hd|英语%3hd|\n",stu[i].chinese_score,stu[i].math_score,stu[i].english_score);	
				}
				else printf("成绩信息未更新\n");
		}
	}
	if(flag) printf("未能找到相关学生信息\n");
	
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	
	return ;
}
//修改学生信息
void change_inf(void)
{
	open_data();
	
	int i,flag=1;
	char j,names[20];
	printf("请输入需要修改信息的学生姓名：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0==strcmp(names,stu[i].stu_name))
		{
			flag=0;
			printf("请重新输入学生的姓名和性别:");
			char nn[20];
			int ns;
			scanf("%s %d",nn,&ns);
			fflush(stdin);
			strcpy(stu[i].stu_name,nn);
			stu[i].stu_sex=ns;
			
			printf("是否需要修改成绩?(y/n)");
			
			scanf(" %c",&j);
			if('y'==j)
			{
				puts("1.语文");
				puts("2.数学");
				puts("3.英语");
				printf("修改哪项？");
				char ch=0;
				scanf(" %c",&ch);
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
			save_studata();
			return;
		}
		
	}
	if(flag) printf("未能找到相关学生信息\n");
	
	save_studata();
	
	return ;
}
//录入学生成绩
void import_score(void)
{
	int i;
	open_data();
	
	char names[20];
	printf("请输入需要登记成绩的学生姓名或学号：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if((0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names)))
		{
			printf("语文：");
			scanf("%hd",&stu[i].chinese_score);
		
			printf("数学：");
			scanf("%hd",&stu[i].math_score);
			
			printf("英语：");
			scanf("%hd",&stu[i].english_score);
			
		}
	}
	puts("成绩录入成功");
	
	save_studata();
	
	return ;
}
//显示在校/离校的学生信息
void show_allstu(void)
{
	int i,n;
	puts("1.在校");
	puts("2.辍学");
	
	scanf("%d",&n);
	
	if(1==n)
	{
		open_data();
		for(i=0;i<student_count;i++)
		{
			if(stu[i].stu_sex)
			{
				printf("姓名：%s ",stu[i].stu_name);
				if(1==stu[i].stu_sex) printf("性别：男\n");
				else if(2==stu[i].stu_sex) printf("性别：女\n");
				printf("学号：%08d\n",stu[i].stu_id);
			
				if(stu[i].chinese_score || stu[i].math_score || stu[i].english_score)
				{
					printf("|语文%3hd|数学%3hd|英语%3hd|\n",stu[i].chinese_score,stu[i].math_score,stu[i].english_score);	
				}
				else printf("成绩信息未更新\n");
			}
			printf("\n");
		}
	}
	else
	{
		char names[20];
		FILE* fdel = fopen("overlord.txt","r");
		while(1)
		{
			if(feof(fdel)) break;
			memset(names,0,sizeof(names));
			fscanf(fdel,"%s\n",names);
			printf("%s\n",names);
		}
		fclose(fdel);
	}
	
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续...");
	getch();
	
	return ;

}
//重置学生密码
void reset_stupassword(void)
{	
	int i,flag=1;
	open_data();
	
	char names[20];
	printf("请输入重置的学生姓名：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0==strcmp(names,stu[i].stu_name))
		{
			flag=0;
			strcpy(stu[i].stu_password,"123456");
			stu[i].stu_error=0;
			
			break;
		}
	}
	if(flag) printf("未能找到相关学生信息\n");
	
	save_studata();
	
	return ;
}
void save_studata(void)//保存文本
{

	FILE* save_stu = fopen("student.txt","w+");
	rewind(save_stu);
	for(int i=0;i<100;i++)
	{
		if(stu[i].stu_sex)fprintf(save_stu,"%s %d %d %s %hd %hd %hd %hhd\n",stu[i].stu_name,stu[i].stu_sex,stu[i].stu_id,stu[i].stu_password,stu[i].chinese_score,stu[i].math_score,stu[i].english_score,stu[i].stu_error);
	}
	fclose(save_stu);
	memset(stu,0,sizeof(stu));//释放结构体的数据
	printf("保存完毕");
	fflush(stdout);
	usleep(200000);
	for(int t=0;t<6;t++)
	{
		printf(".");
		fflush(stdout);
		usleep(300000);
	}
	printf("\n");
	
	return ;
}
