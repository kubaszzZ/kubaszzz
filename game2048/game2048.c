#include <getch.h>
#include "game2048.h"
#include "direction.h"
#include "tools.h"

int (*view)[4] = NULL;

// 初始化相关资源、加载数据
void init_game(void)
{
	debug("%s\n",__func__);
	// 初始化随机数
	// 申请堆内存
	// 从文件中加载数据	
}

// 运行游戏
void run_game(void)
{
	debug("%s\n",__func__);
	for(;;)
	{
		// 显示界面
		show_view();
		// 随机产生一个数字
		rand_number();
		// 检查是否还能继续
		if(is_godie())
		{
			exit_game();
			return;
		}
		// 获取方向键并处理
		switch(getch())
		{
			case 183:up(); break;
			case 184:down(); break;
			case 185:right(); break;
			case 186:left(); break;
		}
	}
}

// 释放相关资源、保存数据
void exit_game(void)
{
	debug("%s\n",__func__);
	// 保存数据
	// 释放堆内存
}
