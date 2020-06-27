#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stddef.h>
#include "User.h"

#define MAXPACKETSIZE 300

typedef enum data_type_e
{
	USERNAME, PASSWORD, COMMAND 

} data_type_t;

typedef struct
{
	data_type_t dataType;
	char data[MAXPACKETSIZE];

} Message;

int Send(int socket, Message* message);
Message* Read(int socket);

#endif