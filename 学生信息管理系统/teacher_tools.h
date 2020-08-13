#ifndef TEACHER_TOOLS_H
#define TEACHER_TOOLS_H

#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

extern int tea_on;

//显示教师菜单
char tea_menu(void);

//添加学生
void add_stu(void);

//删除学生
void del_stu(void);

//查找学生信息
void find_stu(void);

//修改学生信息
void change_inf(void);

//录入学生成绩
void import_score(void);

//显示所有学生信息
void show_allstu(void);

//重置学生密码
void reset_stupassword(void);

//读取文件
void open_data(void);

//保存文件
void save_studata(void);

//教师登录
void tea_link(void);

bool check_id(char* str);
#endif// TEACHER_TOOLS_H
