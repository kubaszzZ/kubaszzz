#ifndef LEADER_TOOLS_H
#define LEADER_TOOLS_H
#define OLT "OLteacher.txt"	//	设置在校教师

//	显示校长菜单
char leader_menu();

//	初次登录账号
void ccdl_zh();

//	初次登录修改密码
void ccdl_mm();

//	退出时保存数据到文件中
void save_data();

//	重置教师密码
void reset_teapassword();

//	添加教师
void add_tea();

//	删除教师
void del_tea();

//	显示在职教师
void show_onlineteacher();

//	显示离职教师
void show_dieteacher();


#endif// LEADER_TOOLS_H
