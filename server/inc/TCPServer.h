#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TCPConnection.h"
#include "ServerApp.h"
#include "ServerConf.h"

#define MAXCLIENT 10
#define NO_ERROR 0

typedef struct
{
    int socket;
    const char* ip;
} SocketDescr;

int StartTCPServer(int port);
int Accept(int server);

#endif