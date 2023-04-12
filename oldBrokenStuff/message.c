#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 5000
struct iplist {int Numbr; int* Sockets;} connections;
// socket, <command> <args>
// connect 
// send

//not working on rn
//use multithreading for connections

void checkNull(void* pointer){if(pointer==NULL){fprintf(stderr,"OUT OF MEM");exit(1);}}

char* socketrecv(int socketSev) {
 int buffLen = 100;
 int messageLen;
 char* command;
 char* buff = (char*) malloc(buffLen*sizeof(char*));
 messageLen = recv(mysocket, buff, buffLen-1, 0);
 buff[messageLen] = NULL;
 fprintf(stderr,"%s\n",buff);
 // not going to work use a string compare function
 if (strcmp((strtok(buffer,':')=command),"command")==1) {

 }else (command=="message"){
 
 }
 }
}

int main(int argc, char* argv) {
 if (argc!=2){fprintf(stderr,"NEEDS IP ADDR OF CLIENT\n");exit(1);}
 struct sockaddr_in socketAddr;
 int socketSev;
 memset(&socketAddr, 0, sizeof(socketAddr));
 connections.Numb = 0;
 connections.Ip = (char**) malloc(sizeof(char**));
 strcpy(connections.Ip[0],argv[1]); 
 if(( socketSev = socket(AF_INET, SOCK_STREAM, 0))!=0) {fprintf(stderr,"ERROR MAKING SOCKET\n");exit(1);}
 // 172.168.0.1:5000
 // for testing
 socketAddr.sin_family = AF_INET;
 socketAddr.sin_port = htons(PORT);
 socketAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
 connect(socketSev, (struct sockaddr *)&socketAddr, sizeof(struct sockaddr_in));
 //code go here
 
}
