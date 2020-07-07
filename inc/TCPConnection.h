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
#include "GPSInfo.h"

#define MAXMESSAGESIZE 1024

typedef enum
{
	SINGIN, LOGIN, DATA, SUCCESS, ERROR  

} MessageType;

typedef struct
{
	int userId;
	GPSInfo data;

} Data;

int Send(int socket, const char* message);
const char* Read(int socket);

#endif