#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stddef.h>

#define MAXPACKETSIZE 1024

typedef enum data_type_e
{
	USERNAME, PASSWORD, COMMAND 

} data_type_t;

typedef struct message_e
{
	data_type_t dataType;
	char data[MAXPACKETSIZE];

} message_t;

int Send(int socket, message_t* message);
message_t* Read(int socket);

#endif