#ifndef GAME2048_H
#define GAME2048_H

extern int (*view)[4];

// 初始化相关资源、加载数据
void init_game(void);

// 运行游戏
void run_game(void);

// 释放相关资源、保存数据
void exit_game(void);

#endif//GAME2048_H
