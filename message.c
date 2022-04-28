#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 5000;
struct iplist {int connectionNumb; char** connectionIp;} connections;

// socket, <command> <args>
// connect 
// send

main(int argc, char* argv) {
 if (argc!=2){fprintf(stderr,"NEEDS IP ADDR OF CLIENT\n");exit(1);}
 struct sockaddr_in socketAddr;
 memset(&socketAddr, 0, sizeof(socketAddr));
 connections.connetionNumb = 0;
 connections.connectionIp = (char**) mollic(sizeof(char**));
 strcpy(connections.connectionIp[0],argv[1]); 
 
 if((int socket = socket(AF_INET, SOCK_STREAM, 0))!=0) {fprintf(stderr,"ERROR MAKING SOCKET\n");exit(1);
 // 0.0.0.0:5000
 socketAddr.sin_family = AF_INET;
 socketAddr.sin_port = htons(PORT);
 socketAddr.sin_addr.s_addr = htonl(0.0.0.0); 
 connect(socket, (struct sockaddr *)&socketAddr, sizeof(struct sockaddr_in));
}

