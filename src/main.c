#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include "args.h"
#include "debug.h"
#include "tcp.h"

void serve_connection(int client,struct sockaddr_in client_addr,socklen_t client_addrlen);

int main(int argc,char **argv){
	DEBUG("starting");

	//============ process args ======================
	if(parse_args(argc,argv) != 0){
		FATAL("could not parse args");
		return 1;
	}

	//============ create and bind server =============
	int server = create_socket();

	struct addrinfo hints, *address_info;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	int result = getaddrinfo(NULL,"80",&hints,&address_info);
	if (result < 0){
		FATAL("could not get addressinfo");
		fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(result));
		close(server);
		return 1;
	}
	result = bind(server,address_info->ai_addr,address_info->ai_addrlen);
	if (result < 0){
		FATAL("could not bind server");
		perror("bind");
		close(server);
		return 1;
	}
	result = listen(server,20);
	if (result < 0){
		FATAL("could not start listening");
		perror("listen");
		close(server);
		return 1;
	}

	//=============== accept connections ==============
	for (;;){
		struct sockaddr_in client_addr;
		socklen_t client_addrlen = sizeof(client_addr);
		int client = accept(server,(struct sockaddr *)&client_addr,&client_addrlen);
		if (client < 0){
			ERROR("accept failed");
			perror("accept");
			close(client);
			continue;
		}

		DEBUG("connection accepted");
		serve_connection(client,client_addr,client_addrlen);

		close(client);
	}

	//============ cleanup =============================
	freeaddrinfo(address_info);
	close(server);
	DEBUG("finished");
}
void serve_connection(int client,struct sockaddr_in client_addr,socklen_t client_addrlen){
		//=============== get client ip ==============
		char client_ip[1024];
		if (inet_ntop(AF_INET,(struct in_addr *)&(client_addr.sin_addr),client_ip,sizeof(client_ip)) == NULL){
			ERROR("could not determine client ip");
			perror("inet_ntop");
			return;
		}
		printf("ip: %s\n",client_ip);
}
