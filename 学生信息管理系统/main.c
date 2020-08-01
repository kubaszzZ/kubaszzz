#include<stdio.h>
#include"tools.h"
#include"teacher_tools.h"
#include"stu_tools.h"
#include"leader_tools.h"

int main()
{
	int n=0;
	while(1)
	{
		if(!n)
		{	
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
		if(1==n)
		{
			read_student();
			open_data();
			switch(stu_menu())
			{
				
				case 1:stu_online();break;
				case 2:find_score();break;
				case 3:change_personpass();break;
				case 4:watch_person();break;
				case 5:return 0;
			}
		}
		else if(2==n)
		{
			if(tea_on==0) tea_link();
			if(tea_on==1)
			{	
				switch(tea_menu())
				{
					case 1:add_stu();break;
					case 2:del_stu();break;
					case 3:find_stu();break;
					case 4:change_inf();break;
					case 5:import_score();break;
					case 6:reset_stupassword();break;
					case 7:show_allstu();break;
					case 8:n=0;tea_on=0;save_studata();break;
				}
			}
			else if(tea_on==2)
			{
				n=0;
				tea_on=0;
			}					
		}
		else if(3==n)
		{
			switch(leader_menu())
			{
				case 1:change_personpass();break;
				case 2:reset_teapassword();break;
				case 3:add_tea();break;
				case 4:del_tea();break;
				case 5:show_onlineteacher();break;
				case 6:show_dieteacher();break;
				case 7:n=0;open_data();save_data();break;
			}
		}
	}
}
