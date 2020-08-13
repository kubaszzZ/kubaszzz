#include "teacher_tools.h"
#include "tools.h"

int tea_on=ling;//在线检测标志　０——离线；１——在线；２——锁定

void open_data(void)			//查看文本
{
	FILE* fp = fopen("student.txt","a");
	fclose(fp);
	fp = fopen("student.txt","r");
	rewind(fp);
	student_count=0;
	for(int i=0;;i++)
	{
		fscanf(fp,"%s %d %d %s %hd %hd %hd %hhd\n",STFS);
		if(stu[i].stu_sex==0) break;
		else student_count++;
	}
	fclose(fp);
}
//教师登录
bool check_id(char* str)
{
	int len = strlen(str);
	if(len>=5) return false;
	for(int i=0;i<len;i++)
	{
		if(isalpha(str[i])) return false;
	}
	return true;
}
void tea_link(void)
{	
	/**************读取教师信息文本**************/
	FILE* fp = fopen("OLteacher.txt","r");
	rewind(fp);
	int tcou=0,order=0;
	char id_t[20];
	for(int i=0;;i++)
	{
		if(feof(fp)) break;
		fscanf(fp,"%s %d %d %s %hhd\n",TFS);
		tcou++;
	}
	fclose(fp);

	/****************教师工号判断****************/
	printf("请输入用户工号:");
	scanf("%s",id_t);
	for(int i=0;i<tcou;i++)
	{
		while(!check_id(id_t))
		{
			printf("工号非法,请重试：");
			bzero(id_t,sizeof(id_t));
			scanf("%s",id_t);
		}
		if(0!=tea[i].tea_sex && atoi(id_t)==tea[i].tea_id)
		{
			order=i;
			break;
		}
		if(0==tea[i].tea_sex||(tcou-1==i&&atoi(id_t)!=tea[i].tea_id))
		{
			printf("未找到工号,请重试：");
			bzero(id_t,sizeof(id_t));
			scanf("%s",id_t);
			i=fu1;				//重置下标以再次遍历
		}	
	}	
	
	/****************密码及锁定判断****************/
	if(tea[order].tea_error>3)	//密码错误计数为4时教师被锁定
	{
		puts("用户已被锁定，请联系管理员");
		tea_on=2;						
		return ;
	}

	char key[13];
	printf("请输入密码:");
	scanf("%s",key);
	if((0==tea[order].tea_error++)&&0==strcmp(key,tea[order].tea_password))
	{
		puts("初次登录请修改密码！");
		change_tea_personpass();	//密码错误计数为0为原始密码
		tea_on=1;				//修改完后直接处于在线模式
		fp = fopen("OLteacher.txt","w");
		for(int i=0;i<tcou;i++)	fprintf(fp,"%s %d %d %s %hhd\n",TFP);						
		fclose(fp);					
		
		return ;
	}
	while(0!=strcmp(key,tea[order].tea_password))
	{
		if(++tea[order].tea_error>3)
		{
			puts("用户已被锁定，请联系管理员");		
			fp = fopen("OLteacher.txt","w");
			for(int i=0;i<tcou;i++)	fprintf(fp,"%s %d %d %s %hhd\n",TFP);
			fclose(fp);
			tea_on=2;
			
			return ;
		}
		printf("密码错误!请重试：");
		memset(key,0,sizeof(key));
		scanf("%s",key);		
	}
	/****************登录成功及保存****************/			
	tea[order].tea_error=1;		//登录成功重置密码错误计数
	tea_on=1;
	fp = fopen("OLteacher.txt","w");
	for(int i=0;i<tcou;i++)	fprintf(fp,"%s %d %d %s %hhd\n",TFP);
	fclose(fp);
	
	return ;
}
//显示教师菜单
char tea_menu(void)
{
	open_data();
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
	if(student_count>=100)
	{
		printf("We need more space！");
		fflush(stdout);
		usleep(3333333);
		return ;
	}
	char fla=0;
	int i=0,j=0,num=1;
	printf("是否批量操作?(y/n)");
	scanf(" %c",&fla);
	if('y'==fla) 
	{
		printf("请输入人数：");
		scanf("%d",&num);
	}
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
	
	return ;
}
//删除学生
void del_stu(void)
{
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
	
	contiiinue();
	return ;
}
//查找在校学生信息
void find_stu(void)
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
			if(1==stu[i].stu_sex) printf("性别：男  \n");
			else if(2==stu[i].stu_sex) printf("性别：女  \n");
			printf("学号：2017%04d   ",stu[i].stu_id);
			if(stu[i].chinese_score||stu[i].math_score||stu[i].english_score)
				{
					printf("|语文%3hd|数学%3hd|英语%3hd|\n",stu[i].chinese_score,stu[i].math_score,stu[i].english_score);	
				}
				else printf("成绩信息未更新\n");
		}
	}
	if(flag) printf("未能找到相关学生信息\n");
	
	contiiinue();
	return ;
}
//修改学生信息
void change_inf(void)
{
	int i,flag=1;
	char sw,names[20];
	printf("请输入需要修改信息的学生姓名：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0==strcmp(names,stu[i].stu_name))
		{
			flag=0;
			printf("请重新输入学生的姓名和性别:");
			memset(names,0,sizeof(names));
			scanf("%s %d",names,&stu[i].stu_sex);
	 		printf("是否需要修改成绩?(y/n)");	
			scanf(" %c",&sw);
			if('y'==sw)
			{
				puts("1.语文");
				puts("2.数学");
				puts("3.英语");
				printf("修改哪项？");
				char ch=0;
				scanf(" %c",&ch);
				switch(ch)
				{
					case '1':scanf("%hd",&stu[i].chinese_score);break;
					case '2':scanf("%hd",&stu[i].math_score);break;
					case '3':scanf("%hd",&stu[i].english_score);break;
				}	
			}
			return;
		}	
	}
	if(flag) printf("未能找到相关学生信息\n");

	return ;
}
//录入学生成绩
void import_score(void)
{
	int i;	
	char names[20];
	printf("请输入需要登记成绩的学生姓名或学号：");
	scanf("%s",names);
	for(i=0;i<student_count;i++)
	{
		if(0==strcmp(names,stu[i].stu_name)||stu[i].stu_id==atoi(names))
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

	return ;
}
//显示在校/离校的学生信息
void show_allstu(void)
{
	puts("1.在校");
	puts("2.辍学");
	int i,n;
	scanf("%d",&n);
	if(1==n)
	{
		puts("┏━━━━━━━┳━━━━┳━━━━━━━━┳━━━━┳━━━━┳━━━━┓");
		puts("┃ 姓名  ┃性别┃  学号  ┃语文┃数学┃英语┃");
		puts("┣━━━━━━━╋━━━━╋━━━━━━━━╋━━━━╋━━━━╋━━━━┫");
		for(i=0;i<student_count;i++)
		{
			if(stu[i].stu_sex)
			{
				printf("┃%s\t",stu[i].stu_name);
				if(1<stu[i].stu_sex)printf("┃ 女 ");
				else if(1==stu[i].stu_sex)printf("┃ 男 ");
				printf("┃2017%04d┃",stu[i].stu_id);
				if(stu[i].chinese_score||stu[i].math_score||stu[i].english_score)
				{
					printf("%3hd ┃%3hd ┃%3hd ┃\n",stu[i].chinese_score,stu[i].math_score,stu[i].english_score);	
				}
				else printf("成绩信息未更新┃\n");
			}	
		}
		puts("┗━━━━━━━┻━━━━┻━━━━━━━━┻━━━━┻━━━━┻━━━━┛");
	}
	else
	{
		char names[20];
		FILE* fdel = fopen("overlord.txt","r");
		while(!feof(fdel))
		{
			memset(names,0,sizeof(names));
			fscanf(fdel,"%s\n",names);
			printf("%s\n",names);
		}
		fclose(fdel);
	}
	contiiinue();

	return ;
}
//重置学生密码
void reset_stupassword(void)
{	
	int i,flag=1;
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
	
	return ;
}
void save_studata(void)		//保存文本
{
	FILE* save_stu = fopen("student.txt","w+");
	for(int i=0;i<100;i++)
	{
		if(stu[i].stu_sex) fprintf(save_stu,"%s %d %d %s %hd %hd %hd %hhd\n",STFP);
	}
	fclose(save_stu);
	memset(stu,0,sizeof(stu));//释放结构体的数据
	printf("保存完毕");
	fflush(stdout);
	usleep(500000);
	return ;
}
