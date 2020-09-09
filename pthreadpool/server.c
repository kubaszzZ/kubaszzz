#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "threadpool.h"
#define CLIENT_MAX 50

NetWork* cli_nw[CLIENT_MAX];

void add_nw(NetWork* nw)
{
	for(int i=0; i<CLIENT_MAX; i++)
	{
		if(NULL == cli_nw[i])
		{
			cli_nw[i] = nw;
			return;
		}
	}
}

void del_nw(NetWork* nw)
{
	for(int i=0; i<CLIENT_MAX; i++)
	{
		if(nw == cli_nw[i])
		{
			nw_close(nw);
			cli_nw[i] = NULL;
			return;
		}
	}
}

void send_nw(NetWork* nw,const char* buf)
{
	for(int i=0; i<CLIENT_MAX; i++)
	{
		if(cli_nw[i] && cli_nw[i]!=nw)
		{
			nw_sends(cli_nw[i],buf);
		}
	}
}

void task(void* arg)
{
	printf("--------------task---------------\n");
	NetWork* nw = arg;
	add_nw(nw);
	char buf[4096] = {};
	char name[20] = {};
	nw_recv(nw,name,sizeof(name));

	sprintf(buf,"!!!欢迎%s进入聊天室!!!\n",name);
	send_nw(nw,buf);

	// 接收内容广播
	for(;;)
	{
		int ret_size = nw_recv(nw,buf,sizeof(buf));
		if(0 == ret_size || 0==strcmp("quit",buf))
		{
			del_nw(nw);
			return;
		}

		strcat(buf,":");
		strcat(buf,name);
		send_nw(nw,buf);
	}
}

int main()
{
	ThreadPool* tp = tp_create(50,30,task);
	NetWork* svr_nw = nw_open(SOCK_STREAM,5566,"192.168.0.125",true);
	if(NULL == svr_nw)
	{
		printf("nw_open 函数出错！\n");
	}
	start(tp);
	for(;;)
	{
		NetWork* nw = nw_accept(svr_nw);
		if(NULL == nw)
		{
			printf("nw_accept 函数出错！\n");
			return EXIT_FAILURE;
		}
		printf("--------------accept------\n");
		tp_push(tp,nw);
	}
}
