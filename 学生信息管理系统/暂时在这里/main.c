#include<stdio.h>
#include"tools.h"
#include"teacher_tools.h"
#include"stu_tools.h"
#include"leader_tools.h"
int main()
{
    int n=0;
	
		
		puts("请选择登陆的身份：");
		puts("1.student");
		puts("2.teacher");
		puts("3.leader");
		printf("请输入：");
		scanf("%d",&n);
	while(1)
	{
		if(1==n)
		{
			
			switch(stu_menu())
			{
				case 1:find_score();break;
				case 2:change_personpass();break;
				case 3:watch_person();break;
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
				case 8:save_data();break;
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
			}
		}
		
	}
}
