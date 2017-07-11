 ///
 /// @file    server.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-22 10:13:03
 ///
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(void)
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == listenfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	
	int reuse = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse, (socklen_t)sizeof(reuse)) < 0)
	{
		perror("setsockopt resueaddr error");
		close(listenfd);
		exit(EXIT_FAILURE);
	}

	//实现系统级别的负载均衡
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (void*)&reuse, (socklen_t)sizeof(reuse)) < 0)
	{
		perror("setsockopt reuseport error");
		close(listenfd);
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);//主机字节序转成网络字节序列
	serverAddr.sin_addr.s_addr = INADDR_ANY;//代表本机地址
	
	int ret = bind(listenfd, 
				   (struct sockaddr *)&serverAddr,
				   sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(listenfd);
		exit(EXIT_FAILURE);
	}

	ret = listen(listenfd, 10);
	if(-1 == ret)
	{
		perror("listen");
		close(listenfd);
		exit(EXIT_FAILURE);
	}
	
	int peerFd = accept(listenfd, NULL, NULL);
	
	char buff[1024] = "welcome to server.";//用户态的应用缓冲区
	ret = write(peerFd, buff, strlen(buff));//将应用缓冲区的数据直接copy到内核
	
	while(1)
	{
		memset(buff, 0, 1024);
		ret = read(peerFd, buff, 1024);//将内核缓冲区中的数据直接copy到应用缓冲区
		ret = write(peerFd, buff, strlen(buff));
	}
	
	return 0;
}
