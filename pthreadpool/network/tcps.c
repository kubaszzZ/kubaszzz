#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "network.h"

void* run(void* arg)
{
	NetWork* nw = (NetWork*)arg;
	char buf[4096] = {};
	size_t buf_size = sizeof(buf);

	for(;;)
	{
		size_t ret_size = nw_recv(nw,buf,buf_size);
		if(0 == ret_size || strcmp("quit",buf))
		{
			perror("nw_recv");
			free(nw);
			return NULL;
		}

		printf("recv:[%s] %d\n",buf,ret_size);
		strcat(buf,":return");
		nw_sends(nw,buf);
	}
}

int main()
{
	NetWork* svr_nw = nw_open(SOCK_STREAM,2345,"192.168.0.125",true);
	if(NULL == svr_nw)
	{
		printf("nw_open 函数执行出错误！\n");
		return EXIT_FAILURE;
	}

	for(;;)
	{
		NetWork* nw = nw_accept(svr_nw);
		if(NULL == nw)
		{
			printf("nw_accept 函数执行错误！\n");
			return EXIT_FAILURE;
		}

		pthread_t tid;
		pthread_create(&tid,NULL,run,nw);
	}
}
