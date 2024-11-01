#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
int create_socket(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0){
		ERROR("could not create socket");
		perror("socket");
		return -1;
	}
	int optval = 1;
	int result = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
	if (result < 0){
		ERROR("could not set the socket to reusable");
		perror("setsockopt");
		return -1;
	}
	return sockfd;
}
