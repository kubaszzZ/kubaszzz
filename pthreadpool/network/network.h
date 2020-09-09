#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdbool.h>
#include <netinet/in.h>

// 网络通信结构
typedef struct NetWork
{
	int sock;					// socket描述符 				
	int type;					// 协议类型
	struct sockaddr_in addr; 	// 通信地址
	socklen_t len; 				// 地址字节数
	bool svr; 					// 服务端标志
}NetWork;

// 打开网络通信对象
NetWork* nw_open(int type,short port,const char* ip,bool svr);

// 等待客户端连接，成功网络对象
NetWork* nw_accept(NetWork* svr_nw);

// 发送数据(阻塞状态)
size_t nw_send(NetWork* nw,const char* buf,size_t len);

// 专门发送字符串
size_t nw_sends(NetWork* nw,const char* buf);

// 接收数据(阻塞状态)
size_t nw_recv(NetWork* nw,char* buf,size_t len);

// 关闭网络通信对象
void nw_close(NetWork* nw);

#endif//NETWORK_H
