#include <sys/socket.h>
#include <string.h>
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
int recvall(int sock,char **return_buffer){
	//for realloc to work
	return_buffer[0] = NULL;

	int return_buffer_length = 0;
	for (;;){
		//receive data
		char recv_buffer[5];
		int recv_buffer_length = recv(sock,recv_buffer,sizeof(recv_buffer),0);
		
		//realloc return buffer and fill it
		*return_buffer = realloc(return_buffer[0],return_buffer_length+recv_buffer_length);
		if (return_buffer == NULL){
			ERROR("realloc failed");
			perror("realloc");
			return -1;
		}
		char *return_buffer_end = *return_buffer+return_buffer_length;
		memcpy(return_buffer_end,recv_buffer,recv_buffer_length);
		return_buffer_length += recv_buffer_length;
		printf("%s\n",*return_buffer);
		if (strncmp(*return_buffer+return_buffer_length-4,"\r\n\r\n",4) == 0){//end of message
			break;
		}
	}
	return return_buffer_length;
}
