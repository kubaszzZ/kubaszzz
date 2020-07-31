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
			puts("请选择登陆的身份：");
			puts("1.student");
			puts("2.teacher");
			puts("3.leader");
			printf("请输入：");
			scanf("%d",&n);
		}
		if(1==n)
		{
			read_student();
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
			switch(tea_menu())
			{
				case 1:add_stu();break;
				case 2:del_stu();break;
				case 3:find_stu();break;
				case 4:change_inf();break;
				case 5:import_score();break;
				case 6:reset_stupassword();break;
				case 7:show_allstu();break;
				case 8:n=0;save_studata();break;
				case 9:
					printf("已锁定，请联系校长解锁");
					fflush(stdout);
					usleep(1000000);
					n=0;
					break;
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
				case 7:n=0;save_data();break;
			}
		}
		else if(4==n)
		{
			return 0;
		}	
	}
}
