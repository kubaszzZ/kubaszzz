#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

typedef struct sockaddr* SP;

int main()
{
	int svr_sock = socket(AF_INET,SOCK_STREAM,0);
	if(0 > svr_sock)
	{
		perror("socket");
		return EXIT_FAILURE;
	}

	struct sockaddr_in svr_addr = {} , cli_addr = {};
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(8866);
	svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t addr_len = sizeof(svr_addr);

	if(bind(svr_sock,(SP)&svr_addr,addr_len))
	{
		perror("bind");
		return EXIT_FAILURE;
	}

	if(listen(svr_sock,5))
	{
		perror("listen");
		return EXIT_FAILURE;
	}
	
	fd_set reads , result;
	FD_ZERO(&reads);
	FD_SET(svr_sock,&reads);

	char buf[4096] = {};
	struct timeval timeout = {5,5000};
	int fd_max = svr_sock , fd_min = svr_sock , fd_num = 0 , buf_size  = sizeof(buf);

	for(;;)
	{
		result = reads;
		fd_num = select(fd_max+1,&result,NULL,NULL,&timeout);
		if(0 == fd_num)
		{
			continue;
		}
		if(0 > fd_num)
		{
			perror("select");
			return EXIT_FAILURE;
		}

		for(int fd=fd_min; fd<=fd_max; fd++)
		{
			if(FD_ISSET(fd,&result))
			{
				if(fd == svr_sock)
				{
					int cli_sock = accept(svr_sock,(SP)&cli_addr,&addr_len);
					if(0 > cli_sock)
					{
						perror("accept");
						return EXIT_FAILURE;
					}
					FD_SET(cli_sock,&reads);
					if(cli_sock > fd_max) fd_max = cli_sock;
					if(cli_sock < fd_min) fd_min = cli_sock;
				}
				else
				{
					int ret_size = recv(fd,buf,buf_size,0);
					if(0 >= ret_size || 0 == strcmp("quit",buf))
					{
						if(fd == fd_max) fd_max--;
						if(fd == fd_min) fd_min++;
						FD_CLR(fd,&reads);
						close(fd);
						continue;
					}
					printf("recv:[%s],bits:%d\n",buf,ret_size);
					strcat(buf,":return");
					send(fd,buf,strlen(buf)+1,0);
				}
			}
		}
	}
}
