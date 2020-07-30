#ifndef TEACHER_TOOLS_H
#define TEACHER_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
void save_studata(void);
#endif// TEACHER_TOOLS_H
