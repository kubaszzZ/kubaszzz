#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "network.h"

typedef struct sockaddr* SP;

// 打开网络通信对象
NetWork* nw_open(int type,short port,const char* ip,bool svr)
{
	NetWork* nw = malloc(sizeof(NetWork));
	nw->sock = socket(AF_INET,type,0);
	if(0 > nw->sock)
	{
		free(nw);
		perror("socket");
		return NULL;
	}

	nw->type = type;
	nw->len = sizeof(nw->addr);
	nw->addr.sin_family = AF_INET;
	nw->addr.sin_port = htons(port);
	nw->addr.sin_addr.s_addr = inet_addr(ip);

	if(svr)
	{
		nw->svr = true;

		if(bind(nw->sock,(SP)&nw->addr,nw->len))
		{
			free(nw);
			perror("bind");
			return NULL;
		}

		if(SOCK_STREAM == type)
		{
			if(listen(nw->sock,50))
			{
				free(nw);
				perror("listen");
				return NULL;
			}
		}
	}
	else if(SOCK_STREAM == type)
	{
		if(connect(nw->sock,(SP)&nw->addr,nw->len))
		{
			free(nw);
			perror("listen");
			return NULL;
		}
	}

	return nw;
}

// 等待客户端连接，成功网络对象
NetWork* nw_accept(NetWork* svr_nw)
{
	if(SOCK_STREAM != svr_nw->type || !svr_nw->svr)
	{
		printf("svr_nw error!\n");
		return NULL;
	}

	NetWork* nw = malloc(sizeof(NetWork));
	nw->len = sizeof(nw->addr);

	nw->sock = accept(svr_nw->sock,(SP)&nw->addr,&nw->len);
	if(0 > nw->sock)
	{
		free(nw);
		perror("accept");
		return NULL;
	}

	nw->type = SOCK_STREAM;
	nw->svr = false;

	return nw;
}

// 发送数据(阻塞状态)
size_t nw_send(NetWork* nw,const char* buf,size_t len)
{
	if(SOCK_STREAM == nw->type)
	{
		return send(nw->sock,buf,len,0);
	}
	else
	{
		return sendto(nw->sock,buf,len,0,(SP)&nw->addr,nw->len);
	}
}

// 专门发送字符串
size_t nw_sends(NetWork* nw,const char* buf)
{
	if(SOCK_STREAM == nw->type)
	{
		return send(nw->sock,buf,strlen(buf)+1,0);
	}
	else
	{
		return sendto(nw->sock,buf,strlen(buf)+1,0,(SP)&nw->addr,nw->len);
	}
}

// 接收数据(阻塞状态)
size_t nw_recv(NetWork* nw,char* buf,size_t len)
{
	if(SOCK_STREAM == nw->type)
	{
		return recv(nw->sock,buf,len,0);
	}
	else
	{
		return recvfrom(nw->sock,buf,len,0,(SP)&nw->addr,&nw->len);
	}
}

// 关闭网络通信对象
void nw_close(NetWork* nw)
{
	close(nw->sock);
	free(nw);
}
