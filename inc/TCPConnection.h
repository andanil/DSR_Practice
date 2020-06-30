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

typedef enum
{
	SINGIN, LOGIN, SENDDATA, SUCCESS, ERROR  

} MessageType;

typedef struct
{
	MessageType messageType;
	User user;

} Message;

typedef struct
{
	int userId;
	GPSInfo data;

} Data;

int Send(int socket, Message* message);
Message* Read(int socket);

int SendData(int socket, Data* message);
Data* ReadData(int socket);

#endif