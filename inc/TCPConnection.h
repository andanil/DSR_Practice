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

typedef enum
{
	SINGIN, LOGIN, SENDDATA, SUCCESS, ERROR  

} MessageType;

typedef struct
{
	MessageType messageType;
	User user;

} Message;

int Send(int socket, Message* message);
Message* Read(int socket);

#endif